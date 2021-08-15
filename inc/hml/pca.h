/*****************************************************************************/
/** 
 * \file        pca.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for PCA/PWM
 * \note        
 * \version     v0.1
 * \ingroup     PCA
******************************************************************************/

#ifndef ___HML_PCA_H___
#define ___HML_PCA_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/util.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark PCA counter pulse source
 */
typedef enum
{
    PCA_CounterPulseSource_SysClkDivBy12 = 0x00, /* System clock/12, SYSclk/12 */
    PCA_CounterPulseSource_SysClkDivBy2  = 0x01, /* System clock/2, SYSclk/2 */
    PCA_CounterPulseSource_Tim0          = 0x02, /* Timer 0 overflow */
    PCA_CounterPulseSource_External      = 0x03, /* External clock from ECI/P1.2 (or P4.1) pin (max speed = SYSclk/2) */
    PCA_CounterPulseSource_SysClk        = 0x04, /* System clock, SYSclk */
    PCA_CounterPulseSource_SysClkDivBy4  = 0x05, /* System clock/4, SYSclk/4 */
    PCA_CounterPulseSource_SysClkDivBy6  = 0x06, /* System clock/4, SYSclk/6 */
    PCA_CounterPulseSource_SysClkDivBy8  = 0x07, /* System clock/4, SYSclk/8 */
} PCA_counterPulseSource;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure
 */
typedef struct
{
    uint8_t        channelPins;
    Action         interruptState;
    Action         power;
} PCA_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/


#endif
