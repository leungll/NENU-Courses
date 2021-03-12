/******************************************************************************
**                                                                           **
**  Copyright (c) 2000 ARM Limited                                           **
**  All rights reserved                                                      **
**                                                                           **
******************************************************************************/

/******************************************************************************
*                                                                             *
* The following are for the Integrator UART system. These are bits to enable  *
* the functions in the Command Registers and the individual masks for the     *
* returned Status registers                                                   *
* Register Bits - these require to be set to enable the defined functions     *
*                                                                             *
******************************************************************************/

#ifndef __UARTDEF
#define __UARTDEF

/*****************************************************************************/
/* UART Structure maps to register offsets                                   */
/* Structure is instantiated in UART.c and placed by scatter file            */
/*****************************************************************************/

struct uart
{ volatile unsigned dr;   // @0x0
  volatile unsigned ecr;  // @0x4
  volatile unsigned lcrh; // @0x8
  volatile unsigned lcrm; // @0x0c
  volatile unsigned lcrl; // @0x10
  volatile unsigned cr;   // @0x14
  volatile unsigned fr;   // @0x18
  volatile unsigned iir;  // @0x1C
};

/*****************************************************************************/
/* Received Status Register - RSR                                            */
/*****************************************************************************/
#define RSR_Overrun_Error   0x08
#define RSR_Break_Error     0x04
#define RSR_Parity_Error    0x02
#define RSR_Framing_Error   0x01

/*****************************************************************************/
/* Line Control High Byte Register - LCRH                                    */
/*****************************************************************************/
#define LCRH_Word_Length_8  0x60
#define LCRH_Word_Length_7  0x40
#define LCRH_Word_Length_6  0x20
#define LCRH_Word_Length_5  0x00
#define LCRH_Fifo_Enabled   0x10
#define LCRH_2_Stop_Bits    0x08
#define LCRH_Even_Parity    0x04
#define LCRH_Parity_Enable  0x02
#define LCRH_Send_Break     0x01

/*****************************************************************************/
/* Line Control Medium Byte Register - LCRM                                  */
/* This register specifies the high byte of the Baud rate divisor            */
/*****************************************************************************/
#define LCRM_Baud_460800  0x00
#define LCRM_Baud_230400  0x00
#define LCRM_Baud_115200  0x00
#define LCRM_Baud_76800   0x00
#define LCRM_Baud_57600   0x00
#define LCRM_Baud_38400   0x00
#define LCRM_Baud_19200   0x00
#define LCRM_Baud_14400   0x00
#define LCRM_Baud_9600    0x00
#define LCRM_Baud_2400    0x01
#define LCRM_Baud_1200    0x02

/*****************************************************************************/
/* Line Control Low Byte Register - LCRL                                     */
/* This register specifies the low byte of the Baud rate divisor             */
/*****************************************************************************/
#define LCRL_Baud_460800  0x01
#define LCRL_Baud_230400  0x03
#define LCRL_Baud_115200  0x07
#define LCRL_Baud_76800   0x0B
#define LCRL_Baud_57600   0x0F
#define LCRL_Baud_38400   0x17
#define LCRL_Baud_19200   0x2F
#define LCRL_Baud_14400   0x3F
#define LCRL_Baud_9600    0x5F
#define LCRL_Baud_2400    0x7F
#define LCRL_Baud_1200    0xFF

/*****************************************************************************/
/* Control Register - CR                                                     */
/*****************************************************************************/
#define CR_Loop_Back_En   0x80
#define CR_Timeout_Int_En 0x40
#define CR_TX_Int_Enable  0x20
#define CR_RX_Int_Enable  0x10
#define CR_ModStat_Int_En 0x08
#define CR_UART_Enable    0x01

/*****************************************************************************/
/* Flag Register - FR                                                        */
/*****************************************************************************/
#define FR_TX_Fifo_Empty  0x80
#define FR_RX_Fifo_Full   0x40
#define FR_TX_Fifo_Full   0x20
#define FR_RX_Fifo_Empty  0x10
#define FR_Busy           0x08
#define FR_Carrier_Detect 0x04
#define FR_Set_Ready      0x02
#define FR_Clear_To_Send  0x01

/*****************************************************************************/
/* Interrupt Identification Register - IIR                                   */
/*****************************************************************************/
#define IIR_RX_Time_Out   0x08
#define IIR_TX            0x04
#define IIR_RX            0x02
#define IIR_Modem         0x01

#endif
