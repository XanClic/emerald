#include <string.h>

char *strchr(const char *s, int c)
{
    while ((*s != c) && *s)
        s++;

    if (!*s)
        return NULL;
    return (char *)s;
}
