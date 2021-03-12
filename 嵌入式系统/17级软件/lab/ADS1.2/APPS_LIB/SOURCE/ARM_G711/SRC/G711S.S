;/*
; * G.711 assembler
; * Copyright (C) ARM Limited 1996,1998-1999. All rights reserved.
; */

;===========================================================================
;
; CCITT A-law (and u-law) to linear (and back) converter routines.
;
; Optimised ARM routines used for ADPCM as defined by G.721, G723, G726.
;
; These routines are based on the C language implementation of G723 from
; Sun Microsystems.
;
; First release date   : 22/02/1996
;
; Added support of A-law <-> u-law conversion
; Date   				: 31/03/1998
;
;===========================================================================

	INCLUDE intworkm.h

	AREA    |C$$Code|, CODE, READONLY, REL $interwork
	EXPORT  |G711_linear2alaw|
	EXPORT  |G711_alaw2linear|
	EXPORT  |G711_linear2ulaw|
	EXPORT  |G711_ulaw2linear|
	EXPORT	|G711_alaw2ulaw|
	EXPORT	|G711_ulaw2alaw|
	EXPORT  |G711_linear2linear|
	
;	IMPORT	G711_a2u_lookup
;	IMPORT	G711_u2a_lookup

; G711_a2u_lookup_ptr	DCD	G711_a2u_lookup
; G711_u2a_lookup_ptr	DCD	G711_u2a_lookup

	INCLUDE     g711m.h

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
;
;-----------------------------------------------------------------------
;
|G711_alaw2linear|
;                          $in, $out, $t1, $t2
	G711_alaw2linear_macro R0,  R0,   R1,  R2
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
;=======================================================================




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
;
;-----------------------------------------------------------------------
;
|G711_linear2alaw|
;                          $in, $out, $t1, $t2, $msk
	G711_linear2alaw_macro R0,  R0,   R1,  R2,  R3
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
;=======================================================================



;====G711_linear2ulaw===================================================
;
; Purpose : Converts a signed 16-bit linear PCM value to an 8-bit u-law value.
;
; Parameters: $in  = register holding input linear PCM value (2's complement,
;                    16-bit range).
;             $out = register used to hold output 8-bit u-law conversion.
;                    (this may be the same as $in, OR the same as $msk,
;                     but must not be the same as $t1,$t2).
;             $msk = temporary register (may be the same as $out).
;             $t1  = temporary register.
;             $t2  = temporary register.
;
; Performance:
;             ARM7M = 26 cycles worst case (25S 0N 1I).
;-----------------------------------------------------------------------
;
|G711_linear2ulaw|
;                          $in, $out, $msk, $t1, $t2
	G711_linear2ulaw_macro R0,  R0,   R1,   R2,  R3
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
;-----------------------------------------------------------------------




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
; Performance (ARM7M):
;    9 cycles all cases (8S 0N 1I)

;-----------------------------------------------------------------------
;
|G711_ulaw2linear|
;                          $in, $out, $seg
	G711_ulaw2linear_macro R0,  R0,   R1
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
;=======================================================================

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
;	$ulaw may equal $alaw but then $ulaw cannot be equal to $table
;
;-----------------------------------------------------------------------
;
|G711_alaw2ulaw|
;	LDR		R2, G711_a2u_lookup_ptr
;                        $alaw, $ulaw, $tmp, $table, $hastable
	G711_alaw2ulaw_macro R0,    R0,    R1,   R2 ;	 ,true
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)

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
;	$alaw may equal $ulaw but then $alaw cannot be equal to $table
;
;-----------------------------------------------------------------------
;
|G711_ulaw2alaw|

;	LDR		R2, G711_u2a_lookup_ptr
;                        $ulaw, $alaw, $tmp, $table, $hastable
	G711_ulaw2alaw_macro R0,    R0,    R1,   R2 ;    ,true
	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
	
;-----------------------------------------------------------------------
; This one does a linear-to-linear conversion (don't ask why...well ok its
; for a function pointer which points to a function to do a conversion.
; If linear is required then nothing need be done. Although the linear
; conversion is slower by two branches, the worst case overall times drop.

|G711_linear2linear|

	RETURN "","","",""	; return (no rlist, no sp, lr, no condition)
;=======================================================================


	END

