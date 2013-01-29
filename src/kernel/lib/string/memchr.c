#include <string.h>

void *memchr(const void *s, int c, size_t n)
{
    const uint8_t *b = s;

    while (n--)
        if (*(b++) == (uint8_t)c)
            return (void *)(b - 1);

    return NULL;
}
