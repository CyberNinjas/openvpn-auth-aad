CC = gcc
CFLAGS = -O2 -Wall -g

SRC_DIR = .

auth-aad:
	${CC} ${CFLAGS} -fPIC -c $@.c \
			-shared ${LDFLAGS} \
			-I${SRC_DIR}/openvpn/include \
			-Wl,-soname,$@.so -o $@.so -lc

