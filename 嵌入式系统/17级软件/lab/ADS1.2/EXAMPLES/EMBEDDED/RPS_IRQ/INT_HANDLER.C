/**************************************************************/
/*     File: int_handler.c                                    */
/*  Purpose: IRQ interrupt handler code                       */
/**************************************************************/

/*
** Copyright (C) ARM Limited, 2000. All rights reserved.
*/


#include "stand_i.h"

#include "rpsarmul.h"       /* EITHER: to use with the ARMulator */
/* #include "intgrt.h" */   /* OR: to use with the Integrator board */



/******************************************************************************
* IRQHandler                                                                  *
*                                                                             *
* This function handles IRQ interrupts.  In this example, these may come from *
* Timer 1 or Timer 2.                                                         *
*                                                                             *
* This handler simply clears the interrupt and sets corresponding flags.      *
* These flags are then checked by the main application.                       *
*                                                                             *
*******************************************************************************/

void __irq IRQ_Handler(void)
{
  unsigned status;

  status = *IRQStatus;
  /* Deal with source of interrupt */
  /* RMC source definitions used for CT1, CT2 */

  if (status & IRQTimer1)
  {
    *Timer1Clear = 0;/* clear the interrupt */
    IntCT1++;        /* set the flag        */
  } 
  else if (status & IRQTimer2)
  {
    *Timer2Clear = 0;/* clear the interrupt */
    IntCT2++;        /* set the flag        */
  } 
}


