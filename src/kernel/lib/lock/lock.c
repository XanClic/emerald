#include <lock.h>
#include <stdbool.h>
#include <stdint.h>


bool lock(volatile lock_t *v)
{
    uint32_t eflags;
    __asm__ __volatile__ ("pushfl; pop %0;" : "=r"(eflags));


    if (__sync_lock_test_and_set(v, locked) == unlocked)
        return true;

    if (!(eflags & (1 << 9))) // IF
        return false;

    while (__sync_lock_test_and_set(v, locked) == locked);

    return true;
}


void unlock(volatile lock_t *v)
{
    __sync_lock_release(v);
}
