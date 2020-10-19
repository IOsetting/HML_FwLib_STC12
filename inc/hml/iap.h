/*****************************************************************************/
/** 
 * \file        iap.h
 * \author      Jiabin Hsu | zsiothsu@zhishan-iot.tk
 * \brief       operations for IAP module
 * \note        
 * \version     v0.0
 * \ingroup     IAP
******************************************************************************/

#ifndef ___HML_IAP_H___
#define ___HML_IAP_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/stc11.h"
/*****************************************************************************/
#include "hml/util.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
#define IAP_ADDR_START 0x0000

#if (HML_MCU_MODEL == MCU_MODEL_STC11F01E)       || \
    (HML_MCU_MODEL == MCU_MODEL_STC11L01E)       || \
    (HML_MCU_MODEL == MCU_MODEL_STC11F02E)       || \
    (HML_MCU_MODEL == MCU_MODEL_STC11L02E)       || \
    (HML_MCU_MODEL == MCU_MODEL_STC11F03E)       || \
    (HML_MCU_MODEL == MCU_MODEL_STC11L03E)
        #define IAP_ADDR_END 0x07FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F04E)     || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L04E)     || \
      (HML_MCU_MODEL == MCU_MODEL_STC11F05E)     || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L05E)     || \
      (HML_MCU_MODEL == MCU_MODEL_STC11F60XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L60XE)
        #define IAP_ADDR_END 0x03FF
#elif (HML_MCU_MODEL == MCU_MODEL_IAP11F06)      || \
      (HML_MCU_MODEL == MCU_MODEL_IAP11L06)
        #define IAP_ADDR_END 0x17FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F08XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L08XE)
        #define IAP_ADDR_END 0xD3FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F16XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L16XE)
        #define IAP_ADDR_END 0xB3FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F32XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L32XE)
        #define IAP_ADDR_END 0x73FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F40XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L40XE)
        #define IAP_ADDR_END 0x53FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F48XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L48XE)
        #define IAP_ADDR_END 0x33FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F52XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L52XE)
        #define IAP_ADDR_END 0x23FF
#elif (HML_MCU_MODEL == MCU_MODEL_STC11F56XE)    || \
      (HML_MCU_MODEL == MCU_MODEL_STC11L56XE)
        #define IAP_ADDR_END 0x13FF
#elif (HML_MCU_MODEL == MCU_MODEL_IAP11F62X)     || \
      (HML_MCU_MODEL == MCU_MODEL_IAP11L62X)
        #define IAP_ADDR_END 0xF7FF
#else
    #define IAP_ADDR_END 0x0000
#endif

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 *\brief define IAP command
 */
typedef enum
{
    IAP_command_idle  = 0x0,
    IAP_command_read  = 0x1,
    IAP_command_write = 0x2,
    IAP_command_erase = 0x3
} IAP_command;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void IAP_cmd(Action a);
bool IAP_eraseByte(uint16_t addr);
void IAP_idle(void);
bool IAP_isSuccess(void);
byte IAP_readByte(uint16_t addr);
void IAP_setAddress(uint16_t addr);
void IAP_setCommand(IAP_command cmd);
void IAP_trig(void);
bool IAP_writeByte(uint16_t addr, byte dat);

#endif
