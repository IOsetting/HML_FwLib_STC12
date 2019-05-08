/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:operations of IAP resource
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */
 
#include "iap.h"

#ifdef ___COMPILE_IAP___

/*
 * @Prototype:void IAP_cmd(Action a)
 * @Parameter:(1)a:expected action
 * @Ret-val:
 * @Note:launch or stop IAP/ISP module
 */
void IAP_cmd(Action a)
{
    CONFB(IAP_CONTR,BIT_NUM_IAPEN,a);
}

/*
 * @Prototype:bool IAP_eraseByte(unsigned int addr)
 * @Parameter:(1)addr:operating address
 * @Ret-val:
 * @Note:clear the value of the register in the specified address
 */
bool IAP_eraseByte(unsigned int addr)
{
    bool status = false;

    if(IAP_ADDR_END < addr)
    {
        return false;
    }

    IAP_cmd(ENABLE);
    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_erase);
    IAP_trig();
    sleep(1);
    IAP_idle();
    status = IAP_isSuccess();

    return status;
}

/*
 * @Prototype:void IAP_idle(void)
 * @Parameter:
 * @Ret-val:
 * @Note:Let IAP be idle
 */
void IAP_idle(void)
{
    IAP_cmd(DISABLE);
    IAP_setAddress(0x0000);
    IAP_setCommand(IAP_command_idle);
}

/*
 *@Prototype:bool IAP_isSuccess(void)
 *@Parameter:
 *@Ret-val:IAP trigger status
 *@Note:if succeed in triggering,the function will return true,or it will return false
 */
bool IAP_isSuccess(void)
{
    if(GET_BIT(IAP_CONTR,CMD_FAIL))
    {
        CLR_BIT_MASK(IAP_CONTR,CMD_FAIL);
        return false;
    }
    else
    {
        return true;
    }
}

/*
 * @Prototype:byte IAP_readByte(unsigned int addr)
 * @Parameter:(1)addr:operating address
 * @Ret-val:byte
 * @Note:read the value of the register in the specified address
 */
byte IAP_readByte(unsigned int addr)
{
    byte dat = 0x00;
    
    IAP_cmd(ENABLE);
    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_read);
    IAP_trig();
    _nop_();
    dat = IAP_DATA;
    IAP_idle();
    
    return dat;
}

/*
 * @Prototype:void IAP_setAddress(unsigned int addr)
 * @Parameter:(1)addr:operating address
 * @Ret-val:
 * @Note:setting the address to be operated
 */
void IAP_setAddress(unsigned int addr)
{
    IAP_ADDRL = addr;
    IAP_ADDRH = addr >> 0x8;
}

/*
 * @Prototype:void IAP_setCommand(IAP_command cmd)
 * @Parameter:(1)cmd:set current command
 * @Ret-val:
 * @Note:set command
 */
void IAP_setCommand(IAP_command cmd)
{
    IAP_CMD = cmd;
}

/*
 * @Prototype:void IAP_trig(void)
 * @Parameter:
 * @Ret-val:
 * @Note:Trigger instruction
 */
void IAP_trig(void)
{
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
}

/*
 * @Prototype:void IAP_writeByte(unsigned int addr,byte dat)
 * @Parameter:
 *  (1)addr:operating address
 *  (2)dat:target data
 * @Ret-val:
 * @Note:write the value into the register in the specified address
 */
bool IAP_writeByte(unsigned int addr,byte dat)
{
    bool status = false;
    
    if(IAP_ADDR_END < addr)
    {
        return false;
    }

    IAP_cmd(ENABLE);
    IAP_setAddress(addr);
    IAP_setCommand(IAP_command_write);
    IAP_DATA = dat;
    IAP_trig();
    _nop_();
    IAP_idle();
    status = IAP_isSuccess();

    return status;
}

#endif
