/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operations for GPIO resource
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */
 
#include "gpio.h"

#ifdef ___COMPILE_GPIO___

/*
 * @Prototype:void GPIO_config(PERIPH_GPIO gpio,GPIO_configTypeDef *gc)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)gc:pointer of configure structure
 * @Ret-val:
 * @Note:configure specified GPIO
 */
void GPIO_config(PERIPH_GPIO gpio,GPIO_configTypeDef *gc)
{
    GPIO_configMode(gpio,gc->pin,gc->mode);
    GPIO_configPortValue(gpio,gc->value);
}

/*
 * @Prototype:void GPIO_configBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin,FunctionalState f)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target GPIO pin
 *  (3)f:expected level state
 * @Ret-val:
 * @Note:configure specified pin as expected state
 */
void GPIO_configBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin,FunctionalState f)
{
    if(f == RESET)
    {
        GPIO_resetBitValue(gpio,pin);
    }
    else
    {
        GPIO_setBitValue(gpio,pin);
    }
}

/*
 * @Prototype:void GPIO_configMode(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin,GPIO_mode mode)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target GPIO pin
 *  (3)mode:expected mode
 * @Ret-val:
 * @Note:configure mode of specified GPIO
 */
void GPIO_configMode(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin,GPIO_mode mode)
{
    switch(mode)
    {
        /* high-impedance state mode */
        case GPIO_mode_HIS:
        {
            switch(gpio)
            {
                /* P0 */
                case PERIPH_GPIO_0:
                {
                    P0M0 = P0M0 & (~pin);
                    P0M1 = P0M1 | pin;
                } break;
                /* P1 */
                case PERIPH_GPIO_1:
                {
                    P1M0 = P1M0 & (~pin);
                    P1M1 = P1M1 | pin;
                } break;
                /* P2 */
                case PERIPH_GPIO_2:
                {
                    P2M0 = P2M0 & (~pin);
                    P2M1 = P2M1 | pin;
                } break;
                /* P3 */
                case PERIPH_GPIO_3:
                {
                    P3M0 = P3M0 & (~pin);
                    P3M1 = P3M1 | pin;
                } break;
                /* P4 */
                case PERIPH_GPIO_4:
                {
                    P4M0 = P4M0 & (~pin);
                    P4M1 = P4M1 | pin;
                } break;
                /* default */
                default: break;
            }
        } break;

        /* open-drain state */
        case GPIO_mode_OD:
        {
            switch(gpio)
            {
                /* P0 */
                case PERIPH_GPIO_0:
                {
                    P0M0 = P0M0 | pin;
                    P0M1 = P0M1 | pin;
                } break;
                /* P1 */
                case PERIPH_GPIO_1:
                {
                    P1M0 = P1M0 | pin;
                    P1M1 = P1M1 | pin;
                } break;
                /* P2 */
                case PERIPH_GPIO_2:
                {
                    P2M0 = P2M0 | pin;
                    P2M1 = P2M1 | pin;
                } break;
                /* P3 */
                case PERIPH_GPIO_3:
                {
                    P3M0 = P3M0 | pin;
                    P3M1 = P3M1 | pin;
                } break;
                /* P4 */
                case PERIPH_GPIO_4:
                {
                    P4M0 = P4M0 | pin;
                    P4M1 = P4M1 | pin;
                } break;
                /* default */
                default: break;
            }
        } break;

        /* pull-push output mode */
        case GPIO_mode_PP:
        {
            switch(gpio)
            {
                /* P0 */
                case PERIPH_GPIO_0:
                {
                    P0M0 = P0M0 | pin;
                    P0M1 = P0M1 & (~pin);
                } break;
                /* P1 */
                case PERIPH_GPIO_1:
                {
                    P1M0 = P1M0 | pin;
                    P1M1 = P1M1 & (~pin);
                } break;
                /* P2 */
                case PERIPH_GPIO_2:
                {
                    P2M0 = P2M0 | pin;
                    P2M1 = P2M1 & (~pin);
                } break;
                /* P3 */
                case PERIPH_GPIO_3:
                {
                    P3M0 = P3M0 | pin;
                    P3M1 = P3M1 & (~pin);
                } break;
                /* P4 */
                case PERIPH_GPIO_4:
                {
                    P4M0 = P4M0 | pin;
                    P4M1 = P4M1 & (~pin);
                } break;
                /* default */
                default: break;
            }
        } break;

        /* quai-bidirectional mode */
        case GPIO_mode_QBD:
        {
            switch(gpio)
            {
                /* P0 */
                case PERIPH_GPIO_0:
                {
                    P0M0 = P0M0 & (~pin);
                    P0M1 = P0M1 & (~pin);
                } break;
                /* P1 */
                case PERIPH_GPIO_1:
                {
                    P1M0 = P1M0 & (~pin);
                    P1M1 = P1M1 & (~pin);
                } break;
                /* P2 */
                case PERIPH_GPIO_2:
                {
                    P2M0 = P2M0 & (~pin);
                    P2M1 = P2M1 & (~pin);
                } break;
                /* P3 */
                case PERIPH_GPIO_3:
                {
                    P3M0 = P3M0 & (~pin);
                    P3M1 = P3M1 & (~pin);
                } break;
                /* P4 */
                case PERIPH_GPIO_4:
                {
                    P4M0 = P4M0 & (~pin);
                    P4M1 = P4M1 & (~pin);
                } break;
                /* default */
                default: break;
            }
        } break;

        default:break;
    }
}

/*
 * @Prototype:void GPIO_configPortValue(PERIPH_GPIO gpio,byte val)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)val:expected port value
 * @Ret-val:
 * @Note:configure port value
 */
void GPIO_configPortValue(PERIPH_GPIO gpio,byte val)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:P0 = val;break;
        case PERIPH_GPIO_1:P1 = val;break;
        case PERIPH_GPIO_2:P2 = val;break;
        case PERIPH_GPIO_3:P3 = val;break;
        case PERIPH_GPIO_4:P4 = val;break;
        default:break;
    }
}

/*
 * @Prototype:void GPIO_getBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target pin
 * @Ret-val:
 * @Note:get value of target pin
 */
FunctionalState GPIO_getBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:return GET_BIT(P0,pin);break;
        case PERIPH_GPIO_1:return GET_BIT(P1,pin);break;
        case PERIPH_GPIO_2:return GET_BIT(P2,pin);break;
        case PERIPH_GPIO_3:return GET_BIT(P3,pin);break;
        case PERIPH_GPIO_4:return GET_BIT(P4,pin);break;
        default:break;
    }

    return RESET;
}

/*
 * @Prototype:unsigned char GPIO_getPortValue(PERIPH_GPIO gpio)
 * @Parameter:
 *  (1)gpio:target GPIO port
 * @Ret-val:
 * @Note:get value of target port
 */
unsigned char GPIO_getPortValue(PERIPH_GPIO gpio)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:return P0;break;
        case PERIPH_GPIO_1:return P1;break;
        case PERIPH_GPIO_2:return P2;break;
        case PERIPH_GPIO_3:return P3;break;
        case PERIPH_GPIO_4:return P4;break;
        default:return 0x00;
    }
}

/*
 * @Prototype:void GPIO_resetBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target pin
 * @Ret-val:
 * @Note:reset value of target pin
 */
void GPIO_resetBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:CLR_BIT_MASK(P0,pin);break;
        case PERIPH_GPIO_1:CLR_BIT_MASK(P1,pin);break;
        case PERIPH_GPIO_2:CLR_BIT_MASK(P2,pin);break;
        case PERIPH_GPIO_3:CLR_BIT_MASK(P3,pin);break;
        case PERIPH_GPIO_4:CLR_BIT_MASK(P4,pin);break;
        default:break;
    }
}

/*
 * @Prototype:void GPIO_setBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target pin
 * @Ret-val:
 * @Note:set value of target pin
 */
void GPIO_setBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:SET_BIT_MASK(P0,pin);break;
        case PERIPH_GPIO_1:SET_BIT_MASK(P1,pin);break;
        case PERIPH_GPIO_2:SET_BIT_MASK(P2,pin);break;
        case PERIPH_GPIO_3:SET_BIT_MASK(P3,pin);break;
        case PERIPH_GPIO_4:SET_BIT_MASK(P4,pin);break;
        default:break;
    }
}

/*
 * @Prototype:void GPIO_toggleBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
 * @Parameter:
 *  (1)gpio:target GPIO port
 *  (2)pin:target pin
 * @Ret-val:
 * @Note:change value of target pin into opposite state
 */
void GPIO_toggleBitValue(PERIPH_GPIO gpio,PERIPH_GPIO_PIN pin)
{
    switch(gpio)
    {
        case PERIPH_GPIO_0:NOT_BIT_MASK(P0,pin);break;
        case PERIPH_GPIO_1:NOT_BIT_MASK(P1,pin);break;
        case PERIPH_GPIO_2:NOT_BIT_MASK(P2,pin);break;
        case PERIPH_GPIO_3:NOT_BIT_MASK(P3,pin);break;
        case PERIPH_GPIO_4:NOT_BIT_MASK(P4,pin);break;
        default:break;
    }
}

/*
 * @Prototype:void GPIO_P44_cmd(Action a)
 * @Parameter:(1)a:enable or disable
 * @Ret-val:
 * @Note:enable Pin-P44 as GPIO
 */
void GPIO_P44_cmd(Action a)
{
    CONFB(P4SW,BIT_NUM_NA_P44,a);
}

/*
 * @Prototype:void GPIO_P45_cmd(Action a)
 * @Parameter:(1)a:enable or disable
 * @Ret-val:
 * @Note:enable Pin-P45 as GPIO
 */
void GPIO_P45_cmd(Action a)
{
    CONFB(P4SW,BIT_NUM_NA_P45,a);
}

/*
 * @Prototype:void GPIO_P46_cmd(Action a)
 * @Parameter:(1)a:enable or disable
 * @Ret-val:
 * @Note:enable Pin-P46 as GPIO
 */
void GPIO_P46_cmd(Action a)
{
    /*
     * @Attention: It seems to exist hardware bug about P46! Even if set special function bit of P46, it can't work as well. The function can't work all the time...
     *             If you know  what cause it, please send E-mail to us!
     */
    
    CONFB(P4SW,BIT_NUM_NA_P46,a);
}

#endif
