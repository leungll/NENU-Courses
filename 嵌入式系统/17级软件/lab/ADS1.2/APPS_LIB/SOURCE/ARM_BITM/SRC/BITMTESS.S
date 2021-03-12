;/*
; * Bit Manipulation assembler test harness
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	INCLUDE intworkm.h

outputarg	RN 0
outputarg2	RN 1

inputarg	RN 0
inputarg2	RN 1
inputarg3	RN 2
inputarg4	RN 3

; internal register names

output		RN 0
output2		RN 7

input		RN 1
input2		RN 2
input3		RN 3
input4		RN 4
input5		RN 5
input6		RN 6
input7		RN 7

constant	RN 8
constant2	RN 9
constant3	RN 10
constant4	RN 11

temp		RN 12
temp2		RN 14

	; include code fragment macros

	INCLUDE	bitmanm.h
	
	; generic macro for initialisation

	MACRO
		INIT	$name, $inargs, $outargs, $arguments, $const1, $const2, $const3, $const4

		EXPORT	init_$name
		EXPORT	call_$name
		EXPORT	end_$name

init_$name	; initialise the registers before macro call
		STMFD	sp!, { R4-R12, lr }		; save APCS registers
		
		ADD temp, sp, #40				; put stack back to prior to saving register states
		IF $inargs > 4					; load off 4, 5, 6 since input 7 placed first on stack
			LDMFD	temp!, { input5 }
		ENDIF
		IF $inargs > 5
			LDMFD	temp!, { input6 }
		ENDIF
		IF $inargs > 6
			LDMFD	temp!, { input7 }
		ENDIF
		IF $inargs > 3
			MOV input4, inputarg4
		ENDIF
		IF $inargs > 2
			MOV input3, inputarg3
		ENDIF
		IF $inargs > 1
			MOV input2, inputarg2
		ENDIF
		MOV	input, inputarg
		
		IF "$const1" <> ""
			LDR	constant, $const1
		ENDIF
		IF "$const2" <> ""
			LDR	constant2, $const2
		ENDIF
		IF "$const3" <> ""
			LDR	constant3, $const3
		ENDIF
		IF "$const4" <> ""
			LDR	constant4, $const4
		ENDIF

call_$name	; call the macro
    	$name $arguments

end_$name	; save results of macro call
		
		MOV outputarg, output
		IF $outargs > 1
			MOV	outputarg2, output2
		ENDIF

		RETURN "r4-r12","","",""	; return (rlist, sp, lr, no condition)
	MEND
	

	AREA	|INITCODE|, CODE $interwork
	
	; initialisation routines for each maths macro
	; parameters are:
	;	macro name
	;	number of input arguments
	;	argument list (given in "" so that entire list is passed to macro asis)
	
	INIT	BCDADD,		2, 1, "output, input, input2, temp, constant, constant2", =0x33333333, =0x88888888

	INIT	BITREV,		1, 1, "output, input, temp, constant"
	INIT	BITREVC,	1, 1, "output, input, temp, constant, constant2, constant3, constant4", =0xFFFF00FF, =0x0F0F0F0F, =0x33333333, =0x55555555

	INIT	BYTEREV,	1, 1, "output, input, temp"
	INIT	BYTEREVC,	1, 1, "output, input, temp, constant", =0xFFFF00FF

	INIT	BYTEWISEMAX, 2, 2, "output, output2, input, input2, temp, constant", =0x01010101

	INIT	LSBSET,		1, 1, "output, input, temp"
	INIT	MSBSET,		1, 1, "output, input, temp"

	INIT	POPCOUNT,	1, 1, "output, input, temp, constant, constant2", =0x49249249, =0xC71C71C7
	INIT	POPCOUNT7,  7, 1, "output, input, input2, input3, input4, input5, input6, input7, constant, constant2, constant3", =0x55555555, =0x33333333, =0x0F0F0F0F

	END
