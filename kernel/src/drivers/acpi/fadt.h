#ifndef FADT_H
#define FADT_H

#include "acpi.h"

struct FACP
{
    struct ACPI_SDTHeader_t h;
    uint32 FirmwareCtrl;
    uint32 DSDT;
 
    // field used in ACPI 1.0; no longer in use, for compatibility only
    uint8  Reserved;
 
    uint8  PreferredPowerManagementProfile;
    uint16 SCI_Interrupt;
    uint32 SMI_CommandPort;
    uint8  AcpiEnable;
    uint8  AcpiDisable;
    uint8  S4BIOS_REQ;
    uint8  PSTATE_Control;
    uint32 PM1aEventBlock;
    uint32 PM1bEventBlock;
    uint32 PM1aControlBlock;
    uint32 PM1bControlBlock;
    uint32 PM2ControlBlock;
    uint32 PMTimerBlock;
    uint32 GPE0Block;
    uint32 GPE1Block;
    uint8  PM1EventLength;
    uint8  PM1ControlLength;
    uint8  PM2ControlLength;
    uint8  PMTimerLength;
    uint8  GPE0Length;
    uint8  GPE1Length;
    uint8  GPE1Base;
    uint8  CStateControl;
    uint16 WorstC2Latency;
    uint16 WorstC3Latency;
    uint16 FlushSize;
    uint16 FlushStride;
    uint8  DutyOffset;
    uint8  DutyWidth;
    uint8  DayAlarm;
    uint8  MonthAlarm;
    uint8  Century;
 
    // reserved in ACPI 1.0; used since ACPI 2.0+
    uint16 BootArchitectureFlags;
 
    uint8  Reserved2;
    uint32 Flags;

    // 12 byte structure; see below for details
    struct GenericAddressStructure_t ResetReg;
 
    uint8  ResetValue;
    uint8  Reserved3[3];
 
    // 64bit pointers - Available on ACPI 2.0+
    uint64  X_FirmwareControl;
    uint64  X_Dsdt;
 
    struct GenericAddressStructure_t X_PM1aEventBlock;
    struct GenericAddressStructure_t X_PM1bEventBlock;
    struct GenericAddressStructure_t X_PM1aControlBlock;
    struct GenericAddressStructure_t X_PM1bControlBlock;
    struct GenericAddressStructure_t X_PM2ControlBlock;
    struct GenericAddressStructure_t X_PMTimerBlock;
    struct GenericAddressStructure_t X_GPE0Block;
    struct GenericAddressStructure_t X_GPE1Block;
} __attribute__((packed));

bool acpiParseFacp(uint32 *ptr);

#endif