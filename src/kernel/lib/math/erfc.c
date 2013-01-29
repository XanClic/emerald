#include <math.h>

double erfc(double x)
{
    return 1. - erf(x);
}

float erfcf(float x)
{
    return 1.f - erff(x);
}

long double erfcl(long double x)
{
    return 1.L - erfl(x);
}
