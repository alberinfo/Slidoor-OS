#include "isr.h"

char *exception_msg[32] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "Device not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown interrupt",
    "x87 FPU Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD FPU Fault",
    "Virtualization Fault",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Secutiry Fault",
    "Reserved",
};

void isr0_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[0]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[0], 0, 0xFFE00000);;
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr1_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[1]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    print("CPU");
    print(base_convert(apicID, 10));
    print(" - ");
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[1], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr2_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[2]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[2], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr3_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[3]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[3], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr4_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[4]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[4], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr5_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[5]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[5], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr6_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[6]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[6], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr7_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[7]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[7], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr8_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[8]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[8], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr9_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[9]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[9], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr10_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[10]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[10], 0, 0xFFE00000);
    printf("\nRegister dump:\nSegment Register:%x\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.error_code, cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr11_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[11]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[11], 0, 0xFFE00000);
    printf("\nRegister dump:\nSegment Register:%x\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.error_code, cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr12_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[12]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[12], 0, 0xFFE00000);
    printf("\nRegister dump:\nSegment Register:%x\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.error_code, cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr13_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[13]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[13], 0, 0xFFE00000);
    printf("\nRegister dump:\nSegment Register:%x\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.error_code, cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr14_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    uint64 cr2 = 0;
    asm volatile("mov %%cr2, %0" : "=g" (cr2));
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[14]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[14], 0, 0xFFE00000);;
    printf("\nRegister dump:\nCR2:%x", cr2);
    if(cpu_regs.error_code & 0x20)
    {
        printf(" PK");
    } else {
        printf(" -");
    }
    if(cpu_regs.error_code & 0x10)
    {
        printf("I/D");
    } else {
        printf("-");
    }
    if(cpu_regs.error_code & 8)
    {
        printf("RSV");
    } else {
        printf("-");
    }
    if(cpu_regs.error_code & 4)
    {
        printf("U");
    } else {
        printf("S");
    }
    if(cpu_regs.error_code & 2)
    {
        printf("W");
    } else {
        printf("R");
    }
    if(cpu_regs.error_code & 1)
    {
        printf("P");
    } else {
        printf("-");
    }
    printf("\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr15_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[15]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[15], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr16_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[16]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[16], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr17_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[17]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[17], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr18_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[18]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[18], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr19_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[19]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[19], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr20_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[20]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[20], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}


void isr21_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[21]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[21], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr22_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[22]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[22], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr23_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[23]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[23], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr24_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[24]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[24], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr25_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[25]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[25], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr26_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[26]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[26], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr27_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[27]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[27], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr28_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[28]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[28], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr29_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[29]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[29], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr30_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[30]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[30], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}

void isr31_handler(struct cpu_regs_t cpu_regs)
{
    ClearScreen();
    printf("\n\n");
    uint32 ebx = 0, unused = 0;
    cpuid(1, unused, ebx, unused, unused);
    uint32 apicID = (ebx & 0xFF000000) >> 24;
    uint32 id_digits = 0;
    if(apicID > 0)
    {
        id_digits = 1;
    } else if(apicID > 9) {
        id_digits = 2;
    } else if(apicID > 99) {
        id_digits = 3;
    } else { //Very very unlikely
        id_digits = 4;
    }
    for(int x = 0; x <= 40 - (int)((strlen(exception_msg[31]) / 2 + 6) + id_digits); x++)
    {
        printf("%c", ' ');
    }
    printf("CPU%i - ", apicID);
    printcolor("PANIC!  ", 0, 0xFFE00000);
    printcolor(exception_msg[31], 0, 0xFFE00000);
    printf("\nRegister dump:\nRAX:%x\nRBX:%x\nRCX:%x\nRDX:%x\nRBP:%x\nRSP:%x\nRSI:%x\nRDI:%x\nRIP:%x\nFLAGS:%x\nCS:%x\nSS:%x\nDS:%x\nES:%x\nFS:%x\nGS:%x\n", cpu_regs.rax, cpu_regs.rbx, cpu_regs.rcx, cpu_regs.rdx, cpu_regs.rbp, cpu_regs.rsp, cpu_regs.rsi, cpu_regs.rdi, cpu_regs.rip, cpu_regs.rflags, cpu_regs.cs, cpu_regs.ss, cpu_regs.ds, cpu_regs.es, cpu_regs.fs, cpu_regs.gs);
    asm volatile("cli;hlt");
}
