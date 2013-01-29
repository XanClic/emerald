#include <math.h>

#define __ldexp(name, type) \
    type name(type x, int expo) \
    { \
        type r; \
        type e = expo; \
        __asm__ __volatile__ ("fscale; fst %%st(0)" : "=t"(r) : "0"(x), "u"(e)); \
        return r; \
    }

__ldexp(ldexp, double)
__ldexp(ldexpf, float)
__ldexp(ldexpl, long double)
