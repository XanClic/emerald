#include <ruby_env.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/value.h"


extern void *mboot;


static void init(mrb_state *mrbs)
{
    mrb_define_const(mrbs, mrbs->object_class, "MBOOT", mrb_fixnum_value((mrb_int)mboot));
}


RUBY_ENV_INIT(init)
