/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:includes some definitions for operating UART module
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___UART_H___
#define ___UART_H___

/* ----- @header file ----- */
#include <stdint.h>
#include "stc11.h"
#include "macro.h"
#include "rcc.h"
#include "tim.h"
#include "util.h"

/* ----- @enumeration type ----- */
/* mark baud rate generator of UART */
typedef enum
{
    UART_baudrateGenerator_brt  = 0x1,    /* independent baud rate generator */
    UART_baudrateGenerator_tim1 = 0x0     /* timer 1 */
} UART_baudrateGenerator;

/* mark work mode */
typedef enum
{
    UART_mode_0 = 0x0,  /* 8-bit shift register */
    UART_mode_1 = 0x1,  /* 8-bit UART,variable baud rate */
    UART_mode_2 = 0x2,  /* 9-bit UART,baud rate = (2^SMOD)/64*_SYS_CLK_ */
    UART_mode_3 = 0x3   /* 9-bit UART,variable baud rate */
} UART_mode;

/* mark function pin location */
typedef enum
{
    UART_pinmap_0 = 0x0,     /* P30(Rx)/P31(Tx) */
    UART_pinmap_1 = 0x1      /* P16(Rx)/P17(Tx) */
} UART_pinmap;

/* ----- @structure define ----- */
/* mark configure structure */
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

/* ----- @function ----- */
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
void UART_BRT_cmd(Action a);
void UART_BRT_setPrescaler(RCC_BRT_prescaler pre);
void UART_BRT_setValue(unsigned char val);
void UART_INT_setPriority(Action a);
void UART_INT_cmd(Action a);

#endif
