#include <string.h>

char *strrchr(const char *s, int c)
{
    int len = strlen(s) - 1;

    for (; len >= 0; len--)
        if (s[len] == c)
            return (char *)&s[len];

    return NULL;
}
