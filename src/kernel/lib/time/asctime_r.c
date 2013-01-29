#include <time.h>

char *asctime_r(const struct tm *tm, char *buf)
{
    strftime(buf, 26, "%a %b %d %H:%M:%S %Y\n", tm);

    return buf;
}
