/*****************************************************************************/
/** 
 * \file       exti_toggleIo.c
 * \author     Weilun Fong | wlf@zhishan-iot.tk
 * \date       
 * \brief      example for interrupt priority
 * \note       a example which shows how to use HML_FwLib_STC11 to toggle P12 
 *             state when EXTI is trigged
 * \version    v0.0
 * \ingroup    example
 * \remarks    test-board: ZS5110; test-MCU: STC11F16XE
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml.h"

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       initial MCU
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void sys_init(void)
{
    EXTI_configTypeDef ec;

    ec.mode     = EXTI_mode_fallEdge;
    ec.priority = DISABLE;
    EXTI_config(PERIPH_EXTI_1,&ec);
    EXTI_cmd(PERIPH_EXTI_1,ENABLE);
    enableAllInterrupts();

    GPIO_setBitValue(PERIPH_GPIO_2,PERIPH_GPIO_PIN_0);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{
    sys_init();
    while(true);
}

/*****************************************************************************/
/** 
 * \author      Amy Chung
 * \date        
 * \brief       interrupt service function for EXTI1
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void exti1_isr(void) __interrupt IE1_VECTOR
{
    GPIO_toggleBitValue(PERIPH_GPIO_2,PERIPH_GPIO_PIN_0);
}
