/******************************************************************************
**                                                                           **
** Copyright (c) 2001 ARM Ltd All rights reserved                            **
**                                                                           **
** This header file defines the base addresses and offsets for the           **
** RPS peripherals of the ARMulator and ARM PID development board.           **
** (derived from rps.h and pid7t.h)                                          **
**                                                                           **
*******************************************************************************/

#ifndef RPSDEF_H
#define RPSDEF_H

/*******************************************************************************/
/*  Base addresses for standard memory-mapped peripherals                      */
/*******************************************************************************/
#define IntBase         0x0A000000  /* Interrupt Controller Base               */
#define TimerBase       0x0A800000  /* Counter/Timer Base                      */
#define ResetBase       0x0B000000  /* Reset and Pause Controller Base         */
                                    /* (for PID board only, not for ARMulator) */

/*******************************************************************************/
/*  Add extra sources defined for PID Interrupt Controller                     */
/*******************************************************************************/
#define IRQCardA        0x0040
#define IRQCardB        0x0080
#define IRQSerialA      0x0100
#define IRQSerialB      0x0200
#define IRQParallel     0x0400
#define IRQASBex0       0x0800
#define IRQASBex1       0x1000
#define IRQAPBex0       0x2000
#define IRQAPBex1       0x4000
#define IRQAPBex2       0x8000

/*******************************************************************************/
/* FIQ source register                                                         */
/*******************************************************************************/
#define FIQSourceIRQ   ((volatile unsigned *)(IntBase + 0x114))

/*******************************************************************************/
/* RPS interrupt Controller IRQ register                                       */
/*******************************************************************************/
#define IRQStatus      ((volatile unsigned *)IntBase)
#define IRQRawStatus   ((volatile unsigned *)(IntBase + 0x04))
#define IRQEnable      ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableSet   ((volatile unsigned *)(IntBase + 0x08))
#define IRQEnableClear ((volatile unsigned *)(IntBase + 0x0c))
#define IRQSoft        ((volatile unsigned *)(IntBase + 0x10))

/*******************************************************************************/
/* RPS interrupt sources                                                       */
/*******************************************************************************/
#define IRQUser         0x0001
#define IRQProgrammed   0x0002
#define IRQCommsRx      0x0004
#define IRQCommsTx      0x0008
#define IRQTimer1       0x0010
#define IRQTimer2       0x0020

#define FIQStatus      ((volatile unsigned *)(IntBase + 0x100))
#define FIQRawStatus   ((volatile unsigned *)(IntBase + 0x104))
#define FIQEnable      ((volatile unsigned *)(IntBase + 0x108))
#define FIQEnableSet   ((volatile unsigned *)(IntBase + 0x108))
#define FIQEnableClear ((volatile unsigned *)(IntBase + 0x10c))

/*******************************************************************************/
/*  Counter/timer registers                                                    */
/*******************************************************************************/
#define Timer1Load       ((volatile unsigned *)TimerBase)
#define Timer1Value      ((volatile unsigned *)(TimerBase + 0x04))
#define Timer1Control    ((volatile unsigned *)(TimerBase + 0x08))
#define Timer1Clear      ((volatile unsigned *)(TimerBase + 0x0C))

#define Timer2Load       ((volatile unsigned *)(TimerBase + 0x020))
#define Timer2Value      ((volatile unsigned *)(TimerBase + 0x024))
#define Timer2Control    ((volatile unsigned *)(TimerBase + 0x028))
#define Timer2Clear      ((volatile unsigned *)(TimerBase + 0x02C))

/*******************************************************************************/
/* Counter/Timer control register bits                                         */
/*******************************************************************************/
#define TimerEnable      0x80
#define TimerPeriodic    0x40
#define TimerPrescale0   0x00
#define TimerPrescale4   0x04
#define TimerPrescale8   0x08
#define TimerDisable     0
#define TimerCyclic      0x00

/*******************************************************************************/
/*  Reset and Wait Control Registers                                           */
/*******************************************************************************/
#define WaitMode           ((volatile unsigned *)ResetBase)
#define Identification     ((volatile unsigned *)(ResetBase + 0x010))
#define ClearResetMap      ((volatile unsigned *)(ResetBase + 0x020))
#define ResetStatus        ((volatile unsigned *)(ResetBase + 0x030))
#define ResetStatusSet     ((volatile unsigned *)(ResetBase + 0x030))
#define ResetStatusClear   ((volatile unsigned *)(ResetBase + 0x034))

/*******************************************************************************/
/* Power on reset Bit                                                          */
/*******************************************************************************/
#define ResetStatusPOR  0x01

#endif

