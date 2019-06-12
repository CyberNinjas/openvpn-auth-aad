CC = gcc

INDENT = indent

CFLAGS = -O2 -Wall -g

SRC_DIR = .

all: auth-aad

auth-aad:
	${CC} ${CFLAGS} -fPIC $@.c \
			-shared ${LDFLAGS} \
			-I${SRC_DIR}/openvpn/include \
			-Wl,-soname,$@.so -o $@.so -lc

debug:
	@LDFLAGS="${LDFLAGS} -ggdb" make

reformat:
	@VERSION_CONTROL=none $(INDENT) auth-aad.c

clean:
	@rm -rf auth-aad.so

clean-all: clean
	@make -C openvpn maintainer-clean
	@cd openvpn && git reset --h

