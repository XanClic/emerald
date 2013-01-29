#include <stdlib.h>
#include <string.h>

char *strdup(const char *s)
{
    char *n = malloc(strlen(s) + 1);
    return strcpy(n, s);
}
