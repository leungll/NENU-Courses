/******************************************************************************
**                                                                           **
**  Copyright (c) 2000 ARM Limited                                           **
**  All rights reserved                                                      **
**                                                                           **
******************************************************************************/

#ifndef __INTGRTDEF
#define __INTGRTDEF

/*****************************************************************************/
/*  Base addresses for standard memory-mapped peripherals                    */
/*****************************************************************************/
#define IntBase         0x14000000  /* Interrupt Controller Base             */
#define FIQBase         0x14000020  /* FIQ Controller Base                   */
#define TimerBase       0x13000000  /* Counter/Timer Base                    */
#define CoreBase        0x10000000  /* Core Module Registers                 */

/*****************************************************************************/
/*  Definitions of IRQ and FIQ ids                                           */
/*****************************************************************************/
#define SOFTINT         0x000001
#define UARTINT0        0x000002
#define UARTINT1        0x000004
#define KBDINT          0x000008
#define MOUSEINT        0x000010
#define TIMERINT0       0x000020
#define TIMERINT1       0x000040
#define TIMERINT2       0x000080
#define RTCINT          0x000100
#define EXPINT0         0x000200
#define EXPINT1         0x000400
#define EXPINT2         0x000800
#define EXPINT3         0x001000
#define PCIINT0         0x002000
#define PCIINT1         0x004000
#define PCIINT2         0x008000
#define PCIINT3         0x010000
#define LINT            0x020000
#define DEGINT          0x040000
#define ENUMINT         0x080000
#define PCIINT          0x100000
#define APCIINT         0x200000

/*****************************************************************************/
/*  Retain previous definitions from PID7T board for code compatibility      */
/*****************************************************************************/
#define IRQSerialA      UARTINT0
#define IRQSerialB      UARTINT1
#define IRQTimer0       TIMERINT0
#define IRQTimer1       TIMERINT1
#define IRQTimer2       TIMERINT2

/*****************************************************************************/
/* RPS interrupt Controller IRQ register                                     */
/*****************************************************************************/
#define IRQStatus      ((volatile unsigned *)IntBase)
#define IRQRawStatus   ((volatile unsigned *)(IntBase + 0x04))
#define IRQEnable      ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableSet   ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableClear ((volatile unsigned *)(IntBase + 0x0c))
#define IRQSoft        ((volatile unsigned *)(IntBase + 0x10))

/*****************************************************************************/
/* RPS interrupt Controller FIQ register                                     */
/*****************************************************************************/
#define FIQStatus      ((volatile unsigned *)FIQBase)
#define FIQRawStatus   ((volatile unsigned *)(FIQBase + 0x04))
#define FIQEnable      ((volatile unsigned *)(FIQBase + 0x08))
#define FIQEnableSet   ((volatile unsigned *)(FIQBase + 0x08))
#define FIQEnableClear ((volatile unsigned *)(FIQBase + 0x0c))

/*****************************************************************************/
/*  Counter/timer registers                                                  */
/*****************************************************************************/
#define Timer0Load       ((volatile unsigned *)TimerBase)
#define Timer0Value      ((volatile unsigned *)(TimerBase + 0x04))
#define Timer0Control    ((volatile unsigned *)(TimerBase + 0x08))
#define Timer0Clear      ((volatile unsigned *)(TimerBase + 0x0C))

#define Timer1Load       ((volatile unsigned *)(TimerBase + 0x100))
#define Timer1Value      ((volatile unsigned *)(TimerBase + 0x104))
#define Timer1Control    ((volatile unsigned *)(TimerBase + 0x108))
#define Timer1Clear      ((volatile unsigned *)(TimerBase + 0x10C))

#define Timer2Load       ((volatile unsigned *)(TimerBase + 0x200))
#define Timer2Value      ((volatile unsigned *)(TimerBase + 0x204))
#define Timer2Control    ((volatile unsigned *)(TimerBase + 0x208))
#define Timer2Clear      ((volatile unsigned *)(TimerBase + 0x20C))

/*****************************************************************************/
/* Counter/Timer control register bits                                       */
/*****************************************************************************/
#define TimerEnable      0x80
#define TimerPeriodic    0x40
#define TimerPrescale0   0x00
#define TimerPrescale4   0x04
#define TimerPrescale8   0x08

/*****************************************************************************/
/*  Core Module Registers                                                    */
/*****************************************************************************/
#define CM_ID              ((volatile unsigned *)CoreBase)
#define CM_PROC            ((volatile unsigned *)(CoreBase + 0x004))
#define CM_OSC             ((volatile unsigned *)(CoreBase + 0x008))
#define CM_CTRL            ((volatile unsigned *)(CoreBase + 0x00C))
#define CM_STAT            ((volatile unsigned *)(CoreBase + 0x010))
#define CM_LOCK            ((volatile unsigned *)(CoreBase + 0x014))
#define CM_SDRAM           ((volatile unsigned *)(CoreBase + 0x020))
#define CM_IRQ_STAT        ((volatile unsigned *)(CoreBase + 0x040))
#define CM_IRQ_RSTAT       ((volatile unsigned *)(CoreBase + 0x044))
#define CM_IRQ_ENSET       ((volatile unsigned *)(CoreBase + 0x048))
#define CM_IRQ_ENCLR       ((volatile unsigned *)(CoreBase + 0x04C))
#define CM_SOFT_INTSET     ((volatile unsigned *)(CoreBase + 0x050))
#define CM_SOFT_INTCLR     ((volatile unsigned *)(CoreBase + 0x054))
#define CM_FIQ_STAT        ((volatile unsigned *)(CoreBase + 0x060))
#define CM_FIQ_RSTAT       ((volatile unsigned *)(CoreBase + 0x064))
#define CM_FIQ_ENSET       ((volatile unsigned *)(CoreBase + 0x068))
#define CM_FIQ_ENCLR       ((volatile unsigned *)(CoreBase + 0x06C))
#define CM_SPD_BASE        ((volatile unsigned *)(CoreBase + 0x100))

/*****************************************************************************/
/*  LED Control Registers & Idle Bit                                         */
/*****************************************************************************/
#define LED_ALPHA          (volatile unsigned *)0x1A000000
#define LED_LIGHTS         (volatile unsigned *)0x1A000004
#define LED_SWITCHES       (volatile unsigned *)0x1A000008
#define LED_IDLE           0x01
#endif

