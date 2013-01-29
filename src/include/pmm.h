#ifndef _PMM_H
#define _PMM_H

#include <stdbool.h>
#include <stdint.h>


void init_pmm(void);

uintptr_t pmm_alloc(int count);
void pmm_free(uintptr_t start, int count);

void pmm_use(uintptr_t start, int count);

int pmm_user_count(uintptr_t paddr);

void pmm_mark_cow(uintptr_t start, int count, bool flag);
bool pmm_is_cow(uintptr_t paddr);

#endif
