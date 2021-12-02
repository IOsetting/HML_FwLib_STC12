/*****************************************************************************/
/** 
 * \file        alarm_clock.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Alarm Clock (DS12C887 Real-Time Clocks chip)
 * \note        Pin connection:
 *              > DS12C887 > STC12 MCU
 *              MOT    => GND(or left disconnected)
 *              AD0-7  => P0_0 - P0_7
 *              GND    => GND
 *              VCC    => VCC
 *              SQW
 *              IRQ    => P3_2
 *              RESET  => VCC
 *              DS     => P1_0
 *              RW     => P1_1
 *              AS     => P1_2
 *              CS     => P1_3
 *              
 *              > USB2TTL > STC12 MCU, Baudrate 125000
 *              TX     => P3_0
 *              RX     => P3_1
 * 
 * \version     v0.1
 * \ingroup     example
 * \remarks     test-board: Minimum System; test-MCU: STC12C5A56S2
******************************************************************************/

/*****************************************************************************
 *                             header file                                   *
 *****************************************************************************/
#include "ds12c887.h"

enum KeyMode {
    K_NORMAL,
    K_DISP_SEC,
    K_DISP_WEEKDAY,
    K_DISP_DATE,
    K_DISP_YEAR,
    K_DISP_ALARM,
    K_BUZZ_ALARM,
    K_SET_MINUTE,
    K_SET_HOUR,
    K_SET_HOUR_12_24,
    K_SET_DATE,
    K_SET_MONTH,
    K_SET_WEEKDAY,
    K_SET_YEAR,
    K_SET_CENTURY,
    K_SET_ALARM_MINUTE,
    K_SET_ALARM_HOUR,
};

// display mode states
enum DisplayMode {
    D_NORMAL,
    D_BUZZ_ALARM,
    D_SET_MINUTE,
    D_SET_HOUR,
    D_SET_HOUR_12_24,
    D_SET_DATE,
    D_SET_MONTH,
    D_SET_WEEKDAY,
    D_SET_YEAR,
    D_SET_CENTURY,
    D_SET_ALARM_MINUTE,
    D_SET_ALARM_HOUR,
    D_DISP_ALARM,
    D_DISP_SEC,
    D_DISP_WEEKDAY,
    D_DISP_DATE,
    D_DISP_YEAR,
};

enum Event {
    EV_NONE,
    EV_K1_SHORT,
    EV_K1_LONG,
    EV_K2_SHORT,
    EV_K2_LONG,
    EV_ALARM,
    EV_TIMEOUT,
};

/*
      0x80
     -------
     |     |
 0x20|0x01 |0x40
     -------      : 0x04
     |     |
 0x10|0x08 |0x02
     -------
0b11111010, #0
0b01000010, #1
0b11011001, #2
0b11001011, #3
0b01100011, #4
0b10101011, #5
0b10111011, #6
0b11000010, #7
0b11111011, #8
0b11101011, #9
0b00001000, #:
*/
const uint8_t numbers[12] = {
    0xFA, //0
    0x42, //1
    0xD9, //2
    0xCB, //3
    0x63, //4
    0xAB, //5
    0xBB, //6
    0xC2, //7
    0xFB, //8
    0xEB, //9
    0x04, //:
    0x00, //[]
    };

#define TIMEOUT_SHORT    0x08
#define TIMEOUT_LONG     0x20
#define TIMEOUT_LONGEST  0xFF
#define SW_CNTMAX 80	//long push
#define KEY1      P4_4
#define KEY2      P4_5
#define BUZZ      P3_3

extern uint8_t ds12c88x_reg_a, ds12c88x_reg_b, ds12c88x_reg_c, 
        ds12c88x_alarm_hour, ds12c88x_alarm_minute, ds12c88x_alarm_second, 
        ds12c88x_centry, ds12c88x_year, ds12c88x_month, ds12c88x_date, ds12c88x_week_day, 
        ds12c88x_hour, ds12c88x_minute, ds12c88x_second;

volatile __bit loop_gate, k1_pressed, k2_pressed, k1_long_pressed, k2_long_pressed,
        blinker_500ms, blinker_1s;

uint8_t lcd_segs[4], 
        m_ticks_buzz,             // 1/50
        m_ticks_keyread,          // 1/200
        m_ticks_mainloop,         // 1/1000
        m_ticks_500ms, m_timeout;
volatile uint8_t debounce[2], switchcount[2];
volatile uint16_t m_ticks;
volatile enum KeyMode kmode = K_NORMAL;
volatile enum DisplayMode dmode = D_NORMAL;
volatile enum Event event;

void LCD_Display(void)
{
    uint8_t digi = m_ticks % (uint8_t)4;
    P2 = numbers[lcd_segs[digi]];
    switch (digi)
    {
        case 0x00:
            P1_4 = 0;
            NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
            P1_4 = 1;
            break;
        case 0x01:
            if (dmode == D_DISP_SEC
                || dmode == D_DISP_ALARM
                || (dmode == D_NORMAL && blinker_1s)
                || (dmode == D_BUZZ_ALARM && blinker_500ms))
            {
                P2 |= numbers[10];
            }
            P1_5 = 0;
            NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
            P1_5 = 1;
            break;
        case 0x02:
            P1_6 = 0;
            NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
            P1_6 = 1;
            break;
        case 0x03:
            P1_7 = 0;
            NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
            P1_7 = 1;
            break;
        default:
            break;
    }
    if (dmode == D_BUZZ_ALARM && blinker_500ms && m_ticks_buzz == 0)
    {
        BUZZ = !BUZZ;
    }
}

void read_key1(void)
{
    debounce[0] = (debounce[0] << 1) | KEY1 ; // 未按下时, debounce为0xFF
    if (debounce[0] == 0x00) { // 8次检测都为0, 按下置位
        k1_pressed = 1;
        if (!k1_long_pressed) { // 如果长按未置位, 计数加1
            switchcount[0]++;
        }
    } else { // 否则未按下
        if (k1_pressed) {
            if (!k1_long_pressed) {
                event = EV_K1_SHORT;
            }
            k1_pressed = 0;
            k1_long_pressed = 0;
            switchcount[0] = 0;
        }
    }
    if (switchcount[0] > SW_CNTMAX) {
        k1_long_pressed = 1;
        switchcount[0] = 0;
        event = EV_K1_LONG;
    }
}

void read_key2(void)
{
    debounce[1] = (debounce[1] << 1) | KEY2 ; // 未按下时, debounce为0xFF
    if (debounce[1] == 0x00) { // 8次检测都为0, 按下置位
        k2_pressed = 1;
        if (!k2_long_pressed) { // 如果长按未置位, 计数加1
            switchcount[1]++;
        }
    } else { // 否则未按下
        if (k2_pressed) {
            if (!k2_long_pressed) {
                event = EV_K2_SHORT;
            }
            k2_pressed = 0;
            k2_long_pressed = 0;
            switchcount[1] = 0;
        }
    }
    if (switchcount[1] > SW_CNTMAX) {
        k2_long_pressed = 1;
        switchcount[1] = 0;
        event = EV_K2_LONG;
    }
}

void print_time(void)
{
    UART_sendHex(ds12c88x_reg_a);
    UART_sendByte('-');
    UART_sendHex(ds12c88x_reg_b);
    UART_sendByte('-');
    UART_sendHex(ds12c88x_reg_c);
    UART_sendByte(' ');
    UART_sendHex(ds12c88x_centry);
    UART_sendByte('-');
    UART_sendHex(ds12c88x_year);
    UART_sendByte('-');
    UART_sendHex(ds12c88x_month);
    UART_sendByte('-');
    UART_sendHex(ds12c88x_date);
    UART_sendByte(' ');
    UART_sendHex(ds12c88x_hour);
    UART_sendByte(':');
    UART_sendHex(ds12c88x_minute);
    UART_sendByte(':');
    UART_sendHex(ds12c88x_second);
    UART_sendByte('\n');
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       initialize UART on P3.0/P3.1
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void initSys(void)
{
    UART_configTypeDef uc;
    uc.mode                        = UART_mode_1;
    uc.doubleBaudrate              = DISABLE;
    uc.baudrateGenerator           = UART_baudrateGenerator_brt;
    UART_config(&uc);
    RCC_BRT_config(125000, RCC_BRT_prescaler_1, uc.doubleBaudrate);
    UART_INT_cmd(DISABLE);
    UART_INT_setPriority(IntPriority_High);
    UART_setReceive(ENABLE);

    // Set Timer0 frequency to 10,000 Hz (interval 0.1ms)
    TIM_configTypeDef tc;
    tc.function          = TIM_function_tim;
    tc.interruptState    = ENABLE;
    tc.interruptPriority = IntPriority_Low;
    tc.mode              = TIM_mode_2;
    tc.prescaler         = TIM_prescaler_12;
    tc.value             = 0x9C9C; // 12000000 / 10000 = 1200 cycles = 12 * 100 = 12 * (256 - 156),  0x9C = 156
    //tc.value             = 0xCECE; // 12000000 / 20000 = 600 cycles = 12 * 50 = 12 * (256 - 206),  0xCE = 206
    TIM_config(PERIPH_TIM_0, &tc);
    UTIL_setInterrupts(ENABLE);
    TIM_cmd(PERIPH_TIM_0, ENABLE);
}

/*****************************************************************************/
/** 
 * \author      IOsetting
 * \date        
 * \brief       main function
 * \param[in]   
 * \return      none
 * \ingroup     example
 * \remarks     
******************************************************************************/
void main(void)
{
    enum Event ev;
    uint8_t tmp;

    initSys();
    DS12C88X_Init();
    DS12C88X_ReloadTime(true);

    EA = 1;
    IT0 = 1;
    EX0 = 1;

    GPIO_configMode(PERIPH_GPIO_1, PERIPH_GPIO_PIN_4, GPIO_mode_PP);
    GPIO_configMode(PERIPH_GPIO_1, PERIPH_GPIO_PIN_5, GPIO_mode_PP);
    GPIO_configMode(PERIPH_GPIO_1, PERIPH_GPIO_PIN_6, GPIO_mode_PP);
    GPIO_configMode(PERIPH_GPIO_1, PERIPH_GPIO_PIN_7, GPIO_mode_PP);
    GPIO_configPortMode(PERIPH_GPIO_2, GPIO_mode_PP);
    GPIO_configMode(PERIPH_GPIO_4, PERIPH_GPIO_PIN_4, GPIO_mode_HIS);
    GPIO_configMode(PERIPH_GPIO_4, PERIPH_GPIO_PIN_5, GPIO_mode_HIS);
    GPIO_configMode(PERIPH_GPIO_3, PERIPH_GPIO_PIN_3, GPIO_mode_OD);

    while (true)
    {
        while (!loop_gate); // wait for open every 100ms
        loop_gate = 0; // close gate

        ev = event;
        event = EV_NONE;
        switch (kmode)
        {
            case K_DISP_SEC:
                dmode = D_DISP_SEC;
                if (ev == EV_K2_SHORT) {
                    kmode = K_DISP_ALARM;
                    m_timeout = TIMEOUT_SHORT;
                }
                break;
            case K_DISP_ALARM:
                dmode = D_DISP_ALARM;
                if (ev == EV_K2_SHORT) {
                    kmode = K_NORMAL;
                } else if (ev == EV_TIMEOUT) {
                    kmode = K_NORMAL;
                }
                break;

            case K_SET_ALARM_MINUTE:
                dmode = D_SET_ALARM_MINUTE;
                if (ev == EV_K2_SHORT) {
                    kmode = K_SET_ALARM_HOUR;
                } else if (ev == EV_K1_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_ALM_MIN);
                }
                break;
            case K_SET_ALARM_HOUR:
                dmode = D_SET_ALARM_HOUR;
                if (ev == EV_K2_SHORT) {
                    kmode = K_NORMAL;
                } else if (ev == EV_K1_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_ALM_HOUR);
                }
                break;

            case K_DISP_DATE:
                dmode = D_DISP_DATE;
                if (ev == EV_K1_SHORT) {
                    kmode = K_DISP_WEEKDAY;
                    m_timeout = TIMEOUT_SHORT;
                } else if (ev == EV_TIMEOUT) {
                    kmode = K_NORMAL;
                }
                break;
            case K_DISP_WEEKDAY:
                dmode = D_DISP_WEEKDAY;
                if (ev == EV_K1_SHORT) {
                    kmode = K_DISP_YEAR;
                    m_timeout = TIMEOUT_SHORT;
                } else if (ev == EV_TIMEOUT) {
                    kmode = K_NORMAL;
                }
                break;
            case K_DISP_YEAR:
                dmode = D_DISP_YEAR;
                if (ev == EV_K1_SHORT) {
                    kmode = K_NORMAL;
                } else if (ev == EV_TIMEOUT) {
                    kmode = K_NORMAL;
                }
                break;
            
            case K_SET_MINUTE:
                dmode = D_SET_MINUTE;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_HOUR;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_MIN);
                }
                break;
            case K_SET_HOUR:
                dmode = D_SET_HOUR;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_DATE;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_HOUR);
                }
                break;
            case K_SET_DATE:
                dmode = D_SET_DATE;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_MONTH;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_DATE);
                }
                break;
            case K_SET_MONTH:
                dmode = D_SET_MONTH;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_WEEKDAY;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_MONTH);
                }
                break;
            case K_SET_WEEKDAY:
                dmode = D_SET_WEEKDAY;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_YEAR;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_WDAY);
                }
                break;
            case K_SET_YEAR:
                dmode = D_SET_YEAR;
                if (ev == EV_K1_SHORT) {
                    kmode = K_SET_CENTURY;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_YEAR);
                }
                break;
            case K_SET_CENTURY:
                dmode = D_SET_CENTURY;
                if (ev == EV_K1_SHORT) {
                    kmode = K_NORMAL;
                } else if (ev == EV_K2_SHORT) {
                    DS12C88X_Increase(DS12C88X_REG_CENTURY);
                }
                break;
            case K_BUZZ_ALARM:
                dmode = D_BUZZ_ALARM;
                if (ev == EV_K1_SHORT || ev == EV_K2_SHORT) {
                    kmode = K_NORMAL;
                } else if (ev == EV_TIMEOUT) {
                    kmode = K_NORMAL;
                }
                break;

            case K_NORMAL:
            default:
                dmode = D_NORMAL;
                
                if (ev == EV_K1_SHORT) {
                    kmode = K_DISP_DATE;
                    m_timeout = TIMEOUT_SHORT;
                } else if (ev == EV_ALARM) {
                    kmode = K_BUZZ_ALARM;
                    m_timeout = TIMEOUT_LONG;
                }
                else if (ev == EV_K1_LONG)
                    kmode = K_SET_MINUTE;
                else if (ev == EV_K2_SHORT)
                    kmode = K_DISP_SEC;
                else if (ev == EV_K2_LONG)
                    kmode = K_SET_ALARM_MINUTE;
        }

        switch (dmode)
        {
            case D_DISP_SEC:
                lcd_segs[0] = 11;
                lcd_segs[1] = 11;
                lcd_segs[2] = ds12c88x_second >> 4;
                lcd_segs[3] = ds12c88x_second & 0x0F;
                break;
            case D_DISP_DATE:
                lcd_segs[0] = ds12c88x_month >> 4;
                lcd_segs[1] = ds12c88x_month & 0x0F;
                lcd_segs[2] = ds12c88x_date >> 4;
                lcd_segs[3] = ds12c88x_date & 0x0F;
                break;
            case D_DISP_WEEKDAY:
                lcd_segs[0] = ds12c88x_week_day >> 4;
                lcd_segs[1] = ds12c88x_week_day & 0x0F;
                lcd_segs[2] = 11;
                lcd_segs[3] = 11;
                break;
            case D_DISP_YEAR:
                lcd_segs[0] = ds12c88x_centry >> 4;
                lcd_segs[1] = ds12c88x_centry & 0x0F;
                lcd_segs[2] = ds12c88x_year >> 4;
                lcd_segs[3] = ds12c88x_year & 0x0F;
                break;
            case D_DISP_ALARM:
                lcd_segs[0] = ds12c88x_alarm_hour >> 4;
                lcd_segs[1] = ds12c88x_alarm_hour & 0x0F;
                lcd_segs[2] = ds12c88x_alarm_minute >> 4;
                lcd_segs[3] = ds12c88x_alarm_minute & 0x0F;
                break;
            
            case D_SET_MINUTE:
                lcd_segs[0] = ds12c88x_hour >> 4;
                lcd_segs[1] = ds12c88x_hour & 0x0F;
                if (blinker_500ms)
                {
                    lcd_segs[2] = ds12c88x_minute >> 4;
                    lcd_segs[3] = ds12c88x_minute & 0x0F;
                }
                else
                {
                    lcd_segs[2] = 11;
                    lcd_segs[3] = 11;
                }
                break;
            case D_SET_HOUR:
                if (blinker_500ms)
                {
                    lcd_segs[0] = ds12c88x_hour >> 4;
                    lcd_segs[1] = ds12c88x_hour & 0x0F;
                }
                else
                {
                    lcd_segs[0] = 11;
                    lcd_segs[1] = 11;
                }
                lcd_segs[2] = ds12c88x_minute >> 4;
                lcd_segs[3] = ds12c88x_minute & 0x0F;
                break;
            case D_SET_DATE:
                lcd_segs[0] = ds12c88x_month >> 4;
                lcd_segs[1] = ds12c88x_month & 0x0F;
                if (blinker_500ms)
                {
                    lcd_segs[2] = ds12c88x_date >> 4;
                    lcd_segs[3] = ds12c88x_date & 0x0F;
                }
                else
                {
                    lcd_segs[2] = 11;
                    lcd_segs[3] = 11;
                }
                break;
            case D_SET_MONTH:
                if (blinker_500ms)
                {
                    lcd_segs[0] = ds12c88x_month >> 4;
                    lcd_segs[1] = ds12c88x_month & 0x0F;
                }
                else
                {
                    lcd_segs[0] = 11;
                    lcd_segs[1] = 11;
                }
                lcd_segs[2] = ds12c88x_date >> 4;
                lcd_segs[3] = ds12c88x_date & 0x0F;
                
                break;
            case D_SET_WEEKDAY:
                if (blinker_500ms)
                {
                    lcd_segs[0] = ds12c88x_week_day >> 4;
                    lcd_segs[1] = ds12c88x_week_day & 0x0F;
                }
                else
                {
                    lcd_segs[0] = 11;
                    lcd_segs[1] = 11;
                }
                lcd_segs[2] = 11;
                lcd_segs[3] = 11;
                break;
            case D_SET_YEAR:
                lcd_segs[0] = ds12c88x_centry >> 4;
                lcd_segs[1] = ds12c88x_centry & 0x0F;
                if (blinker_500ms)
                {
                    lcd_segs[2] = ds12c88x_year >> 4;
                    lcd_segs[3] = ds12c88x_year & 0x0F;
                }
                else
                {
                    lcd_segs[2] = 11;
                    lcd_segs[3] = 11;
                }
                break;
            case D_SET_CENTURY:
                if (blinker_500ms)
                {
                    lcd_segs[0] = ds12c88x_centry >> 4;
                    lcd_segs[1] = ds12c88x_centry & 0x0F;
                }
                else
                {
                    lcd_segs[0] = 11;
                    lcd_segs[1] = 11;
                }
                lcd_segs[2] = ds12c88x_year >> 4;
                lcd_segs[3] = ds12c88x_year & 0x0F;
                break;
            case D_SET_ALARM_MINUTE:
                lcd_segs[0] = ds12c88x_alarm_hour >> 4;
                lcd_segs[1] = ds12c88x_alarm_hour & 0x0F;
                if (blinker_500ms)
                {
                    lcd_segs[2] = ds12c88x_alarm_minute >> 4;
                    lcd_segs[3] = ds12c88x_alarm_minute & 0x0F;
                }
                else
                {
                    lcd_segs[2] = 11;
                    lcd_segs[3] = 11;
                }
                break;
            case D_SET_ALARM_HOUR:
                if (blinker_500ms)
                {
                    lcd_segs[0] = ds12c88x_alarm_hour >> 4;
                    lcd_segs[1] = ds12c88x_alarm_hour & 0x0F;
                }
                else
                {
                    lcd_segs[0] = 11;
                    lcd_segs[1] = 11;
                }
                lcd_segs[2] = ds12c88x_alarm_minute >> 4;
                lcd_segs[3] = ds12c88x_alarm_minute & 0x0F;
                break;

            case D_NORMAL:
            case D_BUZZ_ALARM:
            default:
                lcd_segs[0] = ds12c88x_hour >> 4;
                lcd_segs[1] = ds12c88x_hour & 0x0F;
                lcd_segs[2] = ds12c88x_minute >> 4;
                lcd_segs[3] = ds12c88x_minute & 0x0F;
                break;
        }
    }
}

void IT0IRQ(void) __interrupt(IE0_VECTOR)
{
    DS12C88X_ReloadTime(false);
    blinker_1s = !blinker_1s;
}

void TIM0IRQ(void) __interrupt (TF0_VECTOR) __using(1)
{
    m_ticks++;
    m_ticks_buzz++;
    if (m_ticks_buzz == 50)
    {
        m_ticks_buzz = 0;
    }
    m_ticks_keyread++;
    if (m_ticks_keyread == 100)
    {
        m_ticks_keyread = 0;
        read_key1();
        read_key2();

        m_ticks_mainloop++;
        if (m_ticks_mainloop == 10)
        {
            m_ticks_mainloop = 0;
            if ((ds12c88x_reg_c & 0x20) == 0x20)
            {
                event = EV_ALARM;
            }
            loop_gate = 1;

            m_ticks_500ms++;
            if (m_ticks_500ms == 5)
            {
                m_ticks_500ms = 0;
                blinker_500ms = !blinker_500ms;

                if (m_timeout != 0) {
                    m_timeout--;
                    if (m_timeout == 0) {
                        if (event == EV_NONE) {
                            event = EV_TIMEOUT;
                        }
                    }
                }
            }
        }
    }
    LCD_Display();
}