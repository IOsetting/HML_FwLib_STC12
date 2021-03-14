/*****************************************************************************/
/** 
 * \file        iap.c
 * \author      Jiabin Hsu | zsiothsu@zhishan-iot.tk
 * \brief       operations for IAP module
 * \note        
 * \version     v0.0
 * \ingroup     IAP
******************************************************************************/

#include "hml/iap.h"

#ifdef HAVE_IAP

#ifdef COMPILE_IAP

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        
 * \brief       enable or disable IAP module
 * \param[in]   a : expected action
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_cmd(Action a)
{
    CONFB(IAP_CONTR, BIT_NUM_IAPEN, a);
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       set the wait time of cpu after isp module is triggered
 * \param[in]   none
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_config(void)
{
    IAP_CONTR = (IAP_CONTR & 0xF8) | IAP_WAITTIME;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       erase all data of specified IAP area
 * \param[in]   addr: address of target area
 * \return      complete to erase(true) or failed to execute operation(false)
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
bool IAP_eraseSector(uint16_t addr)
{
    bool status = false;

    if (IAP_ADDR_END < addr)
    {
        return false;
    }

    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_erase);
    IAP_trig();
    status = IAP_isSuccess();

    return status;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       make IAP module be in idle mode
 * \param[in]   
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_idle(void)
{
    /* 0xFFFF point to non-eeprom area */
    IAP_setAddress(0xFFFF);
    IAP_setCommand(IAP_command_idle);
    IAP_DATA = 0xFF;
    IAP_TRIG = 0x00;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        
 * \brief       get result of IAP command execution
 * \param[in]   
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
bool IAP_isSuccess(void)
{
    if (GET_BIT(IAP_CONTR, CMD_FAIL))
    {
        CLR_BIT_MASK(IAP_CONTR, CMD_FAIL);
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       read value of specified area
 * \param[in]   addr: address of specified area
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
byte IAP_readByte(uint16_t addr)
{
    byte dat = 0x00;

    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_read);
    IAP_trig();
    dat = IAP_DATA;

    return dat;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        
 * \brief       set address register for acess target IAP area
 * \param[in]   addr: address of specified area
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_setAddress(uint16_t addr)
{
    IAP_ADDRL = addr;
    IAP_ADDRH = addr >> 0x8;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        
 * \brief       send IAP command to IAP module by writing IAP_CMD register
 * \param[in]   cmd: expected IAP command
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_setCommand(IAP_command cmd)
{
    IAP_CMD = cmd;
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       trigger instruction
 * \param[in]   
 * \return      none
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
void IAP_trig(void)
{
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
    NOP();  /* MCU will hold here until ISP operation */
}

/*****************************************************************************/
/** 
 * \author      Jiabin Hsu
 * \date        2021/03/13
 * \brief       write data to specified IAP area
 * \param[in]   addr: address of target IAP area
 * \param[in]   dat : one byte of data
 * \return      write successfully(true) or not(false)
 * \ingroup     IAP
 * \remarks     
******************************************************************************/
bool IAP_writeByte(uint16_t addr, byte dat)
{
    bool status = false;

    if (IAP_ADDR_END < addr)
    {
        return false;
    }

    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_write);
    IAP_DATA = dat;
    IAP_trig();
    status = IAP_isSuccess();

    return status;
}

#else
    #warning Nothing to be done... User should remove .c file which is disabled by compile control macro from current directory.
#endif

#endif
