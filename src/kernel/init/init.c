#include <boot.h>
#include <pmm.h>
#include <ruby_env.h>
#include <stdnoreturn.h>
#include <stdint.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include "mruby/value.h"


void emerg_puts(const char *str)
{
    static int x = 0, y = 12;

    uint8_t *base = (uint8_t *)0xB8000 + (y * 80 + x) * 2;

    while (*str)
    {
        switch (*str)
        {
            case '\n':
                y++;
                x = 0;
                base = (uint8_t *)0xB8000 + (y * 80 + x) * 2;
                str++;
                break;
            default:
                *(base++) = *(str++);
                *(base++) = 0x4F;
                x++;
                if (x >= 80)
                {
                    x -= 80;
                    y++;
                }
        }
    }
}


noreturn void emerg(mrb_state *mrbs, mrb_value exc)
{
    emerg_puts("FATAL (internal exception)\n\n");

    mrb_value str = mrb_funcall(mrbs, exc, "message", 0);
    emerg_puts(mrb_string_value_cstr(mrbs, &str));

    // mruby doesn't seem to support backtraces so far
    /*
    emerg_puts("\n");

    mrb_value bt_arr = mrb_funcall(mrbs, exc, "backtrace", 0);
    mrb_value bt_str = mrb_funcall(mrbs, bt_arr, "join", 1, mrb_str_new_cstr(mrbs, "\n"));
    emerg_puts(mrb_string_value_cstr(mrbs, &bt_str));
    */

    for (;;)
        __asm__ __volatile__ ("cli;hlt");
}


extern const void _binary_init_rb_start, _binary_init_rb_size;


void main(void *boot_info)
{
    if (!get_boot_info(boot_info))
        return;

    init_pmm();


    mrb_state *mrbs  = mrb_open();

    init_ruby_environment(mrbs);

    mrb_load_nstring(mrbs, &_binary_init_rb_start, (uintptr_t)&_binary_init_rb_size);


    if (mrbs->exc != NULL)
        emerg(mrbs, mrb_obj_value(mrbs->exc));
}
