#ifndef RSDP_H
#define RSDP_H 

#include "acpi.h"

struct RSDP
{
    uint8 Signature[8];
    uint8 CheckSum;
    uint8 OemID[6];
    uint8 Revision;
    uint32 RsdtAddress;
} __attribute__((packed));

struct RSDP2
{
    struct RSDP RSDP1;
    uint32 length;
    uint64 XsdtAddress;
    uint8 ExtendedChecksum;
    uint8 reserved[3];
} __attribute__((packed));


uint32 *acpiCheckRSDPtr(uint32 *ptr);
uint32 *acpiGetRSDPtr(void);

#endif