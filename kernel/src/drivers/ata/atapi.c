#include "atapi.h"

void atapi_identify(struct ata_dev_t *ata_device, int drive_num /*only used in case of non-existance of the drive*/)
{
    //We already made sure this func is only called when the device sets error after IDENTIFY \
    or after ata_identify_type returned a type different from PATA and SATA
    outportb(ata_device->io_base + CMD_REG, 0xA1); //#IDENTIFY PACKET

    if(inportb(ata_device->ctrl_base + ALT_STT_REG) == 0) { ata_delete_drive(drive_num); return; } //The device does not existata_wait_irq(ata_device);
    ata_wait_irq(ata_device);
    if(inportb(ata_device->ctrl_base + ALT_STT_REG) == 0 || inportb(ata_device->ctrl_base + ALT_STT_REG) & 1) { ata_delete_drive(drive_num); return; }

    uint16 *buffer = kmalloc(256*2); //256 Words, each word being two bytes.
    for(int i = 0; i < 256; i++)
    {
    	buffer[i] = inportw(ata_device->io_base + DATA_REG);
	}
    struct ata_identify_packet_t *IDENTIFY_PACKET = kmalloc(sizeof(struct ata_identify_packet_t));
    IDENTIFY_PACKET->GCBSI = buffer[0];
    IDENTIFY_PACKET->Sconf = buffer[2];
    IDENTIFY_PACKET->SerNum = ata_identify_word2ascii(buffer, 10, 19);
    IDENTIFY_PACKET->FirmRev = ata_identify_word2ascii(buffer, 23, 26);
    IDENTIFY_PACKET->ModNum = ata_identify_word2ascii(buffer, 27, 46);
    IDENTIFY_PACKET->Capabilities0 = buffer[49];
    IDENTIFY_PACKET->Capabilities1 = buffer[50];
    IDENTIFY_PACKET->FRV = buffer[53];
    IDENTIFY_PACKET->DMASup0 = buffer[62];
    IDENTIFY_PACKET->DMASup1 = buffer[63];
    IDENTIFY_PACKET->PIOSup = buffer[64];
    IDENTIFY_PACKET->MMDTC = buffer[65];
    IDENTIFY_PACKET->MRMDTC = buffer[66];
    IDENTIFY_PACKET->MPTCwoutFC = buffer[67];
    IDENTIFY_PACKET->MPTCwFC = buffer[68];
    IDENTIFY_PACKET->MajorRevNum = buffer[80];
    IDENTIFY_PACKET->MinorRevNum = buffer[81];
    IDENTIFY_PACKET->CMDSet_FtSup0 = buffer[82];
    IDENTIFY_PACKET->CMDSet_FtSup1 = buffer[83];
    IDENTIFY_PACKET->CMDSet_FtSupExt = buffer[84];
    IDENTIFY_PACKET->CMDSet_FtEn1 = buffer[85];
    IDENTIFY_PACKET->CMDSet_FtEn2 = buffer[86];
    IDENTIFY_PACKET->CMDSet_FtEn2 = buffer[87];
    IDENTIFY_PACKET->UDMASup = buffer[88];
    IDENTIFY_PACKET->TSEUC = buffer[89];
    IDENTIFY_PACKET->TESEC = buffer[90];
    IDENTIFY_PACKET->MPasswdID = buffer[92];
    IDENTIFY_PACKET->HRR = buffer[93];
    IDENTIFY_PACKET->VRAMVal = buffer[94];
    IDENTIFY_PACKET->NAA_IEEIDlo = buffer[108];
    IDENTIFY_PACKET->IEEODhi_UIDlo = buffer[109];
    IDENTIFY_PACKET->UIDmid = buffer[110];
    IDENTIFY_PACKET->UIDhi = buffer[111];
    IDENTIFY_PACKET->ATAPINullByteCnt = buffer[125];
    IDENTIFY_PACKET->SecuritySTT = buffer[128];
    IDENTIFY_PACKET->IntegrityWord = buffer[255];
    ata_device->IDENTIFY_addr = (uint64)IDENTIFY_PACKET;
    free(buffer);
    atapi_read_capacity(ata_device);
    if(IDENTIFY_PACKET->DMASup1 /*MDMA Sup*/ >> 8 || IDENTIFY_PACKET->UDMASup /*UDMA Sup*/ >> 8) {ata_device->DMA = true; return;}
    uint32 prdt_addr = ((uint64)kmalloc_aligned(0x8000, 0x10000)) - 0xFFFF800000000000; //Alloc the double, so we'll be able to align it;
    ata_device->prdt_addr = prdt_addr;
	for(int i = 6, ander = 1 << 6; i >= 0; i--)
    {
        if(IDENTIFY_PACKET->UDMASup & ander) //Is UDMA mode (i) supported?
        {
            //Enable UDMA mode (i)
            outportb(ata_device->io_base + DRV_REG, ata_device->slave << 4); //Drive was already selected
            ata_400ns_delay(ata_device);
            outportb(ata_device->io_base + SEC_CNT_REG, 8 /*0b1000*/ << 3 | i); //UDMA Mode (i)
            outportb(ata_device->io_base + FT_REG, 3); //Change drive's transfer mode
            outportb(ata_device->io_base + CMD_REG, 0xEF); //Set features
            ata_wait_irq(ata_device);
            ata_device->DMA = true;
            return;
        }
        ander >>= 1;
    }
    for(int i = 2, ander = 1 << 2; i >= 0; i--)
    {
        if(IDENTIFY_PACKET->DMASup1 & ander) //Is MDMA mode (i) supported?
        {
            //Enable MDMA mode (i)
            outportb(ata_device->io_base + DRV_REG, ata_device->slave << 4); //Drive was already selected
            ata_400ns_delay(ata_device);
            outportb(ata_device->io_base + SEC_CNT_REG, 4 /*0b100*/ << 3 | i); //MDMA Mode (i)
            outportb(ata_device->io_base + FT_REG, 3); //Change drive's transfer mode
            outportb(ata_device->io_base + CMD_REG, 0xEF); //Set features
            ata_wait_irq(ata_device);
            ata_device->DMA = true;
            return;
        }
        ander >>= 1;
    }
    return;
}

void atapi_read_capacity(struct ata_dev_t *ata_device)
{
    outportb(ata_device->io_base + FT_REG, 0);
    outportb(ata_device->io_base + LBA_MID, 8);
    outportb(ata_device->io_base + LBA_HI, 8);
    outportb(ata_device->io_base + CMD_REG, 0xA0);

    uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    while(!(stat & 1 << 3) && stat & 1 << 7) //Poll for ready bit to set and bsy bit to unset
    {
        sleep(10, SleepMicro);
        stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    }

    atapi_send_command(ata_device, 0x25, 0, 0);

    uint32 lba = 0, block_size = 0;
    uint16 read = inportw(ata_device->io_base + DATA_REG);
    lba |= ((read & 0xFF) << 8) | (read >> 8);
    read = inportw(ata_device->io_base + DATA_REG);
    lba <<= 16;
    lba |= ((read & 0xFF) << 8) | (read >> 8);

    read = inportw(ata_device->io_base + DATA_REG);
    block_size |= ((read & 0xFF) << 8) | (read >> 8);
    read = inportw(ata_device->io_base + DATA_REG);
    block_size <<= 16;
    block_size |= ((read & 0xFF) << 8) | (read >> 8);

    ata_device->size = (lba+1)*block_size / 1024 / 1024;
}

void atapi_prepare_command(struct ata_dev_t *ata_device, uint8 DMA)
{
    outportb(ata_device->io_base + DRV_REG, ata_device->slave << 4);
    outportb(ata_device->io_base + FT_REG, DMA);
    if(DMA) //When using dma transfers, maximal byte count must be 0
    {
    	outportb(ata_device->io_base + LBA_MID, 0);
    	outportb(ata_device->io_base + LBA_HI, 0);
    } else {
    	outportb(ata_device->io_base + LBA_MID, (uint8)ATAPI_GLOBAL_SEC_SIZE);
    	outportb(ata_device->io_base + LBA_HI, (uint8)(ATAPI_GLOBAL_SEC_SIZE >> 8));
    }
    outportb(ata_device->io_base + CMD_REG, 0xA0); //Tell that we're sending an ATA Packet
    uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    while(!(stat & 1 << 3) && stat & 1 << 7) //Poll for ready bit to set and bsy bit to unset
    {
    	sleep(10, SleepMicro);
    	stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    }
    //ata_wait_irq(ata_device); //IRQ Doesnt fire.
}

void atapi_send_command(struct ata_dev_t *ata_device, uint8 command, uint32 lba, uint8 sectors)
{
    outportw(ata_device->io_base + DATA_REG, command);
    outportw(ata_device->io_base + DATA_REG, ((lba >> 8) & 0xFF00) | ((lba >> 24) & 0xFF));
    outportw(ata_device->io_base + DATA_REG, ((lba << 8) & 0xFF00) | ((lba >> 8) & 0xFF));
    outportw(ata_device->io_base + DATA_REG, 0);
    outportw(ata_device->io_base + DATA_REG, sectors);
    outportw(ata_device->io_base + DATA_REG, 0);
    uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    while(!(stat & 1 << 3) && stat & 1 << 7) //Poll for ready bit to set and bsy bit to unset
    {
        sleep(10, SleepMicro);
        stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
    }
    //ata_wait_irq(ata_device); //IRQ Doesnt fire.
}