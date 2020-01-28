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
 *\brief: configure clock frequency of MCU
 */
#define __CONF_FRE_CLKIN 11059200L

/**
 *\brief: configure module of MCU
 */
#define __CONF_MCU_MODEL MCU_MODEL_STC11F04E

/**
 *\brief: select HML module which take part in compilation
 */
#define __CONF_COMPILE_EXTI  1
#define __CONF_COMPILE_GPIO  1
#define __CONF_COMPILE_IAP   1
#define __CONF_COMPILE_MEM   1
#define __CONF_COMPILE_PWR   1
#define __CONF_COMPILE_RCC   1
#define __CONF_COMPILE_TIM   1
#define __CONF_COMPILE_UART  1
#define __CONF_COMPILE_UTIL  1
#define __CONF_COMPILE_WDT   1

#endif
