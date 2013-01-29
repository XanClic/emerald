#include <kassert.h>
#include <pmm.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define PAGE_SHIFT 12
#define PAGE_SIZE  (1 << PAGE_SHIFT)


void *malloc(size_t size)
{
    size += sizeof(size);

    int frame_count = (size + PAGE_SIZE) >> PAGE_SHIFT;


    size_t *mem = (size_t *)pmm_alloc(frame_count);

    *mem = size;


    return mem + 1;
}


void free(void *ptr)
{
    if (ptr == NULL)
        return;


    ptr = (size_t *)ptr - 1;

    kassert(!((uintptr_t)ptr & (PAGE_SIZE - 1)));

    size_t size = *(size_t *)ptr;


    int frame_count = (size + PAGE_SIZE) >> PAGE_SHIFT;


    pmm_free((uintptr_t)ptr, frame_count);
}


void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);


    size_t req_size = size + sizeof(size);


    size_t *sptr = (size_t *)ptr - 1;

    kassert(!((uintptr_t)sptr & (PAGE_SIZE - 1)));

    size_t avl_size = *sptr;


    int avl_frame_count = (avl_size + PAGE_SIZE) >> PAGE_SHIFT;
    int req_frame_count = (req_size + PAGE_SIZE) >> PAGE_SHIFT;


    if (avl_frame_count > req_frame_count)
        return ptr;


    void *new = malloc(size);
    memcpy(new, ptr, avl_size);
    free(ptr);


    return new;
}
