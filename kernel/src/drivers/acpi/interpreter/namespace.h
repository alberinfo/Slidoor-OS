#ifndef ACPI_NAMESPACE_H
#define ACPI_NAMESPACE_H

#include "../../../string/types.h"
#include "../../../string/string.h"
#include "../../../memory/pmm.h"
#include "../../../console/console.h"
#include "../acpi.h"
#include "opcode.h"
#include "eval.h"

struct AcpiNamespaceBlock_t
{
	uint16 child_amount;
	uint64 *child; //We can have more than one child, and we save a pointer for each one
	uint64 *parent;
	string name; //i.e PCI0
	string full_name; //i.e _SB_.PCI0
	uint16 type; //Most likely a packet, method, scope, data or device. Well use the normal PacketOp, MethodOp etc for codes.
	uint64 size;
	uint8 *addr; //Where Acpi Machine code is located (probably DSDT or SSDT, and since it is reserved memory, there's no need to allocate memory and memcpy the AML)
} __attribute__((packed));

void AcpiInitNamespace(void); //Create the root.

void *AcpiWalkNamespace(string destination); //Destination is what we're searching. This will return a pointer what we were searching
void AcpiCreateNamespaceBlock(string parent, struct AcpiNamespaceBlock_t *block); //Self explaining
void AcpiDeleteNamespaceBlock(string node); //self explanatory

void AcpiDumpNamespace(void);
uint8 *AcpiGetAml(void);

#endif