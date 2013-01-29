format ELF

public _longjmp

_longjmp:
mov   edx,[esp+0x04]
mov   eax,[esp+0x08]

mov   esp,[edx+0x00]
add   esp,8
push  edx
push  dword [edx+0x04]
mov   ebx,[edx+0x08]
mov   esi,[edx+0x0C]
mov   edi,[edx+0x10]
mov   ebp,[edx+0x14]

test  eax,eax
jnz   return
add   eax,1
return:
ret
