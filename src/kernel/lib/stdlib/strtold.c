#include <ctype.h>
#include <stdlib.h>

long double strtold(const char *nptr, char **endptr)
{
    long double val = 0;
    int in_dec = 0;
    long double dec_multiplier = 0.1;

    while (*nptr)
    {
        if (isdigit(*nptr))
        {
            if (!in_dec)
            {
                val *= 10;
                val += *nptr - '0';
            }
            else
            {
                val += (long double)(*nptr - '0') * dec_multiplier;
                dec_multiplier /= 10.0;
            }
        }
        else if (*nptr == '.')
        {
            if (in_dec)
                break;
            in_dec = 1;
        }
        else
            break;
        // TODO: Exp

        nptr++;
    }

    if (endptr != NULL)
        *endptr = (char *)nptr;

    return val;
}
