#ifndef _LWIP_TSE_ETHERNETIF_H_
#define _LWIP_TSE_ETHERNETIF_H_

#include <lwip/netif.h>
#include <lwip/err.h>
#include <lwip/sys.h>

#include <stdint.h>

#include <lwip_tse.h>

#define PHY_COUNT 1

//  This times PBUF_POOL_BUFSIZE+4 is the amount of memory used to buffer incoming packets.
//  This can be small if you dedicate sufficient time to process incoming packets.
//  If it's too small, lwIP will run - only incoming packets will be dropped.
#define LWIP_RX_ETH_BUFFER  				60
#define LWIP_RECEIVE_SEMAPHORE				1
#define dprintf(x) printf x
/**
 * Private data used to operate your ethernet interface.
 */
struct ethernetif {
	struct eth_addr *ethaddr;
	volatile int    iface;
	volatile int    link_alive;
	volatile int    link_speed;
	volatile int    full_duplex;

	//  Extra stats
	volatile unsigned   bytes_sent;
	volatile unsigned   bytes_recv;

	//  lwIP pbuf circular buffer.  A list of pbufs that are used to store
	//  incoming Ethernet packets
	struct pbuf     *lwipRxPbuf[LWIP_RX_ETH_BUFFER];
	volatile int    lwipRxIndexIsr;
	volatile int    lwipRxIndex;
	volatile int    lwipRxCount;

	volatile int    current_state;

	//  Pointer to TSE hardware descriptor - needed to send packets
	struct _lwip_tse_info   *tse_info;
};

/* Base-Structure for all lwIP TSE information */
typedef struct _lwip_tse_info
{
	tse_mac_trans_info mi; /* MAC base driver data. */

	// Location for the SGDMA Descriptors
	alt_sgdma_descriptor *desc;

	// lwIP Ethernetif structure
	struct ethernetif   *ethernetif;

	// Hardware location
	alt_tse_system_info *tse;

#if LWIP_RECEIVE_SEMAPHORE
	sys_sem_t rx_semaphore;
#endif
} lwip_tse_info;

extern lwip_tse_info tse[PHY_COUNT];

err_t ethernetif_init(struct netif *netif);
int ethernetif_input(struct netif *netif);

#endif /*_LWIP_TSE_ETHERNETIF_H_ */
