/*****************************************************************************/
/** 
 * \file        exti.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for on-chip EXTI module
 * \note        
 * \version     v0.0
 * \ingroup     EXTI
******************************************************************************/

#ifndef ___HML_EXTI_H___
#define ___HML_EXTI_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/stc12.h"
#include "hml/macro.h"
#include "hml/types.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 *\brief mark EXTI module
 */
typedef enum
{
    PERIPH_EXTI_0 = 0x0,
    PERIPH_EXTI_1 = 0x1
} PERIPH_EXTI;

/**
 *\brief mark work mode
 */
typedef enum
{
    EXTI_mode_fallEdge = 0x1,
    EXTI_mode_lowLevel = 0x0
} EXTI_mode;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 *\brief configuration structure for EXTI
 */
typedef struct
{
    EXTI_mode mode;
    Action    priority;
} EXTI_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void EXTI_cmd(PERIPH_EXTI exti, Action a);
void EXTI_config(PERIPH_EXTI exti, EXTI_configTypeDef *ec);
void EXTI_setMode(PERIPH_EXTI exti, EXTI_mode mode);
void EXTI_setPriority(PERIPH_EXTI exti, Action a);

#endif
