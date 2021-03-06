/*****************************************************************************/
/** 
 * \file        rcc.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for reset and clock control
 * \note        
 * \version     v0.0
 * \ingroup     RCC
******************************************************************************/

#ifndef ___RCC_H___
#define ___RCC_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/util.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark prescaler factor
 */
typedef enum
{
    RCC_BRT_prescaler_1  = 0x1,   /* count per 1 clock cycle */
    RCC_BRT_prescaler_12 = 0x0    /* count per 12 clock cycles */
} RCC_BRT_prescaler;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void RCC_BRT_cmd(Action a);
void RCC_BRT_setClockOutput(Action a);
void RCC_BRT_setPrescaler(RCC_BRT_prescaler pre);
void RCC_BRT_setValue(uint8_t val);
uint16_t RCC_BRT_calcInitValue(uint32_t baud, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate);
void RCC_BRT_config(uint32_t baudrate, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate);
void RCC_softwareReset(void);

#endif
