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

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

static unsigned long long __stdlib_pow(unsigned long base, unsigned long exp)
{
    unsigned long long rbase = 1;

    while (exp--)
        rbase *= base;
    return rbase;
}

long long strtoll(const char *s, char **endptr, int base)
{
    char sign = 0;
    int pos = 0;
    signed char digit[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    int dpos = 0, digits = 0;
    long long retval = 0;

    if (s[pos] == '+')
        pos++;
    else if (s[pos] == '-')
    {
        sign = 1;
        pos++;
    }
    if (!base)
    {
        if ((s[pos] == '0') && ((s[pos + 1] == 'x') || (s[pos + 1] == 'X')))
        {
            base = 16;
            pos += 2;
        }
        else if (s[pos] == '0')
        {
            base = 8;
            pos++;
        }
        else if (isdigit(s[pos]))
            base = 10;
        else
        {
            if (endptr)
                *endptr = (char *)s;
            return 0;
        }
    }
    // FIXME: ERANGE
    while (isalnum(s[pos]))
    {
        if (isdigit(s[pos]))
            digit[dpos] = s[pos++] - '0';
        else if (islower(s[pos]))
            digit[dpos] = s[pos++] + 10 - 'a';
        else
            digit[dpos] = s[pos++] + 10 - 'A';
        if (digit[dpos] >= base)
        {
            digit[dpos] = -1;
            pos--;
            break;
        }
        dpos++;
    }
    if (endptr)
        *endptr = (char *)&s[pos];
    for (dpos = 0; digit[dpos] >= 0; dpos++, digits++);
        for (dpos = 0; dpos < digits; dpos++)
            retval += __stdlib_pow(base, digits - (dpos + 1)) * digit[dpos];
    if (sign)
        retval *= -1;
    return retval;
}

unsigned long strtoul(const char *s, char **endptr, int base)
{
    // FIXME: ERANGE
    return (unsigned long)strtoul(s, endptr, base);
}

long strtol(const char *s, char **endptr, int base)
{
    // FIXME: ERANGE
    return (long)strtoll(s, endptr, base);
}
