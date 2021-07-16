
#ifndef __LWIP_TSE_MAC_H__
#define __LWIP_TSE_MAC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <io.h>
#include <system.h>
#include <alt_types.h>
#include <sys/alt_irq.h>
#include <sys/alt_cache.h>



int tse_sgdma_rx_isr(void * context, u_long intnum);
int tse_sgdma_read_init(lwip_tse_info* tse_ptr);
int tse_mac_rcv(struct ethernetif *ethernetif);
int tse_mac_init(int iface, struct ethernetif *ethernetif);
err_t tse_mac_raw_send(struct netif *netif, struct pbuf *pkt);
int tse_mac_rcv(struct ethernetif *ethernetif);

#endif /* __LWIP_TSE_MAC_H__ */
