#include <stddef.h>
#include <string.h>

size_t strnlen(const char *s, size_t mlen)
{
    size_t i;
    for (i = 0; s[i] && (i < mlen); i++);
    return i;
}
