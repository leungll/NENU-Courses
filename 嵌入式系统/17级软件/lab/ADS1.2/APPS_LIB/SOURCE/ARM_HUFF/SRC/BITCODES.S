;/*
; * Bit code assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	INCLUDE intworkm.h						; include interworking macros

	AREA	|C$$code|, CODE, READONLY $interwork

CODEWBITS	* 27							; number of bits in entry in codeword table that comprise actual codeword
											; all remaining bits at the top of the word give the length of the codeword
											; this must be the same value used to construct the codeword table that is passed

; define the local register names used for the functions
fin_stream	RN	0

source		RN  0
n			RN  1
streamstr	RN	2
codes		RN  3

deststream	RN  2
bits		RN  8
srcword		RN  9
dstword		RN 10
codeword	RN 11
byte		RN codeword
hword		RN codeword
t			RN 12

	INCLUDE	datam.h							; include the load and store operations
	INCLUDE processm.h						; include the main generic byte, halfword and word operations
	INCLUDE regchekm.h						; include distinct register checking macro
	
GENBITCODE		EQU	1						; 1 = support general bit coding function, 0 do not support
											; if this is given as 1, byte, halfword and word data bit coding are supported
											; regardless of the condition of their flags that follow

BYTEBITCODE		EQU	1						; 1 = support bit coding function for byte data, 0 do not support
HWORDBITCODE	EQU	1						; 1 = support bit coding function for halfword data, 0 do not support
WORDBITCODE		EQU	1						; 1 = support bit coding function for word data, 0 do not support

	;---------------------------------------------------------------
	; initialise bit coding
	;
	; saves registers, gets bit stream and bit position and loads 
	; in any previously incomplete destination word else 
	; initialise the destination word to zero
	;
	; $streamstr		register: pointer to a structure that must contain
	;					an unsigned character array as first entry that is
	; 					the bitstream to use and an
	;					unsigned integer as second entry that is the
	;					bit position in this array to start from
	; $deststream		register: to hold address of bit stream
	; $bits				register: to hold bit position in the stream
	; $dstword			register: to hold the current coded word
	; $t				register: temporary
	;
	; $deststream, $bits, $dstword and $t must all be distinct
	;
	;---------------------------------------------------------------
	MACRO
	INITIALISEBITCODING $streamstr, $deststream, $bits, $dstword, $t
	    ; check that registers are distinct
	    DISTINCT $deststream, $bits, $dstword, $t

		STMFD	sp!, { $streamstr, R8 - R12, lr }	; save registers including the state structure pointer
													; the state structure is saved to be updated at the end of the function
		
		LDMIA	$streamstr, { $deststream, $bits }	; load the destination bit stream and bit position in that stream
		
		CMP		$bits, #32					; check if bit position is part way through a word (4 bytes = 32 bits)
		LDRNE	$dstword, [ $deststream ]	; load the incomplete destination word if bits is not 32 so that coding can
											; continue from the last bit position reached or actual start of memory for stream
		MOVEQ	$dstword, #0				; initialise to destination word to 0 if not starting part way through a word

		IF {ENDIAN} = "little"				; the main coding function operates in big endian mode so if the data is little
			BYTEREV $dstword, $dstword, $t	; endian the bytes need reversing into big endian order
		ENDIF
	MEND
	
	;---------------------------------------------------------------
	; code the current symbol
	;
	; given the current symbol it is coded into a variable length
	; codeword which is added to the destination stream
	;
	; $codes			register: array of symbol-to-codewords
	; $symbol			register: symbol to code
	; $codeword			register: to hold the codeword
	; $bits				register: number of bits free in $dstword
	; $dstword			register: current coded word
	; $deststream		register: bit stream to write $dstword when full
	; $t				register: temporary
	; $datasize			the size of the symbols
	; $symbolposinword	the position of the symbol in $symbol
	;
	;					this is supplied by PROCESS... macro
	;
	; $codeword, $bits, $dstword, $deststream and $t must be distinct
	; $codeword must be distinct from $codes
	;
	;---------------------------------------------------------------
	MACRO
	BITCODE $codes, $symbol, $codeword, $bits, $dstword, $deststream, $t, $datasize, $symbolposinword
		; check registers are distinct
		DISTINCT $codeword, $bits, $dstword, $deststream
		DISTINCT $codeword, $codes
		
		; load the next codeword from the table with the entry referenced by the symbol to code
		; LOADDATA asserts that $datasize is of the correct size
		LOADDATA 		$codes, $symbol, $codeword, $codeword, $datasize, $symbolposinword
		; add the codeword to the stream word, update the number of bits free in word and, if full, save it out
		ADDCODETOSTREAM $codeword, $bits, $dstword, $deststream, $t
	MEND
	
	;---------------------------------------------------------------
	; add codeword to stream
	;
	; given a codeword it is added to the destination stream word
	; and if the word is full, the word is saved out and a new word
	; started
	;
	; $codeword			register: the codeword to add
	; $bits				register: number of bits free in $dstword
	; $dstword			register: current coded word
	; $deststream		register: bit stream to write $dstword when full
	; $t				register: temporary
	;
	; all registers must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	ADDCODETOSTREAM $codeword, $bits, $dstword, $deststream, $t
	    ; check that registers are distinct
	    DISTINCT $codeword, $bits, $dstword, $deststream, $t

		SUBS $bits, $bits, $codeword, LSR #CODEWBITS	; the top (32-CODEWBITS) bits of the codeword contain the length of the codeword
														; being added to the stream word
											; this value is subtracted from $bits to leave the number of bits free in the stream
											; word before it must be saved out after this codeword is added to the word
		BIC $codeword, $codeword, #31 << CODEWBITS	; clear the codeword length from the codeword which can is between 1 and 27 in value
													; and is held in the next 5 bits after the codeword bits which are defined as the first
											; CODEWBITS
											; 31 will clear any bits of the 5 bits that are set of the length
											; since all 5 bits are set in the binary expression for 31
		BGE %FT0	; add_code_to_stream	; if $bits >= 0 then the destination word after the current codeword is added will not overflow
											; its 32 bits and so the codeword can be added
											; if this is not true the codeword is too long to fit the destination stream word and must be
											; broken into parts, added to the stream word until full, saved and then the remainder added to
											; the next word
		RSB $bits, $bits, #0				; if $bits < 0 then codeword is too large to fit into destination stream word
											; so set $bits = 0 - $bits = -$bits which gives $bits as positive and gives the
											; number of bits of codeword that are too much to fit into the stream word
		ORR $dstword, $dstword, $codeword, LSR $bits	; now codeword is too large by $bits thus, these bits must be
														; removed from the codeword before it can be added into the stream
											; hence LSR $bits keeps only those bits that fit, shifted to low
											; bits of the codeword and added to stream

		IF {ENDIAN} = "little"				; the bit operations are big endian but if the coding is performed in little endian mode
			BYTEREV $dstword, $dstword, $t	; then the bytes of a word need reversing to make them little endian before they can be saved
		ENDIF

		STR $dstword, [ $deststream ], #4	; the stream word is now full so save it out
		RSB $bits, $bits, #32				; $bits = 32 - $bits
											; this gives the number of bits free in the stream word after the remainder of the codeword
											; has been added
											; it also defines the shift necessary to keep those bits that were not added to the stream
											; previously
		MOV $dstword, #0					; zero initialise the destination word for next 32-bits onto stream and drop
											; through to continue adding the codeword that overflowed destination word
		
0; add_code_to_stream
		ORR $dstword, $dstword, $codeword, LSL $bits	; add the codeword to destination stream word shifting the
														; codeword up by $bits to place it into the next available free
														; bits of the stream working from top bit to low bit
	MEND
	
	;---------------------------------------------------------------
	; end bit coding process
	;
	; save the last coded data, save the last bit stream and position
	; reached in the stream to the structure, restore registers and return
	;
	; $bits				register: number of bits free in $dstword
	; $dstword			register: current coded word
	; $deststream		register: bit stream to write $dstword
	; $finaldeststreamaddress
	;					register: to hold final stream structure returned
	; $t				register: temporary
	;
	; $bits, $dstword, $deststream and $t must all be distinct
	;
	;---------------------------------------------------------------
	MACRO
	ENDBITCODING $bits, $dstword, $deststream, $finaldeststreamaddress, $t
	    ; check that registers are distinct
	    DISTINCT $bits, $dstword, $deststream, $t

		IF {ENDIAN} = "little"				; the bit operations are big endian but if the coding is performed in little endian mode
			BYTEREV $dstword, $dstword, $t	; then the byte of a word need reversing to make them little endian before they can be saved
		ENDIF

		STR		$dstword, [ $deststream ]	; store last destination stream word that has not previously been saved
		CMP		$bits, #0					; check if destination word is completely full
		ADDEQ	$deststream, $deststream, #4	; if destination word is full, increment destination pointer to next
												; position so next data will be added to end of data already coded
											; if the stream word was not full, the pointer is not incremented so that if the coder is
											; called again coding will continue into the last bit position that was reached thus the 
											; incomplete word that has just been saved will need to be read back in again
		
		LDMFD	sp!, { $t }					; read the state structure parameter from the stack that was saved at initialisation
											; the structure is read into $t since $finaldeststreamaddress could easily be one of
											; $deststream or $bits which are still required
		STMIA	$t, { $deststream, $bits }	; store the new bit stream pointer and number of bits free in next word referenced by stream
		MOV		$finaldeststreamaddress, $t	; set up the return register with the returned structure
		
		RETURN	"R8 - R12","","",""			; coding complete, restore registers and return (rlist, sp, lr, no condition)
	MEND
	
; --------------------
;
; function entry point
;
; --------------------
	
	;---------------------------------------------------------------
	; general bit coding
	;
	; call the appropriate bit coding function for given size of data
	;
	; source		register: the source data to code as bytes,
	;							halfwords or words
	; n				register: the number of data items to code
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to use and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; codes			register: symbol-to-codeword table
	; datatype		stacked 8, 16 or 32 as size of symbol data
	;
	;---------------------------------------------------------------
	IF GENBITCODE = 1
		; define the general bit coding function as necessary which requires all other bit coding functions to be defined
		EXPORT	BitCodeSymbols

BitCodeSymbols
		LDMFD	sp, { R12 }					; get "datatype" variable from stack, leaving stack pointer referencing it

		CMP		R12, #8						; if "datatype" is 8 then the data is bytes
		BEQ		BitCodeByteSymbols

		CMP		R12, #16					; if "datatype" is 16 then the data is halfwords
		BEQ		BitCodeHalfWordSymbols
		
		CMP		R12, #32					; if "datatype" is 32 then the data is words
											; this check is made to ensure that no other size can be given
		BEQ		BitCodeWordSymbols
		
		; if this point is reached the value of "datatype" was incorrect so just return
		MOV		fin_stream, streamstr		; expected return is the state structure so move this into the return register
		RETURN	"","","",""					; return (no rlist, sp, lr, no condition)
	ENDIF

	;---------------------------------------------------------------
	; byte bit coding
	;
	; bit code byte symbols to variable length codewords
	;
	; source		register: the source data to code as bytes
	; n				register: the number of bytes to code
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to use and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; codes			register: symbol-to-codeword table
	;
	;---------------------------------------------------------------
	IF GENBITCODE = 1 :LOR: BYTEBITCODE = 1
		; define the byte coding function as necessary
		EXPORT	BitCodeByteSymbols

BitCodeByteSymbols
		; initialise the bit coder - save registers and set up first stream word
		INITIALISEBITCODING streamstr, deststream, bits, dstword, t
		
		; process the source data as bytes calling the bit coding for each source byte
		PROCESSBYTES n, source, srcword, byte, t, "BITCODE codes, byte, codeword, bits, dstword, deststream, t, 32"
		
		; end the bit coder - ensure all data is saved, restore the registers and return
		ENDBITCODING bits, dstword, deststream, fin_stream, t
	ENDIF

	;---------------------------------------------------------------
	; halfword bit coding
	;
	; bit code halfword symbols to variable length codewords
	;
	; source		register: the source data to code as halfwords
	; n				register: the number of halfwords to code
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to use and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; codes			register: symbol-to-codeword table
	;
	;---------------------------------------------------------------
	IF GENBITCODE = 1 :LOR: HWORDBITCODE = 1
		; define the halfword coding function as necessary
		EXPORT	BitCodeHalfWordSymbols

BitCodeHalfWordSymbols
		; initialise the bit coder - save registers and set up first stream word
		INITIALISEBITCODING streamstr, deststream, bits, dstword, t
		
		; process the source data as halfwords calling the bit coding for each source halfword
		PROCESSHWORDS n, source, srcword, hword, "BITCODE codes, hword, codeword, bits, dstword, deststream, t, 32"
		
		; end the bit coder - ensure all data is saved, restore the registers and return
		ENDBITCODING bits, dstword, deststream, fin_stream, t
	ENDIF

	;---------------------------------------------------------------
	; word bit coding
	;
	; bit code word symbols to variable length codewords
	;
	; source		register: the source data to code as words
	; n				register: the number of words to code
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to use and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; codes			register: symbol-to-codeword table
	;
	;---------------------------------------------------------------
	IF GENBITCODE = 1 :LOR: WORDBITCODE = 1
		; define the word coding function as necessary
		EXPORT	BitCodeWordSymbols

BitCodeWordSymbols
		; initialise the bit coder - save registers and set up first stream word
		INITIALISEBITCODING streamstr, deststream, bits, dstword, t
		
		; process the source data as words calling the bit coding for each source word
		PROCESSWORDS n, source, srcword, "BITCODE codes, srcword, codeword, bits, dstword, deststream, t, 32"
		
		; end the bit coder - ensure all data is saved, restore the registers and return
		ENDBITCODING bits, dstword, deststream, fin_stream, t
	ENDIF


	END
