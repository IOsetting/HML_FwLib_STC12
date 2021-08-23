/*****************************************************************************/
/** 
 * \file        spi.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for SPI
 * \note        
 * \version     v0.1
 * \ingroup     SPI
******************************************************************************/

#ifndef ___HML_SPI_H___
#define ___HML_SPI_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/util.h"

/*****************************************************************************
 *                           enumeration type                                *
 *****************************************************************************/

/**
 * \brief mark SPI data order
 */
typedef enum
{
    SPI_FirstBit_MSB = 0x0,
    SPI_FirstBit_LSB = 0x1,
} SPI_FirstBit;

/**
 * \brief mark SPI clock rate
 */
typedef enum
{
    SPI_BaudRatePrescaler_4     = 0x00,      /* CPU_CLK/4   */
    SPI_BaudRatePrescaler_16    = 0x01,      /* CPU_CLK/16  */
    SPI_BaudRatePrescaler_64    = 0x02,      /* CPU_CLK/64  */
    SPI_BaudRatePrescaler_128   = 0x03,      /* CPU_CLK/128 */
} SPI_BaudRatePrescaler;

/**
 * \brief mark SPI clock phase
 */
typedef enum
{
    SPI_CPHA_1Edge   = 0x00,  /* Data driven by SS pin is low   */
    SPI_CPHA_2Edge   = 0x01,  /* Data driven by the leading edge of SPI 
                               * clock, then sampled on the trailing edge  */
} SPI_CPHA;

/**
 * \brief mark PCA counter pulse source
 */
typedef enum
{
    SPI_CPOL_low  = 0x00, /* SPICLK is low when idle */
    SPI_CPOL_high = 0x01, /* SPICLK is high when idle */
} SPI_CPOL;

/**
 * \brief mark SPI SS pin function
 */
typedef enum
{
    SPI_NSS_Hard = 0x0,     /* SS pin decides whether the device is a master or slave */
    SPI_NSS_Soft = 0x1,     /* Ignore SS pin. MSTR decides master mode */
} SPI_NSS;

/**
 * \brief mark function SPI pin location
 */
typedef enum
{
    SPI_pinmap_P1 = 0x0,     /* P14(SS)/P15(MOSI)/P16(MISO)/P17(SPICLK) */
    SPI_pinmap_P4 = 0x1      /* P40(SS)/P41(MOSI)/P42(MISO)/P43(SPICLK) */
} SPI_pinmap;

/**
 * \brief mark SPI interrupts
 */
typedef enum
{
    SPI_INT_SPIF = 0x80,
    SPI_INT_WCOL = 0x40,
} SPI_INT_Bit;

/**
 * \brief mark SPI mode
 */
typedef enum
{
    SPI_Mode_Slave  = 0x0,
    SPI_Mode_Master = 0x1,
} SPI_Mode;

/*****************************************************************************
 *                           structure define                                *
 *****************************************************************************/

/**
 * \brief mark configure structure
 */
typedef struct
{
    SPI_BaudRatePrescaler  baudRatePrescaler;
    SPI_CPHA           cpha;
    SPI_CPOL           cpol;
    SPI_NSS            nss;
    SPI_Mode           mode;
    SPI_FirstBit       firstBit;
    SPI_pinmap         pinmap;
} SPI_configTypeDef;

/*****************************************************************************
 *                          function declare                                 *
 *****************************************************************************/

void SPI_config(SPI_configTypeDef *sc);
void SPI_setFirstBit(SPI_FirstBit firstBit);
void SPI_setBaudRatePrescaler(SPI_BaudRatePrescaler clockRate);
void SPI_setCPHA(SPI_CPHA cpha);
void SPI_setCPOL(SPI_CPOL cpol);
void SPI_setMode(SPI_Mode mode);
void SPI_setPinmap(SPI_pinmap pinmap);
void SPI_cmd(Action a);
uint8_t SPI_RW(uint8_t b);
void SPI_INT_cmd(Action a);
void SPI_INT_clear(uint8_t intBits);
void SPI_INT_setPriority(IntPriority pri);
void SPI_NSS_cmd(SPI_NSS nss);


#endif
