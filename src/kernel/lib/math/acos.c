#include <math.h>

double acos(double x)
{
    if ((x > 1.) || (x < -1.))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return M_PI / 2. - __sign(x) * atan(x / (1. + sqrt(1. - x * x)));
}

float acosf(float x)
{
    if ((x > 1.f) || (x < -1.f))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return (float)M_PI / 2.f - __signf(x) * atanf(x / (1.f + sqrtf(1.f - x * x)));
}

long double acosl(long double x)
{
    if ((x > 1.l) || (x < -1.l))
        return __domain_error();
    if (isnan(x))
        return NAN;
    return (long double)M_PI / 2.l - __signl(x) * atanl(x / (1.l + sqrtl(1.l - x * x)));
}
