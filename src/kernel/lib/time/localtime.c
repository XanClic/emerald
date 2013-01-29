#include <time.h>

struct tm *localtime(const time_t *timep)
{
    return gmtime(timep);
}
