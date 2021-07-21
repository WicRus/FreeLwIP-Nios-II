#
# lwip_sw.tcl
#
# A description of the LwIP TCP/IP stack,
# version 1.4.1, for use with the Nios II BSP tools
#

# Create a new software package named "LwIP"
create_sw_package lwip

# The version of this software
# Note: Version assignment is based on version of Nios II EDS that
#       this was distributed with. The LwIP Stack version is v2.1.2
set_sw_property version 12.0

# (Don't) initialize the driver in alt_sys_init()
set_sw_property auto_initialize false

# Location in generated BSP that above sources will be copied into
set_sw_property bsp_subdirectory lwip

# Include paths
add_sw_property include_directory inc

#
# Source file listings...
#

# C/C++ source files
add_sw_property c_source FreeRTOS/src/api/api_lib.c
add_sw_property c_source FreeRTOS/src/api/api_msg.c
add_sw_property c_source FreeRTOS/src/api/err.c
add_sw_property c_source FreeRTOS/src/api/if_api.c
add_sw_property c_source FreeRTOS/src/api/netbuf.c
add_sw_property c_source FreeRTOS/src/api/netdb.c
add_sw_property c_source FreeRTOS/src/api/netifapi.c
add_sw_property c_source FreeRTOS/src/api/sockets.c
add_sw_property c_source FreeRTOS/src/api/tcpip.c
add_sw_property c_source FreeRTOS/src/arch/alt_lwip_close.c
add_sw_property c_source FreeRTOS/src/arch/alt_lwip_fcntl.c
add_sw_property c_source FreeRTOS/src/arch/alt_lwip_read.c
add_sw_property c_source FreeRTOS/src/arch/alt_lwip_write.c
add_sw_property c_source FreeRTOS/src/core/ipv4/acd.c
add_sw_property c_source FreeRTOS/src/core/ipv4/autoip.c
add_sw_property c_source FreeRTOS/src/core/ipv4/dhcp.c
add_sw_property c_source FreeRTOS/src/core/ipv4/etharp.c
add_sw_property c_source FreeRTOS/src/core/ipv4/icmp.c
add_sw_property c_source FreeRTOS/src/core/ipv4/igmp.c
add_sw_property c_source FreeRTOS/src/core/ipv4/ip4.c
add_sw_property c_source FreeRTOS/src/core/ipv4/ip4_addr.c
add_sw_property c_source FreeRTOS/src/core/ipv4/ip4_frag.c
add_sw_property c_source FreeRTOS/src/core/ipv6/dhcp6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/ethip6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/icmp6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/inet6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/ip6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/ip6_addr.c
add_sw_property c_source FreeRTOS/src/core/ipv6/ip6_frag.c
add_sw_property c_source FreeRTOS/src/core/ipv6/mld6.c
add_sw_property c_source FreeRTOS/src/core/ipv6/nd6.c

add_sw_property c_source FreeRTOS/src/core/altcp.c
add_sw_property c_source FreeRTOS/src/core/altcp_alloc.c
add_sw_property c_source FreeRTOS/src/core/altcp_tcp.c
add_sw_property c_source FreeRTOS/src/core/def.c
add_sw_property c_source FreeRTOS/src/core/dns.c
add_sw_property c_source FreeRTOS/src/core/inet_chksum.c
add_sw_property c_source FreeRTOS/src/core/init.c
add_sw_property c_source FreeRTOS/src/core/ip.c
add_sw_property c_source FreeRTOS/src/core/mem.c
add_sw_property c_source FreeRTOS/src/core/memp.c
add_sw_property c_source FreeRTOS/src/core/netif.c
add_sw_property c_source FreeRTOS/src/core/pbuf.c
add_sw_property c_source FreeRTOS/src/core/raw.c
add_sw_property c_source FreeRTOS/src/core/stats.c
add_sw_property c_source FreeRTOS/src/core/sys.c
add_sw_property c_source FreeRTOS/src/core/tcp.c
add_sw_property c_source FreeRTOS/src/core/tcp_in.c
add_sw_property c_source FreeRTOS/src/core/tcp_out.c
add_sw_property c_source FreeRTOS/src/core/timeouts.c
add_sw_property c_source FreeRTOS/src/core/udp.c


add_sw_property c_source FreeRTOS/src/netif/bridgeif.c
add_sw_property c_source FreeRTOS/src/netif/bridgeif_fdb.c
add_sw_property c_source FreeRTOS/src/netif/ethernet.c
add_sw_property c_source FreeRTOS/src/netif/lowpan6.c
add_sw_property c_source FreeRTOS/src/netif/lowpan6_ble.c
add_sw_property c_source FreeRTOS/src/netif/lowpan6_common.c
add_sw_property c_source FreeRTOS/src/netif/slipif.c
add_sw_property c_source FreeRTOS/src/netif/zepif.c

add_sw_property c_source FreeRTOS/src/netif/ppp/auth.c
add_sw_property c_source FreeRTOS/src/netif/ppp/ccp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/chap_ms.c
add_sw_property c_source FreeRTOS/src/netif/ppp/chap-md5.c
add_sw_property c_source FreeRTOS/src/netif/ppp/chap-new.c
add_sw_property c_source FreeRTOS/src/netif/ppp/demand.c
add_sw_property c_source FreeRTOS/src/netif/ppp/eap.c
add_sw_property c_source FreeRTOS/src/netif/ppp/ecp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/eui64.c
add_sw_property c_source FreeRTOS/src/netif/ppp/fsm.c
add_sw_property c_source FreeRTOS/src/netif/ppp/ipcp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/ipv6cp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/lcp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/magic.c
add_sw_property c_source FreeRTOS/src/netif/ppp/mppe.c
add_sw_property c_source FreeRTOS/src/netif/ppp/ppp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/pppapi.c
add_sw_property c_source FreeRTOS/src/netif/ppp/pppcrypt.c
add_sw_property c_source FreeRTOS/src/netif/ppp/pppoe.c
add_sw_property c_source FreeRTOS/src/netif/ppp/pppol2tp.c
add_sw_property c_source FreeRTOS/src/netif/ppp/pppos.c
add_sw_property c_source FreeRTOS/src/netif/ppp/upap.c
add_sw_property c_source FreeRTOS/src/netif/ppp/utils.c
add_sw_property c_source FreeRTOS/src/netif/ppp/vj.c

add_sw_property c_source FreeRTOS/src/netif/ppp/polarssl/arc4.c
add_sw_property c_source FreeRTOS/src/netif/ppp/polarssl/des.c
add_sw_property c_source FreeRTOS/src/netif/ppp/polarssl/md4.c
add_sw_property c_source FreeRTOS/src/netif/ppp/polarssl/md5.c
add_sw_property c_source FreeRTOS/src/netif/ppp/polarssl/sha1.c

# Include files

add_sw_property include_source FreeRTOS/inc/arch/cc.h
add_sw_property include_source FreeRTOS/inc/arch/perf.h
add_sw_property include_source FreeRTOS/inc/arch/sys_arch.h

add_sw_property include_source FreeRTOS/inc/lwip/acd.h
add_sw_property include_source FreeRTOS/inc/lwip/altcp.h
add_sw_property include_source FreeRTOS/inc/lwip/altcp_tcp.h
add_sw_property include_source FreeRTOS/inc/lwip/altcp_tls.h
add_sw_property include_source FreeRTOS/inc/lwip/api.h
add_sw_property include_source FreeRTOS/inc/lwip/arch.h
add_sw_property include_source FreeRTOS/inc/lwip/autoip.h
add_sw_property include_source FreeRTOS/inc/lwip/debug.h
add_sw_property include_source FreeRTOS/inc/lwip/def.h
add_sw_property include_source FreeRTOS/inc/lwip/dhcp.h
add_sw_property include_source FreeRTOS/inc/lwip/dhcp6.h
add_sw_property include_source FreeRTOS/inc/lwip/dns.h
add_sw_property include_source FreeRTOS/inc/lwip/err.h
add_sw_property include_source FreeRTOS/inc/lwip/errno.h
add_sw_property include_source FreeRTOS/inc/lwip/etharp.h
add_sw_property include_source FreeRTOS/inc/lwip/ethip6.h
add_sw_property include_source FreeRTOS/inc/lwip/icmp.h
add_sw_property include_source FreeRTOS/inc/lwip/icmp6.h
add_sw_property include_source FreeRTOS/inc/lwip/if_api.h
add_sw_property include_source FreeRTOS/inc/lwip/igmp.h
add_sw_property include_source FreeRTOS/inc/lwip/inet.h
add_sw_property include_source FreeRTOS/inc/lwip/inet_chksum.h
add_sw_property include_source FreeRTOS/inc/lwip/init.h
add_sw_property include_source FreeRTOS/inc/lwip/ip.h
add_sw_property include_source FreeRTOS/inc/lwip/ip_addr.h
add_sw_property include_source FreeRTOS/inc/lwip/ip4.h
add_sw_property include_source FreeRTOS/inc/lwip/ip4_addr.h
add_sw_property include_source FreeRTOS/inc/lwip/ip4_frag.h
add_sw_property include_source FreeRTOS/inc/lwip/ip6.h
add_sw_property include_source FreeRTOS/inc/lwip/ip6_addr.h
add_sw_property include_source FreeRTOS/inc/lwip/ip6_frag.h
add_sw_property include_source FreeRTOS/inc/lwip/ip6_zone.h
add_sw_property include_source FreeRTOS/inc/lwip/mem.h
add_sw_property include_source FreeRTOS/inc/lwip/memp.h
add_sw_property include_source FreeRTOS/inc/lwip/mld6.h
add_sw_property include_source FreeRTOS/inc/lwip/nd6.h
add_sw_property include_source FreeRTOS/inc/lwip/netbuf.h
add_sw_property include_source FreeRTOS/inc/lwip/netdb.h
add_sw_property include_source FreeRTOS/inc/lwip/netif.h
add_sw_property include_source FreeRTOS/inc/lwip/netifapi.h
add_sw_property include_source FreeRTOS/inc/lwip/opt.h
add_sw_property include_source FreeRTOS/inc/lwip/pbuf.h
add_sw_property include_source FreeRTOS/inc/lwip/raw.h
add_sw_property include_source FreeRTOS/inc/lwip/sio.h
add_sw_property include_source FreeRTOS/inc/lwip/snmp.h
add_sw_property include_source FreeRTOS/inc/lwip/sockets.h
add_sw_property include_source FreeRTOS/inc/lwip/stats.h
add_sw_property include_source FreeRTOS/inc/lwip/sys.h
add_sw_property include_source FreeRTOS/inc/lwip/tcp.h
add_sw_property include_source FreeRTOS/inc/lwip/tcpbase.h
add_sw_property include_source FreeRTOS/inc/lwip/tcpip.h
add_sw_property include_source FreeRTOS/inc/lwip/timeouts.h
add_sw_property include_source FreeRTOS/inc/lwip/udp.h

add_sw_property include_source FreeRTOS/inc/lwip/priv/altcp_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/api_msg.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/mem_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/memp_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/memp_std.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/nd6_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/raw_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/sockets_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/tcp_priv.h
add_sw_property include_source FreeRTOS/inc/lwip/priv/tcpip_priv.h

add_sw_property include_source FreeRTOS/inc/lwip/prot/acd.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/autoip.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/dhcp.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/dhcp6.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/dns.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/etharp.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/ethernet.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/iana.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/icmp.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/icmp6.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/ieee.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/igmp.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/ip.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/ip4.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/ip6.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/mld6.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/nd6.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/tcp.h
add_sw_property include_source FreeRTOS/inc/lwip/prot/udp.h

add_sw_property include_source FreeRTOS/inc/netif/bridgeif.h
add_sw_property include_source FreeRTOS/inc/netif/bridgeif_opts.h
add_sw_property include_source FreeRTOS/inc/netif/etharp.h
add_sw_property include_source FreeRTOS/inc/netif/ethernet.h
add_sw_property include_source FreeRTOS/inc/netif/ieee802154.h
add_sw_property include_source FreeRTOS/inc/netif/lowpan6.h
add_sw_property include_source FreeRTOS/inc/netif/lowpan6_ble.h
add_sw_property include_source FreeRTOS/inc/netif/lowpan6_common.h
add_sw_property include_source FreeRTOS/inc/netif/lowpan6_opts.h
add_sw_property include_source FreeRTOS/inc/netif/slipif.h
add_sw_property include_source FreeRTOS/inc/netif/zepif.h


add_sw_property include_source FreeRTOS/inc/netif/ppp/auth.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ccp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/chap.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/chap_ms.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/chap-md5.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/chap-new.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/chpms.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/eap.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ecp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/eui64.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/fsm.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ipcp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ipv6cp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/lcp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/magic.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/md5.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/mppe.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pap.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ppp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ppp_impl.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/ppp_opts.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppapi.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppcrypt.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppdebug.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppoe.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppol2tp.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/pppos.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/randm.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/upap.h
add_sw_property include_source FreeRTOS/inc/netif/ppp/vj.h

# Overriden HAL files
add_sw_property excluded_hal_source HAL/inc/os/alt_syscall.h

add_sw_property include_source FreeRTOS/inc/os/alt_syscall.h  
add_sw_property include_source FreeRTOS/inc/lwipopts.h

# This driver supports only FreeRTOS BSP (OS) type
add_sw_property supported_bsp_type FreeRTOS

# Add preprocessor definitions to public makefile: ALT_LWIP
add_sw_property alt_cppflags_addition "-DALT_LWIP"
add_sw_property alt_cppflags_addition "-DLWIP_TSE_MY_SYSTEM"





# LwIP configuration options
add_sw_setting boolean system_h_define checksum.enable_generate_ip SYSTEM_H_LWIP_CHECKSUM_GEN_IP true "Enable generation of checksums for IP frames"
add_sw_setting boolean system_h_define checksum.enable_generate_udp SYSTEM_H_LWIP_CHECKSUM_GEN_UDP true "Enable generation of checksums for UDP frames"
add_sw_setting boolean system_h_define checksum.enable_generate_tcp SYSTEM_H_LWIP_CHECKSUM_GEN_TCP true "Enable generation of checksums for TCP frames"

add_sw_setting boolean system_h_define checksum.enable_check_ip SYSTEM_H_LWIP_CHECKSUM_CHECK_IP true "Enable checking of checksums from IP frames"
add_sw_setting boolean system_h_define checksum.enable_check_udp SYSTEM_H_LWIP_CHECKSUM_CHECK_UDP true "Enable checking of checksums from UDP frames"
add_sw_setting boolean system_h_define checksum.enable_check_tcp SYSTEM_H_LWIP_CHECKSUM_CHECK_TCP true "Enable checking of checksums from TCP frames"

add_sw_setting boolean system_h_define proto.enable_vlan SYSTEM_H_LWIP_PROTO_VLAN false "Enable VLAN support"
add_sw_setting boolean system_h_define proto.enable_icmp SYSTEM_H_LWIP_PROTO_ICMP true "Enable ICMP support"
add_sw_setting boolean system_h_define proto.enable_autoip SYSTEM_H_LWIP_PROTO_AUTOIP false "Enable AutoIP support"
add_sw_setting boolean system_h_define proto.enable_snmp SYSTEM_H_LWIP_PROTO_SNMP false "Enable SNMP support"
add_sw_setting boolean system_h_define proto.enable_igmp SYSTEM_H_LWIP_PROTO_IGMP true "Enable IGMP support"
add_sw_setting boolean system_h_define proto.enable_dns SYSTEM_H_LWIP_PROTO_DNS true "Enable DNS support"
add_sw_setting boolean system_h_define proto.enable_udp SYSTEM_H_LWIP_PROTO_UDP true "Enable UDP support"
add_sw_setting boolean system_h_define proto.enable_tcp SYSTEM_H_LWIP_PROTO_TCP true "Enable TCP support"
add_sw_setting boolean system_h_define proto.enable_dhcp SYSTEM_H_LWIP_PROTO_DHCP true "Enable DHCP support"

add_sw_setting decimal_number system_h_define connections.raw_pcb_count SYSTEM_H_LWIP_RAW_PCB 2 "Number of raw sockets supported (Used by ICMP for example)"
add_sw_setting decimal_number system_h_define connections.udp_pcb_count SYSTEM_H_LWIP_UDP_PCB 4 "Number of UDP sockets supported"
add_sw_setting decimal_number system_h_define connections.tcp_pcb_count SYSTEM_H_LWIP_TCP_PCB 4 "Number of TCP sockets supported"
add_sw_setting decimal_number system_h_define connections.tcp_listen_pcb_count SYSTEM_H_LWIP_TCP_PCB_LISTEN 8 "Number of TCP Listening sockets supported"

add_sw_setting decimal_number system_h_define memory.mem_size SYSTEM_H_LWIP_MEM_SIZE 32768 "Size of the memory poll"
add_sw_setting boolean system_h_define memory.overflow_check SYSTEM_H_LWIP_OVERFLOW_CHECK false "Do memory overflow checking"
add_sw_setting decimal_number system_h_define memory.pbuf_count SYSTEM_H_LWIP_PBUF_COUNT 32 "Number of packet buffers supported"

add_sw_setting boolean system_h_define loopback SYSTEM_H_LWIP_LOOPBACK false "Loopback outgoing traffic to our selfs"
add_sw_setting boolean system_h_define loopback_if SYSTEM_H_LWIP_LOOPBACKIF false "Create a loopback interface 'lo'"
add_sw_setting boolean system_h_define stats SYSTEM_H_LWIP_STATS true "Keep track of the LwIP traffic statistics"
add_sw_setting boolean system_h_define ip_forward SYSTEM_H_LWIP_IP_FORWARD false "Keep track of the LwIP traffic statistics"
add_sw_setting decimal_number system_h_define ttl SYSTEM_H_LWIP_DEFAULT_TTL 64 "The default TTL (Time To Life) set to a packet"

add_sw_setting boolean system_h_define debug.enable SYSTEM_H_LWIP_DEBUG false "Enable debug message printing"
add_sw_setting boolean system_h_define debug.all_modules_enable SYSTEM_H_LWIP_DEBUG_ALL_ON false "Enable all modules debug message printing"
