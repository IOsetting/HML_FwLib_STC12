/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operate on-chip EXTI module
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */
 
#ifndef ___EXTI_H___
#define ___EXTI_H___

/* ----- @header file ----- */
#include "stc11.h"
#include "macro.h"

/* ----- @enumeration type ----- */
/* mark EXTI module */
typedef enum
{
    PERIPH_EXTI_0 = 0x0,
    PERIPH_EXTI_1 = 0x1
} PERIPH_EXTI;

/* mark work mode */
typedef enum
{
    EXTI_mode_fallEdge = 0x1,
    EXTI_mode_lowLevel = 0x0
} EXTI_mode;

/* ----- @structure define ----- */
/* configuration structure */
typedef struct
{
    EXTI_mode mode;
    Action    priority;
} EXTI_configTypeDef;

/* ----- @function ----- */
void EXTI_cmd(PERIPH_EXTI exti,Action a);
void EXTI_config(PERIPH_EXTI exti,EXTI_configTypeDef *ec);
void EXTI_setMode(PERIPH_EXTI exti,EXTI_mode mod);
void EXTI_setPriority(PERIPH_EXTI exti,Action a);

#endif
