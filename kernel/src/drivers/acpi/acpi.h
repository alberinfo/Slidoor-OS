#ifndef ACPI_H
#define ACPI_H

#include "../../string/types.h"
#include "../../arch/x86/cpu.h"
#include "../../console/console.h"

struct GenericAddressStructure_t
{
  uint8 AddressSpace;
  uint8 BitWidth;
  uint8 BitOffset;
  uint8 AccessSize;
  uint64 Address;
} __attribute__((packed));

struct ACPI_SDTHeader_t
{
  char Signature[4];
  uint32 length;
  uint8 Revision;
  uint8 Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32 OEMRevision;
  uint32 CreatorID;
  uint32 CreatorRevision;
} __attribute__((packed));

struct ACPI_Sx_t
{
    uint16 SLPYPa;
    uint16 SLPYPb;
} __attribute__((packed));


struct acpi_pm_info_t
{
    uint8 Revision;
    uint32 cpus;
    struct FACP *facp;
    struct MADT *madt;
    struct HPET *hpet;
    struct LAPIC **lapic;
    struct IOAPIC **ioapic;
    struct LAPIC_OVERRIDE *lapic_override;
    uint16 SLP_EN;
    uint16 SCI_EN;
    struct ACPI_Sx_t ACPI_S5;
    struct ACPI_Sx_t ACPI_S4;
    struct ACPI_Sx_t ACPI_S3;
    struct ACPI_Sx_t ACPI_S2;
    struct ACPI_Sx_t ACPI_S1;
    struct ACPI_Sx_t ACPI_S0;
} __attribute__((packed));

struct acpi_pm_info_t *acpi_pm_info;

int acpiEnable(void);
int initAcpi(void);
void AcpiSCIHandler(void);
void acpiReboot(void);
void acpiPowerOff(void);

//NOTE: These are declared here, bc if not gcc will throw an "incomplete type" error when compiling
#include "interpreter/namespace.h"
#include "interpreter/opcode.h"
#include "../hpet/hpet.h"
#include "madt.h"
#include "fadt.h"
#include "rsdt.h"
#include "dsdt.h"
#include "../pcie/pcie.h"

#endif
