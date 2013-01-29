#include <time.h>

char *asctime(const struct tm *tm)
{
    static char asctime_buf[26];

    return asctime_r(tm, asctime_buf);
}
