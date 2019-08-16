/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Configuration settings */
#define CONFIGURE_DEFINES "enable_async_push=no enable_comp_stub=no enable_crypto_ofb_cfb=yes enable_debug=yes enable_def_auth=yes enable_dlopen=unknown enable_dlopen_self=unknown enable_dlopen_self_static=unknown enable_fast_install=needless enable_fragment=yes enable_iproute2=no enable_libtool_lock=yes enable_lz4=yes enable_lzo=yes enable_management=yes enable_multihome=yes enable_pam_dlopen=no enable_pedantic=no enable_pf=yes enable_pkcs11=no enable_plugin_auth_pam=yes enable_plugin_down_root=yes enable_plugins=yes enable_port_share=yes enable_selinux=no enable_server=yes enable_shared=yes enable_shared_with_static_runtimes=no enable_small=no enable_static=yes enable_strict=no enable_strict_options=no enable_systemd=no enable_werror=no enable_win32_dll=yes enable_x509_alt_username=no with_aix_soname=aix with_crypto_library=openssl with_gnu_ld=yes with_mem_check=no with_sysroot=no"

/* special build string */
/* #undef CONFIGURE_SPECIAL_BUILD */

/* Use memory debugging function in OpenSSL */
/* #undef CRYPTO_MDEBUG */

/* p11-kit proxy */
/* #undef DEFAULT_PKCS11_MODULE */

/* Use dmalloc memory debugging library */
/* #undef DMALLOC */

/* Dimension to use for empty array declaration */
#define EMPTY_ARRAY_SIZE 0

/* Enable async push */
/* #undef ENABLE_ASYNC_PUSH */

/* Enable client capability only */
/* #undef ENABLE_CLIENT_ONLY */

/* Enable compression stub capability */
/* #undef ENABLE_COMP_STUB */

/* Use mbed TLS library */
/* #undef ENABLE_CRYPTO_MBEDTLS */

/* Use OpenSSL library */
#define ENABLE_CRYPTO_OPENSSL 1

/* Enable debugging support */
#define ENABLE_DEBUG 1

/* Enable deferred authentication */
#define ENABLE_DEF_AUTH 1

/* We have persist tun capability */
#define ENABLE_FEATURE_TUN_PERSIST 1

/* Enable internal fragmentation support */
#define ENABLE_FRAGMENT 1

/* enable iproute2 support */
/* #undef ENABLE_IPROUTE */

/* Enable LZ4 compression library */
#define ENABLE_LZ4 1

/* Enable LZO compression library */
#define ENABLE_LZO 1

/* Enable management server capability */
#define ENABLE_MANAGEMENT 1

/* Enable multi-homed UDP server capability */
#define ENABLE_MULTIHOME 1

/* Enable OFB and CFB cipher modes */
#define ENABLE_OFB_CFB_MODE 1

/* Enable internal packet filter */
#define ENABLE_PF 1

/* Enable PKCS11 */
/* #undef ENABLE_PKCS11 */

/* Enable plug-in support */
#define ENABLE_PLUGIN 1

/* Enable TCP Server port sharing */
#define ENABLE_PORT_SHARE 1

/* SELinux support */
/* #undef ENABLE_SELINUX */

/* enable sitnl support */
#define ENABLE_SITNL 1

/* Enable smaller executable size */
/* #undef ENABLE_SMALL */

/* Enable strict options check between peers */
/* #undef ENABLE_STRICT_OPTIONS_CHECK */

/* Enable systemd integration */
/* #undef ENABLE_SYSTEMD */

/* Enable --x509-username-field feature */
/* #undef ENABLE_X509ALTUSERNAME */

/* Define to 1 if you have the `accept' function. */
#define HAVE_ACCEPT 1

/* Define to 1 if you have the `access' function. */
#define HAVE_ACCESS 1

/* Use crypto library */
#define HAVE_AEAD_CIPHER_MODES 1

/* Compiler supports anonymous unions */
#define HAVE_ANONYMOUS_UNION_SUPPORT /**/

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the `basename' function. */
#define HAVE_BASENAME 1

/* Define to 1 if you have the `bind' function. */
#define HAVE_BIND 1

/* Define to 1 if you have the `chdir' function. */
#define HAVE_CHDIR 1

/* Define to 1 if you have the `chroot' function. */
#define HAVE_CHROOT 1

/* Define to 1 if you have the `chsize' function. */
/* #undef HAVE_CHSIZE */

/* struct cmsghdr needed for extended socket error support */
#define HAVE_CMSGHDR 1

/* extra version available in config-version.h */
/* #undef HAVE_CONFIG_VERSION_H */

/* Define to 1 if you have the `connect' function. */
#define HAVE_CONNECT 1

/* Define to 1 if your compiler supports GNU GCC-style variadic macros */
#define HAVE_CPP_VARARG_MACRO_GCC 1

/* Define to 1 if your compiler supports ISO C99 variadic macros */
#define HAVE_CPP_VARARG_MACRO_ISO 1

/* Define to 1 if you have the `ctime' function. */
#define HAVE_CTIME 1

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the `daemon' function. */
#define HAVE_DAEMON 1

/* Define to 1 if you have the declaration of `SIGHUP', and to 0 if you don't.
   */
#define HAVE_DECL_SIGHUP 1

/* Define to 1 if you have the declaration of `SIGINT', and to 0 if you don't.
   */
#define HAVE_DECL_SIGINT 1

/* Define to 1 if you have the declaration of `SIGTERM', and to 0 if you
   don't. */
#define HAVE_DECL_SIGTERM 1

/* Define to 1 if you have the declaration of `SIGUSR1', and to 0 if you
   don't. */
#define HAVE_DECL_SIGUSR1 1

/* Define to 1 if you have the declaration of `SIGUSR2', and to 0 if you
   don't. */
#define HAVE_DECL_SIGUSR2 1

/* Define to 1 if you have the declaration of `SO_MARK', and to 0 if you
   don't. */
#define HAVE_DECL_SO_MARK 1

/* Define to 1 if you have the declaration of `TUNSETPERSIST', and to 0 if you
   don't. */
#define HAVE_DECL_TUNSETPERSIST 1

/* Define to 1 if you have the <direct.h> header file. */
/* #undef HAVE_DIRECT_H */

/* Define to 1 if you have the `dirname' function. */
#define HAVE_DIRNAME 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <dmalloc.h> header file. */
/* #undef HAVE_DMALLOC_H */

/* Define to 1 if you have the `DSA_bits' function. */
#define HAVE_DSA_BITS 1

/* Define to 1 if you have the `DSA_get0_pqg' function. */
#define HAVE_DSA_GET0_PQG 1

/* Define to 1 if you have the `dup' function. */
#define HAVE_DUP 1

/* Define to 1 if you have the `dup2' function. */
#define HAVE_DUP2 1

/* Define to 1 if you have the `EC_GROUP_order_bits' function. */
#define HAVE_EC_GROUP_ORDER_BITS 1

/* Define to 1 if you have the `ENGINE_cleanup' function. */
/* #undef HAVE_ENGINE_CLEANUP */

/* Define to 1 if you have the `ENGINE_load_builtin_engines' function. */
#define HAVE_ENGINE_LOAD_BUILTIN_ENGINES 1

/* Define to 1 if you have the `ENGINE_register_all_complete' function. */
#define HAVE_ENGINE_REGISTER_ALL_COMPLETE 1

/* Define to 1 if you have the `epoll_create' function. */
#define HAVE_EPOLL_CREATE 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <err.h> header file. */
#define HAVE_ERR_H 1

/* Define to 1 if you have the `EVP_aes_256_gcm' function. */
#define HAVE_EVP_AES_256_GCM 1

/* Define to 1 if you have the `EVP_CIPHER_CTX_set_key_length' function. */
#define HAVE_EVP_CIPHER_CTX_SET_KEY_LENGTH 1

/* Define to 1 if you have the `EVP_MD_CTX_free' function. */
#define HAVE_EVP_MD_CTX_FREE 1

/* Define to 1 if you have the `EVP_MD_CTX_new' function. */
#define HAVE_EVP_MD_CTX_NEW 1

/* Define to 1 if you have the `EVP_MD_CTX_reset' function. */
#define HAVE_EVP_MD_CTX_RESET 1

/* Define to 1 if you have the `EVP_PKEY_get0_DSA' function. */
#define HAVE_EVP_PKEY_GET0_DSA 1

/* Define to 1 if you have the `EVP_PKEY_get0_EC_KEY' function. */
#define HAVE_EVP_PKEY_GET0_EC_KEY 1

/* Define to 1 if you have the `EVP_PKEY_get0_RSA' function. */
#define HAVE_EVP_PKEY_GET0_RSA 1

/* Define to 1 if you have the `EVP_PKEY_id' function. */
#define HAVE_EVP_PKEY_ID 1

/* Define to 1 if you have the `execve' function. */
#define HAVE_EXECVE 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `flock' function. */
#define HAVE_FLOCK 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the `ftruncate' function. */
#define HAVE_FTRUNCATE 1

/* Define to 1 if you have the `getgrnam' function. */
#define HAVE_GETGRNAM 1

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define to 1 if you have the `getpass' function. */
#define HAVE_GETPASS 1

/* Define to 1 if you have the `getpeereid' function. */
/* #undef HAVE_GETPEEREID */

/* Define to 1 if you have the `getpeername' function. */
#define HAVE_GETPEERNAME 1

/* Define to 1 if you have the `getpid' function. */
#define HAVE_GETPID 1

/* Define to 1 if you have the `getpwnam' function. */
#define HAVE_GETPWNAM 1

/* Define to 1 if you have the `getsockname' function. */
#define HAVE_GETSOCKNAME 1

/* Define to 1 if you have the `getsockopt' function. */
#define HAVE_GETSOCKOPT 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the <grp.h> header file. */
#define HAVE_GRP_H 1

/* Define to 1 if you have the `HMAC_CTX_free' function. */
#define HAVE_HMAC_CTX_FREE 1

/* Define to 1 if you have the `HMAC_CTX_new' function. */
#define HAVE_HMAC_CTX_NEW 1

/* Define to 1 if you have the `HMAC_CTX_reset' function. */
#define HAVE_HMAC_CTX_RESET 1

/* Define to 1 if you have the `inet_ntoa' function. */
#define HAVE_INET_NTOA 1

/* Define to 1 if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define to 1 if you have the `inet_pton' function. */
#define HAVE_INET_PTON 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if the system has the type `in_addr_t'. */
#define HAVE_IN_ADDR_T 1

/* struct in_pktinfo needed for IP_PKTINFO support */
#define HAVE_IN_PKTINFO 1

/* Define to 1 if the system has the type `in_port_t'. */
#define HAVE_IN_PORT_T 1

/* struct iovec needed for IPv6 support */
#define HAVE_IOVEC 1

/* Define to 1 if you have the <io.h> header file. */
/* #undef HAVE_IO_H */

/* struct iphdr needed for IPv6 support */
#define HAVE_IPHDR 1

/* struct in_pktinfo.ipi_spec_dst needed for IP_PKTINFO support */
#define HAVE_IPI_SPEC_DST 1

/* Define to 1 if you have the <libgen.h> header file. */
#define HAVE_LIBGEN_H 1

/* Define to 1 if you have the `lz4' library (-llz4). */
#define HAVE_LIBLZ4 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <linux/if_tun.h> header file. */
#define HAVE_LINUX_IF_TUN_H 1

/* Define to 1 if you have the <linux/sockios.h> header file. */
#define HAVE_LINUX_SOCKIOS_H 1

/* Define to 1 if you have the <linux/types.h> header file. */
#define HAVE_LINUX_TYPES_H 1

/* Define to 1 if you have the `listen' function. */
#define HAVE_LISTEN 1

/* Define to 1 if you have the <lz4.h> header file. */
#define HAVE_LZ4_H 1

/* Define to 1 if you have the <lzo1x.h> header file. */
/* #undef HAVE_LZO1X_H */

/* Define to 1 if you have the <lzoutil.h> header file. */
/* #undef HAVE_LZOUTIL_H */

/* Define to 1 if you have the <lzo/lzo1x.h> header file. */
#define HAVE_LZO_LZO1X_H 1

/* Define to 1 if you have the <lzo/lzoutil.h> header file. */
#define HAVE_LZO_LZOUTIL_H 1

/* Define to 1 if you have the `mbedtls_cipher_check_tag' function. */
/* #undef HAVE_MBEDTLS_CIPHER_CHECK_TAG */

/* Define to 1 if you have the `mbedtls_cipher_write_tag' function. */
/* #undef HAVE_MBEDTLS_CIPHER_WRITE_TAG */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* struct msghdr needed for extended socket error support */
#define HAVE_MSGHDR 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/in_systm.h> header file. */
#define HAVE_NETINET_IN_SYSTM_H 1

/* Define to 1 if you have the <netinet/ip.h> header file. */
#define HAVE_NETINET_IP_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* Define to 1 if you have the <net/if.h> header file. */
#define HAVE_NET_IF_H 1

/* Define to 1 if you have the <net/if_tun.h> header file. */
/* #undef HAVE_NET_IF_TUN_H */

/* Define to 1 if you have the <net/if_utun.h> header file. */
/* #undef HAVE_NET_IF_UTUN_H */

/* Define to 1 if you have the <net/tun/if_tun.h> header file. */
/* #undef HAVE_NET_TUN_IF_TUN_H */

/* Define to 1 if you have the `nice' function. */
#define HAVE_NICE 1

/* Define to 1 if you have the `openlog' function. */
#define HAVE_OPENLOG 1

/* OpenSSL engine support available */
#define HAVE_OPENSSL_ENGINE 1

/* Define to 1 if you have the `OpenSSL_version' function. */
#define HAVE_OPENSSL_VERSION 1

/* Define to 1 if you have the `poll' function. */
#define HAVE_POLL 1

/* Define to 1 if you have the <poll.h> header file. */
#define HAVE_POLL_H 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the `readv' function. */
#define HAVE_READV 1

/* Define to 1 if you have the `recv' function. */
#define HAVE_RECV 1

/* Define to 1 if you have the `recvfrom' function. */
#define HAVE_RECVFROM 1

/* Define to 1 if you have the `recvmsg' function. */
#define HAVE_RECVMSG 1

/* Define to 1 if you have the <resolv.h> header file. */
#define HAVE_RESOLV_H 1

/* Define to 1 if you have the `RSA_bits' function. */
#define HAVE_RSA_BITS 1

/* Define to 1 if you have the `RSA_get0_key' function. */
#define HAVE_RSA_GET0_KEY 1

/* Define to 1 if you have the `RSA_meth_free' function. */
#define HAVE_RSA_METH_FREE 1

/* Define to 1 if you have the `RSA_meth_get0_app_data' function. */
#define HAVE_RSA_METH_GET0_APP_DATA 1

/* Define to 1 if you have the `RSA_meth_new' function. */
#define HAVE_RSA_METH_NEW 1

/* Define to 1 if you have the `RSA_meth_set0_app_data' function. */
#define HAVE_RSA_METH_SET0_APP_DATA 1

/* Define to 1 if you have the `RSA_meth_set_finish' function. */
#define HAVE_RSA_METH_SET_FINISH 1

/* Define to 1 if you have the `RSA_meth_set_init' function. */
#define HAVE_RSA_METH_SET_INIT 1

/* Define to 1 if you have the `RSA_meth_set_priv_dec' function. */
#define HAVE_RSA_METH_SET_PRIV_DEC 1

/* Define to 1 if you have the `RSA_meth_set_priv_enc' function. */
#define HAVE_RSA_METH_SET_PRIV_ENC 1

/* Define to 1 if you have the `RSA_meth_set_pub_dec' function. */
#define HAVE_RSA_METH_SET_PUB_DEC 1

/* Define to 1 if you have the `RSA_meth_set_pub_enc' function. */
#define HAVE_RSA_METH_SET_PUB_ENC 1

/* Define to 1 if you have the `RSA_meth_set_sign' function. */
#define HAVE_RSA_METH_SET_SIGN 1

/* Define to 1 if you have the `RSA_set0_key' function. */
#define HAVE_RSA_SET0_KEY 1

/* Define to 1 if you have the `RSA_set_flags' function. */
#define HAVE_RSA_SET_FLAGS 1

/* sa_family_t, needed to hold AF_* info */
#define HAVE_SA_FAMILY_T 1

/* Define to 1 if you have the `sd_booted' function. */
/* #undef HAVE_SD_BOOTED */

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `send' function. */
#define HAVE_SEND 1

/* Define to 1 if you have the `sendmsg' function. */
#define HAVE_SENDMSG 1

/* Define to 1 if you have the `sendto' function. */
#define HAVE_SENDTO 1

/* Define to 1 if you have the `setgid' function. */
#define HAVE_SETGID 1

/* Define to 1 if you have the `setgroups' function. */
#define HAVE_SETGROUPS 1

/* Define to 1 if you have the `setsid' function. */
#define HAVE_SETSID 1

/* Define to 1 if you have the `setsockopt' function. */
#define HAVE_SETSOCKOPT 1

/* Define to 1 if you have the `setuid' function. */
#define HAVE_SETUID 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* struct sock_extended_err needed for extended socket error support */
/* #undef HAVE_SOCK_EXTENDED_ERR */

/* Define to 1 if you have the `SSL_CTX_get_default_passwd_cb' function. */
#define HAVE_SSL_CTX_GET_DEFAULT_PASSWD_CB 1

/* Define to 1 if you have the `SSL_CTX_get_default_passwd_cb_userdata'
   function. */
#define HAVE_SSL_CTX_GET_DEFAULT_PASSWD_CB_USERDATA 1

/* Define to 1 if you have the `SSL_CTX_new' function. */
#define HAVE_SSL_CTX_NEW 1

/* Define to 1 if you have the `SSL_CTX_set_security_level' function. */
#define HAVE_SSL_CTX_SET_SECURITY_LEVEL 1

/* Define to 1 if you have the `stat' function. */
#define HAVE_STAT 1

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <stropts.h> header file. */
#define HAVE_STROPTS_H 1

/* Define to 1 if you have the `syslog' function. */
#define HAVE_SYSLOG 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the `system' function. */
#define HAVE_SYSTEM 1

/* Define to 1 if you have the <systemd/sd-daemon.h> header file. */
/* #undef HAVE_SYSTEMD_SD_DAEMON_H */

/* Define to 1 if you have the <sys/epoll.h> header file. */
#define HAVE_SYS_EPOLL_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/inotify.h> header file. */
/* #undef HAVE_SYS_INOTIFY_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/kern_control.h> header file. */
/* #undef HAVE_SYS_KERN_CONTROL_H */

/* Define to 1 if you have the <sys/mman.h> header file. */
#define HAVE_SYS_MMAN_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/sockio.h> header file. */
/* #undef HAVE_SYS_SOCKIO_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <tap-windows.h> header file. */
/* #undef HAVE_TAP_WINDOWS_H */

/* Define to 1 if you have the `time' function. */
#define HAVE_TIME 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the `umask' function. */
#define HAVE_UMASK 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unlink' function. */
#define HAVE_UNLINK 1

/* Define to 1 if you have the <valgrind/memcheck.h> header file. */
/* #undef HAVE_VALGRIND_MEMCHECK_H */

/* Define to 1 if you have the <versionhelpers.h> header file. */
/* #undef HAVE_VERSIONHELPERS_H */

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to 1 if you have the <winsock2.h> header file. */
/* #undef HAVE_WINSOCK2_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define to 1 if you have the `writev' function. */
#define HAVE_WRITEV 1

/* Define to 1 if you have the <ws2tcpip.h> header file. */
/* #undef HAVE_WS2TCPIP_H */

/* Define to 1 if you have the `X509_get0_pubkey' function. */
#define HAVE_X509_GET0_PUBKEY 1

/* Define to 1 if you have the `X509_OBJECT_free' function. */
#define HAVE_X509_OBJECT_FREE 1

/* Define to 1 if you have the `X509_OBJECT_get_type' function. */
#define HAVE_X509_OBJECT_GET_TYPE 1

/* Define to 1 if you have the `X509_STORE_get0_objects' function. */
#define HAVE_X509_STORE_GET0_OBJECTS 1

/* Path to ifconfig tool */
#define IFCONFIG_PATH ""

/* Path to iproute tool */
#define IPROUTE_PATH "/sbin/ip"

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* use copy of LZ4 source in compat/ */
/* #undef NEED_COMPAT_LZ4 */

/* OpenVPN major version - integer */
#define OPENVPN_VERSION_MAJOR 2

/* OpenVPN minor version - integer */
#define OPENVPN_VERSION_MINOR 5

/* OpenVPN patch level - may be a string or integer */
#define OPENVPN_VERSION_PATCH "_git"

/* Version in windows resource format */
#define OPENVPN_VERSION_RESOURCE 2,5,0,0

/* Name of package */
#define PACKAGE "openvpn"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "openvpn-users@lists.sourceforge.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "OpenVPN"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "OpenVPN 2.5_git"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "openvpn"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.5_git"

/* Path separator */
#define PATH_SEPARATOR '/'

/* Path separator */
#define PATH_SEPARATOR_STR "/"

/* Enable pedantic mode */
/* #undef PEDANTIC */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Path to route tool */
#define ROUTE_PATH ""

/* SIGHUP replacement */
/* #undef SIGHUP */

/* SIGINT replacement */
/* #undef SIGINT */

/* SIGTERM replacement */
/* #undef SIGTERM */

/* SIGUSR1 replacement */
/* #undef SIGUSR1 */

/* SIGUSR2 replacement */
/* #undef SIGUSR2 */

/* The size of `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT 4

/* The size of `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Path to systemd-ask-password tool */
#define SYSTEMD_ASK_PASSWORD_PATH ""

/* systemd is newer than v216 */
/* #undef SYSTEMD_NEWER_THAN_216 */

/* The tap-windows id */
#define TAP_WIN_COMPONENT_ID "tap0901"

/* The tap-windows version number is required for OpenVPN */
#define TAP_WIN_MIN_MAJOR 9

/* The tap-windows version number is required for OpenVPN */
#define TAP_WIN_MIN_MINOR 9

/* Are we running AIX? */
/* #undef TARGET_AIX */

/* A string representing our host */
#define TARGET_ALIAS "x86_64-pc-linux-gnu"

/* Are we running on Mac OS X? */
/* #undef TARGET_DARWIN */

/* Are we running on DragonFlyBSD? */
/* #undef TARGET_DRAGONFLY */

/* Are we running on FreeBSD? */
/* #undef TARGET_FREEBSD */

/* Are we running on Linux? */
#define TARGET_LINUX 1

/* Are we running NetBSD? */
/* #undef TARGET_NETBSD */

/* Are we running on OpenBSD? */
/* #undef TARGET_OPENBSD */

/* Target prefix */
#define TARGET_PREFIX "L"

/* Are we running on Solaris? */
/* #undef TARGET_SOLARIS */

/* Are we running WIN32? */
/* #undef TARGET_WIN32 */

/* dlopen libpam */
/* #undef USE_PAM_DLOPEN */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Use valgrind memory debugging library */
/* #undef USE_VALGRIND */

/* Version number of package */
#define VERSION "2.5_git"

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Workaround missing in_addr_t */
/* #undef in_addr_t */

/* Workaround missing in_port_t */
/* #undef in_port_t */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int16_t */

/* Define to the type of a signed integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int32_t */

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to the type of a signed integer type of width exactly 8 bits if such
   a type exists and the standard includes do not define it. */
/* #undef int8_t */

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* type to use in place of socklen_t if not defined */
/* #undef socklen_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */

/* Define to empty if the keyword `volatile' does not work. Warning: valid
   code using `volatile' can become incorrect without. Disable with care. */
/* #undef volatile */
