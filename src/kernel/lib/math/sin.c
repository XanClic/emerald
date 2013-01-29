#include <math.h>

#define __sin(name, type) \
    type name(type x) \
    { \
        type r; \
        if (isinf(x)) \
            return __domain_error(); \
        __asm__ __volatile__ ("fsin" : "=t"(r) : "0"(x)); \
        return r; \
    }

__sin(sin, double)
__sin(sinf, float)
__sin(sinl, long double)
