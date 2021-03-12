;/*
; * Least Mean Square filter assembler macros
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

	INCLUDE	regchekm.h

;-----------------------------------------------------------------------
; LMS PowerUp
;
; Copies the coefficients (possibly from ROM) to RAM interleaving the
; states, which are zeroed to initialise.
;
;-----------------------------------------------------------------------
; Macro parameters:
;
;	$outPtr	= pointer to the next position in output coefficient/state data buffer
; 	$inPtr	= pointer to the next position in input coefficient data buffer
; 	$nCoeffs= number of coefficient data points in input data buffer remaining
; 	$c0		= temporary register to hold current coefficient 0
; 	$s0		= temporary register to hold current state 0
; 	$c1		= temporary register to hold current coefficient 1
; 	$s1		= temporary register to hold current state 1
;
; Register restrictions:
;
;	$c0 < $s0 < $c1 < $s1
;
;-----------------------------------------------------------------------

	MACRO
$lmsPU LMS_PowerUp_MACRO $outPtr, $inPtr, $nInputs, $c0, $s0, $c1, $s1

	ORDER $c0, $s0, $c1, $s1	; check LMD order

    MOV		$s0, #0
    MOV		$s1, #0

$lmsPU.puLoop

	; Load current coefficients, possibly from ROM.
	LDMIA	$inPtr!, { $c0, $c1 }

	; Copy coefficients to  RAM and interleave states.
    STMIA	$outPtr!, { $c0, $s0, $c1, $s1 }
                             ;
	; Do we have any more input's to do?
    SUBS	$nInputs, $nInputs, #2
    BGT		$lmsPU.puLoop  ; If so then loop.

    MEND

;-----------------------------------------------------------------------
; LMS
;
; Performs the real LMS filter given a set of inputs, desired values and
; coefficients & states.
;
;-----------------------------------------------------------------------
; Macro parameters:
;
;	$outPtr		= pointer to the next position in output data buffer
; 	$inPtr		= pointer to the next position in input data buffer
; 	$nInputs	= number of data points in input data buffer remaining
; 	$desPtr		= pointer to the next position in desired data buffer
; 	$out		= temporary register to hold next output data item
; 	$c0			= temporary register to hold coefficient 0
; 	$in			= temporary register to hold next input data item
; 	$tmp		= temporary register
; 	$s0			= adaption multiplier
;			  	  internally used as temporary register to hold state 0
; 	$c1			= temporary register to hold ceofficient 1
; 	$s1			= temporary register to hold state 1
; 	$err		= error
; 	$nCoeffs	= number of coefficients (used as counter, copy kept in stack)
; 	sp	 		= stack
; 	$coeffsPtr 	= pointer to the next coefficient data value
;	Stack		= adaptation multiplier
;			  	  tap counter (total number coefficients)
;
; Register restrictions:
;
;	$c0 < $in < $tmp < $s0 < $c1 < $s1
;	$s0 < $nCoeffs
;
;-----------------------------------------------------------------------

	MACRO
$lms	LMS_MACRO	$outPtr, $inPtr, $nInputs, $desPtr, $out, $c0, $in, $tmp, $s0, $c1, $s1, $err, $nCoeffs, $coeffsPtr

	ORDER $c0, $in, $tmp, $s0, $c1, $s1	; check LMD order
	ORDER $s0, $nCoeffs

	STMFD	sp!, { $s0, $nCoeffs }	; Store adaption rate and number of coefficients (taps)

	MOV		$tmp, #0				; Zero temp.
	MOV		$err, #0				; Zero Error.
	
$lms.Outer_Loop
	LDR		$in, [$inPtr], #4		; Get the next input data value
	
	MOV		$out, #0				; Set output = 0
	
$lms.Inner_Loop
	; Load next two coefficients and previous 2 (uncorrected values)
	LDMIA	$coeffsPtr, { $c0, $s0, $c1, $s1 }
	
	; Update (i)'th coefficient ie. c[ i ] = c[ i ] + ( err * adpt ) * s[ i - 1 ]
	MUL		$tmp, $s0, $err
	ADD		$c0, $c0, $tmp, ASR #14
	
	; Update (i+1)'th coefficient ie. c[ i + 1 ] = c[ i + 1 ] + ( err * adpt ) * s[ i ]
	MUL		$tmp, $s1, $err
	ADD		$tmp, $c1, $tmp, ASR #14
	
	; Note now:  $tmp = $c1, $c1 = temp (for STM ordering reasons)
	
	; Accumulate to output ie. output += c[ i ] * s[ i ]
	MUL		$c1, $in, $c0
	ADD		$out, $out, $c1, ASR #14
	
	; Accumulate to output ie. output += c[ i + 1 ] * s[ i - 1 ]
	MUL		$c1, $s0, $tmp
	ADD		$out, $out, $c1, ASR #14
	
	; Store c[ i ] and c[ i + 1 ] and update the s[ i ] delay line
	STMIA	$coeffsPtr!, { $c0, $in, $tmp, $s0 }
	MOV		$in, $s1
	
	; Loop until all nCoeffs are used
	SUBS	$nCoeffs, $nCoeffs, #2
	BGT		$lms.Inner_Loop
	
;-- $lms.Inner_Looop
	
	LDR		$tmp, [$desPtr], #4		; Get desired value
	SUB		$err, $tmp, $out		; Calculate error value
	
	LDMFD	sp, { $s0, $nCoeffs }	; Re-load taps value and adaptation coefficient
	
	MUL		$err, $s0, $err
	MOV		$err, $err, ASR #14		; Multiply error by adaption coefficient

	STR		$out, [$outPtr], #4		; Store the output value
	
	; Restore coefficient buffer pointer to start
	; Each loop read four entries from buffer = 16 bytes
	; Number of loops = nCoeffs/2
	; Thus each decrement of nCoeffs counts for 8 bytes (LSL #3)
	SUB		$coeffsPtr, $coeffsPtr, $nCoeffs, LSL #3
	
	SUBS	$nInputs, $nInputs, #1	; Check the outer input data loop
	BGT		$lms.Outer_Loop
	
;-- $lms.Outer_Loop

	; Move stack pointer to account for entries placed on at beginning
	ADD		sp, sp, #2*4

	MEND
	
;-----------------------------------------------------------------------
; LMS PowerDown
;
; Copies the changed coefficients back into a coefficient array removing
; unrequired state values.
;
;-----------------------------------------------------------------------
; Macro parameters:
;
;	$outPtr	= pointer to the next position in output coefficient data buffer
; 	$inPtr	= pointer to the next position in input coefficient/state data buffer
; 	$nCoeffs= number of coefficient data points in input data buffer remaining
;			  does not include number of states = 2 * $nCoeffs
; 	$c0		= temporary register to hold current coefficient 0
; 	$s0		= temporary register to hold current state 0
; 	$c1		= temporary register to hold current coefficient 1
; 	$s1		= temporary register to hold current state 0
;
; Register restrictions:
;
;	$c0 < $s0 < $c1 < $s1
;
;-----------------------------------------------------------------------

	MACRO
$lmsPD LMS_PowerDown_MACRO $outPtr, $inPtr, $nInputs, $c0, $s0, $c1, $s1

	ORDER $c0, $s0, $c1, $s1	; check LDM order

$lmsPD.pdLoop

	; Load current coefficients and states
	LDMIA	$inPtr!, { $c0, $s0, $c1, $s1 }

	; Copy coefficients removing states.
    STMIA	$outPtr!, { $c0, $c1 }
                             ;
	; Do we have any more input's to do?
    SUBS	$nInputs, $nInputs, #2
    BGT		$lmsPD.pdLoop  ; If so then loop.

    MEND

;-----------------------------------------------------------------------
; END
;
;-----------------------------------------------------------------------

   END
