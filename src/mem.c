/*****************************************************************************/
/** 
 * \file        mem.c
 * \author      Weillun Fong | wlf@zhishan-iot.tk
 * \brief       operations for memory zone of MCU
 * \note        allow you to directly access the different memory areas of STC11
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
 * \brief       enable or disable pin ALE for Intel 8080 Bus
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     MEM
 * \remarks     (1) disable ALE: as GPIO P45
 *              (2) enable ALE : ALE is active only during a MOVX or MOVC instruction
******************************************************************************/
void MEM_cmd_ale(Action a)
{
    CONFB(P4SW, BIT_NUM_ALE_P45, ~a);
}


/*****************************************************************************/
/** 
 * \author      Weilun Fong
 * \date        
 * \brief       enable or disable pin ALE for Intel 8080 Bus
 * \param[in]   a: expected state
 * \return      none
 * \ingroup     MEM
 * \remarks     there is 64K-byte(0x0000~0xFFFF) addressing space available for 
 *              STC11 series MCU to access external data RAM and it's independent
 *              in logic.
******************************************************************************/
void MEM_cmd_internalExtendedRam(Action a)
{
    CONFB(AUXR, BIT_NUM_EXTRAM, ~a);
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif
