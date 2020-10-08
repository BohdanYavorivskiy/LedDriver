#ifndef DMABUFFER_H
#define DMABUFFER_H

#include "buffer.h"
	
#include <project.h>

/* DMA Configuration for DMA_TX_M */
#define DMA_TX_M_BYTES_PER_BURST       (1u)
#define DMA_TX_M_REQUEST_PER_BURST     (1u)
#define DMA_TX_M_SRC_BASE              (CYDEV_SRAM_BASE)
#define DMA_TX_M_DST_BASE              (CYDEV_PERIPH_BASE)

/* Variable declarations for DMA_TX*/
uint8 txChannel;
uint8 txTD;

void transferEnable()
{
	CyDmaChEnable(txChannel, 1u);
}

void transferEnableWithNewAddr(const uint8  * const addr)
{
	CyDmaTdSetAddress(txTD, LO16((uint32)addr), LO16((uint32)SPIM_TXDATA_PTR));
	CyDmaChEnable(txChannel, 1u);
}	

void initDma()
{
	/* Init DMA, 1 byte bursts, each burst requires a request */ 
    txChannel = DMA_TX_M_DmaInitialize(DMA_TX_M_BYTES_PER_BURST, DMA_TX_M_REQUEST_PER_BURST, 
                                        HI16(DMA_TX_M_SRC_BASE), HI16(DMA_TX_M_DST_BASE));

    txTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(txTD, SizeLine, DMA_DISABLE_TD, TD_INC_SRC_ADR | DMA_TX_M__TD_TERMOUT_EN);

    /* From the memory to the SPIM */
    CyDmaTdSetAddress(txTD, LO16((uint32)bufferPtr()), LO16((uint32)SPIM_TXDATA_PTR));
    
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(txChannel, txTD); 
}
	
	
#endif // DMABUFFER_H