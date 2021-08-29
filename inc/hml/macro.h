/*****************************************************************************/
/** 
 * \file        macro.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML macro define
 * \note        
 * \version     v0.0
 * \ingroup     generic
******************************************************************************/

#ifndef ___HML_MACRO_H___
#define ___HML_MACRO_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/conf.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
/**
 * \brief mark model
 * - suffix 'E': : integrated EEPROM
 * - suffix 'X': : integrated extended RAM
 * - suffix 'XE' : integrated EEPROM & extended RAM
 * - others      : no EEPROM & extended RAM
 */

#define MCU_MODEL_GENERIC         0x01

#define MCU_MODEL_STC12C5A08AD    0x11
#define MCU_MODEL_STC12C5A08S2    0x12
#define MCU_MODEL_STC12C5A08PWM   0x13
#define MCU_MODEL_STC12LE5A08AD   0x14
#define MCU_MODEL_STC12LE5A08S2   0x15
#define MCU_MODEL_STC12LE5A08PWM  0x16

#define MCU_MODEL_STC12C5A16AD    0x21
#define MCU_MODEL_STC12C5A16S2    0x22
#define MCU_MODEL_STC12C5A16PWM   0x23
#define MCU_MODEL_STC12LE5A16AD   0x24
#define MCU_MODEL_STC12LE5A16S2   0x25
#define MCU_MODEL_STC12LE5A16PWM  0x26

#define MCU_MODEL_STC12C5A32AD    0x41
#define MCU_MODEL_STC12C5A32S2    0x42
#define MCU_MODEL_STC12C5A32PWM   0x43
#define MCU_MODEL_STC12LE5A32AD   0x44
#define MCU_MODEL_STC12LE5A32S2   0x45
#define MCU_MODEL_STC12LE5A32PWM  0x46

#define MCU_MODEL_STC12C5A40AD    0x51
#define MCU_MODEL_STC12C5A40S2    0x52
#define MCU_MODEL_STC12C5A40PWM   0x53
#define MCU_MODEL_STC12LE5A40AD   0x54
#define MCU_MODEL_STC12LE5A40S2   0x55
#define MCU_MODEL_STC12LE5A40PWM  0x56

#define MCU_MODEL_STC12C5A48AD    0x61
#define MCU_MODEL_STC12C5A48S2    0x62
#define MCU_MODEL_STC12C5A48PWM   0x63
#define MCU_MODEL_STC12LE5A48AD   0x64
#define MCU_MODEL_STC12LE5A48S2   0x65
#define MCU_MODEL_STC12LE5A48PWM  0x66

#define MCU_MODEL_STC12C5A52AD    0x71
#define MCU_MODEL_STC12C5A52S2    0x72
#define MCU_MODEL_STC12C5A52PWM   0x73
#define MCU_MODEL_STC12LE5A52AD   0x74
#define MCU_MODEL_STC12LE5A52S2   0x75
#define MCU_MODEL_STC12LE5A52PWM  0x76

#define MCU_MODEL_STC12C5A56AD    0x81
#define MCU_MODEL_STC12C5A56S2    0x82
#define MCU_MODEL_STC12C5A56PWM   0x83
#define MCU_MODEL_STC12LE5A56AD   0x84
#define MCU_MODEL_STC12LE5A56S2   0x85
#define MCU_MODEL_STC12LE5A56PWM  0x86

#define MCU_MODEL_STC12C5A60AD    0x91
#define MCU_MODEL_STC12C5A60S2    0x92
#define MCU_MODEL_STC12C5A60PWM   0x93
#define MCU_MODEL_STC12LE5A60AD   0x94
#define MCU_MODEL_STC12LE5A60S2   0x95
#define MCU_MODEL_STC12LE5A60PWM  0x96

#define MCU_MODEL_IAP12C5A62AD    0xa1
#define MCU_MODEL_IAP12C5A62S2    0xa2
#define MCU_MODEL_IAP12C5A62PWM   0xa3
#define MCU_MODEL_IAP12LE5A62AD   0xa4
#define MCU_MODEL_IAP12LE5A62S2   0xa5
#define MCU_MODEL_IAP12LE5A62PWM  0xa6

/**
 * \brief check macro for MCU model
 */
#define IS_STC12_MCU_MODEL(model)           \
    (                                       \
        (model == MCU_MODEL_GENERIC    )     || \
        (model == MCU_MODEL_STC12C5A08AD   ) || \
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
        (model == MCU_MODEL_STC12C5A32AD   ) || \
        (model == MCU_MODEL_STC12C5A32S2   ) || \
        (model == MCU_MODEL_STC12C5A32PWM  ) || \
        (model == MCU_MODEL_STC12LE5A32AD  ) || \
        (model == MCU_MODEL_STC12LE5A32S2  ) || \
        (model == MCU_MODEL_STC12LE5A32PWM ) || \
        (model == MCU_MODEL_STC12C5A40AD   ) || \
        (model == MCU_MODEL_STC12C5A40S2   ) || \
        (model == MCU_MODEL_STC12C5A40PWM  ) || \
        (model == MCU_MODEL_STC12LE5A40AD  ) || \
        (model == MCU_MODEL_STC12LE5A40S2  ) || \
        (model == MCU_MODEL_STC12LE5A40PWM ) || \
        (model == MCU_MODEL_STC12C5A48AD   ) || \
        (model == MCU_MODEL_STC12C5A48S2   ) || \
        (model == MCU_MODEL_STC12C5A48PWM  ) || \
        (model == MCU_MODEL_STC12LE5A48AD  ) || \
        (model == MCU_MODEL_STC12LE5A48S2  ) || \
        (model == MCU_MODEL_STC12LE5A48PWM ) || \
        (model == MCU_MODEL_STC12C5A52AD   ) || \
        (model == MCU_MODEL_STC12C5A52S2   ) || \
        (model == MCU_MODEL_STC12C5A52PWM  ) || \
        (model == MCU_MODEL_STC12LE5A52AD  ) || \
        (model == MCU_MODEL_STC12LE5A52S2  ) || \
        (model == MCU_MODEL_STC12LE5A52PWM ) || \
        (model == MCU_MODEL_STC12C5A56AD   ) || \
        (model == MCU_MODEL_STC12C5A56S2   ) || \
        (model == MCU_MODEL_STC12C5A56PWM  ) || \
        (model == MCU_MODEL_STC12LE5A56AD  ) || \
        (model == MCU_MODEL_STC12LE5A56S2  ) || \
        (model == MCU_MODEL_STC12LE5A56PWM ) || \
        (model == MCU_MODEL_STC12C5A60AD   ) || \
        (model == MCU_MODEL_STC12C5A60S2   ) || \
        (model == MCU_MODEL_STC12C5A60PWM  ) || \
        (model == MCU_MODEL_STC12LE5A60AD  ) || \
        (model == MCU_MODEL_STC12LE5A60S2  ) || \
        (model == MCU_MODEL_STC12LE5A60PWM ) || \
        (model == MCU_MODEL_IAP12C5A62AD   ) || \
        (model == MCU_MODEL_IAP12C5A62S2   ) || \
        (model == MCU_MODEL_IAP12C5A62PWM  ) || \
        (model == MCU_MODEL_IAP12LE5A62AD  ) || \
        (model == MCU_MODEL_IAP12LE5A62S2  ) || \
        (model == MCU_MODEL_IAP12LE5A62PWM )    \
    )

/**
 * \brief have macro for IAP function
 */
#define IS_IAP_MODEL(model)                 \
    (                                       \
        (model == MCU_MODEL_STC12C5A08AD   ) || \
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
        (model == MCU_MODEL_STC12C5A32AD   ) || \
        (model == MCU_MODEL_STC12C5A32S2   ) || \
        (model == MCU_MODEL_STC12C5A32PWM  ) || \
        (model == MCU_MODEL_STC12LE5A32AD  ) || \
        (model == MCU_MODEL_STC12LE5A32S2  ) || \
        (model == MCU_MODEL_STC12LE5A32PWM ) || \
        (model == MCU_MODEL_STC12C5A40AD   ) || \
        (model == MCU_MODEL_STC12C5A40S2   ) || \
        (model == MCU_MODEL_STC12C5A40PWM  ) || \
        (model == MCU_MODEL_STC12LE5A40AD  ) || \
        (model == MCU_MODEL_STC12LE5A40S2  ) || \
        (model == MCU_MODEL_STC12LE5A40PWM ) || \
        (model == MCU_MODEL_STC12C5A48AD   ) || \
        (model == MCU_MODEL_STC12C5A48S2   ) || \
        (model == MCU_MODEL_STC12C5A48PWM  ) || \
        (model == MCU_MODEL_STC12LE5A48AD  ) || \
        (model == MCU_MODEL_STC12LE5A48S2  ) || \
        (model == MCU_MODEL_STC12LE5A48PWM ) || \
        (model == MCU_MODEL_STC12C5A52AD   ) || \
        (model == MCU_MODEL_STC12C5A52S2   ) || \
        (model == MCU_MODEL_STC12C5A52PWM  ) || \
        (model == MCU_MODEL_STC12LE5A52AD  ) || \
        (model == MCU_MODEL_STC12LE5A52S2  ) || \
        (model == MCU_MODEL_STC12LE5A52PWM ) || \
        (model == MCU_MODEL_STC12C5A56AD   ) || \
        (model == MCU_MODEL_STC12C5A56S2   ) || \
        (model == MCU_MODEL_STC12C5A56PWM  ) || \
        (model == MCU_MODEL_STC12LE5A56AD  ) || \
        (model == MCU_MODEL_STC12LE5A56S2  ) || \
        (model == MCU_MODEL_STC12LE5A56PWM ) || \
        (model == MCU_MODEL_STC12C5A60AD   ) || \
        (model == MCU_MODEL_STC12C5A60S2   ) || \
        (model == MCU_MODEL_STC12C5A60PWM  ) || \
        (model == MCU_MODEL_STC12LE5A60AD  ) || \
        (model == MCU_MODEL_STC12LE5A60S2  ) || \
        (model == MCU_MODEL_STC12LE5A60PWM ) || \
        (model == MCU_MODEL_IAP12C5A62AD   ) || \
        (model == MCU_MODEL_IAP12C5A62S2   ) || \
        (model == MCU_MODEL_IAP12C5A62PWM  ) || \
        (model == MCU_MODEL_IAP12LE5A62AD  ) || \
        (model == MCU_MODEL_IAP12LE5A62S2  ) || \
        (model == MCU_MODEL_IAP12LE5A62PWM )    \
    )

/**
 * \brief compile select
 */
#if (__CONF_COMPILE_ADC == 1)
    #define COMPILE_ADC
#endif
#if (__CONF_COMPILE_EXTI == 1)
    #define COMPILE_EXTI
#endif
#if (__CONF_COMPILE_GPIO == 1)
    #define COMPILE_GPIO
#endif
#if (__CONF_COMPILE_IAP == 1)
    #define COMPILE_IAP
#endif
#if (__CONF_COMPILE_MEM == 1)
    #define COMPILE_MEM
#endif
#if (__CONF_COMPILE_PCA == 1)
    #define COMPILE_PCA
#endif
#if (__CONF_COMPILE_PWR == 1)
    #define COMPILE_PWR
#endif
#if (__CONF_COMPILE_EXTI == 1)
    #define COMPILE_EXTI
#endif
#if (__CONF_COMPILE_RCC == 1)
    #define COMPILE_RCC
#endif
#if (__CONF_COMPILE_SPI == 1)
    #define COMPILE_SPI
#endif
#if (__CONF_COMPILE_TIM == 1)
    #define COMPILE_TIM
#endif
#if (__CONF_COMPILE_UART == 1)
    #define COMPILE_UART
#endif
#if (__CONF_COMPILE_UTIL == 1)
    #define COMPILE_UTIL
#endif
#if (__CONF_COMPILE_WDT == 1)
    #define COMPILE_WDT
#endif

/*****************************************************************************
 *                           run-time check                                  *
 *****************************************************************************/

/**
 * \brief MCU clock configuration check
 */
#if (defined __CONF_FRE_CLKIN)
    #define MCU_FRE_CLK __CONF_FRE_CLKIN
#else
    #error HML run-time check: error: HML need define input clock frequency! (ERROR_CODE-0x01)
#endif

/**
 * \brief MCU model check
 */
#if (defined __CONF_MCU_MODEL)
    #if IS_STC12_MCU_MODEL(__CONF_MCU_MODEL)
        #if (__CONF_MCU_MODEL == MCU_MODEL_GENERIC)
            #warning the value of macro HML_MCU_MODEL will be filled with MCU_MODEL_STC12C5A08AD
            #define HML_MCU_MODEL MCU_MODEL_STC12C5A08AD
        #else
            #define HML_MCU_MODEL __CONF_MCU_MODEL
        #endif
    #else
        #error HML run-time check: error: unknow or unsupported MCU model!(ERROR_CODE-0x02)
    #endif
#else
    #error HML run-time check: error: please specify MCU model in conf.h!(ERROR_CODE-0x03)
#endif

/**
 * \brief configure IAP function
 */
#if IS_IAP_MODEL(HML_MCU_MODEL)
    #define HAVE_IAP
#endif

/**
 * \brief HML compile selection check
 */
#ifndef HAVE_IAP
    #ifdef COMPILE_IAP
        #error HML run-time check: error: specified MCU model does not support IAP function. (ERROR_CODE-0x04)
    #endif
#endif

#if (defined COMPILE_RCC) && (!defined COMPILE_UTIL)
    #error HML run-time check: error: RCC depends on UTIL, please make sure to enable them it in conf.h (ERROR_CODE-0x05)
#endif

#ifdef COMPILE_UART
    #if (!defined COMPILE_RCC) || (!defined COMPILE_TIM) || (!defined COMPILE_UTIL)
        #error HML run-time check: error: UART epends on RCC, TIM and UTIL, please make sure to enable them all at the same time in conf.h. (ERROR_CODE-0x06)
    #endif
#endif

/**
 * \brief SDCC version check
 */
#if (__SDCC_VERSION_MAJOR == 3)
    #if (__SDCC_VERSION_MINOR < 6)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x07)
    #endif
#else
    #if (__SDCC_VERSION_MAJOR < 3)
        #error HML run-time check: HML requires SDCC v3.6.0 or later versions (ERROR_CODE-0x07)
    #endif
#endif

#endif
