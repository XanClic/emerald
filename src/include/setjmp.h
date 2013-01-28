#ifndef _SETJMP_H
#define _SETJMP_H

#include <compiler.h>
#include <stdint.h>
#include <stdnoreturn.h>


typedef struct
{
    uint32_t esp, eip;
    uint32_t ebx, esi, edi, ebp;
} cc_packed jmp_buf;


int setjmp(jmp_buf env);
noreturn void longjmp(jmp_buf env, int val);

#define setjmp(buf) _setjmp(&(buf))
#define longjmp(buf, val) _longjmp(&(buf), val)

int _setjmp(jmp_buf *env);
noreturn void _longjmp(jmp_buf *env, int val);

#endif
