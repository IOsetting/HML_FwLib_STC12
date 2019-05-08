/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:includes some definitions for operating UART module
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#include "uart.h"

#ifdef ___COMPILE_UART___

/*
 * @Prototype:void UART_cmd_mode0_multiBaudrate(Action a);
 * @Parameter:(1)a:expected action
 * @Ret-val:None
 * @Note:set speed of UART module under mode 0
 */
void UART_cmd_mode0_multiBaudrate(Action a)
{
    /*
     * DISABLE: the baud rate is equal to classical 8051 MCU (twelve divided-frequency)
     * ENABLE : the baud rate is two divided-frequency
     */
    CONFB(AUXR,BIT_NUM_UART_M0x6,a);
}

/*
 * @Prototype:void UART_cmd_multiBaudrate(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:None
 * @Note:set multi-baudrate state of UART module under mode 1-3
 */
void UART_cmd_multiBaudrate(Action a)
{
    CONFB(PCON,BIT_NUM_SMOD0,a);
}

/*
 * @Prototype:void UART_cmd_receive(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable receive function of UART module
 */
void UART_cmd_receive(Action a)
{
    REN = a;
}

/*
 * @Prototype:void UART_config(UART_configTypeDef *uc,PERIPH_TIM tim)
 * @Parameter:(1)uc:the pointer of configure structure (2)tim:target timer module
 * @Ret-val:None
 * @Note:configure UART module
 */
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

    if(uc->mode == UART_mode_0)
    {
        UART_cmd_mode0_multiBaudrate(uc->multiBaudrate);
    }
    else
    {
        UART_cmd_multiBaudrate(uc->multiBaudrate);
    }
    
    if(uc->baudrateGenerator == UART_baudrateGenerator_brt)
    {
        UART_BRT_cmd(ENABLE);
        if(uc->baudGeneratorPrescalerState)
        {
            RCC_BRT_setPrescaler(RCC_BRT_prescaler_12);
        }
        else
        {
            RCC_BRT_setPrescaler(RCC_BRT_prescaler_1);
        }
        UART_BRT_setValue(UART_getBaudGeneratorInitValue(UART_baudrateGenerator_brt,uc->baudrate));
    }
    else
    {
        tc.function          = TIM_function_tim;
        tc.interruptState    = DISABLE;
        tc.interruptPriority = DISABLE;
        tc.mode              = TIM_mode_2;
        /* configure prescaler */
        if(uc->baudGeneratorPrescalerState)
        {
            tc.prescaler = TIM_prescaler_12;
        }
        else
        {
            tc.prescaler = TIM_prescaler_1;
        }
        tc.value             = 0x00;   /* because of logic order, the value need to be reloaded one more time */
        TIM_config(PERIPH_TIM_1,&tc);
        TIM_cmd(PERIPH_TIM_1,ENABLE);
        TIM_setValue(PERIPH_TIM_1,UART_getBaudGeneratorInitValue(UART_baudrateGenerator_tim1,uc->baudrate));
    }
}

/*
 * @Prototype:unsigned int UART_getBaudGeneratorInitValue(UART_baudrateGenerator gen,uint32_t baud)
 * @Parameter:(1)gen:target baud rate generator;(2)baud:expected baud rate
 * @Ret-val:(1)0x00:overflow;(2)other value:valid result
 * @Note:get 16-bit initial value depend on baud rate generator
 */
unsigned int UART_getBaudGeneratorInitValue(UART_baudrateGenerator gen,uint32_t baud)
{
    /* multi baud rate */
    unsigned char flag_pre  = 0x0;
    unsigned char flag_smod = 0x0;
    unsigned int  res = 0x0000;
    
    /* check prescaler */
    if(gen == UART_baudrateGenerator_brt)
    {
        flag_pre = GET_BIT(AUXR,BRTx12);
    }
    else
    {
        flag_pre = GET_BIT(AUXR,T1x12);
    }
    
    /* check multi-rate control bit */
    if(PCON & 0x80)
    {
        flag_smod = 0x1;
    }
    
    
    /* calculate */
    if(flag_pre)
    {
        /* check overflow */
        if(baud < RCC_getSystemClockFrequency()/16*pow(2,flag_smod))
        {
            res = (unsigned char)(256 - RCC_getSystemClockFrequency()/baud/32);
        }
    }
    else
    {
        if(baud < RCC_getSystemClockFrequency()/12/16*pow(2,flag_smod))
        {
            res = (unsigned char)(256 - RCC_getSystemClockFrequency()/baud/12/32*pow(2,flag_smod));
        }
    }
    
    if(gen != UART_baudrateGenerator_brt)
    {
        res = res & 0x00FF;
        res = (res << 0x8) | res;
    }
    
    return res;
}

/*
 * @Prototype:FunctionalState UART_isReceived(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been received;(2)RESET:data haven't been received
 * @Note:
 */
FunctionalState UART_isReceived(void)
{
    return (FunctionalState)RI;
}

/*
 * @Prototype:FunctionalState UART_isTransmitted(void)
 * @Parameter:
 * @Ret-val:(1)SET:data have been transmitted;(2)RESET:data haven't been transmitted
 * @Note:
 */
FunctionalState UART_isTransmitted(void)
{
    return (FunctionalState)TI;
}

/*
 * @Prototype:void UART_sendByte(byte dat)
 * @Parameter:(1)dat:one byte of data user want to send
 * @Ret-val:
 * @Note:send a byte via UART module
 */
void UART_sendByte(byte dat)
{
    SBUF = dat;
    while(!TI);
    TI = RESET;
}

/*
 * @Prototype:void UART_sendString(char *str)
 * @Parameter:(1)str:the point of string user want to send
 * @Ret-val:
 * @Note:send a ASCII string via UART module
 */
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

/*
 * @Prototype:void UART_setBaudGenerator(UART_baudrateGenerator gen)
 * @Parameter:(1)gen:expected generator
 * @Ret-val:None
 * @Note:specify baud rate generator of UART
 */
void UART_setBaudGenerator(UART_baudrateGenerator gen)
{
    CONFB(AUXR,BIT_NUM_S1BRS,gen);
}

/*
 * @Prototype:void UART_setMode(UART_mode m)
 * @Parameter:(1)m:expected work mode
 * @Ret-val:
 * @Note:set work mode of UART module
 */
void UART_setMode(UART_mode m)
{
    /*
     * @Extra-note:
     *  A.UART_mode_0 (8-bit shift register)
     *    When UART_M0x6 bit is 0, the baud rate is _SYS_CLK_/12. Otherwise, it's _SYS_CLK_/2
     *  B.UART_mode_1 (8-bit UART,variable baud rate)
     *    The baud rate is (2^SMOD)/32*[Overflow rate of baud rate generator]
     *
     * @How to calculate overflow rate of baud rate generator?
     *  >T1x12 = 0: the rate is _SYS_CLK_/12/(256-TH1)
     *  >T1x12 = 1: the rate is _SYS_CLK_/(256-TH1)
     *  >BRTx12 = 0: the rate is _SYS_CLK_/12/(256-BRT)
     *  >BRTx12 = 1: the rate is _SYS_CLK_/(256-BRT)
     */
    
    SCON = (SCON & 0x3F) | ((unsigned char)m << 0x6);
}

/*
 * @Prototype:void UART_setPin(UART_pinmap pm)
 * @Parameter:(1)pm:target pin map
 * @Ret-val:None
 * @Note:
 */
void UART_setPin(UART_pinmap pm)
{
    CONFB(AUXR1,BIT_NUM_UART_P1,pm);
}

/*
 * @Prototype:void UART_BRT_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:None
 * @Note:control state of BRT module, make it is in enable or disable state
 */
void UART_BRT_cmd(Action a)
{
    RCC_BRT_cmd(a);
}

/*
 * @Prototype:void UART_BRT_setPrescaler(RCC_BRT_prescaler pre)
 * @Parameter:(1)pre:prescaler mode
 * @Ret-val:None
 * @Note:configure prescaler mode of BRT module
 */
void UART_BRT_setPrescaler(RCC_BRT_prescaler pre)
{
    RCC_BRT_setPrescaler(pre);
}

/*
 * @Prototype:void UART_BRT_setValue(unsigned char val)
 * @Parameter:(1)val:auto reload value(8-bit)
 * @Ret-val:None
 * @Note:
 */
void UART_BRT_setValue(unsigned char val)
{
    RCC_BRT_setValue(val);
}

/*
 * @Prototype:void UART_INT_setPriority(Action a)
 * @Parameter:(1)a:enable interrupt priority or not
 * @Ret-val:
 * @Note:set priority of UART module
 */
void UART_INT_setPriority(Action a)
{
    PS = a;
}

/*
 * @Prototype:void UART_INT_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable interrupt function of UART module
 */
void UART_INT_cmd(Action a)
{
    ES = a;
}

#endif

