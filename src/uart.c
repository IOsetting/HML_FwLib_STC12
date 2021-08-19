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
 * \brief       set the baud-rate of UART in mode 0 to SYSclk/12 or SYSclk/2
 * \param[in]   a: expected prescaler
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setMode0BaudRatePrescaler(UART_Mode0BaudRatePrescaler prescaler)
{
    /**
     * \note
     *  0x00: the baud rate is equal to classical 8051 MCU (twelve divided-frequency)
     *  0x01 : the baud rate is two divided-frequency
     */
    CONFB(AUXR, BIT_NUM_UART_M0x6, prescaler);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable double-baudrate mode
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setDoubleBaudrate(Action a)
{
    CONFB(PCON, BIT_NUM_PCON_SMOD, a);
}

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
 * \author      IOsetting
 * \date        
 * \brief       get 16-bit initial value of BRT baud rate generator
 * \param[in]   baud: expected baud rate
 * \return      result(0x00 means overflow)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
static uint16_t UART_getBrtInitValue(uint32_t baud, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate)
{
    uint16_t res = 0x0000;
    uint32_t max = RCC_getSystemClockFrequency();
    if (brtPrescaler == RCC_BRT_prescaler_12)
    {
        max = max / 12;
    }
    if (doubleBaudrate == ENABLE) 
    {
        max = max * 2;
    }
    if (baud <= max/32)
    {
        res = (uint16_t)(256 - max/baud/32);
    }
    return res;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get 16-bit initial value of TIM1 baud rate generator
 * \param[in]   baud: expected baud rate
 * \return      result(0x00 means overflow)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
static uint16_t UART_getTim1InitValue(uint32_t baud, TIM_prescaler  timPrescaler, Action doubleBaudrate)
{
    uint16_t res = 0x0000;
    uint32_t max = RCC_getSystemClockFrequency() / timPrescaler;
    if (doubleBaudrate == ENABLE) 
    {
        max = max * 2;
    }
    if (baud <= max/32)
    {
        res = (uint16_t)(256 - max/baud/32);
    }
    res = res & 0x00FF;
    res = (res << 0x8) | res;
    return res;
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
    UART_setReceive(uc->receiveState);
    UART_setBaudGenerator(uc->baudrateGenerator);
    UART_setMode(uc->mode);
    /* UART1 pin is fixed in STC12 */
    //UART2_setPinmap(uc->pinmap);
    UART_INT_cmd(uc->interruptState);
    UART_INT_setPriority(uc->interruptPriority);

    if (uc->mode == UART_mode_0)
    {
        UART_setMode0BaudRatePrescaler(uc->mode0Prescaler);
    }
    else
    {
        UART_setDoubleBaudrate(uc->doubleBaudrate);
    }

    if (uc->baudrateGenerator == UART_baudrateGenerator_brt)
    {
        RCC_BRT_cmd(ENABLE);
        RCC_BRT_setPrescaler(uc->brtPrescaler);
        RCC_BRT_setValue(UART_getBrtInitValue(uc->baudrate, uc->brtPrescaler, uc->doubleBaudrate));
    }
    else
    {
        TIM_configTypeDef tc;
        tc.function          = TIM_function_tim;
        tc.interruptState    = DISABLE;
        tc.interruptPriority = DISABLE;
        tc.mode              = TIM_mode_2;
        tc.prescaler         = uc->timPrescaler;
        tc.value             = 0x00;   /* because of logic order, the value need to be reloaded one more time */
        TIM_config(PERIPH_TIM_1, &tc);
        TIM_cmd(PERIPH_TIM_1, ENABLE);
        TIM_setValue(PERIPH_TIM_1, \
                     UART_getTim1InitValue(uc->baudrate, uc->timPrescaler, uc->doubleBaudrate));
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
byte UART_getByte(void)
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
void UART_sendByte(byte dat)
{
    SBUF = dat;
    while(!TI);
    TI = RESET;
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
 * \brief       specify baud rate generator of UART
 * \param[in]   gen: expected generator
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setBaudGenerator(UART_baudrateGenerator gen)
{
    CONFB(AUXR, BIT_NUM_S1BRS, gen);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set work mode of UART
 * \param[in]   mode: expected work mode
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setMode(UART_mode mode)
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

    SCON = (SCON & 0x3F) | ((uint8_t)mode << 0x6);
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

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure UART2 module
 * \param[in]   uc: the pointer of configure structure
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_config(UART2_configTypeDef *uc)
{
    UART2_setReceive(uc->receiveState);
    UART2_setMode(uc->mode);
    UART2_setPinmap(uc->pinmap);
    UART2_INT_cmd(uc->interruptState);
    UART2_INT_setPriority(uc->interruptPriority);
    UART2_setDoubleBaudrate(uc->doubleBaudrate);
    RCC_BRT_cmd(ENABLE);
    RCC_BRT_setPrescaler(uc->brtPrescaler);
    RCC_BRT_setValue(UART_getBrtInitValue(uc->baudrate, uc->brtPrescaler, uc->doubleBaudrate));
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
 * \brief       enable or disable double-baudrate mode of UART2
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_setDoubleBaudrate(Action a)
{
    CONFB(AUXR, BIT_NUM_S2SMOD, a);
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
byte UART2_getByte(void)
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
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_sendByte(byte dat)
{
    S2BUF = dat;
    while(!TESTB(S2CON, BIT_NUM_S2TI));
    CLRB(S2CON, BIT_NUM_S2TI);
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

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set work mode of UART2
 * \param[in]   mode: expected work mode
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART2_setMode(UART_mode mode)
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

    S2CON = (S2CON & 0x3F) | ((uint8_t)mode << 0x6);
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

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
