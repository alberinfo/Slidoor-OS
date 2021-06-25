#include "energy.h"

void reboot()
{
    ioapicDisable(); //We may have situations in which the IOAPIC is not set to masked, thus causing faults
    acpiReboot();
    uint8 check = 0;
    do
    {
        check = inportb(0x64);
        if(check & 1)
        {
            inportb(0x60);
            continue;
        }
    } while(check & (1 << 1));
    outportb(0x64, 0xFE);

    outportb(0x70, 0x8F);
    outportb(0x71, 0x00);
    outportb(0x70, 0x00);
    outportb(0x92, inportb(0x92) | 1);
    printf("[ ");
    printcolor("PANIC", 0, 0xFFE00000);
    printf(" ] Couldn't reboot the computer. System Halted.\n");
    asm("cli;hlt");
}

void shutdown()
{
    acpiPowerOff();
    printf("[ ");
    printcolor("PANIC", 0, 0xFFE00000);
    printf(" ] ACPI Shutdown failed! System Halted.\n");
    asm("cli;hlt");
}
