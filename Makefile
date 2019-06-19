CC = gcc

INDENT = indent

INSTALL = /usr/bin/install
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

CFLAGS = -O2 -Wall -g -D_AAD_EXPORT
LDFLAGS = -Wl,--strip-debug -Wl,--build-id=none
LDFLAGS += -fPIC -fno-stack-protector -Wl,--export-dynamic
LIBS = -lc -lcurl -ljansson -ljwt -lpam -lsds -luuid

SRC_DIR = .

OPENVPN_SRC_DIR = ${SRC_DIR}/openvpn
PAM_AAD_SRC_DIR = ${SRC_DIR}/pam_aad

SRC = ${SRC_DIR}/auth_aad.c
SRC += ${PAM_AAD_SRC_DIR}/pam_aad.c
SRC += ${OPENVPN_SRC_DIR}/src/plugins/auth-pam/utils.c

INCLUDES = -I${OPENVPN_SRC_DIR}/include
INCLUDES += -I${OPENVPN_SRC_DIR}/src/plugins/auth-pam

SONAME = openvpn-auth-aad.so

PREFIX = /usr/local
LIB_DIR = ${PREFIX}/lib
PLUGIN_DIR = ${LIBDIR}/openvpn/plugins

all: ${SONAME}

${SONAME}:
	${CC} ${CFLAGS} ${LDFLAGS} -shared \
		${SRC} ${INCLUDES} ${LIBS} \
		-Wl,-soname,$@ -o $@

install: ${SONAME}
	${INSTALL_DATA} ${SONAME} ${PLUGIN_DIR}

debug:
	@LDFLAGS="${LDFLAGS} -ggdb" make

reformat:
	@VERSION_CONTROL=none $(INDENT) *.c

clean:
	@rm -rf ${SONAME}

clean-all: clean
	@make -C openvpn maintainer-clean
	@cd openvpn && git reset --h && cd ..
	@make -C pam_aad maintainer-clean
	@cd pam_aad && git reset --h && cd ..

