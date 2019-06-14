CC = gcc

INDENT = indent

CFLAGS = -O2 -Wall -g -D_USE_EXTERNAL
LDFLAGS = -Wl,--strip-debug -Wl,--build-id=none
LDFLAGS += -fPIC -fno-stack-protector -Wl,--export-dynamic
LIBS = -lc -lcurl -ljansson -ljwt -lpam -lsds -luuid

SRC_DIR = .
SRC = ${SRC_DIR}/auth_aad.c
SRC += ${SRC_DIR}/pam_aad/pam_aad.c
INCLUDES = -I${SRC_DIR}/openvpn/include


all: openvpn-auth-aad

openvpn-auth-aad:
	${CC} ${CFLAGS} ${LDFLAGS} -shared \
		${SRC} ${INCLUDES} ${LIBS} \
		-Wl,-soname,$@.so -o $@.so

debug:
	@LDFLAGS="${LDFLAGS} -ggdb" make

reformat:
	@VERSION_CONTROL=none $(INDENT) auth-aad.c

clean:
	@rm -rf auth-aad.so

clean-all: clean
	@make -C openvpn maintainer-clean
	@cd openvpn && git reset --h

