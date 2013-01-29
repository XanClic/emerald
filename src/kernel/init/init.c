#include <boot.h>
#include <pmm.h>
#include <ruby_env.h>
#include <stdint.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/value.h"


extern const void _binary_init_rb_start, _binary_init_rb_size;


void main(void *boot_info)
{
    get_boot_info(boot_info);

    init_pmm();


    mrb_state *mrbs = mrb_open();

    init_ruby_environment(mrbs);


    mrb_load_nstring(mrbs, &_binary_init_rb_start, (uintptr_t)&_binary_init_rb_size);
}
