/*
 * Utility Library: Bit Utility
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitutilc.h"

#include "definesc.h"

void ProveBitUtil( void ) ;

/**** ProveBitUtil ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * using some simple test data call an instance of each of the macros so that they
 * are test compiled to at least prove compilation for the given test data
 *
 * this procedure is only included for testing purposes and has no real use outside
 * of this and should be ignored
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void ProveBitUtil( void )
{
	int				data = 0 ;
	unsigned int	is2 ;
	int				array[ 1 ] ;
	int				array2D[ 1 ][ 1 ] ;
	unsigned int	bits ;
	
	BYTEREVERSEWORD( data, data ) ;	/* uses ROR */
	ISPOWEROF2( 0, is2 ) ;
	POPULATIONCOUNT( 0, data ) ;
	REMOVESIGNEXTENDARRAY( array, 1, 1 ) ;	/* uses REMOVESIGNEXTEND */
	SIGNEDSATURATION( 0, 0, data ) ;
	SIGNEXTENDARRAY( array, 1, 1 ) ;	/* uses SIGNEXTEND */
	TOTALBITS2D( array2D, 1, 1, bits ) ;	/* uses TOTALBITS + MAXBITSET */
}

/**** SwitchEndian ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * reverse the bytes of each entry in the given array and hence the endianness
 *
 * by the nature of the operation, the data must be unsigned
 *
 * Inputs
 * ------
 *   data
 *   - the array to reverse endianness of
 *   n
 *   - the number of data items in the array to reverse
 *   bytes
 *   - the number of bytes in the data that is to be reversed
 *     1 = char data
 *     2 = short data
 *     4 = int data
 *   overwrite
 *   - 0 : the data should be endian swapped into a new array
 *     1 : the data should be endian swapped into the given array
 *         this overwrites each data entry with its endian swapped version
 * Outputs
 * -------
 *   none
 * Return Values
 * ------ ------
 *     void * - an array that holds the endian swapped data
 *              array is of type char (bytes == 1), short (bytes == 2) or int (bytes == 4)
 *              array references new memory if overwrite == 0 or data if overwrite == 1
 *     NULL   - some error occurred
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * if owerwrite == 1, the returned array has been allocated
 * deallocate after use
 *
 * Memory deallocated (not allocated)
 * ------ -----------  --- ---------
 * none
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void *SwitchEndian( void *data, unsigned int n, unsigned int bytes, unsigned int overwrite )
{
	void			*newdata ;
	unsigned short	ubig ;
	unsigned int	i ;

	if( ( !data ) || ( n == 0 ) ) {
		fprintf( stderr, "Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( !overwrite ) {
		if( ( newdata = calloc( n, bytes ) ) == NULL ) {
			fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
			return NULL ;
		}
		if( bytes == BYTEBYTES ) {
			return memcpy( newdata, data, n ) ;
		}
	}
	else {
		if( bytes == BYTEBYTES ) {
			return data ;
		}
		newdata = data ;
	}
	
	for( i = 0 ; i < n ; i += 1 ) {
		switch( bytes ) {
			case BYTEBYTES :
				break ;
			case HWORDBYTES :
				ubig = ( ( unsigned short * )data )[ i ] ;
				( ( unsigned short * )newdata )[ i ] = ( unsigned short )( ( ( ubig >> 8 ) & 0xFF ) + ( ( ubig & 0xFF ) << 8 ) ) ;
				break ;
			case WORDBYTES :
				BYTEREVERSEWORD( ( ( unsigned int * )data )[ i ], ( ( unsigned int * )newdata )[ i ] ) ;
				break ;
			default :
				break ;
		}
	}
	
	return newdata ;
}

