;/*
; * Count assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	INCLUDE intworkm.h						; include interworking macros

	AREA	|C$$code|, CODE, READONLY $interwork

; define the local register names used for the functions
source	RN  0
n		RN  1
counts	RN  2
add		RN  3

srcword	RN 10
scount	RN 11
byte	RN 12
hword	RN byte
t		RN lr

	INCLUDE	datam.h							; include the load and store operations
	INCLUDE processm.h						; include the main generic byte, halfword and word operations
	INCLUDE regchekm.h						; include distinct register checking macro
	
GENCOUNT		EQU	1						; 1 = support general counting function, 0 do not support
											; if this is given as 1, byte, halfword and word data counting are supported
											; regardless of the condition of their flags that follow

BYTECOUNT		EQU	1						; 1 = support counting function for byte data, 0 do not support
HWORDCOUNT		EQU	1						; 1 = support counting function for halfword data, 0 do not support
WORDCOUNT		EQU	1						; 1 = support counting function for word data, 0 do not support
	
	;---------------------------------------------------------------
	; initialise counting
	;
	; saves registers
	;
	;---------------------------------------------------------------
	MACRO
	INITIALISECOUNTING
		STMFD	sp!, { R10 - R11, lr }		; save registers
	MEND
	
	;---------------------------------------------------------------
	; count the current symbol
	;
	; given the current symbol its count for frequency of occurrence
	; in the data is incremented
	;
	; $counts			register: array of symbol counts
	; $symbol			register: symbol to count
	; $symbolcount		register: to hold the symbol count
	; $add				register: increment for count
	; $t				register: temporary
	; $datasize			the size of the symbols
	; $symbolposinword	the position of the symbol in $symbol
	;
	;					this is supplied by PROCESS... macro
	;
	; $symbolcount, $counts, $symbol and $add must be disinct
	; $add and $t must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	COUNT $counts, $symbol, $symbolcount, $add, $t, $datasize, $symbolposinword
		; check registers are disinct
		DISTINCT $symbolcount, $counts, $symbol, $add
		DISTINCT $add, $t
		
		LOADDATA $counts, $symbol, $symbolcount, $t, $datasize, $symbolposinword
		ADDTOCOUNT $symbolcount, $add
		STOREDATA $counts, $symbol, $symbolcount, $t, $datasize, $symbolposinword
	MEND
	
	;---------------------------------------------------------------
	; increment count
	;
	; add increment value to previous symbol count
	;
	;---------------------------------------------------------------
	MACRO
	ADDTOCOUNT $symbolcount, $add
		ADD $symbolcount, $symbolcount, $add	; increment counter by $add
	MEND

	;---------------------------------------------------------------
	; end counting
	;
	; restores registers and returns
	;
	;---------------------------------------------------------------
	MACRO
	ENDCOUNTING
		RETURN	"R10 - R11","","",""		; counting complete, restore registers and return (rlist, sp, lr, no condition)
	MEND
	
; --------------------
;
; function entry point
;
; --------------------
	
	;---------------------------------------------------------------
	; general counting
	;
	; call the appropriate counting function for given size of data
	;
	; source		register: the source data to count as bytes,
	;							halfwords or words
	; n				register: the number of data items to count
	; counts		register: array to hold counts for symbols
	; add			register: counting increment
	; datatype		stacked 8, 16 or 32 as size of symbol data
	;
	;---------------------------------------------------------------
	IF GENCOUNT = 1
		; define the general count function as necessary which requires all other counting functions to be defined
		EXPORT	CountSymbols

CountSymbols
		LDMFD	sp, { R12 }					; get "datatype" variable from stack, leaving stack pointer referencing it

		CMP		R12, #8						; if "datatype" is 8 then the data is bytes
		BEQ		CountByteSymbols

		CMP		R12, #16					; if "datatype" is 16 then the data is halfwords
		BEQ		CountHalfWordSymbols
		
		CMP		R12, #32					; if "datatype" is 32 then the data is words
											; this check is made to ensure that no other size can be given
		BEQ		CountWordSymbols
		
		; if this point is reached the value of "datatype" was incorrect so just return
		RETURN	"","","",""					; return (no rlist, sp, lr, no condition)
	ENDIF

	;---------------------------------------------------------------
	; byte counting
	;
	; count frequency of occurrence of each byte symbol
	;
	; source		register: the source data to count as bytes
	; n				register: the number of data items to count
	; counts		register: array to hold counts for symbols
	; add			register: counting increment
	;
	;---------------------------------------------------------------
	IF GENCOUNT = 1 :LOR: BYTECOUNT = 1
		; define the byte counting function as necessary
		EXPORT	CountByteSymbols

CountByteSymbols
		INITIALISECOUNTING
		
		; process the source data as bytes calling the counting macro for each source byte
		PROCESSBYTES n, source, srcword, byte, t, "COUNT counts, byte, scount, add, t, 32"	 ; counts is 32 bits
	
		ENDCOUNTING
	ENDIF

	;---------------------------------------------------------------
	; halfword counting
	;
	; count frequency of occurrence of each halfword symbol
	;
	; source		register: the source data to count as halfwords
	; n				register: the number of data items to count
	; counts		register: array to hold counts for symbols
	; add			register: counting increment
	;
	;---------------------------------------------------------------
	IF GENCOUNT = 1 :LOR: HWORDCOUNT = 1
		; define the halfword counting function as necessary
		EXPORT	CountHalfWordSymbols

CountHalfWordSymbols
		INITIALISECOUNTING
				
		; process the source data as halfwords calling the counting macro for each source halfword
		PROCESSHWORDS n, source, srcword, hword, "COUNT counts, hword, scount, add, t, 32"	 ; counts is 32 bits
	
		ENDCOUNTING
	ENDIF

	;---------------------------------------------------------------
	; word counting
	;
	; count frequency of occurrence of each word symbol
	;
	; source		register: the source data to count as words
	; n				register: the number of data items to count
	; counts		register: array to hold counts for symbols
	; add			register: counting increment
	;
	;---------------------------------------------------------------
	IF GENCOUNT = 1 :LOR: WORDCOUNT = 1
		; define the word counting function as necessary
		EXPORT	CountWordSymbols

CountWordSymbols
		INITIALISECOUNTING
		
		; process the source data as words calling the counting macro for each source word
		PROCESSWORDS n, source, srcword, "COUNT counts, srcword, scount, add, t, 32"	 ; counts is 32 bits
	
		ENDCOUNTING
	ENDIF
	

	END
