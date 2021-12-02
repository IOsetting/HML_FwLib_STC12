/*****************************************************************************/
/** 
 * \file        spi_nrf24l01_tx.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Example code of SPI driving NRF24L01 module in all scenarios
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
#include "nrf24l01.h"
#include <stdio.h>

extern uint8_t nrf24_buf[NRF24_PLOAD_WIDTH];
const uint8_t txAddr[] = {0x32,0x4E,0x6F,0x64,0x65};
const uint8_t rxAddr[] = {0x32,0x4E,0x6F,0x64,0x22};

void EXTI0_irqHandler(void) __interrupt (IE0_VECTOR)
{
    NRF24L01_handelIrqFlag(nrf24_buf);
}

void EXTI_init(void)
{
    EXTI_configTypeDef ec;
    ec.mode     = EXTI_mode_lowLevel;
    ec.priority = IntPriority_High;
    EXTI_config(PERIPH_EXTI_0, &ec);
    EXTI_cmd(PERIPH_EXTI_0, ENABLE);
    UTIL_setInterrupts(ENABLE);
}

void SPI_init(void)
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

void NRF24L01_init(void)
{
    NRF24_rfConfigTypedef ct;
    ct.channel = 40;
    ct.rfPower = NRF24_rfPower0db;
    ct.rfDataRate = NRF24_rfDataRate1M;
    ct.continuousWave = DISABLE;
    ct.pplLock = DISABLE;
    ct.autoRetransDelay = 1;
    ct.autoRetransLimit = 3;
    ct.addrWidth = 5;
    ct.txAddr = (uint8_t *)txAddr;
    ct.enAutoAckPipes = NRF24_PIPE0|NRF24_PIPE1|NRF24_PIPE2;
    ct.enRxAddrs = NRF24_PIPE0|NRF24_PIPE1|NRF24_PIPE2;
    ct.feature = NRF24_featurePayloadWithACK;
    NRF24L01_setRF(&ct);

    NRF24L01_setPipe(0, 32, (uint8_t *)txAddr, NRF24_ADDR_WIDTH);
    NRF24L01_setPipe(1, 32, (uint8_t *)rxAddr, NRF24_ADDR_WIDTH);

    NRF24_configTypedef ct2;
    ct2.maskBits = 0x00;
    ct2.enableCRC = ENABLE;
    ct2.crcScheme = NRF24_crcEncodingScheme2Byte;
    ct2.enableRx = ENABLE;
    ct2.powerUp = ENABLE;
    NRF24L01_config(&ct2);
}

void main(void)
{
    UTIL_enablePrintf();
    SPI_init();

    while (NRF24L01_check(nrf24_buf))
    {
        printf_tiny("Check failed\r\n");
        sleep(500);
    }
    nrf24_buf[0] = 0x08;

    NRF24L01_init();
    EXTI_init();
    while (true)
    {
        NRF24L01_tx((uint8_t *)nrf24_buf);
        sleep(500);
    }
}
