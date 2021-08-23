/*****************************************************************************/
/** 
 * \file        util.h
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       public interface
 * \note        
 * \version     v0.0
 * \ingroup     UTIL
******************************************************************************/

#ifndef ___HML_UTIL_H___
#define ___HML_UTIL_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <compiler.h>
/*****************************************************************************/
#include "hml/stc12.h"
/*****************************************************************************/
#include "hml/macro.h"
#include "hml/types.h"

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


/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
uint16_t pow(uint8_t x, uint8_t y);
void sleep(uint16_t t);
void UTIL_setInterrupts(Action a);
void UTIL_setClockDivisionFactor(RCC_prescaler d);
uint32_t UTIL_getSystemClockFrequency(void);
void UTIL_enablePrintf(void);

#endif
