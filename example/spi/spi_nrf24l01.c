/*****************************************************************************/
/** 
 * \file        spi_nrf24l01_tx.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of SPI driving NRF24L01 module in TX mode
 * \note        Pin connection:
 *              P1_4(SS, Ignored) => CSN,
 *              P1_5(MOSI)        => MOSI,
 *              P1_6(MISO)        => MISO,
 *              P1_7(SPCLK)       => CLK,
 *              P3_2(INT0)        => IRQ,
 *              P3_7(IO)          => CE,
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5AF56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"
#include "stdio.h"

/**********  NRF24L01 Registers  ***********/
#define READ_REG        0x00
#define WRITE_REG       0x20
#define RD_RX_PLOAD     0x61
#define WR_TX_PLOAD     0xA0
#define FLUSH_TX        0xE1
#define FLUSH_RX        0xE2
#define REUSE_TX_PL     0xE3
#define NRF_NOP         0xFF
/**********  NRF24L01 Register Address *****/
#define CONFIG          0x00
#define EN_AA           0x01
#define EN_RXADDR       0x02
#define SETUP_AW        0x03
#define SETUP_RETR      0x04
#define RF_CH           0x05
#define RF_SETUP        0x06
#define STATUS          0x07
#define OBSERVE_TX      0x08
#define CD              0x09
#define RX_ADDR_P0      0x0A
#define RX_ADDR_P1      0x0B
#define RX_ADDR_P2      0x0C
#define RX_ADDR_P3      0x0D
#define RX_ADDR_P4      0x0E
#define RX_ADDR_P5      0x0F
#define TX_ADDR         0x10
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
#define FIFO_STATUS     0x17

/**********  NRF24L01 Constants *********/
#define MAX_TX  	0x10
#define TX_OK   	0x20
#define RX_OK   	0x40

#define TX_ADR_WIDTH    5
#define RX_ADR_WIDTH    5
#define TX_PLOAD_WIDTH  32
#define RX_PLOAD_WIDTH  32

const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x11,0x22,0x33,0x44,0x55};
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x32,0x4E,0x6F,0x64,0x65};
uint8_t rece_buf[RX_PLOAD_WIDTH];

#define NRF_CSN  P1_4
#define NRF_MOSI P1_5
#define NRF_MISO P1_6
#define NRF_SCK  P1_7
#define NRF_IRQ  P3_2
#define NRF_CE   P3_7

void initSys(void)
{
    SPI_configTypeDef sc;
    sc.baudRatePrescaler = SPI_BaudRatePrescaler_4;
    sc.cpha = SPI_CPHA_1Edge;
    sc.cpol = SPI_CPOL_low;
    sc.firstBit = SPI_FirstBit_MSB;
    sc.pinmap = SPI_pinmap_P1;
    sc.nss = SPI_NSS_Soft;
    sc.mode = SPI_Mode_Master;
    SPI_config(&sc);
    SPI_cmd(ENABLE);
}

uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;

	NRF_CSN = 0;
  	status = SPI_RW(reg);
	SPI_RW(value);
	NRF_CSN = 1;
	return status;
}

uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
    uint8_t value;

    NRF_CSN = 0;
    SPI_RW(reg);
    value = SPI_RW(NRF_NOP);
    NRF_CSN = 1;
    return value;
}

uint8_t NRF24L01_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    uint8_t status, u8_ctr;
    NRF_CSN = 0;
    status = SPI_RW(reg);
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        pBuf[u8_ctr] = SPI_RW(NRF_NOP);
    NRF_CSN = 1;
    return status;
}

uint8_t NRF24L01_Write_Buf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    uint8_t status, u8_ctr;
    NRF_CSN = 0;
    status = SPI_RW(reg);
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        SPI_RW(*pBuf++);
    NRF_CSN = 1;
    return status;
}

uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
    uint8_t state;
    state = NRF24L01_Read_Reg(STATUS);
    NRF24L01_Write_Reg(WRITE_REG + STATUS, state);
    if (state & RX_OK)
    {
        NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);
        NRF24L01_Write_Reg(FLUSH_RX, 0xFF);
        return 0;
    }
    return 1;
}

uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
    uint8_t state;
    NRF_CE = 0;
    NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);
    NRF_CE = 1;
    while (NRF_IRQ == 1);
    state = NRF24L01_Read_Reg(STATUS);
    NRF24L01_Write_Reg(WRITE_REG + STATUS, state);
    if (state & MAX_TX)
    {
        NRF24L01_Write_Reg(FLUSH_TX, 0xff);
        return MAX_TX;
    }
    if (state & TX_OK)
    {
        return TX_OK;
    }
    return 0xFF;
}

uint8_t NRF24L01_Check(void)
{
    const uint8_t check_in_buf[5]  = {0x12, 0x23, 0x34, 0x45, 0x56};
    uint8_t check_out_buf[5] = {0x00};
    NRF_CE = 0;
    NRF24L01_Write_Buf(WRITE_REG + TX_ADDR, check_in_buf, 5);
    NRF24L01_Read_Buf(READ_REG + TX_ADDR, check_out_buf, 5);

    if ((check_out_buf[0] == check_in_buf[0]) &&
        (check_out_buf[1] == check_in_buf[1]) &&
        (check_out_buf[2] == check_in_buf[2]) &&
        (check_out_buf[3] == check_in_buf[3]) &&
        (check_out_buf[4] == check_in_buf[4]))
    {
        return 0;
    }
    else
        return 1;
}

void NRF24L01_Init(void)
{
    NRF_CE = 0;
    NRF24L01_Write_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);
    NRF24L01_Write_Buf(WRITE_REG + TX_ADDR, (uint8_t *)TX_ADDRESS, TX_ADR_WIDTH);
    NRF24L01_Write_Buf(WRITE_REG + RX_ADDR_P0, (uint8_t *)TX_ADDRESS, RX_ADR_WIDTH);
    NRF24L01_Write_Reg(WRITE_REG + EN_AA, 0x3f);
    NRF24L01_Write_Reg(WRITE_REG + EN_RXADDR, 0x3f);
    NRF24L01_Write_Reg(WRITE_REG + SETUP_RETR, 0x0a);
    NRF24L01_Write_Reg(WRITE_REG + RF_CH, 40);
    NRF24L01_Write_Reg(WRITE_REG + RF_SETUP, 0x07);
    NRF24L01_Write_Reg(WRITE_REG + CONFIG, 0x0E);
    NRF_CE = 1;
}

void main(void)
{
    UTIL_enablePrintf();

    initSys();

    while (NRF24L01_Check())
    {
        sleep(500);
    }

    NRF24L01_Init();

    rece_buf[0] = 2;
    rece_buf[1] = 0x88;
    rece_buf[2] = 0x99;

    while (1)
    {
        printf_tiny("%x %x %x %x\n", SPCTL, rece_buf[0], rece_buf[1], rece_buf[2]);
        NRF24L01_TxPacket(rece_buf);
        sleep(500);
    }
}
