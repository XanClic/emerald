#include <math.h>

#define __atan(name, type) \
    type name(type x) \
    { \
        type r; \
        __asm__ __volatile__ ("fld1; fpatan" : "=t"(r) : "0"(x)); \
        return r; \
    }

__atan(atan, double)
__atan(atanf, float)
__atan(atanl, long double)
