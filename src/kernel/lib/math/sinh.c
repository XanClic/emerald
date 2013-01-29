#include <math.h>

double sinh(double x)
{
    return .5 * (exp(x) - exp(-x));
}

float sinhf(float x)
{
    return .5f * (expf(x) - expf(-x));
}

long double sinhl(long double x)
{
    return .5L * (expl(x) - expl(-x));
}
