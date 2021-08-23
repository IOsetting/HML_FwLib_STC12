/*****************************************************************************/
/** 
 * \file        util.c
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       public interface
 * \note        
 * \version     v0.0
 * \ingroup     UTIL
******************************************************************************/

#include "hml/util.h"

#ifdef COMPILE_UTIL

uint8_t df = 0x1;       /* mark current divided factor */


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       globaly enable or disable MCU interrupts
 * \param[in]   a: expected stat
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void UTIL_setInterrupts(Action a)
{
    EA = a;
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
uint16_t pow(uint8_t x, uint8_t y)
{
    uint8_t base = x;

    if (y == 0)
    {
        return 1;
    }
    else
    {
        while (--y)
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
 * \brief       set division factor of system clock
 * \param[in]   d: division factor
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void UTIL_setClockDivisionFactor(RCC_prescaler d)
{
    CLK_DIV = (uint8_t)d;
    df = pow(2, d);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       get current system clock frequency
 * \param[in]   
 * \return      current system clock frequency
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
uint32_t UTIL_getSystemClockFrequency(void)
{
    return (MCU_FRE_CLK/df);
}

/*****************************************************************************/
/**
 * \author      IOsetting
 * \date        2021/08/14
 * \brief       get _sleep_1ms initial value of 1T mode
 * \param[in]   none
 * \return      none
 * \ingroup     UTIL
 * \remarks     private function, don' use it
 *              5:DJNZ cycles, 18:adjust for extra cycles
******************************************************************************/
static uint16_t _sleep_getInitValue(void)
{
    return (uint16_t)(MCU_FRE_CLK/(float)1000/5) - 18;
}

/*****************************************************************************/
/**
 * \author      IOsetting
 * \date        2021/08/14
 * \brief       sleep 1 ms
 * \param[in]   none
 * \return      none
 * \ingroup     UTIL
 * \remarks     private function. 
 *              total loops = (ar7 * 256) + ar6, each DJNZ takes 5 CPU cycles
******************************************************************************/
static void _sleep_1ms(void)
{
    __asm
        push ar6                    ;low
        push ar7                    ;high
        inc  ar7
    delay1ms_loop$:
        djnz ar6,delay1ms_loop$
        djnz ar7,delay1ms_loop$
        pop ar7
        pop ar6
        ret
    __endasm;
}

/*****************************************************************************/
/**
 * \author      Jiabin Hsu
 * \date        2020/10/30
 * \brief       software delay according to MCU clock frequency
 * \param[in]   t: how many one ms you want to delay
 * \return      none
 * \ingroup     UTIL
 * \remarks     
******************************************************************************/
void sleep(uint16_t t)
{
    __asm
        push ar5
        push ar6
        push ar7

        push dph
        push dpl

    ; freq -> r6,r7
        lcall __sleep_getInitValue
        mov ar6,dpl
        mov ar7,dph

    ; t -> dptr
        pop dpl
        pop dph

    ; 0xFFFF - t
        clr c
        mov a,#0xFF
        subb a,dpl
        mov dpl,a
        mov a,#0xFF
        subb a,dph
        mov dph,a

    ; return if time equals 0
        mov a,dpl
        anl a,dph
        cpl a
        jz ENDL$

    ; loop for sleep
    ; loop from (0xFFFF - t) to (0xFFFF)
    LOOP$:
        lcall __sleep_1ms               ;#5*(ar7*(256 + 1) + ar6)
        inc dptr                        ;#2
        mov a,dpl                       ;#1
        anl a,dph                       ;#1
        cpl a                           ;#1
        jnz LOOP$                       ;#2
    ENDL$:
        pop ar7
        pop ar6
        pop ar5
        ret
    __endasm;

    /**
     * \note disable SDCC warning
     */
    t = 0;
}

void UTIL_enablePrintf(void)
{
    // configure serial for 9600 baud, 8 data bits, 1 stop bit.
    TMOD = 0x21;
    SCON = 0x40;
    TH1 = 0xFD;   // TH1 = 256 - 11.0592 * 1000 * 1000 / 12 / 32 / 9600;
    TCON |= 0x40; // start TIM1
    SCON |= 0x02;
}

int putchar (int c) {
    while (!TI);    /* assumes UART is initialized */ 
    TI = 0;
    SBUF = c;
    return (c);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
