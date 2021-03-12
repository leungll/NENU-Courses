;/*
; * Multi-Tone Multi-Frequency Tone Detect assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

; Test for long multiply and halfword support
	GBLL	HALFWORD
	GBLL	LMULTIPLY
	
HALFWORD SETL	:LNOT:( {ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M" )
LMULTIPLY SETL	:LNOT:( {ARCHITECTURE} = "3" )

;--------------------------------------------------------------------------
; Macro definitions required if long multiplies not supported
;--------------------------------------------------------------------------

	MACRO
	MultiplyS32byS16ASR	$RdHi, $RdLo, $Rs32, $Rs16, $x
		MOV		$RdHi, $Rs32, ASR #16
		BIC		$RdLo, $Rs32, $RdHi, LSL #16
		MUL		$RdHi, $Rs16, $RdHi
		MUL		$RdLo, $Rs16, $RdLo
		MOV		$RdLo, $RdLo, LSR #$x
		ADD		$RdHi, $RdLo, $RdHi, LSL #16-$x
	MEND

	MACRO
	MultiplyS32byS32toS64	$dl,$dh,$x,$y,$t0,$t1,$t2
		; extract y first - it may equal dl, dh or x
		MOV		$t1, $y, ASR #16
		BIC		$t0, $y, $t1, LSL #16
		MOV		$dh, $x, ASR #16
		BIC		$t2, $x, $dh, LSL #16
		
		MUL		$dl, $t0, $t2				; low x * low y
		MUL		$t0, $dh, $t0				; high x * low y
		MUL		$dh, $t1, $dh				; high y * high x
		MUL		$t1, $t2, $t1 				; low x * high y
		
		ADDS	$dl, $dl, $t0, LSL#16
		ADC		$dh, $dh, $t0, ASR#16
		ADDS	$dl, $dl, $t1, LSL#16
		ADC		$dh, $dh, $t1, ASR#16
	MEND

	MACRO
	SquareS32toS64	$dl,$dh,$x,$t0,$t1
		MOV		$t1, $x, ASR #16
		BIC		$t0, $x, $t1, LSL #16
		
		MUL		$dl, $t0, $t0				; low x * low y
		MUL		$t0, $t1, $t0				; high x * low y
		MUL		$dh, $t1, $t1				; high y * high x
		
		ADDS	$dl, $dl, $t0, LSL#17
		ADC		$dh, $dh, $t0, ASR#15
	MEND


;--------------------------------------------------------------------------
; Area Name : TONE_DETECT_CODE
;--------------------------------------------------------------------------

	INCLUDE intworkm.h						; include interworking macros

	AREA	TONE_DETECT_CODE, CODE, READONLY $interwork

	EXPORT	ToneDetectSetup
	EXPORT	ToneDetect
	EXPORT	ToneDetectResults
	
;--------------------------------------------------------------------------
; Name 			: ToneDetectSetup
; Description	: Initialises tone data
; inputs		- R0 pointer to tone data.
;				- R1 pointer to tone cosine values
;				  i.e cos(tone_frequency*2*PI/sampling_rate)<<15
;				- R2 no. of tones to process for.
; outputs		- modifies tone data
;--------------------------------------------------------------------------

ToneDetectSetup
	STMFD	sp!, { R4, lr }
	
	MOV		R3, #0
TDSLoop
	LDR		R4, [ R1 ], #4
	STR		R4, [ R0 ], #4

	STR		R3, [ R0 ], #4
	STR		R3, [ R0 ], #4

	SUBS	R2, R2, #1
	BNE		TDSLoop

	RETURN	"R4","","",""					; return (rlist, sp, lr, no condition)


;--------------------------------------------------------------------------
; Name 			: ToneDetect
; Description	: Accumulates individual tone energy	 
; inputs		- R0 pointer to input samples.
;				- R1 no. of samples to process.
;				- R2 pointer to tone data storage.
;				- R3 no. of tones to process for.
; outputs		- modifies tone data
;--------------------------------------------------------------------------

ToneDetect
	STMFD	sp!, { R4 - R11, lr } 
	MOV		R10, R3
	MOV		R11, R2

TDOuter	
	IF HALFWORD
		LDRSH	R4, [ R0 ], #2				; load sample value
	ELSE
		LDR		R4, [ R0 ], #2

		IF {ENDIAN} = "little"
			MOV	R4, R4, LSL #16
			MOV	R4, R4, ASR #16
		ELSE
			MOV	R4, R4, ASR #16
		ENDIF
	ENDIF	

TDInner
	LDMIA	R2, { R5 - R7 }					; load previous tone data cos, w[n-1], w[n-2]

	IF LMULTIPLY
		SMULL	R9, R8, R6, R5
		MOV		R9, R9, LSR #14
		ORR		R8, R9, R8, LSL #18
	ELSE
		MultiplyS32byS16ASR	R8, R9, R6, R5, 14 	; 2*cos*w[n-1]
	ENDIF

	SUB		R8, R8, R7						; 2*cos*w[n-1] - w[n-2]

	MOV		R7, R6							; w[n-2] = w[n-1]
	ADD		R6, R8, R4						; w[n-1] = w[n] + input

	STMIA	R2!, { R5 - R7 }				; save current tone data

	SUBS	R3, R3, #1						; decrement inner loop counter
	BHI		TDInner

	MOV		R3, R10							; restore inner loop counter
	MOV		R2, R11							; restore pointer to tone data
	SUBS	R1, R1, #1						; decrement samples counter	
	BHI		TDOuter

	RETURN	"R4 - R11","","",""				; return (rlist, sp, lr, no condition)


;--------------------------------------------------------------------------
; Name 			: ToneDetectRead
; Description	: Converts tone data in the individual tone energy	 
; inputs		- R0 pointer to output array.
;				- R1 tone data right shift value, used to avoid values overflowing.
;				- R2 pointer to tone data
;				- R3 no. of tones to calculate.
; outputs		- modifies output array.
;--------------------------------------------------------------------------

ToneDetectResults
	STMFD	sp!, { R4 - R11, lr }
	
TDRLoop
	LDMIA	R2!, { R6 - R8 }				; load tone data

	MOV		R7, R7, ASR R1					; scale tone data
	MOV		R8, R8, ASR R1	

	IF LMULTIPLY
		SMULL	R5, R9, R8, R6				; cos*w[n-2]<<15
		MOV		R5, R5, LSR #14	
		ORR		R9, R5, R9, LSL #18			; 2*cos*w[n-2]

		SMULL	R5, R6, R7, R9				; 2*cos*w[n-2]*w[n-1]
		SMULL	R9, R4, R7, R7				; w[n-1]*w[n-1]
		SMLAL	R9, R4, R8, R8				; w[n-1]*w[n-1] + w[n-2]+w[n-2]
		SUBS	R9, R9, R5					; w[n-1]*w[n-1]+w[n-2]*w[n-2]-2*w[n-1]*w[n-2]*cos
		SBC		R4, R4, R6					; 64 bit sub
	ELSE
		MultiplyS32byS16ASR		R9, R5, R8, R6, 14		; 
		MultiplyS32byS32toS64	R5, R6, R7, R9, R4, R10, R11	; 2*cos*w[n-2]

		SquareS32toS64	R9, R4, R7, R10, R11	; w[n-1]*w[n-1]
		SUBS	R9, R9, R5					; w[n-1]*w[n-1]+w[n-2]*w[n-2]-2*w[n-1]*w[n-2]*cos
		SBC		R4, R4, R6					; 64 bit subtract

		SquareS32toS64	R5, R6, R8, R10, R11	; w[n-2]*w[n-2]
		ADDS	R9, R9, R5					; w[n-1]*w[n-1]+w[n-2]*w[n-2]-2*w[n-1]*w[n-2]*cos
		ADC		R4, R4, R6					; 64 bit add
	ENDIF

	STR		R9, [ R0 ], #4					; store 32 result
	SUBS	R3, R3, #1				
	BHI		TDRLoop							; loop back for the next tone

	RETURN	"R4 - R11","","",""				; return (rlist, sp, lr, no condition)



	END
