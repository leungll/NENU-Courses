/*
 * Fast Fourier Transform C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fftc.h"

/**** FFTC **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * calculate the current output for a forward or inverse FFT on the data given 
 * using C routines where the data can be either an array of complex or real integers
 *
 * the data should have been windowed as appropriate before passing here
 *
 * Inputs
 * ------
 *   inputs
 *   - an array of either complex data or real integer data to be FFT'd
 *   nInputs
 *   - the number of data points (complex or integer) in the array inputs
 *   realOnly
 *   - 1 : the given array is real only (integers)
 *     0 : the given array is complex
 *   forward
 *   - 1 : forward FFT the given data
 *     0 : inverse FFT the given data
 *   outputCounter
 *   - the current output number being calculated (index into an output array?)
 *   output
 *   - a pointer to a Complex structure to hold the complex result of the FFT
 * Outputs
 * -------
 *   output
 *   - the complex result of the FFT
 *     output is undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - FFT performed successfully, output is valid
 *     0 - FFT failed, output is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int FFTC( void *inputs, unsigned int nInputs, unsigned int realOnly, unsigned int forward, unsigned int outputCounter, Complex *output )
{
	double			omega = 2.0 * PI /( double )nInputs ;
	double			sumr = 0 ;
	double			sumi = 0 ;
	unsigned int	counter ;
	double			costerm ;
	double			sinterm ;
	double			real ;
	double			imaginary ;
	int				*inputsInt = NULL ;
	Complex			*inputsComplex = NULL ;
	
	if( ( !output ) || ( !inputs ) ) {
		fprintf( stderr, "[FFTC] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	if( realOnly ) {
		inputsInt = ( int * )inputs ;
	}
	else {
		inputsComplex = ( Complex * )inputs ;
	}
	
	for( counter = 0 ; counter < nInputs ; counter += 1 ) {
		costerm = cos( ( double )( ( int )( counter * outputCounter ) ) * omega ) ;
		sinterm = sin( ( double )( ( int )( counter * outputCounter ) ) * omega ) ;
		if( realOnly ) {
			real = ( double )inputsInt[ counter ] ;
			imaginary = 0 ;
		}
		else {
			real = ( double )inputsComplex[ counter ].r ;
			imaginary = ( double )inputsComplex[ counter ].i ;
		}
		if( forward ) {
			sumr += real * costerm + imaginary * sinterm ;
			sumi += imaginary * costerm - real * sinterm ;
		}
		else {
			sumr += real * costerm - imaginary * sinterm ;
			sumi += imaginary * costerm + real * sinterm ;
		}
	}
	if( forward ) {
		output->r = ( int )( ( sumr )/( double )nInputs ) ;
		output->i = ( int )( ( sumi )/( double )nInputs ) ;
	}
	else {
		output->r = ( int )( sumr ) ;
		output->i = ( int )( sumi ) ;
	}
	
	return 1 ;
}

