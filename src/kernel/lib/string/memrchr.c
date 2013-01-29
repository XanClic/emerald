#include <string.h>

void *memrchr(const void *s, int c, size_t n)
{
    const uint8_t *b = s;

    while (n--)
        if (b[n] == (uint8_t)c)
            return (void *)&b[n];

    return NULL;
}
