;/*
; * Mathematics assembler macros
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;==========================================================================
;  ARM Maths routines
;==========================================================================
;
;  Version : 0.15  Dated: 6/3/97
;
;==========================================================================
; This source file contains ARM algorithms for standard maths operations.
; Each is implemented in the form of a MACRO so that it can inlined.
;
; CONTENTS:
;
;	INTEGER:
;	 c = a + abs(b)				32+32=32
;	 Signed-satured addition	32+32=32
;	 MULTIPLY					32x32=64, 64x64=64, 64x64=128
;	 DIVIDE						32/16=16, 32/32=32, 64/32=32, 64/64=64
;	 SQUARE ROOT				sqr(32)=16
;	 CUBE ROOT					cbr(32)=11
;
;	FIXED POINT:
;	 DIVIDE						32/32=32
;    SINE						sin(32)=32
;    COSINE						cos(32)=32
;

	INCLUDE regchekm.h

; The algorithms assume that ARM architecture 3M or 4 is available - with the
; long multipy instructions. If not then the next line is set to false to
; define replacements for _SMULL and _UMULL. If SMULL and UMULL are not
; available then extra registers will be needed. These are labelled
; mull_temp_* and must be free. They must be defined in an external file
; BEFORE including this file.

	GBLL	LONG_MULT
LONG_MULT SETL	:LNOT:({ARCHITECTURE} = "3") ; TRUE if ARM architecture 3M or 4 (or later) is avialable

	GBLA	k	; general counter

	IF :LNOT:LONG_MULT
	; need extra registers so check they have been defined
	 ASSERT	mul_temp_0>=0
	 ASSERT	mul_temp_1>=0
	 ASSERT	mul_temp_2>=0
	ENDIF


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	BASIC MACROS				;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        ; separate a 32 bit value into 2xunsigned 16 bit values
        ; resh and resl must be different
        MACRO
$label  USplit16 $resl, $resh, $src
		DISTINCT $resh, $src
$label  MOV     $resh, $src, LSR #16
        BIC     $resl, $src, $resh, LSL #16
        MEND

        ; separate a 32 bit value into two 16 bit values
        ; high part signed, low part unsigned
        ; resh and resl must be different
        MACRO
$label  SSplit16 $resl, $resh, $src
		DISTINCT $resh, $src
$label  MOV     $resh, $src, ASR #16
        BIC     $resl, $src, $resh, LSL #16
        MEND
        
        ; add a 32 bit value to a 64 bit value, shifted up 16 unsigned
        MACRO
        UAdd16	$resl, $resh, $x
        ADDS	$resl, $resl, $x, LSL#16
        ADC	$resh, $resh, $x, LSR#16
        MEND

        ; add a 32 bit value to a 64 bit value, shifted up 16 signed
        MACRO
        SAdd16	$resl, $resh, $x
        ADDS	$resl, $resl, $x, LSL#16
        ADC	$resh, $resh, $x, ASR#16
        MEND

	; signed 32x32=64 and dl,dh,x must be distinct
	; dh.dl = x*y
	MACRO
	_SMULL	$dl, $dh, $x, $y
	DISTINCT $dl, $dh, $x
	IF LONG_MULT
	  SMULL	$dl, $dh, $x, $y
	ELSE
	  ; no hardware multiplier
	  ; extract y first - it may equal dl, dh or x
	  SSplit16	mul_temp_0, mul_temp_1, $y
	  SSplit16	mul_temp_2, $dh, $x
	  MUL		$dl, mul_temp_0, mul_temp_2	; low x * low y
	  MUL		mul_temp_0, $dh, mul_temp_0	; high x * low y
	  MUL		$dh, mul_temp_1, $dh		; high y * high x
	  MUL		mul_temp_1, mul_temp_2, mul_temp_1 ; low x * high y
	  SAdd16	$dl, $dh, mul_temp_0		; add one middle value
	  SAdd16	$dl, $dh, mul_temp_1		; add other middle value
	ENDIF
	MEND
	
	; unsigned 32x32=64 and dl,dh,x must be distinct
	; dh.dl = x*y
	MACRO
	_UMULL	$dl, $dh, $x, $y
	DISTINCT $dl, $dh, $x
	IF LONG_MULT
	  ; we have a hardware multiplier
	  UMULL	$dl, $dh, $x, $y
	ELSE
	  ; no hardware multiplier
	  ; extract y first - it may equal dl, dh or x
	  USplit16	mul_temp_0, mul_temp_1, $y
	  USplit16	mul_temp_2, $dh, $x
	  MUL		$dl, mul_temp_0, mul_temp_2	; low x * low y
	  MUL		mul_temp_0, $dh, mul_temp_0	; high x * low y
	  MUL		$dh, mul_temp_1, $dh		; high y * high x
	  MUL		mul_temp_1, mul_temp_2, mul_temp_1 ; low x * high y
	  UAdd16	$dl, $dh, mul_temp_0		; add one middle value
	  UAdd16	$dl, $dh, mul_temp_1		; add other middle value
	ENDIF
	MEND

;---------------------------------------------------------------
; c = a + abs(b)
; 2 cycles
;
;---------------------------------------------------------------
; $a, $b	input integers
; $c		output result of addition
;
; if b is positive then EORS sets c=b, carry=0 and the ADC sets 
; c=a+b
;
; if b is negative then EORS sets c=NOT(b), carry=1 and the ADC
; sets c=a+NOT(b)+1=a-b since NOT(b)+1 is the 2's complement of b
;
; Registers $a and $c must be distinct registers from each other.
; Registers $b and $c must be distinct registers from each other.
; Registers $a and $b need not be distinct from each
;
;---------------------------------------------------------------

	MACRO
	ADDABS	$c, $a, $b
		DISTINCT $c, $a
		DISTINCT $c, $b
		
		EORS $c, $b, $b, ASR #32 
	 	ADC $c, $a, $c
 	MEND
 	
;---------------------------------------------------------------
; c = Signed-Saturated(a+b)
; 2 cycles + 1 register constant
;
;---------------------------------------------------------------
; $a, $b	input integers
; $c		output result of addition
;
; constant = 0x80000000
;
; if there is no overflow then c=a+b and the second instruction 
; has no effect
;
; if there is a positive overflow then top bit of c will be 1 
; and so the EORVS instruction will move 
; 0x80000000^0xffffffff=0x7fffffff into c
;
; if there is a negative overflow then top bit of c will be 0 
; and so the EORVS instruction will move 0x80000000^0=0x80000000 
; into c. 
;
; Registers $c and $constant must be distinct registers from each other.
; Registers $a, $b and $constant need not be distinct from each other.
; Registers $a, $b and $c need not be distinct from each other.
;
;---------------------------------------------------------------

 	MACRO
	SIGNSAT	$c, $a, $b, $constant
		DISTINCT $c, $constant
		
	 	ADDS $c, $a, $b 
		EORVS $c, $constant, $c, ASR #31
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;						;
;	INTEGER MULTIPLICATION MACROS		;
;						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; unsigned 32x32 = 64
; al = low 32 bits of b*c
; ah = high 32 bits of b*c
; al, ah, b must be distinct registers

	MACRO
	UMUL_32x32_64 $al, $ah, $b, $c
	_UMULL	$al, $ah, $b, $c
	MEND
	
; signed 32x32 = 64
; as above but signed

	MACRO
	SMUL_32x32_64 $al, $ah, $b, $c
	_SMULL	$al, $ah, $b, $c
	MEND
	
; multiply 64x64 = 64 (same signed as unsigned)
; ah.al = bh.bl * ch.cl
; al, ah, bl, bh must be distinct registers (and cl,ch distinct)

	MACRO
	MUL_64x64_64 $al, $ah, $bl, $bh, $cl, $ch
	DISTINCT $al, $ah, $bl, $bh
	DISTINCT $cl, $ch
	_UMULL	$al, $ah, $bl, $cl
	MLA	$ah, $bl, $ch, $ah
	MLA	$ah, $bh, $cl, $ah
	MEND
	
; unsigned 64x64=128
; a = (a3,a2,a1,a0) = b*c where b=(bh,bl) c=(ch,cl)
; a pair of temporary registers (tl, th) are required

	MACRO
	UMUL_64x64_128	$a0, $a1, $a2, $a3, $bl, $bh, $cl, $ch, $tl, $th
	_UMULL	$a0, $a1, $bl, $cl	; bl * cl
	_UMULL	$a2, $a3, $bh, $ch	; bh * ch
	_UMULL	$tl, $th, $bl, $ch
	ADDS	$a1, $a1, $tl
	ADCS	$a2, $a2, $th
	ADC	$a3, $a3, #0
	_UMULL 	$tl, $th, $bh, $cl
	ADDS	$a1, $a1, $tl
	ADCS	$a2, $a2, $th
	ADC	$a3, $a3, #0
	MEND
	
	; the following code sequence provides an alternative definition for
	; unsigned 64x64=128 that is one instruction shorter, but only works 
	; out quicker in terms of cycles on an ARM9 or StrongARM
	;
	; the original is quicker for an ARM7TDMI since for UMLA takes an 
	; extra cycle in this code and thus this should only be used if using
	; an ARM9 or a StrongARM processor

	; MACRO
	; UMUL_64x64_128	$a0, $a1, $a2, $a3, $bl, $bh, $cl, $ch, $t
    ; MOV     $t,#0
    ; UMULL   $a0,$a1,$bl,$cl
    ; UMULL   $a2,$a3,$bl,$ch
    ; ADDS    $a1,$a1,$a2
    ; ADC     $a2,$t,#0
    ; UMLAL   $a1,$a2,$bh,$cl
    ; ADDS    $a2,$a2,$a3
    ; ADC     $a3,$t,#0
    ; UMLAL   $a2,$a3,$bh,$ch
	; MEND
	
; signed 64x64 = 128
; as above but signed
	
	MACRO
	SMUL_64x64_128	$a0, $a1, $a2, $a3, $bl, $bh, $cl, $ch, $tl, $th
	_UMULL	$a0, $a1, $bl, $cl	; bl * cl
	_SMULL	$a2, $a3, $bh, $ch	; bh * ch
	_SMULL	$tl, $th, $bl, $ch
	TST     $bl, #1<<31
	ADDNE	$th, $th, $ch
	ADDS	$a1, $a1, $tl
	ADCS	$a2, $a2, $th
	ADC	$a3, $a3, $th, ASR#31	; carry + sign bit
	_SMULL 	$tl, $th, $bh, $cl
	TST		$cl, #1<<31
	ADDNE	$th, $th, $bh
	ADDS	$a1, $a1, $tl
	ADCS	$a2, $a2, $th
	ADC	$a3, $a3, $th, ASR#31	; carry + sign bit
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;						;
;	INTEGER DIVISION MACROS			;
;						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	32/16 DIVISION	- 2 cycles per answer bit	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; unsigned 32/16 = 16 with remainder 16
;
; n=numerator	d=denomenator
; q=quotient	r=remainder 	
;
; ie n/d = q + r/d or n=q*d+r and 0<=r<d
; it is assumed that n<(d<<16) for this to work (else q will overflow)
; in particular, divide by 0 is not possible!
; n and d must be distinct
; q and r must be distinct
; can have {q,r} = {n,d}

	MACRO
	UDIV_32d16_16r16 $q, $r, $n, $d, $flag
	DISTINCT $q, $r
	DISTINCT $d, $n
	
	IF "$flag"<>"-"
	  RSB	$d, $d, #0			; negate divisor (if not already)
	ENDIF
        CMN     $n, $d, LSL #8			; is n<(d<<8) ?
        MOV     $d, $d, LSL #15			; get denominator up high
        MOVLO   $n, $n, LSL #7			; if (n<(d<<8)) skip 8 stages
        BLO     %FT01				; skip first 8 stages

        ADDS    $n, $d, $n			; will d go?
        SUBLO   $n, $n, $d			; if not then add it back on
        ADCS    $n, $d, $n, LSL #1		; add answer bit, shift up, try
        SUBLO   $n, $n, $d			; if it didn't go then add on d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
01
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d
        ADCS    $n, $d, $n, LSL #1
        SUBLO   $n, $n, $d			; fix up final remainder
        
        ADC     $q, $n, $n			; insert final answer bit
        MOV     $r, $q, LSR #16			; extract reminder
        BIC     $q, $q, $r, LSL #16		; extract quotient
        MEND
        
; Signed 32/16 = 16 remainder 16
; as above but signed
; the sign temp register must be distinct from all the rest

	MACRO
	SDIV_32d16_16r16 $q, $r, $n, $d, $sign
	DISTINCT $sign, $q
	DISTINCT $sign, $r
	DISTINCT $sign, $n
	DISTINCT $sign, $d
	ANDS	$sign, $d, #1<<31		; extract sign of denominator
	RSBPL	$d, $d, #0			; make denominator -ve
	EORS	$sign, $sign, $n, ASR#32	; add in sign of numerator
	RSBCS	$n, $n, #0			; make numerator +ve
	; sign bit 31 = sign of quotient
	; sign bit 30 = sign of remainder
	UDIV_32d16_16r16 $q, $r, $n, $d, -
	MOVS	$sign, $sign, LSL#1
	RSBCS	$q, $q, #0			; fixup result signs
	RSBMI	$r, $r, #0
	MEND

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	32/32 DIVISION - 3 cycles per answer bit	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; unsigned 32/32 = 32 with remainder 32
;
; n=numerator	d=denomenator
; q=quotient	r=remainder 	
;
; ie n/d = q + r/d or n=q*d+r and 0<=r<d
; if d=0 then it returns q=0, r=n (so n=q*d+r !)
; registers must be distinct
; n and d are corrupted
;
; This algorithm is from the ARM C library and works the same way
; as standard long division. The divisor is shifted up as far as it will
; go staying less than the numerator and then shifted down again one at a
; time, subtracting off n.

	MACRO
	UDIV_32d32_32r32 $q,$r,$n,$d
	MOV	$q, #0		; zero the quotient
	MOV	$r, $n		; set the remainder to the current value
        MOVS    $n, $d		; save the denominator
        BEQ     %FT08		; divide by 0
00
        CMP     $d, $r, LSR #8
        MOVLS   $d, $d, LSL #8
        BLO     %BT00

        CMP     $d, $r, LSR #1
        BHI     %FT07
        CMP     $d, $r, LSR #2
        BHI     %FT06
        CMP     $d, $r, LSR #3
        BHI     %FT05
        CMP     $d, $r, LSR #4
        BHI     %FT04
        CMP     $d, $r, LSR #5
        BHI     %FT03
        CMP     $d, $r, LSR #6
        BHI     %FT02
        CMP     $d, $r, LSR #7
        BHI     %FT01
00
; not executed when falling through
        MOVHI   $d, $d, LSR #8

        CMP     $r, $d, LSL #7
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #7
        CMP     $r, $d, LSL #6
01
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #6
        CMP     $r, $d, LSL #5
02
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #5
        CMP     $r, $d, LSL #4
03
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #4
        CMP     $r, $d, LSL #3
04
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #3
        CMP     $r, $d, LSL #2
05
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #2
        CMP     $r, $d, LSL #1
06
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d, LSL #1
07
        CMP     $r, $d
        ADC     $q, $q, $q
        SUBCS   $r, $r, $d
        CMP     $d, $n
        BNE     %BT00
08
	MEND	
	
	
; signed 32/32 with remainder 32
;
; n=numerator	d=denomenator
; q=quotient	r=remainder
; sign = an extra scratch register to store the signs in.
;
; ie n/d = q + r/d or n=q*d+r 
; q is rounded towards zero and r has the same sign as n
; hence -3/2 = -1 remainder -1.
;       3/-2 = -1 remainder 1
;	-3/-2 = 1 remainder -1.
; if d=0 then it returns q=0, r=n (so n=q*d+r !)
; registers must be distinct

	MACRO
	SDIV_32d32_32r32 $q, $r, $n, $d, $sign
	ANDS	$sign, $d, #1<<31		; get sign of d
	RSBMI	$d, $d, #0			; ensure d +ve
	EORS	$sign, $sign, $n, ASR#32	; b31=result b30=sign of n
	RSBCS	$n, $n, #0			; ensure n +ve
	UDIV_32d32_32r32 $q, $r, $n, $d		; do the divide
	MOVS	$sign, $sign, LSL#1		; get out sign bits
	RSBCS	$q, $q, #0			; negate quotient
	RSBMI	$r, $r, #0			; negate remainder
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	64/32 DIVISION	- 3 cycles per answer bit	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; unsigned 64/32 = 32 remainder 32
; On entry $nh = numerator high, $nl = numerator low, $d = denomenator
; On exit  $q = quotient, $r = remainder
; Assumes that numerator<(denominator<<32)
; Top bit of $d must be 0 (ie denominator < 2^31)
; Flag indicates whether the divisor has already been negated or not
; nl can equal q
; nh can equal r

	MACRO
	UDIV_64d32_32r32 $q, $r, $nl, $nh, $d, $flag
	IF "$flag"<>"-"
	  RSB	$d, $d, #0		; negate divisor
	ENDIF
        ADDS	$q, $nl, $nl		; next bit of numerator/remainder in C
        ADCS	$r, $d, $nh, LSL #1	; rem = 2*rem - divisor
        RSBCC	$r, $d, $r		; if it failed add divisor back on
        ADCS	$q, $q, $q		; insert answer bit and get numerator bit
k	SETA	1
	WHILE	k<32
          ADCS	$r, $d, $r, LSL #1	; rem = 2*rem - divisor
          RSBCC $r, $d, $r		; if it failed add divisor back on
          ADCS  $q, $q, $q		; insert answer bit and get numerator bit
k	  SETA	k+1
	WEND
	MEND
	
; signed 64/32 = 32 with remainder 32
; As above but signed and requires an extra register for the sign

	MACRO
	SDIV_64d32_32r32 $q, $r, $nl, $nh, $d, $sign
        MOVS        $sign, $d
        RSBPL       $d, $d, #0         		; make divisor -ve
        MOV         $sign, $sign, LSR #1        ; shift sign down one bit
        EORS        $sign, $sign, $nh, ASR #1	; insert dividend sign and
        ; $sign bit 31 sign of dividend (= sign of remainder)
        ;       bit 30 sign of dividend EOR sign of divisor (= sign of quotient)
        BPL         %FT01
        RSBS        $nl, $nl, #0                ; absolute value of dividend
        RSC         $nh, $nh, #0                ; absolute value of dividend
01	; numerator now +ve
	UDIV_64d32_32r32 $q, $r, $nl, $nh, $d, -
        MOVS        $sign, $sign, LSL #1
        RSBMI       $q, $q, #0			; set sign of quotient
        RSBCS       $r, $r, #0			; set sign of remainder
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	64/64 DIVISION		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; unsigned 64/64 = 64 with remainder 64
;
; n=numerator	d=denomenator (each split into high and low part)
; q=quotient	r=remainder 	
;
; ie n/d = q + r/d or n=q*d+r and 0<=r<d
; if d=0 then it returns q=0, r=n (so n=q*d+r !)
; registers must be distinct
; n and d are corrupted
; t is a temporary register
;
; Routine is not unrolled since the speedup isn't great.
; Can unroll if you like.

	MACRO
	UDIV_64d64_64r64 $ql,$qh,$rl,$rh,$nl,$nh,$dl,$dh,$t
	MOV	$ql,#0		; zero the quotient
	MOV	$qh,#0
	MOV	$rh,$nh		; set the remainder to the current value
	MOV	$rl,$nl
	TEQ	$dh,#0
	TEQEQ	$dl,#0
	BEQ	%F08		; divide by 0
        MOVS    $t,#0		; count number of shifts
        ; first loop gets $d as large as possible
00
	ADDS	$dl, $dl, $dl
	ADCS	$dh, $dh, $dh	; double d
	BCS	%F01		; overflowed
	CMP	$dh, $rh
	CMPEQ	$dl, $rl
	ADDLS	$t, $t, #1	; done an extra shift
	BLS	%B00
	ADDS	$t, $t, #0	; clear carry
01				; carry the overflow here
	MOVS	$dh, $dh, RRX	; colour
	MOV	$dl, $dl, RRX	; shift back down again
02				; now main loop
	SUBS	$nl, $rl, $dl
	SBCS	$nh, $rh, $dh	; n = r - d and C set if r>=d
	MOVCS	$rh, $nh
	MOVCS	$rl, $nl	; r=r-d if this goes
	ADCS	$ql, $ql, $ql
	ADC	$qh, $qh, $qh	; shift next bit into the answer
	MOVS	$dh, $dh, LSR#1
	MOV	$dl, $dl, RRX	; shift down d
	SUBS	$t, $t, #1
	BGE	%B02		; do next loop (t+1) loops 
08
	MEND	
	
; signed 64/64 with remainder 64
;
; n=numerator	d=denomenator (each has a high and low part)
; q=quotient	r=remainder
; sign = an extra scratch register to store the signs in.
;
; ie n/d = q + r/d or n=q*d+r 
; q is rounded towards zero and r has the same sign as n
; hence -3/2 = -1 remainder -1.
;       3/-2 = -1 remainder 1
;	-3/-2 = 1 remainder -1.
; if d=0 then it returns q=0, r=n (so n=q*d+r !)
; registers must be distinct

	MACRO
	SDIV_64d64_64r64 $ql,$qh,$rl,$rh,$nl,$nh,$dl,$dh,$t,$sign
	ANDS	$sign, $dh, #1<<31		; get sign of d
	BPL	%F00
	RSBS	$dl, $dl, #0			; ensure d +ve
	RSC	$dh, $dh, #0
00
	EORS	$sign, $sign, $nh, ASR#32	; b31=result b30=sign of n
	BCC	%F01
	RSBS	$nl, $nl, #0			; ensure n +ve
	RSC	$nh, $nh, #0
01
	UDIV_64d64_64r64 $ql,$qh,$rl,$rh,$nl,$nh,$dl,$dh,$t ; do the divide
	MOVS	$sign, $sign, LSL#1		; get out sign bits
	BCC %F02
	RSBS	$ql, $ql, #0
	RSC	$qh, $qh, #0
02
	MOVS	$sign, $sign, LSL#1
	BCC %F03
	RSBS	$rl, $rl, #0			; negate remainder
	RSC	$rh, $rh, #0
03
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;				;
;	INTEGER SQUARE ROOT	;
;				;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; take the integer square root of a 32 bit unsigned number
; produces a 16 bit answer (not rounded)
; On entry:
;   n = input number (32 bit)
;   t = temporary register
; On exit:
;   q = square root
;   r = remainder (n=q*q+r) (r<=2*q so may be 17 bits) 
; Internally:
;   r = current remainder ( = n-q*q )
;   q = current root estimate. At the start of stage k this is of the form
;	  01000...00000qqq..qqq
;       where there are k q-bits, giving the top k bits of the 16 bit root
;   t = 3<<30 the constant required to keep q in the indicated form
;
; Code size: 50 instructions (excluding return)
; Time:	     50 cycles (excluding return)
;
; n may be any one of q,r or t but q,r,t must be distinct

	MACRO
	SQR_32_16r17 $q, $r, $n, $t
	DISTINCT $q, $r, $t
	SUBS	$r, $n, #1<<30		; take off first estimate ((1<<15)^2)
	ADDCC	$r, $r, #1<<30		; add back on if it didn't go
	MOV	$t, #3<<30		; initialise a constant in t
	ADC	$q, $t, #1<<31		; peform k=0 stage - add next answer bit
        ; 1..14
k	SETA	1
	WHILE	k<16
	  CMP	$r, $q, ROR #(2*k)	; try setting bit (15-k) of answer
	  SUBCS	$r, $r, $q, ROR #(2*k)	; update remainder if it goes
	  ADC	$q, $t, $q, LSL#1	; insert next bit of answer
k	  SETA	(k+1)
	WEND
	BIC	$q, $q, #3<<30		; extract answer
	MEND
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;				;
;	INTEGER CUBE ROOT	;
;				;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Very Fast integer cube root
; Author: Dominic Symes
;
; 64 cycles total (62 excluding constant setup)
; 6 cycles/bit of answer
;
; Details:
;
; Let n		= original number to be cube rooted
; Let q(k)	= Cube root of n with bits 0 to k-1 cleared (ie the estimate)
; Let r(k)	= n - q(k)^3 (ie the remainder after working out bit k)
; Let b(k)	= bit k of the answer (ie q(k) = [0..0b(11)b(10)..b(k)0..0])
; Let s(k)	= 3*q(k)*q(k) + 3*q(k)*2^(k-1) + 2^(2k-2)
;
; Then it is easily shown that given q(k+1),r(k+1),s(k+1) then b(k)=1
; if and only if r(k+1) >= 2^k * s(k+1)
;
; if b(k)=0 then r(k) = r(k+1)
; if b(k)=1 then r(k) = r(k+1) - 2^k * s(k+1)
;
; Hence the task is to maintain s(k) in the fewest number of cycles.
; By substitution:
;
; if b(k)=0 then s(k) = s(k+1) - 3*2^(k-1)*(   q(k+1) +   2^(k-1) )
; if b(k)=1 then s(k) = s(k+1) + 3*2^(k-1)*( 3*q(k+1) + 5*2^(k-1) )
;
; NB	q(k) is a multiple of 2^k
;	s(k) is a multiple of 2^(2k-2)
;
; Let	Q(k) = (q(k) + 2^(k-2)) ROR #k = [010..0b(11)b(10)..b(k)]
; Let	S(k) = s(k) ROR #(2*k) = [xx0..0x...x]
;
; We need two constants in registers:
;
; c1 = NOT(1<<29)
; c2 = 3<<30

	; Main step macro (to find b(k))
	; On entry: Q1=Q(k+1) R=r(k+1) S=S(k+1) Q=scratch
	; On exit:  Q1=scratch R=r(k) S=S(k) Q=Q(k)
	; We use the shorthand P=2^(k-1) and PP = P*P = 2^(2k-2)
	MACRO
	CBR_STEP $k, $Q, $Q1, $R, $S, $c1, $c2
	; Q = r(k+1) - 2^k * s(k+1) = R - (S ROL (3*k+2))
	SUBS	$Q, $R, $S, ROR #(30-3*$k)
	; now carry=b(k) so update remainder
	MOVCS	$R, $Q
	; now set Q  = Q(k)
	; c2     = [ 1 1 0 ................. 0 ]
	; Q1 LSL #1  = [ 1 0 0 ......... q(k+1)>>k ]
	; carry      = [ 0 0 0 .............. b(k) ]
	; SUM        = [ 0 1 0 ........... q(k)>>k ]
	;            = Q(k)
	ADC	$Q, $c2, $Q1, LSL#1
	; now effectively add P*(q(k+1)+P)) to S
	; Q1         = [ 0 1 0 ....................... q(k+1) >> (k+1) ]
	; S ROL #2   = [ 0 0 0 .......................... s(k+1) >> 2k ]
	; SUM	     = [ 0 1 0 ............. { s(k+1)+P*q(k+1) } >> 2k ]
	ADD	$S, $Q1, $S, ROR #30
	; now if b(k)=1 effectively set Q1=-2*Q1 + magic constant
	; c1         = [ 1 1 0 1 1 ................................ -1 ]
	; Q1 LSL #1  = [ 1 0 0 0 0 .............. { 2q(k+1) } >> (k+1) ]
	; EOR        = [ 0 1 0 1 1 .......... { -2q(k+1)-4P } >> (k+1) ]
	EORCS	$Q1, $c1, $Q1, LSL #1
	; now finally set S = S(k)
	; if b(k)=0 then
	;   S        = [ 0 1 0 0 0 ......... { s(k+1)+P*q(k+1) } >> 2k ]
	;   Q1 ROL#2 = [ 0 0 0 0 0 .......... { 4*q(k+1)+4P } >> (k+1) ]
	;   DIFF     = [ 0 1 0 0 0 ... { s(k+1)-3*P*q(k+1)-4PP } >> 2k ]
	;            = { s(k+1)-3*P*q(k+1)-4PP + PP } ROR 2k
	;            = s(k) ROR 2k
	; if b(k)=1 then
	;   S        = [ 0 1 0 0 0 ......... { s(k+1)+P*q(k+1) } >> 2k ]
	;   Q1 ROL#2 = [ 0 1 1 1 1 ...... { -8q(k+1)-16P+4P } >> (k+1) ]
	;   DIFF     = [ 1 1 0 0 0 .. { s(k+1)+9*P*q(k+1)+12PP } >> 2k ]
	;	     = { s(k+1)+9*P*q(k+1) + 12PP + 3PP } ROR 2k
	;            = s(k) ROR 2k
	SUB	$S, $S, $Q1, ROR #30
	; finished
	MEND

; Integer cube root
; 
; q = register to hold the result (may equal any of the other registers)
; r = register holding the input value
;
; q0, q1, s, c1, c2 = temporary registers, all distinct and
; distinct from r.
;
; The algorithm calculates the largest integer q such that
; q*q*q <= r. The remainder is not currently returned but could
; be extracted with the addition of some more instructions.
; q has at most 11 bits.
;
; cycle count = 2 + 5 + 9*6 + 3 = 64 cycles

	MACRO
	CBR_32_11 $q, $r, $q0, $q1, $s, $c1, $c2
	; initialise constants
	MVN	$c1, #1<<29
	MOV	$c2, #3<<30
	; first case (k=10, trying to set bit 10) optimised
	SUBS	$q0, $r, #1<<30		; can we set bit 10?
	MOVCS	$r, $q0			; if so update remainder
	ADC	$q0, $c2, #1<<31      	; insert answer bit
	MOVCC	$s, #(1<<30)		; S(10) if b(10)=0
	MOVCS	$s, #(3<<30)+4		; S(10) if b(10)=1
	; general cases
	CBR_STEP 9, $q1, $q0, $r, $s, $c1, $c2	; calc b(9)
	CBR_STEP 8, $q0, $q1, $r, $s, $c1, $c2	; calc b(8)
	CBR_STEP 7, $q1, $q0, $r, $s, $c1, $c2	; calc b(7)
	CBR_STEP 6, $q0, $q1, $r, $s, $c1, $c2	; calc b(6)
	CBR_STEP 5, $q1, $q0, $r, $s, $c1, $c2	; calc b(5)
	CBR_STEP 4, $q0, $q1, $r, $s, $c1, $c2	; calc b(4)
	CBR_STEP 3, $q1, $q0, $r, $s, $c1, $c2	; calc b(3)
	CBR_STEP 2, $q0, $q1, $r, $s, $c1, $c2	; calc b(2)
	CBR_STEP 1, $q1, $q0, $r, $s, $c1, $c2	; calc b(1)
	; special case for final bit
	CMP	$r, $s, ROR #30		; 0 or 1?
	ADC	$q0, $q1, $q1		; insert answer bit
	BIC	$q, $q0, #3<<30		; extract answer
	MEND	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;								;
;	FIXED POINT MACROS					;
;								;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; The following macros deal with fixed point numbers with binary
; point before bit $bit (which is specified in the macro). In other
; words the 32 bit integer x is used to represent the number
; x*2^(-$bit).
; The overflow action for each operation should be specified. 
; $topbit gives the number of bits the answer should fit into (with top
; sign bit if signed) without overflow. This will usually be 32.
;
; Ie, format of number:
;                       32     $topbit   $bit      0
;	unsigned:	000..000 xxx...xxx yyy...yyy
;	signed:		sss..sss sxx...xxx yyy...yyy
;
; where x is the integer part, s the sign bit and y the fraction part

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;				;
;	FIXED POINT DIVISION	;
;				;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Unsigned fixed point division with 32 bit answer
;
; Calculates q=n/d where n and d are both integers
; (or both fixed point with the same number of bits after the binary point)
;
; The answer in q is given with fixed point at position $bit (a constant)
; The answer must fit into $topbit bits (usually 32)
; Branches to the label $overflow if there is a divide by 0 or
; an overflow in the division (answer goes outside the given number of bits)
;
; q, n, d must be distinct registers
; n and d are corrupted

	MACRO
	UDIVF_32d32_32	$q, $n, $d, $bit, $topbit, $overflow
	IF "$overflow"<>""
	  CMP	$d, $n, LSR#($topbit-$bit)	; check 2^(topbit-bit) > n/d
	  BLS	$overflow			; if not then overflow/div 0
	ENDIF
	MOV	$q, $n, LSL#$bit		; low of n<<bit
	MOV	$n, $n, LSR#(32-$bit)		; high of n<<bit
	UDIV_64d32_32r32 $q, $n, $q, $n, $d	; do the divide (3 cycles/bit)
	MEND

; Signed fixed point divide with 32 bit answer
; Same as unsigned but needs an extra register to store the sign

	MACRO
	SDIVF_32d32_32	$q, $n, $d, $bit, $topbit, $sign, $overflow
	EORS	$sign, $n, $d, ASR#32		; get sign of quotient in b31
	RSBCS	$d, $d, #0			; make denominator +ve
	MOVS	$n, $n
	RSBMI	$n, $n, #0			; make numerator +ve
	UDIVF_32d32_32	$q, $n, $d, $bit, $topbit-1, $overflow
	TST	$sign, #1<<31
	RSBNE	$q, $q, #0			; get sign of quotient
	MEND
	
;==========================================================================
; Fixed point Cosine macro.
;
; This takes the Cosine of the value passed (assumed to be in radians).
;
; If "$RANGE"=1 the parameter is first range reduced to -PI/2 < x < PI/2 
; and then the Cosine is calculated, else:
;
; If "$RANGE"=0 then the  parameter is assumed to already be range 
; reduced (and will give dodgy result if it isn't in the range).
;
;
;==========================================================================

   MACRO
   ARMCOS   $z, $x, $t0, $t1, $PREC, $RANGE


   CMP    $x, #0        ; if x < 0
   RSBLT  $x, $x, #0    ;    x = -x

  ; First part involves reducing the argument to the range
  ; -PI/2 < f=f(x) < PI/2
  ; Only do this bit if $RANGE is set, otherwise assume is
  ; argument is range checked.
   MOV    $z,      #(0x19<<$PREC) >> 3    ; Fabricate PI to 18 bits
   ADD    $z, $z, #(0x22<<$PREC) >> 11

   ADD     $x,  $x,  $z, ASR #1           ; n = x =  (PI/2) + x

  IF $RANGE>0


    ADD     $t1, $x, $x, ASR #1              ; n = n/PI
    ADD     $t1, $t1, $t1, ASR #15             ; (only for high precision)
    ADD     $t1, $t1, $t1, ASR #6
    SUB     $t1, $t1, $x, ASR #2
    SUB     $t0, $t1, $x, ASR #12

    ADD     $t0,  $t0,  #(1<<($PREC+1))        ; Round to nearest integer, and
    MOV     $t0,  $t0,       ASR #($PREC+2)    ; get back to original precision.

  ELSE
   ; No range checking - argument should be |x| < PI/2
    MOV     $t0, #0
  ENDIF

  TST     $t0,  #0x001                     ; If n is odd then negate result
                                            ; (keep flags till later)
 ; Calculate the range reduced x
  MUL     $t1,  $z,  $t0                   ; x  = x - (n*PI)
  SUB     $x,  $x,   $t1
;  ADD     $x,  $x,   $z, ASR #1          ; x += PI/2 (for cosine)

 ; x is now in range -PI/2 < x < PI/2 so can now calculate sin(x)
   MUL     $t1,  $x,  $x                    ; g = (f/2)**2
   MOV     $t1,  $t1,       ASR #$PREC+2

  ; r  = ((((R3*g) + R2)*g) + R1)*g
   ADD     $z, $t1,  $t1, ASR #1              ; Assume R3*g = approx = g*(13/1024)
   ADD     $z, $z, $t1, ASR #3
   MOV     $z, $z, ASR #7


   MOV     $t0,  #(0x88<<$PREC)>>8            ; Assume R2 = approx = 0x8888 >> 18
   ORR     $t0,  $t0,  $t0,  LSR #8
  IF $PREC > 17
   ORR     $t0,  $t0,  $t0,  LSR #16            ; This op for > 18 bit precision only
  ENDIF
   RSB     $z, $z, $t0,  LSR #2

   ORR     $t0,  $t0,  $t0,  LSR #2             ; Assume R3 = approx = 0xAAAA >> 16

   MUL     $z, $t1, $z                      ; r = r * g
   RSB     $z, $t0,  $z, ASR #$PREC         ; r = r - 0.6666662674

   MUL     $z, $t1, $z                      ; r = r * g
   MOV     $z, $z,      ASR #$PREC

   MUL     $z, $x,  $z                     ; r = x +  r * x
   ADD     $z, $x,  $z, ASR #$PREC

  ; If we have done the range checking then correct the answers sign
   RSBNE   $z, $z, #0

   MEND

;===============================================================================

    MACRO
    ARMSIN   $z, $x, $t0, $t1, $PREC, $RANGE

    TST    $x, $x, LSL #1 ; if (x<0) c=1 else c=0
    
;    CMP    $x, #0        ; if x < 0
;    MOVLT  $sgn, #1      ;    sgn=-1
;    RSBLT  $x, $x, #0    ;    x = -x
    RSBCS  $x, $x, #0    ;    x = -x

  ; First part involves reducing the argument to the range
  ; -PI/2 < f=f(x) < PI/2
  ; Only do this bit if $RANGE is set, otherwise assume is
  ; argument is range checked.
    MOV    $z,      #(0x19<<$PREC) >> 3    ; Fabricate PI to 18 bits
    ADD    $z, $z, #(0x22<<$PREC) >> 11

  IF $RANGE>0

 ;   ADD     $t0,  $x,  $z, ASR #1           ; n = (PI/2) + x

  ; If RANGE=2 then will work for large n, else only work for small n
  IF $RANGE=2
    _UMULL  $t0,  $t1,  $a1, $t0               ; n = n/PI
    MOV     $t0,  $t0,       LSR #$PREC       ; Normalise and get 32 LSBits,
    ORR     $t0,  $t0,  $t1,  LSL #(32-$PREC)  ; assuming it doesn't overflow this
  ELSE

    ADD     $t1, $x, $x, ASR #1              ; n = x/PI
    ADD     $t1, $t1, $t1, ASR #15             ; (only for high precision)
    ADD     $t1, $t1, $t1, ASR #6
    SUB     $t1, $t1, $x, ASR #2
    SUB     $t0, $t1, $x, ASR #12
;    MOV     $t0, $t0,     ASR #2              ; Get back to original precision.
  ENDIF

    ADD     $t0,  $t0,  #(1<<($PREC+1))       ; Round to nearest integer
    MOV     $t0,  $t0,       ASR #($PREC+2)

;   TST     $t0,  #0x001                     ; Is N odd (save in flags for later)

   ; Calculate the range reduced x
;     MUL     $t1,  $z,  $t0                   ; x  = x - (n*PI)
;    SUB     $x,  $x,   $t1,  ASR #$PREC
  ELSE
   ; No range checking - argument should be |x| < 2-sqrt(3)
    MOV     $t0, #0
  ENDIF

; Want to perform:     If (x<0) sgn=-1 else sgn=1
;                      If n is odd then sgn=-sgn
; Flags are already set to CS if (x<0), toggle C-flag if n is odd
  TST     $t0,  #0x001                     ; If n is odd then negate result
  CMPNE   $z, $z, RRX                   ; (toggle C-flag if odd)

  MUL     $t1,  $z,  $t0                   ; x  = x - (n*PI)
  SUB     $x,  $x,   $t1
;  ADD     $x,  $x,   $z, ASR #1          ; x += PI/2 (for cosine)

 ; x is now in range -PI/2 < x < PI/2 so can now calculate sin(x)
   MUL     $t1,  $x,  $x                    ; g = (f/2)**2
   MOV     $t1,  $t1,       ASR #$PREC+2

  ; r  = ((((R3*g) + R2)*g) + R1)*g
   ADD     $z, $t1,  $t1, ASR #1              ; Assume R3*g = approx = g*(13/1024)
   ADD     $z, $z, $t1, ASR #3
   MOV     $z, $z, ASR #7


   MOV     $t0,  #(0x88<<$PREC)>>8            ; Assume R2 = approx = 0x8888 >> 18
   ORR     $t0,  $t0,  $t0,  LSR #8
  IF $PREC > 17
   ORR     $t0,  $t0,  $t0,  LSR #16            ; This op for > 18 bit precision only
  ENDIF
   RSB     $z, $z, $t0,  LSR #2

   ORR     $t0,  $t0,  $t0,  LSR #2             ; Assume R3 = approx = 0xAAAA >> 16

   MUL     $z, $t1, $z                      ; r = r * g
   RSB     $z, $t0,  $z, ASR #$PREC         ; r = r - 0.6666662674

   MUL     $z, $t1, $z                      ; r = r * g
   MOV     $z, $z,      ASR #$PREC

   MUL     $z, $x,  $z                     ; r = x +  r * x
   ADD     $z, $x,  $z, ASR #$PREC

  ; If we have done the range checking then correct the answers sign
   RSBCS   $z, $z, #0

   MEND

;;;;;;;
; END ;
;;;;;;;

	END
