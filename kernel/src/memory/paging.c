#include "paging.h"

#define PML4_IDX (0xFFFF800000000000 >> 39) & 0x1FF
#define PDPT_IDX (0xFFFF800000000000 >> 30) & 0x1FF

uint64 PT[512][512] __attribute__((section(".bss"), aligned(PAGE_SIZE))); //We have one PT for each PD entry, making 512 PT's. Thats around 2MB!!
uint64 PD[512][512] __attribute__((section(".bss"), aligned(PAGE_SIZE))); //We have one PD for each PDPT entry, making 512 PD's. Thats around 2MB!!
uint64 *PDPT = (uint64*)(0x104000 + 0xFFFF800000000000);
uint64 *PML4 = (uint64*)(0x103000 + 0xFFFF800000000000);

void invlpg(uint64 addr)
{
    asm volatile("invlpg (%0)" : : "b" (addr) : "memory");
}

void vmmap(uint64 paddr, uint64 vaddr, uint64 size, uint32 flags) //Size in (atleast) PAGE_SIZEK;
{
    paddr &= (~0xFFF);
    vaddr &= (~0xFFF);
    int PML4_idx = (vaddr >> 39) & 0x1FF;
    int PDPT_idx = (vaddr >> 30) & 0x1FF;
    int PD_idx = (vaddr >> 21) & 0x1FF;
    int PT_idx = (vaddr >> 12) & 0x1FF;
    if(size < PAGE_SIZE)
    {
        size = PAGE_SIZE;
    }
    if(PD[PDPT_idx][PD_idx] == 0)
    {
        PD[PDPT_idx][PD_idx] = (uint32)((uint64)&PT[PD_idx] - 0xFFFF800000000000) | flags;
    }
    if(PDPT[PDPT_idx] == 0)
    {
        PDPT[PDPT_idx] = (uint32)((uint64)&PD[PDPT_idx] - 0xFFFF800000000000) | flags;
    }
    if(PML4[PML4_idx] == 0)
    {
        PML4[PML4_idx] = (uint32)((uint64)PDPT - 0xFFFF800000000000) | flags;
    }
    /*if(PT[PD_idx][PT_idx] != 0)
    {
        return;
    }*/
    for(int i = 0; i < (int)(size / PAGE_SIZE); i++, PT_idx++, paddr += PAGE_SIZE)
    {
        if(PT_idx > 511)
        {
            if(PD[PDPT_idx][PD_idx] == 0)
            {
                PD[PDPT_idx][PD_idx] = (uint32)((uint64)&PT[PD_idx] - 0xFFFF800000000000) | flags;
            }
            PT_idx = 0;
            PD_idx++;
        }
        if(PD_idx > 511)
        {
            if(PDPT[PDPT_idx] == 0)
            {
                PDPT[PDPT_idx] = (uint32)((uint64)&PD[PDPT_idx] - 0xFFFF800000000000) | flags;
            }
            PD_idx = 0;
            PDPT_idx++;
        }
        if(PDPT_idx > 511)
        {
            if(PML4[PML4_idx] == 0)
            {
                PML4[PML4_idx] = (uint32)((uint64)PDPT - 0xFFFF800000000000) | flags;
            }
            PDPT_idx = 0;
            PML4_idx++;
        }
        PT[PD_idx][PT_idx] = paddr | flags;
    }
    return;
}

void id_vmmap(uint64 addr, uint64 size, uint32 flags)
{
    vmmap(addr, addr, size, flags);
}

void vmmunmap(uint64 vaddr, uint64 size) //revisar (?
{
    vaddr &= (~0xFFF);
    int PML4_idx = (vaddr >> 39) & 0x1FF;
    int PDPT_idx = (vaddr >> 30) & 0x1FF;
    int PD_idx = (vaddr >> 21) & 0x1FF;
    int PT_idx = (vaddr >> 12) & 0x1FF;
    for(int i = 0; i < (int)(size / PAGE_SIZE); i++, PT_idx++)
    {
        if(PT_idx > 511)
        {
            PD[PDPT_idx][PD_idx] = 0;
            PD_idx++;
            PT_idx = 0;
        }
        if(PD_idx > 511)
        {
            PDPT[PDPT_idx] = 0;
            PDPT_idx++;
            PD_idx = 0;
        }
        if(PDPT_idx > 511)
        {
            PML4[PML4_idx] = 0;
            PML4_idx++;
            PDPT_idx = 0;
        }
        PT[PD_idx][PT_idx] = 0;
        vaddr += PAGE_SIZE;
        invlpg(vaddr);
    }
}

bool is_page_present(uint64 vaddr)
{
    vaddr &= (~0xFFF);
    int PML4_idx = (vaddr >> 39) & 0x1FF;
    int PDPT_idx = (vaddr >> 30) & 0x1FF;
    int PD_idx = (vaddr >> 21) & 0x1FF;
    int PT_idx = (vaddr >> 12) & 0x1FF;
    if(PML4[PML4_idx])
    {
        if(PDPT[PDPT_idx])
        {
            if(PD[PDPT_idx][PD_idx])
            {
                if(PT[PD_idx][PT_idx])
                {
                    return true;
                }
            }
        }
    }
    return false;
}
