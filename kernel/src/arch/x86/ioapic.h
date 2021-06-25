#ifndef IOAPIC_H
#define IOAPIC_H

#include "../../string/types.h"
#include "../../drivers/acpi/acpi.h"
#include "lapic.h"

void ioapicEnable(uint32 address, uint8 cpu);
void ioapicDisable(void);
void IOApicConfigureNMI(uint8 irq, uint8 flags);
void ioapicMapIrq(uint32 irq_src, uint32 irq_dst, uint8 cpu);

#endif
