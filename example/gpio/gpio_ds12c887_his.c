/*****************************************************************************/
/** 
 * \file        gpio_ds12c887_his.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of read/write DS12C887 Real-Time Clocks chip
 * \note        Pin connection:
 *              > DS12C887 > STC12 MCU
 *              MOT    => GND(or left disconnected)
 *              AD0-7  => P0_0 - P0_7
 *              GND    => GND
 *              VCC    => VCC
 *              SQW
 *              IRQ    => P3_2
 *              RESET  => VCC
 *              DS     => P1_0
 *              RW     => P1_1
 *              AS     => P1_2
 *              CS     => P1_4
 *              
 *              > USB2TTL > STC12 MCU
 *              TX     => P3_0
 *              RX     => P3_1
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5A56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

#define DS12_DS  P1_0
#define DS12_RW  P1_1
#define DS12_AS  P1_2
#define DS12_CS  P1_4
#define DS12_IRQ P3_2

uint8_t reg_a, reg_b, reg_c;
uint8_t centry, year, month, date, week_day, hour, minute, second;
uint8_t alarm_hour, alarm_minute, alarm_second;

void DS12C887_write(uint8_t addr, uint8_t w_data)
{
    DS12_CS = 0;
    DS12_AS = 1;
    DS12_DS = 1;
    DS12_RW = 1;
    P0 = addr;
    DS12_AS = 0;
    DS12_RW = 0;
    P0 = w_data;
    DS12_RW = 1;
    DS12_AS = 1;
    DS12_CS = 1;
}

uint8_t DS12C887_read(uint8_t addr)
{
    uint8_t ds_date;
    DS12_AS = 1;
    DS12_DS = 1;
    DS12_RW = 1;
    DS12_CS = 0;
    P0 = addr;
    DS12_AS = 0;
    DS12_DS = 0;
    /**
     * Set P0 to high impedance. This is the tricky part, if the mode remains quasi-bidirectional,
     * you need to set P0 = 0xFF in order to get output data, but this will also interfere with the output.
     * This is quite different from STC89.
     */
    GPIO_configPortMode(PERIPH_GPIO_0, GPIO_mode_HIS);
    ds_date = P0;
    DS12_DS = 1;
    DS12_AS = 1;
    DS12_CS = 1;
    /** Restore P0 to default quasi-bidirectional */
    GPIO_configPortMode(PERIPH_GPIO_0, GPIO_mode_QBD);
    return ds_date;
}

void print_time(void)
{
    reg_a  = DS12C887_read(0x0a);
    reg_b  = DS12C887_read(0x0b);
    reg_c  = DS12C887_read(0x0c);

    second = DS12C887_read(0x00);
    minute = DS12C887_read(0x02);
    hour   = DS12C887_read(0x04);
    week_day = DS12C887_read(0x06);
    date   = DS12C887_read(0x07);
    month  = DS12C887_read(0x08);
    year   = DS12C887_read(0x09);
    centry = DS12C887_read(0x32);

    alarm_second = DS12C887_read(0x01);
    alarm_minute = DS12C887_read(0x03);
    alarm_hour   = DS12C887_read(0x05);

    UART_sendHex(reg_a);
    UART_sendByte('-');
    UART_sendHex(reg_b);
    UART_sendByte('-');
    UART_sendHex(reg_c);
    UART_sendByte(' ');
    UART_sendHex(centry);
    UART_sendByte('-');
    UART_sendHex(year);
    UART_sendByte('-');
    UART_sendHex(month);
    UART_sendByte('-');
    UART_sendHex(date);
    UART_sendByte(' ');
    UART_sendHex(hour);
    UART_sendByte(':');
    UART_sendHex(minute);
    UART_sendByte(':');
    UART_sendHex(second);
    UART_sendByte('\n');
}

void DS12C887_init()
{ 
    // 0B: SET PIE AIE UIE SQWE DM 24/12 DSE
    DS12C887_write(0x0b, 0x32);
    // 0A: UIP DV2 DV1 DV0 RS3 RS2 RS1 RS0
    //DS12C887_write(0x0a, 0x20);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize UART on P3.0/P3.1
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void initSys(void)
{
    UART_configTypeDef uc;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;
    UART_config(&uc);
    RCC_BRT_config(115200, RCC_BRT_prescaler_1, uc.doubleBaudrate);
    UART_INT_cmd(DISABLE);
    UART_INT_setPriority(IntPriority_Low);
    UART_setReceive(ENABLE);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{
    initSys();
    DS12C887_init();

    EA = 1;
    IT0 = 1;
    EX0 = 1;

    while (true);
}

void Timer0IRQ(void) __interrupt (0)
{
    print_time();
}