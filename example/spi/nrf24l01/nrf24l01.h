/*****************************************************************************/
/** 
 * \file        nrf24l01.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       
 * \note        
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

#ifndef ___HML_NRF24L01_H___
#define ___HML_NRF24L01_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/

#define NRF_CSN  P1_4
#define NRF_MOSI P1_5
#define NRF_MISO P1_6
#define NRF_SCK  P1_7
#define NRF_IRQ  P3_2
#define NRF_CE   P3_7

// SPI(nRF24L01) commands
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
#define NRF24_FLAG_RX_DR         0x40 // RX_DR bit (data ready RX FIFO interrupt)
#define NRF24_FLAG_TX_DS         0x20 // TX_DS bit (data sent TX FIFO interrupt)
#define NRF24_FLAG_MAX_RT        0x10 // MAX_RT bit (maximum number of TX re-transmits interrupt)
#define NRF24_FLAG_TX_FULL       0x01 // 1:TX FIFO full


// NRF24_REG_RF_SETUP
#define NRF24_BIT_RF_SETUP_CONT_WAVE  0x80 // Enables continuous carrier transmit when high
#define NRF24_BIT_RF_SETUP_PLL_LOCK   0x10 // Force PLL lock signal. Only used in test
#define NRF24_BIT_RF_SETUP_RF_DR_250K 0x20 // [RF_DR_LOW, RF_DR_HIGH] = [1,0] RF data rate
#define NRF24_BIT_RF_SETUP_RF_DR_1M   0x00 // [RF_DR_LOW, RF_DR_HIGH] = [0,0] RF data rate
#define NRF24_BIT_RF_SETUP_RF_DR_2M   0x04 // [RF_DR_LOW, RF_DR_HIGH] = [0,1] RF data rate

#define NRF24_PIPE0   0x01
#define NRF24_PIPE1   0x02
#define NRF24_PIPE2   0x04
#define NRF24_PIPE3   0x08
#define NRF24_PIPE4   0x10
#define NRF24_PIPE5   0x20

#define NRF24_ADDR_WIDTH         5    // RX/TX address width
#define NRF24_PLOAD_WIDTH        32   // Payload width
#define NRF24_TEST_ADDR          "nRF24"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

typedef enum
{
    NRF24_configMaskRxDR  = 0x40,
    NRF24_configMaskTxDS  = 0x20,
    NRF24_configMaskMaxRT = 0x10,
} NRF24_configMask;

typedef enum
{
    NRF24_crcEncodingScheme1Byte  = 0x00,
    NRF24_crcEncodingScheme2Byte  = 0x04,
} NRF24_crcEncodingScheme;

typedef enum
{
    NRF24_rfDataRate250K = 0x20,
    NRF24_rfDataRate1M   = 0x00,
    NRF24_rfDataRate2M   = 0x04
} NRF24_rfDataRate;

typedef enum
{
    NRF24_rfPowerNeg18db = 0x00,
    NRF24_rfPowerNeg12db = 0x01,
    NRF24_rfPowerNeg6db  = 0x02,
    NRF24_rfPower0db     = 0x03,
} NRF24_rfPower;

typedef enum
{
    NRF24_featureDynamicPayloadLength = 0x04,
    NRF24_featurePayloadWithACK       = 0x02,
    NRF24_featureDYNACK               = 0x01,
} NRF24_feature;

typedef enum
{
    NRF24_MODE_RX  = 0x00,
    NRF24_MODE_TX  = 0x01
} NRF24_MODE;

typedef enum
{
    NRF24_SCEN_RX_POLLING  = 0x00,
    NRF24_SCEN_RX_EXTI     = 0x01,
    NRF24_SCEN_TX          = 0x02,
    NRF24_SCEN_HALF_DUPLEX = 0x03
} NRF24_SCEN;


/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

typedef struct
{
    uint8_t          addrWidth;
    uint8_t          *txAddr;
    uint8_t          channel;
    uint8_t          enAutoAckPipes;
    uint8_t          enRxAddrs;
    uint8_t          autoRetransDelay;
    uint8_t          autoRetransLimit;
    Action           continuousWave;
    Action           pplLock;
    NRF24_rfDataRate rfDataRate;
    NRF24_rfPower    rfPower;
    NRF24_feature    feature;
} NRF24_rfConfigTypedef;

typedef struct
{
    uint8_t          maskBits;
    Action           enableCRC;
    NRF24_crcEncodingScheme crcScheme;
    Action           powerUp;
    Action           enableRx;
} NRF24_configTypedef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/

void NRF24L01_writeReg(uint8_t reg, uint8_t value);
uint8_t NRF24L01_readReg(uint8_t reg);
void NRF24L01_readToBuf(uint8_t reg, uint8_t *pBuf, uint8_t len);
void NRF24L01_writeFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len);
void NRF24L01_printBuf(uint8_t *buf);
void NRF24L01_handelIrqFlag(uint8_t *buf);
void NRF24L01_checkFlag(uint8_t *tx_ok, uint8_t *tx_fail, uint8_t *rx_ready);
bool NRF24L01_rxAvailable(uint8_t* pipe_num);
void NRF24L01_blockingRx(uint8_t *buf);
void NRF24L01_blockingTx(uint8_t *txbuf);
void NRF24L01_tx(uint8_t *txbuf);
void NRF24L01_ackTx(uint8_t pipe, uint8_t *txbuf);
bool NRF24L01_writeFast(const void* txbuf);
void NRF24L01_startFastWrite(const void* txbuf);
uint8_t NRF24L01_check(uint8_t *buf);
void NRF24L01_setRF(NRF24_rfConfigTypedef *ct);
void NRF24L01_setPipe(uint8_t index, uint8_t payloadWidth, uint8_t *addr, uint8_t addrWidth);
void NRF24L01_config(NRF24_configTypedef *ct);

#endif
