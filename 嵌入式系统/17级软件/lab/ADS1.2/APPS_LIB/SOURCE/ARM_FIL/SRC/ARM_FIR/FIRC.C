/*
 * Finite Impulse Response filter C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>

#include "firc.h"

/**** FIRC **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, FIR filter the data using
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
unsigned int FIRC( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs )
{
	unsigned int counter ;
	
	if( ( !outputs ) || ( !inputs ) || ( !coeffs ) ) {
		fprintf( stderr, "[FIRC] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	for( counter = 0 ; counter < nInputs ; counter += 1 ) {
		outputs[ counter ] = OneFIRC( inputs, nInputs, counter, coeffs, nCoeffs, 1 ) ;
	}
	
	return 1 ;
}

/**** OneFIRC ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, FIR filter the current
 * input data value based on the other input values and coefficients and return the 
 * filtered value calculated
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the data inputs
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   inputOffset
 *   - an offset into the array inputs to the current input element for filtering
 *     must be in the range 0 to nInputs-1
 *   coeffs
 *   - an array referencing the coefficients to be used during the filter
 *   nCoeffs
 *   - the number of coefficients referenced by the array coeffs
 *   forward
 *   - indicator for direction of filter
 *     0 = filter works backward through the input array taking previous inputs
 *     1 = filter works forward through input array taking forthcoming inputs
 * Return Values
 * ------ ------
 *     int - the calculated FIR filter data
 *     0   - if some error occurred, no explicit test possible since FIR value may be 0
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int OneFIRC( int inputs[ ], unsigned int nInputs, unsigned int inputOffset, int coeffs[ ], unsigned int nCoeffs, unsigned int forward )
{
	int 			sum = 0 ;
	unsigned int	counter ;
	
	if( ( !inputs ) || ( !coeffs ) || ( inputOffset > nInputs - 1 ) ) {
		fprintf( stderr, "[OneFIRC] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	for( counter = 0 ; counter < nCoeffs ; counter += 1 ) {
		if( forward ) {
			if( inputOffset + counter > nInputs - 1 ) {
				break ;
			}
			sum += inputs[ inputOffset + counter ] * coeffs[ counter ] ;
		}
		else {
			if( ( ( int )inputOffset - ( int )counter ) < 0 ) {
				break ;
			}
			sum += inputs[ inputOffset - counter ] * coeffs[ counter ] ;
		}
	}
	
	return sum ;
}

