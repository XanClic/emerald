#ifndef _LOCK_H
#define _LOCK_H

#include <stdbool.h>


typedef int lock_t;


#define unlocked 0
#define   locked 1


bool lock(volatile lock_t *v);
void unlock(volatile lock_t *v);

#endif
