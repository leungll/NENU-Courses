/*
 * Huffman decode table macro
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _MAKE_DECODE_TABLE_C_
#define _MAKE_DECODE_TABLE_C_

#include <stdio.h>
#include <stdlib.h>

/*
the function definition and prototype are defined in the header file

the definitions are based on SIZE being defined before this macro file is included
*/
#include "mkdctc.h"

/**** MakeHuffDecodeTable8, MakeHuffDecodeTable16, MakeHuffDecodeTable32 ************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate the codeword-to-symbol lookup tables for each size of symbol data
 *
 * Inputs
 * ------
 *   symbols
 *   - an array of symbols that occurred in the data that was coded that must be sorted into
 *     increasing order of frequency of occurrence
 *     the type for the symbols and hence size of symbols must be defined by SIZE before
 *     this macro file is included
 *   nsymbols
 *   - the number of symbols referenced by the symbol array
 *   freqcodelen
 *   - an array of frequency of occurrence for each length of codeword
 *   maxcodewlen
 *   - the maximum length of codeword that can be decoded
 *     (maxcodewlen + 1) defines the last index into the array freqcodelen
 *   tablebits
 *   - the maximum length of codeword that can be decoded directly using a lookup table
 *     all lengths of codeword over this being decoded using a tree
 *   lentable
 *   - a pointer to an array to hold the decoded codeword length table/tree
 * Outputs
 * -------
 *   lentable
 *   - a pointer to the decoded codeword length table/tree that is synchronised with the
 *     decoded symbol table/tree that is returned
 * Return Values
 * ------ ------
 *     unsigned char *, unsigned short * or unsigned int *
 *           - an array that represents the codeword-to-symbol lookup table/tree
 *             with the size of the data items determined by the value of SIZE that must
 *             be defined before this macro is called
 *     NULL	 - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned length and symbol lookup tables/trees
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
MDCTFUNCTIONDECLARATION( SIZE, TYPE )
{
	TYPE			*decodetable ;
	unsigned int	codeword ;
	unsigned int	ncodewords ;
	int				i, j, k ;
	unsigned int	treestartoffset ;
	unsigned int	nodepair ;
	unsigned int	bits ;
	TYPE			*decparent ;
	unsigned char	*lenparent ;
	
	if( ( symbols == NULL ) || ( nsymbols == 0 ) || ( freqcodelen == NULL ) || ( maxcodewlen == 0 ) || ( maxcodewlen > MAXCODEBITS ) || ( lentable == NULL ) ) {
		fprintf( stderr, "[MakeHuffDecodeTable] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/*
	create the arrays to hold all the data for coding
	*/
	if( ( decodetable = ( TYPE * )calloc( ( 1 << tablebits ) + nsymbols*2 + 2, sizeof( TYPE ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	if( ( *lentable = ( unsigned char * )calloc( ( 1 << tablebits ) + nsymbols*2 + 2, sizeof( unsigned char ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		free( ( void * ) decodetable ) ;
		return NULL ;
	}
	
	codeword = 0 ;								/* initialise the codeword base as zero */
	k = nsymbols - 1 ;							/* initialise to maximumally occuring symbol index */
	/*
	for all codeword lengths that can be decoded directly, create the lookup table
	*/
	if( tablebits > 0 ) {
		for( i = 1 ; i <= tablebits ; i += 1 ) {
			ncodewords = freqcodelen[ i ] ;		/* get the number of codewords of length i */
			while( ncodewords > 0 ) {			/* while there exist codewords of length i... */
				/* 
				define a series of lookup entries so that codeword can be looked up directly
				
				tablebits of data will be the index into the lookup table with the top bits consisting
				of the codeword being decoded, all remaining bits below this can be set as anything
				thus an entry must be created for all possible values of these remaining bits
				*/
				for( j = 0 ; j < ( 1 << ( tablebits - i ) ) ; j += 1 ) {
					decodetable[ codeword + j ] = symbols[ k ] ;
					( *lentable )[ codeword + j ] = ( unsigned char )i ;	
				}
				ncodewords -= 1 ;				/* ...decrement number of codewords of length i */
				codeword += 1 << ( tablebits - i ) ; /* move to next codeword in sequence, codeword at top */
				k -= 1 ;						/* move to next most occurring symbol */
			}
		}
	}
	
	treestartoffset = 1 << tablebits ;			/* define the memory address of the tree */
	/* 
	initialise the first node pair which will be the offset to children from parent
	
	cannot start at zero since this would give an offset of zero which cannot be distinguished from
	a parent which has not previously been set up
	*/
	nodepair = 2 ;								
	/*
	for each codeword of length over tablebits up to the maximum length, create a decoding tree
	*/
	for( i = tablebits + 1 ; i <= maxcodewlen ; i += 1 ) {
		codeword <<= 1 ;						/* shift codeword into correct number of bits with unique prefix */
		ncodewords = freqcodelen[ i ] ;			/* get the number of codewords of length i */
		while( ncodewords > 0 ) {				/* while there exist codewords of length i... */
			
			bits = i - tablebits ;				/* get length of the codeword over that which can be decoded directly */
			decparent = &( decodetable[ codeword >> bits ] ) ;		/* lookup the first tablebits of the codeword in symbol table */
			lenparent = &( ( *lentable )[ codeword >> bits ] ) ;	/* likewise for the length table */
			
			/*
			for each bit of the codeword after the first tablebits set up a tree decoder
			*/
			for( j = 1 << bits - 1 ; j > 0 ; j >>= 1 ) {
				if( *decparent == 0 ) {			/* if parent is zero, parent does not exist so needs initialsing */
					*decparent = ( TYPE )( nodepair >> 1 ) ;	/* set value for parent as next node offset */
					*lenparent = 255 ;			/* initialise length as 255 for internal node */
					
					/* clear the left and right children at the offset given so that do not contain branches */
					decodetable[ treestartoffset + nodepair ] = 0 ;
					decodetable[ treestartoffset + nodepair + 1 ] = 0 ;
					/* initialise length entries for left and right children at offset given so internal nodes */
					( *lentable )[ treestartoffset + nodepair ] = 255 ;
					( *lentable )[ treestartoffset + nodepair + 1 ] = 255 ;
	
					nodepair += 2 ;				/* move to next node pair */
				}
				/* set next parents as the left child of the current parent */
				lenparent = &( ( *lentable )[ treestartoffset + ( *decparent << 1 ) ] ) ;
				decparent = &( decodetable[ treestartoffset + ( *decparent << 1 ) ] ) ;
				/* if the current bit is set in the codeword, next parent should be the right child of the current parent */
				if( codeword & j ) {
					decparent += 1 ;
					lenparent += 1 ;
				}
			}
			*decparent = symbols[ k-- ] ;		/* a leaf node is reached, codeword decoded so add symbol to leaf */
			*lenparent = ( unsigned char )( 255 - i ) ;	/* set length of codeword, subtracting this from 255 as part of tree setup */
			
			ncodewords -= 1 ;					/* ...decrement number of codewords of length i */
			codeword += 1 ;						/* ...move to next codeword in sequence */
		}
	}
	
	return decodetable ;
}

#endif	/* _MAKE_DECODE_TABLE_C_ */