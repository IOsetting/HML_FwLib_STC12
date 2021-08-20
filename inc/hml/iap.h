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
#include "hml/stc12.h"
/*****************************************************************************/
#include "hml/util.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
#define IAP_ADDR_START 0x0000

#if (model == MCU_MODEL_STC12C5A08AD   ) || \
    (model == MCU_MODEL_STC12C5A08S2   ) || \
    (model == MCU_MODEL_STC12C5A08PWM  ) || \
    (model == MCU_MODEL_STC12LE5A08AD  ) || \
    (model == MCU_MODEL_STC12LE5A08S2  ) || \
    (model == MCU_MODEL_STC12LE5A08PWM ) || \
    (model == MCU_MODEL_STC12C5A16AD   ) || \
    (model == MCU_MODEL_STC12C5A16S2   ) || \
    (model == MCU_MODEL_STC12C5A16PWM  ) || \
    (model == MCU_MODEL_STC12LE5A16AD  ) || \
    (model == MCU_MODEL_STC12LE5A16S2  ) || \
    (model == MCU_MODEL_STC12LE5A16PWM ) || \
    (model == MCU_MODEL_STC12C5A20AD   ) || \
    (model == MCU_MODEL_STC12C5A20S2   ) || \
    (model == MCU_MODEL_STC12C5A20PWM  ) || \
    (model == MCU_MODEL_STC12LE5A20AD  ) || \
    (model == MCU_MODEL_STC12LE5A20S2  ) || \
    (model == MCU_MODEL_STC12LE5A20PWM )
        #define IAP_ADDR_END 0x1FFF
#elif (model == MCU_MODEL_STC12C5A32AD   ) || \
    (model == MCU_MODEL_STC12C5A32S2   ) || \
    (model == MCU_MODEL_STC12C5A32PWM  ) || \
    (model == MCU_MODEL_STC12LE5A32AD  ) || \
    (model == MCU_MODEL_STC12LE5A32S2  ) || \
    (model == MCU_MODEL_STC12LE5A32PWM )
        #define IAP_ADDR_END 0x6FFF
#elif (model == MCU_MODEL_STC12C5A40AD   ) || \
    (model == MCU_MODEL_STC12C5A40S2   ) || \
    (model == MCU_MODEL_STC12C5A40PWM  ) || \
    (model == MCU_MODEL_STC12LE5A40AD  ) || \
    (model == MCU_MODEL_STC12LE5A40S2  ) || \
    (model == MCU_MODEL_STC12LE5A40PWM )
        #define IAP_ADDR_END 0x4FFF
#elif (model == MCU_MODEL_STC12C5A48AD   ) || \
    (model == MCU_MODEL_STC12C5A48S2   ) || \
    (model == MCU_MODEL_STC12C5A48PWM  ) || \
    (model == MCU_MODEL_STC12LE5A48AD  ) || \
    (model == MCU_MODEL_STC12LE5A48S2  ) || \
    (model == MCU_MODEL_STC12LE5A48PWM )
        #define IAP_ADDR_END 0x2FFF
#elif (model == MCU_MODEL_STC12C5A52AD   ) || \
    (model == MCU_MODEL_STC12C5A52S2   ) || \
    (model == MCU_MODEL_STC12C5A52PWM  ) || \
    (model == MCU_MODEL_STC12LE5A52AD  ) || \
    (model == MCU_MODEL_STC12LE5A52S2  ) || \
    (model == MCU_MODEL_STC12LE5A52PWM )
        #define IAP_ADDR_END 0x1FFF
#elif (model == MCU_MODEL_STC12C5A56AD   ) || \
    (model == MCU_MODEL_STC12C5A56S2   ) || \
    (model == MCU_MODEL_STC12C5A56PWM  ) || \
    (model == MCU_MODEL_STC12LE5A56AD  ) || \
    (model == MCU_MODEL_STC12LE5A56S2  ) || \
    (model == MCU_MODEL_STC12LE5A56PWM )
        #define IAP_ADDR_END 0x0FFF
#elif (model == MCU_MODEL_STC12C5A60AD   ) || \
    (model == MCU_MODEL_STC12C5A60S2   ) || \
    (model == MCU_MODEL_STC12C5A60PWM  ) || \
    (model == MCU_MODEL_STC12LE5A60AD  ) || \
    (model == MCU_MODEL_STC12LE5A60S2  ) || \
    (model == MCU_MODEL_STC12LE5A60PWM )
        #define IAP_ADDR_END 0x03FF
#elif (model == MCU_MODEL_IAP12C5A62AD   ) || \
    (model == MCU_MODEL_IAP12C5A62S2   ) || \
    (model == MCU_MODEL_IAP12C5A62PWM  ) || \
    (model == MCU_MODEL_IAP12LE5A62AD  ) || \
    (model == MCU_MODEL_IAP12LE5A62S2  ) || \
    (model == MCU_MODEL_IAP12LE5A62PWM )
        #define IAP_ADDR_END 0xF7FF
#else
    #define IAP_ADDR_END 0x0000
#endif

/**
 * \brief the wait time of IAP command, which is related to clock frequency
 */
#if   (__CONF_FRE_CLKIN <=  1000000UL)
    #define IAP_WAITTIME 0x07
#elif (__CONF_FRE_CLKIN <=  2000000UL)
    #define IAP_WAITTIME 0x06
#elif (__CONF_FRE_CLKIN <=  3000000UL)
    #define IAP_WAITTIME 0x05
#elif (__CONF_FRE_CLKIN <=  6000000UL)
    #define IAP_WAITTIME 0x04
#elif (__CONF_FRE_CLKIN <= 12000000UL)
    #define IAP_WAITTIME 0x03
#elif (__CONF_FRE_CLKIN <= 20000000UL)
    #define IAP_WAITTIME 0x02
#elif (__CONF_FRE_CLKIN <= 24000000UL)
    #define IAP_WAITTIME 0x01
#else 
    #define IAP_WAITTIME 0x00
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
void IAP_config(void);
bool IAP_eraseSector(uint16_t addr);
void IAP_idle(void);
bool IAP_isSuccess(void);
uint8_t IAP_readByte(uint16_t addr);
void IAP_setAddress(uint16_t addr);
void IAP_setCommand(IAP_command cmd);
void IAP_trig(void);
bool IAP_writeByte(uint16_t addr, uint8_t dat);

#endif
