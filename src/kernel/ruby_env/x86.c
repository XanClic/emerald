#include <ruby_env.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/value.h"


static mrb_value x86_lgdt(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address, code, data;
    mrb_get_args(mrbs, "iii", &address, &code, &data);

    __asm__ __volatile__ ("push %1;"
                          "pushl $.1;"
                          "lgdt (%0);"
                          "retf;"
                          ".1:;"
                          "mov %2,%%ss;"
                          "mov %2,%%ds;"
                          "mov %2,%%es;"
                          "mov %2,%%fs;"
                          "mov %2,%%gs"
                          :: "b"(address), "a"(code), "d"(data) : "memory");

    return mrb_nil_value();
}


static mrb_value x86_lidt(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address;
    mrb_get_args(mrbs, "i", &address);

    __asm__ __volatile__ ("lidt (%0)" :: "r"(address) : "memory");

    return mrb_nil_value();
}


#define INTR_CASE(num) case num: handler = int_stub_##num; break;
#define INTR_FUNC(num) extern void int_stub_##num(void);

INTR_FUNC(0x00)
INTR_FUNC(0x01)
INTR_FUNC(0x02)
INTR_FUNC(0x03)
INTR_FUNC(0x04)
INTR_FUNC(0x05)
INTR_FUNC(0x06)
INTR_FUNC(0x07)
INTR_FUNC(0x08)
INTR_FUNC(0x09)
INTR_FUNC(0x0a)
INTR_FUNC(0x0b)
INTR_FUNC(0x0c)
INTR_FUNC(0x0d)
INTR_FUNC(0x0e)
INTR_FUNC(0x0f)
INTR_FUNC(0x10)
INTR_FUNC(0x11)
INTR_FUNC(0x12)
INTR_FUNC(0x13)
INTR_FUNC(0x14)
INTR_FUNC(0x15)
INTR_FUNC(0x16)
INTR_FUNC(0x17)
INTR_FUNC(0x18)
INTR_FUNC(0x19)
INTR_FUNC(0x1a)
INTR_FUNC(0x1b)
INTR_FUNC(0x1c)
INTR_FUNC(0x1d)
INTR_FUNC(0x1e)
INTR_FUNC(0x1f)
INTR_FUNC(0x20)
INTR_FUNC(0x21)
INTR_FUNC(0x22)
INTR_FUNC(0x23)
INTR_FUNC(0x24)
INTR_FUNC(0x25)
INTR_FUNC(0x26)
INTR_FUNC(0x27)
INTR_FUNC(0x28)
INTR_FUNC(0x29)
INTR_FUNC(0x2a)
INTR_FUNC(0x2b)
INTR_FUNC(0x2c)
INTR_FUNC(0x2d)
INTR_FUNC(0x2e)
INTR_FUNC(0x2f)
INTR_FUNC(0xa2)

static mrb_value x86_iha(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int intr;
    mrb_get_args(mrbs, "i", &intr);

    void (*handler)(void) = NULL;
    switch (intr)
    {
        INTR_CASE(0x00)
        INTR_CASE(0x01)
        INTR_CASE(0x02)
        INTR_CASE(0x03)
        INTR_CASE(0x04)
        INTR_CASE(0x05)
        INTR_CASE(0x06)
        INTR_CASE(0x07)
        INTR_CASE(0x08)
        INTR_CASE(0x09)
        INTR_CASE(0x0a)
        INTR_CASE(0x0b)
        INTR_CASE(0x0c)
        INTR_CASE(0x0d)
        INTR_CASE(0x0e)
        INTR_CASE(0x0f)
        INTR_CASE(0x10)
        INTR_CASE(0x11)
        INTR_CASE(0x12)
        INTR_CASE(0x13)
        INTR_CASE(0x20)
        INTR_CASE(0x21)
        INTR_CASE(0x22)
        INTR_CASE(0x23)
        INTR_CASE(0x24)
        INTR_CASE(0x25)
        INTR_CASE(0x26)
        INTR_CASE(0x27)
        INTR_CASE(0x28)
        INTR_CASE(0x29)
        INTR_CASE(0x2a)
        INTR_CASE(0x2b)
        INTR_CASE(0x2c)
        INTR_CASE(0x2d)
        INTR_CASE(0x2e)
        INTR_CASE(0x2f)
        INTR_CASE(0xa2)
    }

    return mrb_fixnum_value((uintptr_t)handler);
}


static mrb_value x86_sti(mrb_state *mrbs, mrb_value self)
{
    (void)mrbs;
    (void)self;

    __asm__ __volatile__ ("sti");

    return mrb_nil_value();
}


static mrb_value x86_hlt(mrb_state *mrbs, mrb_value self)
{
    (void)mrbs;
    (void)self;

    __asm__ __volatile__ ("hlt");

    return mrb_nil_value();
}


static mrb_value x86_cr2(mrb_state *mrbs, mrb_value self)
{
    (void)mrbs;
    (void)self;

    uint32_t ret;
    __asm__ __volatile__ ("mov %%cr2,%0" : "=r"(ret));

    return mrb_fixnum_value(ret);
}


static mrb_value x86_cr3(mrb_state *mrbs, mrb_value self)
{
    (void)mrbs;
    (void)self;

    uint32_t ret;
    __asm__ __volatile__ ("mov %%cr3,%0" : "=r"(ret));

    return mrb_fixnum_value(ret);
}


static void init(mrb_state *mrbs)
{
    struct RClass *x86_mod = mrb_define_module(mrbs, "X86");

    mrb_define_module_function(mrbs, x86_mod, "lgdt",              x86_lgdt, ARGS_REQ(3));
    mrb_define_module_function(mrbs, x86_mod, "lidt",              x86_lidt, ARGS_REQ(1));
    mrb_define_module_function(mrbs, x86_mod, "intr_handler_addr", x86_iha,  ARGS_REQ(1));
    mrb_define_module_function(mrbs, x86_mod, "sti",               x86_sti,  ARGS_REQ(0));
    mrb_define_module_function(mrbs, x86_mod, "hlt",               x86_hlt,  ARGS_REQ(0));
    mrb_define_module_function(mrbs, x86_mod, "cr2",               x86_cr2,  ARGS_REQ(0));
    mrb_define_module_function(mrbs, x86_mod, "cr3",               x86_cr3,  ARGS_REQ(0));
}


RUBY_ENV_INIT(init)
