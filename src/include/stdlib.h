#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <stdint.h>
#include <stdnoreturn.h>


#define MB_CUR_MAX 4

#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))


#ifdef __GNUC__
#define ARRAY_CONTAINS(arr, val) \
    ({ \
        bool found = false; \
        for (int _ = 0; _ < (int)ARR_LEN(arr); _++) \
        { \
            if ((arr)[_] == val) \
            { \
                found = true; \
                break; \
            } \
        } \
        found; \
     })
#endif


#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


void *sbrk(intptr_t diff);

int clearenv(void);
char *getenv(const char *name);
int putenv(char *string);
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

void *malloc(size_t sz);
void *calloc(size_t nmemb, size_t sz);
void *realloc(void *ptr, size_t size);
void free(void *mem);

void *aligned_alloc(size_t alignment, size_t size);

size_t _alloced_size(const void *ptr);

noreturn void exit(int status);
noreturn void abort(void);

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);
long long atoq(const char *nptr);
long long strtoll(const char *s, char **endptr, int base);
long strtol(const char *s, char **endptr, int base);
long double strtold(const char *nptr, char **endptr);
double strtod(const char *nptr, char **endptr);
unsigned long strtoul(const char *s, char **endptr, int base);

int mbtowc(wchar_t *pwc, const char *s, size_t n);
int mblen(const char *s, size_t n);
int wctomb(char *s, wchar_t wc);
size_t wcstombs(char* buf, const wchar_t* wcs, size_t len);
size_t mbstowcs(wchar_t* buf, const char* str, size_t len);

int system(const char *c);


static inline int abs(int i) { return (i < 0) ? -i : i; }

#endif
