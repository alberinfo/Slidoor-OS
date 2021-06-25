#include "ata.h"

bool ATA0_MasterRDY = false, ATA0_SlaveRDY = false, ATA1_MasterRDY = false, ATA1_SlaveRDY = false;

struct ata_queue_t ata_queue;

/********* ATA QUEUE INTERFACE *********/

void ata_queue_erase() //Erase the first element
{
    while(ata_transfer_in_progress);
    ata_transfer_in_progress = true; //Disable execution of ata RW requests in queue
    if(ata_queue.size > 1)
    {
        //Free the buffer created in ata_read / write
        free(ata_queue.queue->buffer);
        //Clear the information
        ata_queue.queue->ata_device = 0;
        ata_queue.queue->buffer = 0;
        ata_queue.queue->lba = 0;
        ata_queue.queue->sectors = 0;
        ata_queue.queue->write = 0;
        ata_queue.queue->ATAPI = 0;
        ata_queue.queue->completed = 0;
        //Go to next queue entry
        ata_queue.queue = ata_queue.queue->next;
        free(ata_queue.first_element_addr);
        ata_queue.first_element_addr = ata_queue.queue;
    } else if(ata_queue.size == 1) {
        //Free the buffer created in ata_read / write
        free(ata_queue.queue->buffer);
        //Clear the information
        ata_queue.queue->ata_device = 0;
        ata_queue.queue->buffer = 0;
        ata_queue.queue->lba = 0;
        ata_queue.queue->sectors = 0;
        ata_queue.queue->write = 0;
        ata_queue.queue->ATAPI = 0;
        ata_queue.queue->completed = 0;
        //Clear the last element
        free(ata_queue.first_element_addr);
        ata_queue.queue = 0;
        ata_queue.first_element_addr = 0;
        ata_queue.last_element_addr = 0;
    } else {
        ata_transfer_in_progress = false; //Enable execution of ata RW requests in queue
        return;
    }
    ata_queue.size--;
    ata_transfer_in_progress = false; //Enable execution of ata RW requests in queue
    return;
}

void ata_queue_add(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint8 write, uint8 atapi, uint16 *buffer, uint8 *completion_addr /*at what address we say we completed this command*/) //Add element at the end of the queue
{
    while(ata_transfer_in_progress);
    ata_transfer_in_progress = true; //Disable execution of ata RW requests in queue
    struct ata_queue_element_t *ata_queue_element;
    if(ata_queue.size)
    {
        ata_queue_element = ata_queue.last_element_addr;
        ata_queue_element->next = kmalloc(sizeof(struct ata_queue_element_t));
        ata_queue_element = ata_queue_element->next;
    } else {
        ata_queue.queue = kmalloc(sizeof(struct ata_queue_element_t));
        ata_queue.first_element_addr = ata_queue.queue;
        ata_queue_element = ata_queue.queue;
    }
    ata_queue.size++;
    ata_queue.last_element_addr = ata_queue_element;
    ata_queue_element->ata_device = ata_device;
    ata_queue_element->buffer = buffer;
    ata_queue_element->lba = lba;
    ata_queue_element->sectors = sectors;
    ata_queue_element->write = write;
    ata_queue_element->ATAPI = atapi;
    ata_queue_element->completed = completion_addr;
    ata_transfer_in_progress = false; //Enable execution of ata RW requests in queue
    return;
}

void ata_execute_queue()
{
    if(ata_queue.size && !ata_transfer_in_progress)
    {
        ata_transfer_in_progress = true;
        struct ata_queue_element_t element = *ata_queue.queue; //First element
        uint16 *buffaddr;
        if(element.ATAPI)
        {
            if(!element.write)
            {
                if(!element.ata_device->DMA)
                {
                    buffaddr = atapi_pio_read(element.ata_device, element.lba, element.sectors);
                    memcpy_fast(element.buffer, buffaddr, 2048*element.sectors); //Each atapi read is 2048 bytes long
                    free(buffaddr);
                } else {
                    buffaddr = atapi_dma_read(element.ata_device, element.lba, element.sectors);
                    memcpy_fast(element.buffer, buffaddr, 2048*element.sectors);
                }
            }
        } else {
            if(!element.write)
            {
                if(!element.ata_device->DMA)
                {
                    buffaddr = ata_pio_read(element.ata_device, element.lba, element.sectors);
                    memcpy_fast(element.buffer, buffaddr, 512*element.sectors); //each ata read is 512 bytes long
                    free(buffaddr);
                } else {
                    buffaddr = ata_dma_read(element.ata_device, element.lba, element.sectors);
                    memcpy_fast(element.buffer, buffaddr, 512*element.sectors);

                }
            } else {
                if(!element.ata_device->DMA)
                {
                    ata_pio_write(element.ata_device, element.lba, element.sectors, element.buffer);
                } else {
                    ata_dma_write(element.ata_device, element.lba, element.sectors, element.buffer);
                }
                free(element.buffer); //This was allocated in order to save the sector. Free plz.
            }
        }
        *element.completed = true;
        ata_transfer_in_progress = false;
        ata_queue_erase();
    }
    return;
}

/********* IRQ STUFF *********/

void ata_irq_handler(bool bus) //Could be zero or one
{
    if(!bus)
    {
        inportb(GLOBAL_ATA0_IO + STT_REG); //Clear interrupt reg(?)
        uint8 drv_reg = inportb(GLOBAL_ATA0_IO + DRV_REG);
        if(!(drv_reg & (1 << 4))) ATA0_MasterRDY = true;
        else ATA0_SlaveRDY = true;
    } else {
        inportb(GLOBAL_ATA1_IO + STT_REG); //Clear interrupt reg(?)
        uint8 drv_reg = inportb(GLOBAL_ATA1_IO + DRV_REG);
        if(!(drv_reg & (1 << 4))) ATA1_MasterRDY = true;
        else ATA1_SlaveRDY = true;
    }
    if(!ata_transfer_in_progress) ata_execute_queue();
    return;
}

void ata_wait_irq(struct ata_dev_t *ata_device)
{
    if(!ata_device->channel)
    {
        if(!ata_device->slave)
        {
            while(!ATA0_MasterRDY) asm volatile("hlt"); //Halt CPU until next interrupt arrives
            ATA0_MasterRDY = false;
            uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
            if(!(stat & (1 << 7)) && stat & (1 << 3)) ATA0_MasterRDY = true;
        } else {
            while(!ATA0_SlaveRDY) asm volatile("hlt"); //Halt CPU until next interrupt arrives
            ATA0_SlaveRDY = false;
            uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
            if(!(stat & (1 << 7)) && stat & (1 << 3)) ATA0_SlaveRDY = true;
        }
    } else {
        if(!ata_device->slave)
        {
            while(!ATA1_MasterRDY) asm volatile("hlt"); //Halt CPU until next interrupt arrives
            ATA1_MasterRDY = false;
            uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
            if(!(stat & (1 << 7)) && stat & (1 << 3)) ATA1_MasterRDY = true;
        } else {
            while(!ATA1_SlaveRDY) asm volatile("hlt"); //Halt CPU until next interrupt arrives
            ATA1_SlaveRDY = false;
            uint8 stat = inportb(ata_device->ctrl_base + ALT_STT_REG);
            if(!(stat & (1 << 7)) && stat & (1 << 3)) ATA1_SlaveRDY = true;
        }
    }
    return;
}

/********* ------- *********/

/****** LBA 28 ******/

void ata28_prepare_command(struct ata_dev_t *ata_device, uint32 lba, uint16 sectors)
{
    outportb(ata_device->io_base + DRV_REG, 0xE0 | (ata_device->slave << 4) | ((lba >> 24) & 0xF));
    ata_400ns_delay(ata_device);
    outportb(ata_device->io_base + SEC_CNT_REG, sectors);
    outportb(ata_device->io_base + LBA_LO, (uint8)lba);
    outportb(ata_device->io_base + LBA_MID, (uint8)(lba >> 8));
    outportb(ata_device->io_base + LBA_HI, (uint8)(lba >> 16));
}

/****** LBA 48 ******/

void ata48_prepare_command(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors)
{
    outportb(ata_device->io_base + DRV_REG, 0x40 | ((uint8)ata_device->slave << 4));
    ata_400ns_delay(ata_device);
    outportb(ata_device->io_base + SEC_CNT_REG, (uint8)(sectors >> 8)); //Sector count high byte
    outportb(ata_device->io_base + LBA_LO, (uint8)(lba >> 24)); //LBA 4th byte
    outportb(ata_device->io_base + LBA_MID, (uint8)(lba >> 32)); //LBA 5th byte
    outportb(ata_device->io_base + LBA_HI, (uint8)(lba >> 40)); //LBA 6th byte
    outportb(ata_device->io_base + SEC_CNT_REG, (uint8)sectors); //Sector count low byte
    outportb(ata_device->io_base + LBA_LO, (uint8)lba); //LBA 1st byte
    outportb(ata_device->io_base + LBA_MID, (uint8)(lba >> 8)); //LBA 2nd byte
    outportb(ata_device->io_base + LBA_HI, (uint8)(lba >> 16)); //LBA 3rd byte
}

/********* ------- *********/

void ata_400ns_delay(struct ata_dev_t *ata_device)
{
    sleep(1, SleepMili); //Ye, so what?
    //for(int i = 0; i < 4; i++) inportb(ata_device->ctrl_base + ALT_STT_REG);
}

void ata_soft_reset(struct ata_dev_t *ata_device) //Soft reset ata bus
{
    outportb(ata_device->ctrl_base, 1 << 2); //Set bus reset bit
    //sleep(5, SleepMicro); //microsecs
    sleep(1, SleepMili);
    outportb(ata_device->ctrl_base, 0); //Clear bus reset bit and enable irqs
}

void ata_change_drive(uint16 io_base, uint16 ctrl_base, bool slave)
{
    outportb(io_base + DRV_REG, 0xA0 + (slave << 4));
    inportb(ctrl_base);
    inportb(ctrl_base);
    inportb(ctrl_base);
    inportb(ctrl_base);
}

int ata_identify_type(struct ata_dev_t *ata_device, int drive_num)
{
    ata_change_drive(ata_device->io_base, ata_device->ctrl_base, ata_device->slave);
    uint16 signature = inportb(ata_device->io_base + LBA_MID) | (inportb(ata_device->io_base + LBA_HI) << 8);
    if(signature == 0xEB14)
    {
        ata_device->type = "PATAPI";
    } else if(signature == 0x9669) {
        ata_device->type = "SATAPI";
    } else if(signature == 0) {
        ata_device->type = "PATA";
    } else if(signature == 0xC33C) {
        ata_device->type = "SATA";
    } else {
        ata_delete_drive(drive_num);
        return -1; //Device does not exist or is non-ata
    }
    return 0;
}

string ata_identify_word2ascii(uint16 *buf, uint8 start, uint8 end)
{
    string str = kmalloc(end - start + 1);
    uint8 stridx = 0;
    for(int i = start; i <= end; i++, stridx += 2)
    {
        if(buf[i] != 0x2020)
        {
            str[stridx] = ((uint8)(buf[i] >> 8));
            str[stridx+1] = ((uint8)buf[i]);
        } else {
            break;
        }
    }
    return str;
}

void ata_identify(struct ata_dev_t *ata_device, int drive_num /*only used in case of non-existance of the drive*/)
{
    ata_change_drive(ata_device->io_base, ata_device->ctrl_base, ata_device->slave);
    ata_400ns_delay(ata_device);
    outportb(ata_device->io_base + SEC_CNT_REG, 0);
    outportb(ata_device->io_base + LBA_LO, 0);
    outportb(ata_device->io_base + LBA_MID, 0);
    outportb(ata_device->io_base + LBA_HI, 0);
    outportb(ata_device->io_base + CMD_REG, 0xEC); //#IDENTIFY
    
    if(inportb(ata_device->ctrl_base + ALT_STT_REG) == 0) { ata_delete_drive(drive_num); return; } //The device does not exist
    ata_wait_irq(ata_device);
    if((inportb(ata_device->io_base + LBA_MID) && inportb(ata_device->io_base + LBA_HI)) || inportb(ata_device->io_base + ERR_REG) & (1 << 2)) { atapi_identify(ata_device, drive_num); return; }
    if(inportb(ata_device->ctrl_base + ALT_STT_REG) == 0 || inportb(ata_device->ctrl_base + ALT_STT_REG) & 1) { ata_delete_drive(drive_num); return; }
    
    uint16 *buffer = kmalloc(256*2); //256 Words, each word being two bytes.
    for(int i = 0; i < 256; i++)
    {
        buffer[i] = inportw(ata_device->io_base + DATA_REG);
    }
    struct ata_identify_t *IDENTIFY = kmalloc(sizeof(struct ata_identify_t));
    IDENTIFY->GCBSI = buffer[0];
    IDENTIFY->Sconf = buffer[2];
    IDENTIFY->SerNum = ata_identify_word2ascii(buffer, 10, 19);
    IDENTIFY->FirmRev = ata_identify_word2ascii(buffer, 23, 26);
    IDENTIFY->ModNum = ata_identify_word2ascii(buffer, 27, 46);
    IDENTIFY->MaxSecxDRQ = buffer[47];
    IDENTIFY->TCFSOP = buffer[48];
    IDENTIFY->Capabilities0 = buffer[49];
    IDENTIFY->Capabilities1 = buffer[50];
    IDENTIFY->FFCS = buffer[53];
    IDENTIFY->CurrSecxDRQ = buffer[59];
    IDENTIFY->PIO28_AddressableSec0 = buffer[60];
    IDENTIFY->PIO28_AddressableSec1 = buffer[61];
    IDENTIFY->MDMASup = buffer[63];
    IDENTIFY->PIOSup = buffer[64];
    IDENTIFY->MMDTC = buffer[65];
    IDENTIFY->MRMDTC = buffer[66];
    IDENTIFY->MPTCwoutFC = buffer[67];
    IDENTIFY->MPTCwFC = buffer[68];
    IDENTIFY->QDepth = buffer[75];
    IDENTIFY->SATACap = buffer[76];
    IDENTIFY->SATAFtSup = buffer[78];
    IDENTIFY->SATAFtEn = buffer[79];
    IDENTIFY->MajorRevNum = buffer[80];
    IDENTIFY->MinorRevNum = buffer[81];
    IDENTIFY->CMDSetSup = buffer[82];
    IDENTIFY->CMDSetsSup = buffer[83];
    IDENTIFY->CMDSet_FtSup = buffer[84];
    IDENTIFY->CMDSet_FtEn1 = buffer[85];
    IDENTIFY->CMDSet_FtEn2 = buffer[86];
    IDENTIFY->CMDSet_FtEn2 = buffer[87];
    IDENTIFY->UDMASup = buffer[88];
    IDENTIFY->TSEUC = buffer[89];
    IDENTIFY->TESEC = buffer[90];
    IDENTIFY->CAPMVal = buffer[91];
    IDENTIFY->MPasswdID = buffer[92];
    IDENTIFY->HRR = buffer[93];
    IDENTIFY->VRAMVal = buffer[94];
    IDENTIFY->SMRS = buffer[95];
    IDENTIFY->STTD = buffer[96];
    IDENTIFY->SAL = buffer[97];
    IDENTIFY->SPG0 = buffer[98];
    IDENTIFY->SPG1 = buffer[99];
    IDENTIFY->LBA48_AddressableSec0 = buffer[100];
    IDENTIFY->LBA48_AddressableSec1 = buffer[101];
    IDENTIFY->LBA48_AddressableSec2 = buffer[102];
    IDENTIFY->LBA48_AddressableSec3 = buffer[103];
    if(IDENTIFY->LBA48_AddressableSec0 != 0 || IDENTIFY->LBA48_AddressableSec1 != 0 || IDENTIFY->LBA48_AddressableSec2 != 0 || IDENTIFY->LBA48_AddressableSec3 != 0)
    {
        ata_device->LBA48 = true;
        ata_device->size = (IDENTIFY->LBA48_AddressableSec0 | ((uint32)IDENTIFY->LBA48_AddressableSec1 << 16) | ((uint64)IDENTIFY->LBA48_AddressableSec2 << 32) | ((uint64)IDENTIFY->LBA48_AddressableSec3 << 48)) * 512 / 1024 / 1024;
    } else {
        ata_device->LBA48 = false;
        ata_device->size = (IDENTIFY->PIO28_AddressableSec0 | ((uint32)IDENTIFY->PIO28_AddressableSec1 << 16)) * 512 / 1024 / 1024;
    }
    IDENTIFY->STTP = buffer[104];
    IDENTIFY->SecSize = buffer[106];
    IDENTIFY->IsD = buffer[107];
    IDENTIFY->NAA_IEEIDlo = buffer[108];
    IDENTIFY->IEEODhi_UIDlo = buffer[109];
    IDENTIFY->UIDmid = buffer[110];
    IDENTIFY->UIDhi = buffer[111];
    IDENTIFY->WxSec0 = buffer[117];
    IDENTIFY->WxSec1 = buffer[118];
    IDENTIFY->SupSet = buffer[119];
    IDENTIFY->CMDSet_FtEn3 = buffer[120];
    IDENTIFY->SecuritySTT = buffer[128];
    IDENTIFY->CFAPM1 = buffer[160];
    IDENTIFY->CurrMedSerNum = ata_identify_word2ascii(buffer, 176, 205);
    IDENTIFY->SCTCT = buffer[206];
    IDENTIFY->LBlocksAlign = buffer[209];
    IDENTIFY->WRVSecCountM3_0 = buffer[210];
    IDENTIFY->WRVSecCountM3_1 = buffer[211];
    IDENTIFY->VSecCountM2_0 = buffer[212];
    IDENTIFY->VSecCountM2_1 = buffer[213];
    IDENTIFY->NVCacheCap = buffer[214];
    IDENTIFY->NVCacheSizeLo = buffer[215];
    IDENTIFY->NVCacheSizeHi = buffer[216];
    IDENTIFY->NMRR = buffer[217];
    IDENTIFY->NVCacheOp = buffer[219];
    IDENTIFY->WRVFtSetCurr = buffer[220];
    IDENTIFY->TMajRevNum = buffer[222];
    IDENTIFY->TMinRevNum = buffer[223];
    IDENTIFY->MinNumSecxDownMicro = buffer[234];
    IDENTIFY->MaxNumSecxDownMicro = buffer[235];
    IDENTIFY->IntegrityWord = buffer[255];
    ata_device->IDENTIFY_addr = (uint64)IDENTIFY;
    free(buffer);
    if(IDENTIFY->UDMASup >> 8 || IDENTIFY->MDMASup >> 8) {ata_device->DMA = true; return;}
    uint32 prdt_addr = ((uint64)kmalloc_aligned(0x8000, 0x10000)) - 0xFFFF800000000000; //Alloc the double, so we'll be able to align it;
    ata_device->prdt_addr = prdt_addr;
    for(int i = 6, ander = 1 << 6; i >= 0; i--)
    {
        if(IDENTIFY->UDMASup & ander) //Is UDMA mode (i) supported?
        {
            //Enable UDMA mode (i)
            outportb(ata_device->io_base + DRV_REG, 0xE0 | (ata_device->slave << 4)); //Drive was already selected
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
        if(IDENTIFY->MDMASup & ander) //Is MDMA mode (i) supported?
        {
            //Enable MDMA mode (i)
            outportb(ata_device->io_base + DRV_REG, 0xA0 | (ata_device->slave << 4)); //Drive was already selected
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

void ata_add_drive(uint16 io_base, uint16 ctrl_base, uint16 busmaster, bool channel, bool slave)
{
    ata_devices.devices[ata_devices.dev_amount].channel = channel;
    ata_devices.devices[ata_devices.dev_amount].slave = slave;
    ata_devices.devices[ata_devices.dev_amount].io_base = io_base;
    ata_devices.devices[ata_devices.dev_amount].ctrl_base = ctrl_base;
    ata_devices.devices[ata_devices.dev_amount].busmaster = busmaster;
    ata_devices.devices[ata_devices.dev_amount].type = "Unknown";
    outportb(ata_devices.devices[ata_devices.dev_amount++].io_base + DRV_REG, (1 << 6)); //Enable LBA
}

void ata_delete_drive(int drive_num)
{
    ata_devices.dev_amount--;
    for(int i = drive_num; i < ata_devices.dev_amount; i++)
    {
        ata_devices.devices[i] = ata_devices.devices[i+1];
    }
    memzero(&ata_devices.devices[ata_devices.dev_amount+1],sizeof(struct ata_dev_t)); //Clear the previous last pos, it may keep its old value
}

void init_ata(uint32 busmaster) //soft reset ata bus (ata0 and ata1, but only if there's any device on 'em), identify the devices, and store their information
{
    ata_queue.size = 0;
    ata_queue.first_element_addr = 0;
    ata_queue.last_element_addr = 0;
    ata_transfer_in_progress = false;
    
    struct ata_dev_t temporary_dev;
    temporary_dev.ctrl_base = GLOBAL_ATA0_CTRL;
    ata_soft_reset(&temporary_dev);    

    uint8 bus = inportb(GLOBAL_ATA0_CTRL + ALT_STT_REG);
    if(!(bus & 1 << 5) && !(bus & 1 << 2) && !(bus & 1 << 1))
    {
        ata_add_drive(GLOBAL_ATA0_IO, GLOBAL_ATA0_CTRL, busmaster, 0, ATA_MASTER);
        ata_identify_type(&ata_devices.devices[ata_devices.dev_amount-1], ata_devices.dev_amount-1);
    }
    
    ata_change_drive(GLOBAL_ATA0_IO, GLOBAL_ATA0_CTRL, ATA_SLAVE);
    
    bus = inportb(GLOBAL_ATA0_CTRL + ALT_STT_REG);
    if(!(bus & 1 << 5) && !(bus & 1 << 2) && !(bus & 1 << 1))
    {
        ata_add_drive(GLOBAL_ATA0_IO, GLOBAL_ATA0_CTRL, busmaster, 0, ATA_SLAVE);
        ata_identify_type(&ata_devices.devices[ata_devices.dev_amount-1], ata_devices.dev_amount-1);
    }
    
    temporary_dev.ctrl_base = GLOBAL_ATA1_CTRL;
    ata_soft_reset(&temporary_dev);

    
    bus = inportb(GLOBAL_ATA1_CTRL + ALT_STT_REG);
    if(!(bus & 1 << 5) && !(bus & 1 << 2) && !(bus & 1 << 1))
    {
        ata_add_drive(GLOBAL_ATA1_IO, GLOBAL_ATA1_CTRL, busmaster+8, 1, ATA_MASTER);
        ata_identify_type(&ata_devices.devices[ata_devices.dev_amount-1], ata_devices.dev_amount-1);
    }
    
    ata_change_drive(GLOBAL_ATA1_IO, GLOBAL_ATA1_CTRL, ATA_SLAVE);

    bus = inportb(GLOBAL_ATA1_CTRL + ALT_STT_REG);
    if(!(bus & 1 << 5) && !(bus & 1 << 2) && !(bus & 1 << 1))
    {
        ata_add_drive(GLOBAL_ATA1_IO, GLOBAL_ATA1_CTRL, busmaster+8, 1, ATA_SLAVE);
        ata_identify_type(&ata_devices.devices[ata_devices.dev_amount-1], ata_devices.dev_amount-1);
    }

    //ata_devices.devices = kmalloc(ata_devices.dev_amount); //There are (max) two drives per bus
    for(int i = 0; i < ata_devices.dev_amount; i++)
    {
        ata_identify(&ata_devices.devices[i],i);
    }
}

/********* RW ATA-"API" *********/

void ata_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer, uint8 *completion_addr)
{
    int ATAPI = 0; //Is this an atapi device?
    if(strcmp(ata_device->type, "PATAPI") == 0 || strcmp(ata_device->type, "SATAPI") == 0) ATAPI = 1;
    ata_queue_add(ata_device, lba,sectors, 0, ATAPI, buffer, completion_addr);
    ata_execute_queue(); //If we did not execute any of the ata requests, then theres either a command in progress or the device is not ready
    return;
}

void ata_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer, uint8 *completion_addr)
{
    int ATAPI = 0; //Is this an atapi device?
    if(ata_device->type == "PATAPI" || ata_device->type == "SATAPI") ATAPI = 1;
    
    //Here we'll copy the contents of the buffer, in order to save it from modifications before writing.
    uint16 *actual_buffer;
    if(!ATAPI)
    {
        actual_buffer = kmalloc(2048*sectors);
        memcpy_fast(actual_buffer, buffer, 2048*sectors);
    } else {
        actual_buffer = kmalloc(512*sectors);
        memcpy_fast(actual_buffer, buffer, 512*sectors);
    }
    ata_queue_add(ata_device, lba,sectors, 1, ATAPI, actual_buffer, completion_addr);
    ata_execute_queue(); //If we did not execute any of the ata requests, then theres either a command in progress or the device is not ready
    return;
}
