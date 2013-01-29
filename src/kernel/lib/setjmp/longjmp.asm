format ELF

public _longjmp

_longjmp:
mov   edx,[esp+0x04]
mov   eax,[esp+0x08]

mov   esp,[edx+0x00]
add   esp,8
push  edx
push  dword [eax+0x04]
mov   ebx,[eax+0x08]
mov   esi,[eax+0x0C]
mov   edi,[eax+0x10]
mov   ebp,[eax+0x14]

test  eax,eax
jnz   return
add   eax,1
return:
ret
