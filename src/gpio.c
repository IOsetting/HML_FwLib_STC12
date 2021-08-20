/*****************************************************************************/
/** 
 * \file        gpio.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       operations for GPIO module
 * \note        
 * \version     v0.0
 * \ingroup     GPIO
******************************************************************************/

#include "hml/gpio.h"

#ifdef COMPILE_GPIO

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure target GPIO port
 * \param[in]   gpio: target GPIO port
 * \param[in]   gc  : configuration struct stores all information
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_config(PERIPH_GPIO gpio, GPIO_configTypeDef *gc)
{
    GPIO_configMode(gpio, gc->pin, gc->mode);
    GPIO_configPortValue(gpio, gc->value);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure state of target GPIO bit as SET or RESET
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \param[in]   f   : expected state
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_configBitValue(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin, FunctionalState f)
{
    if (f == RESET)
    {
        GPIO_resetBitValue(gpio, pin);
    }
    else
    {
        GPIO_setBitValue(gpio, pin);
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        2020/10/26
 * \brief       configure work mode of target GPIO bit
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \param[in]   mode: expected work mode
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_configMode(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin, GPIO_mode mode)
{
    uint8_t m0 = 0x00;     /* store mode bits */
    uint8_t m1 = 0x00;

    /**
     * \note obtain mode bit
     */
    m0 = (TESTB(mode, 0)?pin:(~pin)) & pin;
    m1 = (TESTB(mode, 1)?pin:(~pin)) & pin;

    switch (gpio)
    {
        /* P0 */
        case PERIPH_GPIO_0:
        {
            P0M0 = P0M0 & (~pin) | m0;
            P0M1 = P0M1 & (~pin) | m1;
        } break;
        /* P1 */
        case PERIPH_GPIO_1:
        {
            P1M0 = P1M0 & (~pin) | m0;
            P1M1 = P1M1 & (~pin) | m1;
        } break;
        /* P2 */
        case PERIPH_GPIO_2:
        {
            P2M0 = P2M0 & (~pin) | m0;
            P2M1 = P2M1 & (~pin) | m1;
        } break;
        /* P3 */
        case PERIPH_GPIO_3:
        {
            P3M0 = P3M0 & (~pin) | m0;
            P3M1 = P3M1 & (~pin) | m1;
        } break;
        /* P4 */
        case PERIPH_GPIO_4:
        {
            P4M0 = P4M0 & (~pin) | m0;
            P4M1 = P4M1 & (~pin) | m1;
        } break;
        /* default */
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure value specified GPIO port
 * \param[in]   gpio: target GPIO port
 * \param[in]   val : expected value(0x00~0xFF)
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_configPortValue(PERIPH_GPIO gpio, uint8_t val)
{
    switch (gpio)
    {
        case PERIPH_GPIO_0: P0 = val; break;
        case PERIPH_GPIO_1: P1 = val; break;
        case PERIPH_GPIO_2: P2 = val; break;
        case PERIPH_GPIO_3: P3 = val; break;
        case PERIPH_GPIO_4: P4 = val; break;
        default: break;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get state of target GPIO pin
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \return      SET or RESET
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
FunctionalState GPIO_getBitValue(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin)
{
    switch (gpio)
    {
        case PERIPH_GPIO_0: return GET_BIT(P0, pin); break;
        case PERIPH_GPIO_1: return GET_BIT(P1, pin); break;
        case PERIPH_GPIO_2: return GET_BIT(P2, pin); break;
        case PERIPH_GPIO_3: return GET_BIT(P3, pin); break;
        case PERIPH_GPIO_4: return GET_BIT(P4, pin); break;
        default: break;
    }

    return RESET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get value of target GPIO port
 * \param[in]   gpio: target GPIO port
 * \return      current value of target GPIO port
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
uint8_t GPIO_getPortValue(PERIPH_GPIO gpio)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0: return P0; break;
        case PERIPH_GPIO_1: return P1; break;
        case PERIPH_GPIO_2: return P2; break;
        case PERIPH_GPIO_3: return P3; break;
        case PERIPH_GPIO_4: return P4; break;
        default: return 0x00;
    }
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       reset target GPIO pin
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_resetBitValue(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin)
{
    switch (gpio)
    {
        case PERIPH_GPIO_0: CLR_BIT_MASK(P0, pin); break;
        case PERIPH_GPIO_1: CLR_BIT_MASK(P1, pin); break;
        case PERIPH_GPIO_2: CLR_BIT_MASK(P2, pin); break;
        case PERIPH_GPIO_3: CLR_BIT_MASK(P3, pin); break;
        case PERIPH_GPIO_4: CLR_BIT_MASK(P4, pin); break;
        default: break;
    }
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       set target GPIO pin
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_setBitValue(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin)
{
    switch (gpio)
    {
        case PERIPH_GPIO_0: SET_BIT_MASK(P0, pin); break;
        case PERIPH_GPIO_1: SET_BIT_MASK(P1, pin); break;
        case PERIPH_GPIO_2: SET_BIT_MASK(P2, pin); break;
        case PERIPH_GPIO_3: SET_BIT_MASK(P3, pin); break;
        case PERIPH_GPIO_4: SET_BIT_MASK(P4, pin); break;
        default: break;
    }
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       toggle state of target GPIO pin
 * \param[in]   gpio: target GPIO port
 * \param[in]   pin : target GPIO pin
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_toggleBitValue(PERIPH_GPIO gpio, PERIPH_GPIO_PIN pin)
{
    switch (gpio)
    {
        case PERIPH_GPIO_0: NOT_BIT_MASK(P0, pin); break;
        case PERIPH_GPIO_1: NOT_BIT_MASK(P1, pin); break;
        case PERIPH_GPIO_2: NOT_BIT_MASK(P2, pin); break;
        case PERIPH_GPIO_3: NOT_BIT_MASK(P3, pin); break;
        case PERIPH_GPIO_4: NOT_BIT_MASK(P4, pin); break;
        default: break;
    }
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable GPIO function of pin P44
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_P44_cmd(Action a)
{
    CONFB(P4SW, BIT_NUM_NA_P44, a);
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable GPIO function of pin P45
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_P45_cmd(Action a)
{
    CONFB(P4SW, BIT_NUM_ALE_P45, a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable GPIO function of pin P46
 * \param[in]   a: expected action
 * \return      none
 * \ingroup     GPIO
 * \remarks     
******************************************************************************/
void GPIO_P46_cmd(Action a)
{
    /**
     *\note It seems to exist hardware bug about P46! Even if set special 
     *      function bit of P46, it can't work as well. The function can't
     *      work all the time ...
     *      If you know  what cause it, please send E-mail to us!
     */
    CONFB(P4SW, BIT_NUM_NA_P46, a);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
