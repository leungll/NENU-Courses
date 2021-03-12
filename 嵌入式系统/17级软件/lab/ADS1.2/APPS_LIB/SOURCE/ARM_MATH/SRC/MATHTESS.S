;/*
; * Mathematics assembler test
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	INCLUDE intworkm.h

; Initialises the Maths Macros to provides C linkable routines

; register names

arg0	RN 0	; pointer to first arg (lowest first)
arg1	RN 1	; pointer to second arg (lowest first)

; internal register names

t0		RN 0	; temp
t1		RN 1

const	RN 0	; constant register when no temporary

t2		RN 5	; extra temp for cube root
t3		RN 6
t4		RN 7

z0		RN 4	; output arg 0
z1		RN 5

w0		RN 6	; output arg 1
w1		RN 7

x0		RN 8	; input argument 0
x1		RN 9

y0		RN 10	; input argument 1
y1		RN 11

; define extra temporary macros for non-ARM Architecture 3M or 4 environment

mul_temp_0	RN	2
mul_temp_1	RN	3
mul_temp_2	RN	12

	; include maths macros

	INCLUDE	mathsm.h
	
	; generic macro for initialisation

	MACRO
		INIT	$name, $inargs, $outargs, $reglist, $const

		EXPORT	init_$name
		EXPORT	call_$name
		EXPORT	end_$name

init_$name	; initialise the registers before macro call
		STMFD	sp!, { R4-R12, lr }	; save APCS registers
		
		; load input arguments
		IF $inargs >= 1
	  		LDMIA	arg0, { x0, x1 }
		ENDIF

		IF $inargs >= 2
	  		LDMIA	arg1, { y0, y1 }
		ENDIF
	
		STMFD	sp!, { arg0, arg1 }

		IF "$const" <> ""
			LDR	const, $const
		ENDIF

call_$name	; call the macro
    	$name $reglist

end_$name	; save results of macro call
		LDMFD	sp!, { arg0, arg1 }

		IF $outargs >= 1
	  		STMIA	arg0, { z0, z1, w0, w1 } ; all four outputs for case of 128-bit result
		ENDIF

		IF $outargs >= 2
	  		STMIA	arg1, { w0, w1 }
		ENDIF

		RETURN "r4-r12","","",""	; return (rlist, sp, lr, no condition)
	MEND
	

	AREA	CODE, CODE $interwork

	; initialisation routines for each maths macro
	; parameters are:
	;	macro name
	;	number of input arguments
	;	number of output arguments
	;	argument list (given in "" so that entire list is passed to macro asis)
	;	(optional) constant value
	
	INIT	ADDABS,				2, 1,	"z0, x0, y0"
	INIT	SIGNSAT,			2, 1,	"z0, x0, y0, const", =0x80000000
	
	INIT	UMUL_32x32_64,		2, 1, 	"z0, z1, x0, y0"
	INIT	SMUL_32x32_64,		2, 1, 	"z0, z1, x0, y0"
	INIT	MUL_64x64_64,		2, 1, 	"z0, z1, x0, x1, y0, y1"
	INIT	UMUL_64x64_128,		2, 1, 	"z0, z1, w0, w1, x0, x1, y0, y1, t0, t1"
	INIT	SMUL_64x64_128,		2, 1, 	"z0, z1, w0, w1, x0, x1, y0, y1, t0, t1"
	
	INIT	UDIV_32d16_16r16,	2, 2, 	"z0, w0, x0, y0"
	INIT	SDIV_32d16_16r16,	2, 2, 	"z0, w0, x0, y0, t0"
	INIT	UDIV_32d32_32r32,	2, 2, 	"z0, w0, x0, y0"
	INIT	SDIV_32d32_32r32,	2, 2, 	"z0, w0, x0, y0, t0"
	INIT	UDIV_64d32_32r32,	2, 2, 	"z0, w0, x0, x1, y0"
	INIT	SDIV_64d32_32r32,	2, 2, 	"z0, w0, x0, x1, y0, t0"
	INIT	UDIV_64d64_64r64,	2, 2, 	"z0, z1, w0, w1, x0, x1, y0, y1, t0"
	INIT	SDIV_64d64_64r64,	2, 2, 	"z0, z1, w0, w1, x0, x1, y0, y1, t0, t1"
	
	INIT	SQR_32_16r17,		1, 2, 	"z0, w0, x0, t0"
	INIT	CBR_32_11,			1, 1,	"z0, x0, t0, t1, t2, t3, t4"
	
	INIT	UDIVF_32d32_32,		2, 1, 	"z0, x0, y0, 16, 32"
	INIT	SDIVF_32d32_32,		2, 1, 	"z0, x0, y0, 16, 32, t0"

	INIT	ARMCOS,				1, 1,	"z0, x0, t0, t1, 14, 1"
	INIT	ARMSIN,				1, 1,	"z0, x0, t0, t1, 14, 1"

	END
