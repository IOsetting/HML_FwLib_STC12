/*****************************************************************************/
/** 
 * \file        tim_toggleIo.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       a example which shows how to toggle state of specified pin periodic
 *              via timers' interrupt
 * \note        
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
    TIM_configTypeDef tc;

    tc.function          = TIM_function_tim;
    tc.interruptState    = ENABLE;
    tc.interruptPriority = DISABLE;
    tc.mode              = TIM_mode_1;
    tc.prescaler         = TIM_prescaler_12;
    tc.value             = 65536-50000;

    TIM_config(PERIPH_TIM_0, &tc);
    enableAllInterrupts();
    TIM_cmd(PERIPH_TIM_0, ENABLE);
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
 * \author      Weilun Fong
 * \date        
 * \brief       interrupt service function for TIM0
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void tim0_isr(void) __interrupt TF0_VECTOR
{
    static uint8_t i = 0;

    TIM_setValue(PERIPH_TIM_0, 65536-50000); /* reload initial value */
    i++;

    /* 20*50ms = 1s */
    if (i >= 20)
    {
        GPIO_toggleBitValue(PERIPH_GPIO_1, PERIPH_GPIO_PIN_0);
        i = 0;     /* clear */
    }
}
