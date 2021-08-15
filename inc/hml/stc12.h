/*****************************************************************************/
/** 
 * \file        stc12.h
 * \author      Weilun Fong | wlf@zhishan-iot.tk
 * \brief       STC12xx header file
 * \note        
 * \version     v0.0
 * \ingroup     generic
******************************************************************************/

#ifndef ___HML_STC12_H___
#define ___HML_STC12_H___

#include <lint.h>
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
__sfr __at (0x9A) S2CON     ;
__sfr __at (0x9B) S2BUF     ;
__sfr __at (0x9C) BRT       ;
__sfr __at (0x9D) P1ASF     ;
__sfr __at (0xA1) BUS_SPEED ;
__sfr __at (0xA2) AUXR1     ;
__sfr __at (0xA9) SADDR    ;
__sfr __at (0xAB) WKTCH     ;
__sfr __at (0xAA) WKTCL     ;
__sfr __at (0xAF) IE2       ;
__sfr __at (0xB1) P3M1      ;
__sfr __at (0xB2) P3M0      ;
__sfr __at (0xB3) P4M1      ;
__sfr __at (0xB4) P4M0      ;
__sfr __at (0xB5) IP2       ;
__sfr __at (0xB6) IP2H      ;
__sfr __at (0xB7) IPH       ;
__sfr __at (0xB9) SADEN     ;
__sfr __at (0xBB) P4SW      ;
__sfr __at (0xBC) ADC_CONTR ;
__sfr __at (0xBD) ADC_RES   ;
__sfr __at (0xBE) ADC_RESL  ;
__sfr __at (0xC0) P4        ;
__sfr __at (0xC1) WDT_CONTR ;
__sfr __at (0xC2) IAP_DATA  ;
__sfr __at (0xC3) IAP_ADDRH ;
__sfr __at (0xC4) IAP_ADDRL ;
__sfr __at (0xC5) IAP_CMD   ;
__sfr __at (0xC6) IAP_TRIG  ;
__sfr __at (0xC7) IAP_CONTR ;
__sfr __at (0xC8) P5        ;
__sfr __at (0xC9) P5M1      ;
__sfr __at (0xCA) P5M0      ;
__sfr __at (0xCD) SPSTAT    ;
__sfr __at (0xCE) SPCTL     ;
__sfr __at (0xCF) SPDAT     ;
__sfr __at (0xD8) CCON      ;
__sfr __at (0xD9) CMOD      ;
__sfr __at (0xDA) CCAPM0    ;
__sfr __at (0xDB) CCAPM1    ;
__sfr __at (0xE9) CL        ;
__sfr __at (0xEA) CCAP0L    ;
__sfr __at (0xEB) CCAP1L    ;
__sfr __at (0xF2) PCA_PWM0  ;
__sfr __at (0xF3) PCA_PWM1  ;
__sfr __at (0xF9) CH        ;
__sfr __at (0xFA) CCAP0H    ;
__sfr __at (0xFB) CCAP1H    ;

/*  BIT Register  */
/* IE */
/* Enable ADC Interrupt */
__sbit __at (0xAD) EADC     ;
/* Enable Low Voltage Detection Interrupt */
__sbit __at (0xAE) ELVD     ;

/* IP */
/* Interrupt Priority for PCA */
__sbit __at (0xBF) PPCA     ;
/* Interrupt Priority for Low Voltage Detection */
__sbit __at (0xBE) PLVD     ;
/* Interrupt Priority for ADC */
__sbit __at (0xBD) PADC     ;
__sbit __at (0xBC) PS       ;
__sbit __at (0xBB) PT1      ;
__sbit __at (0xBA) pX1      ;
__sbit __at (0xB9) PT0      ;
__sbit __at (0xB8) PX0      ;

/* P4 */
__sbit __at (0xC0) P4_0     ;
__sbit __at (0xC1) P4_1     ;
__sbit __at (0xC2) P4_2     ;
__sbit __at (0xC3) P4_3     ;
__sbit __at (0xC4) P4_4     ;
__sbit __at (0xC5) P4_5     ;
__sbit __at (0xC6) P4_6     ;
__sbit __at (0xC7) P4_7     ;

/* P5 */
__sbit __at (0xC8) P5_0     ;
__sbit __at (0xC9) P5_1     ;
__sbit __at (0xCA) P5_2     ;
__sbit __at (0xCB) P5_3     ;

/* PCA Control Register */
/* Bit Mapping: CF CR - - - - CCF1 CCF0 */
__sbit __at (0xDF) CF       ;
__sbit __at (0xDE) CR       ;
__sbit __at (0xD9) CCF1     ;
__sbit __at (0xD8) CCF0     ;

/* BIT number for bits that are not directly accessible */
/* ADC_CONTR bits */
#define BIT_NUM_CHS0        0
#define BIT_NUM_CHS1        1
#define BIT_NUM_CHS2        2
#define BIT_NUM_ADC_START   3
#define BIT_NUM_ADC_FLAG    4
#define BIT_NUM_SPEED0      5
#define BIT_NUM_SPEED1      6
#define BIT_NUM_ADC_POWER   7

/* AUXR bits */
#define BIT_NUM_S1BRS       0
#define BIT_NUM_EXTRAM      1
#define BIT_NUM_BRTx12      2
#define BIT_NUM_S2SMOD      3
#define BIT_NUM_BRTR        4
#define BIT_NUM_UART_M0x6   5
#define BIT_NUM_T1x12       6
#define BIT_NUM_T0x12       7

/* AUXR1 bits */
#define BIT_NUM_DPS         0
#define BIT_NUM_ADRJ        2
#define BIT_NUM_GF2         3
#define BIT_NUM_S2_P4       4
#define BIT_NUM_SPI_P4      5
#define BIT_NUM_PCA_P4      6

/* BUS_SPEED bits */
#define BIT_NUM_RWS0        0
#define BIT_NUM_RWS1        1
#define BIT_NUM_RWS2        2
#define BIT_NUM_ALES0       4
#define BIT_NUM_ALES1       5

/* CCAPM0 bits */
#define BIT_NUM_ECCF0       0
#define BIT_NUM_PWM0        1
#define BIT_NUM_TOG0        2
#define BIT_NUM_MAT0        3
#define BIT_NUM_CAPN0       4
#define BIT_NUM_CAPP0       5
#define BIT_NUM_ECOM0       6

/* CCAPM1 bits */
#define BIT_NUM_ECCF1       0
#define BIT_NUM_PWM1        1
#define BIT_NUM_TOG1        2
#define BIT_NUM_MAT1        3
#define BIT_NUM_CAPN1       4
#define BIT_NUM_CAPP1       5
#define BIT_NUM_ECOM1       6

/* CLK_DIV bits */
#define BIT_NUM_CLKS0       0
#define BIT_NUM_CLKS1       1
#define BIT_NUM_CLKS2       2

/* CMOD bits */
#define BIT_NUM_CMOD_ECF    0
#define BIT_NUM_CMOD_CPS0   1
#define BIT_NUM_CMOD_CPS1   2
#define BIT_NUM_CMOD_CPS2   3
#define BIT_NUM_CMOD_CIDL   7

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

/* IE2 bits */
#define BIT_NUM_IE2_ES2     0
#define BIT_NUM_IE2_ESPI    1

/* IP2 bits */
#define BIT_NUM_IP2_PS2     0
#define BIT_NUM_IP2_PSPI    1

/* IP2H bits */
#define BIT_NUM_IP2H_PS2H   0
#define BIT_NUM_IP2H_PSPIH  1

/* IPH bits */
#define BIT_NUM_PX0H        0
#define BIT_NUM_PT0H        1
#define BIT_NUM_PX1H        2
#define BIT_NUM_PT1H        3
#define BIT_NUM_PSH         4
#define BIT_NUM_PADCH       5
#define BIT_NUM_PLVDH       6
#define BIT_NUM_PPCAH       7

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

/* S2CON bits */
#define BIT_NUM_S2RI        0
#define BIT_NUM_S2TI        1
#define BIT_NUM_S2RB8       2
#define BIT_NUM_S2TB8       3
#define BIT_NUM_S2REN       4
#define BIT_NUM_S2SM2       5
#define BIT_NUM_S2SM1       6
#define BIT_NUM_S2SM0       7

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
#define BIT_NUM_WDT_PS0     0
#define BIT_NUM_WDT_PS1     1
#define BIT_NUM_WDT_PS2     2
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
#define WDT_PS0             BIT_MASK(BIT_NUM_WDT_PS0)
#define WDT_PS1             BIT_MASK(BIT_NUM_WDT_PS1)
#define WDT_PS2             BIT_MASK(BIT_NUM_WDT_PS2)
#define IDLE_WDT            BIT_MASK(BIT_NUM_IDLE_WDT)
#define CLR_WDT             BIT_MASK(BIT_NUM_CLR_WDT)
#define EN_WDT              BIT_MASK(BIT_NUM_EN_WDT)
#define WDT_FLAG            BIT_MASK(BIT_NUM_WDT_FLAG)

/* Interrupt numbers: address = (number * 8) + 3 */
#define ADC_VECTOR          5    /* 0x2b ADC interrupt generated by ADC_FLAG */
#define LVD_VECTOR          6    /* 0x33 LVD(low voltage ditect) */
#define PCA_VECTOR          7    /* 0x3B generated by the logical OR of CF, CCF0 ~ CCF1 */
#define S2_VECTOR           8    /* 0x43 serial port 2 */
#define SPI_VECTOR          9    /* 0x4B SPI interrupt */

/**
 * \brief mark generic interrupt priority
 */
typedef enum
{
    IntPriority_Lowest  = 0x00,
    IntPriority_Low     = 0x01,
    IntPriority_High    = 0x02,
    IntPriority_Highest = 0x03,
} IntPriority;

#endif
