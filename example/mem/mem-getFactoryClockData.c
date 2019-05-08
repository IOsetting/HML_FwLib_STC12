/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @Compiler:SDCC v3.6.0
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:a demo which shows how to get frequency of the factory RC clock from internal RAM
 * @Test-board:ZS5110
 * @Test-mcu:STC11F16XE
 * @Version:V0
 */

/* ----- @header file ----- */
#include "conf.h"

/* ----- @macro ----- */
#define ADDR_RAM_FACTORY_RC_CLK 0xFC   /* mark address */

/*
 * @Prototype:app_getFactoryClockData(byte *dat)
 * @Parameter:(1)*dat:the pointer of the area for storing data
 * @Ret-val:None
 * @Note:get factory clock data from internal RAM(address is 0xFC~0xFF)
 */
void app_getFactoryClockData(byte *dat)
{
    u8 i = 0;

    /* the data is stored in a specified area, address range of the ara is from 0xFC to 0xFF in internal RAM of STC10 MCU */
    for(i = 0;i < 4;i++)
    {
        dat[i] = __PBYTE[ADDR_RAM_FACTORY_RC_CLK + i];
    }
}

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
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;     /* select BRT as baud rate generator */
    uc.baudGeneratorPrescalerState = ENABLE;
    uc.interruptState              = ENABLE;
    uc.interruptPriority           = DISABLE;
    uc.mode                        = UART_mode_1;
    uc.multiBaudrate               = DISABLE;
    uc.pinmap                      = UART_pinmap_0;
    uc.receiveState                = ENABLE;

    UART_config(&uc);
}

/*
 * @Prototype:void util_byteToHexString(byte src,char *res)
 * @Parameter:(1)src:the byte of date which is going to transfer; (2)res:a array for storing result
 * @Ret-val:None
 * @Note:transfer byte to hex string
 */
void util_byteToHexString(byte src,char *res)
{
    u8 i = 2;
    byte tmp = 0;

    res = res + 2;
    *res = '\0';

    while(i--)
    {
        res--;
        tmp = src % 0x10;

        if(tmp < 10)
        {
            *res = '0' + tmp;
        }
        else
        {
            *res = 'A' + (tmp - 0x0A);
        }
        src = src / 0x10;
    }

}

/* ----- @main ----- */
void main(void)
{
    byte accessResult[4];    /* store results */
    char buffer[2];
    u8 i = 0;

    sys_init();

    while(true)
    {  
        app_getFactoryClockData(accessResult);   /* get data */
        UART_sendString("Access result:");
        
        /* show data */
        for(i= 0;i < 4;i++)
        {
            UART_sendString(" 0x");
            util_byteToHexString(accessResult[i],buffer);
            UART_sendString(buffer);
        }
        UART_sendString("\r\n");

        sleep(1000);    /* gap time */
    }
}
