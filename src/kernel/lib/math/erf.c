#include <math.h>

#define __erf(name, type) \
    type name(type x) \
    { \
        (void)x; \
        return NAN; \
    }

__erf(erf, double)
__erf(erff, float)
__erf(erfl, long double)
