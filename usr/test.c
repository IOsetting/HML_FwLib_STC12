/*****************************************************************************/
/** 
 * \file        test.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       a demo file
 * \note        
 * \version     v0.0
 * \ingroup     generic
 * \remarks     test-board: generic; test-MCU: generic
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
 * \remarks     The possible baudrate options are decided by your oscillator 
 *              frequency, prescaler and double-rate.
 *              For a 11.0592 MHz OSC, the highest baudrate is 691200, when you
 *              set prescaler=1 and enable double-rate.
 *              
******************************************************************************/
void sys_init(void)
{
    UART_configTypeDef uc;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;
    UART_config(&uc);
    RCC_BRT_config(115200, RCC_BRT_prescaler_1, uc.doubleBaudrate);
    UART_INT_cmd(ENABLE);
    UART_INT_setPriority(IntPriority_Low);
    UART_setReceive(ENABLE);
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
        /* send per 500ms */
        sleep(500);
        UART_sendString("Hello, world!\r\n");
    }
}