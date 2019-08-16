OPENVPN_PLUGIN_DIR="/usr/lib/openvpn/plugins"

all: dlopen

dlopentest:
	${CC} ${CLFAGS} ${LDFLAGS} -fPIE -fstack-protector -Wall -o $@ $@.c -ldl

dlopen: dlopentest
	./dlopentest "${OPENVPN_PLUGIN_DIR}/openvpn-auth-aad.so"
