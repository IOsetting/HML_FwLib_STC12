/*****************************************************************************/
/** 
 * \file        uart_sendString_brt_12t.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       a example which shows how to send a string via UART
 * \note       
 * \version     v0.0
 * \ingroup     example
 * \remarks     test-board: ZS5110; test-MCU: STC11F16XE; use BRT-12T as baudrate
 *              generator
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
    UART_configTypeDef uc;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;
    UART_config(&uc);
    RCC_BRT_config(9600, RCC_BRT_prescaler_12, uc.doubleBaudrate);
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
