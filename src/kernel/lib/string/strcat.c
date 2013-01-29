#include <string.h>

char *strcat(char *restrict d, const char *restrict s)
{
    char *vd = d;

    while (*(vd++));
    vd--;

    while (*s)
        *(vd++) = *(s++);
    *vd = 0;

    return d;
}
