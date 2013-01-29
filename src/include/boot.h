#ifndef _BOOT_H
#define _BOOT_H

#include <stdbool.h>


bool get_boot_info(void *info);
const char *get_kernel_command_line(void);

#endif
