/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:
 * #contains definitions that allow you to directly access the different memory areas of the 8051.
 * #have the similar functions like <absacc.h> in Keil
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#include "mem.h"

#ifdef ___COMPILE_MEM___

/*
 * @Prototype:void MEM_BUS_setAccessCycleLength(MEM_BUS_accessCycleLength len)
 * @Parameter:(1)len: expected length
 * @Ret-val:None
 * @Note:configure the MOVX read/write pulse
 */
void MEM_BUS_setAccessCycleLength(MEM_BUS_accessCycleLength len)
{
    BUS_SPEED = (BUS_SPEED & 0xF7) | len;
}

/*
 * @Prototype:void MEM_BUS_setAddressSetupTimeLength(MEM_BUS_addressSetupTimeLength len)
 * @Parameter:(1)len: expected length
 * @Ret-val:None
 * @Note:configure setup time and hold time of the P0 address until negative edge on pin ALE
 */
void MEM_BUS_setAddressSetupTimeLength(MEM_BUS_addressSetupTimeLength len)
{
    BUS_SPEED = (BUS_SPEED & 0xCF) | (len << 0x4);
}

/*
 * @Prototype:void MEM_cmd_ale(Action a)
 * @Parameter:(1)a:expected state
 * @Ret-val:None
 * @Note:enable or disable ALE pin
 */
void MEM_cmd_ale(Action a)
{
    CONFB(P4SW,BIT_NUM_NA_P45,~a);
}

/*
 * @Prototype:void MEM_cmd_internalExtendedRam(Action a)
 * @Parameter:(1)a:expected state
 * @Ret-val:
 * @Note:enable or disable internal extended RAM access
 *  > there is a RAM area integrated insides STC90 MCUs and it's independent in physics
 *  > if you enable this function,this area will occupy address zone in the beginning(RD+ series is 0000H~03FFH(1024 bytes),RC series is 0000H~00FFH(256 bytes));or this RAM area is hide,the MCU is as same as classical 8051 MCU now
 *  > if you want to enable this function,please remember select the option in STC-ISP
 */
void MEM_cmd_internalExtendedRam(Action a)
{
    CONFB(AUXR,BIT_NUM_EXTRAM,~a);
}

#endif

