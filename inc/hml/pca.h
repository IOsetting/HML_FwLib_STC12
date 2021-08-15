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
 * \brief mark PCA module
 */
typedef enum
{
    PERIPH_PCA_0 = 0x0,
    PERIPH_PCA_1 = 0x1,
} PERIPH_PCA;

/**
 * \brief mark timer work mode
 */
typedef enum
{
    PCA_mode_None         = 0x00,      /* N/A */
    PCA_mode_PWM_NoInt    = 0x42,      /* 8-bit PWM, no interrupt */
    PCA_mode_PWM_RiseInt  = 0x63,      /* 8-bit PWM, interrupt triggered by rising edge */
    PCA_mode_PWM_FallInt  = 0x53,      /* 8-bit PWM, interrupt triggered by falling edge */
    PCA_mode_PWM_BothInt  = 0x73,      /* 8-bit PWM, interrupt triggered by both edge */
    PCA_mode_Cap_RiseTri  = 0x20,      /* 16-bit Capture Mode, capture triggered by rising edge on CCPn/PCAn  */
    PCA_mode_Cap_FallTri  = 0x10,      /* 16-bit Capture Mode, capture triggered by falling edge on CCPn/PCAn */
    PCA_mode_Cap_TransTri = 0x30,      /* 16-bit Capture Mode, capture triggered by transition on CCPn/PCAn */
    PCA_mode_SoftTimer    = 0x48,      /* 16-bit software timer */
    PCA_mode_Output       = 0x4C,      /* 16-bit high-speed output */
} PCA_mode;

/**
 * \brief mark PCA counter pulse source
 */
typedef enum
{
    PCA_counterPulseSource_SysClkDivBy12 = 0x00, /* System clock/12, SYSclk/12 */
    PCA_counterPulseSource_SysClkDivBy2  = 0x01, /* System clock/2, SYSclk/2 */
    PCA_counterPulseSource_Tim0          = 0x02, /* Timer 0 overflow */
    PCA_counterPulseSource_External      = 0x03, /* External clock from ECI/P1.2 (or P4.1) pin (max speed = SYSclk/2) */
    PCA_counterPulseSource_SysClk        = 0x04, /* System clock, SYSclk */
    PCA_counterPulseSource_SysClkDivBy4  = 0x05, /* System clock/4, SYSclk/4 */
    PCA_counterPulseSource_SysClkDivBy6  = 0x06, /* System clock/4, SYSclk/6 */
    PCA_counterPulseSource_SysClkDivBy8  = 0x07, /* System clock/4, SYSclk/8 */
} PCA_counterPulseSource;

/**
 * \brief mark function PWM output control
 */
typedef enum
{
    PCA_pwm_Normal = 0x00,     /* PWM output normal */
    PCA_pwm_Low    = 0x03,     /* PWM keep output low */
} PCA_pwm_output;

/**
 * \brief mark function PCA pin location
 */
typedef enum
{
    PCA_pinmap_P1 = 0x0,     /* P12(ECI)/P13(PCA0/PMW0)/P14(PCA1/PWM1) */
    PCA_pinmap_P4 = 0x1      /* P41(ECI)/P42(PCA0/PMW0)/P43(PCA1/PWM1) */
} PCA_pinmap;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure
 */
typedef struct
{
    Action         stopIdleCount;
    Action         overflowInterrupt;
    Action         start;
    PCA_counterPulseSource pulseSource;
    PCA_mode       mode;
    PCA_pwm_output pwmOutputMode;
    uint8_t        compareValue;
    PCA_pinmap     pinmap;
} PCA_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/

void PCA_setCounterPulseSource(PCA_counterPulseSource ps);
void PCA_StopIdleCount_cmd(Action a);
void PCA_OverflowInt_cmd(Action a);
void PCA_config(PERIPH_PCA pca, PCA_configTypeDef *pc);
void PCA_resetCounter(void);
void PCA_setMode(PERIPH_PCA pca, PCA_mode mode);
void PCA_setPWMOutput(PERIPH_PCA pca, PCA_pwm_output mode);
void PCA_setCompareValue(PERIPH_PCA pca, uint8_t val);
void PCA_setPin(PCA_pinmap pinmap);
void PCA_start(Action a);


#endif
