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


static void init(mrb_state *mrbs)
{
    struct RClass *x86_mod = mrb_define_module(mrbs, "X86");

    mrb_define_module_function(mrbs, x86_mod, "lgdt", x86_lgdt, ARGS_REQ(3));
}


RUBY_ENV_INIT(init)
