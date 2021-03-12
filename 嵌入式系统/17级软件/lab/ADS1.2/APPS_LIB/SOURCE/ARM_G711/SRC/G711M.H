;/*
; * G.711 assembler macros
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;===========================================================================
;
; CCITT A-law (and u-law) to linear (and back) converter macros.
;
; Optimised ARM macros used for ADPCM as defined by G.721, G723, G726.
;
; These macros are based on the C language implementation of G723 from
; Sun Microsystems.
;
; First release	: 22/02/1996
;
; Added support of A-law <-> u-law conversion
; Date   		: 31/03/1998
;
;===========================================================================

	INCLUDE regchekm.h

	IMPORT	G711_a2u_lookup
	IMPORT	G711_u2a_lookup

;====G711_alaw2linear===================================================
;
; Purpose : Converts an 8-bit A-law value (inverted, unsigned char) to a signed
;           16-bit PCM value
;
; Parameters: $in  = register holding A-law value (unsigned char)
;             $out = register used to hold output PCM conversion (int)
;                    (this may be the same as $in).
;             $t1  = temporary register.
;             $t2  = temporary register.
;
; Performance:
;             ARM7M = 12 cycles worst case (11S 0N 1I).
; Code Size:
;             11 Instructions (44 bytes).
;
;-----------------------------------------------------------------------
;

  MACRO
$label  G711_alaw2linear_macro $in, $out, $t1, $t2

  DISTINCT $in, $t1, $t2
  DISTINCT $out, $t1, $t2

$label
  EOR      $t2,  $in, #0x55    ; Decode transmitted byte.
  AND      $out, $t2, #0x0F    ; Strip out lower data (t).
  MOV      $out, $out, LSL #4
  MOV      $t1,  $t2, LSR #4   ; Strip out segment number,
  AND      $t1,  $t1, #7       ; and remove sign bit

  SUBS     $t1,  $t1, #1       ; Calculate (seg-1).
  ADDLT    $out, $out, #0x0008 ; If seg=0 then t+=0x008
  ADDGE    $out, $out, #0x0108 ; If seg>0 then t+=0x108
  MOVGT    $out, $out, LSL $t1 ; If seg>1 then t=t << (seg-1)

  TST      $t2,  #0x80         ; Was the sign bit set ?
  RSBEQ    $out, $out, #0      ; If not then t=-t

  MEND


;====G711_linear2alaw===================================================
;
; Purpose : Converts a signed 16-bit linear PCM value to an 8-bit A-law value.
;
; Parameters: $in  = register holding input linear PCM value.
;             $out = register used to hold output 8-bit A-law conversion.
;                    (this may be the same as $in, OR the same as $msk,
;                     but must not be the same as $t1,$t2).
;             $t1  = temporary register.
;             $t2  = temporary register.
;             $msk = temporary register (may be the same as $out).
;
; Performance:
;             ARM7M = 27 cycles worst case (26S 0N 1I).
; Code Size:
;             26 Instructions (104 bytes).
;
;-----------------------------------------------------------------------
;

   MACRO
$label  G711_linear2alaw_macro $in, $out, $t1, $t2, $msk

   DISTINCT $in, $t1, $t2, $msk
   DISTINCT $out, $t1, $t2

$label
  RSBS     $t1,  $in, #0     ; if (pcm_val >=0)
  MOVLE    $msk, #0xD5       ;      mask = 0xD5 : sign (7th bit) = 1
  MOVGT    $msk, #0x55       ; else mask = 0x55 : sign (7th bit) = 0
  SUBGT    $in,  $t1, #8     ;      pcm_val = -pcm_val - 8

; Convert the input signal into logarithmic form (segment number).
  MOV      $t1,  #0
  MOVS     $t2,  $in, LSR #4 ; Store (pcm_val >> 4) for later.
  BLE      %FT00

  CMP      $in,  #0x00001000
  MOVGE    $in,  $in, LSR #4
  ADDGE    $t1,  $t1, #4

  CMP      $in,  #0x00000400
  MOVGE    $in,  $in, LSR #2
  ADDGE    $t1,  $t1, #2

  CMP      $in,  #0x00000100
  MOVGE    $in,  $in, LSR #1
  ADDGE    $t1,  $t1, #1

  CMP      $in,  #0x00000100
  ADDGE    $t1,  $t1, #1

00 ; Skip

; Time to combine the sign, segment, and quantisation bits.
  CMP      $t1,  #8           ; if (seg>=8)
  MOVGE    $in,  #0x7F        ;   return (0x7F ^ mask)
                                    ; else
  MOVLT    $in,  $t1, LSL #4  ;   aval = seg << SEG_SHIFT
  SUBS     $t1,  $t1, #1      ;   if (seg>=2)
  MOVGT    $t2,  $t2, LSR $t1 ;      pcm_val = pcm_val >> (seg-1)

  AND      $t2,  $t2, #0x0F   ; pcm_val = pcm_val & QUANT_MASK
  ORR      $in,  $in, $t2     ; aval |= pcm_val

  EOR      $out, $in, $msk     ; return aval ^ mask

  MEND

;====G711_linear2ulaw===================================================
;
; Purpose : Converts a signed 16-bit linear PCM value to an 8-bit u-law value.
;
; Parameters: $in  = register holding input linear PCM value.
;             $out = register used to hold output 8-bit u-law conversion.
;                    (this may be the same as $in, OR the same as $msk,
;                     but must not be the same as $t1,$t2).
;             $msk = temporary register (may be the same as $out).
;             $t1  = temporary register.
;             $t2  = temporary register.
;
; Performance:
;             ARM7M = 26 cycles worst case (25S 0N 1I).
; Code Size:
;             25 instructions (100 bytes).
;
;-----------------------------------------------------------------------
;
; $in - linear input sample (2's complement, 16-bit range).

  MACRO
$label  G711_linear2ulaw_macro $in, $out, $msk, $t1, $t2

  DISTINCT $in, $t1, $t2, $msk
  DISTINCT $out, $t1, $t2

 ; Get the sign and the magnitude of the input value.
  CMP     $in, #0               ; if (pcm_val < 0) {
  RSBLT   $in, $in, #0x84       ;     pcm_val = BIAS - pcm_val;
  MOVLT   $msk, #0x7F            ;     mask = 0x7F;
                                      ;	} else {
  ADDGE   $in, $in, #0x84       ;     pcm_val += BIAS;
  MOVGE   $msk, #0xFF           ;     mask = 0xFF; }


 ; Convert the input signal into logarithmic form (segment number).
  MOV      $t1, #0
  MOVS     $t2, $in, LSR #3     ; Store (pcm_val >> 3) for later.
  BLE      %FT00

  CMP      $in, #0x00001000
  MOVGE    $in, $in, LSR #4
  ADDGE    $t1, $t1, #4

  CMP      $in, #0x00000400
  MOVGE    $in, $in, LSR #2
  ADDGE    $t1, $t1, #2

  CMP      $in, #0x00000100
  MOVGE    $in, $in, LSR #1
  ADDGE    $t1, $t1, #1

  CMP      $in, #0x00000100
  ADDGE    $t1, $t1, #1

00

 ; Interleave the sign, segment, and quantization bits
 ; and complement the output word.
  CMP      $t1, #8              ; If out of range then return maximum value.
  MOVGE    $in, #0x7F           ;      output = 0x7F

  MOVLT    $in, $t2, ASR $t1    ; else output = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
  ANDLT    $in, $in, #0x0F
  ORRLT    $in, $in, $t1, LSL #4

  EOR      $out, $in, $msk   ; return (output ^ mask);

  MEND

;-----------------------------------------------------------------------
;
; G711_ulaw2linear() - Converts an 8-bit u-law value to a 16-bit linear PCM.
;
; Based on the G711 C code from Sun Microsystems - refer to this for functionality.
;
; First, a biased linear code is derived from the code word. An unbiased
; output can then be obtained by subtracting 33 from the biased code.
;
; Note 1: this function expects to be passed the complement of the
;         original code word. This is in keeping with ISDN conventions.
;
; Note 2: this function could be implemented more quickly with a
;         lookup table, but this would add approx 512 bytes of extra
;         storage space for the table.
;
; Parameters:
;    $in  - register containing the input 8-bit u-law value.
;    $out - register to return the 16-bit linear value in (may be the same as $in).
;    $seg - temporary register (used for the segment number).
;
; Performance:
;              ARM7M = 9 cycles all cases (8S 0N 1I)
; Code Size:
;              8 Instructions (24 bytes).
;

 MACRO
 G711_ulaw2linear_macro $in, $out, $seg

 DISTINCT $in, $seg
 DISTINCT $out, $seg

 MVNS    $seg, $in,  LSL #25  ; Complement to obtain the standard u-law input value, also
                              ; test to see if input was positive (the sign bit gets NOTted and
                              ; shifted into the carry flag, where we shall keep it until needed).
 MOV     $seg, $seg, LSR #29  ; whilst extracting the segment number from the input word, ie does:
                              ;    in=~in;
                              ;    seg=(in & 0x70) >> 4;
                              ;    if (in & sign_bit) {flags=CS} else {flags=CC}

 MVN     $out, $in,  LSL #3   ; Complement again! This time to get the quantisation bits.
 AND     $out, $out, #0x078   ;    out = (in & 0xF) << 3

 ADD     $out, $out, #0x84    ;    out = out + BIAS
 MOV     $out, $out, LSL $seg ;    out = out << segment

 SUBCS   $out, $out, #0x84    ;	   return ((in & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
 RSBCC   $out, $out, #0x84

 MEND
 
;-----------------------------------------------------------------------
;
; G711_alaw2ulaw() - Converts an 8-bit A-law value to an 8-bit u-law value.
;
; Based on the G711 C code from Sun Microsystems - refer to this for functionality.
;
; Parameters:
;   $alaw     - register containing the input 8-bit A-law value
;	$alaw     - register to return the 8-bit u-law value
;			    may be the same register as $alaw
;	$tmp      - temporary register
;	$table 	  - register containing pointer to address of lookup table
;               if register does not contain address for lookup table,
;               do not pass anything for $hastable
;				table address given by G711_a2u_lookup in file uatables.s
;	$hastable - parameter which should only be given if $table contains a valid
;				address for the lookup table that is required
;				the value given can be anything and is not required to
;				to be register
;				if $table is not valid, do not pass anything for this parameter
;
; Register differentation:
;	$alaw, $tmp, $table must be distinct registers
;	$ulaw, $tmp  must be distinct registers
;	$ulaw may equal $table
;	$ulaw may equal $alaw
;
;-----------------------------------------------------------------------
;
	MACRO
	G711_alaw2ulaw_macro $alaw, $ulaw, $tmp, $table, $hastable
 
	DISTINCT $alaw, $tmp, $table
	DISTINCT $ulaw, $tmp
	
	IF	"$hastable" = ""
 					B	a2u_skip_table
G711_a2u_lookup_ptr	DCD	G711_a2u_lookup
a2u_skip_table		LDR	$table, G711_a2u_lookup_ptr
	ENDIF
	
	AND	$tmp, $alaw, #0x7F		; ensure value between 0..127 (remove sign)
	EOR	$tmp, $tmp, #0x55		; remove even bit inversion, in accordance with
								; Note 2 of G.711 Table 1a
	LDRB	$tmp, [$table, $tmp]	; lookup value in table
	EOR	$tmp, $tmp, #0x7F		; exclusive or with 127 to get actual value
	AND	$ulaw, $alaw, #0x80		; put sign bit from original input into output
	ORR	$ulaw, $ulaw, $tmp		; put new value (less sign) into output
	
	MEND

;-----------------------------------------------------------------------
;
; G711_ulaw2alaw() - Converts an 8-bit u-law value to an 8-bit A-law value.
;
; Based on the G711 C code from Sun Microsystems - refer to this for functionality.
;
; Parameters:
;   $ulaw     - register containing the input 8-bit u-law value
;	$alaw     - register to return the 8-bit A-law value
;			    may be the same register as $ulaw
;	$tmp      - temporary register
;	$table 	  - register containing pointer to address of lookup table
;               if register does not contain address for lookup table,
;               do not pass anything for $hastable
;				table address given by G711_u2a_lookup in file uatables.s
;	$hastable - parameter which should only be given if $table contains a valid
;				address for the lookup table that is required
;				the value given can be anything and is not required to
;				to be register
;				if $table is not valid, do not pass anything for this parameter
;
; Register differentation:
;	$ulaw, $tmp, $table must be distinct registers
;	$alaw, $tmp  must be distinct registers
;	$alaw may equal $table
;	$alaw may equal $ulaw
;
;-----------------------------------------------------------------------
;
	MACRO
	G711_ulaw2alaw_macro $ulaw, $alaw, $tmp, $table, $hastable
 
	DISTINCT $ulaw, $tmp, $table
	DISTINCT $alaw, $tmp
	
 	IF	"$hastable" = ""
 					B	u2a_skip_table
G711_u2a_lookup_ptr	DCD	G711_u2a_lookup
u2a_skip_table		LDR	$table, G711_u2a_lookup_ptr
	ENDIF
	
	AND	$tmp, $ulaw, #0x7F		; ensure value between 0..127 (remove sign)
	EOR	$tmp, $tmp, #0x7F		; exclusive or with 127 to get value to lookup
	LDRB	$tmp, [$table, $tmp]	; lookup value in table
	SUB	$tmp, $tmp, #1			; subtract one from value looked up
								; to bring value in range 0..127
	EOR	$tmp, $tmp, #0x55		; add even bit inversion, in accordance with
								; Note 2 of G.711 Table 1a
	AND	$alaw, $ulaw, #0x80		; put sign bit from original input into output
	ORR	$alaw, $alaw, $tmp		; put new value (less sign) into output
	
	MEND

;-----------------------------------------------------------------------

	END

