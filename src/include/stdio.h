#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>


#define EOF (-1)


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


typedef struct FILE { int _pseudo; } FILE;


extern FILE *stdin, *stdout, *stderr;


int putchar(int c);
int putc(int c, FILE *fp);

int getchar(void);
int fgetc(FILE *fp);

int puts(const char *s);
int fputs(const char *s, FILE *fp);

int printf(const char *s, ...);
int fprintf(FILE *fp, const char *s, ...);
int sprintf(char *buf, const char *s, ...);
int snprintf(char *str, size_t n, const char *format, ...);
int vfprintf(FILE *fp, const char *format, va_list args);
int vprintf(const char *format, va_list args);
int vsprintf(char *str, const char *format, va_list args);
int vsnprintf(char *buffer, size_t n, const char *format, va_list argptr);

void perror(const char *s);

int fflush(FILE *fp);

FILE *fopen(const char *path, const char *mode);
int fclose(FILE *fp);

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);

int fseek(FILE *fp, long ofs, int whence);

int feof(FILE *fp);

#endif
