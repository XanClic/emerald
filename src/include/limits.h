#ifndef _LIMITS_H
#define _LIMITS_H

#define  CHAR_BIT   8
#define SCHAR_MIN  -0x80
#define SCHAR_MAX   0x7F
#define UCHAR_MAX   0xFF
#define  CHAR_MIN   SCHAR_MIN
#define  CHAR_MAX   SCHAR_MAX

#define  SHRT_MIN  -0x8000
#define  SHRT_MAX   0x7FFF
#define USHRT_MAX   0xFFFF

#define  WORD_BIT   32
#define  INT_MIN   -0x80000000
#define  INT_MAX    0x7FFFFFFF
#define UINT_MAX    0xFFFFFFFFU

#define  LONG_BIT   32
#define  LONG_MIN  -0x80000000L
#define  LONG_MAX   0x7FFFFFFFL
#define ULONG_MAX   0xFFFFFFFFUL

#define  LLONG_MIN -0x8000000000000000LL
#define  LLONG_MAX  0x7FFFFFFFFFFFFFFFLL
#define ULLONG_MAX  0xFFFFFFFFFFFFFFFFULL

#define  SIZE_MAX  ULONG_MAX
#define SSIZE_MAX   LONG_MAX

#define MB_LEN_MAX  4

#endif
