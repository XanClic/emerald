#include <ruby_env.h>
#include <stdint.h>
#include <string.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/value.h"


#define def_memory_peek(width) \
    static mrb_value memory_peek##width(mrb_state *mrbs, mrb_value self) \
    { \
        (void)self; \
        \
        mrb_int address; \
        mrb_get_args(mrbs, "i", &address); \
        \
        return mrb_fixnum_value(*((uint##width##_t *)address)); \
    }

#define def_memory_poke(width) \
    static mrb_value memory_poke##width(mrb_state *mrbs, mrb_value self) \
    { \
        (void)self; \
        \
        mrb_int address, value; \
        mrb_get_args(mrbs, "ii", &address, &value); \
        \
        *(uint##width##_t *)address = value; \
        \
        return mrb_nil_value(); \
    }

def_memory_peek(8)
def_memory_poke(8)
def_memory_peek(16)
def_memory_poke(16)
def_memory_poke(32)
def_memory_peek(64)
def_memory_poke(64)

    static mrb_value memory_peek32(mrb_state *mrbs, mrb_value self)
    {
        (void)self;
        mrb_int address;
        mrb_get_args(mrbs, "i", &address);
        return mrb_fixnum_value(*((uint32_t *)address));
    }

static mrb_value memory_cstr(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address;
    mrb_get_args(mrbs, "i", &address);

    return mrb_str_new_cstr(mrbs, (const char *)address);
}

static mrb_value memory_memset(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address, c, size;
    mrb_get_args(mrbs, "iii", &address, &c, &size);

    return mrb_fixnum_value((uintptr_t)memset((void *)address, c, size));
}

static mrb_value memory_memmove(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int dst, src, size;
    mrb_get_args(mrbs, "iii", &dst, &src, &size);

    return mrb_fixnum_value((uintptr_t)memmove((void *)dst, (void *)src, size));
}


static void init(mrb_state *mrbs)
{
    struct RClass *memmodule = mrb_define_module(mrbs, "Memory");

    mrb_define_module_function(mrbs, memmodule, "[]",      memory_peek8,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "[]=",     memory_poke8,   ARGS_REQ(2));
    mrb_define_module_function(mrbs, memmodule, "cstr",    memory_cstr,    ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "memset",  memory_memset,  ARGS_REQ(3));
    mrb_define_module_function(mrbs, memmodule, "memmove", memory_memmove, ARGS_REQ(3));


    memmodule = mrb_define_module(mrbs, "Memory8");

    mrb_define_module_function(mrbs, memmodule, "[]",      memory_peek8,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "[]=",     memory_poke8,   ARGS_REQ(1));


    memmodule = mrb_define_module(mrbs, "Memory16");

    mrb_define_module_function(mrbs, memmodule, "[]",      memory_peek16,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "[]=",     memory_poke16,   ARGS_REQ(1));


    memmodule = mrb_define_module(mrbs, "Memory32");

    mrb_define_module_function(mrbs, memmodule, "[]",      memory_peek32,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "[]=",     memory_poke32,   ARGS_REQ(1));


    memmodule = mrb_define_module(mrbs, "Memory64");

    mrb_define_module_function(mrbs, memmodule, "[]",      memory_peek64,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, memmodule, "[]=",     memory_poke64,   ARGS_REQ(1));
}


RUBY_ENV_INIT(init)
