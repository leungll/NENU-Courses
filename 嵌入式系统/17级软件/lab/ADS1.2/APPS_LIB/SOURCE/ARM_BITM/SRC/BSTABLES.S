;/*
; * Bit Manipulation assembler lookup tables
; * Copyright (C) ARM Limited 1996,1998-1999. All rights reserved.
; */

;===========================================================================
;
; Bit set table.
;
; Date: 13/09/1996
;
;===========================================================================

	EXPORT BitSetTable
	
	AREA |C$$DATA|, DATA, READONLY
	
;-----------------------------------------------------------------------
;
; BitSetTable
;
; Lookup table used to find bit set
;
;-----------------------------------------------------------------------
;
; The first entry (32) should be set to whatever result is wanted for an 
; operand of 0 in the following table. 255 can be anything: 
; the entries containing 255 are neverused.
;
BitSetTable
    DCB      32,   0,   1,  12,   2,   6, 255,  13
    DCB       3, 255,   7, 255, 255, 255, 255,  14
    DCB      10,   4, 255, 255,   8, 255, 255,  25
    DCB		255, 255, 255, 255, 255,  21,  27,  15
    DCB      31,  11,   5, 255, 255, 255, 255, 255
    DCB       9, 255, 255,  24, 255, 255,  20,  26
    DCB      30, 255, 255, 255, 255,  23, 255,  19
    DCB      29, 255,  22,  18,  28,  17,  16, 255

	END