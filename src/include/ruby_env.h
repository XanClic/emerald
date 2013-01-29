#ifndef _RUBY_ENV_H
#define _RUBY_ENV_H

#include "mruby.h"


#define RUBY_ENV_INIT(func) static void (*__attribute__((used, section("ruby_env"))) __fnc)(mrb_state *) = func;


void init_ruby_environment(mrb_state *mrbs);

#endif
