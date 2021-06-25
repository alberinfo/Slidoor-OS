#ifndef ATAPI_DMA_H
#define ATAPI_DMA_H

#include "../atapi.h"

uint16 *atapi_dma_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sector);

#endif