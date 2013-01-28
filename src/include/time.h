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

#ifndef _TIME_H
#define _TIME_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

char *asctime(const struct tm *tm);
char *asctime_r(const struct tm *tm, char *buf);
char *ctime(const time_t *timep);
char *ctime_r(const time_t *timep, char *buf);
struct tm *gmtime(const time_t *t);
struct tm *gmtime_r(const time_t *t, struct tm *tm);
struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *timep, struct tm *tm);
time_t mktime(struct tm *tm);
time_t time(time_t *t);
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);

#endif
