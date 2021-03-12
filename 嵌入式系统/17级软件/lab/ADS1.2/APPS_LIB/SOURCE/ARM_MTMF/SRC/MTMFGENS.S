;/*
; * Multi-Tone Multi-Frequency Tone Generate assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

; Test for halfword support
	GBLL	HALFWORD
	
HALFWORD SETL	:LNOT:( {ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M" )


;--------------------------------------------------------------------------
; Macros
;--------------------------------------------------------------------------

	; $rnd must have the value #1<<13
	MACRO
	GoertzelTone	$out, $cos, $w0, $w1, $rnd	; implementation of the Goertzel algorithm
		MLA		$out, $w0, $cos, $rnd		; w(n-1)*cos<<15
		RSB		$out, $w1, $out, ASR #14	; w(n) = 2*w(n-1)*cos - w(n-2)
		MOV		$w1, $w0					; w(n-2) = w(n-1)
		MOV		$w0, $out		       		; w(n-1)= w(n)
	MEND

;--------------------------------------------------------------------------
; Area Name	: TONE_GENERATOR_CODE
;--------------------------------------------------------------------------

	INCLUDE intworkm.h						; include interworking macros

	AREA    TONE_GENERATOR_CODE, CODE, READONLY $interwork

	EXPORT	ToneGenerateSetup
	EXPORT	ToneGenerate

;--------------------------------------------------------------------------
; Name 			: ToneGenerateSetup
; Description	: Initialises tone data
; inputs		- R0 pointer to tone data.
;				- R1 tone cosine value
;				  i.e cos(tone_frequency*2*PI/sampling_rate)<<15
;				- R2 tone sine value 
;				  i.e. sin(tone_frequency*2*PI/sampling_rate)<<15
;				- R3 maximum waveform peak level
; outputs		- modifies tone data
;--------------------------------------------------------------------------

ToneGenerateSetup
	STR		R1, [ R0 ], #4

	MUL		R3, R2, R3
	MOV		R3, R3, LSR #15
	STR		R3, [ R0 ], #4
	
	MOV		R3, #0
	STR		R3, [ R0 ]

	RETURN	"","","",""						; return (no rlist, sp, lr, no condition)


;--------------------------------------------------------------------------
; Name 			: ToneGenerate
; Description	: Generate tone data
; inputs   		- R0 is output pointer
; 				- R1 is number of samples
; 				- R2 is pointer to Tone data structure
; 				- R3 is number of tones to generate
; outputs		- modifies output array.
;--------------------------------------------------------------------------

ToneGenerate
	CMP		R1, #0							; if no samples to process return immediately
	RETURN	"","","","EQ"					; return (no rlist, sp, lr, equality)

	STMFD	sp!, { R4 - R10, lr }

	MOV		R9, R2							; copy tone data pointer
	MOV		R10, R3							; copy no of tones
	MOV		R12, #1<<13
	
SampleLoop
	MOV		R8, #0

	CMP		R3, #0							; if no tones to process bypass tone loop and store 0
	BEQ		NoTones

ToneLoop
	LDMIA   R2!, { R4 - R6 }				; load tone data
	GoertzelTone	R7, R4, R5, R6, R12
	ADD		R8, R8, R7
	STMDB	R2, { R5 - R6 }					; store tone data

	SUBS	R3,	R3, #1
	BHI 	ToneLoop
	
NoTones
	IF HALFWORD
		STRH	R8, [ R0 ], #2 
	ELSE
	    IF {ENDIAN} = "little"
			STRB	R8, [ R0 ], #1
			MOV		R8, R8, ROR #8
			STRB	R8, [ R0 ], #1
	    ELSE
			STRB	R8, [ R0, #1 ]
			MOV		R8, R8, ROR #8
			STRB	R8, [ R0 ], #2
	    ENDIF
	ENDIF
	MOV		R2, R9							; restore tone data pointer
	MOV		R3, R10							; restore no of tones count

	SUBS	R1, R1, #1
	BHI 	SampleLoop

	RETURN	"R4 - R10","","",""				; return (rlist, sp, lr, no condition)



	END
