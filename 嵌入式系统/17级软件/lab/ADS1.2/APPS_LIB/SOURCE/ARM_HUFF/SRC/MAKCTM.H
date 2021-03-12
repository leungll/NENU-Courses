/*
 * Huffman code table macro
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _MAKE_CODE_TABLE_C_
#define _MAKE_CODE_TABLE_C_

#include <stdio.h>
#include <stdlib.h>

/*
the function definition and prototype are defined in the header file

the definitions are based on SIZE being defined before this macro file is included
*/
#include "makctc.h"

/**** MakeHuffCodeTable8, MakeHuffCodeTable16, MakeHuffCodeTable32 ******************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate the symbol-to-codeword lookup table for each size of symbol data
 *
 * Inputs
 * ------
 *   symbols
 *   - an array of symbols that occur in the data to be coded that must be sorted into
 *     increasing order of frequency of occurrence
 *     the type for the symbols and hence size of symbols must be defined by SIZE before
 *     this macro file is included
 *   nsymbols
 *   - the number of symbols referenced by the symbol array
 *   freqcodelen
 *   - an array of frequency of occurrence for each length of codeword
 *   maxcodewlen
 *   - the maximum length of codeword that can be created
 *     (maxcodewlen + 1) defines the last index into the array freqcodelen
 *     value also defines the position in the codeword that the length of the codeword is packed
 *     and must be the same value that is given to the bit coder function for the code table
 * Return Values
 * ------ ------
 *     unsigned int * - an array that represents the symbol-to-codeword lookup table with the
 *                      codeword in the bottom maxcodewlen bits, the length in the bits over this
 *     NULL			  - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned codeword-length lookup table
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
MCTFUNCTIONDECLARATION( SIZE, TYPE )
{
	unsigned int	*codetable ;
	unsigned int	codeword ;
	unsigned int	ncodewords ;
	unsigned int	i ;
	int				j ;
	
	if( ( symbols == NULL ) || ( nsymbols == 0 ) || ( freqcodelen == NULL ) || ( maxcodewlen == 0 ) || ( maxcodewlen > MAXCODEBITS ) ) {
		fprintf( stderr, "[MakeHuffCodeTable] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/*
	create the array to hold codeword-length lookup table
	*/
	if( ( codetable = ( unsigned int * )calloc( nsymbols, sizeof( unsigned int ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	codeword = 0 ;								/* initialise the codeword base as zero */
	j = nsymbols - 1 ;							/* initialise to maximumally occuring symbol index in data */
	
	/*
	for each possible length of codeword, while there exists a codeword of a given length assign a
	codeword to its respective symbol using the fact that the symbol array is sorted in increasing order
	of frequency thus the last entry in the array should have the shortest codeword
	
	(there is no possible codeword of length 0, hence start with length 1)
	*/
	for( i = 1 ; i <= maxcodewlen ; i += 1 ) {
		/*
		intialise the codeword base for the given length of codeword so that the binary expression for
		the codeword base gives the smallest binary number possible for all codewords with given length
		to start from which has a unique prefix to all other codewords and remains within correct number of
		bits

		this only works if the number of occurrences of any given codeword length have been determined correctly
		so that the range of values for codewordbase does not exceed the maximum number of bits

		thus for length i there can be at most 2^( i - 1 ) codewords
		*/
		codeword <<= 1 ;						/* shift codeword into correct number of bits with unique prefix */
		ncodewords = freqcodelen[ i ] ;			/* get the number of codewords of length i */
		while( ncodewords > 0 ) {				/* while there exist codewords of length i... */
			/*
			create the codeword for the given symbol with the top bits containing the length of
			the codeword, the bottom maxcodewlen-bits containing the actual codeword
			*/
			codetable[ symbols[ j-- ] ] = ( i << maxcodewlen ) + codeword ;
			ncodewords -= 1 ;					/* ...decrement number of codewords of length i */
			codeword += 1 ;						/* ...move to next codeword in sequence */
		}
	}
	
	/*
	whilst there exist more symbols which have not been allocated codewords, these symbols do not have
	codewords and should be zero-initialised for their codeword
	*/
	for( ; j >= 0 ; j -= 1 ) {
		codetable[ symbols[ j ] ] = 0 ;
	}
	
	return codetable ;
}

#endif	/* _MAKE_CODE_TABLE_C_ */