#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *memmove(void *d, const void *s, size_t n)
{
    const uint8_t *s8 = s;
    uint8_t *d8 = d;

    if (((uintptr_t)d < (uintptr_t)s) || ((uintptr_t)s + n <= (uintptr_t)d))
        while (n--)
            *(d8++) = *(s8++);
    else
        while (n--)
            d8[n] = s8[n];

    return d;
}
