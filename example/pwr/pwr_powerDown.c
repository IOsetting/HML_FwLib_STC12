/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows power-down mode and recover from it.
 * @Test-board:ZS5110
 * @Test-mcu:STC11F16XE
 * @Version:V0
 */

#include "conf.h"

/*
 * @Extra-note:
 *  (1)P32/P33 are connected to key
 *  (2)user had better use IRC as clock source when run this segment of code
 */

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

    /* indicate start to work via LED */
    GPIO_configPortValue(PERIPH_GPIO_1,0xFF);
    sleep(200);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_0);
    sleep(200);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_1);    
    sleep(200);
    GPIO_toggleBitValue(PERIPH_GPIO_1,PERIPH_GPIO_PIN_2);
    sleep(200);
    GPIO_configPortValue(PERIPH_GPIO_1,0xFF);
    sleep(200);
    
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
                PWR_powerDown();  /* enter into power-down mode */
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
    /* do nothing, recover when one extern interrupt is triggered */
}
