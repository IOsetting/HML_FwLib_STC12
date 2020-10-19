/*****************************************************************************/
/** 
 * \file        tim.h
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       operations for timers
 * \note        
 * \version     v0.0
 * \ingroup     TIM
******************************************************************************/

#ifndef ___HML_TIM_H___
#define ___HML_TIM_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/stc11.h"
#include "hml/macro.h"
#include "hml/types.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark timer module
 */
typedef enum
{
    PERIPH_TIM_0 = 0x0,
    PERIPH_TIM_1 = 0x1,
} PERIPH_TIM;

/**
 * \brief mark timer work mode
 */
typedef enum
{
    TIM_mode_0 = 0x0,        /* 13-bit timer/counter */
    TIM_mode_1 = 0x1,        /* 16-bit timer/counter */
    TIM_mode_2 = 0x2,        /* 8-bit auto reload */
    TIM_mode_3 = 0x3         /* only for timer-0 */
} TIM_mode;

/**
 * \brief mark timer function
 */
typedef enum
{
    TIM_function_cnt = 0x1,  /* counter mode */
    TIM_function_tim = 0x0   /* timer mode */
} TIM_function;

/**
 * \brief mark prescaler factor of timer
 */
typedef enum
{
    TIM_prescaler_12 = 12,
    TIM_prescaler_1  = 1
} TIM_prescaler;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief struct for timer configuration
 */
typedef struct
{
    TIM_function  function;
    Action        interruptState;
    Action        interruptPriority;
    TIM_mode      mode;
    TIM_prescaler prescaler;
    uint16_t      value;
} TIM_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
uint16_t TIM_calculateValue(uint16_t t,TIM_mode mode, TIM_prescaler pre);
void TIM_cmd(PERIPH_TIM tim, Action a);
void TIM_cmd_clockOutput(PERIPH_TIM tim, Action a);
void TIM_config(PERIPH_TIM tim, TIM_configTypeDef *tc);
uint16_t TIM_getValue(PERIPH_TIM tim);
bool TIM_isOverflow(PERIPH_TIM tim);
void TIM_setFunction(PERIPH_TIM tim, TIM_function f);
void TIM_setMode(PERIPH_TIM tim, TIM_mode mode);
void TIM_setPrescaler(PERIPH_TIM tim, TIM_prescaler pre);
void TIM_setValue(PERIPH_TIM tim, uint16_t val);
void TIM_INT_cmd(PERIPH_TIM tim, Action a);
void TIM_INT_setPriority(PERIPH_TIM tim, Action p);

#endif
