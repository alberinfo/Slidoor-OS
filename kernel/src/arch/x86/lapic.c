#include "lapic.h"

extern void _ap_entry();
extern void _ap_pmode_trampoline();
extern int _ap_GDT32Pointer;

/*                                                   */
/**************** Register Definition ****************/
/*                                                   */

#define LAPIC_ID_REG 0x20
#define LAPIC_VER_REG 0x30//Version
#define LAPIC_TPR 0x80//Task priority reg
#define LAPIC_APR 0x90//Arbitration priority reg
#define LAPIC_PPR 0xA0//Processor priority reg
#define LAPIC_EOI 0xB0//End of interrupt reg
#define LAPIC_RRD 0xC0//Remote read reg
#define LAPIC_LDR 0xD0//Logical destination reg
#define LAPIC_DFR 0xE0//Destination format reg
#define LAPIC_SIVR 0xF0//Spurious interrupt vector reg
#define LAPIC_ISR 0x100//In-service reg
#define LAPIC_TMR 0x180//Trigger mode reg
#define LAPIC_IRR 0x200//Interrupt request reg
#define LAPIC_ESR 0x280//Error status reg
#define LAPIC_CMCI 0x2F0//Corrected machine check interrupt reg
#define LAPIC_LICR 0x300//(low)Interrupt command reg
#define LAPIC_HICR 0x310//(high)Interrupt command reg
#define LAPIC_TRR 0x320//Timer reg
#define LAPIC_TSR 0x330//Thermal sensor reg
#define LAPIC_PMCR 0x340//Performance monitoring counters reg
#define LAPIC_LINT0 0x350//Local interrupt (type)0 //ExtINT
#define LAPIC_LINT1 0x360//Local interrupt (type)1 //NMI
#define LAPIC_ERR 0x370//Error reg
#define LAPIC_TICR 0x380//Timer's initial count reg
#define LAPIC_TCCR 0x390//Timer's current count reg
#define LAPIC_TDCR 0x3E0//Timer's divider config reg
#define LAPIC_INIT_IPI 5//Init IPI, bit 14 in ICR must be set, and bit 15 in ICR must be clear
#define LAPIC_INITD_IPI 5//Init IPI Deassert, bit 14 in ICR must be clear, and bit 15 in ICR must be set
#define LAPIC_SIPI 6//Startup IPI

/*                                     */
/**************** xApic ****************/
/*                                     */

uint32 lapicGetBase(void)
{
    uint32 a, b;
    rdmsr(0x1B, &a, &b); //0x1B is the msr address
    return (a & ~(0xFFF)) | ((b & 0xF) << 32);
}

void lapicSetBase(uint32 base)
{
    //Base should in theory have the enable bit (11th) set
    uint32 b = (base >> 32) & 0xF;
    wrmsr(0x1B, base, b);
}

uint32 xApicReadReg(uint16 reg)
{
    return *(volatile uint32*)(lapicGetBase() + reg);
}

void xApicWriteReg(uint16 reg, uint32 val)
{
    *(volatile uint32*)(lapicGetBase() + reg) = val;
    return;
}

/*                                      */
/**************** x2Apic ****************/
/*                                      */

bool x2ApicEnabled = false;

uint64 x2ApicReadReg(uint32 reg)
{
    uint32 high, low;
    rdmsr(0x800 + reg / 16, &low, &high);
    return (high << 32) | low;
}

void x2ApicWriteReg(uint32 reg, uint64 val)
{
    wrmsr(0x800 + reg / 16, val & 0xFFFFFFFF, val >> 32); //They must be inverted...
    return;
}

uint64 lapicReadReg(uint32 reg)
{
    if(!x2ApicEnabled)
    {
        return xApicReadReg(reg);
    } else {
        return x2ApicReadReg(reg);
    }
}

void lapicWriteReg(uint32 reg, uint64 val)
{
    if(!x2ApicEnabled)
    {
        uint32 low = val & 0xFFFFFFFF; //Sanity
        xApicWriteReg(reg, low);
    } else {
        x2ApicWriteReg(reg, val);
    }
}

void lapicSendEOI(void)
{
    if(!x2ApicEnabled)
    {
        xApicWriteReg(LAPIC_EOI, 0);
    } else {
        x2ApicWriteReg(LAPIC_EOI, 0);
    }
    return;
}

void lapicEnable(uint32 flags)
{
    if(flags & 1) PIC_Unmap();
    uint32 ecx, unused;
    cpuid(1, unused, unused, ecx, unused);
    if(ecx & (1 << 21))
    {
        x2ApicEnabled = true;
        lapicSetBase(lapicGetBase() | 0xD00);
    } else {
        x2ApicEnabled = false;
        lapicSetBase(lapicGetBase() | 0x900);
    }
    lapicWriteReg(LAPIC_SIVR, lapicReadReg(LAPIC_SIVR) | 0x1FF); //Spurious interrupt
    lapicWriteReg(LAPIC_TRR, 0x10000); //LVT Timer register
    lapicWriteReg(LAPIC_PMCR, 0x10000); //Performance counter
    lapicWriteReg(LAPIC_ERR, 0); //Clear error reg
    lapicWriteReg(LAPIC_ERR, 0); //Back to back!
    lapicSendEOI(); //EOI If any interrupt has not been ack'ed
    if(flags != 0) //Only if not BSP
    {
        lapicWriteReg(LAPIC_LINT0, 0x700); //Lint0
        lapicWriteReg(LAPIC_LINT1, 0x400); //Lint1
    }
    lapicWriteReg(LAPIC_TPR, 0); //Task priority register
    return;
}

void lapicConfigureNMI(uint8 lint, uint16 flags)
{
    if(lint == 0)
    {
        lapicWriteReg(LAPIC_LINT0, (flags << 12) | (4 << 8));
    } else {
        lapicWriteReg(LAPIC_LINT1, (flags << 12) | (4 << 8));
    }
}

void lapicIPI(uint32 apicID, uint32 value)
{
    if(!x2ApicEnabled)
    {
        lapicWriteReg(LAPIC_HICR, apicID << 24);
        lapicWriteReg(LAPIC_LICR, value);
    } else {
        lapicWriteReg(LAPIC_LICR, ((uint64)apicID << 32) | value); //With x2Apic, we'll always use logical destination
    }
}

void APWakeup(uint32 apicID, uint32 StartAddr) //We'll make an INIT-SIPI-SIPI Sequence.
{
    volatile bool *check_start = 0x500;
    volatile bool *fully_started = 0x501;
    *check_start = false;
    lapicIPI(apicID, LAPIC_INIT_IPI << 8 | (1 << 14)); //Init
    lapicIPI(apicID, LAPIC_INITD_IPI << 8 | (1 << 15)); //Init-Deassert
    sleep(10, SleepMili);//milisecs
    if(lapicReadReg(LAPIC_LICR) & (1 << 12))
    {
        printf("\nCPU With Apic ID %x failed to init.\n", apicID);
        return;
    }
    lapicIPI(apicID, (StartAddr / 0x1000) | LAPIC_SIPI << 8 | (1 << 14) | (1 << 15)); //Startup
    sleep(2, SleepMili);//milisecs
    if(*check_start == false)
    {
        lapicIPI(apicID, (StartAddr / 0x1000) | LAPIC_SIPI << 8 | (1 << 14) | (1 << 15)); //Startup
        sleep(2, SleepMili);
        if(*check_start == false)
        {
            printf("[");
            printcolor("PANIC", 0, 0xFFE00000); //red
            printf("] CPU%i failed to start\n", apicID);
        }
    }
    if(*check_start == false) return;
    while(!(*fully_started));
    *fully_started = 0;
}

void SMP_Start(void) //Start all AP's (if any)
{
    if(acpi_pm_info->cpus > 1)
    {
        id_vmmap(0x1000, 0x5000, 3);
        memcpy_fast(0x1000, &_ap_GDT32Pointer, 8);
        memcpy_fast(0x2000, &_ap_pmode_trampoline, 32);
        memcpy_fast(0x3000, &_ap_entry, 24); //Put the initialization code at a lower address
        for(int i = 1; i < acpi_pm_info->cpus; i++)
        {
            if((acpi_pm_info->lapic[i]->flags & 1) == 0) continue;
            uint64 Stack_Addr = kmalloc(0x20000);
            memcpy_fast(0x4000, &Stack_Addr, 8);
            APWakeup(acpi_pm_info->lapic[i]->apic_id, 0x3000); //Init AP
        }
    }
}

/*                                           */
/**************** Timer stuff ****************/
/*                                           */

uint32 timetillnext = 0;
uint32 tickRate = 0;

void lapicTimerStart(void)
{
    lapicWriteReg(LAPIC_TDCR, 3); //Lapic timer's divisor, set to 16
    lapicWriteReg(LAPIC_TICR, 0xFFFFFFFF); //Lapic timer's init count, set to 0xFFFFFFFF
    lapicWriteReg(LAPIC_TRR, 0x20000); //unmask lapic's timer
    sleep(1, SleepMili);
    lapicWriteReg(LAPIC_TRR, 0x10000); //mask lapic's timer
    timetillnext = 0xFFFFFFFF - (lapicReadReg(LAPIC_TCCR) & 0xFFFFFFFF); //Current count, calculate the amount of ticks passed
    tickRate = 1000000 / (timetillnext/*timetillnext is 1ms*/); //In ns
    lapicWriteReg(LAPIC_TDCR, 3); //Lapic timer's divisor, set to 16
    lapicWriteReg(LAPIC_TICR, timetillnext); //Initial count;
    lapicWriteReg(LAPIC_TRR, 34 | 0x20000); //unmask timer and put it on periodic mode
    lapicSendEOI();
    ChangeTimer("APIC");
}

bool lapic_sleeping = false;
uint32 lapic_countdown = 0;

void lapicTimerHandler(void)
{
    if(lapic_sleeping)
    {
        if(lapic_countdown)
        {
            if(lapic_countdown < tickRate)
            {
                lapic_countdown = 0;
                lapic_sleeping = false;
            } else {
                lapic_countdown-=tickRate;
            }
        } else {
            lapic_sleeping = false;
        }
    }
    return;
}

void lapicTimerSleep(uint32 time, uint8 type)
{
    return;
    //The best i can say is, PLEASE DONT USE THIS SHIT
    lapic_countdown = time;
    lapic_sleeping = true;
    while(lapic_sleeping) asm volatile("hlt"); //Halt CPU until next interrupt arrives
    return;
}
