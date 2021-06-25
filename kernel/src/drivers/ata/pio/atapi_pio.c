#include "atapi_pio.h"

uint16 *atapi_pio_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sectors)
{
    atapi_prepare_command(ata_device, 0 /*PIO*/);
    atapi_send_command(ata_device, 0xA8 /*READ*/, lba, sectors);
    uint16 *buffer = kmalloc(1024*2*sectors);
    for(int i = 0; i < sectors; i++)
    {
        for(int j = 0; j < 1024; j++) //4 Sectors
        {
            buffer[i*1024+j] = inportw(ata_device->io_base + DATA_REG);
        }
        ata_wait_irq(ata_device);
    }
    return buffer;
}
