/*
 * Copyright (c) 2009 The tyndur Project. All rights reserved.
 *
 * This code is derived from software contributed to the tyndur Project
 * by Kevin Wolf.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define ROUND_NEAR  0x000
#define ROUND_DOWN  0x400
#define ROUND_UP    0x800
#define ROUND_TRUNC 0xC00

static int rounding_mode = FE_TONEAREST;

/*
 * Achtung:
 *
 * Die folgende Funktion basieren auf der Annahme, dass das RC-Feld im FPU
 * Control Word normalerweise immer auf 0 gesetzt ist, also der neue Wert durch
 * ein einfaches or eingetragen werden kann.
 */
static inline long double do_round(long double x, int mode)
{
    long double res;
    uint16_t control_word;

    __asm__ __volatile__ (
        // Rundungsmodus setzen
        "fnstcw (%2);"
        "mov (%2), %%eax;"
        "or %3, (%2);"
        "fldcw (%2);"

        // Zahl auf dem Stack runden
        "frndint;"

        // Wieder den Standardrundungsmodus setzen
        "mov %%eax, (%2);"
        "fldcw (%2);"
        : "=t" (res) : "0" (x), "d" (&control_word), "r" (mode) : "eax");

    return res;
}

long double floorl(long double x)
{
    return do_round(x, ROUND_DOWN);
}

double floor(double x)
{
    return floorl(x);
}

float floorf(float x)
{
    return floorl(x);
}

long double ceill(long double x)
{
    return do_round(x, ROUND_UP);
}

double ceil(double x)
{
    return ceill(x);
}

float ceilf(float x)
{
    return ceill(x);
}

long double truncl(long double x)
{
    return do_round(x, ROUND_TRUNC);
}

double trunc(double x)
{
    return truncl(x);
}

float truncf(float x)
{
    return truncl(x);
}

long double roundl(long double x)
{
    long double res;

    __asm__ __volatile__ ("frndint" : "=t" (res) : "0" (x));

    return res;
}

double round(double x)
{
    return roundl(x);
}

float roundf(float x)
{
    return roundl(x);
}

long double nearbyintl(long double x)
{
    switch (rounding_mode) {
        case FE_TONEAREST:
            return roundl(x);
        case FE_TOWARDZERO:
            return truncl(x);
        case FE_DOWNWARD:
            return floorl(x);
        case FE_UPWARD:
            return ceill(x);
    }

    abort();
    return x;
}

double nearbyint(double x)
{
    return nearbyintl(x);
}

float nearbyintf(float x)
{
    return nearbyintl(x);
}

int fegetround(void)
{
    return rounding_mode;
}

int fesetround(int mode)
{
    switch(mode) {
        case FE_TONEAREST:
        case FE_TOWARDZERO:
        case FE_DOWNWARD:
        case FE_UPWARD:
            rounding_mode = mode;
            return 0;

        default:
            return -1;
    }
}
