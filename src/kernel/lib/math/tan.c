#include <math.h>

#define __tan(name, type) \
    type name(type x) \
    { \
        type r; \
        if (isinf(x)) \
            return __domain_error(); \
        __asm__ __volatile__ ("fprem; fptan; fstp %%st(0)" : "=t"(r) : "0"(x), "u"(2 * M_PI)); \
        return r; \
    }

__tan(tan, double)
__tan(tanf, float)
__tan(tanl, long double)
