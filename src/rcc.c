/*****************************************************************************/
/** 
 * \file        rcc.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operation for reset and clock control
 * \note        
 * \version     v0.0
 * \ingroup     RCC
******************************************************************************/

#include "hml/rcc.h"

#ifdef COMPILE_RCC


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable BRT module
 * \param[in]   a: expected action, then value must be ENABLE or DISABLE
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_BRT_cmd(Action a)
{
    CONFB(AUXR, BIT_NUM_BRTR, a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       confiure clock output of BRT module
 * \param[in]   a: expected action, then value must be ENABLE or DISABLE
 * \return      none
 * \ingroup     RCC
 * \remarks     (1)control status of clock output via P10 from BRT module
 *              (2)the frequency value of output clock is _SYS_CLK_/(256-BRT)/2
 *              (under 1T mode) or _SYS_CLK_/12/(256-BRT)/2 (under 12T mode)
******************************************************************************/
void RCC_BRT_setClockOutput(Action a)
{
    CONFB(WAKE_CLKO, BIT_NUM_BRTCLKO, a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set prescaler mode of BRT module
 * \param[in]   pre: expected prescaler mode
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_BRT_setPrescaler(RCC_BRT_prescaler pre)
{
    CONFB(AUXR, BIT_NUM_BRTx12, pre);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set value of  BRT reload register
 * \param[in]   val: target value
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_BRT_setValue(uint8_t val)
{
    BRT = val;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get 16-bit initial value of BRT baud rate generator
 * \param[in]   baud: expected baud rate
 * \return      result(0x00 means overflow)
 * \ingroup     UART
 * \remarks     
******************************************************************************/
uint16_t RCC_BRT_calcInitValue(uint32_t baud, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate)
{
    uint16_t res = 0x0000;
    uint32_t max = UTIL_getSystemClockFrequency();
    if (brtPrescaler == RCC_BRT_prescaler_12)
    {
        max = max / 12;
    }
    if (doubleBaudrate == ENABLE) 
    {
        max = max * 2;
    }
    if (baud <= max/32)
    {
        res = (uint16_t)(256 - max/baud/32);
    }
    return res;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize BRT baud rate generator with speicified baudrate
 * \param[in]   baudrate: expected baud rate
 * \param[in]   brtPrescaler: BRT prescaler
 * \param[in]   doubleBaudrate: double baudrate or not
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_BRT_config(uint32_t baudrate, RCC_BRT_prescaler brtPrescaler, Action doubleBaudrate)
{
    uint16_t initValue = RCC_BRT_calcInitValue(baudrate, brtPrescaler, doubleBaudrate);
    RCC_BRT_cmd(ENABLE);
    RCC_BRT_setPrescaler(brtPrescaler);
    RCC_BRT_setValue(initValue);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       software reset MCU
 * \param[in]   
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_softwareReset(void)
{
    SET_BIT_MASK(IAP_CONTR, SWRST);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
