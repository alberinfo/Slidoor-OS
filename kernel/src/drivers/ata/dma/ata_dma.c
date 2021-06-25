#include "ata_dma.h"

uint16 *ata_dma_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors)
{
    uint32 prdt[2] = {ata_device->prdt_addr, (512 * sectors) | (1 << 31)};
    outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(&prdt)-0xFFFF800000000000); //PRDT
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) | 1 << 3); //Read
    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG) | 4 | 2);
    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x25 /*read ext*/ : 0xC8 /*read*/);
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) | 1);
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) & (~1));
    return ata_device->prdt_addr + 0xFFFF800000000000;
}

void ata_dma_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer)
{
    memcpy_fast(ata_device->prdt_addr + 0xFFFF800000000000, buffer, 512*sectors);
    uint32 prdt[2] = {ata_device->prdt_addr, (512 * sectors) | (1 << 31)};
    outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(&prdt)-0xFFFF800000000000); //PRDT
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) & ~(1 << 3)); //Write
    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG) | 4 | 2);
    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x35 /*Write ext*/ : 0xCA /*Write*/);
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) | 1);
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) & (~1));
    return;
}


