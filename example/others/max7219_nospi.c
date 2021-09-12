/*****************************************************************************/
/** 
 * \file        max7219.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of MAX7219 without hardware SPI
 * \note        Pin wiring:
 *              CLK => P2_2, CS => P2_1, DIN => P2_0
 * 
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"
#include <stdio.h>

#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

#define BLOCKS 1

#define MAX7219_CLK P2_2
#define MAX7219_CS  P2_1
#define MAX7219_DIN P2_0

uint8_t __xdata bytes[] = {
  0x3e,0x63,0x63,0x7f,0x63,0x63,0x63,0x63, //A
  0x7e,0x63,0x63,0x7e,0x63,0x63,0x63,0x7e, //B
  0x3e,0x63,0x63,0x60,0x60,0x63,0x63,0x3e, //C
  0x3e,0x63,0x73,0x6b,0x67,0x63,0x63,0x3e, //0
  0x0c,0x1c,0x3c,0x0c,0x0c,0x0c,0x0c,0x3f, //1
  0x3e,0x63,0x63,0x06,0x0c,0x18,0x30,0x7f, //2
  0x3e,0x63,0x63,0x0e,0x03,0x63,0x63,0x3e, //3
  0x06,0x0e,0x1e,0x36,0x66,0x7f,0x06,0x06, //4
  0x7f,0x60,0x60,0x7e,0x03,0x03,0x03,0x7e, //5
  0x3e,0x63,0x60,0x7e,0x63,0x63,0x63,0x3e, //6
  0x7f,0x03,0x03,0x06,0x0c,0x18,0x18,0x18, //7
  0x3e,0x63,0x63,0x3e,0x63,0x63,0x63,0x3e, //8
  0x3e,0x63,0x63,0x63,0x3f,0x03,0x63,0x3e, //9
};

uint8_t val[BLOCKS];
uint8_t character_len = sizeof(bytes) / 8;

void Max7219_writeByte(uint8_t dat)
{
  uint8_t i;
  MAX7219_CS = 0;
  for(i = 8; i >= 1; i--)
  {
    MAX7219_CLK = 0;
    MAX7219_DIN = dat & 0x80; // &10000000, highest bit
    dat = dat << 1;
    MAX7219_CLK = 1;
  }
}

void Max7219_singeWrite(uint8_t index, uint8_t addr, uint8_t dat)
{ 
  MAX7219_CS = 0;
  Max7219_writeByte(addr);
  Max7219_writeByte(dat);
  while(index--)
  {
    Max7219_writeByte(0x00);
    Max7219_writeByte(0x00);
  }
  MAX7219_CS = 1;
}

void Max7219_multiWrite(uint8_t addr, uint8_t len, uint8_t* dat)
{ 
  MAX7219_CS = 0;
  while(len--)
  {
    Max7219_writeByte(addr);
    Max7219_writeByte(*dat++);
  }
  MAX7219_CS = 1;
}

void Max7219_init(void)
{
  uint8_t i;
  for (i = 0; i < BLOCKS; i++)
  {
    Max7219_singeWrite(i, SHUT_DOWN,   0x01);  // 0x00:shutdown, 0x01:normal
    Max7219_singeWrite(i, DECODE_MODE, 0x00);  // No decode
    Max7219_singeWrite(i, SCAN_LIMIT,  0x07);  // Display 8 digits
    Max7219_singeWrite(i, INTENSITY,   0x03);  // 0x00:min, 0x0F:max
    Max7219_singeWrite(i, DISPLAY_TEST, 0x00); // 0x00:normal, 0x01:test mode
  }
}

void main(void)
{
    uint16_t pos = 0, lpos = 0;
    uint8_t i, j, cpos = 0, bpos = 0, tcpos = 0;
    Max7219_init();
    while (1)
    {
        lpos = pos + sizeof(bytes) - BLOCKS * 8;
        cpos = lpos / 8;        // char pos
        bpos = lpos % 8;        // bit pos
        for (i = 0; i < 8; i++) // for each line, for each val
        {
            // fill the byte of each matrix
            for (j = 0; j < BLOCKS; j++)
            {
                // high bits
                tcpos = (cpos + j) % character_len;
                val[j] = bytes[tcpos * 8 + i] << bpos;
                // low bits
                tcpos = (cpos + j + 1) % character_len;
                val[j] |= bytes[tcpos * 8 + i] >> (8 - bpos);
            }
            Max7219_multiWrite(i + 1, BLOCKS, val);
        }
        // move pos to the right
        pos = (pos + 1) % sizeof(bytes);
        sleep(200);
    }
}