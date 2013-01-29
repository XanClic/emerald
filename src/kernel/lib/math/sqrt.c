#include <math.h>

#define __sqrt(name, type) \
    type name(type x) \
    { \
        type r; \
        if (x < 0) \
            return __domain_error(); \
        __asm__ __volatile__ ("fsqrt" : "=t"(r) : "0"(x)); \
        return r; \
    }

__sqrt(sqrt, double)
__sqrt(sqrtf, float)
__sqrt(sqrtl, long double)
