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
 * \brief       set speed of UART module under mode 0
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_cmd_mode0_multiBaudrate(Action a)
{
    /**
     * \note
     *  DISABLE: the baud rate is equal to classical 8051 MCU (twelve divided-frequency)
     *  ENABLE : the baud rate is two divided-frequency
     */
    CONFB(AUXR, BIT_NUM_UART_M0x6, a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable multi-baudrate mode
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_cmd_multiBaudrate(Action a)
{
    CONFB(PCON, BIT_NUM_SMOD0, a);
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
void UART_cmd_receive(Action a)
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
    TIM_configTypeDef tc;
    unsigned int tmp = 0x0000;

    UART_cmd_receive(uc->receiveState);
    UART_setBaudGenerator(uc->baudrateGenerator);
    UART_setMode(uc->mode);
    UART_setPin(uc->pinmap);
    UART_INT_cmd(uc->interruptState);
    UART_INT_setPriority(uc->interruptPriority);

    if (uc->mode == UART_mode_0)
    {
        UART_cmd_mode0_multiBaudrate(uc->multiBaudrate);
    }
    else
    {
        UART_cmd_multiBaudrate(uc->multiBaudrate);
    }

    if (uc->baudrateGenerator == UART_baudrateGenerator_brt)
    {
        RCC_BRT_cmd(ENABLE);
        if(uc->baudGeneratorPrescalerState)
        {
            RCC_BRT_setPrescaler(RCC_BRT_prescaler_12);
        }
        else
        {
            RCC_BRT_setPrescaler(RCC_BRT_prescaler_1);
        }
        RCC_BRT_setValue(UART_getBaudGeneratorInitValue(UART_baudrateGenerator_brt, uc->baudrate));
    }
    else
    {
        tc.function          = TIM_function_tim;
        tc.interruptState    = DISABLE;
        tc.interruptPriority = DISABLE;
        tc.mode              = TIM_mode_2;
        /* configure prescaler */
        if (uc->baudGeneratorPrescalerState)
        {
            tc.prescaler = TIM_prescaler_12;
        }
        else
        {
            tc.prescaler = TIM_prescaler_1;
        }
        tc.value             = 0x00;   /* because of logic order, the value need to be reloaded one more time */
        TIM_config(PERIPH_TIM_1, &tc);
        TIM_cmd(PERIPH_TIM_1, ENABLE);
        TIM_setValue(PERIPH_TIM_1, \
                     UART_getBaudGeneratorInitValue(UART_baudrateGenerator_tim1, uc->baudrate));
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get 16-bit initial value depend on baud rate generator
 * \param[in]   gen: target baud rate generator
 * \param[in]   baud: expected baud rate
 * \return      result(0x00 means overflow)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint16_t UART_getBaudGeneratorInitValue(UART_baudrateGenerator gen, uint32_t baud)
{
    /* multi baud rate */
    uint8_t   flag_pre  = 0x0;
    uint8_t   flag_smod = 0x0;
    uint16_t  res       = 0x0000;

    /* check prescaler */
    if (gen == UART_baudrateGenerator_brt)
    {
        flag_pre = GET_BIT(AUXR, BRTx12);
    }
    else
    {
        flag_pre = GET_BIT(AUXR, T1x12);
    }

    /* check multi-rate control bit */
    if (PCON & 0x80)
    {
        flag_smod = 0x1;
    }

    /* calculate */
    if (flag_pre)
    {
        /* check overflow */
        if (baud < RCC_getSystemClockFrequency()/16*pow(2, flag_smod))
        {
            res = (unsigned char)(256 - RCC_getSystemClockFrequency()/baud/32);
        }
    }
    else
    {
        if (baud < RCC_getSystemClockFrequency()/12/16*pow(2, flag_smod))
        {
            res = (unsigned char)(256 - RCC_getSystemClockFrequency()/baud/12/32*pow(2, flag_smod));
        }
    }

    if (gen != UART_baudrateGenerator_brt)
    {
        res = res & 0x00FF;
        res = (res << 0x8) | res;
    }

    return res;
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
    while(*str != '\0')
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
 * \brief       set input & output pin of UART module
 * \param[in]   pm: target pin map
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_setPin(UART_pinmap pm)
{
    CONFB(AUXR1, BIT_NUM_UART_P1, pm);
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
 * \author      Weilun Fong
 * \date        
 * \brief       configure interrupt priority class of UART
 * \param[in]   a: expected interrupt priority, the value must be SET(high priority)
 *              or RESET
 * \return      none
 * \ingroup     UART
 * \remarks     
******************************************************************************/
void UART_INT_setPriority(Action a)
{
    PS = a;
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
