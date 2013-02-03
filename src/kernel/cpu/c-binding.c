#include <cpu-state.h>
#include <emerg.h>
#include <stddef.h>
#include <stdint.h>

#include "mruby.h"


extern struct mrb_state *mrbs;


struct cpu_state *i386_common_isr(struct cpu_state *state)
{
    state = (struct cpu_state *)mrb_fixnum(mrb_funcall(mrbs, mrb_nil_value(), "interrupt", 1, mrb_fixnum_value((uintptr_t)state)));

    if (mrbs->exc != NULL)
        emerg(mrbs, mrb_obj_value(mrbs->exc));

    return state;
}


void i386_syscall(struct cpu_state *state)
{
    (void)state;
}
