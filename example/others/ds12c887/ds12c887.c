/*****************************************************************************/
/** 
 * \file        ds12c887.c
 * \author      IOsetting | iosetting@outlook.com
 * \brief       
 * \note        
 * \version     v0.1
 * \ingroup     example
******************************************************************************/

#include "ds12c887.h"

uint8_t ds12c88x_reg_a, ds12c88x_reg_b, ds12c88x_reg_c, 
        ds12c88x_alarm_hour, ds12c88x_alarm_minute, ds12c88x_alarm_second, 
        ds12c88x_centry, ds12c88x_year, ds12c88x_month, ds12c88x_date, ds12c88x_week_day, 
        ds12c88x_hour, ds12c88x_minute, ds12c88x_second;

void DS12C88X_Write(uint8_t addr, uint8_t w_data)
{
    DS12C88X_CS = 0;
    DS12C88X_AS = 1;
    DS12C88X_DS = 1;
    DS12C88X_RW = 1;
    DS12C88X_PORT = addr;
    DS12C88X_AS = 0;
    DS12C88X_RW = 0;
    DS12C88X_PORT = w_data;
    DS12C88X_RW = 1;
    DS12C88X_AS = 1;
    DS12C88X_CS = 1;
}

uint8_t DS12C88X_Read(uint8_t addr)
{
    uint8_t ds_date;
    DS12C88X_AS = 1;
    DS12C88X_DS = 1;
    DS12C88X_RW = 1;
    DS12C88X_CS = 0;
    DS12C88X_PORT = addr;
    DS12C88X_AS = 0;
    DS12C88X_DS = 0;
    /**
     * Set P0 to high impedance. This is the tricky part, if the mode remains quasi-bidirectional,
     * you need to set P0 = 0xFF in order to get output data, but this will also interfere with the output.
     * This is quite different from STC89.
     */
    GPIO_configPortMode(PERIPH_GPIO_0, GPIO_mode_HIS);
    ds_date = DS12C88X_PORT;
    DS12C88X_DS = 1;
    DS12C88X_AS = 1;
    DS12C88X_CS = 1;
    /** Restore P0 to default quasi-bidirectional */
    GPIO_configPortMode(PERIPH_GPIO_0, GPIO_mode_QBD);
    return ds_date;
}

void DS12C88X_ReloadTime(bool refresh)
{
    ds12c88x_reg_a  = DS12C88X_Read(DS12C88X_REG_REGA);
    ds12c88x_reg_b  = DS12C88X_Read(DS12C88X_REG_REGB);
    // Clear IRQ bit
    /**
     * 0C: IRQF PF AF UF  0  0  0  0
     * 
     * Interrupt Request Flag (IRQF). This bit is set to 1 when any of PF/AF/UF are true, 
     * Any time the IRQF bit is 1, the IRQ pin is driven low. This bit can be cleared by 
     * reading Register C or with a RESET.
     * 
     * Periodic Interrupt Flag (PF). This bit is read-only and is set to 1 when an edge 
     * is detected on the selected tap of the divider chain. The RS3 through RS0 bits 
     * establish the periodic rate. PF is set to 1 indepen-dent of the state of the PIE bit. 
     * When both PF and PIE are 1s, the IRQ signal is active and sets the IRQF bit. This bit 
     * can be cleared by reading Register C or with a RESET.
     * 
     * Alarm Interrupt Flag (AF). A 1 in the AF bit indi-cates that the current time has 
     * matched the alarm time. If the AIE bit is also 1, the IRQ pin goes low and a 1 appears 
     * in the IRQF bit. This bit can be cleared by reading Register C or with a RESET.
     * 
     * Update-Ended Interrupt Flag (UF). This bit is set after each update cycle. When the 
     * UIE bit is set to 1, the 1 in UF causes the IRQF bit to be a 1, which asserts the IRQ 
     * pin. This bit can be cleared by reading Register C or with a RESET.
     */
    ds12c88x_reg_c  = DS12C88X_Read(DS12C88X_REG_REGC);

    ds12c88x_second   = DS12C88X_Read(DS12C88X_REG_SEC);
    if (refresh && ds12c88x_second != 0x00) return;

    ds12c88x_minute   = DS12C88X_Read(DS12C88X_REG_MIN);
    if (refresh && ds12c88x_minute != 0x00) return;

    ds12c88x_alarm_second = DS12C88X_Read(DS12C88X_REG_ALM_SEC);
    ds12c88x_alarm_minute = DS12C88X_Read(DS12C88X_REG_ALM_MIN);
    ds12c88x_alarm_hour   = DS12C88X_Read(DS12C88X_REG_ALM_HOUR);
    ds12c88x_hour     = DS12C88X_Read(DS12C88X_REG_HOUR);
    ds12c88x_week_day = DS12C88X_Read(DS12C88X_REG_WDAY);
    ds12c88x_date     = DS12C88X_Read(DS12C88X_REG_DATE);
    ds12c88x_month    = DS12C88X_Read(DS12C88X_REG_MONTH);
    ds12c88x_year     = DS12C88X_Read(DS12C88X_REG_YEAR);
    /**
     * Quote from Datasheet: The century register at location 32h is a BCD register designed to 
     * automatically load the BCD value 20 as the year register changes from 99 to 00. 
     * The MSB of this register is not affected when the load of 20 occurs, and remains at the 
     * value written by the user.
     */
    ds12c88x_centry   = DS12C88X_Read(DS12C88X_REG_CENTURY) & 0x3F;
}

void DS12C88X_SetTime(uint8_t year, uint8_t month, uint8_t date, uint8_t week_day, 
        uint8_t hour, uint8_t minute, uint8_t second)
{
    DS12C88X_Write(DS12C88X_REG_YEAR, year);
    DS12C88X_Write(DS12C88X_REG_MONTH,month);
    DS12C88X_Write(DS12C88X_REG_DATE, date);
    DS12C88X_Write(DS12C88X_REG_WDAY, week_day);
    DS12C88X_Write(DS12C88X_REG_HOUR, hour);
    DS12C88X_Write(DS12C88X_REG_MIN,  minute);
    DS12C88X_Write(DS12C88X_REG_SEC,  second);
}

uint8_t DS12C88X_bcd2dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t DS12C88X_dec2bcd(uint8_t dec)
{
    return ((dec / 10) << 4) + (dec % 10);
}

void DS12C88X_Increase(uint8_t addr)
{
    uint8_t tmp;

    DS12C88X_Write(DS12C88X_REG_REGB, 0xB2);
    switch (addr)
    {
        case DS12C88X_REG_MIN:
            ds12c88x_minute = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_minute) + 1) % 60);
            DS12C88X_Write(DS12C88X_REG_MIN, ds12c88x_minute);
            break;
        case DS12C88X_REG_ALM_MIN:
            ds12c88x_alarm_minute = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_alarm_minute) + 1) % 60);
            DS12C88X_Write(DS12C88X_REG_ALM_MIN, ds12c88x_alarm_minute);
            break;
        case DS12C88X_REG_HOUR:
            ds12c88x_hour = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_hour) + 1) % 24);
            DS12C88X_Write(DS12C88X_REG_HOUR, ds12c88x_hour);
            break;
        case DS12C88X_REG_ALM_HOUR:
            ds12c88x_alarm_hour = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_alarm_hour) + 1) % 24);
            DS12C88X_Write(DS12C88X_REG_ALM_HOUR, ds12c88x_alarm_hour);
            break;
        case DS12C88X_REG_WDAY:
            ds12c88x_week_day = DS12C88X_dec2bcd(DS12C88X_bcd2dec(ds12c88x_week_day) % 7 + 1);
            DS12C88X_Write(DS12C88X_REG_WDAY, ds12c88x_week_day);
            break;
        case DS12C88X_REG_DATE:
            ds12c88x_date = DS12C88X_dec2bcd(DS12C88X_bcd2dec(ds12c88x_date) % 31 + 1);
            DS12C88X_Write(DS12C88X_REG_DATE, ds12c88x_date);
            break;
        case DS12C88X_REG_MONTH:
            ds12c88x_month = DS12C88X_dec2bcd(DS12C88X_bcd2dec(ds12c88x_month) % 12 + 1);
            DS12C88X_Write(DS12C88X_REG_MONTH, ds12c88x_month);
            break;
        case DS12C88X_REG_YEAR:
            ds12c88x_year = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_year) + 1) % 100);
            DS12C88X_Write(DS12C88X_REG_YEAR, ds12c88x_year);
            break;
        case DS12C88X_REG_CENTURY:
            ds12c88x_centry = DS12C88X_dec2bcd((DS12C88X_bcd2dec(ds12c88x_centry) + 1) % 100);
            DS12C88X_Write(DS12C88X_REG_CENTURY, ds12c88x_centry & 0x3F);
            break;
    }
    DS12C88X_Write(DS12C88X_REG_REGB, 0x32);
}

void DS12C88X_Init(void)
{
    /**
     * 0B: SET PIE AIE UIE SQWE DM 24/12 DSE
     *      0   0   1   1   0    0   1    0
     * SET. When the SET bit is 0, the update transfer functions normally by advancing the 
     * counts once per second. When the SET bit is written to 1, any update transfer is 
     * inhibited, and the program can initialize the time and calendar bytes without an update 
     * occurring in the midst of initializing. Read cycles can be executed in a similar manner.
     * 
     * DM. This bit indicates whether time and calendar information is in binary or BCD format. 
     * The DM bit is set by the program to the appropriate format and can be read as required. 
     * This bit is not modi-fied by internal functions or RESET. A 1 in DM signifies binary data, 
     * while a 0 in DM specifies BCD data.
     * 
     */
    DS12C88X_Write(DS12C88X_REG_REGB, 0x32);

    /**
     * 0A: UIP DV2 DV1 DV0 RS3 RS2 RS1 RS0
     * 
     * UIP. This bit is a status flag that can be monitored. When the UIP bit is a 1, the update 
     * transfer occurs soon. When UIP is a 0, the update transfer does not occur for at least 244µs.
     * 
     * DV2, DV1, DV0. These three bits are used to turn the oscillator on or off and to reset the 
     * countdown chain. A pattern of 010 is the only combination of bits that turn the oscillator 
     * on and allow the RTC to keep time. A pattern of 11x enables the oscillator but holds the 
     * countdown chain in reset. The next update occurs at 500ms after a pattern of 010 is written 
     * to DV0, DV1, and DV2.
     * 
     * RS3, RS2, RS1, RS0. These four rate-selection bits select one of the 13 taps on the 15-stage 
     * divider or disable the divider output. The tap selected can be used to generate an output 
     * square wave (SQW pin) and/or a periodic interrupt. The user can do one of the following: 
     * 1) Enable the interrupt with the PIE bit;
     * 2) Enable the SQW output pin with the SQWE bit;
     * 3) Enable both at the same time and the same rate; or 
     * 4) Enable neither.
     * 
     * RS3 RS2 RS1 RS0  PERIODIC Interrupt Rate  SQW Output Freq
     * 0    0   0   0    None                   None
     * 0    0   0   1    3.90625ms             256Hz
     * 0    0   1   0    7.8125ms              128Hz
     * 0    0   1   1    122.070µs             8.192kHz
     * 0    1   0   0    244.141µs             4.096kHz
     * 0    1   0   1    488.281µs             2.048kHz
     * 0    1   1   0    976.5625µs            1.024kHz
     * 0    1   1   1    1.953125ms            512Hz
     * 1    0   0   0    3.90625ms             256Hz
     * 1    0   0   1    7.8125ms              128Hz
     * 1    0   1   0    15.625ms               64Hz
     * 1    0   1   1    31.25ms                32Hz
     * 1    1   0   0    62.5ms                 16Hz
     * 1    1   0   1    125ms                   8Hz              
     * 1    1   1   0    250ms                   4Hz              
     * 1    1   1   1    500ms                   2Hz              
     */
    DS12C88X_Write(DS12C88X_REG_REGA, 0x20);
}