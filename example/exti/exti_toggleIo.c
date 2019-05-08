/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows how to toggle IO by EXTI module
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
    EXTI_config(PERIPH_EXTI_1,&ec);
    EXTI_cmd(PERIPH_EXTI_1,ENABLE);
    enableAllInterrupts();

    GPIO_setBitValue(PERIPH_GPIO_2,PERIPH_GPIO_PIN_0);
}

/* ----- @main ----- */
void main(void)
{
    sys_init();
    while(true);
}

/*
 * @Prototype:void exti1_isr(void)
 * @Parameter:None
 * @Ret-val:None
 * @Note:interrupt function for EXTI1, pin INT1 is connected to a button on board
 */
void exti1_isr(void) __interrupt IE1_VECTOR
{
    GPIO_toggleBitValue(PERIPH_GPIO_2,PERIPH_GPIO_PIN_0);
}
