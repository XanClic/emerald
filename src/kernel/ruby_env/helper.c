#include <kassert.h>
#include <ruby_env.h>
#include <stdlib.h>

#include "mruby.h"
#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/value.h"


static mrb_value h_asc(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    char *str;
    int len;
    mrb_get_args(mrbs, "s", &str, &len);

    kassert(len > 0);

    return mrb_fixnum_value(str[0]);
}


static mrb_value h_load(mrb_state *mrbs, mrb_value self)
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


static mrb_value h_malloc(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int sz;
    mrb_get_args(mrbs, "i", &sz);

    return mrb_fixnum_value((mrb_int)malloc(sz));
}


static mrb_value h_free(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int ptr;
    mrb_get_args(mrbs, "i", &ptr);

    free((void *)ptr);

    return mrb_nil_value();
}


static void init(mrb_state *mrbs)
{
    mrb_define_method(mrbs, mrbs->object_class, "asc",    h_asc,    ARGS_REQ(1));
    mrb_define_method(mrbs, mrbs->object_class, "load",   h_load,   ARGS_REQ(1));
    mrb_define_method(mrbs, mrbs->object_class, "malloc", h_malloc, ARGS_REQ(1));
    mrb_define_method(mrbs, mrbs->object_class, "free",   h_free,   ARGS_REQ(1));
}


RUBY_ENV_INIT(init)
