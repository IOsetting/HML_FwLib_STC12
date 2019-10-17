/*****************************************************************************/
/** 
 * \file       test.c
 * \author     Weilun Fong | wlf@zhishan-iot.tk
 * \date       
 * \brief      a demo file
 * \note       
 * \version    v0.0
 * \ingroup    generic
 * \remarks    test-board: generic; test-MCU: generic
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

    uc.baudrate                    = 115200;                        /* baud rate is 115200bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;    /* select BRT as baud rate generator */
    uc.baudGeneratorPrescalerState = DISABLE;                       /* 1T mode */
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
