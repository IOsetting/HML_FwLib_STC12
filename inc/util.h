/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:provides some public functions
 * @Required-complier:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___UTIL_H___
#define ___UTIL_H___

/* ----- @header file ----- */
#include <compiler.h>
#include "stc11.h"
#include "macro.h"

/* ----- @function ----- */
void disableAllInterrupts(void);
void enableAllInterrupts(void);
unsigned int pow(unsigned char x,unsigned char y);    /* self-define pow function */
void sleep(u16 t);

#endif
