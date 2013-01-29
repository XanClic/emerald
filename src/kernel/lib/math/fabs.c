#include <math.h>

#define __fabs(name, type) \
    type name(type x) \
    { \
        type r; \
        __asm__ __volatile__ ("fabs" : "=t"(r) : "0"(x)); \
        return r; \
    }

__fabs(fabs, double)
__fabs(fabsf, float)
__fabs(fabsl, long double)
