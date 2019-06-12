/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single TCP/UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2002-2018 OpenVPN Inc <sales@openvpn.net>
 *  Copyright (C) 2019 CyberNinjas <info@cyberninjas.com>
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
 * This file implements a simple OpenVPN plugin module which
 * will test deferred authentication.
 *
 * Sample usage:
 *
 * setenv aad_auth 20
 * plugin plugin/auth-aad.so
 *
 * This will enable deferred authentication to occur 20
 * seconds after the normal TLS authentication process.
 *
 * See the README file for build instructions.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openvpn-plugin.h"

/* bool definitions */
#define bool int
#define true 1
#define false 0

/*
 * Our context, where we keep our state.
 */

struct plugin_context {
    int aad_auth;
};

struct plugin_per_client_context {
    int n_calls;
};

/*
 * Given an environmental variable name, search
 * the envp array for its value, returning it
 * if found or NULL otherwise.
 */
static const char *get_env(const char *name, const char *envp[])
{
    if (envp) {
        int i;
        const int namelen = strlen(name);
        for (i = 0; envp[i]; ++i) {
            if (!strncmp(envp[i], name, namelen)) {
                const char *cp = envp[i] + namelen;
                if (*cp == '=') {
                    return cp + 1;
                }
            }
        }
    }
    return NULL;
}

/* used for safe printf of possible NULL strings */
static const char *np(const char *str)
{
    if (str) {
        return str;
    } else {
        return "[NULL]";
    }
}

static int atoi_null0(const char *str)
{
    if (str) {
        return atoi(str);
    } else {
        return 0;
    }
}

OPENVPN_EXPORT openvpn_plugin_handle_t
openvpn_plugin_open_v1(unsigned int *type_mask, const char *argv[],
                       const char *envp[])
{
    struct plugin_context *context;

    printf("FUNC: openvpn_plugin_open_v1\n");

    /*
     * Allocate our context
     */
    context =
        (struct plugin_context *) calloc(1, sizeof(struct plugin_context));

    context->aad_auth = atoi_null0(get_env("aad_auth", envp));
    printf("AAD_AUTH %d\n", context->aad_auth);

    /*
     * Which callbacks to intercept.
     */
    *type_mask = OPENVPN_PLUGIN_MASK(OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY);

    return (openvpn_plugin_handle_t) context;
}

static int
auth_user_verify(struct plugin_context *context,
                 struct plugin_per_client_context *pcc, const char *argv[],
                 const char *envp[])
{
    if (context->aad_auth) {
        /* get username from envp string array */
        const char *username = get_env("username", envp);

        /* get auth_control_file filename from envp string array */
        const char *auth_control_file = get_env("auth_control_file", envp);

        printf("DEFER u='%s' acf='%s'\n",
               np(username), np(auth_control_file));

        /* Authenticate asynchronously in n seconds */
        if (auth_control_file) {
            char buf[256];
            int auth = 2, ret;
            sscanf(username, "%d", &auth);
            snprintf(buf, sizeof(buf),
                     "( sleep %d ; echo AUTH %s %d ; echo %d >%s ) &",
                     context->aad_auth, auth_control_file, auth,
                     pcc->n_calls < auth, auth_control_file);
            printf("%s\n", buf);
            ret = system(buf);
            (void) ret;
            pcc->n_calls++;
            return OPENVPN_PLUGIN_FUNC_DEFERRED;
        } else {
            return OPENVPN_PLUGIN_FUNC_ERROR;
        }
    } else {
        return OPENVPN_PLUGIN_FUNC_SUCCESS;
    }
}

OPENVPN_EXPORT int
openvpn_plugin_func_v2(openvpn_plugin_handle_t handle,
                       const int type,
                       const char *argv[],
                       const char *envp[],
                       void *per_client_context,
                       struct openvpn_plugin_string_list **return_list)
{
    struct plugin_context *context = (struct plugin_context *) handle;
    struct plugin_per_client_context *pcc =
        (struct plugin_per_client_context *) per_client_context;
    printf("OPENVPN_PLUGIN_AUTH_USER_PASS_VERIFY\n");
    return auth_user_verify(context, pcc, argv, envp);

}

OPENVPN_EXPORT void
*openvpn_plugin_client_constructor_v1(openvpn_plugin_handle_t handle)
{
    printf("FUNC: openvpn_plugin_client_constructor_v1\n");
    return calloc(1, sizeof(struct plugin_per_client_context));
}

OPENVPN_EXPORT void
openvpn_plugin_client_destructor_v1(openvpn_plugin_handle_t handle,
                                    void *per_client_context)
{
    printf("FUNC: openvpn_plugin_client_destructor_v1\n");
    free(per_client_context);
}

OPENVPN_EXPORT void openvpn_plugin_close_v1(openvpn_plugin_handle_t handle)
{
    struct plugin_context *context = (struct plugin_context *) handle;
    printf("FUNC: openvpn_plugin_close_v1\n");
    free(context);
}
