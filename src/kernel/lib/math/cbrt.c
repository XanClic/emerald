#include <math.h>

double cbrt(double x)
{
    return pow(x, 1. / 3.);
}

float cbrtf(float x)
{
    return powf(x, 1.f / 3.f);
}

long double cbrtl(long double x)
{
    return powl(x, 1.L / 3.L);
}
