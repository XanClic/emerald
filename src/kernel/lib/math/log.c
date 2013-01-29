#include <math.h>

#define __log(name, type) \
    type name(type x) \
    { \
        type r; \
        if (!x) \
            return __pole_error(1); \
        __asm__ __volatile__ ("fyl2x; fldl2e; fdivp" : "=t"(r) : "0"(x), "u"(1.)); /* 1 · ld x / ld e == ln x */ \
        return r; \
    }

__log(log, double)
__log(logf, float)
__log(logl, long double)
