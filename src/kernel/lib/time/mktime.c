/************************************************************************
 * Copyright (C) 2011 by Hanna Reitz                                    *
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

#include <time.h>

static inline int is_leap_year(int year)
{
    return !(year % 4) && ((year % 100) || !(year % 400));
}

time_t mktime(struct tm *tm)
{
    time_t result = tm->tm_sec + (tm->tm_min + (tm->tm_hour + (tm->tm_yday * 24)) * 60) * 60;

    int year = tm->tm_year;
    while (year-- > 1970)
        result += is_leap_year(year) ? (366 * 86400) : (365 * 86400);

    return result;
}
