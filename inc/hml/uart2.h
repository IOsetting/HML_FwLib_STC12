/*****************************************************************************/
/** 
 * \file        uart2.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for UART2
 * \note        
 * \version     v0.1
 * \ingroup     UART2
******************************************************************************/

#ifndef ___HML_UART2_H___
#define ___HML_UART2_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/uart.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark function UART2 pin location
 */
typedef enum
{
    UART2_pinmap_P1 = 0x0,     /* P12(Rx)/P13(Tx) */
    UART2_pinmap_P4 = 0x1      /* P42(Rx)/P43(Tx) */
} UART2_pinmap;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/

void UART2_config(UART_configTypeDef *uc);
void UART2_setReceive(Action a);
void UART2_setPinmap(UART2_pinmap pinmap);
uint8_t UART2_getByte(void);
FunctionalState UART2_isReceived(void);
FunctionalState UART2_isTransmitted(void);
uint8_t UART2_sendByte(uint8_t dat);
void UART2_sendHex(uint8_t hex);
void UART2_sendString(char *str);
void UART2_INT_cmd(Action a);
void UART2_INT_setPriority(IntPriority pri);

#endif
