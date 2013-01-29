#include <math.h>

double tanh(double x)
{
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

float tanhf(float x)
{
    return (expf(x) - expf(-x)) / (expf(x) + expf(-x));
}

long double tanhl(long double x)
{
    return (expl(x) - expl(-x)) / (expl(x) + expl(-x));
}
