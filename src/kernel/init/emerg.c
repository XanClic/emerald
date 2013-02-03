#include <emerg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/proc.h"
#include "mruby/string.h"
#include "mruby/variable.h"


static void emerg_puts(const char *str)
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
    emerg_puts("FATAL (ruby exception)\n\n");

    mrb_value str = mrb_funcall(mrbs, exc, "message", 0);
    emerg_puts(mrb_string_value_cstr(mrbs, &str));

    emerg_puts("\n\nBacktrace:\n");

    // Taken from mruby itself.
    mrb_int ciidx = mrb_fixnum(mrb_obj_iv_get(mrbs, mrbs->exc, mrb_intern(mrbs, "ciidx")));
    if (ciidx >= mrbs->ciend - mrbs->cibase)
        ciidx = 10; /* ciidx is broken... */

    for (int i = ciidx; i >= 0; i--) {
        mrb_callinfo *ci = &mrbs->cibase[i];

        if (MRB_PROC_CFUNC_P(ci->proc)) {
            continue;
        }

        const char *sep;
        if (ci->target_class == ci->proc->target_class)
            sep = ".";
        else
            sep = "#";

        const char *method = mrb_sym2name(mrbs, ci->mid);
        if (method) {
            const char *cn = mrb_class_name(mrbs, ci->proc->target_class);

            if (cn) {
                emerg_puts("    in ");
                emerg_puts(cn);
                emerg_puts(sep);
                emerg_puts(method);
                emerg_puts("\n");
            }
            else {
                emerg_puts("    in ");
                emerg_puts(method);
                emerg_puts("\n");
            }
        }
        else {
            emerg_puts("    (unknown)\n");
        }
    }

    for (;;)
        __asm__ __volatile__ ("cli;hlt");
}
