#include <stddef.h>
#include <string.h>

char *strncpy(char *restrict d, const char *restrict s, size_t n)
{
    char *vd = d;

    if (!n)
        return d;

    n++;
    while (--n && *s)
        *(vd++) = *(s++);
    while (n--)
        *(vd++) = 0;

    return d;
}
