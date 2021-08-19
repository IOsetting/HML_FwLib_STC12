/*****************************************************************************/
/** 
 * \file        mem.c
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       operations for memory zone of MCU
 * \note        allow you to directly access the different memory areas of STC12
 *              series MCU
 * \version     v0.0
 * \ingroup     MEM
******************************************************************************/

#include "hml/mem.h"

#ifdef COMPILE_MEM

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure the MOVX read/write pulse
 * \param[in]   len: expected time length
 * \return      none
 * \ingroup     MEM
 * \remarks     
******************************************************************************/
void MEM_BUS_setAccessCycleLength(MEM_BUS_accessCycleLength len)
{
    BUS_SPEED = (BUS_SPEED & 0xF7) | len;
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       configure P0 address setup time and hold time to ALE negative edge
 * \param[in]   len: expected time length
 * \return      none
 * \ingroup     MEM
 * \remarks     configure P0 address setup time and hold time to ALE negative edge
******************************************************************************/
void MEM_BUS_setAddressSetupTimeLength(MEM_BUS_addressSetupTimeLength len)
{
    BUS_SPEED = (BUS_SPEED & 0xCF) | (len << 0x4);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable pin P4.5 working as ALE signal for Intel 8080 Bus
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     MEM
 * \remarks     DISABLE: P45 as GPIO
 *              ENABLE:  P45 as ALE, active only in MOVX or MOVC instruction
******************************************************************************/
void MEM_setP45ALE(Action a)
{
    CONFB(P4SW, BIT_NUM_ALE_P45, ~a);
}

/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable the 1k-byte additional onchip RAM
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     MEM
 * \remarks     STC12 can address a range of 64K-byte(0x0000~0xFFFF) and there are 
 *              1k-byte additional data RAM on STC12. EXTRAM is to control the 
 *              access of this additional RAM 
 *              -- When set, disable the additional RAM.  
 *              -- When clear (EXTRAM=0), this additional RAM is in address 
 *               [0x0000, 0x03FF], can be accessed by “MOVX @Ri” and “MOVX @DPTR”,
 *               and address over 0x03FF is for external RAM.
******************************************************************************/
void MEM_setOnchipExtendedRam(Action a)
{
    CONFB(AUXR, BIT_NUM_EXTRAM, ~a);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
