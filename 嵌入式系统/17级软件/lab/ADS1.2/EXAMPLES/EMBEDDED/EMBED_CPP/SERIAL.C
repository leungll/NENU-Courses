/*
** Copyright (C) ARM Limited, 2001. All rights reserved.
*/


/*
** This implements a simple (polled) RS232 serial driver for the 
** ARM Integrator Board.
**
** It outputs single characters on Serial Port A at 34800 Baud, 
** 8 bit, no parity, 1 stop bit.
**
** Initialize the port with init_serial_A() before calling sendchar().
**
** To monitor the characters output, use a null-modem cable to 
** connect Serial Port A to an RS232 terminal or PC running a 
** terminal emulator, e.g. HyperTerminal.
*/

#include "intgrt.h"      
#include "uart.h"

extern struct uart uart0;

#define UART0_DR   uart0.dr
#define UART0_RSR  uart0.dr
#define UART0_ECR  uart0.ecr
#define UART0_LCRH uart0.lcrh
#define UART0_LCRM uart0.lcrm
#define UART0_LCRL uart0.lcrl
#define UART0_CR   uart0.cr
#define UART0_FR   uart0.fr
#define UART0_IIR  uart0.iir
#define UART0_ICR  uart0.iir


void init_serial_A(void) 
{
  /* First set the correct baud rate and word length */
  
  UART0_LCRL = LCRL_Baud_38400;       // LCRL and LCRM writes _MUST_
                                      // be performed before the LCRH
  UART0_LCRM = LCRM_Baud_38400;       // write as LCRH generates the
                                      // write strobe to transfer the
  UART0_LCRH = LCRH_Word_Length_8 |   // data.
               LCRH_Fifo_Enabled;     // 

  /* Now enable the serial port */
                                      
  UART0_CR   = CR_UART_Enable;        // Enable UART0 with no interrupts
}


void sendchar( char *ch )
{
  while (UART0_FR & FR_TX_Fifo_Full)
    ;
  if (*ch == '\n')                    // Replace line feed with '\r'
    *ch = '\r';                       
  UART0_DR = *ch;                    // Transmit next character
}

