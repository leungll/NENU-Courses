/*
** Copyright (C) ARM Limited, 2000. All rights reserved.
*/

/*
** This application flashes the LEDs on the ARM Integrator board.
** It reads the board's switches to determine the flash speed and pattern.
*/


#include <stdio.h>
#include "stand_i.h"

/* #include "rpsarmul.h" */ /* EITHER: to use with the ARMulator */
#include "intgrt.h"         /* OR: to use with the Integrator board */



int IntCT1;
int IntCT2;

char switch_val  = 17,  // Set out of range to ensure values
     cur_sw_val  = 0,   // are different at program start.
     sequence    = 0, 
     seq_init    = 0,
     count       = 0,
     flash_speed = 0, 
     toggle      = 0;


int  Read_Switch(void);
void Led_Write(char val);
void Init_Timers(void);
void Set_Timers(char time);


int main(void)
{
  #pragma import(__use_no_semihosting_swi)   // ensure no functions that use semihosting
                                             // SWIs are linked in from the C library

  Init_Timers();

  IntCT1 = 0;
  IntCT2 = 0;

  while (1)  // Continue flashing LEDs
  {
    // Read switches to see if they have been changed
    cur_sw_val = Read_Switch(); 

    if (switch_val != cur_sw_val)  // Switches have been changed
    {
      switch_val = cur_sw_val;

      flash_speed = switch_val & SPEED_MASK; // Update speed & sequence
      sequence = ((switch_val & SEQUENCE_MASK) >> SEQUENCE_SHIFT);

      seq_init = INIT_VALUE;       // Initialize new LED sequence

      Set_Timers(flash_speed);     // Set the sequence speed
    }

    if (IntCT1)          // Strobe the LEDs 
    {
      IntCT1 = 0;        // Reset the Timer 1 Interrupt Flag 
      Led_Write(count);  // Write the current LED State

      switch (sequence)
      {
        case BIN_COUNT:  // Binary Counter Sequence
          if (seq_init)
          {
            count = 0;
            seq_init = 0;
          }

          if (count > MAX_BIN_COUNT)
            count = 0;
          else
            count++;
          break;
          
        case LEFT_SHIFT:  // Single Bit Left Shift Sequence 
          if (seq_init)
          {
            count =  MIN_LED_VAL;
            seq_init =0;
          }

          if (count == MAX_LED_VAL)
            count = MIN_LED_VAL;
          else
            count <<= SHIFT_VALUE;
          break;

        case ALTERNATE:  // Two bit alternate pattern sequence 
          if (!toggle)
          {
            count = ALT_RIGHT;
            toggle++;
          }
          else
          {
            count = ALT_LEFT;
            toggle = 0;
          }
          break;

        case RIGHT_SHIFT:  // Single bit right shift sequence
          if (seq_init)
          {
            count = MAX_LED_VAL ;
            seq_init =0;
          }
          if (count == MIN_LED_VAL)
            count = MAX_LED_VAL;
          else
            count >>= SHIFT_VALUE;
          break;
      }
    }
  }
}


/**************************************************************************
* Read_Switch                                                             *
* This function reads the current switch setting.                         *
* The 2 least significant bits control the sequence speed, the upper 2    *
* bits control the sequence type. This module returns the full switch     *
* value.                                                                  *
**************************************************************************/
int Read_Switch(void)
{
  char switch_val;
  switch_val = (*LED_SWITCHES & 0x0F);
  return switch_val;
}


/**************************************************************************
* Led_Write                                                               *
* This function writes the current sequence to the LEDs                   *
**************************************************************************/
void Led_Write(char val)
{
  while (*LED_ALPHA & LED_IDLE)  // Wait until the LEDs are 
    ;                            // ready to be written to
  *LED_LIGHTS = val;
}


/**************************************************************************
* Init_Timers                                                             *
* Initializes the Interrupt and sets the counter timers to zero, also     *
* ensures that the Interrupts from the timers are fully reset.            *
**************************************************************************/
void Init_Timers(void)
{
  // Disable all interrupts
  *IRQEnableClear = ~0;

  // Disable counters by clearing the control bytes
  *Timer1Control = 0;
  *Timer2Control = 0;

  // Clear counter/timer interrupts by writing to the clear register
  *Timer1Clear = 0 ; // any data will work
  *Timer2Clear = 0 ; // any data will work
}


/**************************************************************************
* Set_Timers                                                              *
* This module controls the setting up and loading of the counter timers   *
* with the required time to set the sequence speed - a value of 0 - 3 is  *
* passed into the routine which decides the load value of the two timers. *
* The timer controls and interrupts are set on exit.                      *
***************************************************************************/
void Set_Timers(char time)
{
  // Select load time from input value 
  switch (time)
  {
    case SLOW:
      *Timer1Load = SLOW_LOAD;
      *Timer2Load = SLOW_LOAD;
      break;

    case SLOW_MED:
      *Timer1Load = SLOW_MED_LOAD;
      *Timer2Load = SLOW_MED_LOAD;
      break;

    case MED_FAST:
      *Timer1Load = MED_FAST_LOAD;
      *Timer2Load = MED_FAST_LOAD;
      break;

    case FAST:
      *Timer1Load = FAST_LOAD;
      *Timer2Load = FAST_LOAD;
      break;
  }

  // Set Up the Counter Timers Control Registers
  *Timer1Control = (TimerEnable   |   // Enable the Timer   
                    TimerPeriodic |   // Periodic Timer producing interrupt
                    TimerPrescale8 ); // Set Maximum Prescale - 8  bits    

  *Timer2Control = (TimerEnable   |   // Enable the Timer                  
                    TimerPeriodic |   // Periodic Timer producing interrupt
                    TimerPrescale8 ); // Set Maximum Prescale - 8  bits    

  // Now initialize the System Interrupts and Enable the Timer 1 Interrupt
  *IRQEnableClear = ~0;       // Clear all interrupts
  IntCT1 = 0;                 // Clear CT 1 Flag     
  IntCT2 = 0;                 // Clear CT 2 Flag     

  *IRQEnableSet = IRQTimer1 | IRQTimer2; 
  // Enable the counter timer interrupts
}

