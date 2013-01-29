#include <stddef.h>
#include <time.h>
#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    if (tv != NULL)
    {
        tv->tv_sec = time(NULL);
        tv->tv_usec = 0; // TODO
    }
    if (tz != NULL)
    {
        tz->tz_minuteswest = 0;
        tz->tz_dsttime = 0;
    }

    return 0;
}
