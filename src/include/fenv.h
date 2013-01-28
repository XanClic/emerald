#ifndef _FENV_H
#define _FENV_H

#define FE_TONEAREST  0
#define FE_DOWNWARD   1
#define FE_UPWARD     2
#define FE_TOWARDZERO 3

int fegetround(void);
int fesetround(int mode);

#endif
