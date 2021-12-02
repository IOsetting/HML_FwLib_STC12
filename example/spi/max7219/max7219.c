/*****************************************************************************/
/** 
 * \file        spi_max7219.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of SPI driving dot matrix module
 * \note        The module chip is MAX7219, pin connection:
 *              P1_3        => CS, 
 *              P1_5(MOSI)  => DIN, 
 *              P1_7(SPCLK) => CLK
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5A56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

#define MAX7219_CS P1_3

#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

const uint8_t numbers[]={
0x00,0x00,0x7C,0xC6,0xC6,0xCE,0xD6,0xD6,  // -0-.  
0xE6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x38,0x78,0x18,0x18,0x18,  // -1-  
0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0x06,0x0C,0x18,0x30,  // -2-  
0x60,0xC0,0xC6,0xFE,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0x06,0x06,0x3C,0x06,  // -3-  
0x06,0x06,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0x0C,0x1C,0x3C,0x6C,0xCC,0xFE,  // -4-  
0x0C,0x0C,0x0C,0x1E,0x00,0x00,0x00,0x00,  
0x00,0x00,0xFE,0xC0,0xC0,0xC0,0xFC,0x0E,  // -5-  
0x06,0x06,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0x38,0x60,0xC0,0xC0,0xFC,0xC6,  // -6-  
0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00,  
0x00,0x00,0xFE,0xC6,0x06,0x06,0x0C,0x18,  // -7-  
0x30,0x30,0x30,0x30,0x00,0x00,0x00,0x00,  
0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0xC6,  // -8-  
0xC6,0xC6,0xC6,0x7C,0x00,0x00,0x00,0x00, 
0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7E,0x06,  // -9-  
0x06,0x06,0x0C,0x78,0x00,0x00,0x00,0x00};

void MAX7219_write(uint8_t addr, uint8_t dat)
{
    MAX7219_CS = 0;
    SPI_RW(addr);
    SPI_RW(dat);
    MAX7219_CS = 1;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize MAX7219
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void MAX7219_init(void)
{
    MAX7219_write(SHUT_DOWN,0x01);         // 0x00:shutdown, 0x01:normal
    MAX7219_write(DECODE_MODE,0x00);       // No decode
    MAX7219_write(SCAN_LIMIT,0x07);        // Display 8 digits
    MAX7219_write(INTENSITY,0x00);         // 0x00:min, 0xFF:max
    MAX7219_write(DISPLAY_TEST,0x00);      // 0x00:normal, 0x01:test mode
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
    SPI_init();
    MAX7219_init();

    P1_3 = 1;
    uint8_t pos = 0, size = sizeof(numbers), i, j;
    while(1)
    {
        for (i = 0; i < 8; i++)
        {
            j = (pos + i) % size;
            MAX7219_write(i + 1, numbers[j]);
        }
        pos = (pos + 1) % size;
        sleep(100);
    }
}