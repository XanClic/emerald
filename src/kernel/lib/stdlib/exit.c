#include <stdlib.h>
#include <stdnoreturn.h>


noreturn void exit(int status)
{
    (void)status;
    for (;;);
}
