/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows how to use HML_FwLib_STC10 to toggle P10 state per one second by TIM0 module
 * @Test-board:ZS5110
 * @Test-mcu:STC11F16XE
 * @Version:V0
 */

#include "conf.h"

/*
 * @Prototype:void sys_init(void)
 * @Parameter:
 * @Ret-val:
 * @Note:init MCU
 */
void sys_init(void)
{
    TIM_configTypeDef tc;

    tc.function          = TIM_function_tim;
    tc.interruptState    = ENABLE;
    tc.interruptPriority = DISABLE;
    tc.mode              = TIM_mode_1;
    tc.prescaler         = TIM_prescaler_12;
    tc.value             = 65536-50000;

    TIM_config(PERIPH_TIM_0,&tc);
    enableAllInterrupts();
    TIM_cmd(PERIPH_TIM_0,ENABLE);
}

/* ----- @main ----- */
void main(void)
{
    sys_init();
    while(true);
}

/*
 * @Prototype:void tim0_isr(void)
 * @Parameter:
 * @Ret-val:
 * @Note:interrupt handle function for TIM0
 */
void tim0_isr(void) __interrupt TF0_VECTOR
{
    static u8 i = 0;

    TIM_setValue(PERIPH_TIM_0,65536-50000); /* reload initial value */
    i++;

    /* 20*50ms = 1s */
    if(i >= 20)
    {
        GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0);
        i = 0;     /* clear */
    }
}
