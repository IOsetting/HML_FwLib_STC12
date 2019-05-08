/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a example which shows that how to use HML_FwLib_STC10 to use watchdog module
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
    UART_configTypeDef uc;
    
    uc.baudrate                    = 9600;                           /* baud rate is 9600bps */
    uc.baudrateGenerator           = UART_baudrateGenerator_tim1;    /* select timer-1 as baud rate generator */
    uc.baudGeneratorPrescalerState = ENABLE;
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.multiBaudrate               = DISABLE;
    uc.pinmap                      = UART_pinmap_0;
    uc.receiveState                = ENABLE;

    UART_config(&uc);
    WDT_setPrescale(WDT_prescale_32);
    WDT_cmd(ENABLE);
}

/* ----- @main ----- */
void main(void)
{
    sys_init();
    UART_sendString("Startup MCU...\r\n");   /* startup info */
    
    while(true)
    {
        /*feed watchdog per 500ms*/
        sleep(500);
        WDT_clear();
        UART_sendString("watch dog has been fed\r\n");
    }
}

