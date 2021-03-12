;/*
; * Bit decode assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	INCLUDE intworkm.h						; include interworking macros

	AREA	|C$$code|, CODE, READONLY $interwork

	; load and store of halfword operations is required which has specific instructions defined in architecture 4 or later
	; if architecture 4 or later is not available other instructions must be used to simulate the halfword instructions
	;
	; define, therefore, a flag which sets the instructions as appropriate for the architecture supported
	GBLL	ARCHITECTURE_4
	
ARCHITECTURE_4 SETL	:LNOT:( {ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M" )
	
TABLEBITS	* 10							; length of codeword in bits in the decoding tables that can be decoded directly
											; all remaining codeword lengths over this being decoded by decoding trees
											; this must be the same value used to construct the decoding tables/trees that are passed

; define the local register names used for the functions
fin_stream	RN	0

streamstr	RN	0
n			RN  1
dest		RN  2
lentable	RN  3
symtable	RN  4

source		RN  0
lenwalk 	RN  5
symwalk 	RN  6

bits		RN  7
srcword		RN  8
word		RN  9
dstword		RN 10
symbol		RN 11
codebits	RN 12

t			RN codebits
byte		RN codebits

	INCLUDE	datam.h							; include the load and store operations
	INCLUDE regchekm.h						; include distinct register checking macro
	
GENBITDECODE	EQU	1						; 1 = support general bit decoding function, 0 do not support
											; if this is given as 1, byte, halfword and word data bit decoding are supported
											; regardless of the condition of their flags that follow

BYTEBITDECODE	EQU	1						; 1 = support bit decoding function for byte data, 0 do not support
HWORDBITDECODE	EQU	1						; 1 = support bit decoding function for halfword data, 0 do not support
WORDBITDECODE	EQU	1						; 1 = support bit decoding function for word data, 0 do not support
	
	;---------------------------------------------------------------
	; initialise bit decoding
	;
	; saves registers, gets bit stream and bit position and loads 
	; next two words of data for decoding (if they exist)
	;
	; $streamstr		register: pointer to a structure that must contain
	;					an unsigned character array as first entry that is
	; 					the bitstream to use and an
	;					unsigned integer as second entry that is the
	;					bit position in this array to start from
	; $lentable			register: pointer to decoding length table
	; $symtable			register: pointer to decoding symbol table
	; $lenwalk			register: to hold pointer to decoding length tree
	; $symwalk			register: to hold pointer to decoding symbol tree
	; $bits				register: to hold bit position in the stream
	; $source			register: to hold address of bit stream
	; $srcword			register: to hold current word for decoding
	; $word				register: to hold top-up word for decoding
	; $t				register: temporary
	; $datasize			the size of the symbols
	;
	; $streamstr, $symtable, $lenwalk, $symwalk and $t must be distinct
	; $lentable, $symtable, $lenwalk, $symwalk, $bits, $source, $srcword 
	;		and $word must be distinct
	; $t and $bits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	INITIALISEBITDECODING $streamstr, $lentable, $symtable, $lenwalk, $symwalk, $bits, $source, $srcword, $word, $t, $datasize
		ASSERT ( $datasize = 8 :LOR: $datasize = 16 :LOR: $datasize = 32 )	; ensure that $datasize is valid
		
		; check registers are distinct
		DISTINCT	$streamstr, $symtable, $lenwalk, $symwalk, $t
		DISTINCT	$lentable, $symtable, $lenwalk, $symwalk, $bits, $source, $srcword, $word
		DISTINCT	$t, $bits
		
		MOV		$t, sp						; save the stack register on entry
		STMFD	sp!, { $streamstr, R4 - R11, lr }	; save registers including the state structure pointer
		LDR		$symtable, [ $t ]			; get the fifth parameter, the symbol table, which is on the stack
		
		ADD		$lenwalk, $lentable, #1 << TABLEBITS	; set the start of tree for lengths, $lentable being bytes
		
		; set the start of tree for symbols which is dependent on the size of the data
		IF $datasize = 8					; $symtable is array of bytes
			ADD		$symwalk, $symtable, #1 << TABLEBITS
		ELSE
			IF $datasize = 16				; $symtable is array of halfwords
				ADD		$symwalk, $symtable, #1 << ( TABLEBITS + 1 )
			ELSE							; $symtable is array of words
				ADD		$symwalk, $symtable, #1 << ( TABLEBITS + 2 )
			ENDIF
		ENDIF
		
		LDMIA	$streamstr, { $source, $bits }	; load bit stream to decode and the bit position to start from in the stream
											
		LDMIA	$source!, { $srcword, $word }	; load in two words of bits from the source stream and increment 
												; the pointer to next un-read position
											; the first word is the first 32-bits for decoding, the second is the
											; refill word used to keep the word being decoded topped up with bits
	
		IF {ENDIAN} = "little"				; the main decoding function operates in big endian mode so if the data is little
			BYTEREV $srcword, $srcword, $t	; endian the bytes need reversing into big endian mode
			BYTEREV $word, $word, $t
		ENDIF

		CMP		$bits, #32					; check if bit position is part way through a word (4 bytes = 32 bits)
		RSBNE	$t, $bits, #32				; if $bits != 32, set $t = 32 - $bits
											; $bits gives the number of bits free in word that keeps decoding word topped up and
											; thus $t gives the number of bits in word for decoding that have previously been
											; decoded and therefore need clearing
		MOVNE	$srcword, $srcword, LSL $t	; re-pack the word being decoded by clearing out the previously decoded bits
											; so that actual next bits for decoding are contained from top bit down 
											; through word
		ORRNE	$srcword, $srcword, $word, LSR bits	; refill word for decoding so that all free bits are now filled with next
													; bits for decoding read from top up word
											; these bits are contained in the top $bits of the top-up word and required 
											; in the bottom $bits of the word for decoding hence the shift right
	MEND

	;---------------------------------------------------------------
	; load data
	;
	; load next codeword length and symbol for given codeword
	;
	; the data read might reference a tree to traverse
	;
	; $lentable			register: memory address of length table
	; $symtable			register: memory address of bytes, 
	;								halfwords or words symbol table
	; $srcword			register: codeword index into the tables
	; $codebits			register: to hold length table data read
	; $symbol			register: to hold symbol data read
	; $datasize			the size of the data items in the array - 8, 16 or 32 bits
	; $indexposinword	the position codeword in $srcword to use as index
	;
	; $symtable must be distinct from $symbol
	; $srcword and $codebits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	LOADSYMBOLANDLENGTH $lentable, $symtable, $srcword, $codebits, $symbol, $datasize, $indexposinword
		; check registers are distinct
		DISTINCT $srcword, $codebits
		
		; load the next length information from byte length table
		; 255 is returned if symbol to be read describes tree internal node else gives decoded codeword length
		IF $indexposinword = 0				; index given directly in bottom 8 bits
			LDRB	$codebits, [ $lentable, $srcword ]
		ELSE								; index needs shifting into bottom 8 bits first
			LDRB	$codebits, [ $lentable, $srcword, LSR #$indexposinword ]
		ENDIF
		
		; load the next symbol information
		; this references an internal tree node is length is 255 else symbol to decode to
		; this checks the value in datasize
		LOADDATA $symtable, $srcword, $symbol, $symbol, $datasize, $indexposinword
	MEND

	; decode the next codeword to a symbol and length of codeword that has been decoded
	;---------------------------------------------------------------
	; load data
	;
	; load next codeword length and symbol for given codeword
	;
	; the data read might reference a tree to traverse
	;
	; $lentable			register: memory address of length table
	; $symtable			register: memory address of bytes, 
	;								halfwords or words symbol table
	; $srcword			register: word of current data to decode
	; $word				register: top-up word for $srcword
	; $bits				register: number of bits left before $word exhausted
	; $codebits			register: to hold length table data read
	; $symbol			register: to hold symbol data read
	; $datasize			the size of the data items in the array - 8, 16 or 32 bits
	;
	; $symtable must be distinct from $symbol
	; $srcword, $codebits, $bits and $word must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, $datasize
		; check registers are distinct
		DISTINCT $bits, $codebits, $srcword, $word
		
		; load next length and symbol information using only bottom TABLEBITS of $srcword as codeword lookup index
		LOADSYMBOLANDLENGTH $lentable, $symtable, $srcword, $codebits, $symbol, $datasize, 32-TABLEBITS

		SUBS	$bits, $bits, $codebits		; calculate the number of bits that will remain in the top-up word before it is
											; after the current codeword is decoded, removed from decoding word and the top-up
											; word used to top-up the decoding word
											; $codebits may at this point be 255 however and thus this may not be true at this point

		MOVGE	$srcword, $srcword, LSL $codebits	; if $bits >= 0, remove the codeword that is being decoded from the decoding
													; word and shift all remaining bits into the top freeing the bottom
		
		; datasize is known to be correct here since it was checked by LOADSYMBOLANDLENGTH
		; set up branch for tree or refilling decoding word based on data size
		IF $datasize = 8					; byte data
			BLLT    tree_or_refill_byte		; if $bits < 0, escape to either perform a tree walk ($codebits = 255) or to
											; refill the top-up word from memory since there are not enough bits left in it
											; to refill the decoding word after the codeword has been decoded
											; (this will happen less often than a straight drop through in either case and thus
											; the code is written so that most cases require minimum number of cycles with 
											; special cases requiring more work)
		ELSE
			IF $datasize = 16				; halfword data
				BLLT	tree_or_refill_hword
			ELSE
				BLLT	tree_or_refill_word	; word data
			ENDIF
		ENDIF
		
		ORR		$srcword, $srcword, $word, LSR $bits	; refill the bottom bits of the word being decoded with the 
														; next bits from the top-up word which are at the top of the word and need
														; shifting down
	MEND

	;---------------------------------------------------------------
	; end bit decoding process
	;
	; save the last bit stream and position reached in the stream 
	; to the structure, restore registers and return
	;
	; $bits				register: number of bits free in $dstword
	; $source			register: bit stream data is decoded from
	; $finaldeststreamaddress
	;					register: to hold final stream structure returned
	; $t				register: temporary
	;
	; $bits, $source, and $t must all be distinct
	;
	;---------------------------------------------------------------
	MACRO
	ENDBITDECODING $bits, $source, $finalstreamaddress, $t
		; check registers are distinct
		DISTINCT $bits, $source, $t
		
		CMP		$bits, #0					; check if top-up word has been completely exhausted
		ADDEQ	$source, $source, #4		; if the top-up word has been exhausted, move to the next memory location to read
											; the next top-up word in else leave the location so that top-up word can be read
											; back in again with current data
		SUB		$source, $source, #8		; subtract two words from pointer so that if the decoder is called again
											; the word for decoding will be read back with the data that is contains now
											; and the top-up word will be the next set of data to read in
		
		
		LDMFD	sp!, { $t }					; read the state structure parameter from the stack that was saved at initialisation
											; the structure is read into $t since $finalstreamaddress could easily be one of
											; $source or $bits which are still required
		STMIA	$t, { $source, $bits }		; store the bit stream pointer reached and number of bits free in top-up word
		MOV		$finalstreamaddress, $t		; set up the return register with the returned structure
		
		RETURN	"R4 - R11","","",""			; decoding complete, restore registers and return (rlist, sp, lr, no condition)
	MEND
	
	;---------------------------------------------------------------
	; decode to an array of bytes
	;
	; decode variable length codewords to byte symbols
	;
	; $nbytes		register: number of bytes to decode
	; $bytedest		register: an array to store bytes decoded
	; $dstword		register: to hold decoded bytes before saving
	; $lentable		register: decoding length table
	; $symtable		register: decoding symbol table
	; $srcword		register: current word being decoded
	; $word			register: top-up for $srcword
	; $bits			register: number of bits before $word is exhausted
	; $codebits		register: to hold each length of codeword being decoded
	; $symbol		register: to hold each decoded symbol
	; $t			register: temporary
	;
	; $nbytes, $bytedest, $dstword, $lentable, $symtable, $srcword, $word,
	; $bits, $codebits and $symbol must all be distinct
	;
	; $t must be distinct from all registers except $codebits and $symbol
	;
	;---------------------------------------------------------------
	MACRO
	DECODETOBYTES $nbytes, $bytedest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, $t
		; check registers are distinct
		DISTINCT $nbytes, $bytedest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol
		DISTINCT $t, $nbytes, $bytedest, $dstword, $lentable, $symtable, $srcword, $word, $bits
		
		SUBS	$nbytes, $nbytes, #4		; check that there are at least 4 bytes (1 word)...
		BLT		%FT7 ; decode_bytes			; ...if <4 bytes, cannot operate on words so process as bytes
		
		ANDS	$t, $bytedest, #3			; check that pointer is word-aligned (low 2-bits clear)...
		BEQ		%FT0 ; get_4_decoded_bytes	; ...if word aligned begin processing over words
		
		LDR		$dstword, [$bytedest, -$t]!	; ...else get initial (incomplete) destination word
											; adjusting the pointer to make it word-aligned and leave the
											; pointer in its adjusted state

		ADD		$nbytes, $nbytes, $t		; 4 has already been subtracted for word operations, however the
											; byte offset for pointer indicates how many bytes have already been
											; decoded into the destination and thus how many less will be
											; decoded for the first word
	
		CMP		$t, #2						; comparison used for branch to operate on bytes obtained
		IF {ENDIAN} = "little"
			BIC	$dstword, $dstword, #255 << 24	; clear top 8 bits of $dstword since required to hold data
												; after operation which will be added by ADDing into bits
												; 1 <= $t <= 3
		ELSE
			BIC	$dstword, $dstword, #255		; as for little but clear bottom 8 bits
		ENDIF
		BGT		%FT4 ; get_decoded_byte_3	; $t = 3 bytes already decoded into, jump to start of decoding with 1 byte remaining
		IF {ENDIAN} = "little"
			BIC	$dstword, $dstword, #255 << 16	; clear bits 16-23 of $dstword since required to hold data
												; after operation which will be added by ADDing into bits
												; top 8-bits are also clear by previous operation
											; where passed over branch instruction
											; 2 <= $t <= 3
		ELSE
			BIC	$dstword, $dstword, #255 << 8	; as for little but clear bits 8-15
		ENDIF
		BEQ		%FT3 ; get_decoded_byte_2	; $t = 2 bytes already decoded into, jump to start of decoding with 2 bytes remaining
		IF {ENDIAN} = "little"
			BIC	$dstword, $dstword, #255 << 8	; clear bits 8-15 of $dstword since required to hold data
												; after operation which will be added by ADDing into bits
												; bits 16-31 are also clear by previous two operations
											; where passed over two branch instructions to here
											; $t = 3
		ELSE
			BIC	$dstword, $dstword, #255 << 16	; as for little but clear bits 16-23
		ENDIF
		BLT		%FT2 ; get_decoded_byte_1	; $t = 1 byte already decoded to, jump to start of decoding with 3 bytes remaining
											; all values of $t covered
											; could use just B (branch) here without a test as always true at this point
	
; for each codeword decode it to a byte symbol

0 ; get_4_decoded_bytes

1 ; get_decoded_byte_0
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 8
		IF {ENDIAN} = "little"
			ADD		$dstword, $symbol, #0	; add decoded byte as bits 0-7 (bottom byte)
		ELSE
			MOV		$dstword, #0			; clear the destination word
			ADD		$dstword, $dstword, $symbol, LSL #24	; add decoded byte as bits 24-31 (top byte)
		ENDIF
	
2 ; get_decoded_byte_1
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 8
		IF {ENDIAN} = "little"
			ADD		$dstword, $dstword, $symbol, LSL #8	; add the decoded byte as bits 8-15
		ELSE
			ADD		$dstword, $dstword, $symbol, LSL #16	; add the decoded byte as bits 16-23
		ENDIF
	
3 ; get_decoded_byte_2
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 8
		IF {ENDIAN} = "little"
			ADD		$dstword, $dstword, $symbol, LSL #16	; add the decoded byte as bits 16-23
		ELSE
			ADD		$dstword, $dstword, $symbol, LSL #8	; add the decoded byte as bits 8-15
		ENDIF
	
4 ; get_decoded_byte_3
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 8
		IF {ENDIAN} = "little"
			ADD		$dstword, $dstword, $symbol, LSL #24	; add the decoded byte as bits 24-31 (top byte)
		ELSE
			ADD		$dstword, $dstword, $symbol	; add the decoded byte as bits 0-7 (bottom byte)
		ENDIF

5 ; save_4_decoded_bytes
		STR		$dstword, [$bytedest], #4	; $dstword is now full so store into decoded byte array
	
6 ; check_4_byte_decode_process
		SUBS	$nbytes, $nbytes, #4		; decrement the number of words (4 bytes) decoded
		BGE		%BT0 ; get_4_decoded_bytes	; loop while more words to decode else drop through to decode over bytes

7 ; decode_bytes
		ADDS	$nbytes, $nbytes, #4		; add four onto number of bytes to decode
											; 4 bytes will always have been subtracted from $nbytes when this point reached
											; by word operations thus add back 4 to determine actual number of bytes
											; remaining for processing which should be 0 <= $nbytes <= 3 unless function
											; called with $nbytes < 0
		BLE		%FT10 ; end_byte_decoder	; if there are <= 0 bytes to decode, finished so clean up and return
	
8 ; byte_decode
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 8
		STRB	$symbol, [$bytedest], #1	; store the decoded byte into decoded byte array and move to next position

9 ; check_byte_decode
		SUBS	$nbytes, $nbytes, #1		; decrement number of bytes decoded
		BGT		%BT8 ; byte_decode			; loop while more bytes to decode

10 ; end_byte_decoder
	MEND
	
	;---------------------------------------------------------------
	; decode to an array of halfwords
	;
	; decode variable length codewords to halfword symbols
	;
	; $nhwords		register: number of halfwords to decode
	; $hworddest	register: an array to store halfwords decoded
	; $dstword		register: to hold decoded halfwords before saving
	; $lentable		register: decoding length table
	; $symtable		register: decoding symbol table
	; $srcword		register: current word being decoded
	; $word			register: top-up for $srcword
	; $bits			register: number of bits before $word is exhausted
	; $codebits		register: to hold each length of codeword being decoded
	; $symbol		register: to hold each decoded symbol
	; $t			register: temporary
	;
	; $nhwords, $hworddest, $dstword, $lentable, $symtable, $srcword, $word,
	; $bits, $codebits and $symbol must all be distinct
	;
	; $t must be distinct from all registers except $codebits and $symbol
	;
	;---------------------------------------------------------------
	MACRO
	DECODETOHWORDS $nhwords, $hworddest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, $t
		; check registers are distinct
		DISTINCT $nhwords, $hworddest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol
		DISTINCT $t, $nhwords, $hworddest, $dstword, $lentable, $symtable, $srcword, $word, $bits
		
		SUBS	$nhwords, $nhwords, #2		; check that there are at least 2 half words (1 word)...
		BLT		%FT5 ; check_hword_decode_process	; ...if < 2 half words, cannot operate on words so process half word
		
		ANDS	$t, $hworddest, #3			; check that pointer is word-aligned (low 2-bits clear)...
		BEQ		%FT0 ; get_2_decoded_hwords	; ...if word aligned begin processing over words
		
		LDR		$dstword, [$hworddest, #-2]!	; ...else get initial (incomplete) destination word
												; adjusting the pointer to make it word-aligned and leave the
												; pointer in its adjusted state

		IF {ENDIAN} = "little"
			BIC	$dstword, $dstword, #255 << 16	; clear bits 16-31 since data added here by ADDing into bits
			BIC	$dstword, $dstword, #255 << 24
		ELSE
			BIC	$dstword, $dstword, #255		; clear bits 0-15 since data added here by ADDing into bits
			BIC	$dstword, $dstword, #255 << 8
		ENDIF
		
		ADD		$nhwords, $nhwords, #1		; $nhwords = $nhwords + 1
											; word operations decrement number of half words processed by 2 thus add 1
											; to ensure $nhwords is divisible by 2 so that decrement will remove 1 for 
											; odd half word and this extra 1 added here to leave correct number remaining
		B		%FT2 ; get_high_decoded_hword	; branch to have odd half word decoded which is in high 2-bytes of word
		
; for each codeword decode it to a halfword symbol

0 ; get_2_decoded_hwords

1 ; get_low_decoded_hword
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 16
		IF {ENDIAN} = "little"
			ADD		$dstword, $symbol, #0	; add decoded halfword as bits 0-15 (low half word)
		ELSE
			MOV		$dstword, #0			; clear the destination word
			ADD		$dstword, $dstword, $symbol, LSL #16	; add decoded halfword as bits 16-31 (high half word)
		ENDIF
	
2 ; get_high_decoded_hword
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 16
		IF {ENDIAN} = "little"
			ADD		$dstword, $dstword, $symbol, LSL #16	; add the decoded halfword as bits 16-31
		ELSE
			ADD		$dstword, $dstword, $symbol	; add the decoded halfword as bits 0-15
		ENDIF
	
3 ; save_2_decoded_hwords
		STR		$dstword, [$hworddest], #4	; $dstword is now full so store into decoded array
	
4 ; check_2_hword_decode_process
		SUBS	$nhwords, $nhwords, #2		; decrement the number of half words decoded
		BGE		%BT0 ; get_2_decoded_hwords	; loop while more words to decode else drop through to decode last half word

5 ; check_hword_decode_process
		ADDS	$nhwords, $nhwords, #2		; add 2 back to $nhwords since will always have been decremented by 2 when reach here
		BLE		%FT7 ; end_hword_decoder	; if there are <= 0 half words to decode, finished so clean up and return
	
6 ; decode_hword
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 16
		IF ARCHITECTURE_4
			STRH	$symbol, [$hworddest], #2	; store the decoded halfword into array and move to next position
		ELSE
			IF {ENDIAN} = "big"				; store the byte of the halfword in the correct order for endianness
				STRB	$symbol, [$hworddest, #1]	; increment the pointer and store but do not permanently update pointer
			ELSE
				STRB	$symbol, [$hworddest], #1	; store and increment the pointer permanently
			ENDIF
			MOV		$symbol, $symbol, ROR #8	; clear the bottom 8 bits and move the top 8 bits of the halfword into the bottom
			STRB	$symbol, [$hworddest], #1	; store the next byte
		ENDIF

7 ; end_hword_decoder
	MEND
	
	;---------------------------------------------------------------
	; decode to an array of word
	;
	; decode variable length codewords to word symbols
	;
	; $nwords		register: number of words to decode
	; $worddest		register: an array to store words decoded
	; $dstword		register: to hold decoded word before saving
	; $lentable		register: decoding length table
	; $symtable		register: decoding symbol table
	; $srcword		register: current word being decoded
	; $word			register: top-up for $srcword
	; $bits			register: number of bits before $word is exhausted
	; $codebits		register: to hold each length of codeword being decoded
	; $symbol		register: to hold each decoded symbol
	; $t			register: temporary
	;
	; $nwords, $worddest, $dstword, $lentable, $symtable, $srcword, $word,
	; $bits, $codebits and $symbol must all be distinct
	;
	; $t must be distinct from all registers except $codebits and $symbol
	;
	;---------------------------------------------------------------
	MACRO
	DECODETOWORDS $nwords, $worddest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, $t
		; check registers are distinct
		DISTINCT $nwords, $worddest, $dstword, $lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol
		DISTINCT $t, $nwords, $worddest, $dstword, $lentable, $symtable, $srcword, $word, $bits
		
		B		%FT2 ; check_word_decode_process	; branch to check number of words to decode
		
; for each codeword decode it to a word symbol

0 ; get_decoded_word
		DECODECODEWORD	$lentable, $symtable, $srcword, $word, $bits, $codebits, $symbol, 32
	
1 ; save_decoded_word
		STR		$symbol, [$worddest], #4	; store into decoded array
	
2 ; check_word_decode_process
		SUBS	$nwords, $nwords, #1		; decrement the number of words decoded
		BGE		%BT0 ; get_decoded_word		; loop while more words to decode

7 ; end_word_decoder
	MEND
	
	;---------------------------------------------------------------
	; tree or refill
	;
	; determine if a tree traversal is required or a decoding word
	; refill
	;
	; $bits			register: amount by which top-up word is exhausted
	;							or < -32 for a tree traversal
	; $datasize		the size of the data items in the array - 8, 16 or 32 bits
	;
	;---------------------------------------------------------------
	MACRO
	TREEORREFILL $bits, $datasize
		ASSERT ( $datasize = 8 :LOR: $datasize = 16 :LOR: $datasize = 32 )	; check data size
		
		CMP		$bits, #-32					; if the codeword could not be looked up in the table, 255 is returned as its
											; length which is subracted from $bits thus test for this which indicates the 
											; case of walking through the tree
											; $bits has normal range 0 <= $bits <= 32, thus the test for -32 is sufficient 
											; test for tree walk case and allows for the value for tree walking to be changed 
											; to anything from 33 or more
											; $bits is always negative here
		IF $datasize = 8
			BLT		tree_walk_byte			; if $bits < -32, then perform a tree traversal else drop through to refill
											; which MUST follow an instance of this macro
											; it is assumed that the tree walk is only used for codewords that do not occur
											; very frequently and thus the branch to this point is more likely to be for
											; refilling rather than tree walking hence no extra overhead is added to branch
											; again to refill but another branch is required to walk to the tree
		ELSE
			IF $datasize = 16
				BLT	tree_walk_hword
			ELSE
				BLT	tree_walk_word
			ENDIF
		ENDIF
	MEND
	
	;---------------------------------------------------------------
	; refill top-up word
	;
	; use the final bits from the top-up word then refill the top-up word
	;
	; $source		register: pointer to bit stream to read next word for decoding
	; $srcword		register: the current 32 bits being decoded
	; $word			register: the top-up word that needs refilling
	; $codebits		register: the number of bits in $srcword to replace
	; $bits			register: the amount by which the top-up word is short
	;							for refilling $srcword
	; $t			register: temporary
	;
	; $source, $srcword, $word and $bits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	REFILLBUFFER $source, $srcword, $word, $codebits, $bits, $t
		; check registers are distinct
		DISTINCT $srcword, $word, $source, $bits
		
		MOV		$srcword, $srcword, LSL $codebits	; remove the codeword that has been decoded from top of the decoding word shifting
													; all remaining bits to decode into the top bits
											; $codebits may be equal to (255-codeword length) where codeword length <= 27 thus the
											; shift clears
		
		RSB		$bits, $bits, #0			; $bits < 0 thus get $bits = 0 - $bits = -$bits
											; this gives $bits as a positive number of the number of bits that are required
											; from the top-up word that currently don't exist in the word since it has been
											; exhausted
		ORR		$srcword, $srcword, $word, LSL $bits	; add remaining bits from the top-up word to the decoding word from the
														; first free bit down
		LDR		$word, [ $source ], #4		; load the next 32 bits from the coded stream into the top-up word

		IF {ENDIAN} = "little"				; the bit operations are big endian but if the decoding is performed in little endian mode
			BYTEREV $word, $word, $t		; then the bytes of a word need reversing to make them little endian before they can be used
		ENDIF

		RSB 	$bits, $bits, #32			; $bits = 32 - $bits
											; this gives the number of bits free in the top-up word after the remainder of the decoding
											; word has been refilled (which is performed on return)
		MOV		pc, lr						; return to caller
	MEND
	
	;---------------------------------------------------------------
	; finish tree walk
	;
	; tree traversal is completed updating the number of free bits in
	; the top-up word after refilling the decoding word and the top-up
	; word is refilled if necessary
	;
	; $codebits		register: the number of bits that have been decoded
	; $bits			register: the number of bits left in the top-up before exhausted
	; $datasize		the size of the data items being decoded - 8, 16 or 32 bits
	;
	; $codebits and $bits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	FINISHTREEWALK $codebits, $bits, $datasize
		; check registers are distinct
		DISTINCT $bits, $codebits
		
		ADDS	$bits, $bits, $codebits		; update the number of free bits in the top-up word after it has refilled the decoding word
											; the final code word length is set as (255-codeword length) to enable one instruction
											; to restore the bits value to that prior to 255 being subtracted for the tree walk
											; thus adding the codeword length given adds 255 and then subtracts the actual codeword 
											; length
		MOVLT	$codebits, #0				; if $bits < 0 a refill is going to be performed which will include a shift of the decoding
											; word to clear out the codeword data, however this has been performed already thus
											; the shift should have no effect, hence clear the length to shift by
		IF $datasize = 8
			BLT		refill_buffer_byte		; if $bits < 0, top-up word needs refilling and return from the top up...
		ELSE
			IF $datasize = 16
				BLT	refill_buffer_hword
			ELSE
				BLT	refill_buffer_word
			ENDIF
		ENDIF
		RETURN	"","","",""					; ...else return to caller (no rlist, sp, lr, no condition)
	MEND
		
	;---------------------------------------------------------------
	; decoded current tree node
	;
	; get the next bit for decoding, load a tree location for this bit
	; and if a symbol is reached end tree walk
	;
	; $srcword		register: current 32 bits being decoded
	; $symbol		register: to hold the decoded symbol
	; $lenwalk		register: address of decoding length tree
	; $symwalk		register: address of decoding symbol tree
	; $codebits		register: to hold number of bits of codeword decoded
	; $datasize		the size of the data items being decoded - 8, 16 or 32 bits
	;
	; $srcword and $symbol must be distinct
	; $symwalk must be distinct from $symbol
	; $srcword and $codebits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	CHECKTREENODE $srcword, $symbol, $lenwalk, $symwalk, $codebits, $datasize
		; check registers distinct
		DISTINCT $srcword, $symbol
		
		MOVS	$srcword, $srcword, LSL #1	; decode the next bit from the decoding word shifting the bit out into the carry
											; and moving all remaining bits up
		ADC		$symbol, $symbol, $symbol	; $symbol at this point contains the next node pair offset so to actually access
											; the correct node, double the offset given and add in the carry which if set
											; determines that the right hand node from current parent should be taken
											; else take the left hand node

		; load the next length and symbol or node offset from current node
		LOADSYMBOLANDLENGTH $lenwalk, $symwalk, $symbol, $codebits, $symbol, $datasize, 0

		CMP		$codebits, #255				; check if node is internal ($codebits = 255) or leaf node (otherwise)
		IF $datasize = 8
			BNE		finished_walk_byte		; if $codebits <> 255, then found leaf node with decoded data, so complete walk
		ELSE
			IF $datasize = 16
				BNE	finished_walk_hword
			ELSE
				BNE	finished_walk_word
			ENDIF
		ENDIF
	MEND
	
	;---------------------------------------------------------------
	; tree walk
	;
	; traverse the tree decoding a codeword one bit at a time until 
	; a symbol is reached
	;
	; $lenwalk		register: address of decoding length tree
	; $symwalk		register: address of decoding symbol tree
	; $srcword		register: current 32 bits being decoded
	; $symbol		register: to hold the decoded symbol
	; $codebits		register: to hold number of bits of codeword decoded
	; $bits			register: the number of bits left in the top-up word before exhausted
	; $datasize		the size of the data items being decoded - 8, 16 or 32 bits
	;
	; $codebits and $bits must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	TREEWALK $lenwalk, $symwalk, $srcword, $symbol, $codebits, $bits, $datasize
		ASSERT ( $datasize = 8 :LOR: $datasize = 16 :LOR: $datasize = 32 )	; check size of data given
		
		MOV		$srcword, $srcword, LSL #TABLEBITS	; the top TABLEBITS of the decoding word have been used to determine the branch
													; to this point to perform a tree walk, so clear these out moving the remaining
													; bits to the top of the word
		
		; while a symbol (leaf node) has not been reached, traverse the tree one bit a time
		; the decoding word will not need refilling during the traversal since initially it was packed with 32 bits and a codeword
		; can have a maximum length of 27 bits
0 ; tree_walk_check_nodes
		CHECKTREENODE $srcword, $symbol, $lenwalk, $symwalk, $codebits, $datasize
		CHECKTREENODE $srcword, $symbol, $lenwalk, $symwalk, $codebits, $datasize
		CHECKTREENODE $srcword, $symbol, $lenwalk, $symwalk, $codebits, $datasize
		CHECKTREENODE $srcword, $symbol, $lenwalk, $symwalk, $codebits, $datasize
		B %BT0 ; tree_walk_check_nodes		; loop until codeword decoded
	MEND
	
; --------------------
;
; function entry point
;
; --------------------
	
	;---------------------------------------------------------------
	; general bit decoding
	;
	; call the appropriate bit decoding function for given size of data
	;
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to decode and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; n				register: the number of data items to decode
	; dest			register: the destination array to hold byte,
	;							halfword or word symbols
	; lentable		register: decoding length table
	; symtable		stacked: decoding symbol table
	; datatype		stacked 8, 16 or 32 as size of symbol data
	;
	;---------------------------------------------------------------
	IF GENBITDECODE = 1
		; define the general bit decoding function as necessary which requires all other bit decoding functions to be defined
		EXPORT	BitDecodeSymbols

BitDecodeSymbols
		LDR		R12, [ sp, #4 ]				; get "datatype" variable from stack, leaving stack pointer as reference 
											; when called which is for the fifth parameter, symtable

		CMP		R12, #8						; if "datatype" is 8 then the data is bytes
		BEQ		BitDecodeByteSymbols

		CMP		R12, #16					; if "datatype" is 16 then the data is halfwords
		BEQ		BitDecodeHalfWordSymbols
		
		CMP		R12, #32					; if "datatype" is 32 then the data is words
											; this check is made to ensure that no other size can be given
		BEQ		BitDecodeWordSymbols
		
		; if this point is reached the value of "datatype" was incorrect so just return
		MOV		fin_stream, streamstr		; expected return is the state structure so move this into the return register
		RETURN	"","","",""					; return (no rlist, sp, lr, no condition)
	ENDIF

	;---------------------------------------------------------------
	; byte bit decoding
	;
	; bit decode variable length codewords to byte symbols
	;
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to decode and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; n				register: the number of data items to decode
	; dest			register: the destination array to hold byte symbols
	; lentable		register: decoding length table
	; symtable		stacked: decoding symbol table
	;
	;---------------------------------------------------------------
	IF GENBITDECODE = 1 :LOR: BYTEBITDECODE = 1
		; define the byte decoding function as necessary
		EXPORT	BitDecodeByteSymbols

BitDecodeByteSymbols
		; initialise the bit decoder - save registers, setup memory addresses and initialise decoding and stream words
		INITIALISEBITDECODING streamstr, lentable, symtable, lenwalk, symwalk, bits, source, srcword, word, t, 8
		
		; process the coded data calling the bit decoding for each codeword to get bytes
		DECODETOBYTES n, dest, dstword, lentable, symtable, srcword, word, bits, codebits, symbol, t
		
		; end the bit decoder - ensure all data is saved, restore the registers and return
		ENDBITDECODING bits, source, fin_stream, t

tree_or_refill_byte
		; determine if tree should be traversed for decoding or if top-up word needs refilling
		TREEORREFILL bits, 8
	
refill_buffer_byte
		; use the remaining bits in the top-up word then refill it
		REFILLBUFFER source, srcword, word, codebits, bits, t
	
tree_walk_byte
		; traverse the tree until the codeword has been decoded to a symbol
		TREEWALK lenwalk, symwalk, srcword, symbol, codebits, bits, 8
	
finished_walk_byte
		; end the tree traversal refilling the top-up word as necessary
		FINISHTREEWALK codebits, bits, 8
	ENDIF

	;---------------------------------------------------------------
	; halfword bit decoding
	;
	; bit decode variable length codewords to halfword symbols
	;
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to decode and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; n				register: the number of data items to decode
	; dest			register: the destination array to hold halfword symbols
	; lentable		register: decoding length table
	; symtable		stacked: decoding symbol table
	;
	;---------------------------------------------------------------
	IF GENBITDECODE = 1 :LOR: HWORDBITDECODE = 1
		; define the halfword decoding function as necessary
		EXPORT	BitDecodeHalfWordSymbols

BitDecodeHalfWordSymbols
		; initialise the bit decoder - save registers, setup memory addresses and initialise decoding and stream words
		INITIALISEBITDECODING streamstr, lentable, symtable, lenwalk, symwalk, bits, source, srcword, word, t, 16

		; process the coded data calling the bit decoding for each codeword to get halfwords
		DECODETOHWORDS n, dest, dstword, lentable, symtable, srcword, word, bits, codebits, symbol, t	
		
		; end the bit decoder - ensure all data is saved, restore the registers and return
		ENDBITDECODING bits, source, fin_stream, t

tree_or_refill_hword
		; determine if tree should be traversed for decoding or if top-up word needs refilling
		TREEORREFILL bits, 16
	
refill_buffer_hword
		; use the remaining bits in the top-up word then refill it
		REFILLBUFFER source, srcword, word, codebits, bits, t
	
tree_walk_hword
		; traverse the tree until the codeword has been decoded to a symbol
		TREEWALK	lenwalk, symwalk, srcword, symbol, codebits, bits, 16
	
finished_walk_hword
		; end the tree traversal refilling the top-up word as necessary
		FINISHTREEWALK codebits, bits, 16
	ENDIF

	;---------------------------------------------------------------
	; word bit decoding
	;
	; bit decode variable length codewords to word symbols
	;
	; streamstr		register: pointer to a structure that must contain
	;				an unsigned character array as first entry that is
	; 				the bitstream to decode and an
	;				unsigned integer as second entry that is the
	;				bit position in this array to start from
	; n				register: the number of data items to decode
	; dest			register: the destination array to hold word symbols
	; lentable		register: decoding length table
	; symtable		stacked: decoding symbol table
	;
	;---------------------------------------------------------------
	IF GENBITDECODE = 1 :LOR: WORDBITDECODE = 1
		; define the word decoding function as necessary
		EXPORT	BitDecodeWordSymbols

BitDecodeWordSymbols
		; initialise the bit decoder - save registers, setup memory addresses and initialise decoding and stream words
		INITIALISEBITDECODING streamstr, lentable, symtable, lenwalk, symwalk, bits, source, srcword, word, t, 32
		
		; process the coded data calling the bit decoding for each codeword to get words
		DECODETOWORDS n, dest, dstword, lentable, symtable, srcword, word, bits, codebits, symbol, t
		
		; end the bit decoder - ensure all data is saved, restore the registers and return
		ENDBITDECODING bits, source, fin_stream, t

tree_or_refill_word
		; determine if tree should be traversed for decoding or if top-up word needs refilling
		TREEORREFILL bits, 32
	
refill_buffer_word
		; use the remaining bits in the top-up word then refill it
		REFILLBUFFER source, srcword, word, codebits, bits, t
	
tree_walk_word
		; traverse the tree until the codeword has been decoded to a symbol
		TREEWALK	lenwalk, symwalk, srcword, symbol, codebits, bits, 32
	
finished_walk_word
		; end the tree traversal refilling the top-up word as necessary
		FINISHTREEWALK codebits, bits, 32
	ENDIF


	
	END
