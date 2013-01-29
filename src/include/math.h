#ifndef _MATH_H
#define _MATH_H

#include <errno.h>
#include <signal.h>
#include <stdint.h>

#define NAN (__builtin_nanf(""))
#define INFINITY (__builtin_inff())

// 42 decimal digits ought to be enough for everyone
#define M_PI 3.141592653589793238462643383279502884197169

typedef int fenv_t;

extern int __fp_exceptions;

#define FE_INVALID   (1 << 0)
#define FE_DIVBYZERO (1 << 1)

#define FE_ALL_EXCEPT (FE_INVALID | FE_DIVBYZERO)

#define FE_DFL_ENV 0

#define HAVE_LOG2

#define isinff(x) ((x) == __builtin_inff())
#define isinfd(x) ((x) == __builtin_inf ())
#define isinfl(x) ((x) == __builtin_infl())

#define isinf(x) \
    ((sizeof(x) == sizeof(float)) ? isinff(x) : \
     ((sizeof(x) == sizeof(double)) ? isinfd(x) : isinfl(x)))

#define isnan(x) ((x) != (x))

// TODO: _Generic. Wenn gcc das endlich mal kann.

#define __sign(x)  (((x) <= -0. ) ? -1.  : 1. )
#define __signf(x) (((x) <= -0.f) ? -1.f : 1.f)
#define __signl(x) (((x) <= -0.l) ? -1.l : 1.l)

#define __def1(fname) \
    double fname(double x); \
    float fname##f(float x); \
    long double fname##l(long double x)

#define __def1i(fname) \
    double fname(double x, int y); \
    float fname##f(float x, int y); \
    long double fname##l(long double x, int y)

#define __def2(fname) \
    double fname(double x, double y); \
    float fname##f(float x, float y); \
    long double fname##l(long double x, long double y)

__def1(sin);
__def1(cos);
__def1(tan);
__def1(asin);
__def1(acos);
__def1(atan);
__def1(sqrt);
__def1(log);
__def1(log2);
__def1(log10);
__def1(fabs);
__def2(fmod);
__def1(rint);
__def1(floor);
__def1(ceil);
__def1(trunc);
__def1(round);
__def1(nearbyint);
__def1i(ldexp);
__def2(pow);
__def1(exp);
__def2(atan2);
__def1(sinh);
__def1(cosh);
__def1(tanh);
__def1(asinh);
__def1(acosh);
__def1(atanh);
__def1(cbrt);
__def2(hypot);
__def1(erf);
__def1(erfc);

double frexp(double x, int *exp);
float frexpf(float x, int *exp);
long double frexpl(long double x, int *exp);

static inline int feraiseexcept(int excepts)
{
    __fp_exceptions |= excepts;
    if (__fp_exceptions)
        raise(SIGFPE);
    return 0;
}

static inline int feclearexcept(int excepts)
{
    __fp_exceptions &= ~excepts;
    return 0;
}

static inline int fetestexcept(int excepts)
{
    return __fp_exceptions & excepts;
}

static inline int fegetenv(fenv_t *envp)
{
    *envp = __fp_exceptions;
    return 0;
}

static inline int feholdexcept(fenv_t *envp)
{
    *envp = __fp_exceptions;
    __fp_exceptions = 0;
    return 0;
}

static inline int fesetenv(const fenv_t *envp)
{
    __fp_exceptions = *envp;
    return 0;
}

static inline int feupdateenv(const fenv_t *envp)
{
    __fp_exceptions |= *envp;
    return 0;
}

static inline long double __domain_error(void)
{
    errno = EDOM;
    feraiseexcept(FE_INVALID);
    return NAN;
}

static inline long double __domain_error_noerrno(void)
{
    feraiseexcept(FE_INVALID);
    return NAN;
}

static inline long double __pole_error(int negative)
{
    errno = ERANGE;
    feraiseexcept(FE_DIVBYZERO);
    return negative ? -INFINITY : INFINITY;
}

#endif
