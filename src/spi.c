/*****************************************************************************/
/** 
 * \file        spi.c
 * \author      IOsetting | iosetting@outlook.com
 * \brief       operations for SPI
 * \note        
 * \version     v0.0
 * \ingroup     SPI
******************************************************************************/

#include "hml/spi.h"

#ifdef COMPILE_SPI

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure SPI module
 * \param[in]   ac: the pointer of configure structure
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_config(SPI_configTypeDef *sc)
{
    SPI_setBaudRatePrescaler(sc->baudRatePrescaler);
    SPI_setCPHA(sc->cpha);
    SPI_setCPOL(sc->cpol);
    SPI_setFirstBit(sc->firstBit);
    SPI_NSS_cmd(sc->nss);
    SPI_setMode(sc->mode);
    SPI_setPin(sc->pinmap);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure SPI data order LSB or MSB
 * \param[in]   firstBit: expected data first bit
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setFirstBit(SPI_FirstBit firstBit)
{
    CONFB(SPCTL, BIT_NUM_DORD, firstBit);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure SPI baud rate prescaler
 * \param[in]   baudRatePrescaler: expected baud rate prescaler
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setBaudRatePrescaler(SPI_BaudRatePrescaler baudRatePrescaler)
{
    SPCTL = (SPCTL & 0xFC) | (uint8_t)baudRatePrescaler;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure SPI clock phase
 * \param[in]   cpha: expected clock phase
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setCPHA(SPI_CPHA cpha)
{
    CONFB(SPCTL, BIT_NUM_CPHA, cpha);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure SPI clock polarity
 * \param[in]   cpol: expected clock polarity
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setCPOL(SPI_CPOL cpol)
{
    CONFB(SPCTL, BIT_NUM_CPOL, cpol);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       disable or enable SPI module
 * \param[in]   a   : expected status
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_cmd(Action a)
{
    CONFB(SPCTL, BIT_NUM_SPEN, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set SPI mode
 * \param[in]   mode: expected mode
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setMode(SPI_Mode mode)
{
    CONFB(SPCTL, BIT_NUM_MSTR, mode);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set pin of SPI
 * \param[in]   pm: target pin map
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_setPin(SPI_pinmap pinmap)
{
    CONFB(AUXR1, BIT_NUM_SPI_P4, pinmap);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable interrupt of SPI
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_INT_cmd(Action a)
{
    CONFB(IE2, BIT_NUM_IE2_ESPI, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       clear SPI INT flag in SPSTAT
 * \param[in]   intBits: INT bits
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_INT_clear(uint8_t intBits)
{
    SPSTAT = SPSTAT | intBits;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set interrupt priority
 * \param[in]   p: target priority
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_INT_setPriority(IntPriority pri)
{
    switch (pri)
    {
        case IntPriority_Lowest:
            CLRB(IP2, BIT_NUM_IP2_PSPI);
            CLRB(IP2H, BIT_NUM_IP2H_PSPIH);
            break;
        case IntPriority_Low:
            SETB(IP2, BIT_NUM_IP2_PSPI);
            CLRB(IP2H, BIT_NUM_IP2H_PSPIH);
            break;
        case IntPriority_High:
            CLRB(IP2, BIT_NUM_IP2_PSPI);
            SETB(IP2H, BIT_NUM_IP2H_PSPIH);
            break;
        case IntPriority_Highest:
            SETB(IP2, BIT_NUM_IP2_PSPI);
            SETB(IP2H, BIT_NUM_IP2H_PSPIH);
            break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       Control whether SS pin is ignored or not
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     SPI
 * \remarks     
******************************************************************************/
void SPI_NSS_cmd(SPI_NSS nss)
{
    CONFB(SPCTL, BIT_NUM_SSIG, nss);
}


#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
