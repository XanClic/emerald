#include <string.h>

char *strpbrk(const char *s1, const char *s2)
{
    int i;

    s1--;
    while (*(++s1))
        for (i = 0; s2[i]; i++)
            if (*s1 == s2[i])
                return (char *)s1;
    return NULL;
}
