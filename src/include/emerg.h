#ifndef _EMERG_H
#define _EMERG_H

#include <stdnoreturn.h>

#include "mruby.h"


noreturn void emerg(mrb_state *mrbs, mrb_value exc);

#endif
