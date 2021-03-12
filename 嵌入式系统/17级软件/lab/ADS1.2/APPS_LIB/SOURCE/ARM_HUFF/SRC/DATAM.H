;/*
; * Data assembler macros
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

	; load and store of halfword operations is required which has specific instructions defined in architecture 4 or later
	; if architecture 4 or later is not available other instructions must be used to simulate the halfword instructions
	;
	; define, therefore, a flag which sets the instructions as appropriate for the architecture supported
	GBLL	ARCHITECTURE_4
	
ARCHITECTURE_4 SETL	:LNOT:({ARCHITECTURE} = "3" :LOR: {ARCHITECTURE} = "3M")
	
	;---------------------------------------------------------------
	; byte reversal within a word
	;
	; reverses a and places the answer in c supposing a=(a,b,c,d)
	; in bytes (a=msb) then c=(d,c,b,a)
	;
	; $a		register: input word
	; $c		register: output result of byte reversal
	; $t		register: temporary
	;
	; both registers $a and $c must be distinct from register $t
	;
	;---------------------------------------------------------------
	MACRO
	BYTEREV	$c, $a, $t
		ASSERT ( $t <> $a ):LAND:( $t <> $c )
		
		EOR $t, $a, $a, ROR#16				; (a^c)(b^d)(a^c)(b^d) 
		BIC $t, $t, #0xFF0000				; (a^c) 0 (a^c)(b^d) 
		MOV $c, $a, ROR #8					; d a b c 
		EOR $c, $c, $t, LSR#8				; d c b a
	MEND
	
	;---------------------------------------------------------------
	; load an entry from an array or store an entry to an array
	;
	; $dataaddress		register: memory address of array of bytes, 
	;								halfwords or words
	; $dataindex		register: index into the array
	; $dataword			register: to read data into or write data from
	; $tindex			register: temporary
	; $datasize			the size of the data items in the array - 8, 16 or 32 bits
	; $dindexposinword	the position of the array index in $dataindex between 0 and 32
	; $loadstore		LDR or STR
	;
	; register $dataaddress must be distinct from register $tindex
	; register $dataword must be distinct from register $tindex if $loadstore = STR
	;
	; this macro should not be used directly - use LOADDATA and STOREDATA
	;
	;---------------------------------------------------------------
	MACRO
	INTERNALLOADSTORE $dataaddress, $dataindex, $dataword, $tindex, $datasize, $dindexposinword, $loadstore
		ASSERT ( $datasize = 8 :LOR: $datasize = 16 :LOR: $datasize = 32 )
		ASSERT ( $dindexposinword >= 0 :LAND: $dindexposinword <= 32 )
		
		; check that registers are distinct
		IF "$loadstore" = "STR"
			ASSERT ( $tindex <> $dataword )
		ENDIF
		ASSERT ( $tindex <> $dataaddress )
		
		IF $datasize = 8
			IF $dindexposinword = 0
				$loadstore.B	$dataword, [ $dataaddress, $dataindex ]
			ELSE
				$loadstore.B	$dataword, [ $dataaddress, $dataindex, LSR #$dindexposinword ]
			ENDIF
		ELSE
			IF $dindexposinword <> 0
				MOV		$tindex, $dataindex, LSR #$dindexposinword
			ENDIF
			IF $datasize = 16 
				IF ARCHITECTURE_4
					IF $dindexposinword = 0
						MOV		$tindex, $dataindex, LSL #1
					ELSE
						MOV		$tindex, $tindex, LSL #1
					ENDIF
					$loadstore.H	$dataword, [ $dataaddress, $tindex ]
				ELSE
					IF $dindexposinword = 0
						$loadstore		$dataword, [ $dataaddress, $dataindex, LSL #1 ]
					ELSE
						$loadstore		$dataword, [ $dataaddress, $tindex, LSL #1 ]
					ENDIF
					IF {ENDIAN} = "little"
						MOV		$dataword, $dataword, LSL #16
					ENDIF
					MOV		$dataword, $dataword, LSR #16
				ENDIF
			ELSE
				IF $dindexposinword = 0
					$loadstore		$dataword, [ $dataaddress, $dataindex, LSL #2 ]
				ELSE
					$loadstore		$dataword, [ $dataaddress, $tindex, LSL #2 ]
				ENDIF
			ENDIF
		ENDIF
	MEND
	
	;---------------------------------------------------------------
	; load an entry from an array
	;
	; $dataaddress		register: memory address of array of bytes, 
	;								halfwords or words
	; $dataindex		register: index into the array
	; $dataword			register: to read data into
	; $tindex			register: temporary
	; $datasize			the size of the data items in the array - 8, 16 or 32 bits
	; $dindexposinword	the position of the array index in $dataindex between 0 and 32
	;
	; register $dataaddress must be distinct from register $tindex
	;
	;---------------------------------------------------------------
	MACRO
	LOADDATA $dataaddress, $dataindex, $dataword, $tindex, $datasize, $dindexposinword
		INTERNALLOADSTORE $dataaddress, $dataindex, $dataword, $tindex, $datasize, $dindexposinword, "LDR"
	MEND
	
	;---------------------------------------------------------------
	; store an entry to an array
	;
	; $dataaddress		register: memory address of array of bytes, 
	;								halfwords or words
	; $dataindex		register: index into the array
	; $dataword			register: to write data from
	; $tindex			register: temporary
	; $datasize			the size of the data items in the array - 8, 16 or 32 bits
	; $dindexposinword	the position of the array index in $dataindex between 0 and 32
	;
	; both registers $dataword and $dataaddress must be distinct from register $tindex
	;
	;---------------------------------------------------------------
	MACRO
	STOREDATA $dataaddress, $dataindex, $dataword, $tindex, $datasize, $dindexposinword
		INTERNALLOADSTORE $dataaddress, $dataindex, $dataword, $tindex, $datasize, $dindexposinword, "STR"
	MEND


	END
