#include "pmm.h"

struct global_heap_t global_heap __attribute__((section(".heap")));

void heapInit(uint32 block_size)
{
    global_heap.heap = 0;
    global_heap.block_size = block_size;
}

void heapAddBlock(uint64 base_addr, uint64 size)
{
    struct heap_block_t *heap_block = base_addr;
    heap_block->next = global_heap.heap;
    global_heap.heap = heap_block;
    
    size -= sizeof(struct heap_block_t);
    heap_block->size = size;
    heap_block->max = size / global_heap.block_size;
    heap_block->start = 0;

    uint32 *heap = &heap_block[1];
    heap[heap_block->start] = (heap_block->max-1) << 1;
}

void *heap_alloc(uint64 size, uint64 alignment, uint32 flags)
{
    struct heap_block_t *heap_block;
    uint64 ptr;
    for(heap_block = global_heap.heap; heap_block; heap_block = heap_block->next)
    {
        uint32 *heap = &heap_block[1];
        for(int i = heap_block->start; i < heap_block->max;)
        {
            if(heap[i] & 1 || ((heap[i] >> 1)-i +1) * global_heap.block_size < size)
            {
                i = (heap[i] >> 1) +1;
                continue;
            }
            uint64 ptr = (uint64)heap + i * global_heap.block_size + heap_block->max * 4;

            if(ptr % alignment != 0)
            {
                uint64 aligned_ptr = ((ptr + (alignment - 1)) & ~(alignment-1));
                uint32 difference = aligned_ptr - ptr;
                if(((heap[i] >> 1)-i +1) * global_heap.block_size < size + difference)
                {
                    i = (heap[i] >> 1) + 1;
                    continue;
                }
                ptr = aligned_ptr;
                size += difference;

                int aligned_i = (aligned_ptr - (uint64)heap - heap_block->max * 4) / global_heap.block_size;
                heap[aligned_i] = (i << 1) | 1;
            }
            uint32 blocks_to_allocate = (size / global_heap.block_size) * global_heap.block_size < size ? (size / global_heap.block_size) + 1 : size / global_heap.block_size;

            if(!(heap[i+blocks_to_allocate] & 1)) heap[i+blocks_to_allocate] = heap[i];
            heap[i] = ((i+blocks_to_allocate-1)<<1) | 1;

            if(ptr < 0xFFFF800000000000) ptr += 0xFFFF800000000000;
            return (void*)ptr;
        }
    }

    printf("FATAL: OUT OF MEMORY\n(alberinfo, please implement a proper handler ffs)\n"); while(1);
    return 0;
}

void heap_free(void *addr)
{
    if(addr < 0xFFFF800000000000) addr += 0xFFFF800000000000;
    for(struct heap_block_t *heap_block = global_heap.heap; heap_block; heap_block = heap_block->next)
    {
        uint32 *heap = &heap_block[1];
        if(!(addr > heap && addr < (uint64)heap + heap_block->size)) continue; //If the address isnt in the current heap's range, go to the next heap

        addr = (uint64)addr - (uint64)heap - heap_block->max * 4;
        uint32 startpoint = (uint64)addr / global_heap.block_size;
        uint32 endpoint = heap[startpoint] >> 1;

        if(endpoint < startpoint && heap[startpoint] & 1) //aligned alloc
        {
            heap[startpoint] = 0;
            startpoint = endpoint;
            endpoint = heap[startpoint] >> 1;
        }

        heap[startpoint] &= ~((uint32)1);

        if(endpoint + 1 < heap_block->max)
        {
            if(!(heap[endpoint + 1] & 1))
            {
                heap[startpoint] = heap[endpoint+1];
                heap[endpoint+1] = 0;
            }
        }

        for(int i = startpoint-1; i >= heap_block->start; i--)
        {
            if(heap[i] == 0) continue;
            if(heap[i] & 1) break;
            heap[i] = heap[startpoint];
            heap[startpoint] = 0;
            startpoint = i;
        }
        break;
    }
    return;
}


void *kmalloc(uint64 size)
{
    return heap_alloc(size, 1, 3);
}

void *malloc(uint64 size)
{
    return heap_alloc(size, 1, 7) - 0xFFFF800000000000;
}

void *kmalloc_aligned(uint64 size, uint64 alignment)
{
    return heap_alloc(size, alignment, 3);
}

void *malloc_alignment(uint64 size, uint64 alignment)
{
    return heap_alloc(size, alignment, 7) - 0xFFFF800000000000;
}

void free(void *ptr)
{
    heap_free(ptr);
}

void kill_pmm(void)
{
    for(struct heap_block_t *heap_block = global_heap.heap; heap_block; heap_block = heap_block->next)
    {
        uint64 heap = &heap_block[1];
        memzero(heap, heap_block->max*4);
    }
}