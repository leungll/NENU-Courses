;/*
; * IS-54-B Convolutional Encoder assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;---Convolutional Encoder-----------------------------------------------
;
; Purpose   : An implementation of the IS-54 FEC speech Convolutional 
;             encoder
;
; Date      : 1/4/98
;
;-----------------------------------------------------------------------
;
; EXPORTs and AREA directive

	; load of halfword operations is required which has specific instructions defined in architecture 4 or later
	; if architecture 4 or later is not available other instructions must be used to simulate the halfword instructions
	;
	; define, therefore, a flag which sets the instructions as appropriate for the architecture supported
	GBLL	ARCHITECTURE_4
	
ARCHITECTURE_4 SETL	:LNOT:({ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M")

		INCLUDE intworkm.h

        AREA    |C$$Code|, CODE, READONLY, REL $interwork
        EXPORT  |ConvolutionalEncoder|



;-----------------------------------------------------------------------
; Include the file holding the macro definitions.

        INCLUDE	is54cem.h

;==ConvolutionalEncoder=================================================
;
; Purpose : An implementation of the IS-54 FEC speech convolutional 
;           encoder.
;
; On Entry:
;
;  R0  = pointer to output data buffer.
;  R1  = pointer to input data buffer (6 shorts of data followed by a 0)
;-----------------------------------------------------------------------
;
; Register usage:
;  R0  = pointer to next place to write output word.
;  R1  = pointer to next place to read input word from.
;  R2  = count down of the number of input bytes left to process.
;  R3  = I[n+1]<<16 | I[n]
;  R4  = Mask 0x0F000F00
;  R5  = Mask 0x30303030
;  R6  = Mask 0x44444444
;  R7  = G0
;  R8  = G1
;  R9  =
;  R10 =
;  R11 = 
;  R12 = 
;  R13 = stack register.
;  R14 = link register (used for internal subroutines as well).


|ConvolutionalEncoder|
	STMFD  sp!, { R4-R8, lr } ; Save state, (APCS subroutine entry).

	; Get the address of the bit masks, and then load them.
	ADR    R4, ConvEnc_Mask1
	LDMIA  R4, { R4, R5, R6 }

	; Get Input[n] - and place at top two bytes,
	; so that when we enter the loop below it is where we want it.
	IF ARCHITECTURE_4
		LDRH   R3, [ R1 ], #2
	ELSE
		LDR    R3, [ R1 ], #2
	ENDIF
	
	IF {ENDIAN} = "little" :LOR: ARCHITECTURE_4
		MOV	R3, R3, LSL #16
	ENDIF
 
	; Initialise inputs to six (extra input already read in)
	MOV	   R2, #6

00 ; Outer Loop 

	; Get Input[n+1] and only keep 16-bits
	IF ARCHITECTURE_4
		LDRH    R7, [ R1 ], #2
	ELSE
		LDR    R3, [ R1 ], #2
	ENDIF
	
	IF {ENDIAN} = "big" :LAND: :LNOT: ARCHITECTURE_4
		MOV	R7, R7, LSR #16
	ENDIF
 
	MOV    R7, R7, LSL #16

	; And combine with Input[n] which we already have.
	ORR    R3, R7, R3, LSR #16

 	;                         		In, G0, G1, msk1, msk2, msk3, out
	ConvolutionalEncoderKernelMacro R3, R7, R8, R4,   R5,   R6,   R7

	; Time to save our word of data, and to start on a new one.
	STR    R7, [ R0 ], #4

	; Have we any more input bytes to do?
	SUBS   R2, R2, #1  

	BGT    %BT00 ; Outer loop

	RETURN "r4-r8","","",""	; return (rlist, sp, lr, no condition)

;..Static Data............................................................
; Static data here (the three masks)              = 3 words (12 bytes)
; Total Static data (including passed parameters) = 6 words (24 bytes).

; Three words taken up by the bit masks to be used.
ConvEnc_Mask1  DCD 0x0F000F00
ConvEnc_Mask2  DCD 0x30303030
ConvEnc_Mask3  DCD 0x44444444

;=========================================================================

	END

