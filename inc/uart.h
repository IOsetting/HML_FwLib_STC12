/*****************************************************************************/
/** 
 * \file        uart.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for UART
 * \note        
 * \version     v0.1
 * \ingroup     UART
******************************************************************************/

#ifndef ___UART_H___
#define ___UART_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include <stdint.h>
/*****************************************************************************/
#include "rcc.h"
#include "tim.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/
/**
 *\brief: mark baud rate generator of UART
 */
typedef enum
{
    UART_baudrateGenerator_brt  = 0x1,    /* independent baud rate generator */
    UART_baudrateGenerator_tim1 = 0x0     /* timer 1 */
} UART_baudrateGenerator;

/**
 *\brief: mark work mode
 */
typedef enum
{
    UART_mode_0 = 0x0,  /* 8-bit shift register */
    UART_mode_1 = 0x1,  /* 8-bit UART,variable baud rate */
    UART_mode_2 = 0x2,  /* 9-bit UART,baud rate = (2^SMOD)/64*_SYS_CLK_ */
    UART_mode_3 = 0x3   /* 9-bit UART,variable baud rate */
} UART_mode;

/**
 *\brief: mark function pin location
 */
typedef enum
{
    UART_pinmap_0 = 0x0,     /* P30(Rx)/P31(Tx) */
    UART_pinmap_1 = 0x1      /* P16(Rx)/P17(Tx) */
} UART_pinmap;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 *\brief: mark configure structure
 */
typedef struct
{
    uint32_t       baudrate;
    UART_baudrateGenerator baudrateGenerator;
    Action         baudGeneratorPrescalerState;
    Action         interruptState;
    Action         interruptPriority;
    UART_mode      mode;
    Action         multiBaudrate;
    UART_pinmap    pinmap;
    Action         receiveState;
} UART_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void UART_cmd_mode0_multiBaudrate(Action a);
void UART_cmd_multiBaudrate(Action a);
void UART_cmd_receive(Action a);
void UART_config(UART_configTypeDef *uc);
unsigned int UART_getBaudGeneratorInitValue(UART_baudrateGenerator gen,uint32_t baud);
FunctionalState UART_isReceived(void);
FunctionalState UART_isTransmitted(void);
void UART_sendByte(byte dat);
void UART_sendString(char *str);
void UART_setBaudGenerator(UART_baudrateGenerator gen);
void UART_setMode(UART_mode m);
void UART_setPin(UART_pinmap pm);
void UART_INT_cmd(Action a);
void UART_INT_setPriority(Action a);

#endif
