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
    UART2_configTypeDef uc;
    uc.baudrate                    = 115200;                         /* baud rate is 115200bps */
    uc.brtPrescaler                = RCC_BRT_prescaler_1;            /* 1T mode */
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.receiveState                = ENABLE;
    uc.pinmap                      = UART2_pinmap_P1;
    UART2_config(&uc);
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
