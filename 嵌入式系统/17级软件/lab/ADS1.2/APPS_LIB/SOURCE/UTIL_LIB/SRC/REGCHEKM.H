;/*
; * Utility Library: Register Check assembler macros
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;==========================================================================
;  ARM Register Checking Macros
;==========================================================================
;
; Version:	1.0.0
; Date:		15/01/1998
;
;==========================================================================
; This source file contains ARM algorithms for checking register arguments
; passed to a macro.
; Each is implemented in the form of a MACRO so that it can inlined.
;

	; Global value that will hold list of registers used
    GBLA      DISTINCT_WORD

;==========================================================================
;
; DISTINCT
;
; Checks that the register list passed contains no duplicate
; registers.
;
; Used to check that the registers passed to a macro are distinct.
;==========================================================================

    MACRO
    DIFFTHAN $a
		IF ( "$a" <> "" )
			; Check register has not been used previously (no bit set)
			ASSERT ( ( DISTINCT_WORD :AND:( 1 << $a ) ) = 0 )
			; Set the bit for the given register in list of registers used
DISTINCT_WORD SETA ( DISTINCT_WORD :OR:( 1<<$a ) )
		ENDIF
    MEND


    MACRO
    DISTINCT $a, $b, $c, $d, $e, $f, $g, $h, $i, $j, $k, $l, $m, $n, $o, $p
DISTINCT_WORD SETA 0	; Initialise the registers used to none
		
		DIFFTHAN $a
		DIFFTHAN $b
		DIFFTHAN $c
		DIFFTHAN $d
		DIFFTHAN $e
		DIFFTHAN $f
		DIFFTHAN $g
		DIFFTHAN $h
		DIFFTHAN $i
		DIFFTHAN $j
		DIFFTHAN $k
		DIFFTHAN $l
		DIFFTHAN $m
		DIFFTHAN $n
		DIFFTHAN $o
    MEND

;==========================================================================
;
; ORDER
;
; ARM assembler macro which checks that the register list passed is in 
; ascending order.
;
; Used to check that the registers in an LDM/STM are correct.
;
; Can't handle ranges (yet!)
;==========================================================================

	MACRO
	LESSTHAN $a, $b
		IF ( ( "$a" <> "" ):LAND:( "$b" <> "" ) )
			ASSERT ( $a < $b ) ; Check register order for LDM or STM
		ENDIF
	MEND


    MACRO
    ORDER $a, $b, $c, $d, $e, $f, $g, $h, $i, $j, $k, $l, $m, $n, $o, $p
		LESSTHAN $a, $b
		LESSTHAN $b, $c
		LESSTHAN $c, $d
		LESSTHAN $d, $e
		LESSTHAN $e, $f
		LESSTHAN $f, $g
		LESSTHAN $g, $h
		LESSTHAN $h, $i
		LESSTHAN $i, $j
		LESSTHAN $j, $k
		LESSTHAN $k, $l
		LESSTHAN $l, $m
		LESSTHAN $m, $n
		LESSTHAN $n, $o
		LESSTHAN $o, $p
    MEND
    
; END
    
    END
