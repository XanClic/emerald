#include <math.h>
#include <stdint.h>


double frexp(double x, int *exp)
{
    uint64_t *dir = (uint64_t *)&x;

    *exp = ((*dir >> 52) & ((1 << 11) - 1)) - 1022;

    *dir &= ~(((1LL << 11) - 1) << 52);
    *dir |= 1022LL << 52;

    return x;
}


float frexpf(float x, int *exp)
{
    uint32_t *dir = (uint32_t *)&x;

    *exp = ((*dir >> 23) & ((1 << 8) - 1)) - 126;

    *dir &= ~(((1 << 8) - 1) << 23);
    *dir |= 126 << 23;

    return x;
}


long double frexpl(long double x, int *exp)
{
    // FIXME
    *exp = 0;

    while (fabsl(x) < .5L)
    {
        x *= 2.L;
        (*exp)--;
    }

    while (fabsl(x) >= 1.L)
    {
        x /= 2.L;
        (*exp)++;
    }

    return x;
}
