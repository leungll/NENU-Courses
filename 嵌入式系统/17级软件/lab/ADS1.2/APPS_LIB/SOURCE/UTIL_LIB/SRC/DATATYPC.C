/*
 * Utility Library: Data Type
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "datatypc.h"

/**** CreateComplexFromInt **********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create an array of complex numbers from a given array of integers with the real
 * and imaginary parts interleaved and thus the array of complex number is half 
 * the size of the given integer array
 *
 * Inputs
 * ------
 *   dataInt
 *   - the array of interleaved real and imaginary integers that are to make up the
 *     the complex array
 *   size
 *   - the number of data points in the given array
 *     this is not the number of complex values, but the number of real and imaginary
 *     values in the array
 * Outputs
 * -------
 *   size
 *   - the number of complex values in the returned array
 *     the number of entries in the original integer array if some error (NULL returned)
 * Return Values
 * ------ ------
 *     Complex * - the array of complex numbers created
 *     NULL      - some error occurred (could not create array?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned complex array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
Complex *CreateComplexFromInt( int dataInt[ ], unsigned int *size )
{
	Complex			*dataComplex ;
	unsigned int	counter ;
	
	if( ( dataComplex = ( Complex * )calloc( *size/2, sizeof( Complex ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create complex data array (for conversion from integer), aborting.\n\n" ) ;
		return NULL ;
	}
	
	for( counter = 0 ; counter < *size ; counter += 2 ) {
		dataComplex[ counter/2 ].r = dataInt[ counter ] ;
		dataComplex[ counter/2 ].i = dataInt[ counter + 1 ] ;
	}
	*size /= 2 ;
	
	return dataComplex ;
}

/**** CreateIntFromComplex **********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create an array of integer numbers from a given array of complex numbers, the
 * created array having the the real and imaginary parts interleaved and thus 
 * the array of integers is twice the size of the given complex array
 *
 * Inputs
 * ------
 *   dataComplex
 *   - the array of complex integers that are to be interleaved for the complex array
 *   size
 *   - the number of data points in the given array
 *     this is the number of complex values and not the number of real and imaginary
 *     values in the array
 * Outputs
 * -------
 *   size
 *   - the number of integers in the returned array
 *     the number of entries in the original complex array if some error (NULL returned)
 * Return Values
 * ------ ------
 *     int * - the array of integers created
 *     NULL  - some error occurred (could not create array?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned integer array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int *CreateIntFromComplex( Complex dataComplex[ ], unsigned int *size )
{
	int				*dataInt ;
	unsigned int	counter ;
	
	if( ( dataInt = ( int * )calloc( *size*2, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create integer array (for conversion from complex), aborting.\n\n" ) ;
		return NULL ;
	}
	
	*size *= 2 ;
	for( counter = 0 ; counter < *size ; counter += 2 ) {
		dataInt[ counter ] = dataComplex[ counter/2 ].r ;
		dataInt[ counter + 1 ] = dataComplex[ counter/2 ].i ;
	}
	
	return dataInt ;
}

