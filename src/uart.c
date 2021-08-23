/*****************************************************************************/
/** 
 * \file        uart.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for UART
 * \note        
 * \version     v0.0
 * \ingroup     UART
******************************************************************************/

#include "hml/uart.h"

#ifdef COMPILE_UART

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable receive function
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setReceive(Action a)
{
    REN = a;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure UART module
 * \param[in]   uc: the pointer of configure structure
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_config(UART_configTypeDef *uc)
{
    /**
     * \note
     *  - UART_mode_0 (8-bit shift register)
     *    When UART_M0x6 bit is 0, the baud rate is _SYS_CLK_/12. Otherwise, it's _SYS_CLK_/2
     *  - UART_mode_1 (8-bit UART,variable baud rate)
     *    The baud rate is (2^SMOD)/32*[Overflow rate of baud rate generator]
     *
     *  How to calculate overflow rate of baud rate generator?
     *  >T1x12 = 0: the rate is _SYS_CLK_/12/(256-TH1)
     *  >T1x12 = 1: the rate is _SYS_CLK_/(256-TH1)
     *  >BRTx12 = 0: the rate is _SYS_CLK_/12/(256-BRT)
     *  >BRTx12 = 1: the rate is _SYS_CLK_/(256-BRT)
     */
    SCON = (SCON & 0x3F) | ((uint8_t)uc->mode << 0x6);
    CONFB(AUXR, BIT_NUM_S1BRS, uc->baudrateGenerator);
    if (uc->mode == UART_mode_0)
    {
        /**
         * \note
         *  0x00: the baud rate is equal to classical 8051 MCU (twelve divided-frequency)
         *  0x01 : the baud rate is two divided-frequency
         */
        CONFB(AUXR, BIT_NUM_UART_M0x6, uc->mode0Prescaler);
    }
    else
    {
        CONFB(PCON, BIT_NUM_PCON_SMOD, uc->doubleBaudrate);
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2020/02/09
 * \brief       get result of UART receiver
 * \param[in]   
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint8_t UART_getByte(void)
{
    return SBUF;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get state of receiver
 * \param[in]   
 * \return      SET(data have been received) or RESET
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART_isReceived(void)
{
    return (FunctionalState)RI;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get state of transmitter
 * \param[in]   
 * \return      SET(data have been transmitted) or RESET
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART_isTransmitted(void)
{
    return (FunctionalState)TI;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       send one byte of data via UART module
 * \param[in]   dat: expected data
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint8_t UART_sendByte(uint8_t dat)
{
    SBUF = dat;
    while(!TI);
    TI = RESET;
    return dat;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2020/02/09
 * \brief       output a hex number with character format via UART
 * \param[in]   hex: expected hex number(range: 0x0 ~ 0xF)
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_sendHex(uint8_t hex)
{
    UART_sendByte(hexTable[hex >> 0x4]);
    UART_sendByte(hexTable[hex & 0xF]);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       send a ASCII string via UART module
 * \param[in]   str: the point of expected string
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_sendString(char *str)
{
    while (*str != '\0')
    {
        SBUF = *str;
        while(!TI);
        TI = RESET;     /* clear */
        str++;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable interrupt of UART
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_INT_cmd(Action a)
{
    ES = a;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure interrupt priority class of UART
 * \param[in]   a: expected interrupt priority
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_INT_setPriority(IntPriority pri)
{
    switch (pri)
    {
        case IntPriority_Lowest:
            PS = RESET;
            CLRB(IPH, BIT_NUM_PSH);
            break;
        case IntPriority_Low:
            PS = SET;
            CLRB(IPH, BIT_NUM_PSH);
            break;
        case IntPriority_High:
            PS = RESET;
            SETB(IPH, BIT_NUM_PSH);
            break;
        case IntPriority_Highest:
            PS = SET;
            SETB(IPH, BIT_NUM_PSH);
            break;
        default: break;
    }
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
