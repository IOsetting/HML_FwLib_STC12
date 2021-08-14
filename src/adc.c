/*****************************************************************************/
/** 
 * \file        adc.c
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for ADC
 * \note        
 * \version     v0.0
 * \ingroup     ADC
******************************************************************************/

#include "hml/adc.h"

#ifdef COMPILE_ADC

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure ADC module
 * \param[in]   ac: the pointer of configure structure
 * \return      none
 * \ingroup     ADC
 * \remarks     
******************************************************************************/
void ADC_config(ADC_configTypeDef *ac)
{
    ADC_setPin(ac->channelPins);
    ADC_CONTR = ac->sampleTime | ac->channel;
    ADC_INT_cmd(ac->interruptState);
    ADC_Power_cmd(ac->power);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       Set P1.x as ADC input channel-x
 * \param[in]   pins: pins to be work as ADC input channel
 * \return      none
 * \ingroup     ADC
 * \remarks     
*******************************************UART***********************************/
void ADC_setPin(uint8_t pins)
{
    P1ASF = pins;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set channel to be converted
 * \param[in]   ch: target channel
 * \return      none
 * \ingroup     ADC
 * \remarks     
******************************************************************************/
void ADC_setChannel(ADC_channel ch)
{
    ADC_CONTR = (ADC_CONTR & 0xF8) | ch;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable interrupt of ADC
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     ADC
 * \remarks     
*******************************************UART***********************************/
void ADC_INT_cmd(Action a)
{
    EADC = a;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       Clear ADC interrupt flag. It will be set by the device after the 
 *              device has finished a conversion, and should be cleared by the 
 *              user's software
 * \param[in]   
 * \return      none
 * \ingroup     ADC
 * \remarks     
*******************************************UART***********************************/
void ADC_INT_clear(void)
{
    CLRB(ADC_CONTR, BIT_NUM_ADC_FLAG);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable ADC module
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     ADC
 * \remarks     
******************************************************************************/
void ADC_Power_cmd(Action a)
{
    CONFB(ADC_CONTR, BIT_NUM_ADC_POWER, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       start ADC conversion
 * \param[in]   
 * \return      none
 * \ingroup     ADC
 * \remarks     
******************************************************************************/
void ADC_start(void)
{
    SETB(ADC_CONTR, BIT_NUM_ADC_START);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       start a single ADC conversion
 * \param[in]   ch: target channel
 * \return      none
 * \ingroup     ADC
 * \remarks     
******************************************************************************/
byte ADC_convert(ADC_channel ch)
{
    ADC_setChannel(ch);
    ADC_start();
    NOP();
    NOP();
    NOP();
    NOP();
    /* Wait complete flag */
    while(!TESTB(ADC_CONTR, BIT_NUM_ADC_FLAG));
    ADC_INT_clear();
    return ADC_RES;
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
