#include <string.h>

char *strtok_r(char *string1, const char *string2, char **saveptr)
{
    char *tok;
    int slen = strlen(string2);

    if (string1 == NULL)
        string1 = *saveptr;

    if (string1 == NULL)
        return NULL;

    while ((tok = strstr(string1, string2)) == string1)
        string1 += slen;

    if (!*string1)
    {
        *saveptr = NULL;
        return NULL;
    }

    if (tok == NULL)
        *saveptr = NULL;
    else
    {
        *tok = '\0';
        *saveptr = tok + slen;
    }

    return string1;
}

char *strtok(char *string1, const char *string2)
{
    static char *next_token = NULL;

    return strtok_r(string1, string2, &next_token);
}
