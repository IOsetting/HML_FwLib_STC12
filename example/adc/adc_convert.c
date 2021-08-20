/*****************************************************************************/
/** 
 * \file        adc_convert.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of A/D conversion in polling mode
 * \note        An example of using HML_FwLib_STC12 to convert analog input
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
 * \brief       initialize UART on P3.0/P3.1 and ADC on P1.0/P1.1
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

    ADC_configTypeDef ac;
    ac.channelPins              = PERIPH_GPIO_PIN_0|PERIPH_GPIO_PIN_1;
    ac.channel                  = ADC_Channel_0;
    ac.interruptState           = DISABLE;
    ac.power                    = ENABLE;
    ac.sampleTime               = ADC_SampleTime_540Cycles;

    ADC_config(&ac);

    enableAllInterrupts();
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

    while (true)
    {
        uint8_t result = ADC_convert(ADC_Channel_0);
        UART_sendHex(result);
        UART_sendString("\r\n");
        sleep(300);
    }
}
