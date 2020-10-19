/*****************************************************************************/
/** 
 * \file        pwr_idleMode.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       example for idle mode
 * \note        (1) a example which shows how to enter into idle mode and recover 
 *              from it
 * \version     v0.0
 * \ingroup     example
 * \remarks     test-board: ZS5110; test-MCU: STC11F16XE
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

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
    EXTI_config(PERIPH_EXTI_0, &ec);
    EXTI_cmd(PERIPH_EXTI_0, ENABLE);

    GPIO_configPortValue(PERIPH_GPIO_1, 0xFF);
    enableAllInterrupts();
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

    while( true)
    {
        sleep(200);
        GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_0);
        /* check state of KEY(connected to P33) */
        if (GPIO_getBitValue(PERIPH_GPIO_3, PERIPH_GPIO_PIN_3) == RESET)
        {
            /* avoid shake */
            sleep(5);
            if(GPIO_getBitValue(PERIPH_GPIO_3, PERIPH_GPIO_PIN_3) == RESET)
            {
                PWR_idle();  /* enter into idle mode */
            }
        }
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       interrupt handle function for EXTI0
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void exti0_isr(void) __interrupt IE0_VECTOR
{    
    /* do nothing, recover when extern interrupt is triggered */
}
