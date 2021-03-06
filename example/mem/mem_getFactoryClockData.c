/*****************************************************************************/
/** 
 * \file        mem_getFactoryClockData.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \date        
 * \brief       example for get frequency
 * \note        a example which shows how to get frequency of the factory RC 
 *              clock from internal RAM
 * \version     v0.0
 * \ingroup     example
 * \remarks     test-board: ZS5110; test-MCU: STC11F16XE
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
#define ADDR_RAM_FACTORY_RC_CLK 0xFC   /* mark address */

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get factory clock data from internal RAM(address is 0xFC~0xFF)
 * \param[in]   *dat: the pointer of the area for storing data
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void app_getFactoryClockData(uint8_t *dat)
{
    uint8_t i = 0;

    /* the data is stored in a specified area, address range of the ara is from 0xFC to 0xFF in internal RAM of STC10 MCU */
    for (i = 0; i < 4; i++)
    {
        dat[i] = __PBYTE[ADDR_RAM_FACTORY_RC_CLK + i];
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       initial MCU
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void sys_init(void)
{
    UART_configTypeDef uc;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;
    UART_config(&uc);
    RCC_BRT_config(9600, RCC_BRT_prescaler_12, uc.doubleBaudrate);
    UART_INT_cmd(ENABLE);
    UART_INT_setPriority(IntPriority_Low);
    UART_setReceive(ENABLE);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       transfer byte to hex string
 * \param[in]   src: the byte of date which is going to transfer
 * \param[in]   res: a array for storing result
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void util_byteToHexString(uint8_t src, char *res)
{
    uint8_t i = 2;
    uint8_t tmp = 0;

    res = res + 2;
    *res = '\0';

    while (i--)
    {
        res--;
        tmp = src % 0x10;

        if (tmp < 10)
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

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{
    uint8_t accessResult[4];    /* store results */
    char buffer[2];
    uint8_t i = 0;

    sys_init();

    while (true)
    {  
        app_getFactoryClockData(accessResult);   /* get data */
        UART_sendString("Access result:");
        
        /* show data */
        for (i= 0; i < 4; i++)
        {
            UART_sendString(" 0x");
            util_byteToHexString(accessResult[i], buffer);
            UART_sendString(buffer);
        }
        UART_sendString("\r\n");
        sleep(1000);    /* gap time */
    }
}
