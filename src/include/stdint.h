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

#endif
