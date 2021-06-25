#include "setup.h"

void dosetup(uint64 mboot_addr, uint64 kernel_end)
{
    PIC_Map();
    SetIsr();
    SetIrq();
    SetLapicSpuriousIrq();
    idtInit();
    heapInit(32);
    parseMultiboot(mboot_addr, kernel_end);
    VesaInit();
    ConsoleInit();
    printf("[ ");
    printcolor("OK", 0, 0x1FFC00);
    printf(" ] IDT Set-UP - Done!\n");
    printf("[ ");
    printcolor("OK", 0, 0x1FFC00);
    printf(" ] PMM Set-UP - Done!\n");
    printf("[ ");
    printcolor("OK", 0,0x1FFC00);
    printf(" ] Multiboot Parsing - Done!\n");
    pitInit(1000); //hz
    int AcpiStatus = initAcpi();
    if(!AcpiStatus)
    {
        printf("[ ");
        printcolor("OK", 0, 0x1FFC00);
        printf(" ] ACPI Enabling - Done!\n");
    } else {
        printf("[ ");
        printcolor("PANIC", 0, 0xFFE00000);
        printf(" ] Can't use ACPI! - Continuing...\n");
    }
    detectCpu();
    PciInit();
    printf("[ ");
    printcolor("OK", 0, 0x1FFC00);
    printf(" ] PCI Bus Init - Done!\n");
    if(!AcpiStatus) SMP_Start();
}