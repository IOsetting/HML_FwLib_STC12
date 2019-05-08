/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:reset and clock control
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */
 
#include "rcc.h"

#ifdef ___COMPILE_RCC___

u8 df = 0x1;       /* mark current divided factor */

/*
 * @Prototype:void RCC_BRT_cmd(Action a)
 * @Parameter:(1)a:expected action:enable or disable
 * @Ret-val:None
 * @Note:control switch status of BRT module
 */
void RCC_BRT_cmd(Action a)
{
    CONFB(AUXR,BIT_NUM_BRTR,a);
}

/*
 * @Prototype:void RCC_BRT_setClockOutput(Action a)
 * @Parameter:(1)a:expected action:enable or disable
 * @Ret-val:None
 * @Note:
 *  (1)control status of clock output via P10 from BRT module
 *  (2)the frequency value of output clock is _SYS_CLK_/(256-BRT)/2 (under 1T mode) or _SYS_CLK_/12/(256-BRT)/2 (under 12T mode)
 */
void RCC_BRT_setClockOutput(Action a)
{
    CONFB(WAKE_CLKO,BIT_NUM_BRTCLKO,a);
}

/*
 * @Prototype:void RCC_BRT_setPrescaler(RCC_BRT_prescaler pre)
 * @Parameter:(1)pre:expected prescaler mode
 * @Ret-val:None
 * @Note:set prescaler mode of BRT module
 */
void RCC_BRT_setPrescaler(RCC_BRT_prescaler pre)
{
    CONFB(AUXR,BIT_NUM_BRTx12,pre);
}

/*
 * @Prototype:void RCC_BRT_setValue(unsigned char val)
 * @Parameter:(1)val:target value
 * @Ret-val:None
 * @Note:set value of BRT reload register
 */
void RCC_BRT_setValue(unsigned char val)
{
    BRT = val;
}

/*
 * @Prototype:void RCC_setClockDivisionFactor(RCC_prescaler d)
 * @Parameter:(1)d:division factor
 * @Ret-val:
 * @Note:set division factor of system clock
 */
void RCC_setClockDivisionFactor(RCC_prescaler d)
{
    CLK_DIV = (byte)d;
    df = pow(2,d);
}

/*
 * @Prototype:void RCC_softwareReset(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:reset MCU
 */
void RCC_softwareReset(void)
{
    SET_BIT_MASK(IAP_CONTR,SWRST);
}

/*
 * @Prototype:uint32_t RCC_getSystemClockFrequency(void)
 * @Parameter:None
 * @Ret-val:current system clock frequency
 * @Note:get current system clock frequency
 */
uint32_t RCC_getSystemClockFrequency(void)
{
    return (_FRE_OSC_/df);
}

#endif
