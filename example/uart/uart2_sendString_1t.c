/*****************************************************************************/
/** 
 * \file        uart2_sendString_1t.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       a example which shows how to send a string via UART2
 * \note        
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5AF56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

/*****************************************************************************/
/** 
 * \author      IOsetting
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
    UART2_config(&uc);
    RCC_BRT_config(115200, RCC_BRT_prescaler_1, DISABLE);
    UART2_INT_cmd(ENABLE);
    UART2_INT_setPriority(IntPriority_Low);
    UART2_setReceive(ENABLE);
    UART2_setPinmap(UART2_pinmap_P1);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
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
        UART2_sendString("Hello, world!\r\n");
    }
}
