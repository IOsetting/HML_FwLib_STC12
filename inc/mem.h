/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:
 * #define macro that allow you to directly access the different memory areas of the 8051.
 * #include the similar functions like <absacc.h> in Keil
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___MEM_H___
#define ___MEM_H___

/* ----- @header file ----- */
#include "stc11.h"
#include "macro.h"

/* ----- @macro ----- */
#define __CBYTE ((unsigned char volatile __code  *) 0)
#define __DBYTE ((unsigned char volatile __data  *) 0)
#define __PBYTE ((unsigned char volatile __pdata *) 0)
#define __XBYTE ((unsigned char volatile __xdata *) 0)

#define __CWORD ((unsigned int volatile __code  *) 0)
#define __DWORD ((unsigned int volatile __data  *) 0)
#define __PWORD ((unsigned int volatile __pdata *) 0)
#define __XWORD ((unsigned int volatile __xdata *) 0)

/* ----- @enumeration type ----- */
/* mark read/write pulse length */
typedef enum
{
    MEM_BUS_accessCycleLength_1T      = 0x00,         /* the MOVX read/write pulse is one clock cycle */
    MEM_BUS_accessCycleLength_2T      = 0x01,
    MEM_BUS_accessCycleLength_3T      = 0x02,
    MEM_BUS_accessCycleLength_4T      = 0x03,
    MEM_BUS_accessCycleLength_5T      = 0x04,
    MEM_BUS_accessCycleLength_6T      = 0x05,
    MEM_BUS_accessCycleLength_7T      = 0x06,
    MEM_BUS_accessCycleLength_8T      = 0x07,
    MEM_BUS_accessCycleLength_default = 0x03          /* default value is four clock cycles */
} MEM_BUS_accessCycleLength;

/* mark bus stable time */
typedef enum
{
    MEM_BUS_addressSetupTimeLength_1T      = 0x00,    /* one clock cycle */
    MEM_BUS_addressSetupTimeLength_2T      = 0x01,
    MEM_BUS_addressSetupTimeLength_3T      = 0x02,
    MEM_BUS_addressSetupTimeLength_4T      = 0x03,
    MEM_BUS_addressSetupTimeLength_default = 0x02     /* default value is three clock cycles */
} MEM_BUS_addressSetupTimeLength;

/* ----- @function ----- */
void MEM_BUS_setAccessCycleLength(MEM_BUS_accessCycleLength len);
void MEM_BUS_setAddressSetupTimeLength(MEM_BUS_addressSetupTimeLength len);
void MEM_cmd_ale(Action a);
void MEM_cmd_internalExtendedRam(Action a);

#endif
