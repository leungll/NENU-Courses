;/*
; * Least Mean Square filter assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;-----------------------------------------------------------------------
; Least Mean Square (LMS)
;
;-----------------------------------------------------------------------
; Purpose      : An implementation of a real LMS filter.
;
; Precision    : 16-bit fixed point precision (from 32-bit words).
;
; Restrictions : Does two taps at a time, so the number of taps should
;                be a multiple of 2.
;
; Comments	   : The coefficients and the delay line are interleaved to
;                increase the sequentiality of data transfer (set up by
;				 the power up code).
;
;                The coefficients are updated at the start of the
;                loop rather than at the end. Thus the coefficients of the
;                ARM code after n inputs will be the same as the coefficients
;                of the C code after (n-1) inputs. The first time through
;                the loop the ARM code updates the coefficients with a zero
;                error value (which doesn't change them). This method therefore
;                requires that the error value is stored between invocations
;                in a register.
;
; Date         : 20/12/95.
;
; Update	   : 03/03/1998
;
;-----------------------------------------------------------------------

	INCLUDE intworkm.h

;-----------------------------------------------------------------------
; Assembler directives (specifies memory areas and makes the
; subroutines available to the linker).
;
;-----------------------------------------------------------------------

	AREA    |C$$Code|, CODE, READONLY, REL $interwork
	EXPORT	|LMS_PowerUp|
	EXPORT  |LMS|
	EXPORT	|LMS_PowerDown|
	
	INCLUDE	lmsm.h    ; Get the macros for the LMS algorithm

;-----------------------------------------------------------------------
; LMS PowerUp Outer Support Code
;
; Copies the coefficients (possibly from ROM) to RAM interleaving the
; states, which are zeroed to initialise.
;
;-----------------------------------------------------------------------
; On entry:
;
;	R0  	= pointer to the output coefficient/state data buffer
;	R1  	= pointer to the input coefficient data buffer
;	R2  	= number of coefficient data points in input data buffer (multiple of 2)
;	R3  	= 
;
;-----------------------------------------------------------------------
; Register usage:
;
;	R0  	= pointer to the next position in output coefficient/state data buffer
; 	R1  	= pointer to the next position in input coefficient data buffer
; 	R2  	= number of coefficient data points in input data buffer remaining
; 	R3  	= temporary register to hold current coefficient 0
; 	R4  	= temporary register to hold current state 0
; 	R5  	= temporary register to hold current coefficient 1
; 	R6  	= temporary register to hold current state 0
;
; Register restrictions:
;
;	$c0 < $s0 < $c1 < $s1
;
;-----------------------------------------------------------------------

|LMS_PowerUp|
	; Subroutine entry (ARM Procedure Calling Standard - APCS)
    STMFD    sp!, { R4-R6, lr }		; Save state (subroutine entry)

	; Use LMS Power Up Macro Code
	;                 outPtr, inPtr, nCoeffs, c0, s0, c1, s1
	LMS_PowerUp_MACRO R0,     R1,    R2,      R3, R4, R5, R6


	; Subroutine return (ARM Procedure Calling Standard - APCS)
	RETURN "r4-r6","","",""	; return (rlist, sp, lr, no condition)

;-----------------------------------------------------------------------
; LMS Outer Support Code
;
;-----------------------------------------------------------------------
; On entry:
;
;	R0  	= pointer to the output data buffer
;	R1  	= pointer to the input data buffer
;	R2  	= number of data points in input data buffer
;	R3  	= pointer to the desired data buffer
;	Stack	= adapt rate
;			  number of coefficients (multiple of 2)
;				(not number coefficients & states = 2 * number coefficients)
;			  pointer to the coefficient/state data buffer
;
;-----------------------------------------------------------------------
; Register usage:
;
;	R0  	= pointer to the next position in output data buffer
; 	R1  	= pointer to the next position in input data buffer
; 	R2  	= number of data points in input data buffer remaining
; 	R3  	= pointer to the next position in desired data buffer
; 	R4  	= temporary register to hold next output data item
; 	R5  	= temporary register to hold coefficient 0
; 	R6  	= temporary register to hold next input data item
; 	R7	 	= temporary register
; 	R8		= adaption multiplier
;			  internally used as temporary register to hold state 0
; 	R9 		= temporary register to hold ceofficient 1
; 	R10  	= temporary register to hold state 1
; 	R11 	= error
; 	R12 	= number of coefficients (used as counter, copy kept in stack)
; 	R13 	= stack
; 	R14 	= pointer to the next coefficient data value
;	Stack	= adaptation multiplier
;			  tap counter (total number coefficients)
;
; Register restrictions:
;
;	$c0 < $in < $tmp < $s0 < $c1 < $s1
;	$s0 < $nCoeffs
;
;-----------------------------------------------------------------------

|LMS|
	; Subroutine entry (ARM Procedure Calling Standard - APCS)
	STMFD    sp!, { R4-R12, lr }	; Save state (subroutine entry).

	; Stack pointer has moved by the number of registers stored in subroutine entry, 10
	; Each register is of size one word = 32-bits = 4-bytes
	ADD      R6, sp, #10*4			; Get stack pointer position for inputs
	; Load the other parameters off the stack into registers
	LDMFD    R6, { R8, R12, R14 }	
	
	;			outPtr, inPtr, nInputs, desPtr, out, c0, in, tmp, s0, c1, s1,  err, nCoeffs, coeffsPtr
	LMS_MACRO	R0,     R1,    R2,      R3,     R4,  R5, R6, R7,  R8, R9, R10, R11, R12,     R14

	; Subroutine return (ARM Procedure Calling Standard - APCS)
	RETURN "r4-r12","","",""	; return (rlist, sp, lr, no condition)

;-----------------------------------------------------------------------
; LMS PowerDown Outer Support Code
;
; Copies the changed coefficients back into a coefficient array removing
; unrequired state values.
;
;-----------------------------------------------------------------------
; On entry:
;
;	R0  	= pointer to the output coefficient data buffer
;	R1  	= pointer to the input coefficient/state data buffer
;	R2  	= number of coefficient data points in input data buffer (multiple of 2)
;	R3  	= 
;
;-----------------------------------------------------------------------
; Register usage:
;
;	R0  	= pointer to the next position in output coefficient data buffer
; 	R1  	= pointer to the next position in input coefficient/state data buffer
; 	R2  	= number of coefficient data points in input data buffer remaining
;			  does not include number of states = 2 * R2 if included
; 	R3  	= temporary register to hold current coefficient 0
; 	R4  	= temporary register to hold current state 0
; 	R5  	= temporary register to hold current coefficient 1
; 	R6  	= temporary register to hold current state 0
;
; Register restrictions:
;
;	$c0 < $s0 < $c1 < $s1
;
;-----------------------------------------------------------------------

|LMS_PowerDown|
	; Subroutine entry (ARM Procedure Calling Standard - APCS)
    STMFD    sp!, { R4-R6, lr }		; Save state (subroutine entry)

	; Use LMS Power Down Macro Code
	;                   outPtr, inPtr, nCoeffs, c0, s0, c1, s1
	LMS_PowerDown_MACRO R0,     R1,    R2,      R3, R4, R5, R6

	; Subroutine return (ARM Procedure Calling Standard - APCS)
	RETURN "r4-r6","","",""	; return (rlist, sp, lr, no condition)

;-----------------------------------------------------------------------
; END
;
;-----------------------------------------------------------------------
	
	END

