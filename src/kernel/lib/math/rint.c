#include <math.h>

#define __rint(name, type, round) \
    type name(type x) \
    { \
        return round(x); \
    }

__rint(rint, double, nearbyint)
__rint(rintf, float, nearbyintf)
__rint(rintl, long double, nearbyintl)
