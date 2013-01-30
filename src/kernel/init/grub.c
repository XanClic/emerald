#include <boot.h>
#include <memmap.h>
#include <multiboot.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


static uint32_t mbhdr[] __attribute__((section(".multiboot"), used)) = { 0x1BADB002, 0x00000003, (uint32_t)-(0x1BADB002 + 0x00000003) };


struct multiboot_info *mboot;

static struct memory_map *mmap;
static int mmap_length;

static struct multiboot_module *modules;
static int module_count;

extern const void __kernel_elf_end;


bool get_boot_info(void *info)
{
    // Ist das auch GRUB?
    if (*(uint32_t *)info != 0x2BADB002)
        return false;


    mboot = (struct multiboot_info *)((uint32_t *)info)[1];


    if (!(mboot->mi_flags & (1 << 6))) // Memory Map
        return false;

    mmap = (struct memory_map *)mboot->mmap_addr;

    for (struct memory_map *entry = mmap; (uintptr_t)entry - (uintptr_t)mmap < (int)mboot->mmap_length; mmap_length++)
        entry = (struct memory_map *)((uintptr_t)entry + entry->size + sizeof(entry->size));


    if (mboot->mi_flags & (1 << 3)) // Module
    {
        modules = (struct multiboot_module *)mboot->mods_addr;
        module_count = mboot->mods_count;
    }
    else
    {
        modules = NULL;
        module_count = 0;
    }


    return true;
}


const char *get_kernel_command_line(void)
{
    return (const char *)mboot->cmdline;
}


int memmap_length(void)
{
    return mmap_length;
}


void get_memmap_info(int index, bool *usable, uintptr_t *start, size_t *length)
{
    if ((index < 0) || (index >= mmap_length))
        goto unusable;


    struct memory_map *entry = mmap;

    while (index--)
        entry = (struct memory_map *)((uintptr_t)entry + entry->size + sizeof(entry->size));


    if (entry->base >> 32)
        goto unusable;


    *usable = (entry->type == 1);
    *start  = (uintptr_t)entry->base;

    *length = (entry->length >> 32) ? 0xFFFFFFFF : (size_t)entry->length;

    return;


unusable:
    *usable = false;
    *start = 0;
    *length = 0;
}


void get_kernel_dim(uintptr_t *start, uintptr_t *end)
{
    *start = 0; // Wer braucht schon Lower Memory

    uintptr_t e = (uintptr_t)&__kernel_elf_end;

    for (int i = 0; i < module_count; i++)
        if (modules[i].mod_end > e)
            e = modules[i].mod_end;

    if ((uintptr_t)(mmap + mmap_length) > e)
        e = (uintptr_t)(mmap + mmap_length);

    if ((uintptr_t)(modules + module_count) > e)
        e = (uintptr_t)(modules + module_count);

    *end = e;
}
