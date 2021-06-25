#ifndef MADT_H
#define MADT_H

#include "acpi.h"
#include "../../arch/x86/lapic.h"
#include "../../arch/x86/ioapic.h"

struct MADT
{
    char Signature[4];
    uint32 Length;
    uint8 revision;
    uint8 checksum;
    char OEMID[6];
    char OEMable_id[8];
    uint32 OEMRevision;
    uint32 CreatorID;
    uint32 CreatorREV;
    uint32 local_controller_addr;
    uint32 flags;
    uint8 rest_fields;
}__attribute__((packed));

struct LAPIC
{
    uint8 type;
    uint8 length;
    uint8 processor_id;
    uint8 apic_id;
    uint32 flags;
} __attribute__((packed));

struct IOAPIC
{
    uint8 type;
    uint8 length;
    uint8 ioapic_id;
    uint8 reserved;
    uint32 address;
    uint32 global_sib; //System interrupt base
} __attribute__((packed));

struct APIC_ISO //Interrupt source override
{
    uint8 type;
    uint8 length;
    uint8 bus_src;
    uint8 irq_src;
    uint32 interrupt;
    uint16 flags;
} __attribute__((packed));

struct IOAPIC_NMI
{
    uint8 type;
    uint8 length;
    uint8 flags;
    uint8 GSI; //Global_System_Interrupt
} __attribute__((packed));

struct LAPIC_NMI
{
    uint8 type;
    uint8 length;
    uint8 processor_id;
    uint8 flags;
    uint8 lint;
} __attribute__((packed));

struct LAPIC_OVERRIDE
{
    uint8 type;
    uint8 length;
    uint16 reserved;
    uint64 addr;
} __attribute__((packed));

void acpiParseMadt(uint32 *ptr);

#endif