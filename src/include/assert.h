#ifdef assert
#undef assert
#endif

#ifndef NDEBUG

#ifndef __quote
#define __squote(arg) #arg
#define __quote(arg) __squote(arg)
#endif

#define assert(assertion) do { if (!(assertion)) for (;;); } while (0)

#endif
