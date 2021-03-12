;/*
; * Infinite Impulse Response filter assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;-----------------------------------------------------------------------
; Infinite Impulse Response (IIR)
;
;-----------------------------------------------------------------------
; Purpose      : An implementation of a real IIR filter.
;
; Precision    : 16-bit fixed point precision (from 32-bit words).
;
; Restrictions : Four coefficients are used at a time (biquad) thus the
;				 number of coefficients given should be a multiple of 4.
;
; Comments	   : The coefficients for each biquad and the delay lines 
;				 are interleaved such that the sequence of coefficients and
;                states is { c0, c1, c2, c3, s0, s1 }.  This interleaving
;				 is set up by the PowerUp code.
;
; Date         : 07/04/95.
;
; Update	   : 03/03/1998
;
;-----------------------------------------------------------------------

	INCLUDE intworkm.h

; Assembler directives (specifies memory areas and makes the
; subroutines available to the linker).
;
;-----------------------------------------------------------------------

	AREA	|C$$Code|, CODE, READONLY, REL $interwork
	EXPORT	|IIR_PowerUp|
	EXPORT	|IIR|

	INCLUDE	iirm.h    ; Include the IIR macros definition.

;-----------------------------------------------------------------------
; IIR PowerUp Outer Support Code
;
; Copies the coefficients (possibly from ROM) to RAM interleaving the
; states, which are zeroed to initialise.
;
;-----------------------------------------------------------------------
; On entry:
;
;	R0  	= pointer to the output coefficient/state data buffer
;	R1  	= pointer to the input coefficient data buffer
;	R2  	= number of biquads
;			  number of coefficient data points in input data buffer/4
;	R3  	= 
;
;-----------------------------------------------------------------------
; Register usage:
;
;	R0  	= pointer to the next position in output coefficient/state data buffer
; 	R1  	= pointer to the next position in input coefficient data buffer
; 	R2  	= biquad counter
; 	R3  	= temporary register to hold current coefficient 0
; 	R4  	= temporary register to hold current coefficient 1
; 	R5  	= temporary register to hold current coefficient 2
; 	R6  	= temporary register to hold current coefficient 3
; 	R7  	= temporary register to hold current state 0
; 	R8  	= temporary register to hold current state 1
;
; Register restrictions:
;
;	$c0 < $c1 < $c2 < $c3 < $s0 < $s1
;
;-----------------------------------------------------------------------

|IIR_PowerUp|
	; Subroutine entry (ARM Procedure Calling Standard - APCS)
    STMFD    sp!, { R4-R8, lr }		; Save state (subroutine entry)

	; Use IIR Power Up Macro Code
	;                 outPtr, inPtr, nBq, c0, c1, c2, c3, s0, s1
	IIR_PowerUp_MACRO R0,     R1,    R2,  R3, R4, R5, R6, R7, R8

	; Subroutine return (ARM Procedure Calling Standard - APCS)
	RETURN "r4-r8","","",""	; return (rlist, sp, lr, no condition)

;-----------------------------------------------------------------------
; IIR Outer Support Code
;
;-----------------------------------------------------------------------
; On entry:
;
;	R0  	= pointer to the output data buffer
;	R1  	= pointer to the input data buffer
;	R2  	= number of data points in input data buffer
;	R3  	= number of biquads
;           = number of coefficients in coefficient buffer/4
;			  not number of coefficients & states = 6 * biquad
;	Stack	= pointer to the coefficient/state data buffer
;
;-----------------------------------------------------------------------
; Register usage:
;
;	R0  	= pointer to the next position in output data buffer
; 	R1  	= pointer to the next position in input data buffer
; 	R2  	= number of data points in input data buffer remaining
; 	R3  	= number of biquads left to do
;	R4		= pointer to coefficient/state data buffer
;	R5		= temporary register to hold current input data item
;	R6		= temporary register to hold coefficient 0
;	R7		= temporary register to hold coefficient 1
;	R8		= temporary register to hold coefficient 2
;	R9		= temporary register to hold coefficient 3
;	R10		= temporary register to hold state 0
;	R11		= temporary register to hold state 1
;	R12		= 
;	R13		= stack
;	R14		= copy of pointer to start of coefficient/state buffer
;
; Register restrictions:
;
;	$c0 < $c1 < $c2 < $c3 < $s0 < $s1
;	$in < $s0
;
;-----------------------------------------------------------------------

|IIR|
	; Subroutine entry (ARM Procedure Calling Standard - APCS)
	STMFD   sp!, { R4-R11, lr }		; Save state (subroutine entry)

	LDR		R4, [ sp, #9*4 ]		; Set the pointer to coefficients.

	;			outPtr, inPtr, nInputs, nBqs, coeffsPtr, in, c0, c1, c2, c3, s0,  s1,  coefPtrCopy
    IIR_MACRO	R0,     R1,    R2,      R3,   R4,        R5, R6, R7, R8, R9, R10, R11, R14

	; Subroutine return (ARM Procedure Calling Standard - APCS)
	RETURN "r4-r11","","",""	; return (rlist, sp, lr, no condition)

;-----------------------------------------------------------------------
; END
;
;-----------------------------------------------------------------------
	
    END

