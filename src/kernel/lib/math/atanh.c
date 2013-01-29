#include <math.h>

double atanh(double x)
{
    return .5 * log((1. + x) / (1. - x));
}

float atanhf(float x)
{
    return .5f * logf((1.f + x) / (1.f - x));
}

long double atanhl(long double x)
{
    return .5L * logl((1.L + x) / (1.L - x));
}
