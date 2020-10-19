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
 * \brief mark division factor
 */
typedef enum
{
    RCC_prescaler_1   = 0x00,
    RCC_prescaler_2   = 0x01,
    RCC_prescaler_4   = 0x02,
    RCC_prescaler_8   = 0x03,
    RCC_prescaler_16  = 0x04,
    RCC_prescaler_32  = 0x05,
    RCC_prescaler_64  = 0x06,
    RCC_prescaler_128 = 0x07
} RCC_prescaler;

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
void RCC_setClockDivisionFactor(RCC_prescaler d);
void RCC_softwareReset(void);
uint32_t RCC_getSystemClockFrequency(void);

#endif
