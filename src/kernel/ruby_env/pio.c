#include <ruby_env.h>
#include <stdint.h>
#include <string.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/string.h"
#include "mruby/value.h"


#define def_pio_in(width) \
    static mrb_value pio_in##width(mrb_state *mrbs, mrb_value self) \
    { \
        (void)self; \
        \
        mrb_int port; \
        mrb_get_args(mrbs, "i", &port); \
        \
        uint##width##_t val; \
        __asm__ __volatile__ ("in %1,%0" : "=a"(val) : "d"((uint16_t)port)); \
        \
        return mrb_fixnum_value(val); \
    }

#define def_pio_out(width) \
    static mrb_value pio_out##width(mrb_state *mrbs, mrb_value self) \
    { \
        (void)self; \
        \
        mrb_int port, val; \
        mrb_get_args(mrbs, "ii", &port, &val); \
        \
        __asm__ __volatile__ ("out %0,%1" :: "a"((uint##width##_t)val), "d"((uint16_t)port)); \
        \
        return mrb_nil_value(); \
    }

def_pio_in(8)
def_pio_out(8)
def_pio_in(16)
def_pio_out(16)
def_pio_in(32)
def_pio_out(32)


static void init(mrb_state *mrbs)
{
    struct RClass *piomodule = mrb_define_module(mrbs, "PIO8");

    mrb_define_module_function(mrbs, piomodule, "[]",  pio_in8,   ARGS_REQ(1));
    mrb_define_module_function(mrbs, piomodule, "[]=", pio_out8,  ARGS_REQ(1));


    piomodule = mrb_define_module(mrbs, "PIO16");

    mrb_define_module_function(mrbs, piomodule, "[]",  pio_in16,  ARGS_REQ(1));
    mrb_define_module_function(mrbs, piomodule, "[]=", pio_out16, ARGS_REQ(1));


    piomodule = mrb_define_module(mrbs, "PIO32");

    mrb_define_module_function(mrbs, piomodule, "[]",  pio_in32,  ARGS_REQ(1));
    mrb_define_module_function(mrbs, piomodule, "[]=", pio_out32, ARGS_REQ(1));
}


RUBY_ENV_INIT(init)
