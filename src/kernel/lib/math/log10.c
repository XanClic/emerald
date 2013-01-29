#include <math.h>

#define __log10(name, type) \
    type name(type x) \
    { \
        type r; \
        if (!x) \
            return __pole_error(1); \
        __asm__ __volatile__ ("fld1; fyl2x; fldl2t; fdivrp" : "=t"(r) : "0"(x)); /* 1 · ld x / ld 10 == lg x */ \
        return r; \
    }

__log10(log10, double)
__log10(log10f, float)
__log10(log10l, long double)
