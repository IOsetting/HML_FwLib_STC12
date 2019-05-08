/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operations about power management
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#include "pwr.h"

#ifdef ___COMPILE_PWR___

/*
 * @Prototype:void PWR_idle(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:enter idle mode
 */
void PWR_idle(void)
{
    SET_BIT_MASK(PCON,IDL);
}

/*
 * @Prototype:void PWR_powerDown(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:make MCU enter power down mode
 */
void PWR_powerDown(void)
{
    SET_BIT_MASK(PCON,PD);
}

/*
 * @Prototype:void PWR_LVD_clearFlag(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:clear LVDF bit in PCON register
 */
void PWR_LVD_clearFlag(void)
{
    CLR_BIT_MASK(PCON,LVDF);
}

/*
 * @Prototype:void PWR_LVD_cmd(Action a)
 * @Parameter:(1)a:expected status
 * @Ret-val:None
 * @Note:enable or disable LVD(low voltage level detect) module
 */
void PWR_LVD_cmd(Action a)
{
     CONFB(P4SW,BIT_NUM_NA_P46,~a);
}

/*
 * @Prototype:FunctionalState PWR_LVD_getFlag(void)
 * @Parameter:None
 * @Ret-val:current value of LVDF bit
 * @Note:get value of LVDF bit in PCON register
 */
FunctionalState PWR_LVD_getFlag(void)
{
    return ((FunctionalState)GET_BIT(PCON,LVDF));
}

/*
 * @Prototype:void PWR_LVD_INT_cmd(Action a)
 * @Parameter:(1)a:expected status
 * @Ret-val:
 * @Note:enable or disable interrupt status of LVD(low voltage level detect) module
 */
void PWR_LVD_INT_cmd(Action a)
{
    ELVD = (FunctionalState)a;
}

/*
 * @Prototype:void PWR_PD_IE_cmd(PWR_PD_IEPIN pin,Action a)
 * @Parameter:(1)pin:target pin;(2)a:expected status
 * @Ret-val:
 * @Note:disable or enable one pin for waking up MCU from power down state
 */
void PWR_PD_IE_cmd(PWR_PD_IEPIN pin,Action a)
{
    switch(pin)
    {
        case PWR_PD_IEPIN_RXD:CONFB(WAKE_CLKO,BIT_NUM_RD_PIN_IE,a);break;
        case PWR_PD_IEPIN_T0 :CONFB(WAKE_CLKO,BIT_NUM_T0_PIN_IE,a);break;
        case PWR_PD_IEPIN_T1 :CONFB(WAKE_CLKO,BIT_NUM_T1_PIN_IE,a);break;
        default:break;
    }
}

/*
 * @Prototype:void PWR_WKT_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:disable or enable wake timer under power down mode
 */
void PWR_WKT_cmd(Action a)
{
    CONFB(WKTCH,BIT_NUM_WKTEN,a);
}

/*
 * @Prototype:bool PWR_WKT_setWakeCount(uint16_t c)
 * @Parameter:(1)c:count cycle, the wake counter costume about 560us per cycle
 * @Ret-val:(1)true:valid input argument; (2)false: invalid argument
 * @Note:
 */
bool PWR_WKT_setWakeCount(uint16_t c)
{
    if(c > 4096)
    {
        WKTCL = (byte)(c & 0x00FF);
        WKTCH = (byte)((c & 0x0F00) >> 0x8);

        return true;
    }
    else
    {
        return false;
    }
}

#endif
