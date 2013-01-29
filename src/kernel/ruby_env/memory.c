#include <ruby_env.h>
#include <stdint.h>
#include <string.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/value.h"


static mrb_value memory_peek(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address;
    mrb_get_args(mrbs, "i", &address);

    return mrb_fixnum_value(*((uint8_t *)address));
}

static mrb_value memory_poke(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address, value;
    mrb_get_args(mrbs, "ii", &address, &value);

    *(uint8_t *)address = value;

    return mrb_nil_value();
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
    struct RClass *memclass = mrb_define_class(mrbs, "Memory", mrbs->object_class);

    mrb_define_class_method(mrbs, memclass, "[]",      memory_peek,    ARGS_REQ(1));
    mrb_define_class_method(mrbs, memclass, "[]=",     memory_poke,    ARGS_REQ(2));
    mrb_define_class_method(mrbs, memclass, "memset",  memory_memset,  ARGS_REQ(3));
    mrb_define_class_method(mrbs, memclass, "memmove", memory_memmove, ARGS_REQ(3));
}


RUBY_ENV_INIT(init)
