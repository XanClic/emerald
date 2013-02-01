#ifndef _STDINT_H
#define _STDINT_H

typedef   signed char   int8_t;
typedef unsigned char  uint8_t;
typedef   signed short  int16_t;
typedef unsigned short uint16_t;
typedef   signed int    int32_t;
typedef unsigned int   uint32_t;
typedef   signed long long  int64_t;
typedef unsigned long long uint64_t;

typedef  int32_t  intptr_t;
typedef uint32_t uintptr_t;
typedef  int32_t ptrdiff_t;

typedef uint32_t wchar_t;


typedef  int8_t   int_fast8_t;
typedef uint8_t  uint_fast8_t;
typedef  int32_t  int_fast16_t;
typedef uint32_t uint_fast16_t;
typedef  int32_t  int_fast32_t;
typedef uint32_t uint_fast32_t;
typedef  int64_t  int_fast64_t;
typedef uint64_t uint_fast64_t;


typedef  int64_t  intmax_t;
typedef uint64_t uintmax_t;


#define  INT8_C(x)  x
#define UINT8_C(x)  x ## U
#define  INT16_C(x) x
#define UINT16_C(x) x ## U
#define  INT32_C(x) x
#define UINT32_C(x) x ## U
#define  INT64_C(x) x ## LL
#define UINT64_C(x) x ## ULL


#define  INT8_MIN  (-0x7F-1)
#define  INT8_MAX  ( 0x7F)
#define UINT8_MAX  ( 0xFF)
#define  INT16_MIN (-0x7FFF-1)
#define  INT16_MAX ( 0x7FFF)
#define UINT16_MAX ( 0xFFFF)
#define  INT32_MIN (-0x7FFFFFFF-1)
#define  INT32_MAX ( 0x7FFFFFFF)
#define UINT32_MAX ( 0xFFFFFFFFU)
#define  INT64_MIN (-0x7FFFFFFFFFFFFFFFLL-1)
#define  INT64_MAX ( 0x7FFFFFFFFFFFFFFFLL)
#define UINT64_MAX ( 0xFFFFFFFFFFFFFFFFULL)

#define  INT_LEAST8_MIN  (-0x7F-1)
#define  INT_LEAST8_MAX  ( 0x7F)
#define UINT_LEAST8_MAX  ( 0xFF)
#define  INT_LEAST16_MIN (-0x7FFF-1)
#define  INT_LEAST16_MAX ( 0x7FFF)
#define UINT_LEAST16_MAX ( 0xFFFF)
#define  INT_LEAST32_MIN (-0x7FFFFFFF-1)
#define  INT_LEAST32_MAX ( 0x7FFFFFFF)
#define UINT_LEAST32_MAX ( 0xFFFFFFFFU)
#define  INT_LEAST64_MIN (-0x7FFFFFFFFFFFFFFFLL-1)
#define  INT_LEAST64_MAX ( 0x7FFFFFFFFFFFFFFFLL)
#define UINT_LEAST64_MAX ( 0xFFFFFFFFFFFFFFFFULL)

#define  INT_FAST8_MIN  (-0x7FFFFFFF-1)
#define  INT_FAST8_MAX  ( 0x7FFFFFFF)
#define UINT_FAST8_MAX  ( 0xFFFFFFFFU)
#define  INT_FAST16_MIN (-0x7FFFFFFF-1)
#define  INT_FAST16_MAX ( 0x7FFFFFFF)
#define UINT_FAST16_MAX ( 0xFFFFFFFFU)
#define  INT_FAST32_MIN (-0x7FFFFFFF-1)
#define  INT_FAST32_MAX ( 0x7FFFFFFF)
#define UINT_FAST32_MAX ( 0xFFFFFFFFU)
#define  INT_FAST64_MIN (-0x7FFFFFFFFFFFFFFFLL-1)
#define  INT_FAST64_MAX ( 0x7FFFFFFFFFFFFFFFLL)
#define UINT_FAST64_MAX ( 0xFFFFFFFFFFFFFFFFULL)

#define  INTPTR_MIN  INT32_MIN
#define  INTPTR_MAX  INT32_MAX
#define UINTPTR_MAX UINT32_MAX
#define  INTMAX_MIN  INT64_MIN
#define  INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX
#define  PTRDIFF_MIN INT32_MIN
#define  PTRDIFF_MAX INT32_MAX

#endif
