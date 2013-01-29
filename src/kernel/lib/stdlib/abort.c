#include <stdlib.h>
#include <stdnoreturn.h>


noreturn void abort(void)
{
    exit(1);
}
