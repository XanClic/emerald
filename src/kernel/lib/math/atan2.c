#include <math.h>

#define __atan2(name, type) \
    type name(type x, type y) \
    { \
        type r; \
        __asm__ __volatile__ ("fpatan" : "=t"(r) : "0"(x), "u"(y)); \
        return r; \
    }

__atan2(atan2, double)
__atan2(atan2f, float)
__atan2(atan2l, long double)
