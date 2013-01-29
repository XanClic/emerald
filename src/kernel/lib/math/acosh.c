#include <math.h>

double acosh(double x)
{
    return log(x + sqrt(x * x - 1.));
}

float acoshf(float x)
{
    return logf(x + sqrtf(x * x - 1.f));
}

long double acoshl(long double x)
{
    return logl(x + sqrtl(x * x - 1.L));
}
