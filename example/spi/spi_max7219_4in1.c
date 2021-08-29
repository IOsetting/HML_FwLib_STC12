/*****************************************************************************/
/** 
 * \file        spi_max7219_4in1.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of SPI driving 4-in-1 8x8 dot matrix module
 * \note        The module chip is MAX7219, pin connection:
 *              P1_3        => CS, 
 *              P1_5(MOSI)  => DIN, 
 *              P1_7(SPCLK) => CLK
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5AF56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

#define MAX7219_CS   P1_3
#define BLOCKS       4

#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

const uint8_t numbers[]={
  0x3e,0x63,0x63,0x7f,0x63,0x63,0x63,0x63, //A
  0x7e,0x63,0x63,0x7e,0x63,0x63,0x63,0x7e, //B
  0x3e,0x63,0x63,0x60,0x60,0x63,0x63,0x3e, //C
  0x7e,0x63,0x63,0x63,0x63,0x63,0x63,0x7e, //D
  0x7f,0x60,0x60,0x7f,0x60,0x60,0x60,0x7f, //E
  0x7f,0x60,0x60,0x7e,0x60,0x60,0x60,0x60, //F
  0x3e,0x63,0x63,0x60,0x67,0x63,0x63,0x3e, //G
  0x63,0x63,0x63,0x7f,0x63,0x63,0x63,0x63, //H
  0x3f,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3f, //I
  0x1f,0x06,0x06,0x06,0x06,0x66,0x66,0x3c, //J
  0x63,0x66,0x6c,0x78,0x6c,0x66,0x63,0x61, //K
  0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7f, //L
  0x63,0x77,0x7f,0x6b,0x63,0x63,0x63,0x63, //M
  0x63,0x63,0x73,0x7b,0x6f,0x67,0x63,0x63, //N
  0x3e,0x63,0x63,0x63,0x63,0x63,0x63,0x3e, //O
  0x7e,0x63,0x63,0x63,0x7e,0x60,0x60,0x60, //P
  0x3c,0x66,0x66,0x66,0x66,0x6e,0x66,0x3f, //Q
  0x7e,0x63,0x63,0x63,0x7e,0x6c,0x66,0x63, //R
  0x3e,0x63,0x63,0x60,0x3e,0x03,0x63,0x3e, //S
  0x3f,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c, //T
  0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3e, //U
  0x63,0x63,0x63,0x63,0x63,0x36,0x1c,0x08, //V
  0x63,0x63,0x63,0x63,0x6b,0x7f,0x77,0x63, //W
  0x63,0x63,0x36,0x1c,0x1c,0x36,0x63,0x63, //X
  0x33,0x33,0x33,0x33,0x1e,0x0c,0x0c,0x0c, //Y
  0x7f,0x03,0x06,0x0c,0x18,0x30,0x60,0x7f, //Z
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
uint8_t character_len = sizeof(numbers) / 8;

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       Write to No.index MAX7219 only
 * \param[in]   index: the index of MAX7219 block
 * \param[in]   addr: register address
 * \param[in]   dat: value to be written
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void MAX7219_singeWrite(uint8_t index, uint8_t addr, uint8_t dat)
{
    index = index % BLOCKS;
    MAX7219_CS = 0;
    SPI_RW(addr);
    SPI_RW(dat);
    while(index--)
    {
        SPI_RW(0x00);
        SPI_RW(0x00);
    }
    MAX7219_CS = 1;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       Write to [len] MAX7219 blocks in one invoke
 * \param[in]   addr: register address
 * \param[in]   len: dat length
 * \param[in]   dat: value to be written
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void MAX7219_multiWrite(uint8_t addr, uint8_t len, uint8_t* dat)
{
    MAX7219_CS = 0;
    while (len--)
    {
        SPI_RW(addr);
        SPI_RW(*dat++);
    }
    MAX7219_CS = 1;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize MAX7219
 * \param[in]   none
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void MAX7219_init(void)
{
    for (uint8_t i = 0; i < BLOCKS; i++)
    {
        MAX7219_singeWrite(i, SHUT_DOWN, 0x01);    // 0x00:shutdown, 0x01:normal
        MAX7219_singeWrite(i, DECODE_MODE, 0x00);  // No decode
        MAX7219_singeWrite(i, SCAN_LIMIT, 0x07);   // Display 8 digits
        MAX7219_singeWrite(i, INTENSITY, 0x00);    // 0x00:min, 0xFF:max
        MAX7219_singeWrite(i, DISPLAY_TEST, 0x00); // 0x00:normal, 0x01:test mode
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize SPI
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void SPI_init(void)
{
    SPI_configTypeDef sc;
    sc.baudRatePrescaler = SPI_BaudRatePrescaler_64;
    sc.cpha = SPI_CPHA_1Edge;
    sc.cpol = SPI_CPOL_low;
    sc.firstBit = SPI_FirstBit_MSB;
    sc.pinmap = SPI_pinmap_P1;
    sc.nss = SPI_NSS_Soft;
    sc.mode = SPI_Mode_Master;
    SPI_config(&sc);
    SPI_cmd(ENABLE);
}

void main()
{
    uint16_t pos = 0, lpos = 0;
    uint8_t i, j, cpos = 0, bpos = 0, tcpos = 0;
    SPI_init();
    MAX7219_init();

    while (1)
    {
        lpos = pos + sizeof(numbers) - BLOCKS * 8;
        cpos = lpos / 8;        // char position
        bpos = lpos % 8;        // bit position
        for (i = 0; i < 8; i++) // fill this line
        {
            for (j = 0; j < BLOCKS; j++)
            {
               tcpos = (cpos + j) % character_len;
                val[j] = numbers[tcpos * 8 + i] << bpos;
                tcpos = (cpos + j + 1) % character_len;
                val[j] |= numbers[tcpos * 8 + i] >> (8 - bpos);
            }
            MAX7219_multiWrite(i + 1, BLOCKS, val);
        }
        pos = (pos + 1) % sizeof(numbers);
        sleep(100);
    }
}