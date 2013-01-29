#include <stddef.h>
#include <stdio.h>

#include "mruby.h"


extern mrb_state *pmrbs;


FILE *fopen(const char *path, const char *mode)
{
    mrb_value ret = mrb_funcall_argv(pmrbs, mrb_nil_value(), mrb_intern(pmrbs, "fopen"), 2,
                                     (mrb_value[]){ mrb_str_new_cstr(pmrbs, path), mrb_str_new_cstr(pmrbs, mode) });

    return (FILE *)mrb_fixnum(ret);
}
