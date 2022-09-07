#include "ata_pio.h"

/********* SEND COMMAND PIO *********/

uint16 *ata_pio_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors)
{
    uint16 *buffer = kmalloc(ata_device->sectorSize*sectors);

    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x24 /*Read ext*/ : 0x20 /*Read*/);

    uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    while(stat & (1 << STT_BSY) && !(stat & (1 << STT_DRQ)))
    {
        stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    }

    for(int i = 0; i < sectors; i++)
    {
        ata_wait_irq(ata_device);
        for(int j = 0; j < ata_device->sectorSize / 2; j++)
        {
            buffer[i*(ata_device->sectorSize / 2) + j] = inportw(ata_device->io_base + DATA_REG);
        }
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
        for(int j = 0; j < ata_device->sectorSize / 2; j++)
        {
            outportw(ata_device->io_base + DATA_REG, buffer[i*(ata_device->sectorSize / 2) + j]);
        }
        ata_wait_irq(ata_device);
        outportb(ata_device->io_base + CMD_REG, 0xE7); //Cache Flush
        ata_wait_irq(ata_device);
    }
    return;
}
