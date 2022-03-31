#include "atapi_dma.h"

uint16 *atapi_dma_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sectors)
{
    void *dma_addr = kmalloc_aligned(ata_device->sectorSize * sectors, 64*1024);

    uint32 *prdt = kmalloc(8); //two 4-byte entries
    prdt[0] = dma_addr - 0xFFFF800000000000;
    prdt[1] = ((ata_device->sectorSize * sectors) % (64 * 1024)) | (1 << 31); //Byte size % 64kb is done because when doing a 64kb transfer (maximum possible for dma), the byte count should be zero

    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG)); //Clear interrupt and error bits
    outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(prdt)-0xFFFF800000000000); //PRDT

    free(prdt);

    atapi_prepare_command(ata_device, 1 /*DMA*/);
    atapi_send_command(ata_device, 0xA8 /*READ*/, lba, sectors);

    outportb(ata_device->busmaster + BM_CMD_REG, 1 | (1 << 3)); //Read
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, 0); //Clear direction bit and start/stop bit


    return dma_addr;
}