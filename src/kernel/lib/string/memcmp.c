#include <stdint.h>
#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    int ret = 0;
    const uint8_t *b1 = s1, *b2 = s2;

    while (n-- && !(ret = (unsigned char)*(b2++) - (unsigned char)*b1++));

    return ret;
}
