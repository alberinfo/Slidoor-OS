#ifndef ATA_DMA_H
#define ATA_DMA_H

#include "../ata.h"

#define BM_CMD_REG 0
#define BM_STT_REG 2
#define BM_PRD_REG 4

uint16 *ata_dma_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors);
void ata_dma_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer);

#endif
