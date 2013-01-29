#include <ruby_env.h>

#include "mruby.h"


extern const void ruby_env_start, ruby_env_end;


void init_ruby_environment(mrb_state *mrbs)
{
    void (**func)(mrb_state *) = (void (**)(mrb_state *))(uintptr_t)&ruby_env_start;

    while ((uintptr_t)func < (uintptr_t)&ruby_env_end)
        (*(func++))(mrbs);
}
