/************************************************************************
 * Copyright (C) 2009 by Hanna Reitz                                    *
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

#ifndef _CTYPE_H
#define _CTYPE_H

static inline int isalnum(int c) __attribute__((pure, unused));
static inline int isalpha(int c) __attribute__((pure, unused));
static inline int isascii(int c) __attribute__((pure, unused));
static inline int isblank(int c) __attribute__((pure, unused));
static inline int iscntrl(int c) __attribute__((pure, unused));
static inline int isdigit(int c) __attribute__((pure, unused));
static inline int isgraph(int c) __attribute__((pure, unused));
static inline int islower(int c) __attribute__((pure, unused));
static inline int isprint(int c) __attribute__((pure, unused));
static inline int ispunct(int c) __attribute__((pure, unused));
static inline int isspace(int c) __attribute__((pure, unused));
static inline int isupper(int c) __attribute__((pure, unused));
static inline int isxdigit(int c) __attribute__((pure, unused));
static inline int tolower(int c) __attribute__((pure, unused));
static inline int toupper(int c) __attribute__((pure, unused));

static inline int isalnum(int c)
{
    return !!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')));
}

static inline int isalpha(int c)
{
    return !!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

static inline int isascii(int c)
{
    return !!((c >= 0) && (c <= 127));
}

static inline int isblank(int c)
{
    return !!((c == ' ') || (c == '\t'));
}

static inline int iscntrl(int c)
{
    return !!(((c >= 0) && (c <= 0x1F)) || (c == 0x7F));
}

static inline int isdigit(int c)
{
    return !!((c >= '0') && (c <= '9'));
}

static inline int isgraph(int c)
{
    return !!(c > ' ');
}

static inline int islower(int c)
{
    return !!((c >= 'a') && (c <= 'z'));
}

static inline int isprint(int c)
{
    return !!(c >= ' ');
}

static inline int ispunct(int c)
{
    return !!((c >= ' ') && !(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9'))));
}

static inline int isspace(int c)
{
    return !!((c == ' ') || (c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v'));
}

static inline int isupper(int c)
{
    return !!((c >= 'A') && (c <= 'Z'));
}

static inline int isxdigit(int c)
{
    return !!(((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F')));
}

static inline int tolower(int c)
{
    if ((c >= 'A') && (c <= 'Z'))
        return c + 32;
    return c;
}

static inline int toupper(int c)
{
    if ((c >= 'a') && (c <= 'z'))
        return c - 32;
    return c;
}

#endif
