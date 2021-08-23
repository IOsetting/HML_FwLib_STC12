/*****************************************************************************/
/** 
 * \file        rcc_softwareReset.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       example for software reset
 * \note        a example which shows software reset via state of \
 *              IO(connected to LED)
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
    UTIL_setInterrupts(ENABLE);
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
    while (true)
    {
        sleep(500);
        GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_0);
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       interrupt service function for EXTI0
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void exti0_isr(void) __interrupt IE0_VECTOR
{
    disableAllInterrupts();

    /* indicate the MCU is going to reset */
    GPIO_setBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_0 | PERIPH_GPIO_PIN_1 | PERIPH_GPIO_PIN_2);
    sleep(500);
    GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_0);
    sleep(250);
    GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_1);
    sleep(250);
    GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_2);
    sleep(250);

    RCC_softwareReset();
}
