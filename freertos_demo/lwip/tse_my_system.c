#ifdef ALT_INICHE
    #include "ipport.h"
#endif

#include "system.h"
#include "altera_avalon_tse.h"
#include "altera_avalon_tse_system_info.h"

alt_tse_system_info tse_mac_device[MAXNETS] = {
		TSE_SYSTEM_INT_MEM_NO_SHARED_FIFO(ETH_TSE, 0, ETH_SGDMA_TX, ETH_SGDMA_RX, TSE_PHY_AUTO_ADDRESS, 0)
		
};
