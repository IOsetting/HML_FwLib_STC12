/*****************************************************************************/
/** 
 * \file        util.c
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       public interface
 * \note        
 * \version     v0.0
 * \ingroup     UTIL
******************************************************************************/

#include "util.h"

#ifdef __CONF_COMPILE_UTIL

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       disable master switch of MCU interrupt
 * \param[in]   
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void disableAllInterrupts(void)
{
    EA = RESET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable master switch of MCU interrupt
 * \param[in]   
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void enableAllInterrupts(void)
{
    EA = SET;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       self-define pow function
 * \param[in]   x: base
 * \param[in]   y: power exponent
 * \return      calculate result
 * \ingroup     UTIL
 * \remarks     (1)calculate result of x^y, data type of return value is 
 *              unsigned int because of limited zone of 8051 MCU
 *              (2)due to SDCC doesn't provide this function, we write a lite 
 *              version here
******************************************************************************/
unsigned int pow(unsigned char x,unsigned char y)
{
    u8 base = x;

    if (y == 0)
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

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       software delay according to MCU clock frequency
 * \param[in]   t: how many one ms you want to delay
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void sleep(u16 t)
{
    u8 i = 0x00;
    u8 j = 0x00;

    #if ( MCU_FRE_CLK == 11059200L )

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
        
    #elif ( MCU_FRE_CLK == 12000000L )

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

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
