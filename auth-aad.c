/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single TCP/UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2002-2018 OpenVPN Inc <sales@openvpn.net>
 *  Copyright (C) 2016-2018 Selva Nair <selva.nair@gmail.com>
 *  Copyright (C) 2019 Lucas Ramage <lramage@cyberninjas.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * OpenVPN plugin module to do Azure Active Directory authentication using a split
 * privilege model.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <security/pam_appl.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include "utils.h"

#include <openvpn-plugin.h>

#define DEBUG(verb) ((verb) >= 4)

/* Command codes for foreground -> background communication */
#define COMMAND_VERIFY 0
#define COMMAND_EXIT   1

/* Response codes for background -> foreground communication */
#define RESPONSE_INIT_SUCCEEDED   10
#define RESPONSE_INIT_FAILED      11
#define RESPONSE_VERIFY_SUCCEEDED 12
#define RESPONSE_VERIFY_FAILED    13

/*
 * Plugin state, used by foreground
 */
struct auth_aad_context
{
    /* Foreground's socket to background process */
    int foreground_fd;

    /* Process ID of background process */
    pid_t background_pid;

    /* Verbosity level of OpenVPN */
    int verb;
};

/*
 * Name/Value pairs for conversation function.
 * Special Values:
 *
 *  "USERNAME" -- substitute client-supplied username
 */

#define N_NAME_VALUE 16

struct name_value {
    const char *name;
    const char *value;
};

struct name_value_list {
    int len;
    struct name_value data[N_NAME_VALUE];
};

/* Background process function */
static void aad_server(int fd, const char *service, int verb, const struct name_value_list *name_value_list);


/*
 * Socket read/write functions.
 */

static int
recv_control(int fd)
{
    unsigned char c;
    const ssize_t size = read(fd, &c, sizeof(c));
    if (size == sizeof(c))
    {
        return c;
    }
    else
    {
        /*fprintf (stderr, "AUTH-AAD: DEBUG recv_control.read=%d\n", (int)size);*/
        return -1;
    }
}

static int
send_control(int fd, int code)
{
    unsigned char c = (unsigned char) code;
    const ssize_t size = write(fd, &c, sizeof(c));
    if (size == sizeof(c))
    {
        return (int) size;
    }
    else
    {
        return -1;
    }
}

static int
recv_string(int fd, char *buffer, int len)
{
    if (len > 0)
    {
        ssize_t size;
        memset(buffer, 0, len);
        size = read(fd, buffer, len);
        buffer[len-1] = 0;
        if (size >= 1)
        {
            return (int)size;
        }
    }
    return -1;
}

static int
send_string(int fd, const char *string)
{
    const int len = strlen(string) + 1;
    const ssize_t size = write(fd, string, len);
    if (size == len)
    {
        return (int) size;
    }
    else
    {
        return -1;
    }
}

#ifdef DO_DAEMONIZE

/*
 * Daemonize if "daemon" env var is true.
 * Preserve stderr across daemonization if
 * "daemon_log_redirect" env var is true.
 */
static void
daemonize(const char *envp[])
{
    const char *daemon_string = get_env("daemon", envp);
    if (daemon_string && daemon_string[0] == '1')
    {
        const char *log_redirect = get_env("daemon_log_redirect", envp);
        int fd = -1;
        if (log_redirect && log_redirect[0] == '1')
        {
            fd = dup(2);
        }
        if (daemon(0, 0) < 0)
        {
            fprintf(stderr, "AUTH-AAD: daemonization failed\n");
        }
        else if (fd >= 3)
        {
            dup2(fd, 2);
            close(fd);
        }
    }
}

#endif /* ifdef DO_DAEMONIZE */

/*
 * Close most of parent's fds.
 * Keep stdin/stdout/stderr, plus one
 * other fd which is presumed to be
 * our pipe back to parent.
 * Admittedly, a bit of a kludge,
 * but posix doesn't give us a kind
 * of FD_CLOEXEC which will stop
 * fds from crossing a fork().
 */
static void
close_fds_except(int keep)
{
    int i;
    closelog();
    for (i = 3; i <= 100; ++i)
    {
        if (i != keep)
        {
            close(i);
        }
    }
}

/*
 * Usually we ignore signals, because our parent will
 * deal with them.
 */
static void
set_signals(void)
{
    signal(SIGTERM, SIG_DFL);

    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
}

/*
 * Return 1 if query matches match.
 */
static int
name_value_match(const char *query, const char *match)
{
    while (!isalnum(*query))
    {
        if (*query == '\0')
        {
            return 0;
        }
        ++query;
    }
    return strncasecmp(match, query, strlen(match)) == 0;
}

OPENVPN_EXPORT int
openvpn_plugin_open_v3(const int v3structver,
                       struct openvpn_plugin_args_open_in const *args,
                       struct openvpn_plugin_args_open_return *ret)
{
    pid_t pid;
    int fd[2];

    struct auth_aad_context *context;
    struct name_value_list name_value_list;

    const int base_parms = 2;

    const char **argv = args->argv;
    const char **envp = args->envp;

    /* Check API compatibility -- struct version 5 or higher needed */
    if (v3structver < 5)
    {
        fprintf(stderr, "AUTH-AAD: This plugin is incompatible with the running version of OpenVPN\n");
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    /*
     * Allocate our context
     */
    context = (struct auth_aad_context *) calloc(1, sizeof(struct auth_aad_context));
    if (!context)
    {
        goto error;
    }
    context->foreground_fd = -1;

    /*
     * Intercept the --auth-user-pass-verify callback.
     */
    ret->type_mask = OPENVPN_PLUGIN_MASK(OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY);

    /*
     * Get verbosity level from environment
     */
    {
        const char *verb_string = get_env("verb", envp);
        if (verb_string)
        {
            context->verb = atoi(verb_string);
        }
    }

    /*
     * Make a socket for foreground and background processes
     * to communicate.
     */
    if (socketpair(PF_UNIX, SOCK_DGRAM, 0, fd) == -1)
    {
        fprintf(stderr, "AUTH-AAD: socketpair call failed\n");
        goto error;
    }

    /*
     * Fork off the privileged process.  It will remain privileged
     * even after the foreground process drops its privileges.
     */
    pid = fork();

    if (pid)
    {
        int status;

        /*
         * Foreground Process
         */

        context->background_pid = pid;

        /* close our copy of child's socket */
        close(fd[1]);

        /* don't let future subprocesses inherit child socket */
        if (fcntl(fd[0], F_SETFD, FD_CLOEXEC) < 0)
        {
            fprintf(stderr, "AUTH-AAD: Set FD_CLOEXEC flag on socket file descriptor failed\n");
        }

        /* wait for background child process to initialize */
        status = recv_control(fd[0]);
        if (status == RESPONSE_INIT_SUCCEEDED)
        {
            context->foreground_fd = fd[0];
            ret->handle = (openvpn_plugin_handle_t *) context;
            return OPENVPN_PLUGIN_FUNC_SUCCESS;
        }
    }
    else
    {
        /*
         * Background Process
         */

        /* close all parent fds except our socket back to parent */
        close_fds_except(fd[1]);

        /* Ignore most signals (the parent will receive them) */
        set_signals();

#ifdef DO_DAEMONIZE
        /* Daemonize if --daemon option is set. */
        daemonize(envp);
#endif

        /* execute the event loop */
        aad_server(fd[1], argv[1], context->verb, &name_value_list);

        close(fd[1]);

        exit(0);
        return 0; /* NOTREACHED */
    }

error:
    if (context)
    {
        free(context);
    }
    return OPENVPN_PLUGIN_FUNC_ERROR;
}

OPENVPN_EXPORT int
openvpn_plugin_func_v1(openvpn_plugin_handle_t handle, const int type, const char *argv[], const char *envp[])
{
    struct auth_aad_context *context = (struct auth_aad_context *) handle;

    if (type == OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY && context->foreground_fd >= 0)
    {
        /* get username from envp string array */
        const char *username = get_env("username", envp);

        if (username && strlen(username) > 0 && password)
        {
            if (send_control(context->foreground_fd, COMMAND_VERIFY) == -1
                || send_string(context->foreground_fd, username) == -1
            {
                fprintf(stderr, "AUTH-AAD: Error sending auth info to background process\n");
            }
            else
            {
                const int status = recv_control(context->foreground_fd);
                if (status == RESPONSE_VERIFY_SUCCEEDED)
                {
                    return OPENVPN_PLUGIN_FUNC_SUCCESS;
                }
                if (status == -1)
                {
                    fprintf(stderr, "AUTH-AAD: Error receiving auth confirmation from background process\n");
                }
            }
        }
    }
    return OPENVPN_PLUGIN_FUNC_ERROR;
}

OPENVPN_EXPORT void
openvpn_plugin_close_v1(openvpn_plugin_handle_t handle)
{
    struct auth_aad_context *context = (struct auth_aad_context *) handle;

    if (DEBUG(context->verb))
    {
        fprintf(stderr, "AUTH-AAD: close\n");
    }

    if (context->foreground_fd >= 0)
    {
        /* tell background process to exit */
        if (send_control(context->foreground_fd, COMMAND_EXIT) == -1)
        {
            fprintf(stderr, "AUTH-AAD: Error signaling background process to exit\n");
        }

        /* wait for background process to exit */
        if (context->background_pid > 0)
        {
            waitpid(context->background_pid, NULL, 0);
        }

        close(context->foreground_fd);
        context->foreground_fd = -1;
    }

    free(context);
}

OPENVPN_EXPORT void
openvpn_plugin_abort_v1(openvpn_plugin_handle_t handle)
{
    struct auth_aad_context *context = (struct auth_aad_context *) handle;

    /* tell background process to exit */
    if (context && context->foreground_fd >= 0)
    {
        send_control(context->foreground_fd, COMMAND_EXIT);
        close(context->foreground_fd);
        context->foreground_fd = -1;
    }
}

/*
 * Return 1 if authenticated and 0 if failed.
 * Called once for every username/password
 * to be authenticated.
 */
static int
aad_auth(const char *service, const struct user_pass *up)
{
    int status = SUCCESS;
    int ret = 0;
    const int name_value_list_provided = (up->name_value_list && up->name_value_list->len > 0);

    if (status == SUCCESS)
    {
        /* Call AAD to verify username */
        status = aad_authenticate(pamh, 0);
        if (status == SUCCESS)
        {
            status = pam_acct_mgmt(pamh, 0);
        }
        if (status == SUCCESS)
        {
            ret = 1;
        }

        /* Output error message if failed */
        if (!ret)
        {
            fprintf(stderr, "AUTH-AAD: BACKGROUND: user '%s' failed to authenticate: %s\n",
                    up->username,
        }

    }

    return ret;
}

/*
 * Background process -- runs with privilege.
 */
static void
aad_server(int fd, const char *service, int verb, const struct name_value_list *name_value_list)
{
    int command;

    /*
     * Do initialization
     */
    if (DEBUG(verb))
    {
        fprintf(stderr, "AUTH-AAD: BACKGROUND: INIT service='%s'\n", service);
    }

    /*
     * Tell foreground that we initialized successfully
     */
    if (send_control(fd, RESPONSE_INIT_SUCCEEDED) == -1)
    {
        fprintf(stderr, "AUTH-AAD: BACKGROUND: write error on response socket [1]\n");
        goto done;
    }

    /*
     * Event loop
     */
    while (1)
    {
        memset(&up, 0, sizeof(up));
        up.verb = verb;
        up.name_value_list = name_value_list;

        /* get a command from foreground process */
        command = recv_control(fd);

        if (DEBUG(verb))
        {
            fprintf(stderr, "AUTH-AAD: BACKGROUND: received command code: %d\n", command);
        }

        switch (command)
        {
            case COMMAND_VERIFY:
                if (recv_string(fd, up.username, sizeof(up.username)) == -1
                {
                    fprintf(stderr, "AUTH-AAD: BACKGROUND: read error on command channel: code=%d, exiting\n",
                            command);
                    goto done;
                }

                if (DEBUG(verb))
                {
#if 0
                    fprintf(stderr, "AUTH-AAD: BACKGROUND: USER/PASS: %s/%s\n",
                            up.username, up.password);
#else
                    fprintf(stderr, "AUTH-AAD: BACKGROUND: USER: %s\n", up.username);
#endif
                }

                if (aad_auth(service, &up)) /* Succeeded */
                {
                    if (send_control(fd, RESPONSE_VERIFY_SUCCEEDED) == -1)
                    {
                        fprintf(stderr, "AUTH-AAD: BACKGROUND: write error on response socket [2]\n");
                        goto done;
                    }
                }
                else /* Failed */
                {
                    if (send_control(fd, RESPONSE_VERIFY_FAILED) == -1)
                    {
                        fprintf(stderr, "AUTH-AAD: BACKGROUND: write error on response socket [3]\n");
                        goto done;
                    }
                }
                break;

            case COMMAND_EXIT:
                goto done;

            case -1:
                fprintf(stderr, "AUTH-AAD: BACKGROUND: read error on command channel\n");
                goto done;

            default:
                fprintf(stderr, "AUTH-AAD: BACKGROUND: unknown command code: code=%d, exiting\n",
                        command);
                goto done;
        }
    }
done:
    if (DEBUG(verb))
    {
        fprintf(stderr, "AUTH-AAD: BACKGROUND: EXIT\n");
    }

    return;
}
