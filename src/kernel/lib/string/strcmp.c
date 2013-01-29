#include <string.h>

int strcmp(const char *s1, const char *s2)
{
    int ret;

    while (!(ret = (unsigned char)*(s2++) - (unsigned char)*s1))
        if (!*(s1++))
            return 0;

    return ret;
}
