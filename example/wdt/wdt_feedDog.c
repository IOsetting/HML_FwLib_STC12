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
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    UART_config(&uc);
    UART_setBaudrateGeneratorTIM1(9600, TIM_prescaler_1, DISABLE);
    UART_INT_cmd(ENABLE);
    UART_INT_setPriority(IntPriority_Low);
    UART_setReceive(ENABLE);

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

