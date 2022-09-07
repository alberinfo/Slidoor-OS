#include "ata_dma.h"

uint16 *ata_dma_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors)
{
    void *dma_addr = kmalloc_aligned(ata_device->sectorSize * sectors, 64*1024);
    
    uint32 *prdt = kmalloc(8); //two 4-byte fields
    prdt[0] = dma_addr - 0xFFFF800000000000;
    prdt[1] = ((ata_device->sectorSize * sectors) % (64 * 1024)) | (1 << 31); //Byte size % 64kb is done because when doing a 64kb transfer (maximum possible for dma), the byte count should be zero

    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG)); //Clear interrupt and error bits
    outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(prdt)-0xFFFF800000000000); //PRDT

    free(prdt);

    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x25 /*read ext*/ : 0xC8 /*read*/);

    outportb(ata_device->busmaster + BM_CMD_REG, 1 | (1 << 3)); //Read
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, 0); //Clear direction bit and start/stop bit

    return dma_addr;
}

void ata_dma_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer)
{
    void *dma_addr = kmalloc_aligned(ata_device->sectorSize * sectors, 64*1024);
    memcpy_fast(dma_addr, buffer, ata_device->sectorSize*sectors);
    
    uint32 *prdt = kmalloc(8); //two 4-byte fields
    prdt[0] = dma_addr - 0xFFFF800000000000;
    prdt[1] = ((ata_device->sectorSize * sectors) % (64 * 1024)) | (1 << 31); //Byte size % 64kb is done because when doing a 64kb transfer (maximum possible for dma), the byte count should be zero

    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG)); //Clear interrupt and error bits
    outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(prdt)-0xFFFF800000000000); //PRDT

    free(prdt);

    if(!ata_device->LBA48) ata28_prepare_command(ata_device, lba, sectors);
    else ata48_prepare_command(ata_device, lba, sectors);
    outportb(ata_device->io_base + CMD_REG, ata_device->LBA48 ? 0x35 /*Write ext*/ : 0xCA /*Write*/);

    outportb(ata_device->busmaster + BM_CMD_REG, 1); //Write
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, 0); //Clear direction bit and start/stop bit

    free(dma_addr);
    
    return;
}