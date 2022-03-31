#include "atapi_pio.h"

uint16 *atapi_pio_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sectors)
{
    atapi_prepare_command(ata_device, 0 /*PIO*/);
    atapi_send_command(ata_device, 0xA8 /*READ (12)*/, lba, sectors);
    
    uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    while(stat & (1 << STT_BSY) && !(stat & (1 << STT_DRQ)))
    {
        stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    }

    uint16 *buffer = kmalloc(ata_device->sectorSize*sectors);
    for(int i = 0; i < sectors; i++)
    {
        ata_wait_irq(ata_device);
        for(int j = 0; j < ata_device->sectorSize / 2; j++)
        {
            buffer[i*(ata_device->sectorSize / 2)+j] = inportw(ata_device->io_base + DATA_REG);
        }
    }

    return buffer;
}
