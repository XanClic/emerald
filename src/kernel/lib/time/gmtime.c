#include <time.h>

struct tm *gmtime(const time_t *t)
{
    static struct tm _tm;

    return gmtime_r(t, &_tm);
}
