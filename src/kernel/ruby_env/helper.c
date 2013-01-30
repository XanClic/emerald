#include <kassert.h>
#include <ruby_env.h>

#include "mruby.h"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/compile.h"
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


static mrb_value load(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_value name;
    mrb_get_args(mrbs, "S", &name);

    mrb_value ret = mrb_funcall(mrbs, mrb_nil_value(), "load_file_find", 1, name);

    if (mrb_nil_p(ret))
    {
        mrb_raise(mrbs, mrbs->eException_class, "Could not find file to be loaded.");
        return mrb_nil_value();
    }

    mrb_int len = mrb_fixnum(mrb_ary_pop(mrbs, ret));
    mrb_int ptr = mrb_fixnum(mrb_ary_pop(mrbs, ret));

    return mrb_load_nstring(mrbs, (const char *)ptr, len);
}


static mrb_value give(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    char *string;
    mrb_get_args(mrbs, "z", &string);

    char *out = (char *)0xb8000;
    while (*string)
    {
        *(out++) = *(string++);
        *(out++) = 15;
    }

    return mrb_nil_value();
}


static void init(mrb_state *mrbs)
{
    struct RClass *helper = mrb_define_module(mrbs, "Helper");

    mrb_define_class_method(mrbs, helper, "asc",  asc,  ARGS_REQ(1));


    mrb_define_method(mrbs, mrbs->object_class, "load", load, ARGS_REQ(1));
    mrb_define_method(mrbs, mrbs->object_class, "give", give, ARGS_REQ(1));
}


RUBY_ENV_INIT(init)
