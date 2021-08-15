/*****************************************************************************/
/** 
 * \file        conf.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       HML configurations, this file need to be modified by users
 * \note        
 * \version     v0.0
 * \ingroup     generic
******************************************************************************/

#ifndef ___HML_CONF_H___
#define ___HML_CONF_H___

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

/**
 *\brief configure clock frequency of MCU
 */
#ifndef __CONF_FRE_CLKIN
    #warning no specified clock frequency, HML will fill it with 11.0592MHz
    #define __CONF_FRE_CLKIN 11059200UL
#endif

/**
 *\brief configure module of MCU
 */
#ifndef __CONF_MCU_MODEL
    #warning no specified MCU model, HML will fill it with STC11F04E
    #define __CONF_MCU_MODEL MCU_MODEL_STC12C5A08AD
#endif

/**
 *\brief select HML module which take part in compilation
 */
#define __CONF_COMPILE_ADC   1
#define __CONF_COMPILE_EXTI  1
#define __CONF_COMPILE_GPIO  1
#define __CONF_COMPILE_IAP   1
#define __CONF_COMPILE_MEM   1
#define __CONF_COMPILE_PCA   1
#define __CONF_COMPILE_PWR   1
#define __CONF_COMPILE_RCC   1
#define __CONF_COMPILE_TIM   1
#define __CONF_COMPILE_UART  1
#define __CONF_COMPILE_UTIL  1
#define __CONF_COMPILE_WDT   1

#endif
