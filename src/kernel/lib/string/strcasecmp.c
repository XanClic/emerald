#include <ctype.h>
#include <string.h>

int strcasecmp(const char *s1, const char *s2)
{
    while (*s1 || *s2)
    {
        int diff = tolower(*(s1++)) - tolower(*(s2++));
        if (diff)
            return diff;
    }

    return 0;
}
