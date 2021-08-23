/*****************************************************************************/
/** 
 * \file        tim.c
 * \author      Jiabin Hsu   | zsiothsu@zhishan-iot.tk
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       operations for timers
 * \note        
 * \version     v0.0
 * \ingroup     TIM
******************************************************************************/

#include "hml/tim.h"

#ifdef COMPILE_TIM

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2021/03/04
 * \brief       calculate initial value for THx/TLx register
 * \param[in]   time: expected timing cycle(unit: us)
 * \param[in]   mode: work mode of timer
 * \param[in]   pre : prescaler factor
 * \return      initial value of timer counter register(if return 0x0000, it 
 *              means that the time has over the limit)
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
uint16_t TIM_calculateValue(uint16_t time, TIM_mode mode, TIM_prescaler pre)
{
    uint16_t maxTick = 0x0000;     /* MachineCycle: 12/MCU_FRE_CLK */
    uint16_t t       = time * (MCU_FRE_CLK / 1000000) / pre;

    switch (mode)
    {
        case TIM_mode_0: maxTick = 0x1FFF; break;
        case TIM_mode_1: maxTick = 0xFFFF; break;
        case TIM_mode_2: maxTick = 0x00FF; break;
        case TIM_mode_3: maxTick = 0x00FF; break;
        default: break;
    }

    if (t >= maxTick)
    {
        return 0;
    }
    else
    {
        return maxTick + 1 - t;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       lanuch timer or not
 * \param[in]   tim: target timer
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_cmd(PERIPH_TIM tim, Action a)
{
    switch (tim)
    {
        case PERIPH_TIM_0: TR0 = a; break;
        case PERIPH_TIM_1: TR1 = a; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable clock output
 * \param[in]   tim: target timer
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setClockOutput(PERIPH_TIM tim, Action a)
{
    switch (tim)
    {
        case PERIPH_TIM_0: CONFB(WAKE_CLKO, BIT_NUM_T0CLKO, a); break;
        case PERIPH_TIM_1: CONFB(WAKE_CLKO, BIT_NUM_T1CLKO, a); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure target timer
 * \param[in]   tim: target timer
 * \param[in]   tc : pointer to a struct includes all configuration information
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_config(PERIPH_TIM tim, TIM_configTypeDef *tc)
{
    TIM_setFunction(tim, tc->function);
    TIM_setMode(tim, tc->mode);
    TIM_setValue(tim, tc->value);
    TIM_setPrescaler(tim, tc->prescaler);
    TIM_INT_cmd(tim, tc->interruptState);
    TIM_INT_setPriority(tim, tc->interruptPriority);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get value of target timer initial value register
 * \param[in]   tim: target timer
 * \return      current value of target timer initial value register, it will 
 *              return 0 when pass a wrong patameter
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
uint16_t TIM_getValue(PERIPH_TIM tim)
{
    switch (tim)
    {
        case PERIPH_TIM_0: return ((TH0 << 0x08) | TL0);
        case PERIPH_TIM_1: return ((TH1 << 0x08) | TL1);
        default: return 0;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get overflow state of specified timer
 * \param[in]   tim: target timer
 * \return      true(overflow) or false
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
bool TIM_isOverflow(PERIPH_TIM tim)
{
    switch (tim)
    {
        case PERIPH_TIM_0: return (bool)TF0;
        case PERIPH_TIM_1: return (bool)TF1;
        default: return false;
    }
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set specified timer as counter or timer
 * \param[in]   tim: target timer
 * \param[in]   f  : expected function, and the value mustbe TIM_function_cnt 
 *              or TIM_function_tim
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setFunction(PERIPH_TIM tim, TIM_function f)
{
    switch (tim)
    {
        case PERIPH_TIM_0: CONFB(TMOD, BIT_NUM_T0_CT, f); break;
        case PERIPH_TIM_1: CONFB(TMOD, BIT_NUM_T1_CT, f); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set work mode of specified timer
 * \param[in]   tim : target timer
 * \param[in]   mode: work mode(TIM_mode_0~3)
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setMode(PERIPH_TIM tim, TIM_mode mode)
{
    switch(tim)
    {
        case PERIPH_TIM_0: TMOD = (TMOD & 0xFC) | mode; break;
        case PERIPH_TIM_1: TMOD = (TMOD & 0xCF) | (mode << 0x04); break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set prescaler factor for selecting 1T or 12T mode
 * \param[in]   tim: target timer
 * \param[in]   pre: prescaler factor value
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setPrescaler(PERIPH_TIM tim, TIM_prescaler pre)
{
    switch (tim)
    {
        case PERIPH_TIM_0:
        {
            if (pre == TIM_prescaler_1)
            {
                SET_BIT_MASK(AUXR, T0x12);
            }
            else
            {
                CLR_BIT_MASK(AUXR, T0x12);
            }
        } break;
        case PERIPH_TIM_1:
        {
            if (pre == TIM_prescaler_1)
            {
                SET_BIT_MASK(AUXR, T1x12);   /* 1T mode */
            }
            else
            {
                CLR_BIT_MASK(AUXR, T1x12);
            }
        } break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set initial value register of target timer
 * \param[in]   tim: target timer
 * \param[in]   val: expected value with [TH:TL]
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_setValue(PERIPH_TIM tim, uint16_t val)
{
    switch (tim)
    {
        case PERIPH_TIM_0:
        {
            TH0 = (uint8_t)((val >> 0x8) & 0x00FF);
            TL0 = (uint8_t)(val & 0x00FF);
        } break;
        case PERIPH_TIM_1:
        {
            TH1 = (uint8_t)((val >> 0x8) & 0x00FF);
            TL1 = (uint8_t)(val & 0x00FF);
        } break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable interrupt function of target timer
 * \param[in]   tim: target timer
 * \param[in]   a  : expected state
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_INT_cmd(PERIPH_TIM tim, Action a)
{
    switch (tim)
    {
        case PERIPH_TIM_0: ET0 = a; break;
        case PERIPH_TIM_1: ET1 = a; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       set interrupt priority of target timer
 * \param[in]   tim: target timer
 * \param[in]   priority: expected interrupt priority
 * \return      none
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
void TIM_INT_setPriority(PERIPH_TIM tim, IntPriority priority)
{
    switch (tim)
    {
        case PERIPH_TIM_0:
            switch (priority)
            {
                case IntPriority_Lowest:
                    PT0 = RESET;
                    CLRB(IPH, BIT_NUM_PT0H);
                    break;
                case IntPriority_Low:
                    PT0 = SET;
                    CLRB(IPH, BIT_NUM_PT0H);
                    break;
                case IntPriority_High:
                    PT0 = RESET;
                    SETB(IPH, BIT_NUM_PT0H);
                    break;
                case IntPriority_Highest:
                    PT0 = SET;
                    SETB(IPH, BIT_NUM_PT0H);
                    break;
                default: break;
            }
            break;
        case PERIPH_TIM_1: 
            switch (priority)
            {
                case IntPriority_Lowest:
                    PT1 = RESET;
                    CLRB(IPH, BIT_NUM_PT1H);
                    break;
                case IntPriority_Low:
                    PT1 = SET;
                    CLRB(IPH, BIT_NUM_PT1H);
                    break;
                case IntPriority_High:
                    PT1 = RESET;
                    SETB(IPH, BIT_NUM_PT1H);
                    break;
                case IntPriority_Highest:
                    PT1 = SET;
                    SETB(IPH, BIT_NUM_PT1H);
                    break;
                default: break;
            }
            break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       get 16-bit initial value of TIM1 baud rate generator
 * \param[in]   baud: expected baud rate
 * \return      result(0x00 means overflow)
 * \ingroup     TIM
 * \remarks     
******************************************************************************/
uint16_t TIM_calcInitValue(uint32_t baud, TIM_prescaler  timPrescaler, Action doubleBaudrate)
{
    uint16_t res = 0x0000;
    uint32_t max = UTIL_getSystemClockFrequency() / timPrescaler;
    if (doubleBaudrate == ENABLE) 
    {
        max = max * 2;
    }
    if (baud <= max/32)
    {
        res = (uint16_t)(256 - max/baud/32);
    }
    res = res & 0x00FF;
    res = (res << 0x8) | res;
    return res;
}

void TIM_TIM1_config(uint32_t baudrate, TIM_prescaler  timPrescaler, Action doubleBaudrate)
{
    uint16_t initValue = TIM_calcInitValue(baudrate, timPrescaler, doubleBaudrate);
    TIM_configTypeDef tc;
    tc.function          = TIM_function_tim;
    tc.interruptState    = DISABLE;
    tc.interruptPriority = DISABLE;
    tc.mode              = TIM_mode_2;
    tc.prescaler         = timPrescaler;
    tc.value             = 0x00;   /* because of logic order, the value need to be reloaded one more time */
    TIM_config(PERIPH_TIM_1, &tc);
    TIM_cmd(PERIPH_TIM_1, ENABLE);
    TIM_setValue(PERIPH_TIM_1, initValue); // UART_getTim1InitValue(uc->baudrate, uc->timPrescaler, uc->doubleBaudrate)
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
