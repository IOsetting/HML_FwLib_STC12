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
 * \remarks     test-board: Minimum System; test-MCU: STC12C5A60S2
 *              In my test STC12 cannot achive the best performance of nRF24L01,
 *              you have to put 20~40ms delay betwen each sending, or error rate
 *              will increase dramatically.
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"
#include <stdio.h>

/**********  SPI(nRF24L01) commands  ***********/
// 
#define NRF24_CMD_R_REGISTER     0x00 // [000A AAAA] Register read
#define NRF24_CMD_W_REGISTER     0x20 // [001A AAAA] Register write
#define NRF24_CMD_R_RX_PAYLOAD   0x61 // Read RX payload
#define NRF24_CMD_W_TX_PAYLOAD   0xA0 // Write TX payload
#define NRF24_CMD_FLUSH_TX       0xE1 // Flush TX FIFO
#define NRF24_CMD_FLUSH_RX       0xE2 // Flush RX FIFO
#define NRF24_CMD_REUSE_TX_PL    0xE3 // Reuse TX payload
#define NRF24_CMD_R_RX_PL_WID    0x60 // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
#define NRF24_CMD_W_ACK_PAYLOAD  0xA8 // [1010 1PPP] Write ACK Payload to be with ACK packet on PIPE PPP
#define NRF24_CMD_W_TX_PAYLOAD_NOACK 0xB0 //Write TX payload and disable AUTOACK
#define NRF24_CMD_NOP            0xFF // No operation (used for reading status register)

#define NRF24_CMD_ACTIVATE       0x50 // (De)Activates R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK features
#define NRF24_CMD_LOCK_UNLOCK    0x50 // Lock/unlock exclusive features

// SPI(nRF24L01) register address definitions
#define NRF24_REG_CONFIG         0x00 // Configuration register
#define NRF24_REG_EN_AA          0x01 // Enable "Auto acknowledgment"
#define NRF24_REG_EN_RXADDR      0x02 // Enable RX addresses
#define NRF24_REG_SETUP_AW       0x03 // Setup of address widths
#define NRF24_REG_SETUP_RETR     0x04 // Setup of automatic re-transmit
#define NRF24_REG_RF_CH          0x05 // RF channel
#define NRF24_REG_RF_SETUP       0x06 // RF setup
#define NRF24_REG_STATUS         0x07 // Status register
#define NRF24_REG_OBSERVE_TX     0x08 // Transmit observe register
#define NRF24_REG_RPD            0x09 // Received power detector
#define NRF24_REG_RX_ADDR_P0     0x0A // Receive address data pipe 0
#define NRF24_REG_RX_ADDR_P1     0x0B // Receive address data pipe 1
#define NRF24_REG_RX_ADDR_P2     0x0C // Receive address data pipe 2
#define NRF24_REG_RX_ADDR_P3     0x0D // Receive address data pipe 3
#define NRF24_REG_RX_ADDR_P4     0x0E // Receive address data pipe 4
#define NRF24_REG_RX_ADDR_P5     0x0F // Receive address data pipe 5
#define NRF24_REG_TX_ADDR        0x10 // Transmit address
#define NRF24_REG_RX_PW_P0       0x11 // Number of bytes in RX payload in data pipe 0
#define NRF24_REG_RX_PW_P1       0x12 // Number of bytes in RX payload in data pipe 1
#define NRF24_REG_RX_PW_P2       0x13 // Number of bytes in RX payload in data pipe 2
#define NRF24_REG_RX_PW_P3       0x14 // Number of bytes in RX payload in data pipe 3
#define NRF24_REG_RX_PW_P4       0x15 // Number of bytes in RX payload in data pipe 4
#define NRF24_REG_RX_PW_P5       0x16 // Number of bytes in RX payload in data pipe 5
#define NRF24_REG_FIFO_STATUS    0x17 // FIFO status register
#define NRF24_REG_DYNPD          0x1C // Enable dynamic payload length
#define NRF24_REG_FEATURE        0x1D // Feature register

// Register bits definitions
#define NRF24_CONFIG_PRIM_RX     0x01 // PRIM_RX bit in CONFIG register
#define NRF24_CONFIG_PWR_UP      0x02 // PWR_UP bit in CONFIG register
#define NRF24_FEATURE_EN_DYN_ACK 0x01 // EN_DYN_ACK bit in FEATURE register
#define NRF24_FEATURE_EN_ACK_PAY 0x02 // EN_ACK_PAY bit in FEATURE register
#define NRF24_FEATURE_EN_DPL     0x04 // EN_DPL bit in FEATURE register
#define NRF24_FLAG_RX_DREADY     0x40 // RX_DR bit (data ready RX FIFO interrupt)
#define NRF24_FLAG_TX_DSENT      0x20 // TX_DS bit (data sent TX FIFO interrupt)
#define NRF24_FLAG_MAX_RT        0x10 // MAX_RT bit (maximum number of TX re-transmits interrupt)
#define NRF24_FLAG_TX_FULL       0x01 // 1:TX FIFO full

// Register masks definitions
#define NRF24_MASK_REG_MAP       0x1F // Mask bits[4:0] for CMD_RREG and CMD_WREG commands
#define NRF24_MASK_CRC           0x0C // Mask for CRC bits [3:2] in CONFIG register
#define NRF24_MASK_STATUS_IRQ    0x70 // Mask for all IRQ bits in STATUS register
#define NRF24_MASK_RF_PWR        0x06 // Mask RF_PWR[2:1] bits in RF_SETUP register
#define NRF24_MASK_RX_P_NO       0x0E // Mask RX_P_NO[3:1] bits in STATUS register
#define NRF24_MASK_DATARATE      0x28 // Mask RD_DR_[5,3] bits in RF_SETUP register
#define NRF24_MASK_EN_RX         0x3F // Mask ERX_P[5:0] bits in EN_RXADDR register
#define NRF24_MASK_RX_PW         0x3F // Mask [5:0] bits in RX_PW_Px register
#define NRF24_MASK_RETR_ARD      0xF0 // Mask for ARD[7:4] bits in SETUP_RETR register
#define NRF24_MASK_RETR_ARC      0x0F // Mask for ARC[3:0] bits in SETUP_RETR register
#define NRF24_MASK_RXFIFO        0x03 // Mask for RX FIFO status bits [1:0] in FIFO_STATUS register
#define NRF24_MASK_TXFIFO        0x30 // Mask for TX FIFO status bits [5:4] in FIFO_STATUS register
#define NRF24_MASK_PLOS_CNT      0xF0 // Mask for PLOS_CNT[7:4] bits in OBSERVE_TX register
#define NRF24_MASK_ARC_CNT       0x0F // Mask for ARC_CNT[3:0] bits in OBSERVE_TX register

#define NRF24_ADDR_WIDTH         5    // RX/TX address width
#define NRF24_PLOAD_WIDTH        32   // Payload width
#define NRF24_TEST_ADDR          "nRF24"

uint8_t nrf24_state;

typedef enum
{
    NRF24_MODE_RX  = 0x00,
    NRF24_MODE_TX  = 0x01
} NRF24_MODE;

typedef enum
{
    NRF24_SCEN_RX          = 0x00,
    NRF24_SCEN_TX          = 0x01,
    NRF24_SCEN_HALF_DUPLEX = 0x02
} NRF24_SCEN;

uint8_t xbuf[NRF24_PLOAD_WIDTH + 1];
const uint8_t TX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x65};
const uint8_t RX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x22};
const NRF24_SCEN CURRENT_SCEN = NRF24_SCEN_TX;

#define NRF_CSN  P1_4
#define NRF_MOSI P1_5
#define NRF_MISO P1_6
#define NRF_SCK  P1_7
#define NRF_IRQ  P3_2
#define NRF_CE   P3_7

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

/**
* Flush the RX FIFO
*/
void NRF24L01_flushRX(void)
{
    NRF24L01_writeReg(NRF24_CMD_FLUSH_RX, NRF24_CMD_NOP);
}

/**
* Flush the TX FIFO
*/
void NRF24L01_flushTX(void)
{
    NRF24L01_writeReg(NRF24_CMD_FLUSH_TX, NRF24_CMD_NOP);
}

void NRF24L01_checkFlag(uint8_t *tx_ds, uint8_t *max_rt, uint8_t *rx_dr)
{
    // Read the status & reset the status in one easy call
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_RX_DREADY|NRF24_FLAG_TX_DSENT|NRF24_FLAG_MAX_RT);
    // Report to the user what happened
    *tx_ds = nrf24_state & NRF24_FLAG_TX_DSENT;
    *max_rt = nrf24_state & NRF24_FLAG_MAX_RT;
    *rx_dr = nrf24_state & NRF24_FLAG_RX_DREADY;
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

void NRF24L01_handelIrqFlag(uint8_t *buf)
{
    int8_t tx_ds, max_rt, rx_dr, pipe_num;
    NRF24L01_checkFlag(&tx_ds, &max_rt, &rx_dr);
    if (NRF24L01_rxAvailable(&pipe_num)) {
        NRF24L01_readToBuf(NRF24_CMD_R_RX_PAYLOAD, buf, NRF24_PLOAD_WIDTH);
    }
    printf_tiny("TX_DS:%x, MAX_RT:%x, RX_DR:%x, PIPE:%x\r\n", tx_ds, max_rt, rx_dr, pipe_num);
    //NRF24L01_printBuf(xbuf);
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

void NRF24L01_startFastWrite(const void* txbuf)
{
    NRF24L01_writeFromBuf(NRF24_CMD_W_TX_PAYLOAD, txbuf, NRF24_PLOAD_WIDTH);
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

void NRF24L01_resetTX(void)
{
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_STATUS, NRF24_FLAG_MAX_RT);//Clear max retry flag
    NRF_CE = 0;
    NRF_CE = 1;
}

uint8_t NRF24L01_check(void)
{
    uint8_t i;
    uint8_t *ptr = (uint8_t *)NRF24_TEST_ADDR;
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, ptr, NRF24_ADDR_WIDTH);
    NRF24L01_readToBuf(NRF24_CMD_R_REGISTER | NRF24_REG_TX_ADDR, xbuf, NRF24_ADDR_WIDTH);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++) {
        if (xbuf[i] != *ptr++) return 1;
    }
    return 0;
}

void NRF24L01_init(NRF24_MODE mode)
{
    NRF_CE = 0;
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_TX_ADDR, (uint8_t *)TX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RX_PW_P0, NRF24_PLOAD_WIDTH);
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_RX_ADDR_P0, (uint8_t *)TX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RX_PW_P1, NRF24_PLOAD_WIDTH);
    NRF24L01_writeFromBuf(NRF24_CMD_W_REGISTER + NRF24_REG_RX_ADDR_P1, (uint8_t *)RX_ADDRESS, NRF24_ADDR_WIDTH);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_AA, 0x3f);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_EN_RXADDR, 0x3f);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_SETUP_RETR, 0x13);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_CH, 40);
    NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_RF_SETUP, 0x07);
    switch (mode)
    {
        case NRF24_MODE_TX:
            NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0E);
            break;
        case NRF24_MODE_RX:
        default:
            NRF24L01_writeReg(NRF24_CMD_W_REGISTER + NRF24_REG_CONFIG, 0x0F);
            break;
    }
    NRF_CE = 1;
}

void EXTI0_irqHandler(void) __interrupt (IE0_VECTOR)
{
    NRF24L01_handelIrqFlag(xbuf);
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

void main(void)
{
    uint8_t sta;
    uint8_t tmp[] = {
            0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
            0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
            0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
            0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};

    UTIL_enablePrintf();
    SPI_init();

    while (NRF24L01_check())
    {
        printf_tiny("Check failed\r\n");
        sleep(500);
    }

    switch (CURRENT_SCEN)
    {
    case NRF24_SCEN_TX:
        NRF24L01_init(NRF24_MODE_TX);
        EXTI_init();
        while (true)
        {
            NRF24L01_writeFast(tmp);
            sleep(10);
        }
        break;

    case NRF24_SCEN_RX:
        NRF24L01_init(NRF24_MODE_RX);
        EXTI_init();
        while(true);
        break;

    case NRF24_SCEN_HALF_DUPLEX:
        NRF24L01_init(NRF24_MODE_RX);
        EXTI_init();
        while (true)
        {
            NRF24L01_tx(tmp);
            sleep(500);
        }
        break;

    default:
        printf_tiny("Unknown scen\r\n");
        break;
    }
}
