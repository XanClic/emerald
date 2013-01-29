#include <math.h>

#define __cos(name, type) \
    type name(type x) \
    { \
        type r; \
        if (isinf(x)) \
            return __domain_error(); \
        __asm__ __volatile__ ("fcos" : "=t"(r) : "0"(x)); \
        return r; \
    }

__cos(cos, double)
__cos(cosf, float)
__cos(cosl, long double)
