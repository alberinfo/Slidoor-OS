#include "idt.h"
#include "irq.h"

idt_entry_t idt[256] __attribute__((section(".bss")));
idt_ptr_t idt_ptr __attribute__((section(".bss")));
idt_entry_t idt_smp[256] __attribute__((section(".bss")));
idt_ptr_t idt_ptr_smp __attribute__((section(".bss")));

void PIC_Mask(uint32 line)
{
    uint16 port = 0;
    uint8 val = 0;
    if(line < 8)
    {
        port = 0x21;
    } else {
        port = 0xA1;
        line -= 8;
    }
    val = inportb(port) | (1 << line);
    outportb(port, val);
}

void PIC_Unmask(uint32 line)
{
    uint16 port = 0;
    uint8 val = 0;
    if(line < 8)
    {
        port = 0x21;
    } else {
        port = 0xA1;
        line -= 8;
    }
    val = inportb(port) & ~(1 << line);
    outportb(port, val);
}

void PIC_Map(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x20);
    outportb(0x21, 4);
    outportb(0xA1, 2);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0);
    outportb(0xA1, 0);
    return;
}

void PIC_Unmap(void)
{
    outportb(0xA1, 0xFF);
    outportb(0x21, 0xFF);
    return;
}

void SetIsr(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1; //Since this function is supposed to be the first one called when setting up the idt, we will configure the descriptor right here
    idt_ptr.base = &idt;
    memset(&idt, 0, sizeof(idt_entry_t)*256);

    idtSetGate(0, (uint64)&isr0, 0x08, 0x8E);
    idtSetGate(1, (uint64)&isr1, 0x08, 0x8E);
    idtSetGate(2, (uint64)&isr2, 0x08, 0x8E);
    idtSetGate(3, (uint64)&isr3, 0x08, 0x8E);
    idtSetGate(4, (uint64)&isr4, 0x08, 0x8E);
    idtSetGate(5, (uint64)&isr5, 0x08, 0x8E);
    idtSetGate(6, (uint64)&isr6, 0x08, 0x8E);
    idtSetGate(7, (uint64)&isr7, 0x08, 0x8E);
    idtSetGate(8, (uint64)&isr8, 0x08, 0x8E);
    idtSetGate(9, (uint64)&isr9, 0x08, 0x8E);
    idtSetGate(10, (uint64)&isr10, 0x08, 0x8E);
    idtSetGate(11, (uint64)&isr11, 0x08, 0x8E);
    idtSetGate(12, (uint64)&isr12, 0x08, 0x8E);
    idtSetGate(13, (uint64)&isr13, 0x08, 0x8E);
    idtSetGate(14, (uint64)&isr14, 0x08, 0x8E);
    idtSetGate(15, (uint64)&isr15, 0x08, 0x8E);
    idtSetGate(16, (uint64)&isr16, 0x08, 0x8E);
    idtSetGate(17, (uint64)&isr17, 0x08, 0x8E);
    idtSetGate(18, (uint64)&isr18, 0x08, 0x8E);
    idtSetGate(19, (uint64)&isr19, 0x08, 0x8E);
    idtSetGate(20, (uint64)&isr20, 0x08, 0x8E);
    idtSetGate(21, (uint64)&isr21, 0x08, 0x8E);
    idtSetGate(22, (uint64)&isr22, 0x08, 0x8E);
    idtSetGate(23, (uint64)&isr23, 0x08, 0x8E);
    idtSetGate(24, (uint64)&isr24, 0x08, 0x8E);
    idtSetGate(25, (uint64)&isr25, 0x08, 0x8E);
    idtSetGate(26, (uint64)&isr26, 0x08, 0x8E);
    idtSetGate(27, (uint64)&isr27, 0x08, 0x8E);
    idtSetGate(28, (uint64)&isr28, 0x08, 0x8E);
    idtSetGate(29, (uint64)&isr29, 0x08, 0x8E);
    idtSetGate(30, (uint64)&isr30, 0x08, 0x8E);
    idtSetGate(31, (uint64)&isr31, 0x08, 0x8E);
}

void SetIrq(void)
{
    idtSetGate(32, (uint64)&irq0, 0x08, 0x8E);
    idtSetGate(33, (uint64)&irq1, 0x08, 0x8E);
    idtSetGate(34, (uint64)&irq2, 0x08, 0x8E);
    idtSetGate(35, (uint64)&irq3, 0x08, 0x8E);
    idtSetGate(36, (uint64)&irq4, 0x08, 0x8E);
    idtSetGate(37, (uint64)&irq5, 0x08, 0x8E);
    idtSetGate(38, (uint64)&irq6, 0x08, 0x8E);
    idtSetGate(39, (uint64)&irq7, 0x08, 0x8E);
    idtSetGate(40, (uint64)&irq8, 0x08, 0x8E);
    idtSetGate(41, (uint64)&irq9, 0x08, 0x8E);
    idtSetGate(42, (uint64)&irq10, 0x08, 0x8E);
    idtSetGate(43, (uint64)&irq11, 0x08, 0x8E);
    idtSetGate(44, (uint64)&irq12, 0x08, 0x8E);
    idtSetGate(45, (uint64)&irq13, 0x08, 0x8E);
    idtSetGate(46, (uint64)&irq14, 0x08, 0x8E);
    idtSetGate(47, (uint64)&irq15, 0x08, 0x8E);
}

void SetLapicSpuriousIrq(void)
{
    idtSetGate(255, (uint64)&lapic_spurious, 0x08, 0x8E);
}

void idtInit(void)
{
    asm volatile("lidt %0" :: "m"(idt_ptr));
    asm volatile("sti");
}

void idtSetGate(int gate, uint64 base, uint16 selector, uint8 type)
{
    idt[gate].offset_1 = base;
    idt[gate].selector = selector;
    idt[gate].zero = 0;
    idt[gate].ist = 0;
    idt[gate].type_attr = type;
    idt[gate].offset_2 = base >> 16;
    idt[gate].offset_3 = base >> 32;
}
