#ifndef PMM_H
#define PMM_H

#include "../string/types.h"
#include "paging.h"
#include "../console/console.h"

struct heap_entry_t
{
    struct heap_entry_t *prev;
    struct heap_entry_t *next;
    uint64 size : 63;
    uint64 used : 1;
} __attribute__((packed));

struct heap_block_t
{
    struct heap_block_t *next;
    //uint32 start;
    //uint32 max;
    uint64 size;
} __attribute__((packed));

struct global_heap_t
{
    struct heap_block_t *heap;
    //uint32 block_size;
} __attribute__((packed));

void heapInit(uint32 size);
void heapAddBlock(uint64 base_addr, uint64 size);
void *kmalloc(uint64 size);
void *malloc(uint64 size);
void *kmalloc_aligned(uint64 size, uint64 alignment);
void *malloc_aligned(uint64 size, uint64 alignment);
void free(void *ptr);
void kill_pmm(void);

#endif
