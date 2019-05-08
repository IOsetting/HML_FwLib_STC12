/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows that how to send string via UART1 (baud rate generator is timer-1)
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
    UART_configTypeDef uc;
    
    uc.baudrate                    = 115200;                         /* baud rate is 115200bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_tim1;    /* select timer-1 as baud rate generator */
    uc.baudGeneratorPrescalerState = DISABLE;                        /* 1T mode */
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.multiBaudrate               = DISABLE;
    uc.pinmap                      = UART_pinmap_0;
    uc.receiveState                = ENABLE;

    UART_config(&uc);
}

/* ----- @main ----- */
void main(void)
{    
    sys_init();

    while(true)
    {
        /* send per 500ms */
        sleep(500);
        UART_sendString("Hello,world!\r\n");
    }
}

