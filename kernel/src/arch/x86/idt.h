#ifndef IDT_H
#define IDT_H

#include "../../string/types.h"

typedef struct idt_entry
{
    uint16 offset_1;
    uint16 selector;
    uint8 ist;
    uint8 type_attr;
    uint16 offset_2;
    uint32 offset_3;
    uint32 zero;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr
{
    uint16 limit;
    idt_entry_t *base;
} __attribute__((packed)) idt_ptr_t;

extern int isr0();
extern int isr1();
extern int isr2();
extern int isr3();
extern int isr4();
extern int isr5();
extern int isr6();
extern int isr7();
extern int isr8();
extern int isr9();
extern int isr10();
extern int isr11();
extern int isr12();
extern int isr13();
extern int isr14();
extern int isr15();
extern int isr16();
extern int isr17();
extern int isr18();
extern int isr19();
extern int isr20();
extern int isr21();
extern int isr22();
extern int isr23();
extern int isr24();
extern int isr25();
extern int isr26();
extern int isr27();
extern int isr28();
extern int isr29();
extern int isr30();
extern int isr31();

extern int irq0();
extern int irq1();
extern int irq2();
extern int irq3();
extern int irq4();
extern int irq5();
extern int irq6();
extern int irq7();
extern int irq8();
extern int irq9();
extern int irq10();
extern int irq11();
extern int irq12();
extern int irq13();
extern int irq14();
extern int irq15();

void PIC_Map(void);
void PIC_Unmap(void);
void idtSetGate(int gate, uint64 base, uint16 selector, uint8 type);
void SetIsr(void);
void SetIrq(void);
void SetLapicSpuriousIrq(void);
void idtInit(void);

#endif
