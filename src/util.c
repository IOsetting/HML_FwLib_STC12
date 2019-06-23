/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:provides some public functions
 * @Required-complier:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#include "util.h"

#ifdef ___COMPILE_UTIL___

/*
 * @Prototype:void disableAllInterrupts(void)
 * @Parameter:
 * @Ret-val:
 * @Note:disable all interrupts
 */
void disableAllInterrupts(void)
{
    EA = RESET;
}

/*
 * @Prototype:void enableAllInterrupts(void)
 * @Parameter:
 * @Ret-val:
 * @Note:enable total switch of interrupts
 */
void enableAllInterrupts(void)
{
    EA = SET;
}

/*
 * @Prototype:unsigned int pow(unsigned char x,unsigned char y)
 * @Parameter:(1)x:base;(2)y:power exponent
 * @Ret-val:result
 * @Note:
 *  (1)calculate result of x^y, data type of return value is unsigned int because of limited zone of 8051 MCU
 *  (2)due to SDCC doesn't provide this function, we write a lite version here.
 */
unsigned int pow(unsigned char x,unsigned char y)
{
    u8 base = x;
    
    if(y == 0)
    {
        return 1;
    }
    else
    {
        while(--y)
        {
            x = x*base;
        }
    }
    
    return x;
}

/*
 * @Prototype:void sleep(u16 t)
 * @Parameter:(1)how many ms users expected
 * @Ret-val:
 * @Note:software delay according to frequency of crystal oscillator
 */
void sleep(u16 t)
{
    u8 i = 0x00;
    u8 j = 0x00;
    
    #if ( _FRE_OSC_ == 11059200L )

        while(t--)
        {
            NOP();
            i = 5;
            j = 70;
            do
            {
                while (--j);
            } while (--i);
        }
        
    #elif ( _FRE_OSC_ == 12000000L )

        while(t--)
        {
            NOP();
            NOP();
            i =5;
            j = 100;
            do
            {
                while (--j);
            } while (--i);
        }
        
    #else
        
    //TODO
    
    #endif
}

#endif

