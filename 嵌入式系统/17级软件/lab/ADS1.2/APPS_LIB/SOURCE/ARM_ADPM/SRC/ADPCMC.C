/*
 * Adaptive Differential Pulse Code Modulation C tests
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "adpcmc.h"

static const int indexTable[ 16 ] = {
	-1, -1, -1, -1, 2, 4, 6, 8,
	-1, -1, -1, -1, 2, 4, 6, 8
} ;
/* define an array of index adjustments to the step index value */

#define	MAXSTEPINDEX	88
/* define the maximum value to access the top element of stepSizeTable below */

static const int stepSizeTable[ MAXSTEPINDEX + 1 ] = {
	    7,     8,     9,    10,    11,    12,    13,    14,    16,    17,
	   19,    21,    23,    25,    28,    31,    34,    37,    41,    45,
	   50,    55,    60,    66,    73,    80,    88,    97,   107,   118,
	  130,   143,   157,   173,   190,   209,   230,   253,   279,   307,
	  337,   371,   408,   449,   494,   544,   598,   658,   724,   796,
	  876,   963,  1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
	 2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,
	 5894,  6484,  7132,  7845,  8630,  9493, 10442, 11487, 12635, 13899,
	15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
} ;
/* define an array containing the step sizes that are available */

/**** DecodeADPCMC ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * decode the current adpcm value to its (approximate) pcm value given a required
 * internal structure
 *
 * Inputs
 * ------
 *   adpcmSample
 *   - the adpcm sample to decode based on the previous decoded sample
 *     the sample should be unsigned 4-bit and thus be a value between 0 and 15 only 
 *     with the top bit indicating the sign
 *   decodeStatePtr
 *   - a pointer to an ADPCMState structure that contains the index to lookup
 *     in the step size table and the prediction for the current decoded sample
 *     (which is equivalent to the previous decoded sample)
 *     for the first call in a sequence the stepIndex and prediction should be 0
 *     thereafter they should be maintained between function calls with the values
 *     that are placed in the structure during each function call
 * Outputs
 * -------
 *   decodeStatePtr
 *   - the updated state structure containing the values necessary for the next 
 *     instance of the function call
 * Return Values
 * ------ ------
 *     int	- the adpcm sample decoded to its (approximate) pcm value
 *
 * Notes
 * -----
 * if the structure is not intialised for the first function call in a sequence
 * or is not maintained with the values returned between function calls the result
 * will not be correct
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int DecodeADPCMC( int adpcmSample, ADPCMStatePtr decodeStatePtr )
{
	int	step ;
	int	delta ;
	int	predictionAdjustment ;
	
	if( ( adpcmSample < 0 ) || ( adpcmSample > 15 ) ) {
		fprintf( stderr, "[DecodeADPCMC] Error in ADPCM sample, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	if( !decodeStatePtr ) {
		fprintf( stderr, "[DecodeADPCMC] Error in ADPCMState, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
		
	step = stepSizeTable[ decodeStatePtr->stepIndex ] ;
	
	delta = adpcmSample ;

	decodeStatePtr->stepIndex += indexTable[ delta ] ;
	/* range check the stepIndex */
	if( decodeStatePtr->stepIndex < 0 ) {
		decodeStatePtr->stepIndex = 0 ;
	}
	else if( decodeStatePtr->stepIndex > MAXSTEPINDEX ) {
		decodeStatePtr->stepIndex = MAXSTEPINDEX ;
	}

	/* remove sign from delta - pull to 3-bit */
	if( delta > 7 ) {
		delta -= 8 ;
	}
	
	predictionAdjustment = ( 2*delta + 1 )* step/8 ;
	if( adpcmSample > 7 ) {
		decodeStatePtr->prediction -= predictionAdjustment ;
	}
	else {
		decodeStatePtr->prediction += predictionAdjustment ;
	}
	
	/* range check the prediction so that fits in number of bits */
	if( decodeStatePtr->prediction > ( 1 << ( MAXBITS - 1 ) ) - 1 ) {
		decodeStatePtr->prediction = ( 1 << ( MAXBITS - 1 ) ) - 1 ;
	}
	else if( decodeStatePtr->prediction < -( 1 << ( MAXBITS - 1 ) ) ) {
		decodeStatePtr->prediction = -( 1 << ( MAXBITS - 1 ) ) ;
	}

	return decodeStatePtr->prediction ;
}

/**** EncodeADPCMC ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * encode the current pcm value to its adpcm value given the previously 
 * encoded adpcm sample and a required internal structure
 *
 * Inputs
 * ------
 *   pcmSample
 *   - the pcm sample to encode based on the previous encoded adpcm sample
 *     the sample should be 16-bit linear PCM
 *   previousADPCMEncoded
 *   - the previously encoded adpcm sample
 *     this value should be exactly that returned from the previous call to this
 *     function or 0 if calling the function for the first time
 *   statePtr
 *   - a pointer to an ADPCMState structure that contains the index to lookup
 *     in the step size table and the prediction for decoding the given
 *     previousADPCMEncoded sample 
 *     for the first call in a sequence the stepIndex and prediction should be 0
 *     thereafter they should be maintained between function calls with the values
 *     that are placed in the structure during each function call
 * Outputs
 * -------
 *   statePtr
 *   - the updated state structure containing the values necessary for the next 
 *     instance of the function call
 * Return Values
 * ------ ------
 *     int	- the pcm sample encoded to its adpcm value
 *
 * Notes
 * -----
 * if the structure is not intialised for the first function call in a sequence
 * or is not maintained with the values returned between function calls the result
 * will not be correct
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int EncodeADPCMC( int pcmSample, int previousADPCMEncoded, ADPCMStatePtr statePtr )
{
	int	step ;
	int	difference ;
	int	delta ;
	
	difference = pcmSample - DecodeADPCMC( previousADPCMEncoded, statePtr ) ;
	/* decode the previously encoded adpcm sample to get prediction for this sample */

	step = stepSizeTable[ statePtr->stepIndex ] ;
	
	delta = abs( difference ) * 4 / step ;
	
	/* range check delta */
	if( delta > 7 ) {
		delta = 7 ;
	}
	
	/* include the sign into the top bit of delta */
	if( difference < 0 ) {
		delta += 8 ;
	}	

	return delta ;
}

