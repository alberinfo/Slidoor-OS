#ifndef CPU_H
#define CPU_H

#include "../../string/types.h"
#include "../../string/string.h"
#include "../../memory/pmm.h"

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

struct cpu_info_t
{
    string brand;
    string type;
    string family;
    string extended_family;
    string model;
    string name;
    uint32 stepping;
    uint32 reserved;
    uint8 AVX; //0 means no AVX, 1 means AVX1, 2 AVX2, 3 AVX512
} __attribute__((packed));

struct cpu_info_t cpu_info;

void CPUDisableInts(void);
void CPUEnableInts(void);
uint8 inportb (uint16 _port);
void outportb (uint16 _port, uint8 _data);
uint16 inportw(uint16 _port);
void outportw(uint16 _port, uint16 _data);
uint32 inportl(uint16 _port);
void outportl(uint16 _port, uint32 _data);
void rdmsr(uint32 msr, uint32 *low, uint32 *high);
void wrmsr(uint32 msr, uint32 low, uint32 high);
void detectCpu();


#endif
