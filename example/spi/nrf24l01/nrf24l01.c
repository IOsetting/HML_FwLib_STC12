/*****************************************************************************/
/** 
 * \file        nrf24l01.c
 * \author      IOsetting | iosetting@outlook.com
 * \brief       
 * \note        
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

#include "nrf24l01.h"
#include <stdio.h>

uint8_t nrf24_state;

void NRF24L01_writeReg(uint8_t reg, uint8_t value)
{
    NRF_CSN = 0;
    nrf24_state = SPI_RW(reg);
    SPI_RW(value);
    NRF_CSN = 1;
}

uint8_t NRF24L01_readReg(uint8_t reg)
{
    uint8_t value;
    NRF_CSN = 0;
    nrf24_state = SPI_RW(reg);
    value = SPI_RW(NRF24_CMD_NOP);
    NRF_CSN = 1;
    return value;
}

void NRF24L01_readToBuf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    uint8_t u8_ctr;
    NRF_CSN = 0;
    nrf24_state = SPI_RW(reg);
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        pBuf[u8_ctr] = SPI_RW(NRF24_CMD_NOP);
    NRF_CSN = 1;
}

void NRF24L01_writeFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    uint8_t u8_ctr;
    NRF_CSN = 0;
    nrf24_state = SPI_RW(reg);
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)
        SPI_RW(*pBuf++);
    NRF_CSN = 1;
}

void NRF24L01_printBuf(uint8_t *buf)
{
    for (uint8_t i = 0; i < NRF24_PLOAD_WIDTH; i++)
    {
        printf_tiny("%x ", buf[i]);
    }
    printf_tiny("\r\n");
}

void NRF24L01_handelIrqFlag(uint8_t *buf)
{
    int8_t tx_ds, max_rt, rx_dr, pipe_num;
    NRF24L01_checkFlag(&tx_ds, &max_rt, &rx_dr);
    if (NRF24L01_rxAvailable(&pipe_num)) {
        NRF24L01_readToBuf(NRF24_CMD_R_RX_PAYLOAD, buf, NRF24_PLOAD_WIDTH);
    }
    printf_tiny("TX_DS:%x, MAX_RT:%x, RX_DR:%x, PIPE:%x\r\n", tx_ds, max_rt, rx_dr, pipe_num);
}

void NRF24L01_checkFlag(uint8_t *tx_ds, uint8_t *max_rt, uint8_t *rx_dr)
{
    // Read the status & reset the status in one easy call
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_RX_DR|NRF24_FLAG_TX_DS|NRF24_FLAG_MAX_RT);
    // Report to the user what happened
    *tx_ds = nrf24_state & NRF24_FLAG_TX_DS;
    *max_rt = nrf24_state & NRF24_FLAG_MAX_RT;
    *rx_dr = nrf24_state & NRF24_FLAG_RX_DR;
}

bool NRF24L01_rxAvailable(uint8_t* pipe_num)
{
    nrf24_state = NRF24L01_readReg(NRF24_REG_STATUS);
    uint8_t pipe = (nrf24_state >> 1) & 0x07;
    if (pipe > 5)
        return false;
    // If the caller wants the pipe number, include that
    if (pipe_num)
        *pipe_num = pipe;

    return true;
}

void NRF24L01_blockingRx(uint8_t *buf)
{
    while(NRF_IRQ);
    NRF24L01_handelIrqFlag(buf);
}

void NRF24L01_blockingTx(uint8_t *txbuf)
{
    NRF_CE = 0;
    NRF24L01_writeFromBuf(NRF24_CMD_W_TX_PAYLOAD, txbuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
    while (NRF_IRQ == 1);
    NRF24L01_handelIrqFlag(txbuf);
}

void NRF24L01_tx(uint8_t *txbuf)
{
    NRF_CE = 0;
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0E);
    NRF24L01_writeFromBuf(NRF24_CMD_W_TX_PAYLOAD, txbuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
    sleep(4); // 4ms+ for reliable DS state when SETUP_RETR is 0x13
    NRF_CE = 0;
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0F);
    NRF_CE = 1;
}

bool NRF24L01_writeFast(const void* txbuf)
{
    //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
    while ((NRF24L01_readReg(NRF24_REG_STATUS) & NRF24_FLAG_TX_FULL)) {
        if (nrf24_state & NRF24_FLAG_MAX_RT) {
            return false;
        }
    }
    NRF24L01_startFastWrite(txbuf);
    return true;
}

void NRF24L01_startFastWrite(const void* txbuf)
{
    NRF24L01_writeFromBuf(NRF24_CMD_W_TX_PAYLOAD, txbuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
}

void NRF24L01_ackTx(uint8_t pipe, uint8_t *txbuf)
{
    pipe = pipe % 0x06;
    NRF_CE = 0;
    NRF24L01_writeReg(NRF24_CMD_FLUSH_TX, NRF24_CMD_NOP);
    NRF24L01_writeFromBuf(NRF24_CMD_W_ACK_PAYLOAD | pipe, txbuf, NRF24_PLOAD_WIDTH);
    NRF_CE = 1;
}

uint8_t NRF24L01_check(uint8_t *buf)
{
    uint8_t i;
    uint8_t *ptr = (uint8_t *)NRF24_TEST_ADDR;
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, ptr, NRF24_ADDR_WIDTH);
    NRF24L01_readToBuf(NRF24_CMD_R_REGISTER | NRF24_REG_TX_ADDR, buf, NRF24_ADDR_WIDTH);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++) {
        if (buf[i] != *ptr++) return 1;
    }
    return 0;
}

void NRF24L01_setRF(NRF24_rfConfigTypedef *ct)
{
    NRF_CE = 0;
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_SETUP_AW, (ct->addrWidth - 2)); // 3:0x01, 4:0x02, 5:0x03
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_TX_ADDR, ct->txAddr, ct->addrWidth);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_CH, ct->channel);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_SETUP, ct->continuousWave << 7|ct->pplLock << 4|ct->rfDataRate << 3|ct->rfPower << 1);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_AA, ct->enAutoAckPipes);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_RXADDR, ct->enRxAddrs);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_SETUP_RETR, ct->autoRetransDelay << 4 | ct->autoRetransLimit);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_FEATURE, ct->feature);
    NRF_CE = 1;
}

void NRF24L01_setPipe(uint8_t index, uint8_t payloadWidth, uint8_t *addr, uint8_t addrWidth)
{
    NRF_CE = 0;
    index = index % 6;
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RX_PW_P0 + index, payloadWidth);
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_RX_ADDR_P0 + index, addr, addrWidth);
    NRF_CE = 1;
}

void NRF24L01_config(NRF24_configTypedef *ct)
{
    NRF_CE = 0;
    uint8_t bits = ct->maskBits|ct->crcScheme|(ct->enableCRC << 3)|(ct->powerUp << 1)|ct->enableRx;
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, bits);
    NRF_CE = 1;
}
