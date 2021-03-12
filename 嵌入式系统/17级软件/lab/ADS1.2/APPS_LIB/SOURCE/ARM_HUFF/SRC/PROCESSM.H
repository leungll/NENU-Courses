;/*
; * Process data assembler macro
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	; load and store of halfword operations is required which has specific instructions defined in architecture 4 or later
	; if architecture 4 or later is not available other instructions must be used to simulate the halfword instructions
	;
	; define, therefore, a flag which sets the instructions as appropriate for the architecture supported
	GBLL	ARCHITECTURE_4
	
ARCHITECTURE_4 SETL	:LNOT:( {ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M" )
	
	;---------------------------------------------------------------
	; process an array of bytes
	;
	; reads in each byte from a given array and for each, calls
	; the macro $process
	;
	; $nbytes		register: number of bytes in the array to process
	; $bytesrc		register: array of bytes to process
	; $srcword		register: to hold current four bytes
	; $byte			register: to hold current byte
	; $t			register: temporary
	; $process		a macro name together with all its parameters
	;				which is called for each byte to process
	;
	;				the macro should take $byte as a parameter
	;
	;				an extra parameter is supplied to the macro
	;				which specifies the bit position in $byte
	;				that contains the byte to be processed
	;
	; all registers must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	PROCESSBYTES $nbytes, $bytesrc, $srcword, $byte, $t, $process
	    ASSERT ( "$process" <> "" )			; ensure that $process is non-empty
	    
	    ; check that registers are distinct
	    ASSERT ( $nbytes <> $bytesrc ):LAND:( $nbytes <> $srcword )
	    ASSERT ( $nbytes <> $byte ):LAND:( $nbytes <> $t )
	    ASSERT ( $bytesrc <> $srcword ):LAND:( $bytesrc <> $byte )
	    ASSERT ( $bytesrc <> $t )
	    ASSERT ( $srcword <> $byte ):LAND:( $srcword <> $t )
	    ASSERT ( $byte <> $t )
	    
		SUBS	$nbytes, $nbytes, #4		; check that there are at least 4 bytes (1 word)...
		BLT		%FT6 ; process_bytes		; ...if <4 bytes, cannot operate on words so process as bytes
		
		ANDS	$t, $bytesrc, #3			; check that pointer is word-aligned (low 2-bits clear)...
		BEQ		%FT0 ; process_4_bytes		; ...if word aligned begin processing over words
		
		BIC		$bytesrc, $bytesrc, #3		; ...if not, word-align pointer (clear low 2-bits) for word operations
											; this moves address back in memory to before data but word-aligned
		LDR		$srcword, [$bytesrc], #4	; load a word with extra bytes before word-aligned boundary
											; stored in word such that in correct order and position for operations

		ADD		$nbytes, $nbytes, $t		; 4 has already been subtracted for word operations
											; however as pointer is not word aligned, some of the first
											; word's data has already been coded and thus can be ignored so
											; add on number of bytes that have  previously been coded as given by
											; byte offset for pointer
		CMP		$t, #2						; comparison used for branch to operate on bytes obtained
		BLT		%FT2 ; process_byte_1_from_word		; $t = 1 byte has been processed, jump to start of processing 3 bytes remaining
		BEQ		%FT3 ; process_byte_2_from_word		; $t = 2 bytes have been processed, jump to start of processing 2 bytes remaining
		BGT		%FT4 ; process_byte_3_from_word		; $t = 3 bytes have been processed, jump to start of processing 1 byte remaining
	
; for each byte process the byte by calling the specific macro passed

0 ; process_4_bytes
		LDR	$srcword, [$bytesrc], #4		; read four bytes, packed into a word

1 ; process_byte_0_from_word
		IF {ENDIAN} = "little"
			AND		$byte, $srcword, #255	; get the byte stored in bits 0-7
			$process, 0
		ELSE
			AND		$byte, $srcword, #255 << 24	; get the byte stored in bits 24-31
			$process, 24
		ENDIF
	
2 ; process_byte_1_from_word
		IF {ENDIAN} = "little"
			AND		$byte, $srcword, #255 << 8	; get the byte stored in bits 8-15
			$process, 8
		ELSE
			AND		$byte, $srcword, #255 << 16	; get the byte stored in bits 16-23
			$process, 16
		ENDIF
	
3 ; process_byte_2_from_word
		IF {ENDIAN} = "little"
			AND		$byte, $srcword, #255 << 16	; get the byte stored in bits 16-23
			$process, 16
		ELSE
			AND		$byte, $srcword, #255 << 8	; get the byte stored in bits 8-15
			$process, 8
		ENDIF
	
4 ; process_byte_3_from_word
		IF {ENDIAN} = "little"
			AND		$byte, $srcword, #255 << 24	; get the byte stored in bits 24-31
			$process, 24
		ELSE
			AND		$byte, $srcword, #255	; get the byte stored in bits 0-7
			$process, 0
		ENDIF

5 ; check_4_bytes_process
		SUBS	$nbytes, $nbytes, #4		; decrement the number of words (4 bytes) processed
		BGE		%BT0 ; process_4_bytes		; loop while more words to process else drop through to process bytes
	
6 ; process_bytes
		ADDS	$nbytes, $nbytes, #4		; add four onto number of bytes to process
											; 4 bytes will always have been subtracted from $nbytes when this point reached
											; by word operations thus add back 4 to determine actual number of bytes
											; remaining for processing which should be 0 <= $nbytes <= 3 unless function
											; called with $nbytes < 0
		BLE		%FT9 ; end_byte_process		; if there are <= 0 bytes to process, finished so clean up and return
	
7 ; process_1_byte
		LDRB	$byte, [$bytesrc], #1		; read one byte in
		$process, 0

8 ; check_byte_process
		SUBS	$nbytes, $nbytes, #1		; decrement number of bytes processed
		BGT		%BT7 ; process_1_byte		; loop while more bytes to process

9 ; end_byte_process
	MEND
	
	;---------------------------------------------------------------
	; process an array of halfwords
	;
	; reads in each halfword from a given array and for each, calls
	; the macro $process
	;
	; $nhwords		register: number of halfwords in the array to process
	; $hwordsrc		register: array of halfwords to process
	; $srcword		register: to hold current two halfwords
	; $hword		register: to hold current halfword
	; $process		a macro name together with all its parameters
	;				which is called for each halfword to process
	;
	;				the macro should take $hword as a parameter
	;
	;				an extra parameter is supplied to the macro
	;				which specifies the bit position in $hword
	;				that contains the halfword to be processed
	;
	; all registers must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	PROCESSHWORDS $nhwords, $hwordsrc, $srcword, $hword, $process
	    ASSERT ( "$process" <> "" )			; ensure that $process is non-empty
	    
	    ; check that registers are distinct
	    ASSERT ( $nhwords <> $hwordsrc ):LAND:( $nhwords <> $srcword )
	    ASSERT ( $nhwords <> $hword )
	    ASSERT ( $hwordsrc <> $srcword ):LAND:( $hwordsrc <> $hword )
	    ASSERT ( $srcword <> $hword )

		SUBS	$nhwords, $nhwords, #2		; check that there are at least 2 half words (1 word)...
		BLT		%FT4 ; check_hword_process	; ...if < 2 half words, cannot operate on words so process half word
		
		ANDS	$hword, $hwordsrc, #3		; check that pointer is word-aligned (low 2-bits clear)...
		BEQ		%FT0 ; process_2_hwords		; ...if word aligned begin processing over words
		
		BIC		$hwordsrc, $hwordsrc, #3	; ...if not, word-align pointer (clear low 2-bits) for word operations
											; this moves address back in memory to before data but word-aligned
											; bit 0 should actually be clear previously since working on half words
		LDR		$srcword, [$hwordsrc], #4	; load a word with extra half word before word-aligned boundary
											; stored in word such that in correct order and position for operations

		ADD		$nhwords, $nhwords, #1		; $nhwords = $nhwords + 1
											; word operations decrement number of half words processed by 2 thus add 1
											; to ensure $nhwords is divisible by 2 so that decrement will remove 1 for 
											; odd half word and this extra 1 added here to leave correct number remaining
		B		%FT2 ; high_hword_from_word	; branch to have odd half word processed which is in high 2-bytes of word

; for each halfword process the halfword by calling the specific macro passed

0 ; process_2_hwords
		LDR		$srcword, [$hwordsrc], #4	; read 2 halfwords, packed into a word
	
1 ; low_hword_from_word
		IF {ENDIAN} = "little"
			MOV		$hword, $srcword, LSL #16	; get the low 2 bytes, placing into high 2 bytes to clear them
		ELSE
			MOV		$hword, $srcword		; next halfword is already in high 2 bytes
		ENDIF
		$process, 16						; ensure retrieves value from high 2 bytes
	
2 ; high_hword_from_word
		IF {ENDIAN} = "big"
			MOV		$hword, $srcword, LSL #16	; get the low 2 bytes, placing into high 2 bytes to clear them
		ELSE
			MOV		$hword, $srcword		; next halfword is already in high 2 bytes
		ENDIF
		$process, 16						; ensure retrives value from high 2 bytes
	
3 ; check_2_hwords_process
		SUBS	$nhwords, $nhwords, #2		; decrement the number of half words processed
		BGE		%BT0 ; process_2_hwords		; loop while more words to process else drop through to process half word
	
4 ; check_hword_process
		ADDS	$nhwords, $nhwords, #2		; add 2 back to $nhwords since will always have been decremented by 2 when reach here
		BLE		%FT6 ; end_hword_process	; if <= 0 halfwords, finished so clean up and return
	
5 ; process_hword
		IF ARCHITECTURE_4
			LDRH	$hword, [$hwordsrc], #2	; read halfword
			$process, 0						; halfword is in the low 2 bytes
		ELSE
			LDR		$hword, [$hwordsrc], #2
			IF {ENDIAN} = "little"			; if big, halfword is in top 2 bytes
				MOV	$hword, $hword, LSL #16	; place halfword into top halfword to clear top 2 bytes
			ENDIF
			$process, 16					; ensure retrieves halfword from top halfword
		ENDIF			

6 ; end_hword_process
	MEND
	
	;---------------------------------------------------------------
	; process an array of words
	;
	; reads in each word from a given array and for each, calls
	; the macro $process
	;
	; $nwords		register: number of words in the array to process
	; $wordsrc		register: array of word to process
	; $srcword		register: to hold current word
	; $process		a macro name together with all its parameters
	;				which is called for each word to process
	;
	;				the macro should take $srcword as a parameter
	;
	;				an extra parameter is supplied to the macro
	;				which specifies the bit position in $srcword
	;				that contains the word to be processed - this
	;				is always zero and can be ignored
	;
	; all registers must be distinct
	;
	;---------------------------------------------------------------
	MACRO
	PROCESSWORDS $nwords, $wordsrc, $srcword, $process
	    ASSERT ( "$process" <> "" )			; ensure that $process is non-empty
	    
	    ; check that registers are distinct
	    ASSERT ( $nwords <> $wordsrc ):LAND:( $nwords <> $srcword )
	    ASSERT ( $wordsrc <> $srcword )
	    
		B		%FT1 ; check_word_process

0 ; process_word
		LDR		$srcword, [$wordsrc], #4	; read next word for processing
		$process, 0

1 ; check_word_process
		SUBS	$nwords, $nwords, #1		; decrement the number of words processed
		BGE		%BT0 ; process_word			; loop while more words to process else finished
	
2 ; end_word_process
	MEND
	
	END
