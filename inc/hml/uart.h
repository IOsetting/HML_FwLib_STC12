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
 * \brief mark baud rate generator of UART
 */
typedef enum
{
    UART_baudrateGenerator_brt  = 0x1,    /* independent baud rate generator */
    UART_baudrateGenerator_tim1 = 0x0     /* timer 1 */
} UART_baudrateGenerator;

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

/**
 * \brief mark function UART2 pin location
 */
typedef enum
{
    UART_pinmap_P1 = 0x0,     /* P12(Rx)/P13(Tx) */
    UART_pinmap_P4 = 0x1      /* P42(Rx)/P43(Tx) */
} UART2_pinmap;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure
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
    UART2_pinmap   pinmap;
    Action         receiveState;
} UART_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/
void UART_cmd_mode0_multiBaudrate(Action a);
void UART_cmd_multiBaudrate(Action a);
void UART_cmd_receive(Action a);
void UART_config(UART_configTypeDef *uc);
uint16_t UART_getBaudGeneratorInitValue(UART_baudrateGenerator gen, uint32_t baud);
byte UART_getByte(void);
FunctionalState UART_isReceived(void);
FunctionalState UART_isTransmitted(void);
void UART_sendByte(byte dat);
void UART_sendHex(uint8_t hex);
void UART_sendString(char *str);
void UART_setBaudGenerator(UART_baudrateGenerator gen);
void UART_setMode(UART_mode mode);
void UART_INT_cmd(Action a);
void UART_INT_setPriority(IntPriority pri);

void UART2_sendByte(byte dat);
void UART2_sendHex(uint8_t hex);
void UART2_sendString(char *str);
void UART2_INT_cmd(Action a);
void UART2_INT_setPriority(IntPriority pri);
void UART2_setMode(UART_mode mode);
void UART2_setPinmap(UART2_pinmap pinmap);


#endif
