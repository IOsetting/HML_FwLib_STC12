/*****************************************************************************/
/** 
 * \file       uart_sendString(tim1-12T).c
 * \author     Weilun Fong | wlf@zhishan-iot.tk
 * \date       
 * \brief      a example which shows how to send a string via UART
 * \note       
 * \version    v0.0
 * \ingroup    example
 * \remarks    test-board: ZS5110; test-MCU: STC11F16XE; use TIM1 as baudrate
 *             generator
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
    UART_configTypeDef uc;
    
    uc.baudrate                    = 9600;                           /* baud rate is 9600bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_tim1;    /* select timer-1 as baud rate generator */
    uc.baudGeneratorPrescalerState = ENABLE;                         /* 12T mode */
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.multiBaudrate               = DISABLE;
    uc.pinmap                      = UART_pinmap_0;
    uc.receiveState                = ENABLE;

    UART_config(&uc);
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

    while(true)
    {
        /* send per 500ms */
        sleep(500);
        UART_sendString("Hello,world!\r\n");
    }
}
