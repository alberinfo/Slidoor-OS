#include "ata_pio.h"

/********* SEND COMMAND PIO *********/

uint16 *ata_pio_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors)
{
    uint16 *buffer = kmalloc(256*2*sectors);
    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x24 /*Read ext*/ : 0x20 /*Read*/);
    for(int i = 0; i < sectors; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            buffer[i*256 + j] = inportw(ata_device->io_base + DATA_REG);
        }
        ata_wait_irq(ata_device);
    }
    return buffer;
}

void ata_pio_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer)
{
    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x34 /*Write ext*/ : 0x30 /*Write*/);
    for(int i = 0; i < sectors; i++)
    {
        //ata_wait_irq(ata_device);
        for(int j = 0; j < 256; j++)
        {
            outportw(ata_device->io_base + DATA_REG, buffer[i*256 + j]);
        }
        ata_wait_irq(ata_device);
        outportb(ata_device->io_base + CMD_REG, 0xE7); //Cache Flush
        ata_wait_irq(ata_device);
    }
    return;
}
