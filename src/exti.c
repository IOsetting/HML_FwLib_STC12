/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operate on-chip EXTI module
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#include "exti.h"

#ifdef ___COMPILE_EXTI___

/*
 * @Prototype:void EXTI_config(PERIPH_EXTI exti,EXTI_configTypeDef ec)
 * @Parameter:
 *  (1)exti:target EXTI module
 *  (2)ec:the pointer of configuration structure which includes all configuration information
 * @Note:configure EXTI module
 */
void EXTI_config(PERIPH_EXTI exti,EXTI_configTypeDef *ec)
{
    EXTI_setMode(exti,ec->mode);
    EXTI_setPriority(exti,ec->priority);
}

/*
 * @Prototype:void EXTI_cmd(PERIPH_EXTI exti,Action a)
 * @Parameter:
 *  (1)exti:target EXTI module
 *  (2)a:expected status
 * @Note:enable or disable EXTI module
 */
void EXTI_cmd(PERIPH_EXTI exti,Action a)
{
    switch(exti)
    {
        case PERIPH_EXTI_0:EX0 = a;break;
        case PERIPH_EXTI_1:EX1 = a;break;
        default:break;
    }
}

/*
 * @Prototype:void EXTI_setMode(PERIPH_EXTI exti,EXTI_mode mod)
 * @Parameter:
 *  (1)exti:target EXTI module
 *  (2)mod:expected work mode
 * @Note:set work mode EXTI module
 */
void EXTI_setMode(PERIPH_EXTI exti,EXTI_mode mod)
{
    switch(exti)
    {
        case PERIPH_EXTI_0:IT0 = mod;break;
        case PERIPH_EXTI_1:IT1 = mod;break;
        default:break;
    }
}

/*
 * @Prototype:void EXTI_setPriority(PERIPH_EXTI exti,Action a)
 * @Parameter:
 *  (1)exti:target EXTI module
 *  (2)a:expected status
 * @Note:set priority of EXTI module
 */
void EXTI_setPriority(PERIPH_EXTI exti,Action a)
{
    switch(exti)
    {
        case PERIPH_EXTI_0:PX0 = a;break;
        case PERIPH_EXTI_1:PX1 = a;break;
        default:break;
    }
}

#endif

