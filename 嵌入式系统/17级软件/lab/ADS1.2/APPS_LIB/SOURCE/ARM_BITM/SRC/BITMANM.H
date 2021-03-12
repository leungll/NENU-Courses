;/*
; * Bit Manipulation assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;---------------------------------------------------------------
; Generally Useful Code Fragments
;
;---------------------------------------------------------------
; Each code fragment is implemented in the form of a MACRO so
; that it can be inlined.
;
; Contents:
;
;	binary coded decimal (BCD) addition
;		BCDADD
;   bit reversal in a word
;       BITREV, BITREVC
;	byte reversal in a word
;		BYTEREV, BYTEREVC
;	bytewise maximum
;		BYTEWISEMAX
;   least and most significant bit set
;		LSBSET, MSBSET
;	population count (1's in binary representation of integer)
;		POPCOUNT, POPCOUNT7 (over seven words)
;
;---------------------------------------------------------------

	INCLUDE	regchekm.h

;---------------------------------------------------------------
; Binary Coded Decimal (BCD) Addition
; 7 cycles 
;
;---------------------------------------------------------------
; $a			binary coded decimal input a
; $b			binary coded decimal input b
; $c			output result of binary coded decimal addition
; $t			temporary register
;
; constant1 = 0x33333333
; constant2 = 0x88888888
;
; the code returns in c the binary coded decimal addition of
; a + b (or a + b + carry if code adjusted accordingly)
; where a and b are valid BCD numbers - i.e. every nibble
; lies in the range 0-9 (else the result will be meaningless)
;
; Registers $constant1 and $constant2 must be distinct from each other.
; Register $t must be a distinct register from each of $a, $b, $c
; and $constant2.
; Register $c must be a distinct register from both $a and $b.
; Registers $a and $b need not be distinct from each other.
; Register $constant1 need not be distinct from $a, $b, $c or $t
; Register $constant2 need not be distinct from $a, $b or $c
;
;---------------------------------------------------------------

	MACRO
	BCDADD	$c, $a, $b, $t, $constant1, $constant2, $withcarry
		DISTINCT $constant1, $constant2
		DISTINCT $a, $c, $t
		DISTINCT $b, $c, $t
		DISTINCT $constant2, $t
		
		;Suppose we add a, b and 0x66666666. Look at the least significant nibble
		;("LSN") of this sum. This will generate a carry into the next nibble if:
		;
		;LSN(a) + LSN(b) + 6 >= 16,
		;
		;i.e. if:
		;
		;LSN(a) + LSN(b) >= 10.
		;
		;Which is precisely the condition we want for whether the LSN of the BCD
		;sum generates a carry into the next nibble.
		;
		;Looking at the next nibble, we then find that it generates a carry into
		;the third nibble if:
		;
		;NextNybble(a) + NextNybble(b) + (Carry from LSN) + 6 >= 16,
		;
		;i.e. if:
		;
		;NextNybble(a) + NextNybble(b) + (Carry from LSN) >= 10,
		;
		;which is precisely when we want this nibble to generate a carry into the
		;third nibble in the BCD sum. This clearly continues all the way through,
		;so the carries between nibbles in the a+b+0x66666666 addition are
		;precisely those we want between the BCD digits.
		
		ADDS    $c,$a,$b             ;start BCD equivalent of ADD $c, $a, $b
									 ;but corrupts the flags else...
	    ;ADCS	$c, $a, $b			 ;...use this line instead to perform the BCD
	    							 ;equivalent of ADC $c, $a, $b which adds
	    							 ;the carry flag as well
	    
	    ADD     $t,$constant1,$c,RRX ;Generate sum with BCD carries
	    EOR     $t,$t,$a,LSR #1      ; )
	    EOR     $t,$t,$b,LSR #1      ; ) Isolate those carries
	    AND     $t,$t,$constant2     ; )
	    ADD     $c,$c,$t,LSR #1      ;Adjust sum according to the BCD
	    ADD     $c,$c,$t,LSR #2      ; carries
	    
		;After the first instruction, c contains the 33 bit unsigned sum of a
		;and b. So the RRX shift in the second instruction ends up generating the
		;true unsigned version of (a+b) >> 1, and the addition of 0x33333333 then
		;gives us (a+b+0x66666666) >> 1. So to get the carries out of each of the
		;nibbles of the BCD sum, we want the carries into bits 3, 7, 11, 15, 19,
		;23, 27 and 31 of the result of the second instruction. (Note that although
		;three operands have been added together, there can only be a single carry
		;out of any nibble, because the operand nibbles are all 0-9 and the third
		;nibble is effectively 6.)
		;
		;To get the carry into a bit of a sum which is known to have only had a
		;single carry into it, you can use the fact that:
		;
		;(sum bit) = (EOR of all the operand bits) EOR (carry in bit),
		;
		;or equivalently:
		;
		;(carry in bit) = (EOR of all the operand bits) EOR (sum bit)
		;
		;Since the relevant bits of the constant 0x33333333 are all zero, we can
		;EOR with a >> 1 and b >> 1 to get a value in which bits 3, 7, 11, 15,
		;19, 23, 27 and 31 are the desired BCD carries out of each nibble. Then
		;ANDing with 0x88888888 will isolate those carries.
		
		;Now all we have to do is add 6 to each nibble of the original sum of a
		;and b which should have produced a BCD carry out, to force its value to
		;the correct BCD digit and to force it to produce a carry into the next
		;nibble if it hasn't already.
		;
		;Note that the carry out from the top nibble of the BCD addition is
	    ;in bit 31 of $t so the code might be adjusted to move this into the
	    ;carry flag which would allow the synthesis of multi-precision BCD
	    ;additions

	MEND
	
;---------------------------------------------------------------
; Reverse the required bit-size units
; 3 cycles + 1 register constant
;
;---------------------------------------------------------------
; $a		input word
; $c		output result of unit reversal
; $t		temporary register
; $constant	temporary register containing one of the following
;           according to the unit bit size
;			0x0000FFFF	reverse units of 16-bits (2 bytes)
; 			0x00FF00FF	reverse units of 8-bits (1 byte)
; 			0x0F0F0F0F	reverse units of 4-bits (1 nibble)
; 			0x33333333	reverse units of 2-bits
; 			0x55555555	reverse units of 1-bit
; $bits		one of 16, 8, 4, 2 or 1 according to unit bit size
;           another other value (including 32) returns $a in $c
;
; Register $t must be distinct from registers $a, $c and $constant
; Registers $constant, $a and $c need not be distinct from each other
;
;---------------------------------------------------------------
	MACRO
	REVERSEUNITS $c, $a, $t, $constant, $bits
		DISTINCT $t, $constant
		DISTINCT $t, $a
		DISTINCT $t, $c
		
		IF $bits = 16 :LOR: $bits = 8 :LOR: $bits = 4 :LOR: $bits = 2 :LOR: $bits = 1
			AND	$t, $constant, $a, LSR #$bits
			AND	$c, $a, $constant
			ORR	$c, $t, $c, LSL #$bits			; reversed units of $bits bits
		ELSE
			MOV $c, $a
		ENDIF
	MEND

;---------------------------------------------------------------
; Bit reversal within a word
; 17 cycles or 12 cycles/value + 5 setup cycles 
;
;---------------------------------------------------------------
; $a		input word
; $c		output result of bit reversal
; $t		temporary register
; $constant	temporary register to hold constants (BITREV only)
;
; constant1 = 0xFFFF00FF (BITREVC only)
; constant2 = 0x0F0F0F0F (BITREVC only)
; constant3 = 0x33333333 (BITREVC only)
; constant4 = 0x55555555 (BITREVC only)
;
; reverses a and places the answer in c supposing each bit x of a
; is reversed to be in bit 31-x (bits 0 to 31)
;
; first method takes 12 cycles but needs 4 register constants set 
; prior to the macro call and thus five temporary registers
;
; the second method takes 17 cycles but does not need a register 
; set up, and so only requires two temporary registers
;
;---------------------------------------------------------------

;---------------------------------------------------------------
; Bit reversal within a word - method 1
; 17 cycles 
;
; $a		input word
; $c		output result of byte reversal
; $t		temporary register
; $constant	temporary register (to hold constants during reversal)
;
; Registers $t and $constant must be distinct from each other
; Registers $t and $constant must be distinct from both $a and $c
; Registers $a and $c need not be distinct from each other
;
;---------------------------------------------------------------

	MACRO
	BITREV	$c, $a, $t, $constant
		DISTINCT $constant, $a
		DISTINCT $constant, $c

		MVN 		$constant, #0xFF00							; constant = 0xFFFF00FF
		
		; use BYTEREVC since require constant for future constant construction
		BYTEREVC 	$c, $a, $t, $constant						; endianness swap
			
		BIC			$constant, $constant, #0xFF000000
		EOR			$constant, $constant, $constant, LSL #4		; $constant = 0x0F0F0F0F
	
		REVERSEUNITS $c, $c, $t, $constant, 4
	
		EOR			$constant, $constant, $constant, LSL #2		; $constant = 0x33333333
	
		REVERSEUNITS $c, $c, $t, $constant, 2
	
		EOR			$constant, $constant, $constant, LSL #1		; $constant = 0x55555555
	
		REVERSEUNITS $c, $c, $t, $constant, 1
	MEND
	
;---------------------------------------------------------------
; Bit reversal within a word - method 2
; 12 cycles/value + 4 register constants
;
; $a		input word
; $c		output result of bit reversal
; $t		temporary register
;
; constant1 = 0xFFFF00FF
; constant2 = 0x0F0F0F0F
; constant3 = 0x33333333
; constant4 = 0x55555555
;
; Register $t must be distinct from registers $a, $c, $constant1,
; $constant2, $constant3 and $constant4
; Register $c must be distinct from registers $constant2, $constant3 
; and $constant4
; Register $c need not be distinct from register $constant1 or $a
; Register $a need not be distinct from any of registers $constant1,
; $constant2, $constant3 or $constant4
;
;---------------------------------------------------------------

	MACRO 
	BITREVC	$c, $a, $t, $constant1, $constant2, $constant3, $constant4
		DISTINCT $constant1, $constant2, $constant3, $constant4
		DISTINCT $c, $constant2, $constant3, $constant4

		BYTEREVC $c, $a, $t, $constant1			; endianness swap
		
		REVERSEUNITS $c, $c, $t, $constant2, 4
	
		REVERSEUNITS $c, $c, $t, $constant3, 2
	
		REVERSEUNITS $c, $c, $t, $constant4, 1
	MEND

;---------------------------------------------------------------
; Byte reversal within a word
; 4 cycles or 3 cycles/value + 1 setup cycle 
;
;---------------------------------------------------------------
; $a		input word
; $c		output result of byte reversal
; $t		temporary register
;
; $constant = 0xFFFF00FF (BYTEREVC only)
;
; reverses a and places the answer in c supposing a=(a,b,c,d)
; in bytes (a=msb)
;
; first method takes 3 cycles but needs a register constant set 
; prior to the macro call and thus two temporary registers
;
; the second method takes 4 cycles but does not need a register 
; set up, and so only requires one temporary register
;
;---------------------------------------------------------------

;---------------------------------------------------------------
; Byte reversal within a word - method 1
; 4 cycles 
;
; $a		input word
; $c		output result of byte reversal
; $t		temporary register
;
; Both registers $a and $c must be distinct from register $t
; Register $c need not be distinct from $a.
;
;---------------------------------------------------------------

	MACRO
	BYTEREV	$c, $a, $t
		DISTINCT $t, $a
		DISTINCT $t, $c
		
		EOR $t, $a, $a, ROR#16				; (a^c)(b^d)(a^c)(b^d) 
		BIC $t, $t, #0xFF0000				; (a^c) 0 (a^c)(b^d) 
		MOV $c, $a, ROR #8					; d a b c 
		EOR $c, $c, $t, LSR#8				; d c b a
	MEND
	
;---------------------------------------------------------------
; Byte reversal within a word - method 2
; 3 cycles/value + 1 register constant 
;
; $a		input word
; $c		output result of byte reversal
; $t		temporary register
;
; $constant = 0xFFFF00FF
;
; Both registers $a and $constant must be distinct from register $t
; Registers $a, $c and $constant need not be distinct from each other
; Registers $c and $t need not be distinct from each other
;
;---------------------------------------------------------------
 
 	MACRO
	BYTEREVC	$c, $a, $t, $constant
		DISTINCT $t, $a
		DISTINCT $t, $constant
		
		EOR $t, $a, $a, ROR #16				; (a^c)(b^d)(a^c)(b^d) 
		AND $t, $constant, $t, LSR#8		; 0 (a^c) 0 (a^c) 
		EOR $c, $t, $a, ROR #8 				; d c b a
	MEND
		
;---------------------------------------------------------------
; Bytewise maximum
; 8 cycles 
;
;---------------------------------------------------------------
; $a			input a
; $b			input b
; $c			each byte of output result 
;				= MAX( corresponding bytes of a and b) 
; $d			each byte of output result
;				= 0 or 1 if corresponding byte of a or b chosen (respectively)
; $t			temporary register
;
; constant = 0x01010101
;
; the code returns in each byte of c the maximum value of the corresponding
; byte from a or b and returns in each byte of d a 0 (zero) if the corresponding
; byte in c was chosen from a or a 1 (one) if the corresponding byte in c
; was chosen from b
;
; if the bytes of a and b are identical it is assumed it is unimportant which
; is selected and thus the corresponding byte of d may contain either a 0 or a 1
;
; all bytes are treated as unsigned 
;
; Registers $a, $c, $d and $t must be distinct registers from each other
; Register $c must be distinct from $b
; Registers $c and $d must be distinct from $constant
; Either register $d or $t need not be distinct from register $b
; Register $t need not be distinct from register $constant
; Registers $a, $b and $constant need not be distinct from each other
;
;---------------------------------------------------------------

	MACRO
	BYTEWISEMAX	$c, $d, $a, $b, $t, $constant
		DISTINCT $a, $c, $d, $t
		DISTINCT $b, $c
		DISTINCT $c, $d, $constant
		
	    EOR     $c,$a,$b                  ;EOR of operands used twice below
	    SUBS    $d,$a,$b                  ;Do a 32-bit subtraction
	    EOR     $d,$d,$c                  ;EOR with operands to generate
	                                      ; borrows into each bit
	    AND     $d,$constant,$d,LSR #8    ;Isolate borrows into bits 8, 16, 24
	                                      ; and shift into bits 0, 8, 16
	    ORRCC   $d,$d,#0x01000000         ;Now bits 0, 8, 16, 24 are borrows out
	                                      ; of the four bytes
	    RSB     $t,$d,$d,LSL #8           ;Multiply these by 255 to get bytes of
	                                      ; 0x00 or 0xFF according to whether
	                                      ; byte generated a borrow in a-b
	    AND     $c,$c,$t                  ;Generate (a byte) EOR 0 = (a byte)
	    EOR     $c,$c,$a                  ; for non-borrowing bytes, (a byte)
	                                      ; EOR ((a byte) EOR (b byte)) =
	                                      ; (b byte) for borrowing bytes.

		;This uses the same sort of ideas as the BCDADD code. To start with,
		;suppose we do the 32-bit subtraction a-b. Then for each byte, we know:
		;
		;  If (a byte) > (b byte), no "borrow" will be generated from the next byte
		;  up during this subtraction.
		;
		;  If (a byte) < (b byte), a "borrow" will definitely be generated from the
		;  next byte up during this subtraction.
		;
		;  If (a byte) = (b byte), a "borrow" may or may not be generated from the
		;  next byte during this subtraction: whether it is depends on whether this
		;  byte receives a "borrow" from the next byte down.
		;
		;So a suitable value for d has:
		;
		;  Bit 0 = "borrow" from bit 8 generated by bit 7 during the subtraction;
		;  Bit 8 = "borrow" from bit 16 generated by bit 15 during the subtraction;
		;  Bit 16 = "borrow" from bit 24 generated by bit 23 during the subtraction;
		;  Bit 24 = "borrow" from outside the word generated by bit 31 during the
		;    subtraction;
		;  All other bits zero.
		;
		;The C flag generated by a SUBS instruction is equal to NOT("borrow" from
		;outside the word), so the ORRCC instruction puts the right value into bit 24
		;of d. The other three "borrows" required are found by using the fact that:
		;
		;  (Bit i of a-b) = (a bit i) EOR (b bit i) EOR ("borrow" from bit i)
		;
		;so that:
		;
		;  ("borrow" from bit i) = (a bit i) EOR (b bit i) EOR (Bit i of a-b)
		;
		;and so the EOR/SUBS/EOR/AND sequence puts the right values into bits 0, 8
		;and 16 of d.
		;
		;The code then uses d to generate a bit mask equal to 0x00 in the bytes
		;where a is wanted and to ((a byte) EOR (b byte)) in the bytes where b is
		;wanted. Finally, this is EORed with a to produce the desired value for c.
		
	MEND
	
;---------------------------------------------------------------
; Bit set in a word
; 6 cycles + possible 6 cycles for lookup table
;
;---------------------------------------------------------------
; $a		input word with at most one bit set
; $c		output result of finding position of bit set in a
; $table	register containing pointer to address of lookup table
;           if register does not contain address for lookup table,
;           do not pass anything for $hastable
;			table address given by BitSetTable in file bstables.s
; $hastable parameter which should only be given if $table contains a valid
;			address for the lookup table that is required
;			the value given can be anything and is not required to
;			to be a register
;			if $table is not valid, do not pass anything for this parameter
;
; the code returns in c the position of the bit that
; is set in a, or 32 if the a = 0
;
; Both registers $a and $c must be distinct from register $table
; Register $a need not be distinct from $c.
;
;---------------------------------------------------------------
	IMPORT	BitSetTable
	
	MACRO
	GETBITSET $c, $a, $table, $hastable
		DISTINCT $a, $table
		DISTINCT $c, $table

	 	IF	"$hastable" = ""	; table not given so needs defining
	 		B	%FT02			; branch over the DCD declaration next
01								; label for the DCD declation
			DCD BitSetTable
02			LDR	$table, %BT01	; put pointer to table into $table
			; LDR $table, =BitSetTable 	; not used since may not be able to create
										; literal pool near enough, given method will
										; always work
		ENDIF

		;to translate the word with 0 or 1 bit set into the
		;position of that bit, or a special value to indicate that 
		;no bits are set, one option would be to use a "divide and conquer" 
		;approach - start with a result of 0 and check whether the top 
		;16 bits are zero: if not, increment the result by 16 and shift 
		;the value right by 16. Then do similar things for bits 15:8, 
		;7:4, 3:2, 1 and 0. This takes about 15-20 instructions.

		;a much faster method involves multiplication by a "magic constant".
		;There are only 33 possible values if at most one bit set.
		;If we can multiply by a constant which ends up with a different 
		;value in the top 6 bits of the product for each of these 33 values, 
		;we can then shift that product right by 32-6 = 26 bits and use 
		;it as an index into a lookup table.  After some searching for a 
		;suitable "magic constant", this resulted in the following code:

		;the following multiplication of c by 0x11 and then 0x451 uses 
		;ORR instructions rather than ADDs since doesn't affect the result
		;because X has 0 or 1 bit set, and it speeds up the code on ARM8.
	    ORR     $c,$a,$a,LSL #4     	;c = X * 0x11
	    ORR     $c,$c,$c,LSL #6     	;c = X * 0x451
	    RSB     $c,$c,$c,LSL #16    	;c = X * 0x0450FBAF
	
	    LDRB    $c,[$table,$c,LSR #26]  ;look up table entry indexed by top bits of c
	MEND		
	
;---------------------------------------------------------------
; Least Significant Bit set in a word
; 8 cycles + possible 6 cycles for lookup table
;
;---------------------------------------------------------------
; $a		input word 
; $c		output result of finding least significant bit set in a
; $table	register containing pointer to address of lookup table
;           if register does not contain address for lookup table,
;           do not pass anything for $hastable
;			table address given by BitSetTable in file bstables.s
; $hastable parameter which should only be given if $table contains a valid
;			address for the lookup table that is required
;			the value given can be anything and is not required to
;			to be a register
;			if $table is not valid, do not pass anything for this parameter
;
; the code returns in c the position of the least significant bit that
; is set in a, or 32 if a = 0
;
; Both registers $a and $c must be distinct from register $table
; Register $a need not be distinct from $c.
;
;---------------------------------------------------------------
	MACRO
	LSBSET	$c, $a, $table, $hastable
		;locating the bottom bit is fairly easy, using the fact that 
		;the 2's complement of a number is identical to the number 
		;from bit 0 up to and including the least significant 1, 
		;and its bitwise inverse above that. So (a AND -a) will have a 
		;1 at the position of the least significant 1 in a and zeros 
		;at all other positions. (Or will be zero everywhere if a=0.)
	    RSB     $c,$a,#0            	;Standard trick to isolate X = bottom bit of
	    AND     $c,$c,$a            	;a in c, or produce X = 0 in c if a = 0.
	    
	    GETBITSET $c, $c, $table, $hastable
	
	MEND
	
;---------------------------------------------------------------
; Most Significant Bit set in a word
; 12 cycles + possible 6 cycles for lookup table
;
;---------------------------------------------------------------
; $a		input word 
; $c		output result of finding most significant bit set in a
; $table	register containing pointer to address of lookup table
;           if register does not contain address for lookup table,
;           do not pass anything for $hastable
;			table address given by BitSetTable in file bstables.s
; $hastable parameter which should only be given if $table contains a valid
;			address for the lookup table that is required
;			the value given can be anything and is not required to
;			to be a register
;			if $table is not valid, do not pass anything for this parameter
;
; the code returns in c the position of the most significant bit that
; is set in a, or 32 if a = 0
;
; Both registers $a and $c must be distinct from register $table
; Register $a need not be distinct from $c.
;
;---------------------------------------------------------------
	MACRO
	MSBSET	$c, $a, $table, $hastable
		;located the top bit
	    ORR    $c,$a,$a,LSR #1
	    ORR    $c,$c,$c,LSR #2
	    ORR    $c,$c,$c,LSR #4
	    ORR    $c,$c,$c,LSR #8
	    ORR    $c,$c,$c,LSR #16     ;c contains 1s from the most significant 
	    							;1 in a downwards.
	    BIC    $c,$c,$c,LSR #1      ;c now contains only the most significant 1 in a.

		GETBITSET $c, $c, $table, $hastable
	MEND
	
;---------------------------------------------------------------
; Population count
; 10 cycles + 2 register constants
;
;---------------------------------------------------------------
; $a		input word
; $c		output result of population count
; $t		temporary register
;
; constant1 = 0x49249249
; constant2 = 0xC71C71C7
;
; the code returns in c the number of 1's set in the binary 
; expression for a
;
; uses 'divide by 3 and conquer'. 
;
; Registers $constant1, $constant2, $t and $c must all be distinct from each other
; Registers $a and $t must be distinct registers from each other.
; Register $a need not be distinct from one of $constant1, $constant2 or $c
;
;---------------------------------------------------------------

	MACRO
	POPCOUNT	$c, $a, $t, $constant1, $constant2
		DISTINCT $c, $t, $constant1, $constant2
		DISTINCT $a, $t
		
		; Use a divide by 3 and conquer approach
			
		; Add up bits in the triplets 31:29,
		AND $t, $a, $constant1, LSL #1
	 	; 28:26, 25:23, 22:20, 19:17, 16:14,
	 	SUB $c, $a, $t, LSR #1
	 	; 13:11, 10:8, 7:5, 4:2 and the 
	 	AND $t, $c, $constant1, LSR #1
	 	; pair 1:0 
	 	ADD $c, $c, $t
	 	
	 	; The last four instructions basically halved the value
	 	; of the top bit in each triplet and doubled the value
	 	; of the bottom bit
	 	
	 	; Add adjacent triplet sums,
	 	ADD $c, $c, $c, LSR #3
	 	; and then take every alternate result
	 	AND $c, $c, $constant2
	 	
	 	; Add the resulting sums of 3, 6, 6,
	 	ADD $c, $c, $c, LSR #6
	 	; 6, 6 and 5 bits together
	 	ADD $c, $c, $c, LSR #12 			 
	 	ADD $c, $c, $c, LSR #24
	 	 
	 	; Throw away all the "junk" in the remaining bits
		AND $c, $c, #63
 	MEND
 	
;---------------------------------------------------------------
; Population count over seven words
; 46 cycles + 3 register constants
;
;---------------------------------------------------------------
; $a, $b	input words a and b
; $c, $d	input words c and d
; $e, $f	input words e and f
; $g		input word g
; $res		output result of population count over seven words
;
; constant1 = 0x55555555
; constant2 = 0x33333333
; constant3 = 0x0F0F0F0F
;
; the code returns in res the number of 1's set in the binary 
; expressions for all the words a, b, c, d, e, f and g
;
; uses 'divide by 3 and conquer'.
;
; Registers $a, $b, $c, $d, $e, $f and $g are corrupted.
;
; Registers $a, $b, $c, $d, $e, $f, $g, $constant1, $constant2 and
; $constant3 must all be distinct registers from each other.
; Register $res need not be distinct from any one of the other registers.
;
;---------------------------------------------------------------

	; The macro definitions prefixed POPCOUNT7_INTERNAL are intended only for use 
	; internally to POPCOUNT7 and have no significance outside of that context
	
	MACRO
	POPCOUNT7_INTERNAL_PARALLEL_ADD_MACRO	$a, $b, $c
		; Calculate 2*b+a := a+b+c
		
		EOR     $a,$a,$b
	    BIC     $b,$b,$a        ;Calculates b AND NOT (a EOR b) = a AND b
	    EOR     $a,$a,$c
	    BIC     $c,$c,$a        ;Same technique
	    ORR     $b,$b,$c 
	MEND

	MACRO
	POPCOUNT7_INTERNAL_POPCOUNT_MACRO	$c, $a, $constant1, $constant2, $constant3
		; Does a population count on a, stopping at the point where each byte
		; contains its own population count in the range 0-8 with the result
		; stored in c - same constants as given above
	
	    BIC     $c,$a,$constant1
	    SUB     $a,$a,$c,LSR #1
	    BIC     $c,$a,$constant2
	    AND     $a,$a,$constant2
	    ADD     $a,$a,$c,LSR #2
	    ADD     $a,$a,$a,LSR #4
		AND     $a,$a,$constant3
	MEND

	MACRO
 	POPCOUNT7 $res, $a, $b, $c, $d, $e, $f, $g, $constant1, $constant2, $constant3
 		DISTINCT $a, $b, $c, $d, $e, $f, $g, $constant1, $constant2, $constant3
 		
		; We start by doing a "parallel addition" of the words. The basic idea
		; here is that if we have two 32-bit values a and b, and we calculate
		; x = a AND b, y = a EOR b, then at each bit position, we have:
		;
		;   2*(x bit) + (y bit) = (a bit) + (b bit)
		;
		; i.e. we have effectively added 32 1-bit numbers in parallel, storing the
		; least significant bit of each sum in y and the next bit in x. This
		; idea is extended here to produce something similar which does:
		;
		;   4*(c bit) + 2*(b bit) + (a bit)
		;     = (a bit)+(b bit)+(c bit)+(d bit)+(e bit)+(f bit)+(g bit)
		;
		; Relationships like this are denoted in an abbreviated way in the
		; comments below - this one is described as 4c+2b+a :=
		; a+b+c+d+e+f+g, for instance.
		;
		; Then we just have to calculate 4*popcount(c)+2*popcount(b)+popcount(a)
		; to get the desired result. Some code is saved here by only doing part of
		; the popcount operations before combining the results.
		;
		; The net result is 46 instructions and 46 cycles to do a population count on
		; 224 bits, i.e. a counting rate of nearly 5 bits per cycle. (As a point of
		; comparison, naive code which simply shifts the bits out of the registers and
		; increments a register each time a 1 is shifted out is likely to end up more
		; like 2-6 cycles per bit, depending on the amount of loop unrolling i.e.
		; this code is about 10-30 times faster.)
	
		; 2*b+a := a+b+c:
		
		POPCOUNT7_INTERNAL_PARALLEL_ADD_MACRO	$a, $b, $c
	
		; 2*e+d := d+e+f similarly:
	
		POPCOUNT7_INTERNAL_PARALLEL_ADD_MACRO	$d, $e, $f
	
		; 2*d+a := (new a)+(new d)+g similarly:
	
		POPCOUNT7_INTERNAL_PARALLEL_ADD_MACRO	$a, $d, $g
	
		; Stuff so far has given us 2*b+2*d+2*e+a := a+b+c+d+e+f+g
		; overall, so we can complete 4*c+2*b+a := a+b+c+d+e+f+g by
		; doing 2*c+b := b+d+e:
	
		; Not quite the same as POPCOUNT7_INTERNAL_PARALLEL_ADD_MACRO (though close)
	    EOR     $b,$b,$d
	    BIC     $c,$d,$b
	    EOR     $b,$b,$e
	    BIC     $e,$e,$b
	    ORR     $c,$c,$e 
	
		; Do population count on a, stopping at the point where we have each byte
		; containing its own population count in the range 0-8. Then do the same
		; for each of b and c.
	
		POPCOUNT7_INTERNAL_POPCOUNT_MACRO $g, $a, $constant1, $constant2, $constant3
	
		POPCOUNT7_INTERNAL_POPCOUNT_MACRO $g, $b, $constant1, $constant2, $constant3
	
		POPCOUNT7_INTERNAL_POPCOUNT_MACRO $g, $c, $constant1, $constant2, $constant3
	
		; Add up 4*popcount(c)+2*popcount(b)+popcount(a) for each byte
		; separately now, obtaining a number in a with 4 bytes in the range 0-56
		; to be added together.
	
	    ADD     $a,$a,$b,LSL #1
	    ADD     $a,$a,$c,LSL #2
	
		; Add them together in the bottom byte, discarding the junk left in the
		; other bytes.
	
	    ADD     $a,$a,$a,LSR #8
	    ADD     $a,$a,$a,LSR #16
	    AND     $res,$a,#0xFF
    
    MEND

;;;;;;;
; END ;
;;;;;;;

	END

