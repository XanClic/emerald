#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *memcpy(void *restrict d, const void *restrict s, size_t n)
{
    const uint8_t *s8 = s;
    uint8_t *d8 = d;

    while (n--)
        *(d8++) = *(s8++);

    return d;
}
