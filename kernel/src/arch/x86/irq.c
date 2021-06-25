#include "irq.h"

bool isapicenabled = false;

void SetApicIRQ(bool val)
{
    isapicenabled = val;
}

void lapic_spurious()
{
    lapicSendEOI();
    return;
}

void irq0_handler()
{
    if(memcmp(getUsedTimer(),"PIT",3) == 0)
    {
        pitHandler();
    } else if(memcmp(getUsedTimer(),"APIC", 4) == 0){
        lapicTimerHandler();
    } else if(memcmp(getUsedTimer(),"HPET",4) == 0) {
        HpetHandler();
    }
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq1_handler()
{
    kbd_handler();
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq2_handler()
{
    if(memcmp(getUsedTimer(),"PIT",3) == 0)
    {
        pitHandler();
    } else if(memcmp(getUsedTimer(),"APIC", 4) == 0){
        lapicTimerHandler();
    } else if(memcmp(getUsedTimer(),"HPET", 4) == 0) {
        HpetHandler();
    }
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq3_handler()
{
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq4_handler()
{
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq5_handler()
{
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq6_handler()
{
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq7_handler()
{
    if(!isapicenabled)
    {
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq8_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq9_handler()
{
    AcpiSCIHandler();
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq10_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq11_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq12_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq13_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq14_handler()
{
    ata_irq_handler(0); //ATA Bus 0
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    return;
}

void irq15_handler()
{
    if(!isapicenabled)
    {
        outportb(0xA0, 0x20);
        outportb(0x20, 0x20);
    } else {
        lapicSendEOI();
    }
    ata_irq_handler(1); //ATA Bus 1
    return;
}
