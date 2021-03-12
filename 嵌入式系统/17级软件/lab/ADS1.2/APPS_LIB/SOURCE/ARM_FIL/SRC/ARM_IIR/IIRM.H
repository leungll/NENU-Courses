;/*
; * Infinite Impulse Response filter assembler macros
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
; Date         : 06/04/1995
;
; Update	   : 03/03/1998
;
;-----------------------------------------------------------------------

	INCLUDE	regchekm.h

;-----------------------------------------------------------------------
; IIR PowerUp
;
; Copies the coefficients (possibly from ROM) to RAM interleaving the
; states, which are zeroed to initialise.
;
;-----------------------------------------------------------------------
; Macro parameters:
;
;	$outPtr	= pointer to the next position in output coefficient/state data buffer
; 	$inPtr	= pointer to the next position in input coefficient data buffer
; 	$taps	= number of biquads
;			  number of coefficients in coefficient data buffer/4
; 	$c0		= temporary register to hold current coefficient 0
;	$c1		= temporary register to hold current coefficient 1
;	$c2		= temporary register to hold current coefficient 2
;	$c3		= temporary register to hold current coefficient 3
; 	$s0		= temporary register to hold current state 0
; 	$s1		= temporary register to hold current state 1
;
; Register restrictions:
;
;	$c0 < $c1 < $c2 < $c3 < $s0 < $s1
;
;-----------------------------------------------------------------------

	MACRO
$iirPU IIR_PowerUp_MACRO $outPtr, $inPtr, $taps, $c0, $c1, $c2, $c3, $s0, $s1

	ORDER $c0, $c1, $c2, $c3, $s0, $s1	; check LDM order

    MOV		$s0, #0
    MOV		$s1, #0

$iirPU.puLoop

	; Load current coefficients, possibly from ROM.
	LDMIA	$inPtr!, { $c0, $c1, $c2, $c3 }

	; Copy coefficients to  RAM and interleave states (zeroing delay).
    STMIA	$outPtr!, { $c0, $c1, $c2, $c3, $s0, $s1 }
                             ;
	; Do we have any more biquad's to do?
    SUBS	$taps, $taps, #1
    BGT		$iirPU.puLoop  ; If so then loop.

    MEND

;-----------------------------------------------------------------------
; IIR
;
;-----------------------------------------------------------------------
; Macro parameters:
;
;	$outPtr  	= pointer to the next position in output data buffer
; 	$inPtr  	= pointer to the next position in input data buffer
; 	$nInputs	= number of data points in input data buffer remaining
; 	$nBqs		= number of biquads left to do
;	$coeffsPtr	= pointer to coefficient/state data buffer
;	$in			= temporary register to hold current input data item
;	$c0			= temporary register to hold coefficient 0
;	$c1			= temporary register to hold coefficient 1
;	$c2			= temporary register to hold coefficient 2
;	$c3			= temporary register to hold coefficient 3
;	$s0			= temporary register to hold state 0
;	$s1			= temporary register to hold state 1
;	R12			= 
;	sp			= stack
;	$coefPtrCop	= copy of pointer to start of coefficient/state buffer
;
; Register restrictions:
;
;	$c0 < $c1 < $c2 < $c3 < $s0 < $s1
;	$in < $s0
;
;-----------------------------------------------------------------------

	MACRO
$iir	IIR_MACRO	$outPtr, $inPtr, $nInputs, $nBqs, $coeffsPtr, $in, $c0, $c1, $c2, $c3, $s0, $s1, $coefPtrCop

	ORDER $c0, $c1, $c2, $c3, $s0, $s1	; check LDM order
	ORDER $in, $s0
	
	STR	$nBqs, [sp, #-4]!	; store number of biquads onto stack

$iir.Outer_Loop
	LDR		$in, [$inPtr], #4			; Get the next input data value
	
	MOV		$coefPtrCop, $coeffsPtr		; Keep a copy of pointer to start of buffer
	

$iir.Inner_Loop
	; Load next biquad and state
	LDMIA	$coeffsPtr!, { $c0, $c1, $c2, $c3, $s0, $s1 }
	
	LCLS t
t	SETS "$in"							; $in is also used for $t as long as s0 = t before it becomes $in again

	LCLS tmp
tmp	SETS "$c2"							; $c2 is only used once then becomes temporary register

	; t = in + c2*s0
	MUL		$tmp, $s0, $c2
	ADD		$t, $in, $tmp, ASR #14
	
	; t = ( in + c2*s0 ) + c3*s1
	MUL		$tmp, $c3, $s1
	ADD		$t, $t, $tmp, ASR #14
	
	STMDB	$coeffsPtr, { $t, $s0 }		; Store s0 = t and s1 = s0
	
	; in = t + c0*s0
	MUL		$tmp, $c0, $s0
	ADD		$in, $t, $tmp, ASR #14
	
	; in = ( t + c0*s0 ) + c1*s1
	MUL		$tmp, $c1, $s1
	ADD		$in, $in, $tmp, ASR #14
	
	; Any more biquads to do?
	SUBS	$nBqs, $nBqs, #1
	BGT		$iir.Inner_Loop
	
	LDR	$nBqs, [sp]	; reload number of biquads

; -- $iir.Inner_Loop


	STR		$in, [$outPtr], #4		; Store the output value
	
	MOV		$coeffsPtr, $coefPtrCop	; Restore coefficient buffer pointer to start
	
	SUBS	$nInputs, $nInputs, #1	; Check outer input data loop
	BGT		$iir.Outer_Loop
	
	ADD		sp, sp, #4	; pop number of biquads from stack and ignore value
; -- $iir.Outer_Loop

    MEND

;-----------------------------------------------------------------------
; END
;
;-----------------------------------------------------------------------

    END

