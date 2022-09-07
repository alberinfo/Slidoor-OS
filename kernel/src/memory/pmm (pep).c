#include "pmm (pep).h"

struct global_heap_t global_heap __attribute__((section(".heap")));

void heapInit(uint32 block_size)
{
    global_heap.heap = 0;
    //global_heap.block_size = block_size;
}

void heapAddBlock(uint64 base_addr, uint64 size)
{
    struct heap_block_t *heap_block = base_addr;
    heap_block->next = global_heap.heap;
    global_heap.heap = heap_block;

    heap_block->size = size - sizeof(struct heap_block_t);

    struct heap_entry_t *heap = &heap_block[1];
    heap->next = 0;
    heap->prev = 0;
    heap->size = heap_block->size - sizeof(struct heap_entry_t);
    heap->used = false;
}

void *heap_alloc(uint64 size, uint64 alignment, uint32 flags)
{
    if(size == 0) return 0;
    //if(size <= sizeof(struct heap_entry_t)) size = sizeof(struct heap_entry_t);

    struct heap_block_t *heap_block;
    uint64 ptr;
    for(heap_block = global_heap.heap; heap_block; heap_block = heap_block->next)
    {
        struct heap_entry_t *heap;
        for(heap = &heap_block[1]; heap; heap = heap->next)
        {
            if(heap->used || heap->size < size) continue;

            uint64 ptr = &heap[1]; //skip metadata

            if(ptr % alignment != 0)
            {
                uint64 aligned_ptr = ((ptr + (alignment - 1)) & ~(alignment-1));
                uint32 difference = aligned_ptr - ptr;
                if(heap->size < size + difference) continue;

                heap->prev->next = aligned_ptr;
                heap->prev->size += difference;
                memcpy_fast(aligned_ptr-sizeof(struct heap_entry_t), heap, sizeof(struct heap_entry_t));

                heap = aligned_ptr - sizeof(struct heap_entry_t);

                ptr = aligned_ptr;
                //size += difference;
            }

            heap->used = true;
            if(heap->size - size > sizeof(struct heap_entry_t))
            {
                struct heap_entry_t *merge_heap = ptr + size;
                memzero(merge_heap, sizeof(struct heap_entry_t));
                merge_heap->prev = heap;
                merge_heap->next = heap->next;
                merge_heap->size = heap->size - size - sizeof(struct heap_entry_t);
                merge_heap->used = false;

                if(heap->next != 0) heap->next->prev = merge_heap;

                heap->next = merge_heap;
                heap->size = size;
            }

            if(ptr < 0xFFFF800000000000) ptr += 0xFFFF800000000000;

            memzero(ptr, size);
            return (void*)ptr;
        }
    }

    printf("Concept list ran out of mem. May want to debug the whole list here.\n");
    while(1);
    return 0;
}

void heap_free(void *addr)
{
    if(addr < 0xFFFF800000000000) addr += 0xFFFF800000000000;

    struct heap_entry_t *heap = (uint64)addr - sizeof(struct heap_entry_t);
    heap->used = false;

    struct heap_entry_t *merge_heap = heap->next;
    while(merge_heap)
    {
        if(merge_heap->used)
        {
            merge_heap->prev = heap;
            break;
        }

        heap->next = merge_heap->next;
        heap->size += merge_heap->size + sizeof(struct heap_entry_t);

        memzero(merge_heap, sizeof(struct heap_entry_t));

        merge_heap = heap->next;
    }

    merge_heap = heap->prev;
    while(merge_heap)
    {
        if(merge_heap->used)
        {
            if(merge_heap->next != 0) merge_heap->next->prev = merge_heap;
            break;
        }

        merge_heap->next = heap->next;
        merge_heap->size += heap->size + sizeof(struct heap_entry_t);

        memzero(heap, sizeof(struct heap_entry_t));

        heap = merge_heap;
        merge_heap = merge_heap->prev;
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

void *malloc_aligned(uint64 size, uint64 alignment)
{
    return heap_alloc(size, alignment, 7) - 0xFFFF800000000000;
}

void free(void *ptr)
{
    heap_free(ptr);
}

void kill_pmm(void)
{
    struct heap_block_t *heap_block = global_heap.heap;
    while(heap_block)
    {
        uint64 next_addr = heap_block->next;
        memzero(heap_block, heap_block->size + sizeof(struct heap_block_t));
        heap_block = next_addr;
    }
}