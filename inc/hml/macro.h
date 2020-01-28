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
 *\brief: mark model
 * - suffix 'E': : integrated EEPROM
 * - suffix 'X': : integrated extended RAM
 * - suffix 'XE' : integrated EEPROM & extended RAM
 * - others      : no EEPROM & extended RAM
 */

#define MCU_MODEL_GENERIC         0x01
#define MCU_MODEL_STC11F01        0x02
#define MCU_MODEL_STC11L01        0x03
#define MCU_MODEL_STC11F01E       0x04
#define MCU_MODEL_STC11L01E       0x05
#define MCU_MODEL_STC11F02        0x06
#define MCU_MODEL_STC11L02        0x07
#define MCU_MODEL_STC11F02E       0x08
#define MCU_MODEL_STC11L02E       0x09
#define MCU_MODEL_STC11F03E       0x0A
#define MCU_MODEL_STC11L03E       0x0B
#define MCU_MODEL_STC11F04        0x0C
#define MCU_MODEL_STC11L04        0x0D
#define MCU_MODEL_STC11F04E       0x0E
#define MCU_MODEL_STC11L04E       0x0F
#define MCU_MODEL_STC11F05E       0x10
#define MCU_MODEL_STC11L05E       0x11
#define MCU_MODEL_IAP11F06        0x12
#define MCU_MODEL_IAP11L06        0x13
#define MCU_MODEL_STC11F08XE      0x14
#define MCU_MODEL_STC11L08XE      0x15
#define MCU_MODEL_STC11F16XE      0x16
#define MCU_MODEL_STC11L16XE      0x17
#define MCU_MODEL_STC11F32XE      0x18
#define MCU_MODEL_STC11L32XE      0x19
#define MCU_MODEL_STC11F40XE      0x1A
#define MCU_MODEL_STC11L40XE      0x1B
#define MCU_MODEL_STC11F48XE      0x1C
#define MCU_MODEL_STC11L48XE      0x1D
#define MCU_MODEL_STC11F52XE      0x1E
#define MCU_MODEL_STC11L52XE      0x1F
#define MCU_MODEL_STC11F56XE      0x20
#define MCU_MODEL_STC11L56XE      0x21
#define MCU_MODEL_STC11F60XE      0x22
#define MCU_MODEL_STC11L60XE      0x23
#define MCU_MODEL_IAP11F62X       0x24
#define MCU_MODEL_IAP11L62X       0x25

/**
 *\brief: check macro for MCU model
 */
#define IS_STC11_MCU_MODEL(model)           \
    (                                       \
        (model == MCU_MODEL_GENERIC)     || \
        (model == MCU_MODEL_STC11F01)    || \
        (model == MCU_MODEL_STC11L01)    || \
        (model == MCU_MODEL_STC11F01E)   || \
        (model == MCU_MODEL_STC11L01E)   || \
        (model == MCU_MODEL_STC11F02)    || \
        (model == MCU_MODEL_STC11L02)    || \
        (model == MCU_MODEL_STC11F02E)   || \
        (model == MCU_MODEL_STC11L02E)   || \
        (model == MCU_MODEL_STC11F03E)   || \
        (model == MCU_MODEL_STC11L03E)   || \
        (model == MCU_MODEL_STC11F04)    || \
        (model == MCU_MODEL_STC11L04)    || \
        (model == MCU_MODEL_STC11F04E)   || \
        (model == MCU_MODEL_STC11L04E)   || \
        (model == MCU_MODEL_STC11F05E)   || \
        (model == MCU_MODEL_STC11L05E)   || \
        (model == MCU_MODEL_IAP11F06)    || \
        (model == MCU_MODEL_IAP11L06)    || \
        (model == MCU_MODEL_STC11F08XE)  || \
        (model == MCU_MODEL_STC11L08XE)  || \
        (model == MCU_MODEL_STC11F16XE)  || \
        (model == MCU_MODEL_STC11L16XE)  || \
        (model == MCU_MODEL_STC11F32XE)  || \
        (model == MCU_MODEL_STC11L32XE)  || \
        (model == MCU_MODEL_STC11F40XE)  || \
        (model == MCU_MODEL_STC11L40XE)  || \
        (model == MCU_MODEL_STC11F48XE)  || \
        (model == MCU_MODEL_STC11L48XE)  || \
        (model == MCU_MODEL_STC11F52XE)  || \
        (model == MCU_MODEL_STC11L52XE)  || \
        (model == MCU_MODEL_STC11F56XE)  || \
        (model == MCU_MODEL_STC11L56XE)  || \
        (model == MCU_MODEL_STC11F60XE)  || \
        (model == MCU_MODEL_STC11L60XE)  || \
        (model == MCU_MODEL_IAP11F62X)   || \
        (model == MCU_MODEL_IAP11L62X)      \
    )

/**
 *\brief: have macro for IAP function
 */
#define IS_IAP_MODEL(model)                 \
    (                                       \
        (model == MCU_MODEL_STC11F01E)   || \
        (model == MCU_MODEL_STC11L01E)   || \
        (model == MCU_MODEL_STC11F02E)   || \
        (model == MCU_MODEL_STC11L02E)   || \
        (model == MCU_MODEL_STC11F03E)   || \
        (model == MCU_MODEL_STC11L03E)   || \
        (model == MCU_MODEL_STC11F04E)   || \
        (model == MCU_MODEL_STC11L04E)   || \
        (model == MCU_MODEL_STC11F05E)   || \
        (model == MCU_MODEL_STC11L05E)   || \
        (model == MCU_MODEL_IAP11F06)    || \
        (model == MCU_MODEL_IAP11L06)    || \
        (model == MCU_MODEL_STC11F08XE)  || \
        (model == MCU_MODEL_STC11L08XE)  || \
        (model == MCU_MODEL_STC11F16XE)  || \
        (model == MCU_MODEL_STC11L16XE)  || \
        (model == MCU_MODEL_STC11F32XE)  || \
        (model == MCU_MODEL_STC11L32XE)  || \
        (model == MCU_MODEL_STC11F40XE)  || \
        (model == MCU_MODEL_STC11L40XE)  || \
        (model == MCU_MODEL_STC11F48XE)  || \
        (model == MCU_MODEL_STC11L48XE)  || \
        (model == MCU_MODEL_STC11F52XE)  || \
        (model == MCU_MODEL_STC11L52XE)  || \
        (model == MCU_MODEL_STC11F56XE)  || \
        (model == MCU_MODEL_STC11L56XE)  || \
        (model == MCU_MODEL_STC11F60XE)  || \
        (model == MCU_MODEL_STC11L60XE)  || \
        (model == MCU_MODEL_IAP11F62X)   || \
        (model == MCU_MODEL_IAP11L62X)      \
    )

/**
 *\brief: compile select
 */
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
#if (__CONF_COMPILE_PWR == 1)
    #define COMPILE_PWR
#endif
#if (__CONF_COMPILE_EXTI == 1)
    #define COMPILE_EXTI
#endif
#if (__CONF_COMPILE_RCC == 1)
    #define COMPILE_RCC
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
 *\brief: MCU clock configuration check
 */
#if (defined __CONF_FRE_CLKIN)
    #define MCU_FRE_CLK __CONF_FRE_CLKIN
#else
    #error HML run-time check: error: HML need define input clock frequency! (ERROR_CODE-0x01)
#endif

/**
 *\brief: MCU model check
 */
#if (defined __CONF_MCU_MODEL)
    #if IS_STC11_MCU_MODEL(__CONF_MCU_MODEL)
        #if (__CONF_MCU_MODEL == MCU_MODEL_GENERIC)
            #warning the value of macro HML_MCU_MODEL will be filled with MCU_MODEL_STC11F04E
            #define HML_MCU_MODEL MCU_MODEL_STC11F04E
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
 *\brief: configure IAP function
 */
#if IS_IAP_MODEL(HML_MCU_MODEL)
    #define HAVE_IAP
#endif

/**
 *\brief: HML compile selection check
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
 *\brief: SDCC version check
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
