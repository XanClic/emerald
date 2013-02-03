#include <boot.h>
#include <pmm.h>
#include <ruby_env.h>
#include <stddef.h>
#include <stdint.h>

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"


extern const void _binary_init_rb_start, _binary_init_rb_size;

struct mrb_state *mrbs;


void main(void *boot_info)
{
    if (!get_boot_info(boot_info))
        return;

    init_pmm();


    mrbs = mrb_open();

    init_ruby_environment(mrbs);

    mrb_load_nstring(mrbs, &_binary_init_rb_start, (uintptr_t)&_binary_init_rb_size);


    if (mrbs->exc != NULL)
        emerg(mrbs, mrb_obj_value(mrbs->exc));


    __asm__ __volatile__ ("sti");

    for (;;)
        __asm__ __volatile__ ("hlt");
}
