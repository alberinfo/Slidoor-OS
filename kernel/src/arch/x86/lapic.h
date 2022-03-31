#ifndef LAPIC_H
#define LAPIC_H

#include "../../console/console.h"
#include "../../string/types.h"
#include "cpu.h"
#include "../../drivers/acpi/acpi.h"
#include "ioapic.h"
#include "../../drivers/sleep/sleep.h"

void lapicEnable(uint32 flags);
void lapicConfigureNMI(uint8 lint, uint16 flags);
void lapicIPI(uint32 apicID, uint32 value);
void APWakeup(uint32 apicID, uint32 StartAddr);
void SMP_Start(void);
void lapicTimerStart(void);
void lapicTimerHandler(void);
void lapicTimerSleep(uint32 time, uint8 type);
void lapicSendEOI(void);

#endif
