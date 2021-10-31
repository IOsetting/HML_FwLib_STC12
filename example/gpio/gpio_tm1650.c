/*****************************************************************************/
/** 
 * \file        gpio_tm1650.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of TM1650 LED Display/Keypad Driver
 * \note        Pin connection:
 * 
 *              > TM1650 > 2841AS/AH, 3641AS/AH, 4041AS/AH, 5643AS/AH,
 *              1:DIG1     => 12
 *              5:DIG2     => 9
 *              6:DIG3     => 8
 *              7:DIG4     => 6
 *              8:A/KI1    => 11
 *              9:B/KI2    => 7
 *              11:C/KI3   => 4
 *              12:D/KI4   => 2
 *              13:E/KI5   => 1
 *              14:F/KI6   => 10
 *              15:G/KI7   => 5
 *              16:DP/KP   => 3
 * 
 *              > TM1650 > STC12 MCU
 *              2:SCL    => P3_7
 *              3:SDA    => P3_6
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5A56S2, OSC:11.0592MHz
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

#define TM1650_SCL  P3_7
#define TM1650_SDA  P3_6

#define TM1650_MODE     0x48
#define TM1650_READ_KEY 0x49
#define DIG1 0x68
#define DIG2 0x6A
#define DIG3 0x6C
#define DIG4 0x6E

const uint8_t DIGITS[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint8_t pos = 0;

void TM1650_start(void)
{
    TM1650_SCL = 1;
    TM1650_SDA = 1;
    TM1650_SDA = 0;
}

void TM1650_stop(void)
{
    TM1650_SCL = 1;
    TM1650_SDA = 0;
    TM1650_SDA = 1;
}

void TM1650_ack(void)
{
    uint8_t timeout = 1;
    TM1650_SCL = 1;
    TM1650_SCL = 0;
    while ((TM1650_SDA) && (timeout <= 100))
    {
        timeout++;
    }
    TM1650_SCL = 0;
}

void TM1650_write(uint8_t dat)
{
    uint8_t i;
    TM1650_SCL = 0;
    for (i = 0; i < 8; i++)
    {
        dat = dat << 1;
        // CY:Carry Flag, is set if data is coming out of bit 7 of Acc during an Arithmetic operation.
        TM1650_SDA = CY;
        TM1650_SCL = 0;
        TM1650_SCL = 1;
        TM1650_SCL = 0;
    }
}

uint8_t TM1650_scanKey(void)
{
    uint8_t i;
    uint8_t rekey;
    TM1650_start();
    TM1650_write(TM1650_READ_KEY);
    TM1650_ack();
    for (i = 0; i < 8; i++)
    {
        TM1650_SCL = 1;
        rekey = rekey << 1;
        if (TM1650_SDA)
        {
            rekey++;
        }
        TM1650_SCL = 0;
    }
    TM1650_ack();
    TM1650_stop();
    return (rekey);
}


void TM1650_send(uint8_t addr, uint8_t dat)
{
    TM1650_start();
    TM1650_write(addr);
    TM1650_ack();
    TM1650_write(dat);
    TM1650_ack();
    TM1650_stop();
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize TM1650
 * \param[in]   brightness level, increasing from 0x01 to 0x07 (0x00 is the brightest)
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void TM1650_init(uint8_t brightness)
{
    TM1650_send(TM1650_MODE, ((brightness << 4) + 0x01));
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
    TM1650_init(1);
    while (1){
        TM1650_send(DIG1, DIGITS[(pos + 0)%10]);
        TM1650_send(DIG2, DIGITS[(pos + 1)%10]);
        TM1650_send(DIG3, DIGITS[(pos + 2)%10]);
        TM1650_send(DIG4, DIGITS[(pos + 3)%10]);
        pos = (pos + 1)%10;
        sleep(1000);
    }
}
