/*
 * Least Mean Square filter C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>

#include "lmsc.h"

#include "firc.h"

/**** LMSC **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, an array of coefficients, an array of desired values
 * and an adaption rate, LMS filter the data using C routines and return the 
 * filtered values in the array given
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
 *   desired
 *   - an array referencing at least nInputs values that represent the desired outputs
 *     that the filter is based on
 *   adaptRate
 *   - the adaption rate for the filter between 0 and 1 that governs the speed of
 *     learning
 *     actual value is 14-bit fixed point extended to allow for floating point rate
 * Outputs
 * -------
 *   outputs
 *   - the result of the filtering, with nInputs filtered data points
 *     undefined if 0 returned (see Return Values)
 *   coeffs
 *   - the updated coefficient values after the filtering has adapted them
 *     the original coefficinet values if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the array outputs contains the filtered data, coeffs updated
 *     0 - some error occurred and outputs is undefined, coeffs unadjusted
 *
 * coeffs will be updated with the modified coefficient values after filtering
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int LMSC( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, int desired[ ], unsigned int adaptRate )
{
	int				error = 0 ;
	unsigned int	dataCounter ;
	unsigned int	coeffCounter ;
		
	if( ( !outputs ) || ( !inputs ) || ( !coeffs ) || ( !desired ) ) {
		fprintf( stderr, "[LMSC] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}

	for( dataCounter = 0 ; dataCounter < nInputs ; dataCounter += 1 ) {
		for( coeffCounter = 0 ; coeffCounter < nCoeffs ; coeffCounter += 1 ) {
			if( ( ( int )dataCounter - 1 - ( int )coeffCounter ) < 0 ) {
				break ;
			}
			coeffs[ coeffCounter ] += ( int )( ( ( double )( adaptRate )/( 1 << 14 ) )*( ( double )( error )/( 1 << 14 ) )*( ( double )( inputs[ dataCounter - 1 - coeffCounter ] ) ) ) ;
		}
		outputs[ dataCounter ] = ( OneFIRC( inputs, nInputs, dataCounter, coeffs, nCoeffs, 0 ) >> 14 ) ;
		error = desired[ dataCounter ] - outputs[ dataCounter ] ;
	}
	
	return 1 ;
}

