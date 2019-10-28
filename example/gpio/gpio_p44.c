/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a demo which shows use pin P44 as GPIO
 * @Test-board:ZS5110
 * @Test-mcu:STC11F16XE
 * @Version:V0
 */

#include "conf.h"

/* ----- @main ----- */
void main(void)
{    
    GPIO_P44_cmd(ENABLE);
    GPIO_resetBitValue(PERIPH_GPIO_4,PERIPH_GPIO_PIN_4);
    
    /* blink */
    while(true)
    {
        sleep(500);
        GPIO_toggleBitValue(PERIPH_GPIO_4,PERIPH_GPIO_PIN_4);   /* P44 is connected to a LED for testing */
    }    
}
