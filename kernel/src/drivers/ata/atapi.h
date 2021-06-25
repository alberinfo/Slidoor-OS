#ifndef ATAPI_H
#define ATAPI_H

#define ATAPI_GLOBAL_SEC_SIZE 2048

#include "ata.h"
#include "../../memory/pmm.h"

void atapi_identify(struct ata_dev_t *ata_device, int drive_num);
void atapi_prepare_command(struct ata_dev_t *ata_device, uint8 DMA);
void atapi_send_command(struct ata_dev_t *ata_device, uint8 command, uint32 lba, uint8 sectors);

#endif