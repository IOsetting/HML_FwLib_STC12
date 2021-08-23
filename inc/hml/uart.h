/*****************************************************************************/
/** 
 * \file        uart.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for UART
 * \note        
 * \version     v0.1
 * \ingroup     UART
******************************************************************************/

#ifndef ___HML_UART_H___
#define ___HML_UART_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/rcc.h"
#include "hml/tim.h"

/*****************************************************************************
 *                             array define                                  *
 *****************************************************************************/
static __code char hexTable[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark mode0 baud rate
 */
typedef enum
{
    UART_Mode0BaudRatePrescaler_12   = 0x00,      /* SYSclk/12   */
    UART_Mode0BaudRatePrescaler_2    = 0x01,      /* SYSclk/2  */
} UART_Mode0BaudRatePrescaler;

/**
 * \brief mark work mode
 */
typedef enum
{
    UART_mode_0 = 0x0,  /* 8-bit shift register.
                         * UART_M0x6 = 0, baud rate = SYSclk/12, 
                         * UART_M0x6 = 1, baud rate = SYSclk/2 */
    UART_mode_1 = 0x1,  /* 8-bit UART,variable baud rate = (2^SMOD)/32*(TIM1 or BRT) */
    UART_mode_2 = 0x2,  /* 9-bit UART,baud rate = (2^SMOD)/64*_SYS_CLK_ */
    UART_mode_3 = 0x3   /* 9-bit UART,variable baud rate = (2^SMOD)/32*(TIM1 or BRT) */
} UART_mode;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure of UART.
 *        brtPrescaler is required when baudrateGenerator is BRT,
 *        timPrescaler is required when baudrateGenerator is TIM1,
 *        mode0Prescaler is required for UART_mode 0,
 *        doubleBaudrate is required for UART_mode 1,2,3
 */
typedef struct
{
    UART_mode      mode;
    UART_Mode0BaudRatePrescaler mode0Prescaler;
    Action         doubleBaudrate;
} UART_configTypeDef;


/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void UART_setBaudrateGeneratorBRT(uint32_t baudrate, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate);
void UART_setBaudrateGeneratorTIM1(uint32_t baudrate, TIM_prescaler  timPrescaler, Action doubleBaudrate);
void UART_setReceive(Action a);
void UART_config(UART_configTypeDef *uc);
uint8_t UART_getByte(void);
FunctionalState UART_isReceived(void);
FunctionalState UART_isTransmitted(void);
uint8_t UART_sendByte(uint8_t dat);
void UART_sendHex(uint8_t hex);
void UART_sendString(char *str);
void UART_INT_cmd(Action a);
void UART_INT_setPriority(IntPriority pri);

#endif
