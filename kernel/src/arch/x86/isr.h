#ifndef ISR_H
#define ISR_H

#include "../../string/types.h"
#include "../../console/console.h"
#include "cpu.h"

struct cpu_regs_t
{
    uint64 ds, es, fs, gs;
    uint64 rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64 error_code, rip, cs, rflags, rsp, ss;
} __attribute__((packed));

void isr0_handler(struct cpu_regs_t cpu_regs);
void isr1_handler(struct cpu_regs_t cpu_regs);
void isr2_handler(struct cpu_regs_t cpu_regs);
void isr3_handler(struct cpu_regs_t cpu_regs);
void isr4_handler(struct cpu_regs_t cpu_regs);
void isr5_handler(struct cpu_regs_t cpu_regs);
void isr6_handler(struct cpu_regs_t cpu_regs);
void isr7_handler(struct cpu_regs_t cpu_regs);
void isr8_handler(struct cpu_regs_t cpu_regs);
void isr9_handler(struct cpu_regs_t cpu_regs);
void isr10_handler(struct cpu_regs_t cpu_regs);
void isr11_handler(struct cpu_regs_t cpu_regs);
void isr12_handler(struct cpu_regs_t cpu_regs);
void isr13_handler(struct cpu_regs_t cpu_regs);
void isr14_handler(struct cpu_regs_t cpu_regs);
void isr15_handler(struct cpu_regs_t cpu_regs);
void isr16_handler(struct cpu_regs_t cpu_regs);
void isr17_handler(struct cpu_regs_t cpu_regs);
void isr18_handler(struct cpu_regs_t cpu_regs);
void isr19_handler(struct cpu_regs_t cpu_regs);
void isr20_handler(struct cpu_regs_t cpu_regs);
void isr21_handler(struct cpu_regs_t cpu_regs);
void isr22_handler(struct cpu_regs_t cpu_regs);
void isr23_handler(struct cpu_regs_t cpu_regs);
void isr24_handler(struct cpu_regs_t cpu_regs);
void isr25_handler(struct cpu_regs_t cpu_regs);
void isr26_handler(struct cpu_regs_t cpu_regs);
void isr27_handler(struct cpu_regs_t cpu_regs);
void isr28_handler(struct cpu_regs_t cpu_regs);
void isr29_handler(struct cpu_regs_t cpu_regs);
void isr30_handler(struct cpu_regs_t cpu_regs);
void isr31_handler(struct cpu_regs_t cpu_regs);

#endif
