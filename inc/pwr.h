/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operations about power management
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */
 
#ifndef ___PWR_H___
#define ___PWR_H___

/* ----- @header file ----- */
#include <stdbool.h>
#include <stdint.h>
#include "stc11.h"
#include "macro.h"

/* ----- @enumeration type ----- */
/* mark wakeup pins for power-down mode */
typedef enum
{
    PWR_PD_IEPIN_RXD = 0x1,
    PWR_PD_IEPIN_T0  = 0x2,
    PWR_PD_IEPIN_T1  = 0x3
} PWR_PD_IEPIN;

/* ----- @function ----- */
void PWR_idle(void);
void PWR_powerDown(void);
void PWR_LVD_clearFlag(void);
void PWR_LVD_cmd(Action a);
FunctionalState PWR_LVD_getFlag(void);
void PWR_LVD_INT_cmd(Action a);
void PWR_PD_IE_cmd(PWR_PD_IEPIN pin,Action a);
void PWR_WKT_cmd(Action a);
bool PWR_WKT_setWakeCount(uint16_t c);

#endif
