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
#include "utils.h"              /* openvpn/src/plugins/auth-pam */

#define OPENVPN_PLUGIN_VERSION_MIN 3    /* Require OpenVPN Plugin API v3 */
#define OPENVPN_PLUGIN_STRUCTVER 4

extern int azure_authenticator(const char *user);       /* pam_aad.c */

struct plugin_context {
    int aad_auth;
};

void handle_sigchld(int sig)
{
    while (waitpid((pid_t) (-1), 0, WNOHANG) > 0) {
        /* nonblocking wait (WNOHANG) for any child (-1) to come back */
    }
}

OPENVPN_EXPORT int openvpn_plugin_min_version_required_v1()
{
    return OPENVPN_PLUGIN_VERSION_MIN;
}

OPENVPN_EXPORT int
openvpn_plugin_open_v3(const int structver,
                       struct openvpn_plugin_args_open_in const *args,
                       struct openvpn_plugin_args_open_return *ret)
{
    struct plugin_context *context;

    (void) args;                /* unused parameter */

    /* OPENVPN_PLUGINv3_STRUCTVER defined in openvpn-plugin.h */
    if (structver < OPENVPN_PLUGIN_STRUCTVER) {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    /* Allocate the context */
    context =
        (struct plugin_context *) calloc(1, sizeof(struct plugin_context));

    context->aad_auth = 1;      /* dummy value */

    /* Intercept the --auth-user-pass-verify callback. */
    ret->type_mask =
        OPENVPN_PLUGIN_MASK(OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY);

    ret->handle = (openvpn_plugin_handle_t) context;

    return OPENVPN_PLUGIN_FUNC_SUCCESS;
}

static int azure_auth_handler(struct plugin_context *context, const char *argv[], const char *envp[])
{
    pid_t pid;
    struct sigaction sa;        /* signal.h */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sa.sa_handler = &handle_sigchld;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }

    pid = fork();

    if (pid < 0) {
        /* Fork failed, bail out. */
        return OPENVPN_PLUGIN_FUNC_ERROR;
    } else if (pid > 0) {
        /* We're the parent. Tell openvpn we're deferring. */
        return OPENVPN_PLUGIN_FUNC_DEFERRED;
    } else {
        const char *username = get_env("username", envp);
        azure_authenticator(username);
        exit(127);
    }

}

OPENVPN_EXPORT int
openvpn_plugin_func_v3(const int structver,
                       struct openvpn_plugin_args_func_in const *args,
                       struct openvpn_plugin_args_func_return *ret)
{
    struct plugin_context *context = (struct plugin_context *) args->handle;

    /* Check API compatibility -- struct version or higher needed */
    if (structver < OPENVPN_PLUGIN_STRUCTVER)
        return OPENVPN_PLUGIN_FUNC_ERROR;

    switch (args->type) {
    case OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY:
        return azure_auth_handler(context, args->argv, args->envp);
    default:
        return OPENVPN_PLUGIN_FUNC_ERROR;
    }
}

OPENVPN_EXPORT void openvpn_plugin_close_v1(openvpn_plugin_handle_t handle)
{
    struct plugin_context *context = (struct plugin_context *) handle;
    free(context);
}
