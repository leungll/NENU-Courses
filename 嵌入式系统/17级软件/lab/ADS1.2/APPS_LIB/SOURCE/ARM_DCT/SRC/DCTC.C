/*
 * Discrete Cosine Transform C
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <math.h>
#include <stdio.h>

#include "dctc.h"

/**** DCTCosArrayInit ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a cosine lookup table that is required by the real DCT routines given in
 * this file
 *
 * Inputs
 * ------
 *   dctCosArray
 *   - an initialised DCTCosArray to hold the cosine table values which must hold
 *     at least 8*8 doubles
 * Outputs
 * -------
 *   dctCosArray
 *   - a 2D cosine lookup table containing 8*8 entries that is suitable for the passing
 *     to the real DCT routines
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the first 8 rows, 8 columns of dctCosArray contain the cosine lookup table
 *     0 - some error occurred, dctCosArray is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int DCTCosArrayInit( DCTCosArray dctCosArray )
{
	unsigned int	x, y ;
	double			val ;
    double			PIdiv16 = PI/16.0 ;
    
    if( !dctCosArray ) {
		fprintf( stderr, "[DCTCosArrayInit] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
    	return 0 ;
    }

    for( y = 0; y < 8; y += 1 )	{
        for( x = 0; x < 8; x += 1 ) {
        	val = cos( ( ( double )( ( unsigned int )( ( 2*y + 1 ) * x ) ) ) * PIdiv16 ) ;

            if( x == 0 ) {
            	val /= sqrt( 2.0 ) ;
            }
             
            dctCosArray[ y ][ x ] = val * 0.5 ;
        }
	}
	
	return 1 ;
}

/**** FDCTReal **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * a procedure to calculate the forward DCT for a given block of data given a cosine
 * lookup table
 *
 * Inputs
 * ------
 *   dctCosArray
 *   - an 8*8 DCTCosArray that should contain the cosine lookup table that is required
 *     during the DCT operations (as created by DCTCosArrayInit)
 *   dctIn
 *   - a single DCTArray that contains the input data that is to be forward DCT'd
 *   dctOut
 *   - an initialised DCTArray that can hold the output data, the result of the forward
 *     DCT
 * Outputs
 * -------
 *   dctOut
 *   - a DCTArray contains the output from the forward DCT of the data in dctIn
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - forward DCT was successful, dctOut is valid
 *     0 - some error occurred, dctOut is not valid
 *
 * Notes
 * -----
 * if the cosine lookup table is not created by DCTCosArrayInit the results of the
 * coding are undefined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int FDCTReal( DCTCosArray dctCosArray, DCTArray dctIn, DCTArray dctOut )
{
	unsigned int	x, y ;
	unsigned int	u, v ;
	double			sum ;

	if( ( !dctCosArray ) || ( !dctIn ) || ( !dctOut ) ) {
		fprintf( stderr, "[FDCTReal] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
    for( v = 0; v < 8; v += 1 ) {
        for( u = 0; u < 8; u += 1 ) {
        	sum = 0.0 ;

            for( y = 0; y < 8; y += 1 ) {
                for( x = 0; x < 8; x += 1 ) {
                    sum += ( ( double )( ( int )( dctIn[ y ][ x ] - 128 ) ) ) * dctCosArray[ y ][ v ] * dctCosArray[ x ][ u ] ;
                }
            }
            		
            dctOut[ v ][ u ] = ( int )floor( sum + 0.5 ) ;
        }
	}
	
	return 1 ;
}

/**** FDCTReal **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * a procedure to calculate the inverse DCT for a given block of data given a cosine
 * lookup table
 *
 * Inputs
 * ------
 *   dctCosArray
 *   - an 8*8 DCTCosArray that should contain the cosine lookup table that is required
 *     during the DCT operations (as created by DCTCosArrayInit)
 *   dctIn
 *   - a single DCTArray that contains the input data that is to be inverse DCT'd
 *   dctOut
 *   - an initialised DCTArray that can hold the output data, the result of the inverse
 *     DCT
 * Outputs
 * -------
 *   dctOut
 *   - a DCTArray contains the output from the inverse DCT of the data in dctIn
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - inverse DCT was successful, dctOut is valid
 *     0 - some error occurred, dctOut is not valid
 *
 * Notes
 * -----
 * if the cosine lookup table is not created by DCTCosArrayInit the results of the
 * coding are undefined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int RDCTReal( DCTCosArray dctCosArray, DCTArray dctIn, DCTArray dctOut )
{
	unsigned int	x, y ;
	unsigned int	u, v ;
	double			sum ;
	
	if( ( !dctCosArray ) || ( !dctIn ) || ( !dctOut ) ) {
		fprintf( stderr, "[RDCTReal] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
    for( y = 0; y < 8; y += 1 ) {
        for( x = 0; x < 8; x += 1 ) {
        	sum = 0.0 ;

            for( v = 0; v < 8; v += 1 ) {
                for( u = 0; u < 8; u += 1 ) {
                    sum += dctIn[ v ][ u ] * dctCosArray[ y ][ v ] * dctCosArray[ x ][ u ] ;
                }
            }
             		
            dctOut[ y ][ x ] = ( int )floor( sum + 0.5 ) + 128 ;
        }
	}
	
	return 1 ;
}
