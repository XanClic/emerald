/************************************************************************
 * Copyright (C) 1991, 1992  Linus Torvalds                             *
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
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

///Die folgenden drei Funktionen stammen größtenteils von Linux 0.99.15 und
///wurden ein wenig modifiziert (z. B. zur Anzeige von doubles, daher gehört
///float_number nicht dazu)
///Copyrighthinweis:
/*
 *  linux/kernel/vsprintf.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/* vsprintf.c -- Lars Wirzenius & Linus Torvalds. */
/*
 * Wirzenius wrote this portably, Torvalds fucked it up :-)
 */
///In der COPYING steht die GPL als Lizenz.
static int skip_atoi(const char **s)
{
    int i=0;

    while (isdigit(**s))
        i = i*10 + *((*s)++) - '0';
    return i;
}

static char *number(char *str, long long num, int base, int size, int precision, int type, size_t *osize, size_t n)
{
    char c, sign, tmp[66];
    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    int i;

    if (type & 0x40)
        digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (type & 0x10)
        type &= 0xFE;
    if ((base < 2) || (base > 36))
        return NULL;
    c = (type & 0x01) ? '0' : ' ';
    sign = 0;
    if (type & 0x02)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
            size--;
        }
        else if (type & 0x04)
        {
            sign = '+';
            size--;
        }
        else if (type & 0x08)
        {
            sign = ' ';
            size--;
        }
    }
    if (type & 0x20)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
        tmp[i++]='0';
    else
    {
        while (num != 0)
        {
            unsigned long long __res;
            __res = ((unsigned long long)num) % (unsigned int)base;
            num = ((unsigned long long)num) / (unsigned int)base;
            tmp[i++] = digits[__res];
        }
    }
    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & 0x11))
        while(size-- > 0)
            if ((*osize)++ < n)
                *(str++) = ' ';
    if (sign)
        if ((*osize)++ < n)
            *(str++) = sign;
    if (type & 0x20)
    {
        if (base == 8)
        {
            if ((*osize)++ < n)
                *(str++) = '0';
        }
        else if (base == 16)
        {
            if ((*osize)++ < n)
                *(str++) = '0';
            if ((*osize)++ < n)
                *(str++) = digits[33];
        }
    }
    if (!(type & 0x10))
        while (size-- > 0)
            if ((*osize)++ < n)
                *(str++) = c;
    while (i < precision--)
        if ((*osize)++ < n)
            *(str++) = '0';
    while (i-- > 0)
        if ((*osize)++ < n)
            *(str++) = tmp[i];
    while (size-- > 0)
        if ((*osize)++ < n)
            *(str++) = ' ';
    return str;
}

#define put(c) do { if ((*osize)++ < n) *(str++) = (c); } while (0)

static long double exp_table[10] =
{
    1e0l,
    1e1l,
    1e2l,
    1e3l,
    1e4l,
    1e5l,
    1e6l,
    1e7l,
    1e8l,
    1e9l
};

static char *float_number(char *str, long double num, int precision, int flags, size_t *osize, size_t n)
{
    bool uppercase = !!(flags & 0x400);
    bool adjust_precision = false;

    if (precision == -1)
        precision = 6;

    if (isnan(num))
    {
        put(uppercase ? 'N' : 'n');
        put(uppercase ? 'A' : 'a');
        put(uppercase ? 'N' : 'n');
        return str;
    }

    if (num < 0)
    {
        put('-');
        num *= -1;
    }
    else if (flags & 0x04)
        put('+');
    else if (flags & 0x08)
        put(' ');

    if (isinf(num))
    {
        put(uppercase ? 'I' : 'i');
        put(uppercase ? 'N' : 'n');
        put(uppercase ? 'F' : 'f');
        return str;
    }

    if ((flags & 0x300) == 0x300)
    {
        flags &= ~0x300;
        if ((num < 1e-4l) || (num >= exp_table[precision]))
            flags |= 0x200;
        else
            flags |= 0x100;

        adjust_precision = true;
    }

    if (flags & 0x100)
    {
        int number_of_digits = 0;

        while (num >= 1.l)
        {
            num /= 10.l;
            number_of_digits++;
        }

        if (!number_of_digits)
            put('0');
        else
        {
            while (number_of_digits--)
            {
                num *= 10.l;

                if (!adjust_precision)
                    put((int)num + '0');
                else
                {
                    if (--precision < 0)
                        put('0');
                    else
                        put((int)num + '0');
                }

                num -= (int)num;
            }

            if (precision < 0)
                precision = 0;
        }

        if (precision && num)
            put('.');

        while (precision-- && num)
        {
            num *= 10.l;
            put((int)num + '0');
            num -= (int)num;
        }
    }
    else
    {
        if (!num)
        {
            put('0');
            return str;
        }

        int exponent = 0;

        while (num < 1.l)
        {
            num *= 10.l;
            exponent--;
        }

        while (num >= 10.l)
        {
            num /= 10.l;
            exponent++;
        }

        put((int)num + '0');
        num -= (int)num;

        if (adjust_precision)
            precision--;

        if (precision && num)
            put('.');

        while (precision-- && num)
        {
            num *= 10.l;
            put((int)num + '0');
            num -= (int)num;
        }

        put(uppercase ? 'E' : 'e');

        str = number(str, exponent, 10, 2, 0, 0x05, osize, n);
    }

    return str;
}

#undef put

int vsnprintf(char *buffer, size_t n, const char *format, va_list argptr)
{
    int len;
    unsigned long long num;
    long double fnum;
    int i, base;
    char *str;
    char *s;
    int flags;        //Flags für number()
    int field_width;  //Breite des Ausgabefelds
    int precision;    //Dezimalstellen (Original: "min. # of digits for integers; max number of chars for from string")
    int qualifier;    //'h', 'l', oder 'L' für Integer
    size_t osize = 0;

    n--; //Platz fürs Nullzeichen

    if (format == NULL)
        format = "<NULL>";

    for (str = buffer; *format; format++)
    {
        if (*format != '%')
        {
            if (osize++ < n)
                *(str++) = *format;
            continue;
        }

        //Flags verarbeiten
        flags = 0;
        for (;;)
        {
            format++; //Hier wird auch das %-Zeichen weggelassen
            switch (*format)
            {
                case '-':
                    flags |= 0x10;
                    continue;
                case '+':
                    flags |= 0x04;
                    continue;
                case ' ':
                    flags |= 0x08;
                    continue;
                case '#':
                    flags |= 0x20;
                    continue;
                case '0':
                    flags |= 0x01;
                    continue;
            }
            break;
        }

        //Feldbreite ermitteln
        field_width = -1;
        if (isdigit(*format))
            field_width = skip_atoi(&format);
        else if (*format == '*')
        {
            format++;
            //In der Argumentliste suchen
            field_width = va_arg(argptr, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= 0x10;
            }
        }

        //Genauigkeit ermitteln
        precision = -1;
        if (*format == '.')
        {
            format++;
            if (isdigit(*format))
                precision = skip_atoi(&format);
            else if (*format == '*')
            {
                format++;
                //In der Argumentliste suchen
                precision = va_arg(argptr, int);
            }
            if (precision < 0)
                precision = 0;
        }

        //Den Längenmodifizierer ermitteln
        qualifier = -1;
        if ((*format == 'h') || (*format == 'l') || (*format == 'L'))
            qualifier = *(format++);
        if (((qualifier == 'l') && (*format == 'l')) || ((qualifier == 'L') && (*format == 'L'))) //ll
        {
            qualifier = '#';
            format++;
        }

        //Basis des Dezimalsystems
        base = 10;

        switch (*format)
        {
            case ('c'):
                if (!(flags & 0x01))
                    while (--field_width > 0)
                        if (osize++ < n)
                            *(str++) = ' ';
                if (osize++ < n)
                    *(str++) = (unsigned char)va_arg(argptr, int);
                while (--field_width > 0)
                    if (osize++ < n)
                        *(str++) = ' ';
                continue;
            case ('s'):
                s = va_arg(argptr, char *);
                if (s == NULL)
                    s = (char *)"<NULL>";
                len = strnlen(s, precision);
                if (!(flags & 0x10))
                    while (len < field_width--)
                        if (osize++ < n)
                            *(str++) = ' ';
                for (i = 0; i < len; i++)
                    if (osize++ < n)
                        *(str++) = *(s++);
                while (len < field_width--)
                    if (osize++ < n)
                        *(str++) = ' ';
                continue;
            case ('P'):
                if (field_width == -1)
                {
                    field_width = 16;
                    flags |= 0x01;
                }
                qualifier = '#';
            case ('p'):
                if (field_width == -1)
                {
                    field_width = 8;
                    flags |= 0x01;
                }
                if (qualifier == -1)
                    qualifier = 'l';
                if (osize++ < n)
                    *(str++) = '0';
                if (osize++ < n)
                    *(str++) = 'x';
                flags |= 0x40;
                base = 16;
                break;
            case ('n'):
                if (qualifier == 'l')
                {
                    long *ip = va_arg(argptr, long*);
                    *ip = str-buffer;
                }
                else
                {
                    int *ip = va_arg(argptr, int*);
                    *ip = str-buffer;
                }
                continue;
                //Integer - Flags setzen und abbrechen
            case ('o'):
                base = 8;
                break;
            case ('X'):
                flags |= 0x40;
            case ('x'):
                base = 16;
                break;
            case ('d'):
            case ('i'):
                flags |= 0x02;
            case ('u'):
                break;
            case ('E'):
                flags |= 0x400;
            case ('e'):
                flags |= 0x200;
                goto display_double;
            case ('F'):
                flags |= 0x400;
            case ('f'):
                flags |= 0x100;
                goto display_double;
            case ('G'):
                flags |= 0x400;
            case ('g'):
                flags |= 0x300;
                if (!precision)
                    precision = 1;
                goto display_double;
            default:
                if (*format != '%')
                    if (osize++ < n)
                        *(str++) = '%';
                if (*format)
                {
                    if (osize++ < n)
                        *(str++) = *format;
                }
                else
                    format--;
                continue;
        }

        if (qualifier == 'l')
            num = va_arg(argptr, unsigned long);
        else if (qualifier == 'h')
        {
            if (flags & 0x02)
                num = (signed int)(va_arg(argptr, int) & 0xFFFF);
            else
                num = (unsigned int)(va_arg(argptr, unsigned int) & 0xFFFF);
        }
        else if (qualifier == '#')
            num = va_arg(argptr, unsigned long long);
        else if (flags & 0x02)
            num = (signed int)va_arg(argptr, int);
        else
            num = (unsigned int)va_arg(argptr, unsigned int);

        str = number(str, num, base, field_width, precision, flags, &osize, n);

        continue;


        display_double:

        if (qualifier == 'L')
            fnum = va_arg(argptr, long double);
        else
            fnum = va_arg(argptr, double);

        str = float_number(str, fnum, precision, flags, &osize, n);
    }
    *str = '\0';
    return osize;
}
