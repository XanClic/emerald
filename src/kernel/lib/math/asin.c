#include <math.h>

double asin(double x)
{
    if ((x > 1.) || (x < -1.))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return 2. * atan(x / (1. + sqrt(1. - x * x)));
}

float asinf(float x)
{
    if ((x > 1.f) || (x < -1.f))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return 2.f * atanf(x / (1.f + sqrtf(1.f - x * x)));
}

long double asinl(long double x)
{
    if ((x > 1.l) || (x < -1.l))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return 2.l * atanl(x / (1.l + sqrtl(1.l - x * x)));
}
