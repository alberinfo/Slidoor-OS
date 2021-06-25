#ifndef ATA_PIO_H
#define ATA_PIO_H

#include "../ata.h"

uint16 *ata_pio_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors);
void ata_pio_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer);

#endif
