#include <boot.h>
#include <pmm.h>
#include <ruby_env.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <stdint.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/proc.h"
#include "mruby/string.h"
#include "mruby/value.h"
#include "mruby/variable.h"


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


void emerg_puti(int i)
{
    int outi = 12;
    char out[outi];

    out[--outi] = 0;

    bool negative = (i < 0);
    if (i < 0)
        i = -i;

    while (i)
    {
        out[--outi] = i % 10 + '0';
        i /= 10;
    }

    if (negative)
        out[--outi] = '-';

    emerg_puts(&out[outi]);
}


noreturn void emerg(mrb_state *mrbs, mrb_value exc)
{
    emerg_puts("FATAL (internal exception)\n\n");

    mrb_value str = mrb_funcall(mrbs, exc, "message", 0);
    emerg_puts(mrb_string_value_cstr(mrbs, &str));

    emerg_puts("\n\nBacktrace:\n");

    // Taken from mruby itself.
    mrb_int ciidx = mrb_fixnum(mrb_obj_iv_get(mrbs, mrbs->exc, mrb_intern(mrbs, "ciidx")));
    if (ciidx >= mrbs->ciend - mrbs->cibase)
        ciidx = 10; /* ciidx is broken... */

    for (int i = ciidx; i >= 0; i--) {
        mrb_callinfo *ci = &mrbs->cibase[i];
        const char *filename = "(unknown)";
        int line = -1;

        if (MRB_PROC_CFUNC_P(ci->proc)) {
            continue;
        }
        else {
            mrb_irep *irep = ci->proc->body.irep;
            if (irep->filename != NULL)
                filename = irep->filename;
            if (irep->lines != NULL) {
                mrb_code *pc;

                if (i+1 <= ciidx) {
                    pc = mrbs->cibase[i+1].pc;
                }
                else {
                    pc = (mrb_code*)mrb_voidp(mrb_obj_iv_get(mrbs, mrbs->exc, mrb_intern(mrbs, "lastpc")));
                }
                if (irep->iseq <= pc && pc < irep->iseq + irep->ilen) {
                    line = irep->lines[pc - irep->iseq - 1];
                }
            }
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
