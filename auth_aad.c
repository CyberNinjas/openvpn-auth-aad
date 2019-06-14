/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single TCP/UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2002-2018 OpenVPN Inc <sales@openvpn.net>
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "openvpn-plugin.h"

/*
 * Constants
 */
#define OPENVPN_PLUGIN_VERSION_MIN 3

extern int azure_authenticator(const char *user);

/*
 * Our context, where we keep our state.
 */

struct plugin_context {
	char *username;
};

void handle_sigchld(int sig)
{
    /*
     * nonblocking wait (WNOHANG) for any child (-1) to come back
     */
    while(waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
}

/*
 * Require OpenVPN Plugin API v3
 */
OPENVPN_EXPORT int
openvpn_plugin_min_version_required_v1()
{
    return OPENVPN_PLUGIN_VERSION_MIN;
}

OPENVPN_EXPORT int
openvpn_plugin_open_v3(const int struct_version,
                       struct openvpn_plugin_args_open_in const *arguments,
                       struct openvpn_plugin_args_open_return *retptr)
{
    struct plugin_context *context;

    if (struct_version < OPENVPN_PLUGINv3_STRUCTVER) {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    /*
     * Allocate our context
     */
    context = (struct plugin_context *) calloc(1, sizeof(struct plugin_context));

    if (arguments->argv[1]) {
        context->username = strdup(arguments->argv[1]);
        if (context->username == NULL) {
            perror("Unable to allocate memory\n");
            exit(EXIT_FAILURE);
        }
    }

    /*
     * Which callbacks to intercept.
     */
    retptr->type_mask =
        OPENVPN_PLUGIN_MASK(OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY);

    retptr->handle = (openvpn_plugin_handle_t) context;

    return OPENVPN_PLUGIN_FUNC_SUCCESS;
}

static int
deferred_auth_handler(struct plugin_context *context, const char *argv[], const char *envp[])
{
    pid_t pid;
    struct sigaction sa;
    char *username = context->username;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sa.sa_handler = &handle_sigchld;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    pid = fork();

    if (pid < 0) {
        /*
         * Fork failed, bail out.
         */
        return OPENVPN_PLUGIN_FUNC_ERROR;
    } else if (pid > 0) {
        /*
         * We're the parent.  Tell openvpn we're deferring.
         */
        return OPENVPN_PLUGIN_FUNC_DEFERRED;
    } else {
        azure_authenticator(username);

	exit(127);
    }

}

OPENVPN_EXPORT int
openvpn_plugin_func_v3(const int struct_version,
                       struct openvpn_plugin_args_func_in const *arguments,
                       struct openvpn_plugin_args_func_return *retptr)
{
    struct plugin_context *context = (struct plugin_context *) arguments->handle;

    if (struct_version < OPENVPN_PLUGINv3_STRUCTVER) {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    switch (arguments->type)
    {
        case OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY:
            return deferred_auth_handler(context, arguments->argv, arguments->envp);

        default:
            return OPENVPN_PLUGIN_FUNC_ERROR;
    }
}

OPENVPN_EXPORT void
openvpn_plugin_close_v1(openvpn_plugin_handle_t handle)
{
    struct plugin_context *context = (struct plugin_context *) handle;
    free(context->username);
    free(context);
}

