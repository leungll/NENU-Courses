/*
 * Fast Fourier Transform windowing
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "windowc.h"

static unsigned int Window( int outputs[ ], int inputs[ ], unsigned int nDataPoints, unsigned int windowCoeff ) ;

/**** GenerateWindow ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a set of windowing data coefficients for either a Hamming or Hanning 
 * window with the required number of points in the window as given
 *
 * Inputs
 * ------
 *   windowCoeff
 *   - a fixed-point (after bit 14) coefficient that determines window
 *     HAMMING : perform a Hamming window (0x1D70)
 *     HANNING : perform a Hanning window (0x2000)
 *     int     : anything else generates an error
 *   nDataPoints
 *   - the number of points that should be in the window
 * Return Values
 * ------ ------
 *     int * - an array that contains the windowing data with nDataPoints data points
 *             the data is returned as fixed-point (after bit 14) sign-extended
 *     NULL  - some error occurred (memory allocation?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array, if not NULL
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int *GenerateWindow( unsigned int windowCoeff, unsigned int nDataPoints )
{
	int	*window ;
	int	element ;
	
	if( ( windowCoeff != HAMMING ) && ( windowCoeff != HANNING ) || ( nDataPoints == 0 ) ) {
		fprintf( stderr, "[GenerateWindow] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( window = ( int * )calloc( nDataPoints, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Unable to create window, aborting.\n\n" ) ;
		return NULL ;
	}
	
	for( element = nDataPoints - 1 ; element >= 0 ; element -= 1 ) {
		window[ element ] = ( 0x4000 - windowCoeff ) - windowCoeff * ( int )cos( ( 2.0 * PI * ( double )element )/( double )( ( int )( nDataPoints - 1 ) ) ) ;
		if( window[ element ] & ( 1 << 15 ) ) {
			window[ element ] |= 0xFFFF0000 ;
			/* sign extend data value */
		}
	}
	
	return window ;
}

/**** HammingWindow *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform a Hamming window on the data given
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array of integers to hold the result of the windowing which
 *     should contain at least as many entries as there are in inputs
 *   inputs
 *   - the array of integers that are to be windowed
 *   nDataPoints
 *   - the number of points that are in the array inputs and will be in array outputs
 * Outputs
 * -------
 *   outputs
 *   - an array that contains the windowed data, containing as many entries
 *     as inputs = nDataPoints
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the windowing was completed successfully, outputs is valid
 *     0 - the windowing failed, outputs is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int HammingWindow( int outputs[ ], int inputs[ ], unsigned int nDataPoints )
{
	return Window( outputs, inputs, nDataPoints, HAMMING ) ;
}

/**** HanningWindow *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform a Hanning window on the data given
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array of integers to hold the result of the windowing which
 *     should contain at least as many entries as there are in inputs
 *   inputs
 *   - the array of integers that are to be windowed
 *   nDataPoints
 *   - the number of points that are in the array inputs and will be in array outputs
 * Outputs
 * -------
 *   outputs
 *   - an array that contains the windowed data, containing as many entries
 *     as inputs = nDataPoints
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the windowing was completed successfully, outputs is valid
 *     0 - the windowing failed, outputs is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int HanningWindow( int outputs[ ], int inputs[ ], unsigned int nDataPoints )
{
	return Window( outputs, inputs, nDataPoints, HANNING ) ;
}

/**** Window ************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform the required window (Hamming or Hanning) on the data given
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array of integers to hold the result of the windowing which
 *     should contain at least as many entries as there are in inputs
 *   inputs
 *   - the array of integers that are to be windowed
 *   nDataPoints
 *   - the number of points that are in the array inputs and will be in array outputs
 *   windowCoeff
 *   - a fixed-point (after bit 14) coefficient that determines window
 *     HAMMING : perform a Hamming window (0x1D70)
 *     HANNING : perform a Hanning window (0x2000)
 *     int     : anything else generates an error
 * Outputs
 * -------
 *   outputs
 *   - an array that contains the windowed data, containing as many entries
 *     as inputs = nDataPoints
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the windowing was completed successfully, outputs is valid
 *     0 - the windowing failed, outputs is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int Window( int outputs[ ], int inputs[ ], unsigned int nDataPoints, unsigned int windowCoeff )
{
	int	*window ;
	int	element ;
	
	if( ( !outputs ) || ( !inputs ) ) {
		return 0 ;
	}
	
	if( ( window = GenerateWindow( windowCoeff, nDataPoints ) ) == NULL ) {
		return 0 ;
	}
	
	for( element = nDataPoints - 1 ; element >= 0 ; element -= 1 ) {
		outputs[ element ] = ( inputs[ element ] * window[ element ] ) >> 14 ;
	}
	
	return 1 ;
}

