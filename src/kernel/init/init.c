#include <boot.h>
#include <kassert.h>
#include <pmm.h>
#include <stdint.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/compile.h"
#include "mruby/value.h"


static mrb_value memory_peek(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address;
    mrb_get_args(mrbs, "i", &address);

    return mrb_fixnum_value(*((uint8_t *)address));
}

static mrb_value memory_poke(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    mrb_int address, value;
    mrb_get_args(mrbs, "ii", &address, &value);

    *(uint8_t *)address = value;

    return mrb_nil_value();
}


static mrb_value asc(mrb_state *mrbs, mrb_value self)
{
    (void)self;

    char *str;
    int len;
    mrb_get_args(mrbs, "s", &str, &len);

    kassert(len > 0);

    return mrb_fixnum_value(str[0]);
}


void main(void *boot_info)
{
    get_boot_info(boot_info);

    init_pmm();


    uint8_t *blub = (uint8_t *)0xB8000;

    blub[0] = 'X';
    blub[1] = 15;


    mrb_state *mrbs = mrb_open();

    struct RClass *helper = mrb_define_module(mrbs, "Helper");

    mrb_define_class_method(mrbs, helper, "asc", asc, ARGS_REQ(1));

    struct RClass *memclass = mrb_define_class(mrbs, "Memory", mrbs->object_class);

    mrb_define_class_method(mrbs, memclass, "[]",  memory_peek, ARGS_REQ(1));
    mrb_define_class_method(mrbs, memclass, "[]=", memory_poke, ARGS_REQ(2));


    mrb_load_string(mrbs, "class String\n    def asc\n        Helper.asc(self)\n    end\nend\n\nMemory[0xB8000] = 'A'.asc");
}
