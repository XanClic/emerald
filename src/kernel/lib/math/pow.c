#include <math.h>

long double powl(long double x, long double y)
{
    long double res;

    __asm__ __volatile__ (
        // ST(0) == x; ST(1) == y
        "fld1;"
        // ST(0) == 1; ST(1) == x; ST(2) == y
        "fxch;"
        // ST(0) == x; ST(1) == 1; ST(2) == y
        "fyl2x;"
        // ST(0) == log2(x); ST(1) == y
        "fmulp;"
        // ST(0) == y * log2(x)
        "f2xm1;"
        // ST(0) == 2^(y * log2(x)) - 1 == x^y - 1
        "fld1;"
        // ST(0) == 1; ST(1) == x^y - 1
        "faddp"
        // ST(0) == x^y
        : "=t"(res) : "0"(x), "u"(y));

    return res;
}

double pow(double x, double y)
{
    return powl(x, y);
}

float powf(float x, float y)
{
    return powf(x, y);
}
