/*****************************************************************************/
/** 
 * \file        ds1302.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of DS1302 timer chip
 * \note        Pin wiring:
 *               |           |               |
 *               | --------- | ------------  |
 *               |1:Vcc2 VCC | 8:Vcc1        |
 *               |2:X1   OCS | 7:SCLK   P1_0 |
 *               |3:X2   OCS | 6:I/O    P1_1 |
 *               |4:GND  GND | 5:RST/CE P1_2 |
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5AF56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"
#include <stdio.h>

#define DS1302_W_SECOND     0x80
#define DS1302_W_MINUTE     0x82
#define DS1302_W_HOUR       0x84
#define DS1302_W_DAY        0x86
#define DS1302_W_MONTH      0x88
#define DS1302_W_WEEK       0x8A
#define DS1302_W_YEAR       0x8C
#define DS1302_W_PROTECT    0x8E
#define DS1302_W_TK_CHARGER 0x90
#define DS1302_W_CLK_BURST  0xBE
#define DS1302_W_RAM_BURST  0xFE

#define DS1302_R_SECOND     0x81
#define DS1302_R_MINUTE     0x83
#define DS1302_R_HOUR       0x85
#define DS1302_R_DAY        0x87
#define DS1302_R_MONTH      0x89
#define DS1302_R_WEEK       0x8B
#define DS1302_R_YEAR       0x8D
#define DS1302_R_PROTECT    0x8F
#define DS1302_R_TK_CHARGER 0x91
#define DS1302_R_CLK_BURST  0xBF
#define DS1302_R_RAM_BURST  0xFF

#define DS1302_RAM_SIZE     0x31 // Ram Size in bytes
#define DS1302_RAM_START    0xC0 // First byte Address

#define HEX2BCD(v)	((v) % 10 + (v) / 10 * 16)
#define BCD2HEX(v)	((v) % 16 + (v) / 16 * 10)

#define DS1302_SCK P1_0
#define DS1302_IO  P1_1
#define DS1302_RST P1_2

const uint8_t READ_RTC_ADDR[7]  = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
const uint8_t WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
uint8_t BUF[8] = { 0 };

// Write one byte to DS1302
void DS1302_writeByte(uint8_t writeByte)
{
    for(uint8_t i=0; i < 8; i++)
    {
        if(1 == (writeByte & 0x01)){
            DS1302_IO = 1;
        }else{
            DS1302_IO = 0;
        }
        DS1302_SCK = 1;
        DS1302_SCK = 0;
        writeByte >>= 1; // From low to high
    }
}
 
// Read one byte from DS1302
uint8_t DS1302_readByte(void)
{
    uint8_t readByte = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        readByte >>= 1;
		if(DS1302_IO)
        {
			readByte |= 0x80; // Write 1 to the highest bit
		}
        DS1302_SCK = 1;
        DS1302_SCK = 0;
    }
    return readByte;
}

void DS1302_writeReg(uint8_t addr, uint8_t value)
{
    DS1302_RST = 0;
    DS1302_SCK = 0;
    DS1302_RST = 1;
    DS1302_writeByte(addr);
    DS1302_writeByte(value);
    DS1302_SCK = 1;
    DS1302_RST = 0;
}
 
uint8_t DS1302_readReg(uint8_t addr)
{
    uint8_t readByte = 0;
    DS1302_RST = 0;
    DS1302_SCK = 0;
    DS1302_RST = 1;
    DS1302_writeByte(addr);
    readByte = DS1302_readByte();
    DS1302_SCK = 1;
    DS1302_RST = 0;
    return readByte;
}

void DS1302_readBurst(uint8_t cmd, uint8_t len, uint8_t *buf) 
{
    uint8_t readByte = 0;
    DS1302_RST = 0;
    DS1302_SCK = 0;
    DS1302_RST = 1;
    DS1302_writeByte(cmd);
    while(len--)
        *buf++ = DS1302_readByte();
    DS1302_SCK = 1;
    DS1302_RST = 0;
}

void DS1302_init(void)
{
    DS1302_writeReg(DS1302_W_PROTECT, 0x00); // write unprotect
    DS1302_writeReg(DS1302_W_TK_CHARGER, 0x01); // stop charger
    DS1302_writeReg(0XC0, 0x00);
    DS1302_writeReg(0XC2, 0x01);
    DS1302_writeReg(0XC4, 0x02);
    DS1302_writeReg(0XC6, 0x03);
    DS1302_writeReg(DS1302_W_PROTECT, 0x80); // write protect
}

void DS1302_print(uint8_t dat)
{
    printf_tiny("%x%x ", dat >> 4, dat & 0x0F);
}

void DS1302_printBuf(uint8_t len)
{
    for(uint8_t i = 0; i < len; i++)
    {
        printf_tiny("%x%x ", BUF[i] >> 4, BUF[i] & 0x0F);
    }
    printf_tiny("\n");
}

void main(void)
{
    UTIL_enablePrintf();
    DS1302_init();
    while(1)
    {
        uint8_t dat = DS1302_readReg(DS1302_R_SECOND);
        DS1302_print(dat);
        dat = DS1302_readReg(DS1302_R_MINUTE);
        DS1302_print(dat);
        dat = DS1302_readReg(DS1302_R_HOUR);
        DS1302_print(dat);
        printf_tiny("\n");
        DS1302_readBurst(DS1302_R_CLK_BURST, 8, BUF);
        DS1302_printBuf(8);
        DS1302_readBurst(DS1302_R_RAM_BURST, 8, BUF);
        DS1302_printBuf(8);
        sleep(491);
    }
}