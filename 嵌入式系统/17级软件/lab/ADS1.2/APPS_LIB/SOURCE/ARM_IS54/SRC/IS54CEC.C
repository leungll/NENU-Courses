/*
 * IS-54-B Convolutional Encoder C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "is54cec.h"

/**** ConvEncoderC ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of seven unsigned short data values, the last of which being 0x0000,
 * IS54 convolutionally encode them and return the result split over an array of
 * unsigned integer values with six entries
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array of unsigned integers to hold the result of the encoding
 *     which must reference at least six entries
 *   inputs
 *   - an array of seven unsigned shorts that contains the 89 bits of data to be 
 *     IS54 convolutionally encoded together with 23 bits of padding thus the last entry
 *     should be 0x0000
 * Outputs
 * -------
 *   outputs
 *   - contains the 178-bits of encoded values split over the six entries of the array
 *     with 14 pad bits in the high bits of the last entry (assuming the input array
 *     was correctly padded)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void ConvEncoderC( unsigned int outputs[ ], unsigned short inputs[ ] )
{
	const unsigned int	inMask  = 0x0000FFFF ;
	const unsigned int	outMask = 0x00000001 ;
	unsigned int		counter ;
	unsigned int		input ;
	unsigned short		d0, d1, d2, d3, d4, d5 ;
	unsigned short		g0, g1 ;
	unsigned int		output ;
	unsigned int		shifter ;
	
	/* last input is 0x0000 for end of encoding sequence */
	for( counter = 0 ; counter < 6 ; counter += 1 ) {
		/* get current 16 bits + previous 16 bits */
		input = ( ( unsigned int )( inputs[ counter + 1 ] << 16 ) ) | ( ( unsigned int )inputs[ counter ] ) ;
		
		/* undelayed input */
		d0 = ( unsigned short )( inMask & input ) ;
		/* delayed by 1 */
		d1 = ( unsigned short )( inMask & ( input >> 1 ) ) ;
		/* delayed by 2 */
		d2 = ( unsigned short )( inMask & ( input >> 2 ) ) ;
		/* delayed by 3 */
		d3 = ( unsigned short )( inMask & ( input >> 3 ) ) ;
		/* delayed by 4 */
		d4 = ( unsigned short )( inMask & ( input >> 4 ) ) ;
		/* delayed by 5 */
		d5 = ( unsigned short )( inMask & ( input >> 5 ) ) ;
		
		g0 = ( unsigned short )( d0 ^ d1 ^ d3 ^ d5 ) ;
		g1 = ( unsigned short )( g0 ^ d1 ^ d2 ^ d4 ) ;	/* g1 = d0^d2^d3^d4^d5 */
		
		output = 0 ;
		for( shifter = 0 ; shifter < 16 ; shifter += 1 ) {
			output |= ( ( ( unsigned int )( g0 >> shifter ) ) & outMask ) << ( 2 * shifter ) ;
			output |= ( ( ( unsigned int )( g1 >> shifter ) ) & outMask ) << ( 2 * shifter + 1 ) ;
		}
		
		outputs[ counter ] = output ;		/* write 32 bits of output */
	}
}
