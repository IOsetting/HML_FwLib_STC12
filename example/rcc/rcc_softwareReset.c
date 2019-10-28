/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows software reset via state of IO(connected to LED)
 * @Test-board:ZS5110
 * @Test-mcu:STC11F16XE
 * @Version:V0
 */

#include "conf.h"

/*
 * @Prototype:void sys_init(void)
 * @Parameter:None
 * @Ret-val:None
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
        sleep(500);
        GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0);
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
    disableAllInterrupts();
    
    /* indicate the MCU is going to reset */
    GPIO_setBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0 | PERIPH_GPIO_PIN_1 | PERIPH_GPIO_PIN_2);
    sleep(500);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0);
    sleep(250);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_1);
    sleep(250);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_2);
    sleep(250);
    
    RCC_softwareReset();
}
