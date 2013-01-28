#ifndef _COMPILER_H
#define _COMPILER_H

#ifdef __GNUC__
#define cc_packed       __attribute__((packed))
#define cc_noreturn     __attribute__((noreturn))
#define cc_weak         __attribute__((weak))
#define cc_unreachable  __builtin_unreachable()
#define cc_unused(func) func __attribute__((unused))
#define likely(x)       __builtin_expect((x), 1)
#define unlikely(x)     __builtin_expect((x), 0)
#else
#error Unknown compiler.
#endif

#endif
