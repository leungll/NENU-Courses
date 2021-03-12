/*
 * Utility Library: Bit Utility macros
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _BITUTIL_C_
#define _BITUTIL_C_

/**** BITREVERSEWORD ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given a word reverse the bits so that bit x becomes bit 31-x in the new word
 *
 * Inputs
 * ------
 *   WORD
 *   - the word to reverse bits of
 *   REVERSED
 *   - a word to hold the bit reversed version of WORD
 * Outputs
 * -------
 *   REVERSED
 *   - the bit reversed version of WORD
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define BITREVERSEWORD( WORD, REVERSED ) { \
	BYTEREVERSEWORD( WORD, REVERSED ) ; \
	REVERSEUNITS( REVERSED, REVERSED, 0x0F0F0F0F, 4 ) ; \
	REVERSEUNITS( REVERSED, REVERSED, 0x33333333, 2 ) ; \
	REVERSEUNITS( REVERSED, REVERSED, 0x55555555, 1 ) ; \
}

/**** BYTEREVERSEWORD ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given a word (a,b,c,d), reverse the bytes to give the word (d,c,b,a)
 *
 * Inputs
 * ------
 *   WORD
 *   - the word to reverse bytes of
 *   REVERSED
 *   - a word to hold the byte reversed version of WORD
 * Outputs
 * -------
 *   REVERSED
 *   - the byte reversed version of WORD
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define BYTEREVERSEWORD( WORD, REVERSED ) { \
	unsigned int	rorred ; \
	ROR( WORD, 16, rorred ) ; \
	rorred = ( WORD ^ rorred ) & ~0xFF0000 ; \
	ROR( WORD, 8, REVERSED ) ; \
	REVERSED ^= rorred >> 8 ; \
}

/**** ISPOWEROF2 ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determines if the given integer number is a power of 2 (zero is not!)
 *
 * Inputs
 * ------
 *   NUMBER
 *   - the integer number to test
 *   IS
 *   - integer to hold the result of the test
 * Outputs
 * -------
 *   IS
 *   - the result of the test for power of 2
 *     0	the given number is not a power of 2 (false)
 *     1	the given number is a power of 2 (true)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define ISPOWEROF2( NUMBER, IS ) { \
	IS = 0 ; \
	if( ( NUMBER != 0 ) && ( NUMBER == ( NUMBER & ( -NUMBER ) ) ) ) { \
		IS = 1 ; \
	} \
}

/**** MAXBITSET *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine the maximum bit position that is set in the given word
 *
 * negative values are first made positive then the maximum bit position is found
 *
 * Inputs
 * ------
 *   WORD
 *   - a 32-bit integer word to find the maximum bit position set
 *   MAXBIT
 *   - integer to hold the maximum bit set from { -1, 0..30 }
 * Outputs
 * -------
 *   MAXBIT
 *   - the maximum bit set in the given word
 *     0..30	the maximum bit set
 *     -1		the given word was zero
 *
 * Notes
 * -----
 * the bit range for a word is from bit 0 to bit 30 (not including sign bit)
 *
 * to determine the number of bits required for data add two (2) to the returned value:
 * one (1) for the sign bit and one (1) to shift the range 0..30 to 1..31, the number of
 * bits the data actually uses
 *
 * a zero value (-1 returned) still requires one bit to hold value
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define MAXBITSET( WORD, MAXBIT ) { \
	unsigned int	posWord = ( unsigned int )WORD ; \
	unsigned int 	test ; \
	unsigned int	newTest ; \
	if( WORD == 0 ) { \
		MAXBIT = -1 ; \
		/* -1 since data requires MAXBIT + 2 bits (1 for sign, 1 to shift 0..30 to 1..31) */ \
	} \
	else { \
		MAXBIT = 0 ; \
		if( WORD < 0 ) { \
			posWord = ( unsigned int )-WORD ; \
		} \
		test = posWord >> 16 ; \
		if( !test ) { \
			test = posWord & 0x0000FFFF ; \
		} \
		else { \
			MAXBIT = 16 ; \
		} \
		if( ( newTest = test >> 8 ) == 0 ) { \
			newTest = test &0x00FF ; \
		} \
		else { \
			MAXBIT += 8 ; \
		} \
		if( ( test = newTest >> 4 ) == 0 ) { \
			test = newTest & 0x0F ; \
		} \
		else { \
			MAXBIT += 4 ; \
		} \
		if( ( newTest = test >> 2 ) == 0 ) { \
			newTest = test & 0x6 ; \
		} \
		else { \
			MAXBIT += 2 ; \
		} \
		if( ( test = newTest >> 1 ) != 0 ) { \
			MAXBIT += 1 ; \
		} \
	} \
}

/**** POPULATIONCOUNT ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine number of set bits in the binary representation of the given word (including
 * the sign bit)
 *
 * Inputs
 * ------
 *   WORD
 *   - the word to count the number of bits set
 *   COUNT
 *   - an integer to hold the number of bits set in WORD
 * Outputs
 * -------
 *   COUNT
 *   - the result of the count on the number of bits set in WORD
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define POPULATIONCOUNT( WORD, COUNT ) { \
	unsigned int temp1 ; \
	unsigned int temp2 ; \
	unsigned int constant1 = 0x49249249 ; \
	temp2 = WORD & ( constant1 << 1 ) ; \
	temp1 = WORD - ( temp2 >> 1 ) ; \
	temp2 = temp1 & ( constant1 >> 1 ) ; \
	temp1 += temp2 ; \
	temp1 += ( temp1 >> 3 ) ; \
	temp1 &= 0xC71C71C7 ; \
	temp1 += ( temp1 >> 6 ) ; \
	temp1 += ( temp1 >> 12 ) ; \
	temp1 += ( temp1 >> 24 ) ; \
	COUNT = temp1 & 63 ; \
}

/**** REMOVESIGNEXTEND **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * remove any sign extension from the given data value that is of the given number 
 * of bits in size after removing sign extension
 *
 * Inputs
 * ------
 *   DATA
 *   - the data value to remove sign extend from
 *   BITS
 *   - the size of the data in bits (including sign bit) after removing sign extension
 * Outputs
 * -------
 *   DATA
 *   - the data with any sign extension removed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define REMOVESIGNEXTEND( DATA, BITS ) { \
	unsigned int mask = 0xFFFFFFFF ; \
	if( ( BITS > 0 ) && ( BITS < 32 ) ) { \
		DATA = ( int )( ( int )DATA & ( mask >> ( 31 - ( BITS - 1 ) ) ) ) ; \
	} \
}

/**** REMOVESIGNEXTENDARRAY *********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * remove any sign extension from the given array of data, each entry of the given 
 * number of bits in size after removing the sign extension
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of data values to remove any sign extension
 *   SIZE
 *   - the number of entries/data points in the array
 *   BITS
 *   - the size of each data item in bits (including sign bit) after removing sign extension
 * Outputs
 * -------
 *   ARRAY
 *   - the array of data items with any sign extension removed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define REMOVESIGNEXTENDARRAY( ARRAY, SIZE, BITS ) { \
	int counter ; \
	for( counter = 0 ; counter < SIZE ; counter += 1 ) { \
		REMOVESIGNEXTEND( ARRAY[ counter ], BITS ) ; \
	} \
}

/**** REVERSEUNITS ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given a word reverse the required bit-size units
 *
 * Inputs
 * ------
 *   WORD
 *   - the word to reverse bit-size units of
 *   REVERSED
 *   - a word to hold the unit reversed version of WORD
 *   MASK
 *   - a constant value that must contain one of
 *     0x0000FFFF	reverse units of 16-bits
 *     = (a,b)->(b,a)
 *	   0x00FF00FF	reverse units of 8-bits
 *     = (a,b,c,d)->(b,a,d,c)
 *     0x0F0F0F0F	reverse units of 4-bits
 *     = (a,b,c,d,e,f,g,h)->(b,a,d,c,f,e,h,g)
 *     0x33333333	reverse units of 2-bits
 *     = (a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)->(b,a,d,c,f,e,h,g,j,i,l,k,n,m,p,o)
 *     0x55555555	reverse units of 1-bit
 *     = (a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,aa,bb,cc,dd,ee,ff)
 *     -> (b,a,d,c,f,e,h,g,j,i,l,k,n,m,p,o,r,q,t,s,v,u,x,w,z,y,bb,aa,dd,cc,ff,ee)
 *   BITS
 *   - a constant value that must be either 16, 8, 4, 2 or 1
 *     any other value, the returned value is undertermined
 * Outputs
 * -------
 *   REVERSED
 *   - the unit reversed version of WORD
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define REVERSEUNITS( WORD, REVERSED, MASK, BITS ) { \
	unsigned int	topBits ; \
	topBits = ( ( unsigned int )WORD >> BITS ) & ( unsigned int )MASK ; \
	REVERSED = ( unsigned int )WORD & ( unsigned int )MASK ; \
	REVERSED = topBits | ( ( unsigned int )REVERSED << BITS ) ; \
}

/**** ROR ***************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * rotate right the given word by the given number of bits
 *
 * Inputs
 * ------
 *   WORD
 *   - the word to rotate right
 *   BITS
 *   - the number of bits to rotate by
 *   ROTATED
 *   - a word to hold the rotated word result
 * Outputs
 * -------
 *   ROTATED
 *   - the rotated word result
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define ROR( WORD, BITS, ROTATED ) { \
	if( ( BITS >= 0 ) && ( BITS <= 32 ) ) { \
		ROTATED = ( WORD << ( 32 - BITS ) ) | ( ( unsigned int )WORD >> BITS ) ; \
	} \
}

/**** SIGNEDSATURATION **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given two signed numbers, add them together saturating the result
 *
 * Inputs
 * ------
 *   NUMBER1, NUMBER2
 *   - the two signed numbers to add together
 *   SIGNSAT
 *   - an integer to hold the result of the signed saturated addition
 * Outputs
 * -------
 *   SIGNSAT
 *   - the result of the signed saturation addition
 *     if the result overflows the negative range, the result is 0x80000000
 *     if the result overflows the positive range, the result is 0x7FFFFFFF
 *     otherwise the result is the result of the addition
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define SIGNEDSATURATION( NUMBER1, NUMBER2, SIGNSAT ) { \
	int	sign = 0x80000000 ; \
	SIGNSAT = NUMBER1 + NUMBER2 ; \
	if( ( ( NUMBER1 & sign ) == ( NUMBER2 & sign ) ) \
		&& ( ( NUMBER1 & sign ) != ( SIGNSAT & sign ) ) ) { \
		SIGNSAT = sign ^ ( ( signed )SIGNSAT >> 31 ) ; \
	} \
}

/**** SIGNEXTEND ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * sign extend the given data value that is of the given number of bits in size
 *
 * Inputs
 * ------
 *   DATA
 *   - the data value to sign extend
 *   BITS
 *   - the size of the data in bits (including sign bit)
 * Outputs
 * -------
 *   DATA
 *   - the sign extended data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define SIGNEXTEND( DATA, BITS ) { \
	int	mask = 0xFFFFFFFF ; \
	if( ( BITS > 0 ) && ( BITS < 32 ) ) { \
		if( ( int )DATA & ( 1 << ( BITS - 1 ) ) ) { \
			DATA = ( int )DATA | ( ( mask >> ( BITS - 1 ) ) << ( BITS - 1 )) ; \
		} \
	} \
}

/**** SIGNEXTENDARRAY ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * sign extend the given array of data, each entry of the given number of bits in size
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of data values to sign extend
 *   SIZE
 *   - the number of entries/data points in the array
 *   BITS
 *   - the size of each data item in bits (including sign bit)
 * Outputs
 * -------
 *   ARRAY
 *   - the array of sign extended data items
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define SIGNEXTENDARRAY( ARRAY, SIZE, BITS ) { \
	unsigned int counter ; \
	for( counter = 0 ; counter < SIZE ; counter += 1 ) { \
		SIGNEXTEND( ARRAY[ counter ], BITS ) ; \
	} \
}

/**** TOTALBITS *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine the minimum number of bits that are required to hold the given array of
 * data
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of data to determine the number of bits required
 *   SIZE
 *   - the number of entries/data points in the array
 *   BITS
 *   - integer to hold the minimum number of bits required for the data
 * Outputs
 * -------
 *   BITS
 *   - the minimum number of bits that are required to hold data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define TOTALBITS( ARRAY, SIZE, BITS ) { \
	int	counter ; \
	int	maxBit ; \
	for( BITS = 0, counter = 0 ; counter < SIZE ; counter += 1, BITS += maxBit + 2 ) { \
	/* add 2 since data requires maxBit + 2 bits (1 for sign, 1 to shift 0..30 to 1..31) */ \
		MAXBITSET( ARRAY[ counter ], maxBit ) ; \
	} \
}

/**** TOTALBITS2D *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine the minimum number of bits that are required to hold the given 2D array of
 * data
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of data to determine the number of bits required
 *   WIDTH
 *   - the number of columns in the array
 *   HEIGHT
 *   - the number of rows in the array
 *   BITS
 *   - integer to hold the minimum number of bits required for the data
 * Outputs
 * -------
 *   BITS
 *   - the minimum number of bits that are required to hold data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define TOTALBITS2D( ARRAY, WIDTH, HEIGHT, BITS ) { \
	int y ; \
	int	bits1d ; \
	for( BITS = 0, y = 0 ; y < HEIGHT ; y += 1, BITS += bits1d ) { \
		TOTALBITS( ARRAY[ y ], WIDTH, bits1d ) ; \
	} \
}

void *SwitchEndian( void *data, unsigned int n, unsigned int bytes, unsigned int overwrite ) ;


#endif	/* _BITUTIL_C_ */