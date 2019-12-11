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

#ifdef __CONF_COMPILE_RCC

uint8_t df = 0x1;       /* mark current divided factor */

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
    CONFB(AUXR,BIT_NUM_BRTR,a);
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
    CONFB(WAKE_CLKO,BIT_NUM_BRTCLKO,a);
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
    CONFB(AUXR,BIT_NUM_BRTx12,pre);
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
 * \author      Weilun Fong
 * \date        
 * \brief       set division factor of system clock
 * \param[in]   d: division factor
 * \return      none
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
void RCC_setClockDivisionFactor(RCC_prescaler d)
{
    CLK_DIV = (byte)d;
    df = pow(2,d);
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
    SET_BIT_MASK(IAP_CONTR,SWRST);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get current system clock frequency
 * \param[in]   
 * \return      current system clock frequency
 * \ingroup     RCC
 * \remarks     
******************************************************************************/
uint32_t RCC_getSystemClockFrequency(void)
{
    return (MCU_FRE_CLK/df);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
