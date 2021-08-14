/*****************************************************************************/
/** 
 * \file        adc.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for ADC
 * \note        
 * \version     v0.1
 * \ingroup     ADC
******************************************************************************/

#ifndef ___HML_ADC_H___
#define ___HML_ADC_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/rcc.h"
#include "hml/tim.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark sample time
 */
typedef enum
{
    ADC_SampleTime_540Cycles = 0x00, /* 540 cycles */
    ADC_SampleTime_360Cycles = 0x20,
    ADC_SampleTime_180Cycles = 0x40,
    ADC_SampleTime_90Cycles  = 0x60
} ADC_sampleTime;

/**
 * \brief mark channel
 */
typedef enum
{
    ADC_Channel_0 = 0x00, /* P1.0 (default) as the A/D channel input */
    ADC_Channel_1 = 0x01, /* P1.1 as the A/D channel input */
    ADC_Channel_2 = 0x02,
    ADC_Channel_3 = 0x03,
    ADC_Channel_4 = 0x04,
    ADC_Channel_5 = 0x05,
    ADC_Channel_6 = 0x06,
    ADC_Channel_7 = 0x07,
} ADC_channel;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure
 */
typedef struct
{
    uint8_t        channelPins;
    ADC_channel    channel;
    Action         interruptState;
    Action         power;
    ADC_sampleTime sampleTime;
} ADC_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void ADC_config(ADC_configTypeDef *ac);
void ADC_setPin(uint8_t pins);
void ADC_setChannel(ADC_channel ch);
void ADC_INT_cmd(Action a);
void ADC_INT_clear(void);
void ADC_Power_cmd(Action a);
void ADC_start(void);
byte ADC_convert(ADC_channel ch);

#endif
