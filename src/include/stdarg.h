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

#ifndef _STDARG_H
#define _STDARG_H

#define va_start(argptr, last_fixed_arg) __builtin_va_start(argptr, last_fixed_arg)
#define va_arg(argptr, type) __builtin_va_arg(argptr, type)
#define va_copy(dest, src) __builtin_va_copy(dest, src)
#define va_end(argptr) __builtin_va_end(argptr)


typedef __builtin_va_list va_list;

#endif
