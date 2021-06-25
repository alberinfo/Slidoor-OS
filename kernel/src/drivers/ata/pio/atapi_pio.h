#ifndef ATAPI_PIO_H
#define ATAPI_PIO_H

#include "../atapi.h"

uint16 *atapi_pio_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sectors);

#endif
