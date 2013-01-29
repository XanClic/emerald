format ELF

public _setjmp

_setjmp:
mov   ecx,[esp+0x00]
mov   eax,[esp+0x04]
mov   [eax+0x00],esp
mov   [eax+0x04],ecx
mov   [eax+0x08],ebx
mov   [eax+0x0C],esi
mov   [eax+0x10],edi
mov   [eax+0x14],ebp

xor   eax,eax
ret
