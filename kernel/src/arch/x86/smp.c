#include "smp.h"

void _ap_main()
{
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    idtInit(); //Idt has already been configured
    lapicEnable(0);
    printf("[INFO] CPU%i startup - Done!\n",(ebx & 0xFF000000) >> 24);
    volatile bool *fully_started = 0x501;
    *fully_started = true;
    while(1) //In case of an NMI / isr
    {
        asm("hlt");
    }
}
