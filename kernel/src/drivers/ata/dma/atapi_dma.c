#include "atapi_dma.h"

uint16 *atapi_dma_read(struct ata_dev_t *ata_device, uint32 lba, uint8 sectors)
{
	uint32 prdt[2] = {ata_device->prdt_addr, (2048 * sectors) | (1 << 31)};
	outportl(ata_device->busmaster + BM_PRD_REG, (uint64)(&prdt)-0xFFFF800000000000); //PRDT
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) | 1 << 3); //Read
    outportb(ata_device->busmaster + BM_STT_REG, inportb(ata_device->busmaster + BM_STT_REG) | 4 | 2);

	atapi_prepare_command(ata_device, 1 /*DMA*/);
    atapi_send_command(ata_device, 0xA8 /*READ*/, lba, sectors);

    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) | 1);
    ata_wait_irq(ata_device);
    outportb(ata_device->busmaster + BM_CMD_REG, inportb(ata_device->busmaster + BM_CMD_REG) & (~1));

    return ata_device->prdt_addr + 0xFFFF800000000000;
}