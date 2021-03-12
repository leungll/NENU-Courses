/*
 * Infinite Impulse Response filter C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "iirc.h"

/**** IIRC **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, IIR filter the data using
 * C routines and return the filtered values in the array given
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array that references at least nInputs locations
 *   inputs
 *   - an array referencing the data inputs
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   coeffs
 *   - an array referencing the coefficients to be used during the filter
 *   nCoeffs
 *   - the number of coefficients referenced by the array coeffs
 * Outputs
 * -------
 *   outputs
 *   - the result of the filtering, with nInputs filtered data points
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the array outputs contains the filtered data
 *     0 - some error occurred and outputs is undefined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int IIRC( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs )
{
	unsigned int	counter ;
	unsigned int	bCounter ;
	int 			w ;

	int nBiquads = nCoeffs / 4;
	int *wh; 	/* IIR history */
	
	if( ( !outputs ) || ( !inputs ) || ( !coeffs ) ) {
		fprintf( stderr, "[IIRC] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}

	wh = ( int * )calloc( nBiquads * 2,  sizeof( int ) );

        if (wh==NULL)
	{
		fprintf( stderr, "[IIRC] Failure to create IIR history.\n\n" ) ;
	}

	for( bCounter = 0 ; bCounter < nBiquads ; bCounter ++ ) {
		wh[ bCounter * 2     ] = 0;
		wh[ bCounter * 2 + 1 ] = 0;
		}

	for( counter = 0 ; counter < nInputs ; counter += 1 ) {
		outputs[ counter ] = inputs[ counter ] ;
		for( bCounter = 0 ; bCounter < nBiquads ; bCounter ++ ) {
		/* increment a biquad at a time */
			w = outputs[ counter ] + ( ( coeffs[ bCounter*4 + 2 ]*wh[ bCounter * 2     ] ) >> 14 ) +
			                         ( ( coeffs[ bCounter*4 + 3 ]*wh[ bCounter * 2 + 1 ] ) >> 14 ) ;
			outputs[ counter ] = w + ( ( coeffs[ bCounter*4 + 0 ]*wh[ bCounter * 2     ] ) >> 14 ) +
			                        ( ( coeffs[ bCounter*4 + 1 ]*wh[ bCounter * 2 + 1 ] ) >> 14 ) ;
			wh[ bCounter * 2 + 1 ] = wh[ bCounter * 2 ] ;
			wh[ bCounter * 2     ] = w ;
		}
	}
	
	free(wh);

	return 1 ;
}

