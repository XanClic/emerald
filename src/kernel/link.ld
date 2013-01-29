OUTPUT_ARCH("i386:i386")
OUTPUT_FORMAT("elf32-i386")
physical = 0x00100000;

SECTIONS
{
    . = physical;

    .entry :
    {
        *(.entry)
    }
    .multiboot ALIGN(4) :
    {
        *(.multiboot)
    }
    .text ALIGN(64) :
    {
        *(.text)
    }
    .data ALIGN(64) :
    {
        *(.data)
    }
    .bss ALIGN(64) :
    {
        *(.bss)
        *(COMMON)
    }

    __kernel_elf_end = .;
}

