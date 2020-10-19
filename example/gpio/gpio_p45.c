/*****************************************************************************/
/** 
 * \file        gpio_p45.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       show how to use HML_FwLib_STC11 to toggle GPIO bit
 * \note        a example which shows how to configure pin ALE/P45 as GPIO
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
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{    
    GPIO_P45_cmd(ENABLE);
    GPIO_resetBitValue(PERIPH_GPIO_4, PERIPH_GPIO_PIN_5);

    /* blink */
    while(true)
    {
        sleep(500);
        GPIO_toggleBitValue(PERIPH_GPIO_4, PERIPH_GPIO_PIN_5);  /* P45 is connected to a LED for testing */
    }
}
