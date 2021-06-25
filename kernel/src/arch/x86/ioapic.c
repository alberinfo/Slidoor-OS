#include "ioapic.h"

uint32 IoApicAddress = 0;

uint32 ReadIoApic(uint32 reg)
{
    uint32 volatile *ioapic = (uint32 volatile*)IoApicAddress;
    ioapic[0] = (reg & 0xFF);
    return ioapic[4];
}

void WriteIoApic(uint32 reg, uint32 val)
{
    uint32 volatile *ioapic = (uint32 volatile*)IoApicAddress;
    ioapic[0] = (reg & 0xFF);
    ioapic[4] = val;
}

void ioapicEnable(uint32 addr, uint8 cpu)
{
    IoApicAddress = addr;
    for(int i = 0; i < 24; i++)
    {
        WriteIoApic(0x10 + i * 2, 0x20 + i); //Enable all interrupts
        WriteIoApic(0x10 + i * 2 + 1, cpu << 24);
    }
    SetApicIRQ(true);
    lapicSendEOI();
    asm volatile("sti");
}

void ioapicDisable()
{
    for(int i = 0; i < 24; i++) WriteIoApic(0x10 + i * 2, 1 << 16);
    SetApicIRQ(false);
    return;
}

void ioapicMapIrq(uint32 irq_src, uint32 irq_dst, uint8 cpu)
{
    WriteIoApic(0x10 + irq_src * 2, 0x20 + irq_dst);
    WriteIoApic(0x10 + irq_src * 2 + 1, 0);
}

void ioapicMaskIrq(uint32 irq)
{
    if(IoApicAddress == 0)
    {
        PIC_Mask(irq);
        return;
    }
    WriteIoApic(0x10 + irq * 2, 1 << 16); //mask
}

void IOApicConfigureNMI(uint8 irq, uint8 flags)
{
    WriteIoApic(0x10 + irq * 2, (0x20 + irq) | (4 << 8) | (flags << 12));
    WriteIoApic(0x10 + irq * 2 + 1, 0);
}
