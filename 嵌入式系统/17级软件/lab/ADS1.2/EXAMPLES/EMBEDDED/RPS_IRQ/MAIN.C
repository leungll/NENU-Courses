/*
** Copyright (C) ARM Limited, 2000. All rights reserved.
*/


/*
** This example illustrates a RPS-based interrupt-driven timer, suitable for
** embedded applications.  This has a main() function, which initializes and
** starts two RPS timers.  When a timer expires, an interrupt is generated.
**
** The interrupt is handled in int_handler.c, which simply sets a flag and
** clears the interrupt.  The interrupt flags are checked below in a
** do-forever loop.  If a flag is set, a message is displayed, and the flag
** is then cleared.
**
** This can be compiled/linked on its own and executed in the semihosting 
** environment (in this case, Install_Handler is called to install the 
** interrupt vector).
**
** Alternatively it can be built as an embedded application with no semihosting
** (#define EMBEDDED, or compile with -DEMBEDDED).  When built as an embedded 
** application, this program uses __use_no_semihosting_swi to ensure that no 
** functions which use semihosting SWIs are linked in from the C library.
*/

#include <stdio.h>
#include <stdlib.h>
#include "stand_i.h"

#include "rpsarmul.h"       /* EITHER: to use with the ARMulator */
/* #include "intgrt.h" */   /* OR: to use with the Integrator board */


int IntCT1 = 0;
int IntCT2 = 0;
int Count  = 0;

#ifndef EMBEDDED
extern IRQ_Handler(void);
unsigned *irqvec = (unsigned *)0x18;
unsigned Install_Handler (unsigned routine, unsigned *vector)

  /* Updates contents of 'vector' to contain branch instruction */
  /* to reach 'routine' from 'vector'. Function return value is */
  /* original contents of 'vector'. */
  /* NB: 'Routine' must be within range of 32MB from 'vector'.  */

{ unsigned vec, oldvec;
  vec = ((routine - (unsigned)vector - 0x8)>>2);
  if (vec & 0xff000000)
  {
    printf ("Installation of Handler failed");
    exit(1);
  }
  vec = 0xea000000 | vec;
  oldvec = *vector;
  *vector = vec;
  return (oldvec);
}
#endif


/*
   Enabling and disabling interrupts
   Interrupts are enabled or disabled by reading the cpsr flags
   and updating bit 7. 

   These functions work only in a privileged mode, because the 
   control bits of the cpsr and spsr cannot be changed while in
   User mode.
*/

__inline void enable_IRQ(void)
{
  int tmp;
  __asm
  {
    MRS tmp, CPSR
    BIC tmp, tmp, #0x80
    MSR CPSR_c, tmp
  }
}

__inline void disable_IRQ(void)
{
  int tmp;
  __asm
  {
    MRS tmp, CPSR
    ORR tmp, tmp, #0x80
    MSR CPSR_c, tmp
  }
}


#ifdef EMBEDDED
extern void init_serial_A(void);
#endif


int main(void)
{
#ifdef EMBEDDED
  #pragma import(__use_no_semihosting_swi)  // ensure no functions that use semihosting 
                                            // SWIs are linked in from the C library
#ifdef USE_SERIAL_PORT
  init_serial_A();            // Initialize serial port A
#endif
#endif

  printf("RPS Timer Interrupt Example\n");

#ifdef EMBEDDED
#ifdef ROM_RAM_REMAP
  printf("Embedded (ROM/RAM remap, no SWIs) version\n");
#else
  printf("Embedded (ROM at 0x0, no SWIs) version\n");
#endif
#else
  Install_Handler ((unsigned)IRQ_Handler, irqvec);

  printf("Normal (RAM at 0x8000, semihosting) version\n\n");
#endif

  printf("Initializing...\n");

  enable_IRQ();

  *IRQEnableClear = ~0;      // Clear/disable all interrupts

  *Timer1Control = 0;        // Disable counters by clearing the control bytes
  *Timer2Control = 0;

  *Timer1Clear = 0 ;         // Clear counter/timer interrupts by writing to
  *Timer2Clear = 0 ;         // The clear register - any data will work

  *Timer1Load = FAST_LOAD;        // Load counter values 
  *Timer2Load = MED_FAST_LOAD;    

  *Timer1Control = (TimerEnable   |   // Enable the Timer                  
                    TimerPeriodic |   // Periodic Timer producing interrupt
                    TimerPrescale8 ); // Set Maximum Prescale - 8 bits     

  *Timer2Control = (TimerEnable   |   // Enable the Timer                  
                    TimerPeriodic |   // Periodic Timer producing interrupt
                    TimerPrescale8 ); // Set Maximum Prescale - 8 bits     

  *IRQEnableSet = IRQTimer1 | IRQTimer2; // Enable the counter timer interrupts

  printf("Running...\n");

  IntCT1 = 0;          // Clear CT 1 Flag
  IntCT2 = 0;          // Clear CT 2 Flag
  Count  = 0;

  while ( Count < 20 )
  {
    if (IntCT1 != 0)        // Timer 1 Interrupt occurred
    {
      Count++;
      printf("IntCT1\n");
      IntCT1 = 0;           // Reset the Timer 1 Interrupt Flag
    }
    if (IntCT2 != 0)        // Timer 2 Interrupt occurred
    {
      Count++;
      printf("IntCT2\n");
      IntCT2 = 0;           // Reset the Timer 2 Interrupt Flag
    }
  }

  disable_IRQ();
}

