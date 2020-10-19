/*****************************************************************************/
/** 
 * \file        wdt_feedDog.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       a example of watchdog module
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
    UART_configTypeDef uc;

    uc.baudrate                    = 9600;                           /* baud rate is 9600bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_tim1;    /* select timer-1 as baud rate generator */
    uc.baudGeneratorPrescalerState = ENABLE;
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.multiBaudrate               = DISABLE;
    uc.pinmap                      = UART_pinmap_0;
    uc.receiveState                = ENABLE;

    UART_config(&uc);
    WDT_setPrescale(WDT_prescale_32);
    WDT_cmd(ENABLE);
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
    UART_sendString("Startup MCU...\r\n");   /* startup info */

    while (true)
    {
        /*feed watchdog per 500ms*/
        sleep(500);
        WDT_feed();
        UART_sendString("watch dog has been fed\r\n");
    }
}

