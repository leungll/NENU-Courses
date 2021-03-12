;/*
; * Finite Impulse Response filter assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

; Block filter FIR in ARM

	INCLUDE intworkm.h

	AREA sBlkFir,CODE $interwork

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; MAIN BLOCK FILTER CODE			;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Entry: R0 = pointer to output correlation
;        R1 = pointer to intput data
;	     R2 = pointer to coeficients
;	     R3 = number of outputs (any number)
;	     [SP] = number of coefs (any number)
;	          = number of valid data items (any number)
; Exit:  R4-R11 preserved
;
; Does the FIR making sure not to run out of valid data

; inputs
corr	RN 0
data	RN 1
coefs	RN 2
ndata	RN 3
len		RN 4		; filter length (ncoefs)
dlen	RN 5
; internal
sum0	RN 9
sum1	RN 10
sum2	RN 11
sum3	RN 12

	EXPORT	s_blk_fir_rhs
s_blk_fir_rhs
	MOV	r12, sp
	STMFD	sp!,{R4-R11,R14}
	LDMIA	r12, {len, dlen}
	; finished C header
	SUBS	ndata, ndata, #4	; try doing a block of 4
	BLT	%F03			; can't
00	; do blocks of 4 loop
	BL	s_blk_fir_rhs_prim_zero
	STMIA	corr!, {sum0, sum1, sum2, sum3}	; save results
	ADD	data, data, #4*4	; move on 4 items
	SUB	dlen, dlen, #4		; data now 4 shorter
	SUBS	ndata, ndata, #4	; try doing 4 more
	BGE	%B00			; can do it
03	; finished block FIR's
	ADDS	ndata, ndata, #4	; number left
	BLE	%F02			; none - finished
01	; do one at a time loop
	BL	s_fir_rhs_prim_zero
	STR	sum0, [corr], #4
	ADD	data, data, #4
	SUB	dlen, dlen, #1
	SUBS	ndata, ndata, #1
	BGT	%B01
02	; C unheader
	RETURN "r4-r11","","",""	; return (rlist, sp, lr, no condition)
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; BLOCK FILTER PRIMATIVE		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
; Block filter with right hand edge detection (primative)
; Performs 4 filters at once

; Entry:
data	RN 1		; address of input data
coefs	RN 2		; address of coefs
len		RN 4		; filter length (ncoefs)
dlen	RN 5		; data length (for right hand edge detection)
sum0	RN 9		; current sums (usually zeroed)
sum1	RN 10
sum2	RN 11
sum3	RN 12
; On exit sums are updated
; R0-R8 saved

; inner loop
co0		RN 0
data	RN 1
coefs	RN 2
co1		RN 3
len		RN 4
co2		RN 5
x0		RN 6
x1		RN 7
x2		RN 8
sum0	RN 9		; current sums (usually zeroed)
sum1	RN 10
sum2	RN 11
sum3	RN 12
SP		RN 13
count	RN 14

s_blk_fir_rhs_prim_zero
	MOV	sum0,#0
	MOV	sum1,#0
	MOV	sum2,#0
	MOV	sum3,#0			; zero the counts
s_blk_fir_rhs_primative
	STMFD	sp!, {R0-R8, R14}
	LDMIA	data!,{x0,x1,x2}	; fill input data buffer
	SUBS	count, dlen, #3		; did we have this many elements
	BLT	%F10			; can't do any
	CMP	count, len
	MOVGT	count, len		; number of diagonal FIR's to do
	SUB	len, len, count		; number left afterwards
	SUBS	count, count, #3	; try doing 3 more
	BLT	%F02			; can't
01	; Do a main 4x3 diagonal block, use 3 coefs and 3 datas
	LDMIA	coefs!,{co0,co1,co2}
	MLA	sum0,co0,x0,sum0
	MLA	sum0,co1,x1,sum0
	MLA	sum0,co2,x2,sum0
	MLA	sum1,co0,x1,sum1
	MLA	sum1,co1,x2,sum1
	MLA	sum2,co0,x2,sum2
	LDMIA	data!,{x0,x1,x2}
	MLA	sum1,co2,x0,sum1
	MLA	sum2,co1,x0,sum2
	MLA	sum2,co2,x1,sum2
	MLA	sum3,co0,x0,sum3
	MLA	sum3,co1,x1,sum3
	MLA	sum3,co2,x2,sum3	; finish processing next coefs
	SUBS	count, count, #3	; can we do another 3?
	BGE	%B01			; can do another block
02	; finished blocks of 3
	ADDS	count, count, #3	; number left
	BLE	%F04			; finished the diagonals
03	; do another diagonal
	LDR	co0, [coefs], #4	; load next coef
	MLA	sum0,co0,x0,sum0
	MLA	sum1,co0,x1,sum1
        MLA	sum2,co0,x2,sum2
        MOV	x0, x1
        MOV	x1, x2
        LDR	x2, [data], #4
        MLA	sum3,co0,x2,sum3
        SUBS	count, count, #1
        BGT	%B03
04	; finished all the full diagonals
	CMP	len, #0			; anything left to do?
        BLE	%F06			; no
        ; Some coefs left. Therefore we've run out of data.
        LDMIA	coefs!,{co0,co1,co2}	; load next 3 coefs
        CMP	len, #2
	MLA	sum0,co0,x0,sum0
	MLA	sum1,co0,x1,sum1
        MLA	sum2,co0,x2,sum2	; first row
        MLAGE	sum0,co1,x1,sum0
        MLAGE	sum1,co1,x2,sum1
        MLAGT	sum0,co2,x2,sum0	; now exhausted data
06	; finished the next four results
	RETURN "r0-r8","","",""	; return (rlist, sp, lr, no condition)
10	; special seeding of data buffer for very small dlen
	CMP	dlen, #1
	MOV	x2, #0
	MOVLE	x1, #0
	MOVLT	x0, #0
	B	%B04
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; SINGLE FILTER PRIMATIVE		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
; Single filter with right hand edge detection (primative)

; Entry:
data	RN 1		; address of input data
coefs	RN 2		; address of coefs
len		RN 4		; filter length (ncoefs)
dlen	RN 5		; data length (for right hand edge detection)
sum0	RN 9		; current sum (usually zeroed)
; On exit sum is updated
; R0-R8 R10-R12 saved

; inner loop
co0		RN 0
data	RN 1
coefs	RN 2
co1		RN 3
len		RN 4
co2		RN 5
x0		RN 6
x1		RN 7
x2		RN 8
sum0	RN 9		; current sums (usually zeroed)
; 10, 11 free
co3		RN 12
x3		RN 14

s_fir_rhs_prim_zero
	MOV	sum0,#0
s_fir_rhs_primative
	STMFD	sp!, {R0-R8, R12, R14}
	CMP	len, dlen
	MOVGT	len, dlen		; length of the filter
	SUBS	len, len, #4		; try doing 4 more
	BLT	%F02			; can't
01	; Main do next 4 coefs block
	LDMIA	coefs!,{co0,co1,co2, co3}
	LDMIA	data!, {x0,x1,x2,x3}
	MLA	sum0,co0,x0,sum0
	MLA	sum0,co1,x1,sum0
	MLA	sum0,co2,x2,sum0
	MLA	sum0,co3,x3,sum0
	SUBS	len, len, #4		; can we do another 4?
	BGE	%B01			; can do another block
02	; finished blocks of 4
	ADDS	len, len, #4		; number left
	BLE	%F04			; finished the diagonals
03	; finish off
	LDR	co0, [coefs], #4	; load next coef
	LDR	x0, [data], #4
	MLA	sum0,co0,x0,sum0
        SUBS	len, len, #1
        BGT	%B03
04	; finished
	RETURN "r0-r8,r12","","",""	; return (rlist, sp, lr, no condition)
	
;;;;;;;;;;;;;;;;;;;;;;;;;
; END OF CODE		;
;;;;;;;;;;;;;;;;;;;;;;;;;
	
	END
