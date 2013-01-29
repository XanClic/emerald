/************************************************************************
 * Copyright (C) 2010 by Hanna Reitz                                    *
 * xanclic@googlemail.com                                               *
 *                                                                      *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the  Free Software Foundation;  either version 2 of the License,  or *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program  is  distributed  in the hope  that it will  be useful, *
 * but  WITHOUT  ANY  WARRANTY;  without even the  implied  warranty of *
 * MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the  GNU  General  Public License *
 * along with this program; if not, write to the                        *
 * Free Software Foundation, Inc.,                                      *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.            *
 ************************************************************************/

#include <stdint.h>
#include <time.h>

static const int month_start[12] =
{
    0,
    31,
    31 + 28,
    31 + 28 + 31,
    31 + 28 + 31 + 30,
    31 + 28 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30
};

static const int leaped_month_start[12] =
{
    0,
    31,
    31 + 29,
    31 + 29 + 31,
    31 + 29 + 31 + 30,
    31 + 29 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30
};

static inline int is_leap_year(int year)
{
    return !(year % 4) && ((year % 100) || !(year % 400));
}

struct tm *gmtime_r(const time_t *t, struct tm *result)
{
    int year = 1970;
    int month = 0;

    result->tm_sec = *t % 60;
    result->tm_min = (*t / 60) % 60;
    result->tm_hour = (*t / 3600) % 24;

    int64_t day = *t / 86400;
    // 1.1.1970 == Donnerstag
    result->tm_wday = (day + 4) % 7;

    while (day > 365)
        day -= 365 + is_leap_year(year++);
    if (!is_leap_year(year) && (day == 365))
    {
        day = 0;
        year++;
    }

    result->tm_year = year;
    result->tm_yday = day;
    if (is_leap_year(year))
    {
        while (day >= leaped_month_start[month + 1])
            month++;
        result->tm_mday = day +  1 - leaped_month_start[month];
    }
    else
    {
        while (day >= month_start[month + 1])
            month++;
        result->tm_mday = day + 1 - month_start[month];
    }
    result->tm_mon = month;

    result->tm_isdst = -1;

    return result;
}
