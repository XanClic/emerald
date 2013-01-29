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

#include <stddef.h>
#include <stdio.h>
#include <time.h>

static const char *weekday_abbr[] =
{
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char *weekday_full[] =
{
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

static const char *month_abbr[] =
{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *month_full[] =
{
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

static void cat(char *s, size_t *o, size_t max, const char *append)
{
    while (*append && (*o < max))
        s[(*o)++] = *(append++);
}

size_t strftime(char *s, size_t max, const char *format, const struct tm *tm)
{
    size_t o = 0;
    char some_buf[64];

    max--; // Nullbyte

    while ((o < max) && *format)
    {
        if (*format != '%')
            s[o++] = *(format++);
        else
        {
            format++;
            while ((*format == 'E') || (*format == 'O'))
                format++;

            switch (*(format++))
            {
                case 'a':
                    cat(s, &o, max, weekday_abbr[tm->tm_wday]);
                    break;
                case 'A':
                    cat(s, &o, max, weekday_full[tm->tm_wday]);
                    break;
                case 'b':
                case 'h':
                    cat(s, &o, max, month_abbr[tm->tm_mon]);
                    break;
                case 'B':
                    cat(s, &o, max, month_full[tm->tm_mon]);
                    break;
                case 'c':
                    sprintf(some_buf, "%02i.%02i.%04i %02i:%02i", tm->tm_mday, tm->tm_mon, tm->tm_year, tm->tm_hour, tm->tm_min);
                    cat(s, &o, max, some_buf);
                    break;
                case 'C':
                    sprintf(some_buf, "%02i", tm->tm_year / 100);
                    cat(s, &o, max, some_buf);
                    break;
                case 'd':
                    sprintf(some_buf, "%02i", tm->tm_mday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'D':
                    sprintf(some_buf, "%02i/%02i/%02i", tm->tm_mon, tm->tm_mday, tm->tm_year % 100);
                    cat(s, &o, max, some_buf);
                    break;
                case 'e':
                    sprintf(some_buf, "%2i", tm->tm_mday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'F':
                    sprintf(some_buf, "%04i-%02i-%02i", tm->tm_year, tm->tm_mon, tm->tm_mday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'H':
                    sprintf(some_buf, "%02i", tm->tm_hour);
                    cat(s, &o, max, some_buf);
                    break;
                case 'I':
                    sprintf(some_buf, "%02i", !(tm->tm_hour % 12) ? 12 : (tm->tm_hour % 12));
                    cat(s, &o, max, some_buf);
                    break;
                case 'j':
                    sprintf(some_buf, "%03i", tm->tm_yday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'k':
                    sprintf(some_buf, "%2i", tm->tm_hour);
                    cat(s, &o, max, some_buf);
                    break;
                case 'l':
                    sprintf(some_buf, "%2i", !(tm->tm_hour % 12) ? 12 : (tm->tm_hour % 12));
                    cat(s, &o, max, some_buf);
                    break;
                case 'm':
                    sprintf(some_buf, "%02i", tm->tm_mon);
                    cat(s, &o, max, some_buf);
                    break;
                case 'M':
                    sprintf(some_buf, "%02i", tm->tm_min);
                    cat(s, &o, max, some_buf);
                    break;
                case 'n':
                    cat(s, &o, max, "\n");
                    break;
                case 'p':
                    cat(s, &o, max, (tm->tm_hour < 12) ? "AM" : "PM");
                    break;
                case 'P':
                    cat(s, &o, max, (tm->tm_hour < 12) ? "am" : "pm");
                    break;
                case 'r':
                    sprintf(some_buf, "%02i:%02i:%02i %s", !(tm->tm_hour % 12) ? 12 : (tm->tm_hour % 12), tm->tm_min, tm->tm_sec, (tm->tm_hour < 12) ? "AM" : "PM");
                    cat(s, &o, max, some_buf);
                    break;
                case 'R':
                    sprintf(some_buf, "%02i:%02i", tm->tm_hour, tm->tm_min);
                    cat(s, &o, max, some_buf);
                    break;
                case 's':
                    cat(s, &o, max, "<unixtime goes here>"); // TODO
                    break;
                case 'S':
                    sprintf(some_buf, "%02i", tm->tm_sec);
                    cat(s, &o, max, some_buf);
                    break;
                case 't':
                    cat(s, &o, max, "\t");
                    break;
                case 'T':
                    sprintf(some_buf, "%02i:%02i:%02i", tm->tm_hour, tm->tm_min, tm->tm_sec);
                    cat(s, &o, max, some_buf);
                    break;
                case 'u':
                    sprintf(some_buf, "%i", !tm->tm_wday ? 7 : tm->tm_wday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'w':
                    sprintf(some_buf, "%i", tm->tm_wday);
                    cat(s, &o, max, some_buf);
                    break;
                case 'x':
                    sprintf(some_buf, "%02i.%02i.%04i", tm->tm_mday, tm->tm_mon, tm->tm_year);
                    cat(s, &o, max, some_buf);
                    break;
                case 'X':
                    sprintf(some_buf, "%02i:%02i", tm->tm_hour, tm->tm_min);
                    cat(s, &o, max, some_buf);
                    break;
                case 'y':
                    sprintf(some_buf, "%02i", tm->tm_year % 100);
                    cat(s, &o, max, some_buf);
                    break;
                case 'Y':
                    sprintf(some_buf, "%04i", tm->tm_year);
                    cat(s, &o, max, some_buf);
                    break;
                case 'z':
                    cat(s, &o, max, "+0000");
                    break;
                case 'Z':
                    cat(s, &o, max, "UTC");
                    break;
                case '%':
                    cat(s, &o, max, "%");
                    break;
                default:
                    sprintf(some_buf, "%%%c", format[-1]);
                    cat(s, &o, max, some_buf);
            }
        }
    }

    if (o >= max)
        return 0;

    s[o] = 0;
    return o;
}
