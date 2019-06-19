# openvpn-auth-aad

## Compiling

1) Fetch source code:

```terminal
git clone https://github.com/CyberNinjas/openvpn-auth-aad

cd openvpn-auth-aad
```

2) Configure:

```terminal
./bootstrap.sh
```

3) Compile:

```terminal
make
```

4) Install:

```terminal
sudo make install
```

## Configuration

### Server

`/etc/openvpn/server.conf`

```txt
plugin /usr/lib/openvpn/openvpn-auth-aad.so
client-cert-not-required
username-as-common-name
```

Source: [contrib/server.conf](../contrib/server.conf)

Note: A valid [pam_aad setup][pam_aad-index-config] is also required.

### Client

`/etc/openvpn/client.conf`, (or `C:\Program Files\OpenVPN\config\client.ovpn` on Windows)

```txt
# OpenVPN Client Configuration
client
dev tun
proto udp
remote 192.168.1.128 1194
nobind
;user nobody
;group nobody
persist-key
persist-tun
;mute-replay-warnings
ca ca.crt # from server
verb 5
auth-user-pass
```

Source: [contrib/client.conf](../contrib/client.conf)

## Resources

- [Debian Wiki - OpenVPN](https://wiki.debian.org/OpenVPN)
- [OpenVPN - 2x HOW TO](https://openvpn.net/community-resources/how-to)
- [Ubuntu Documentation - OpenVPN](https://help.ubuntu.com/lts/serverguide/openvpn.html)

[pam_aad-index-config]: https://github.com/CyberNinjas/pam_aad/blob/master/doc/index.md#configuration
