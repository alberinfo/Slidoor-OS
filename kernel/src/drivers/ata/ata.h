#ifndef ATA_H
#define ATA_H

#include "../../string/types.h"
#include "../../arch/x86/cpu.h"
#include "../sleep/sleep.h"
#include "pio/ata_pio.h"
#include "pio/atapi_pio.h"
#include "dma/ata_dma.h"

#define ATA_MASTER 0
#define ATA_SLAVE 1

#define GLOBAL_ATA0_IO 0x1F0
#define GLOBAL_ATA0_CTRL 0x3F6
#define GLOBAL_ATA1_IO 0x170
#define GLOBAL_ATA1_CTRL 0x376

/* IO */

#define DATA_REG 0
#define ERR_REG 1
#define FT_REG 1 //Features register
#define SEC_CNT_REG 2 //Sector count register
#define LBA_LO 3 //lba low
#define LBA_MID 4 //lba middle
#define LBA_HI 5 //lba high
#define DRV_REG 6 //Drive register
#define STT_REG 7 //Status Register
#define CMD_REG 7 //Command Register

/* CTRL */

#define ALT_STT_REG 0 //Alternate status register
#define DEV_CTRL_REG 0 //Device Control register
#define DRV_ADDR_REG 1 //Drive Addres register

/* Status Register */
#define STT_ERR 0 //Error bit
#define STT_IDX 1 //Index bit (always 0)
#define STT_CORR 2 //Corrected Data bit (always 0)
#define STT_DRQ 3 //Data Request / in transfer bit
#define STT_SRV 4 //Overlapped mode service request
#define STT_DF 5 //Drive Fault
#define STT_RDY 6 //Device Ready
#define STT_BSY 7 //Device Busy

void init_ata(uint32 busmaster);

struct ata_identify_t
{
    uint16 GCBSI; //General Configuration bit-signidicant information
    uint16 obs0; //Obsolete
    uint16 Sconf; //Specific configuration
    uint16 obs1; //Obsolete
    uint16 ret0[2]; //retired
    uint16 obs2; //Obsolete
    uint16 res0; //Reserved by the CompatFlah(tm) Associaton
    uint16 ret1; //Obsolete
    string SerNum; //Serial Number
    uint16 ret2[2]; //Retired
    uint16 obs3; //obsolete
    string FirmRev; //Firmware Revision
    string ModNum; //Model number
    uint16 MaxSecxDRQ; //Maximum number of logical sectors that shall be tranferred per DRQ data block
    uint16 TCFSOP; //Truster computing feature set options
    uint16 Capabilities0;
    uint16 Capabilities1;
    uint16 obs4[2]; //Obsolete
    uint16 FFCS; //Free-fall control sensitivity
    uint16 obs5[5]; //Obsolete
    uint16 CurrSecxDRQ; //Current setting for number of logical sectors that shall be transferred per DRQ data block
    uint16 PIO28_AddressableSec0; //Amount of user addressable logical sectors(PIO 28) - Word 0
    uint16 PIO28_AddressableSec1; //Amount of user addressable logical sectors(PIO 28) - Word 1
    uint16 obs6; //Obsolete
    uint16 MDMASup; //Multiword DMA Support and current config
    uint16 PIOSup; //Pio modes supported
    uint16 MMDTC; //Minimum Multiword DMA transfer cycle time per word (ns)
    uint16 MRMDTC; //Manufacturer's recommended multiword dma transfer cycle time (ns)
    uint16 MPTCwoutFC; //Minimum PIO transfer cycle time Without Flow control (ns)
    uint16 MPTCwFC; //Minimum PIO transfer cycle time with IORDY Flow control (ns)
    uint16 res1[2]; //Reserved
    uint16 IDPD0; //Reserved for identify packet device
    uint16 IDPD1; //Reserved for identify packet device
    uint16 IDPD2; //Reserved for identify packet device
    uint16 IDPD3; //Reserved for identify packet device
    uint16 QDepth; //Maximum Queue Depth
    uint16 SATACap; //Sata Capabilities
    uint16 res2; //Reserved for SATA
    uint16 SATAFtSup; //SATA Features supported
    uint16 SATAFtEn; //Sata Features Enabled
    uint16 MajorRevNum; //Major revision number
    uint16 MinorRevNum; //Minor revision number
    uint16 CMDSetSup; //Command set supported
    uint16 CMDSetsSup; //Command sets supported
    uint16 CMDSet_FtSup; //Command Set / Feature supported
    uint16 CMDSet_FtEn0; //Command Set / Feature Enabled / Supported
    uint16 CMDSet_FtEn1; //Command Set / Feature Enabled / Supported
    uint16 CMDSet_FtEn2; //Command Set / Feature Enabled / Supported
    uint16 UDMASup; //Ultra DMA modes supported
    uint16 TSEUC; //Time requiered for Security Erase uint Completion
    uint16 TESEC; //Time requiered for Enchanced Security Erase Completion
    uint16 CAPMVal; //Current Advanced Power Management Val
    uint16 MPasswdID; //Master Password Identifier
    uint16 HRR; //Hardware Reset Result
    uint16 VRAMVal; //Vendor's recommended acoustic management value
    uint16 SMRS; //Stream Minimum Request Size
    uint16 STTD; //Streaming Transfer Time - DMA
    uint16 SAL; //Streaming Access Latency
    uint16 SPG0; //Streaming Performance Granularity
    uint16 SPG1; //Streaming Performance Granularity
    uint16 LBA48_AddressableSec0; //Amount of user addressable logical sectors(LBA 48) - Word 0
    uint16 LBA48_AddressableSec1; //Amount of user addressable logical sectors(LBA 48) - Word 1
    uint16 LBA48_AddressableSec2; //Amount of user addressable logical sectors(LBA 48) - Word 2
    uint16 LBA48_AddressableSec3; //Amount of user addressable logical sectors(LBA 48) - Word 3
    uint16 STTP; //Streaming Transfer Time - PIO
    uint16 res3; //Reserved
    uint16 SecSize; //Logical / Physical Sector size
    uint16 IsD; //Inter-seek delay for iso-7779 acousting testing (microsecs)
    uint16 NAA_IEEIDlo; //NAA(?) & IEEE(standard) OUI (universal identifier, only low on this variable)
    uint16 IEEODhi_UIDlo; //IEEE(standard) OUI (universal identifier, only high on this variable), Unique ID.
    uint16 UIDmid; // Unique ID
    uint16 UIDhi; // Unique ID
    uint16 res4[4]; //Reserved for world wide name extension to 128-bits
    uint16 res5; //Reserved for INCITS TR37-2004
    uint16 WxSec0; //Words per logical sector
    uint16 WxSec1; //Words per logical Sectior
    uint16 SupSet; //Supported Settings (cont from word 82-84)
    uint16 CMDSet_FtEn3; ////Command Set / Feature Enabled / Supported (cont from words 85-87)
    uint16 res6[8]; //Reserved for more settings
    uint16 obs12; //Obsolete
    uint16 SecuritySTT; //Security Status
    uint16 VendorSpecific[30];
    uint16 CFAPM1; //CFA Power mode 1
    uint16 res7[15]; //Reserved by the CompactFlash Association
    string CurrMedSerNum; //Current media serial number
    uint16 SCTCT; //SCT Command Transport
    uint16 res8[2]; //Reserved for CE-ATA
    uint16 LBlocksAlign; //Alignment of logical blocks within a larger physical block
    uint16 WRVSecCountM3_0; //Write-Read-Verify Sector Count Mode 3 only
    uint16 WRVSecCountM3_1; //Write-Read-Verify Sector Count Mode 3 only
    uint16 VSecCountM2_0; //Verify Sector Count Mode 2 only
    uint16 VSecCountM2_1; //Verify Sector Count Mode 2 only
    uint16 NVCacheCap; //NV Cache Capabilities
    uint16 NVCacheSizeLo; //NV Cache size in logical blocks (0:15)
    uint16 NVCacheSizeHi; //NV Cache Size in logical blocks (16:31)
    uint16 NMRR; //Nominal Media rotation rate
    uint16 NVCacheOp; //NV Cache Options
    uint16 WRVFtSetCurr; //Write-read-verify Feature set current mode
    uint16 res9;
    uint16 TMajRevNum; //Transport Major Revision Number
    uint16 TMinRevNum; //Transport Minor Revision Number
    uint16 res10[10]; //Reserved for CE-ATA
    uint16 MinNumSecxDownMicro; //Minimum number of 512byte blocks per download microcode command for mode 3
    uint16 MaxNumSecxDownMicro; //Maximum number of 512byte blocks per download microcode command for mode 3
    uint16 res11[19]; //Reserved
    uint16 IntegrityWord; //Checksum && Signature
} __attribute__((packed));

struct ata_identify_packet_t
{
    uint16 GCBSI; //General Configuration bit-signidicant information
    uint16 res0; //Reserved
    uint16 Sconf; //Specific
    uint16 res1[7]; //Reserved
    string SerNum; //Serial Number
    uint16 res2[3]; //Reserved
    string FirmRev; //Firmware Revision
    string ModNum; //Model number
    uint16 res3[2]; //Reserved
    uint16 Capabilities0;
    uint16 Capabilities1;
    uint16 obs0[2]; //Obsolete
    uint16 FRV; //Fields reported are valid (word 88 and 64:70)
    uint16 res4[8]; //Reserved
    uint16 DMASup0; //Dma modes supported
    uint16 DMASup1; //Same as above
    uint16 PIOSup; //PIO transfer modes supported
    uint16 MMDTC; //Minimum Multiword DMA transfer cycle time per word (ns)
    uint16 MRMDTC; //Manufacturer's recommended multiword dma transfer cycle time (ns)
    uint16 MPTCwoutFC; //Minimum PIO transfer cycle time Without Flow control (ns)
    uint16 MPTCwFC; //Minimum PIO transfer cycle time with IORDY Flow control (ns)
    uint16 res5[2]; //Reserved
    uint16 obs1[2]; //Obsolete
    uint16 res6[2]; //Reserved
    uint16 obs2; //obsolete
    uint16 res7[4]; //Reserved for SATA
    uint16 MajorRevNum; //Major revision number
    uint16 MinorRevNum; //Minor revision number
    uint16 CMDSet_FtSup0; //Command Set / Feature supported
    uint16 CMDSet_FtSup1; //Command Set / Feature supported
    uint16 CMDSet_FtSupExt; //Command Set / Feature supported extension
    uint16 CMDSet_FtEn0; //Command Set / Feature Enabled / Supported
    uint16 CMDSet_FtEn1; //Command Set / Feature Enabled / Supported
    uint16 CMDSet_FtEn2; //Command Set / Feature Enabled / Supported
    uint16 UDMASup; //Ultra DMA modes supported
    uint16 TSEUC; //Time requiered for Security Erase uint Completion
    uint16 TESEC; //Time requiered for Enchanced Security Erase Completion
    uint16 res8; //Reserved
    uint16 MPasswdID; //Master Password Identifier
    uint16 HRR; //Hardware Reset Result
    uint16 VRAMVal; //Vendor's recommended acoustic management value
    uint16 res9[13]; //Reserved
    uint16 NAA_IEEIDlo; //NAA(?) & IEEE(standard) OUI (universal identifier, only low on this variable)
    uint16 IEEODhi_UIDlo; //IEEE(standard) OUI (universal identifier, only high on this variable), Unique ID.
    uint16 UIDmid; // Unique ID
    uint16 UIDhi; // Unique ID
    uint16 res10[4]; //Reserved for world wide name extension to 128-bits
    uint16 res11[9]; //Reserved
    uint16 ATAPINullByteCnt; //ATAPI Behaviour when byte count == 0
    uint16 obs3[2]; //obsolete
    uint16 SecuritySTT; //Security Status
    uint16 VendorSpecific[30];
    uint16 res12[16]; //Reserved by CompactFlash
    uint16 res13[79]; //Reserved
    uint16 IntegrityWord; //Checksum && Signature
} __attribute__((packed));

struct ata_dev_t
{
    string type;
    uint8 channel;
    bool slave;
    bool LBA48; //Set if it supports LBA48 (if clear, it only supports PIO28)
    bool DMA; //Set if device supports DMA Based transfers
    uint64 size; //In MB
    uint16 io_base;
    uint16 ctrl_base;
    uint32 busmaster;
    uint32 prdt_addr; //Transfer Address
    uint64 IDENTIFY_addr; //Holds a pointer to the data recieved from the identify command sent at the ata controller init. If type = pata || sata, then the struct used is a ata_identify_t. else if type = patapi || satapi, then the struct used is ata_identify_packet_t. if type = unknown, the drive must not be used.
} __attribute__((packed));

struct ata_devices_t
{
    uint8 dev_amount;
    struct ata_dev_t devices[32*32+4]; //Each 32-drives per 32 SATA ports, and 4 of the PATA Drives
} __attribute__((packed));

struct ata_devices_t ata_devices;

struct ata_queue_element_t
{
    struct ata_queue_element_t *next;
    struct ata_dev_t *ata_device;
    uint16 *buffer;
    uint64 lba;
    uint16 sectors; //Amount of sectors (will be normally set to one)
    uint8 write; //0 = read, 1 = write
    uint8 ATAPI; //0 = ATA, 1 = ATAPI
    uint8 *completed; //Basically, set to one when command is completed. Set to zero otherwise
} __attribute__((packed));

struct ata_queue_t
{
    struct ata_queue_element_t *queue;
    int size; //Amount of elements in the queue
    uint64 first_element_addr; //Address of the first element in the queue
    uint64 last_element_addr; //Address of the last element in the queue
} __attribute__((packed));

bool ata_transfer_in_progress;

void ata_irq_handler(bool bus);
void ata_wait_irq(struct ata_dev_t *ata_device);
string ata_identify_word2ascii(uint16 *buf, uint8 start, uint8 end);
void ata28_prepare_command(struct ata_dev_t *ata_device, uint32 lba, uint16 sectors);
void ata48_prepare_command(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors);
void ata_read(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer, uint8 *completion_addr);
void ata_write(struct ata_dev_t *ata_device, uint64 lba, uint16 sectors, uint16 *buffer, uint8 *completion_addr);

#endif
