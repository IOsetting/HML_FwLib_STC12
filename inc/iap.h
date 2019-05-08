/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:includes some definitions for operating IAP module
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___IAP_H___
#define ___IAP_H___

/* ----- @header file ----- */
#include <stdbool.h>
#include "stc11.h"
#include "intrasm.h"
#include "macro.h"
#include "util.h"

/* ----- @enumeration type ----- */
/* mark command of IAP */
typedef enum
{
    IAP_command_idle  = 0x0,
    IAP_command_read  = 0x1,
    IAP_command_write = 0x2,
    IAP_command_erase = 0x3
} IAP_command;

/* ---------- address define --------- */
#define IAP_ADDR_START 0x0000

#if (_MCU_MODEL_ == _MCU_STC11F01E_)  || (_MCU_MODEL_ == _MCU_STC11L01E_) || \
    (_MCU_MODEL_ == _MCU_STC11F02E_)  || (_MCU_MODEL_ == _MCU_STC11L02E_) || \
    (_MCU_MODEL_ == _MUC_STC11F03E_)  || (_MCU_MODEL_ == _MUC_STC11L03E_) || \
    (_MCU_MODEL_ == _MCU_STC11F60XE_) || (_MCU_MODEL_ == _MCU_STC11L60XE_)

    #define IAP_ADDR_END 0x07FF

#elif (_MCU_MODEL_ == _MCU_STC11F04E_) || (_MCU_MODEL_ == _MCU_STC11L04E_) || \
      (_MCU_MODEL_ == _MCU_STC11F05E_) || (_MCU_MODEL_ == _MCU_STC11L05E_)

    #define IAP_ADDR_END 0x03FF

#elif (_MCU_MODEL_ == _MCU_IAP11F06) || (_MCU_MODEL_ == _MCU_IAP11L06_)

    #define IAP_ADDR_END 0x17FF

#elif (_MCU_MODEL_ == _MCU_STC11F08XE_) || (_MCU_MODEL_ == _MCU_STC11L08XE_)

    #define IAP_ADDR_END 0xD3FF

#elif (_MCU_MODEL_ == _MCU_STC11F16XE_) || (_MCU_MODEL_ == _MCU_STC11L16XE_)

    #define IAP_ADDR_END 0xB3FF

#elif (_MCU_MODEL_ == _MCU_STC11F32XE_) || (_MCU_MODEL_ == _MCU_STC11L32XE_)

    #define IAP_ADDR_END 0x73FF

#elif (_MCU_MODEL_ == _MCU_STC11F40XE_) || (_MCU_MODEL_ == _MCU_STC11L40XE_)

    #define IAP_ADDR_END 0x53FF

#elif (_MCU_MODEL_ == _MCU_STC11F48XE_) || (_MCU_MODEL_ == _MCU_STC11L48XE)

    #define IAP_ADDR_END 0x33FF

#elif (_MCU_MODEL_ == _MCU_STC11F52XE_) || (_MCU_MODEL_ == _MCU_STC11L52XE)

    #define IAP_ADDR_END 0x23FF

#elif (_MCU_MODEL_ == _MCU_STC11F56XE_) || (_MCU_MODEL_ == _MCU_STC11L56XE_)

    #define IAP_ADDR_END 0x13FF

#elif (_MCU_MODEL_ == _MCU_IAP11F62X_) || (_MCU_MODEL_ == _MCU_IAP11L62X_)

    #define IAP_ADDR_END 0xF7FF

#else

    #define IAP_ADDR_END 0x0000

#endif

/* ----- @function ----- */
void IAP_cmd(Action a);
bool IAP_eraseByte(unsigned int addr);
void IAP_idle(void);
bool IAP_isSuccess(void);
byte IAP_readByte(unsigned int addr);
void IAP_setAddress(unsigned int addr);
void IAP_setCommand(IAP_command cmd);
void IAP_trig(void);
bool IAP_writeByte(unsigned int addr,byte dat);

#endif