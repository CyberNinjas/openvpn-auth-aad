#
#  OpenVPN (TM) AAD Auth Plugin -- OpenVPN Plugin
#
#  Copyright (C) 2012      Alon Bar-Lev <alon.barlev@gmail.com>
#

MAINTAINERCLEANFILES = \
	$(srcdir)/Makefile.in

AM_CFLAGS = \
	-I$(top_srcdir)/include \
	$(PLUGIN_AUTH_AAD_CFLAGS) \
	$(OPTIONAL_CRYPTO_CFLAGS)

if ENABLE_PLUGIN_AUTH_AAD
plugin_LTLIBRARIES = openvpn-plugin-auth-aad.la
dist_doc_DATA = README.auth-aad
endif

openvpn_plugin_auth_aad_la_SOURCES = \
	utils.c \
	auth-aad.c \
	auth-aad.exports
openvpn_plugin_auth_aad_la_LIBADD = \
	$(PLUGIN_AUTH_AAD_LIBS)
openvpn_plugin_auth_aad_la_LDFLAGS = $(AM_LDFLAGS) \
	-export-symbols "$(srcdir)/auth-aad.exports" \
	-module -shared -avoid-version -no-undefined
