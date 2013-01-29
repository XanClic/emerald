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
    ruby_env ALIGN(64) :
    {
        ruby_env_start = .;
        *(ruby_env)
        ruby_env_end = .;
    }

    __kernel_elf_end = .;
}

