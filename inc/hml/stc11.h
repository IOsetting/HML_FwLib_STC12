/*
 * @Author:
 *  #Weilun Fong | wlf(at)zhishan-iot.tk
 * @E-mail:mcu(at)zhishan-iot.tk
 * @File-description:STC11xx header file
 * @Required-compiler:SDCC
 * @Support-mcu:STC micro STC11 series
 * @Version:V0
 */

#ifndef ___STC11_H___
#define ___STC11_H___

#include <8051.h>
#include "bit.h"

/*  BYTE Register  */
__sfr __at (0x8E) AUXR      ;
__sfr __at (0x8F) WAKE_CLKO ;
__sfr __at (0x91) P1M1      ;
__sfr __at (0x92) P1M0      ;
__sfr __at (0x93) P0M1      ;
__sfr __at (0x94) P0M0      ;
__sfr __at (0x95) P2M1      ;
__sfr __at (0x96) P2M0      ;
__sfr __at (0x97) CLK_DIV   ;
__sfr __at (0x9C) BRT       ;
__sfr __at (0xA1) BUS_SPEED ;
__sfr __at (0xA2) AUXR1     ;
__sfr __at (0xA9) SADDDR    ;
__sfr __at (0xAB) WKTCH     ;
__sfr __at (0xAA) WKTCL     ;
__sfr __at (0xB1) P3M1      ;
__sfr __at (0xB2) P3M0      ;
__sfr __at (0xB3) P4M1      ;
__sfr __at (0xB4) P4M0      ;
__sfr __at (0xB9) SADEN     ;
__sfr __at (0xBB) P4SW      ;
__sfr __at (0xC0) P4        ;
__sfr __at (0xC1) WDT_CONTR ;
__sfr __at (0xC2) IAP_DATA  ;
__sfr __at (0xC3) IAP_ADDRH ;
__sfr __at (0xC4) IAP_ADDRL ;
__sfr __at (0xC5) IAP_CMD   ;
__sfr __at (0xC6) IAP_TRIG  ;
__sfr __at (0xC7) IAP_CONTR ;

/*  BIT Register  */
/* IE */
__sbit __at (0xAE) ELVD     ;

/* P4 */
__sbit __at (0xC0) P4_0     ;
__sbit __at (0xC1) P4_1     ;
__sbit __at (0xC2) P4_2     ;
__sbit __at (0xC3) P4_3     ;
__sbit __at (0xC4) P4_4     ;
__sbit __at (0xC5) P4_5     ;
__sbit __at (0xC6) P4_6     ;
__sbit __at (0xC7) P4_7     ;

/* BIT number for bits that are not directly accessible */
/* AUXR bits */
#define BIT_NUM_S1BRS       0
#define BIT_NUM_EXTRAM      1
#define BIT_NUM_BRTx12      2
#define BIT_NUM_BRTR        4
#define BIT_NUM_UART_M0x6   5
#define BIT_NUM_T1x12       6
#define BIT_NUM_T0x12       7

/* AUXR1 bits */
#define BIT_NUM_DPS         0
#define BIT_NUM_GF2         3
#define BIT_NUM_UART_P1     7

/* BUS_SPEED bits */
#define BIT_NUM_RWS0        0
#define BIT_NUM_RWS1        1
#define BIT_NUM_RWS2        2
#define BIT_NUM_ALES0       4
#define BIT_NUM_ALES1       5

/* CLK_DIV bits */
#define BIT_NUM_CLKS0       0
#define BIT_NUM_CLKS1       1
#define BIT_NUM_CLKS2       2

/* IAP_CMD bits */
#define BIT_NUM_MS0         0
#define BIT_NUM_MS1         1

/* IAP_CONTR bits */
#define BIT_NUM_WT0         0
#define BIT_NUM_WT1         1
#define BIT_NUM_WT2         2
#define BIT_NUM_CMD_FAIL    4
#define BIT_NUM_SWRST       5
#define BIT_NUM_SWBS        6
#define BIT_NUM_IAPEN       7

/* P4SW bits */
#define BIT_NUM_NA_P44      4
#define BIT_NUM_ALE_P45     5
#define BIT_NUM_NA_P46      6

/* PCON bits */
#define BIT_NUM_IDL         0
#define BIT_NUM_PD          1
#define BIT_NUM_GF0         2
#define BIT_NUM_GF1         3
#define BIT_NUM_POF         4
#define BIT_NUM_LVDF        5
#define BIT_NUM_SMOD        6
#define BIT_NUM_SMOD0       7

/* TCON bits */
#define BIT_NUM_T0_M0       0
#define BIT_NUM_T0_M1       1
#define BIT_NUM_T0_CT       2
#define BIT_NUM_T0_GATE     3
#define BIT_NUM_T1_M0       4
#define BIT_NUM_T1_M1       5
#define BIT_NUM_T1_CT       6
#define BIT_NUM_T1_GATE     7

/* WAKE_CLKO bits */
#define BIT_NUM_T0CLKO      0
#define BIT_NUM_T1CLKO      1
#define BIT_NUM_BRTCLKO     2
#define BIT_NUM_T0_PIN_IE   4
#define BIT_NUM_T1_PIN_IE   5
#define BIT_NUM_RD_PIN_IE   6

/* WKTCH bits */
#define BIT_NUM_WKTEN       7

/* WDT_CONTR bits */
#define BIT_NUM_PS0         0
#define BIT_NUM_PS1         1
#define BIT_NUM_PS2         2
#define BIT_NUM_IDLE_WDT    3
#define BIT_NUM_CLR_WDT     4
#define BIT_NUM_EN_WDT      5
#define BIT_NUM_WDT_FLAG    7

/* BIT definitions for bits that are not directly accessible */
/* AUXR bits */
#define S1BRS               BIT_MASK(BIT_NUM_S1BRS)
#define EXTRAM              BIT_MASK(BIT_NUM_EXTRAM)
#define BRTx12              BIT_MASK(BIT_NUM_BRTx12)
#define BRTR                BIT_MASK(BIT_NUM_BRTR)
#define UART_M0x6           BIT_MASK(BIT_NUM_UART_M0x6)
#define T1x12               BIT_MASK(BIT_NUM_T1x12)
#define T0x12               BIT_MASK(BIT_NUM_T0x12)

/* AUXR1 bits */
#define DPS                 BIT_MASK(BIT_NUM_DPS)
#define GF2                 BIT_MASK(BIT_NUM_GF2)
#define UART_P1             BIT_MASK(BIT_NUM_UART_P1)

/* BUS_SPEED bits */
#define RWS0                BIT_MASK(BIT_NUM_RWS0)
#define RWS1                BIT_MASK(BIT_NUM_RWS1)
#define RWS2                BIT_MASK(BIT_NUM_RWS2)
#define ALES0               BIT_MASK(BIT_NUM_ALES0)
#define ALES1               BIT_MASK(BIT_NUM_ALES1)

/* CLK_DIV bits */
#define CLKS0               BIT_MASK(BIT_NUM_CLKS0)
#define CLKS1               BIT_MASK(BIT_NUM_CLKS1)
#define CLKS2               BIT_MASK(BIT_NUM_CLKS2)

/* IAP_CMD bits */
#define MS0                 BIT_MASK(BIT_NUM_MS0)
#define MS1                 BIT_MASK(BIT_NUM_MS1)

/* IAP_CONTR bits */
#define WT0                 BIT_MASK(BIT_NUM_WT0)
#define WT1                 BIT_MASK(BIT_NUM_WT1)
#define WT2                 BIT_MASK(BIT_NUM_WT2)
#define CMD_FAIL            BIT_MASK(BIT_NUM_CMD_FAIL)
#define SWRST               BIT_MASK(BIT_NUM_SWRST)
#define SWBS                BIT_MASK(BIT_NUM_SWBS)
#define IAPEN               BIT_MASK(BIT_NUM_IAPEN)

/* P4SW bits */
#define NA_P44              BIT_MASK(BIT_NUM_NA_P44)
#define NA_P45              BIT_MASK(BIT_NUM_NA_P45)
#define NA_P46              BIT_MASK(BIT_NUM_NA_P46)

/* PCON bits */
#define POF                 BIT_MASK(BIT_NUM_POF)
#define LVDF                BIT_MASK(BIT_NUM_LVDF)
#define SMOD0               BIT_MASK(BIT_NUM_SMOD0)

/* WAKE_CLKO bits */
#define T0CLKO              BIT_MASK(BIT_NUM_T0CLKO)
#define T1CLKO              BIT_MASK(BIT_NUM_T1CLKO)
#define BRTCLKO             BIT_MASK(BIT_NUM_BRTCLKO)
#define T0_PIN_IE           BIT_MASK(BIT_NUM_T0_PIN_IE)
#define T1_PIN_IE           BIT_MASK(BIT_NUM_T1_PIN_IE)
#define RD_PIN_IE           BIT_MASK(BIT_NUM_RD_PIN_IE)

/* WKTCH bits */
#define WKTEN               BIT_MASK(BIT_NUM_WKTEN)

/* WDT_CONTR bits */
#define PS0                 BIT_MASK(BIT_NUM_PS0)
#define PS1                 BIT_MASK(BIT_NUM_PS1)
#define PS2                 BIT_MASK(BIT_NUM_PS2)
#define IDLE_WDT            BIT_MASK(BIT_NUM_IDLE_WDT)
#define CLR_WDT             BIT_MASK(BIT_NUM_CLR_WDT)
#define EN_WDT              BIT_MASK(BIT_NUM_EN_WDT)
#define WDT_FLAG            BIT_MASK(BIT_NUM_WDT_FLAG)

/* Interrupt numbers: address = (number * 8) + 3 */
// #define ADC_VECTOR          5    /* reserved for ADC function */
#define LVD_VECTOR          6    /* 0x33 LVD(low voltage ditect)*/

#endif
