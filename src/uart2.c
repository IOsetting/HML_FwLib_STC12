/*****************************************************************************/
/** 
 * \file        uart2.c
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for UART2
 * \note        UART2 ports are P1.2(RX)/P1.3(TX), or P4.2(RX)/P4.3(TX)
 * \version     v0.1
 * \ingroup     UART
******************************************************************************/

#include "hml/uart2.h"

#ifdef COMPILE_UART


/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure UART2 module
 * \param[in]   uc: the pointer of configure structure
 * \return      none
 * \ingroup     UART
 * \remarks     need to invoke RCC_BRT_config() to make UART2 work
******************************************************************************/
void UART2_config(UART_configTypeDef *uc)
{
    /**
     * \note
     *  - UART_mode_0 (8-bit shift register)
     *    The baud rate is _SYS_CLK_/12
     *  - UART_mode_1 (8-bit UART,variable baud rate)
     *    The baud rate is (2^S2MOD)/32*[Overflow rate of BRT]
     *
     *  How to calculate overflow rate of baud rate generator?
     *  >BRTx12 = 0: the rate is _SYS_CLK_/12/(256-BRT)
     *  >BRTx12 = 1: the rate is _SYS_CLK_/(256-BRT)
     */

    S2CON = (S2CON & 0x3F) | ((uint8_t)uc->mode << 0x6);
    CONFB(AUXR, BIT_NUM_S2SMOD, uc->doubleBaudrate);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable receive function of UART2
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_setReceive(Action a)
{
    CONFB(S2CON, BIT_NUM_S2REN, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable interrupt of UART2
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_INT_cmd(Action a)
{
    CONFB(IE2, BIT_NUM_IE2_ES2, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure interrupt priority class of UART2
 * \param[in]   a: expected interrupt priority
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_INT_setPriority(IntPriority pri)
{
    switch (pri)
    {
        case IntPriority_Lowest:
            CLRB(IP2, BIT_NUM_IP2_PS2);
            CLRB(IP2H, BIT_NUM_IP2H_PS2H);
            break;
        case IntPriority_Low:
            SETB(IP2, BIT_NUM_IP2_PS2);
            CLRB(IP2H, BIT_NUM_IP2H_PS2H);
            break;
        case IntPriority_High:
            CLRB(IP2, BIT_NUM_IP2_PS2);
            SETB(IP2H, BIT_NUM_IP2H_PS2H);
            break;
        case IntPriority_Highest:
            SETB(IP2, BIT_NUM_IP2_PS2);
            SETB(IP2H, BIT_NUM_IP2H_PS2H);
            break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set input & output pin of UART2
 * \param[in]   pinmap: target pin map
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_setPinmap(UART2_pinmap pinmap)
{
    CONFB(AUXR1, BIT_NUM_S2_P4, pinmap);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get result of UART2 receiver
 * \param[in]   
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint8_t UART2_getByte(void)
{
    return S2BUF;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get state of UART2 receiver
 * \param[in]   
 * \return      SET(data have been received) or RESET
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART2_isReceived(void)
{
    return (FunctionalState)GET_BIT(S2CON, S2RI);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get state of UART2 transmitter
 * \param[in]   
 * \return      SET(data have been transmitted) or RESET
 * \ingroup     UART
 * \remarks     
******************************************************************************/
FunctionalState UART2_isTransmitted(void)
{
    return (FunctionalState)GET_BIT(S2CON, S2TI);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       send one byte of data via UART2
 * \param[in]   dat: expected data
 * \return      dat
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint8_t UART2_sendByte(uint8_t dat)
{
    S2BUF = dat;
    while(!TESTB(S2CON, BIT_NUM_S2TI));
    CLRB(S2CON, BIT_NUM_S2TI);
    return dat;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       output a hex number with character format via UART2
 * \param[in]   hex: expected hex number(range: 0x0 ~ 0xF)
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_sendHex(uint8_t hex)
{
    UART2_sendByte(hexTable[hex >> 0x4]);
    UART2_sendByte(hexTable[hex & 0xF]);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       send a ASCII string via UART2
 * \param[in]   str: the point of expected string
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_sendString(char *str)
{
    while (*str != '\0')
    {
        S2BUF = *str;
        while(!TESTB(S2CON, BIT_NUM_S2TI));
        CLRB(S2CON, BIT_NUM_S2TI);
        str++;
    }
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
