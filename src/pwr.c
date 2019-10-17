/*****************************************************************************/
/** 
 * \file        pwr.c
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for power management
 * \note        
 * \version     v0.0
 * \ingroup     PWR
******************************************************************************/

#include "pwr.h"

#ifdef __CONF_COMPILE_PWR

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable idle mode
 * \param[in]   
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_idle(void)
{
    SET_BIT_MASK(PCON,IDL);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable power down mode
 * \param[in]   
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_powerDown(void)
{
    SET_BIT_MASK(PCON,PD);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       clear LVDF bit in PCON register
 * \param[in]   
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_LVD_clearFlag(void)
{
    CLR_BIT_MASK(PCON,LVDF);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable LVD(low voltage level detect) module
 * \param[in]   a: expected status
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_LVD_cmd(Action a)
{
     CONFB(P4SW,BIT_NUM_NA_P46,~a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get value of LVDF bit in PCON register
 * \param[in]   
 * \return      none
 * \ingroup     PWR
 * \remarks     current value of LVDF bit
******************************************************************************/
FunctionalState PWR_LVD_getFlag(void)
{
    return ((FunctionalState)GET_BIT(PCON,LVDF));
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable interrupt status of LVD module
 * \param[in]   a: expected status
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_LVD_INT_cmd(Action a)
{
    ELVD = (FunctionalState)a;
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable or enable specified pin for waking up MCU from power 
 *              down state
 * \param[in]   a  : expected status
 * \param[in]   pin: target pin
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_PD_IE_cmd(PWR_PD_IEPIN pin,Action a)
{
    switch(pin)
    {
        case PWR_PD_IEPIN_RXD: CONFB(WAKE_CLKO,BIT_NUM_RD_PIN_IE,a); break;
        case PWR_PD_IEPIN_T0 : CONFB(WAKE_CLKO,BIT_NUM_T0_PIN_IE,a); break;
        case PWR_PD_IEPIN_T1 : CONFB(WAKE_CLKO,BIT_NUM_T1_PIN_IE,a); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable wake-up timer under power down mode
 * \param[in]   a: expected status
 * \return      none
 * \ingroup     PWR
 * \remarks     
******************************************************************************/
void PWR_WKT_cmd(Action a)
{
    CONFB(WKTCH,BIT_NUM_WKTEN,a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set how many wake-up clock cycle consume until MCU wakes up by 
 *              itself
 * \param[in]   c: expected status
 * \return      if parameter 'c' is larger than 4096, the function will return
 *              false
 * \ingroup     PWR
 * \remarks     length of clock cycle is about 560us(not accurate)
******************************************************************************/
bool PWR_WKT_setWakeCount(uint16_t c)
{
    if(c > 4096)
    {
        WKTCL = (byte)(c & 0x00FF);
        WKTCH = (byte)((c & 0x0F00) >> 0x8);

        return true;
    }
    else
    {
        return false;
    }
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
