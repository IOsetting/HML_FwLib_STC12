/*****************************************************************************/
/** 
 * \file        gpio_toggleIo.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       example show how to use HML_FwLib_STC11 to toggle GPIO bit
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
 * \author      Amy Chung
 * \date        
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{
    GPIO_resetBitValue(PERIPH_GPIO_2, PERIPH_GPIO_PIN_0);

    /* blink */
    while(true)
    {
        sleep(500);
        GPIO_toggleBitValue(PERIPH_GPIO_2, PERIPH_GPIO_PIN_0);
    }
}