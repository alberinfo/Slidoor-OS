#ifndef PCIe_H
#define PCIe_H

#include "../acpi/acpi.h"
#include "../pci/pci.h"

struct MCFG
{
	struct ACPI_SDTHeader_t h;
	//Aaaaaaaaaaaaaaaand here would be the BAR's for each enchanced access mechanism\
	but, were going to use the ptr + x to calculate the address, and then access the data. LOL
} __attribute__((packed));

struct ENCHANCED_CONFIG_BAR_t
{
	uint64 BAR;
	uint16 PCISegNum; //PCI Segment group number
	uint8 StartPCIBusNum; //Start pci bus number decoded by this host bridge
	uint8 EndPCIBusNum; //End pci bus number decoded by this host bridge
	uint32 reserved;
} __attribute__((packed));

void acpiParsePCIe(uint32 *ptr);

#endif