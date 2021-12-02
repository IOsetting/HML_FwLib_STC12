/*****************************************************************************/
/** 
 * \file        ds12c887.h
 * \author      IOsetting | iosetting@outlook.com
 * \brief       
 * \note        
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

#ifndef ___HML_DS12C887_H___
#define ___HML_DS12C887_H___

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "hml/hml.h"

/*****************************************************************************
 *                                macro                                      *
 *****************************************************************************/
#define DS12C88X_DS  P1_0
#define DS12C88X_RW  P1_1
#define DS12C88X_AS  P1_2
#define DS12C88X_CS  P1_3
#define DS12C88X_IRQ P3_2
#define DS12C88X_PORT  P0

#define DS12C88X_REG_REGA     0x0a
#define DS12C88X_REG_REGB     0x0b
#define DS12C88X_REG_REGC     0x0c
#define DS12C88X_REG_SEC      0x00
#define DS12C88X_REG_ALM_SEC  0x01
#define DS12C88X_REG_MIN      0x02
#define DS12C88X_REG_ALM_MIN  0x03
#define DS12C88X_REG_HOUR     0x04
#define DS12C88X_REG_ALM_HOUR 0x05
#define DS12C88X_REG_WDAY     0x06
#define DS12C88X_REG_DATE     0x07
#define DS12C88X_REG_MONTH    0x08
#define DS12C88X_REG_YEAR     0x09
#define DS12C88X_REG_CENTURY  0x32

uint8_t DS12C88X_Read(uint8_t addr);
void    DS12C88X_Write(uint8_t addr, uint8_t w_data);
void    DS12C88X_ReloadTime(bool refresh);
void    DS12C88X_SetTime(uint8_t year, uint8_t month, uint8_t date, uint8_t week_day, uint8_t hour, uint8_t minute, uint8_t second);
void    DS12C88X_Init(void);
void    DS12C88X_Increase(uint8_t addr);
uint8_t DS12C88X_bcd2dec(uint8_t bcd);
uint8_t DS12C88X_dec2bcd(uint8_t dec);

#endif
