#include <kassert.h>
#include <ruby_env.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/value.h"


static mrb_value asc(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    char *str;
    int len;
    mrb_get_args(mrbs, "s", &str, &len);

    kassert(len > 0);

    return mrb_fixnum_value(str[0]);
}


static void init(mrb_state *mrbs)
{
    struct RClass *helper = mrb_define_module(mrbs, "Helper");

    mrb_define_class_method(mrbs, helper, "asc", asc, ARGS_REQ(1));
}



RUBY_ENV_INIT(init)
