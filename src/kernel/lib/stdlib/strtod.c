#include <stdlib.h>

double strtod(const char *nptr, char **endptr)
{
    return strtold(nptr, endptr);
}
