#ifndef PAGING_H
#define PAGING_H

#include "../string/types.h"
#include "../string/string.h"

#define PAGE_SIZE 4096

void remap_kernel(uint64 kernel_end);
void invlpg(uint64 addr);
void vmmap(uint64 paddr, uint64 vaddr, uint64 size, uint32 flags);
void id_vmmap(uint64 addr, uint64 size, uint32 flags);
void vmmunmap(uint64 vaddr, uint64 size);

#endif
