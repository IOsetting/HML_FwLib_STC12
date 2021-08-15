/*****************************************************************************/
/** 
 * \file        pca.c
 * \author      IOsetting   | iosetting@outlook.com
 * \brief       operations for PCA and PWM
 * \note        
 * \version     v0.0
 * \ingroup     PCA
******************************************************************************/

#include "hml/pca.h"

#ifdef COMPILE_PCA


/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable stopping PCA counter function in idle mode.
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_StopIdleCount_cmd(Action a)
{
    /* If CIDL=0, the PCA counter will continue functioning during idle mode. 
     * If CIDL=1, the PCA counter will be gated off during idle mode. */
    CONFB(CMOD, BIT_NUM_CMOD_CIDL, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       enable or disable PCA counter overflow interrupt
 *              (enable or disable CF bit in CCON to generate an interrupt)
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_OverflowInt_cmd(Action a)
{
    CONFB(CMOD, BIT_NUM_CMOD_ECF, a);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set counter pulse source
 * \param[in]   ps : pulse source
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_setCounterPulseSource(PCA_counterPulseSource ps)
{
    CMOD = (CMOD & 0xF1) | ((uint8_t)ps << 0x1);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       configure target PCA/PWM
 * \param[in]   pca: target PCA/PWM
 * \param[in]   pc : pointer to a struct includes all configuration information
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_config(PERIPH_PCA pca, PCA_configTypeDef *pc)
{
    PCA_setCounterPulseSource(pc->pulseSource);
    PCA_OverflowInt_cmd(pc->overflowInterrupt);
    PCA_StopIdleCount_cmd(pc->stopIdleCount);
    PCA_setMode(pca, pc->mode);
    PCA_setCompareValue(pca, pc->compareValue);
    PCA_setPWMOutput(pca, pc->pwmOutputMode);
    PCA_setPin(pc->pinmap);
    PCA_resetCounter();
    PCA_start(pc->start);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       reset PCA counter(CL, CH) value to 0x00
 * \param[in]   
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_resetCounter(void)
{
    CL = RESET;
    CH = RESET;
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set initial comparator value of target PCA/PWM
 * \param[in]   pca: target PCA/PWM
 * \param[in]   val: expected value
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_setCompareValue(PERIPH_PCA pca, uint8_t val)
{
    switch (pca)
    {
        case PERIPH_PCA_0: CCAP0H = CCAP0L = val; break;
        case PERIPH_PCA_1: CCAP1H = CCAP1L = val; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set PCA/PWM work mode
 * \param[in]   pca : target PCA/PWM
 * \param[in]   mode: work mode(PCA_mode_0~9)
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_setMode(PERIPH_PCA pca, PCA_mode mode)
{
    switch(pca)
    {
        case PERIPH_PCA_0: CCAPM0 = mode; break;
        case PERIPH_PCA_1: CCAPM1 = mode; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set PWM output mode
 * \param[in]   pca : target PCA/PWM
 * \param[in]   mode: output mode(normal, low)
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_setPWMOutput(PERIPH_PCA pca, PCA_pwm_output mode)
{
    switch (pca)
    {
        case PERIPH_PCA_0: PCA_PWM0 = (PCA_PWM0 & 0xFC) | (uint8_t)mode; break;
        case PERIPH_PCA_1: PCA_PWM1 = (PCA_PWM1 & 0xFC) | (uint8_t)mode; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set output pin of PCA/PWM
 * \param[in]   pm: target pin map
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_setPin(PCA_pinmap pinmap)
{
    CONFB(AUXR1, BIT_NUM_PCA_P4, pinmap);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       turn PCA/PWM counter on or off
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     PCA
 * \remarks     
******************************************************************************/
void PCA_start(Action a)
{
    CR = a;
}


#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
