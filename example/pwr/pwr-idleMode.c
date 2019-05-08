/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows how to enter into idle mode and recover from it.
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
    EXTI_configTypeDef ec;
    
    ec.mode     = EXTI_mode_fallEdge;
    ec.priority = DISABLE;
    EXTI_config(PERIPH_EXTI_0,&ec);
    EXTI_cmd(PERIPH_EXTI_0,ENABLE);

    GPIO_configPortValue(PERIPH_GPIO_1,0xFF);
    enableAllInterrupts();
}

/* ----- @main ----- */
void main(void)
{
    sys_init();
    while(true)
    {
        sleep(200);
        GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0);
        
        /* check state of KEY(connected to P33) */
        if(GPIO_getBitValue(PERIPH_GPIO_3,PERIPH_GPIO_PIN_3) == RESET)
        {
            /* avoid shake */
            sleep(5);
            if(GPIO_getBitValue(PERIPH_GPIO_3,PERIPH_GPIO_PIN_3) == RESET)
            {
                PWR_idle();  /* enter into idle mode */
            }
        }
    }
}

/*
 * @Prototype:void exti0_isr(void) __interrupt IE0_VECTOR
 * @Parameter:
 * @Ret-val:
 * @Note:interrupt handle function for EXTI0
 */
void exti0_isr(void) __interrupt IE0_VECTOR
{    
    /* do nothing, recover when extern interrupt is triggered */
}
