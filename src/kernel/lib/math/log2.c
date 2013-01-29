#include <math.h>

#define __log2(name, type) \
    type name(type x) \
    { \
        type r; \
        if (!x) \
            return __pole_error(1); \
        __asm__ __volatile__ ("fld1; fyl2x" : "=t"(r) : "0"(x)); \
        return r; \
    }

__log2(log2, double)
__log2(log2f, float)
__log2(log2l, long double)
