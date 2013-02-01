format ELF
use32

extrn main


section '.entry' executable

jmp     next


section '.text' executable

next:

mov     esp,stk
xor     ebp,ebp

push    ebx
push    eax

mov     eax, cr4
; PGE, MCE, !PCE, !PAE, PSE, DE, !TSD, !PVI, !VME, OSFXSR, OSXMMEXCPT
and     eax, 11111111111111111111100000000000b
or      eax, 00000000000000000000011011011000b
mov     cr4, eax

mov     eax, cr0
; !PG, WP, PE, !CD, !NW, !AM, !NE, !EM, !MP
and     eax, 00011111111110101111111111010000b
or      eax, 00000000000000010000000000000001b
mov     cr0, eax

fninit
ldmxcsr [mxcsr]


push    esp
call    main


hangman:
cli
hlt
jmp    hangman


mxcsr:
dd 0x1f80


section '.bss' writable

times 8192 db ?
stk:
