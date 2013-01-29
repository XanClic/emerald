#include <math.h>

double cosh(double x)
{
    return .5 * (exp(x) + exp(-x));
}

float coshf(float x)
{
    return .5f * (expf(x) + expf(-x));
}

long double coshl(long double x)
{
    return .5L * (expl(x) + expl(-x));
}
