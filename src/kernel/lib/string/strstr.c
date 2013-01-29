#include <string.h>

char *strstr(const char *s1, const char *s2)
{
    int i;

    while (*s1)
    {
        for (i = 0; s2[i] && (s1[i] == s2[i]); i++);

        if (!s2[i])
            return (char *)s1;

        s1++;
    }

    return NULL;
}
