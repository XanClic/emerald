#include <string.h>

char *strncat(char *restrict d, const char *restrict s, size_t n)
{
    char *vd = d;

    while (*(vd++));
    vd--;

    while (*s && n--)
        *(vd++) = *(s++);
    *vd = 0;

    return d;
}
