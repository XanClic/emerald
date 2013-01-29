#ifndef _MEMMAP_H
#define _MEMMAP_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


int memmap_length(void);
void get_memmap_info(int index, bool *usable, uintptr_t *start, size_t *length);

void get_kernel_dim(uintptr_t *start, uintptr_t *end);

#endif
