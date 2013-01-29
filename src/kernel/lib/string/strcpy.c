#include <string.h>

char *strcpy(char *restrict d, const char *restrict s)
{
    char *vd = d;

    while (*s)
        *(vd++) = *(s++);
    *vd = 0;

    return d;
}
