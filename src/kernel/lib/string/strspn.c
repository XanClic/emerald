#include <string.h>

int strspn(const char *s1, const char *s2)
{
    int i, j, found;

    for (i = 0; s1[i]; i++)
    {
        for (j = 0, found = 0; s2[j]; j++)
        {
            if (s1[i] == s2[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
            return i;
    }
    return i;
}
