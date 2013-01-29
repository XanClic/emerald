#include <math.h>

double asinh(double x)
{
    return log(x + sqrt(x * x + 1.));
}

float asinhf(float x)
{
    return logf(x + sqrtf(x * x + 1.f));
}

long double asinhl(long double x)
{
    return logl(x + sqrtl(x * x + 1.L));
}
