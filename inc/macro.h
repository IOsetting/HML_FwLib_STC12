/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:include some important macro
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___MACRO_H___
#define ___MACRO_H___

/* ----- @type define ----- */
typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned int  word;

/* ----- @enumeration type ----- */
/* mark user action */
typedef enum
{
    DISABLE = 0x0,
    ENABLE  = !DISABLE
} Action;

/* mark bit value/state */
typedef enum
{
    RESET = 0x0,
    SET   = !RESET
} FunctionalState;

/* ----- @macro ----- */
/* mark model
 * (1)end with 'E' : integrated EEPROM
 * (2)end with 'X' : integrated extended RAM
 * (3)end with "XE": integrated EEPROM & extended RAM
 * (4)others: no EEPROM & extended RAM
 */
#define _MCU_NULL_           0x00
#define _MCU_STC11F01_       0x01
#define _MCU_STC11F01E_      0x02
#define _MCU_STC11L01E_      0x03
#define _MCU_STC11F02_       0x04
#define _MCU_STC11F02E_      0x05
#define _MCU_STC11L02E_      0x06
#define _MUC_STC11F03_       0x07
#define _MUC_STC11F03E_      0x08
#define _MUC_STC11L03E_      0x09
#define _MCU_STC11F04_       0x0A
#define _MCU_STC11F04E_      0x0B
#define _MCU_STC11L04E_      0x0C
#define _MCU_STC11F05_       0x0D
#define _MCU_STC11F05E_      0x0E
#define _MCU_STC11L05E_      0x0F
#define _MCU_IAP11F06        0x10
#define _MCU_IAP11L06_       0x11
#define _MCU_STC11F08_       0x12
#define _MCU_STC11F08X_      0x13
#define _MCU_STC11F08XE_     0x14
#define _MCU_STC11L08XE_     0x15
#define _MCU_STC11F16_       0x16
#define _MCU_STC11F16X_      0x17
#define _MCU_STC11F16XE_     0x18
#define _MCU_STC11L16XE_     0x19
#define _MCU_STC11F32_       0x1A
#define _MCU_STC11F32X_      0x1B
#define _MCU_STC11F32XE_     0x1C
#define _MCU_STC11L32XE_     0x1D
#define _MCU_STC11F40_       0x1E
#define _MCU_STC11F40X_      0x1F
#define _MCU_STC11F40XE_     0x20
#define _MCU_STC11L40XE_     0x21
#define _MCU_STC11F48_       0x22
#define _MCU_STC11F48X_      0x23
#define _MCU_STC11F48XE_     0x24
#define _MCU_STC11L48XE      0x25
#define _MCU_STC11F52_       0x26
#define _MCU_STC11F52X_      0x27
#define _MCU_STC11F52XE_     0x28
#define _MCU_STC11L52XE      0x29
#define _MCU_STC11F56_       0x2A
#define _MCU_STC11F56X_      0x2B
#define _MCU_STC11F56XE_     0x2C
#define _MCU_STC11L56XE_     0x2D
#define _MCU_STC11F60_       0x2E
#define _MCU_STC11F60X_      0x2F
#define _MCU_STC11F60XE_     0x30
#define _MCU_STC11L60XE_     0x31
#define _MCU_IAP11F62_       0x32
#define _MCU_IAP11F62X_      0x33
#define _MCU_IAP11L62X_      0x34

/* ---------- NEED TO CONFIG MANUALLY !!! ---------- */
/* configure MCU model, default value is _MCU_STC11F04E_ */
#define _MCU_MODEL_ _MCU_STC11F04E_

/* configure input clock frequency */
#define _FRE_OSC_ 11059200L
//#define _FRE_OSC_ 12000000L

/* select the part you need  compile due to limited store zone of MCU */
#define ___COMPILE_EXTI___
#define ___COMPILE_GPIO___
#define ___COMPILE_IAP___
#define ___COMPILE_MEM___
#define ___COMPILE_PWR___
#define ___COMPILE_RCC___
#define ___COMPILE_TIM___
#define ___COMPILE_UART___
#define ___COMPILE_UTIL___
#define ___COMPILE_WDT___

/* ---------- END OF MANUAL CONFIGURATON PART --------- */

/* ---------- @run-time check --------- */
#if (_MCU_MODEL_ == _MCU_NULL_)
    #error HML run-time check:not specify MCU model! (ERROR_CODE-0x01)
#endif

#ifndef _FRE_OSC_
    #error HML run-time check:the firmware library need define extern clcok frequency! (ERROR_CODE-0x02)
#endif

#if (defined ___COMPILE_PWR___) && (!defined ___COMPILE_GPIO___)
    #error HML run-time check:PWR part need sextern part GPIO, please enable macro define ___COMPILE_GPIO___ (ERROR_CODE-0x04)
#endif

#if (defined ___COMPILE_RCC___) && (!defined ___COMPILE_UTIL___)
    #error HML run-time check:RCC part need extern part UTIL, please make sure enable them all (ERROR_CODE-0x05)
#endif

#ifdef ___COMPILE_UART___
    #if (!defined ___COMPILE_RCC___) || (!defined ___COMPILE_TIM___) || (!defined ___COMPILE_UTIL___)
        #error HML run-time check:UART part need extern part RCC, TIM and UTIL, please make sure enable them all (ERROR_CODE-0x06)
    #endif
#endif

/* ---------- ---------- */

#endif
