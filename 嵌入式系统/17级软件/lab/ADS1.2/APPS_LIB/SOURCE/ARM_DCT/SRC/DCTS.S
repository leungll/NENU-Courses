;/*
; * Discrete Cosine Transform assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

; Highly optimised forward and inverse 2DIM DCT

; The 1 DIM 8 element FDCT
; ========================
;
; The 1 DIM 8 element DCT takes 8 inputs f(0)-f(7) and produces 8 outputs,
; T(0)-T(7).
;
; It is described by the formula:
;
; T(u) = C(u) (f(0)c(u,0) + ... + f(7)c(u,7))
;
; where C(u) = 1/(2*sqr(2)) if u=0  and  1/2 if u>0
; and   c(u,x) = cos( (2x+1)*u*pi/16 )
;
; The most efficient way of calculating it so far know is by Arai, Agui,
; and Nakajima and can be split up into stages as follows:
;
; Stage 1:
;		g(0) = f(0)+f(7)
;		g(1) = f(1)+f(6)
;		g(2) = f(2)+f(5)
;		g(3) = f(3)+f(4)
;		g(4) = f(3)-f(4)
;		g(5) = f(2)-f(5)
;		g(6) = f(1)-f(6)
;		g(7) = f(0)-f(7)
;
; Stage 2:
;		f(0) = g(0)+g(3)
;		f(3) = g(0)-g(3)
;
;		f(1) = g(1)+g(2)
;		f(2) = g(1)-g(2)
;
;		f(4) = g(4)+g(5)
;		f(5) = g(5)+g(6)
;		f(6) = g(6)+g(7)
;		f(7) = g(7)
;
; Stage 3:
;		g(0) = f(0)
;		g(1) = f(1)
;
;		g(2) = (f(2)+f(3)) * a1		(a1 = 1/sqr(2))
;		g(3) = f(3)
;
;		temp = (f(4)-f(6)) * a5	    (a5 = cos(3*pi/8))
;		g(4) = temp + f(4) * a2		(a2 = cos(pi/8)-cos(3*pi/8))
;		g(6) = temp + f(6) * a4		(a4 = cos(pi/8)+cos(3*pi/8))
;
;		temp = f(5) * a3			(a3 = 1/sqr(2))
;		g(5) = f(7) + temp
;		g(7) = f(7) - temp
;
; Stage 4:	(produce the Fourier transform results *8 and *16)
;		F(0) = g(0)+g(1)
;		F(4) = g(0)-g(1)
;		
;		F(2) = g(3)+g(2)
;		F(6) = g(3)-g(2)
;
;		F(5) = g(7)+g(4)
;		F(3) = g(7)-g(4)
;
;		F(1) = g(5)+g(6)
;		F(7) = g(5)-g(6)
;
; Stage 5:
;		T(0) = F(0)/2
;		T(u) = F(u)/sqr(2)/cos(pi*u/16)/2 == F(u) / ( sqr(2)*cos(pi*u/16)*2 )
;
; The key point being that the calculation to convert F to T can be
; done at the same time as the quantisation! This just leaves 5 multiplies
; for the main part of the DCT.
;
; Constants are	a1 = a3 = cos(pi/4) = 1/sqr(2)	= 0.707106781
;				a2 		= cos(pi/8)-cos(3*pi/8) = 0.5411961
;				a4 		= cos(pi/8)+cos(3*pi/8) = 1.30656297
;				a5 		= cos(3*pi/8) 			= 0.382683433
;
; And T(u) = F(u)/t(u)/2 where:
;
;		t(u) = 1 					if u=0
;		t(u) = sqr(2)*cos(pi*u/16) 	if u>0
;
; The 1 DIM 8 element RDCT
; ========================
;
; The reverse DCT algorithm can be found by reversing each step of the above algorithm.
; For example
;		F(1) = g(5)+g(6)
;		F(7) = g(5)-g(6)
; is reversed as:
;               g(5) = (F(1)+F(7)) / 2
;               g(6) = (F(1)-F(7)) / 2
; As an optimization the divisions by 2 are left out. Similarly, multiplications by N
; are replaced by 1/N and the rotation in stage 3 is reversed.
; The result is a reverse DCT which is almost lossless while only using 16 bit arithmetic.


; The 2 DIM 8x8 DCT
; =================
;
; Do 1 DIM DCT horizontally on very row then vertically on every column
; (or the other way around). Note that if the t(u) scalings are not
; done then you are left with a matrix of t(i)t(j) elements to divide
; by. This is the AANscales matrix.
;
; The horizontal DCT magnifies by sqrt(8) and the vertical by sqrt(8)
; so to normalise a right shift of 3 is needed after a horizontal or
; vertical DCT. For extra precision, an initial shift of 1 is included
; in the FDCT (result is 12 bit signed, upshifted by 1+3 bits)
; and 4 for the RDCT (result is 8 bit signed, upshifted by 4+3 bits).

; This implementation of the DCT is highly optimised and so may be hard to follow
; The code performs two DCT's at once on 16 bit data by storing them in the form
;
;	reg[n] = f0(n) + (f1(n)<<16)	for ARM code
;
;	reg[n].h = f1(n)	for PICCOLO code
;	reg[n].l = f0(n)
;
; where f0 and f1 are the two 8x8 arrays being transformed.
;
; Lines 0-7 of the flowgraph are kept in registers r0-r7. In order to save
; registers, registers r0-r3 are also used as temporaries when calculating
; on coefficients f4 - f7.
; The results are stored out in wierd orders (whatever is optimal from an ARM
; register allocation viewpoint) since the order can be corrected by the modifying
; the zig zag table. Hence the zig-zag table has become quite complicated.

	INCLUDE intworkm.h

FASTMUL EQU 0
        
        AREA    |C$$code|, CODE, READONLY $interwork
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	ARM MACROS		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

t0      RN  0
t1      RN  1
t2      RN  2
t3      RN  3
srce	RN  8	; source colour data
dst     RN  9	; destination output
quant   RN dst  ; quantization table pointer
q_ptr   RN t0
round   RN 10   ; DCT rounding value (0.5)
q_round RN 11   ; quantization rounding value (0.5)
bias	RN 11	; DC bias
const   RN 12   ; current multiplication constant
mask    RN 14   ; mask for merging 2 signed 16 bit values
dst_end RN t0
src_end RN t0

FDCT_SHIFT * 10 ; precision of FDCT coefficients after multiply
RDCT_SHIFT *  9 ; precision of RDCT coefficients after multiply

	; FAST MULTIPLY
	; take two combined values in $reg and multiply both by $val
	; uses MUL instruction and two temps
	; shift is the number of bits to shift right after the MUL
        MACRO
        MUL_F   $reg, $val, $tmp1, $tmp2, $shift
          MOVS    $tmp1, $reg, ASR #16			
          ADDCS   $tmp1, $tmp1, #1                  ; get high part of $reg
          MLA     $tmp2, $tmp1, $val, round			; multiply by $val
          SUB     $reg, $reg, $tmp1, LSL #16		; get low part of $reg
          MLA     $tmp1, $reg, $val, round			; multiply by $val
          AND     $tmp2, mask, $tmp2, LSL #16 - $shift
          ADD     $reg, $tmp2, $tmp1, ASR #$shift	; combine
        MEND

	; SLOW MULTIPLY by 724 = (sqrt(2) at q10)
	; For processor without fast multiplier
        MACRO
        MUL_S   $reg, $val, $tmp1, $tmp2, $shift
          MOVS    $tmp1, $reg, ASR #16
          ADDCS   $tmp1, $tmp1, #1					; tmp1 = top value
          SUB     $reg, $reg, $tmp1, LSL #16		; reg = bottom value
  
          ASSERT  $val = 724
          ADD     $tmp2, $reg, $reg, LSL #1
          RSB     $tmp2, $tmp2, $tmp2, LSL #4
          ADD     $tmp2, $reg, $tmp2, LSL #2		; tmp2 = reg * 181
          ADD     $tmp2, round, $tmp2, LSL #2		; *4 = 724
  
          ADD     $reg, $tmp1, $tmp1, LSL #1
          RSB     $reg, $reg, $reg, LSL #4
          ADD     $reg, $tmp1, $reg, LSL #2			; reg = tmp1 * 181
          ADD     $reg, round, $reg, LSL #2			; *4 = 724
  
          AND     $reg, mask, $reg, LSL #16 - $shift
          ADD     $reg, $reg, $tmp2, ASR #$shift	; combine
        MEND


	; Multiply 2 combined values ($reg1 and $reg2) by constant $val
        MACRO
        MUL2C  $reg1, $reg2, $val, $shift
          IF      FASTMUL = 1
            MOV     const, #$val					; fast multiply
            MUL_F   $reg1, const, t0, t1, $shift
            MUL_F   $reg2, const, t0, t1, $shift
          ELSE
            MUL_S   $reg1, $val, t0, t1, $shift		; slow multiply
            MUL_S   $reg2, $val, t0, t1, $shift
          ENDIF
        MEND

	; Multiply a single combined value in $reg by constant $val
        MACRO
        MULC  $reg, $val, $shift
          IF      FASTMUL = 1
            MOV     const, #$val
            MUL_F   $reg, const, t0, t1, $shift
          ELSE
            MUL_S   $reg, $val, t0, t1, $shift
          ENDIF
        MEND
        
        ; Peform rotation from step 3:
	; temp = (f(4)-f(6)) * a5	        (a5 = cos(3*pi/8))
	; g(4) = temp + f(4) * a2			(a2 = cos(pi/8)-cos(3*pi/8))
	; g(6) = temp + f(6) * a4			(a4 = cos(pi/8)+cos(3*pi/8))
	; here $r1 and $r2 are the unpacked values f(4) and f(6)
	; $val1 = cos(3*pi/8)
	; $val2 = cos(pi/8)
        MACRO
        ROT3_C  $r1, $r2, $t1, $t2, $val1, $val2
        SUB     $t1, $r1, $r2						; get 'temp'
        IF      FASTMUL = 1							; fast multiplier available
          MOV     const, #$val1
          MLA     $t2, $t1, const, round
          ADD     const, const, #$val2 - 2 * $val1	; $val2 - $val1
          MLA     $t1, $r1, const, $t2
          ADD     const, const, #$val1 * 2			; $val1 + $val2
          MLA     $t2, $r2, const, $t2
        ELSE										; no fast multiplier
          ASSERT ($val1 = 392) :LAND: ($val2 = 946)
          ADD   $t2, $t1, $t1, LSL #1
          ADD   $t2, $t1, $t2, LSL #4           	; t2 = t1 * 49 (392 >> 3)
          ADD   $t2, round, $t2, LSL #3

          RSB   $t1, $r1, $r1, LSL #5
          ADD   $t1, $t1, $t1, LSL #3
          SUB   $r1, $t1, $r1, LSL #1           	; r1 *= 277 (554 >> 1)

          RSB   $t1, $r2, $r2, LSL #3
          RSB   $t1, $r2, $t1, LSL #5
          ADD   $r2, $t1, $t1, LSL #1           	; r2 *= 669 (1338 >> 1)
          
          ADD   $t1, $t2, $r1, LSL #1
          ADD   $t2, $t2, $r2, LSL #1
        ENDIF
        MEND

	; Perform rotation from step 3 on COMBINED values in $reg1, $reg2
        MACRO
        ROTATE  $reg1, $reg2, $val1, $val2, $shift
        MOVS    t0, $reg1, ASR #16
        ADDCS   t0, t0, #1
        SUB     $reg1, $reg1, t0, LSL #16			; split reg1
        MOVS    t1, $reg2, ASR #16
        ADDCS   t1, t1, #1
        SUB     $reg2, $reg2, t1, LSL #16			; split reg2
        ROT3_C  t0, t1, t2, t3, $val1, $val2		; rotate 'high' values
        ROT3_C  $reg1, $reg2, t0, t1, $val1, $val2	; rotate 'low' values
        AND     t2, mask, t2, LSL #16 - $shift
        ADD     $reg1, t2, t0, ASR #$shift			; combine reg1
        AND     t3, mask, t3, LSL #16 - $shift
        ADD     $reg2, t3, t1, ASR #$shift			; combine reg2
        MEND

	; Compress quantize a pair of combined values
	; $reg = combined values
	; $ptr = current output ptr
        MACRO
        quantize $reg, $ptr
        LDR     t0, [quant], #4						; find next quant coef + zigzag
        MOVS    t1, $reg, ASR #16
        ADDCS   t1, t1, #1							; get high value
        AND     t2, t0, #&00FFFFFF					; extract quant coef
        MLA     t3, t1, t2, q_round					; quantise high (now shifted 16 up)
        SUB     $reg, $reg, t1, LSL #16				; extract low
        MLA     t2, $reg, t2, q_round				; quantise low
        AND     t3, mask, t3						; knock bottom bits off high
        ORR     $reg, t3, t2, LSR #16				; ORR-combine & shift down low 16
        STR     $reg, [$ptr, t0, ASR #22]			; save at t0-position
        MEND

	; Forward DCT part 1
        MACRO
        fdct_1
	; stage 1 for r0-r7
        ADD     r0, r0, r7
        SUB     r7, r0, r7, LSL #1
        ADD     r1, r1, r6
        SUB     r6, r1, r6, LSL #1
        ADD     r2, r2, r5
        SUB     r5, r2, r5, LSL #1
        ADD     r3, r3, r4
        SUB     r4, r3, r4, LSL #1
	; stage 2 for r0-r3
        ADD     r0, r0, r3
        SUB     r3, r0, r3, LSL #1
        ADD     r1, r1, r2
        SUB     r2, r1, r2, LSL #1
	; stage 3,4 for r0-r1
        ADD     r0, r0, r1
        SUB     r1, r0, r1, LSL #1
        ; r0-r1 now finished
        MEND

	; Forward DCT part 2
        MACRO
        fdct_2
	; stage 2 for r4-r7
        ADD     r4, r4, r5
        ADD     r5, r5, r6
        ADD     r6, r6, r7
        ; stage 3 for r2-r3,r5
        ADD     r2, r2, r3
        MUL2C   r2, r5, 724, FDCT_SHIFT
        ; stage 4 for r2-r3
        ADD     r2, r2, r3
        RSB     r3, r2, r3, LSL #1
	; r2-r3 now finished
        MEND
        
        ; Forward DCT part 3
        MACRO
        fdct_3
	; stage 3 for r4,r6
        ROTATE  r4, r6, 392, 946, FDCT_SHIFT
        ; stage 4 for r4-r7
        ADD     r5, r5, r7
        RSB     r7, r5, r7, LSL #1
        ADD     r4, r4, r7
        RSB     r7, r4, r7, LSL #1
        ADD     r5, r5, r6
        SUB     r6, r5, r6, LSL #1
        MEND

	; Reverse DCT part 1
        MACRO
        rdct_1
        ; invert stage 3,4 for r4-r7
        SUB     r4, r4, r7
        ADD     r7, r4, r7, LSL #1
        ADD     r5, r5, r6
        RSB     r6, r5, r6, LSL #1
        ROTATE  r4, r6, 392, 946, RDCT_SHIFT
        ADD     r7, r7, r5
        RSB     r5, r7, r5, LSL #1
        MULC    r5, 724, RDCT_SHIFT
        ADD     r6, r6, r7
        ADD     r5, r5, r6
        SUB     r4, r4, r5
        MEND

	; Reverse DCT part 2
        MACRO
        rdct_2
	; invert stages 4,3,2 for r2-r3
        SUBS    r2, r2, r3
        ADD     r3, r2, r3, LSL #1
        BEQ     %FT00									; >10% zero
        MULC    r2, 724, RDCT_SHIFT
00      ; mul finished
        SUB     r2, r2, r3
        MEND

	; Reverse DCT part 3
        MACRO
        rdct_3
	; invert rest of stages
        ADD     r0, r0, r1
        SUB     r1, r0, r1, LSL #1
        ADD     r0, r0, r3
        SUB     r3, r0, r3, LSL #1
        ADD     r1, r1, r2
        SUB     r2, r1, r2, LSL #1
        ADD     r0, r0, r7
        SUB     r7, r0, r7, LSL #1
        SUB     r1, r1, r6
        ADD     r6, r1, r6, LSL #1
        ADD     r2, r2, r5
        SUB     r5, r2, r5, LSL #1
        ADD     r3, r3, r4
        SUB     r4, r3, r4, LSL #1
        MEND
        
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Forward DCT - ARM                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; r0 = DCT buffer, 256 byte-aligned (input at r0, output at r0)
;      (shifts up to do horziontal then down again doing vertical+quant)
; r1 = MCU descriptor, with the number of 8x8 FDCTs to do. 
;      As the FDCT processes 2 blocks at a time, this number is rounded 
;      upwards to a multiple of 2.
; r2 = quantization array pointer, contains #blocks / 2 pointers to
;      quantization tables. The same table is used for each block pair

dctbuf	RN 0
mcudesc	RN 1
quanta	RN 2

        EXPORT  fdct_fast
fdct_fast
        STMFD   sp!, {R4-R11, R14}
        ADD     mcudesc, mcudesc, #1
        MOV     mcudesc, mcudesc, LSR #1			; get number of double 8x8 blocks
        ADD     srce, dctbuf, mcudesc, LSL #8		; END of source picture
        ADD     dctbuf, dctbuf, #32					; doing last row first!
        ADD     dst, dctbuf, mcudesc, LSL #8		; destination buffer end
        ADD     mcudesc, dctbuf, mcudesc, LSL #8	; dst_end
        STMFD   sp!, {dctbuf, mcudesc, quanta}
        MOV     mask, #255 << 16
        ORR     mask, mask, #255 << 24				; mask = 0xffff0000
        MOV     round, #1 << (FDCT_SHIFT - 1)		; round = 0.5
        MOV	bias, #1024 * 2
        ORR	bias, bias, bias, LSL #16
        ; Horizontal DCT loop (backwards from the last block)
fdct_nextrow
        LDMDB   srce!, {r0 - r7}					; load next 16 pixels - going BACKWARDS
        fdct_1
        SUB     r0, r0, bias						; subtract DC bias
        STR     r0, [dst, #-4]!						; save data in first block - going BACK
        STR     r1, [dst, #32*1]
        fdct_2
        STR     r2, [dst, #32*2]
        STR     r3, [dst, #32*3]
        fdct_3
        STR     r4, [dst, #32*4]
        STR     r5, [dst, #32*5]
        STR     r6, [dst, #32*6]
        STR     r7, [dst, #32*7]
        TST     dst, #0x1F
        BNE     fdct_nextrow						; still on same block
        LDR     dst_end, [sp, #0]					; get start of MCU buffer
        SUB     dst, dst, #256 - 32					; move back a block
        CMP     dst, dst_end						; finished?
        BHI     fdct_nextrow
        ADD     srce, dst, #256 - 32
        MOV     q_round, #1 << 15
        ; Vertical Block loop
fdct_nextcol1        
        LDR     q_ptr, [sp, #8]						; get ptr to array of quant ptrs
        LDR     quant, [q_ptr], #4					; get adr of quantization table
        STR     q_ptr, [sp, #8]						; store ptr to next quantization table
        ; Vertical 8xDCT loop
fdct_nextcol
        LDMIA   srce!, {r0 - r7}					; now go forward
        fdct_1
        STMDB   srce!, {r0, r1}
        fdct_2
        STMDB   srce!, {r2, r3}
        fdct_3
        quantize r4, srce							; funny order corrected by zig/zag
        quantize r5, srce
        quantize r6, srce
        quantize r7, srce
        LDMIA   srce!, {r4 - r7}
        quantize r4, srce        					; f2
        quantize r5, srce      						; f3
        quantize r6, srce        					; f0
        quantize r7, srce        					; f1
        TST     srce, #255
        BNE     fdct_nextcol						; in same block
        LDR     src_end, [sp, #4]					; end of data
        CMP     srce, src_end
        BLS     fdct_nextcol1						; next block
        ADD     sp, sp, #12							; 'pull' end markers
        RETURN "r4-r11","","",""	; return (rlist, sp, lr, no condition)
        

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Reverse DCT - ARM                     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; r0 = DCT input buffer (256 byte-aligned) input at r0 + 256, output at r0
; r1 = MCU descriptor, with the number of 8x8 RDCTs to do. 
;      As the FDCT processes 2 blocks at a time, this number is rounded 
;      upwards to a multiple of 2.

dctbuf	RN 0
mcudesc	RN 1

        EXPORT  rdct_fast
rdct_fast
        STMFD   sp!, {R4-R11, R14}
        ADD     mcudesc, mcudesc, #1
        MOV     mcudesc, mcudesc, LSR #1			; get number of double 8x8 blocks
        ADD     mcudesc, dctbuf, mcudesc, LSL#8		; get end mark
        STR     mcudesc, [sp, #-4]!					; stack it
        ADD     srce, mcudesc, #256					; points just behind the last input block
        ADD     dst, dctbuf, #256					; points to 2nd block
        MOV     mask, #255 << 16
        ORR     mask, mask, #255 << 24				; mask = 0xffff0000
        MOV     round, #1 << (RDCT_SHIFT - 1)		; round = 0.5
        ; Horizontal loop
        ; (this is actually inverse vertical as the zig/zag did a transpose)
        ; stored horizontally (so transposed) as well
rdct_nextrow
	LDMDB   srce!, {r4 - r7}
	ORRS    const, r4, r5
	ORREQS  const, r6, r7
        BNE     rdct_nonzero1						; if r4-r7 not all 0 do rotate
	LDMDB   srce!, {r0 - r3}
        ORRS    const, r2, r3
        ORREQS  const, r0, r1
        BNE     rdct_nonzero2						; if r0-r3 not all 0 do them
        ; all zero - skip row - don't even neeed to store
        TST     srce, #255							; reached the end?
        BNE     rdct_nextrow						; no
        B       rdct_nextblock						; yes
rdct_nonzero1
	rdct_1
	LDMDB   srce!, {r2, r3}
	SUB     srce, srce, #8
rdct_nonzero2
	rdct_2
	LDMIA   srce, {r0, r1}
	rdct_3
        STMIA   srce, {r0 - r7}
        TST     srce, #255
        BNE     rdct_nextrow
        ; Vertical block loop
rdct_nextblock        
        CMP     srce, dst
        BHI     rdct_nextrow
        SUB     dst, srce, #256
        ; Vertical column loop
        ; (actually the inverse horizontal transform)
        ; (matrix is transposed when read)
rdct_nextcol
        LDR     r4, [srce, #32*4]
        LDR     r5, [srce, #32*5]
        LDR     r6, [srce, #32*6]
        LDR     r7, [srce, #32*7]
        ORRS    const, r4, r5
        ORREQS  const, r6, r7
        BEQ     rdct_zero1
        rdct_1
rdct_zero1
        LDR     r2, [srce, #32*2]
        LDR     r3, [srce, #32*3]
        rdct_2
        LDR     r1, [srce, #32*1]
        LDR     r0, [srce], #4
        rdct_3
        STMIA   dst!, {r0 - r7}
        TST     dst, #255
        BNE     rdct_nextcol
        LDR     dst_end, [sp, #0]
        ADD     srce, srce, #256 - 32
        CMP     dst, dst_end
        BLO     rdct_nextcol
        ADD     sp, sp, #4								; unstack end pointer
        RETURN "r4-r11","","",""	; return (rlist, sp, lr, no condition)

        END
