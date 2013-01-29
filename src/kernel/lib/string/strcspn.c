#include <string.h>

int strcspn(const char *s1, const char *s2)
{
    int i, j;

    for (i = 0; s1[i]; i++)
        for (j = 0; s2[j]; j++)
            if (s1[i] == s2[j])
                return i;
    return i;
}
