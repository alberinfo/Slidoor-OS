#ifndef HPET_H
#define HPET_H

#include "../acpi/acpi.h"

struct HPET
{
	struct ACPI_SDTHeader_t h;
	uint8 HwRevID; //Hardware revision id
	uint8 ComparatorCount : 5;
	uint8 CounterSize : 1;
	uint8 reserved : 1;
	uint8 LegacyReplacement : 1;
	uint16 PciVendorID;
	struct GenericAddressStructure_t Address;
	uint8 HpetNumber;
	uint16 MinimumTick; //Periodic mode only
	uint8 PageProtection;
} __attribute__((packed));

void acpiParseHpet(uint32 *ptr);
void HpetHandler();
void HpetSleep(uint64 Time, uint8 type);

#endif
