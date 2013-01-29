#include <stddef.h>
#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n--)
    {
        if (*(s1++) != *s2)
            return (unsigned char)s2[0] - (unsigned char)s1[-1];
        if (!*(s2++))
            return 0;
    }

    return 0;
}
