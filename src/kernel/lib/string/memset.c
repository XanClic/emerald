#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *memset(void *s, int c, size_t n)
{
    uint8_t *d = s;

    while (n--)
        *(d++) = c;

    return s;
}
