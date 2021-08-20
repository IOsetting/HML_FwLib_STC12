/*****************************************************************************/
/** 
 * \file        pwm_led_fade.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of PWM output
 * \note        An example of using HML_FwLib_STC12 to generate PWM output
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5AF56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

uint8_t d = 0x00, v = 0x00;

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize UART on P3.0/P3.1 and PWM output on P1.3/P1.4
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void initSys(void)
{
    UART_configTypeDef uc;

    uc.baudrate                    = 115200;                        /* baud rate is 115200bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;    /* select BRT as baud rate generator */
    uc.brtPrescaler                = RCC_BRT_prescaler_1;           /* 1T mode */
    uc.interruptState              = DISABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.receiveState                = ENABLE;

    UART_config(&uc);

    PCA_configTypeDef pc;
    pc.mode              = PCA_mode_PWM_NoInt;
    pc.pulseSource       = PCA_counterPulseSource_SysClkDivBy2;
    pc.overflowInterrupt = DISABLE;
    pc.stopIdleCount     = DISABLE;
    pc.pinmap            = PCA_pinmap_P1;
    pc.compareValue      = 0x80;
    pc.pwmOutputMode     = PCA_pwm_Normal;
    pc.start             = DISABLE;

    PCA_config(PERIPH_PCA_0, &pc);
    PCA_config(PERIPH_PCA_1, &pc);
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
    initSys();
    PCA_start(ENABLE);

    while (true)
    {
        PCA_setCompareValue(PERIPH_PCA_0, v);
        PCA_setCompareValue(PERIPH_PCA_1, ~v);
        if (d) {
            if (++v == 0xff) {
                d = 0;
            }
        } else {
            if (--v== 0x00) {
                d = 1;
            }
        }
        UART_sendHex(v);
        UART_sendString("\r\n");
        sleep(10);
    }
}
