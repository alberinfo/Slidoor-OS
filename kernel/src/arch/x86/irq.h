#ifndef IRQ_H
#define IRQ_H

#include "../../string/types.h"
#include "../../drivers/kb/kb.h"
#include "../../drivers/pit/pit.h"
#include "../../drivers/sleep/sleep.h"
#include "../../drivers/ata/ata.h"
#include "lapic.h"

void lapic_spurious();
void irq0_handler();
void irq1_handler();
void irq3_handler();
void irq4_handler();
void irq5_handler();
void irq6_handler();
void irq7_handler();
void irq8_handler();
void irq9_handler();
void irq10_handler();
void irq11_handler();
void irq12_handler();
void irq13_handler();
void irq14_handler();
void irq15_handler();

#endif
