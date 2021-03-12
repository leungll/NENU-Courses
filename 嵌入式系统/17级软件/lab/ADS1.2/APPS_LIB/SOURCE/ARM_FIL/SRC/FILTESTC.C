/*
 * Filter test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdlib.h>

#include "firc.h"
#include "firs.h"
#include "iirc.h"
#include "iirs.h"
#include "lmsc.h"
#include "lmss.h"

#include "filtestc.h"

#include "bitutilc.h"
#include "custredc.h"
#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define FILTER_OPTIONS	6

static Boolean Filter( unsigned int option ) ;
static void Menu( unsigned int numberOptions ) ;
static int *PerformFIR( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm ) ;
static int *PerformIIR( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm ) ;
static Boolean PerformIIRARM( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs ) ;
static int *PerformLMS( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm ) ;
static Boolean PerformLMSARM( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, int desired[ ], unsigned int adaptRate ) ;

/**** fil_main **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * initialise the application then loop whilst the user is still working
 *
 * Return Values
 * ------ ------
 *     0 - application terminated correctly
 *     1 - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int fil_main( int argc, char **argv )
{
	unsigned int	option ;
	char			newStdIn[ ] = "stdin" ;
	char			newStdOut[ ] = "stdout" ;
	char			newStdErr[ ] = "stderr" ;
	unsigned int	stdio = 0 ;
	
	if( ChangeStdIO( &argc, &argv, newStdIn, stdin ) == STDINID ) {
		stdio |= ( 1 << STDINID ) ;
	}
	if( ChangeStdIO( &argc, &argv, newStdOut, stdout ) == STDOUTID ) {
		stdio |= ( 1 << STDOUTID ) ;
	}
	if( ChangeStdIO( &argc, &argv, newStdErr, stderr ) == STDERRID ) {
		stdio |= ( 1 << STDERRID ) ;
	}
	
	printf( "Program to perform filtering.\n\n" ) ;
	
	printf( "This application provides access to the filters with input data\n" ) ;
	printf( "in hexadecimal format, each data item being 16-bit with fixed point precision\n" ) ;
	printf( "and the decimal point being between bits 13 and 14 so that dividing the hexadecimal\n" ) ;
	printf( "number by (1 << 14) provides the actual decimal value.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( FILTER_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		Filter( option ) ;
	}
	
	/* redirection based on trying to open files that don't exist do using defaults */
	if( stdio & ( 1 << STDINID ) ) {
		ResetStdIO( stdin ) ;
	}
	if( stdio & ( 1 << STDOUTID ) ) {
		ResetStdIO( stdout ) ;
	}
	if( stdio & ( 1 << STDERRID ) ) {
		ResetStdIO( stderr ) ;
	}
	
	return 0 ;
}

/**** Filter ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read files of 16-bit integer data given by the user for inputs and coefficients,
 * perform the required filter using ARM or C routines, based on value of parameter,
 * and write the new values to a file given by the user
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 6 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines which of ARM or C routines
 *     are used for the encoding and decoding and what filter to perform
 * Return Values
 * ------ ------
 *     TRUE  - the filtering process was successful and data written
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Filter( unsigned int option )
{
	int				*inputs ;
	unsigned int	nInputs ;
	int				*coeffs ;
	unsigned int 	nCoeffs ;
	int				*outputs ;
	
	if( ( inputs = ( int * )GetData( WORDBYTES, "input", &nInputs ) ) == NULL ) {
		return FALSE ;
	}
	SIGNEXTENDARRAY( inputs, nInputs, 16 ) ;

	if( ( coeffs = ( int * )GetData( WORDBYTES, "coefficient", &nCoeffs ) ) == NULL ) {
		free( ( void * ) inputs ) ;
		return FALSE ;
	}
	SIGNEXTENDARRAY( coeffs, nCoeffs, 16 ) ;
	
	switch( option ) {
		case 1 :
		case 2 :
			outputs = PerformFIR( inputs, nInputs, coeffs, nCoeffs, ( Boolean )( ( option == 1 ) ? TRUE : FALSE ) ) ;
			break ;
		case 3 :
		case 4 :
			outputs = PerformIIR( inputs, nInputs, coeffs, nCoeffs, ( Boolean )( ( option == 3 ) ? TRUE : FALSE ) ) ;
			break ;
		case 5 :
		case 6 :
			outputs = PerformLMS( inputs, nInputs, coeffs, nCoeffs, ( Boolean )( ( option == 5 ) ? TRUE : FALSE ) ) ;
			break ;
		case 0 :
		default :
			free( ( void * ) inputs ) ;
			free( ( void * ) coeffs ) ;
			return TRUE ;	/* don't return error, just assume ok */
	}
	
	free( ( void * ) inputs ) ;
	if( !outputs ) {
		free( ( void * ) coeffs ) ;
		return FALSE ;
	}
	
	REMOVESIGNEXTENDARRAY( outputs, nInputs, 16 ) ;
	SaveData( outputs, nInputs, WORDBYTES, 0, "output" ) ;
	free( ( void * ) outputs ) ;
	
	switch( option ) {
		case 5 :
		case 6 :
			REMOVESIGNEXTENDARRAY( coeffs, nCoeffs, 16 ) ;
			SaveData( coeffs, nCoeffs, WORDBYTES, 0, "modified coefficient" ) ;
			break ;
		default :
			break ;
	}
	
	free( ( void * ) coeffs ) ;
	
	return TRUE ;
}

/**** Menu **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the menu of options to the screen (defined in standard way for NextTask 
 * function and will be called by NextTask)
 *
 * Inputs
 * ------
 *   numberOptions
 *   - the number of menu options that should be printed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void Menu( unsigned int numberOptions )
{
	if( numberOptions == FILTER_OPTIONS ) {
		printf( " 1. FIR ARM Assembler Filter\n" ) ;
		printf( " 2. FIR C Filter\n" ) ;
		printf( " 3. IIR ARM Assembler Filter\n" ) ;
		printf( " 4. IIR C Filter\n" ) ;
		printf( " 5. LMS ARM Assembler Filter\n" ) ;
		printf( " 6. LMS C Filter\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PerformFIR ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, FIR filter the data using
 * either ARM or C routines and return the filtered values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the data inputs
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   coeffs
 *   - an array referencing the coefficients to be used during the filter
 *   nCoeffs
 *   - the number of coefficients referenced by the array coeffs
 *   arm
 *   - 1 : use ARM Assembler routines to perform the filter
 *     0 : use C routines to perform the filter
 * Return Values
 * ------ ------
 *     int * - an array of filtered values with nInputs data points
 *     NULL  - some error occurred (memory allocation failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of integers
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int *PerformFIR( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm )
{
	int				*outputs ;
	unsigned int	outCounter ;
	
	if( ( !inputs ) || ( !coeffs ) ) {
		return NULL ;
	}
	
	if( ( outputs = ( int * )calloc( nInputs, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	if( arm ) {
		printf( "ARM " ) ;
	}
	else {
		printf( "C " ) ;
	}
	printf( "FIR filtering data...\n\n" ) ;
	
	if( arm ) {
		s_blk_fir_rhs( outputs, inputs, coeffs, nInputs, nCoeffs, nInputs ) ;
	}
	else {
		FIRC( outputs, inputs, nInputs, coeffs, nCoeffs ) ;
	}
	
	/* does not know sample data is 14-bit fixed point thus requires correcting */
	for( outCounter = 0 ; outCounter < nInputs ; outCounter += 1 ) {
		outputs[ outCounter ] = outputs[ outCounter ]/( 1 << 14 ) ;
	}
	
	printf( "Data FIR filtered.\n\n" ) ;
	
	return outputs ;
}

/**** PerformIIR ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, IIR filter the data using
 * either ARM or C routines and return the filtered values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the data inputs
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   coeffs
 *   - an array referencing the coefficients to be used during the filter
 *   nCoeffs
 *   - the number of coefficients referenced by the array coeffs
 *   arm
 *   - 1 : use ARM Assembler routines to perform the filter
 *     0 : use C routines to perform the filter
 * Return Values
 * ------ ------
 *     int * - an array of filtered values with nInputs data points
 *     NULL  - some error occurred (memory allocation failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of integers
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int *PerformIIR( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm )
{
	int	*outputs ;

	if( ( outputs = ( int * )calloc( nInputs, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	if( arm ) {
		printf( "ARM " ) ;
	}
	else {
		printf( "C " ) ;
	}
	printf( "IIR filtering data...\n\n" ) ;
	
	if( arm ) {
		if( !( PerformIIRARM( outputs, inputs, nInputs, coeffs, nCoeffs ) ) ) {
			free( ( void * ) outputs ) ;
			return NULL ;
		}
	}
	else {
		IIRC( outputs, inputs, nInputs, coeffs, nCoeffs ) ;
	}
	
	printf( "Data IIR filtered.\n\n" ) ;
	
	return outputs ;
}

/**** PerformIIRARM *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, IIR filter the data using
 * ARM routines and return the filtered values in the array given
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
 *     undefined if FALSE returned (see Return Values)
 * Return Values
 * ------ ------
 *     TRUE  - the array outputs contains the filtered data
 *     FALSE - some error occurred (memory allocation?) and outputs is undefined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformIIRARM( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs )
{
	unsigned int	nBiquads = nCoeffs / 4 ;
	int				*coeffsStates ;
	
	if( ( coeffsStates = ( int * )calloc( ( nCoeffs*3 )/2, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for coefficients and states, aborting.\n\n" ) ;
		return FALSE ;
	}

	
	IIR_PowerUp( coeffsStates, coeffs, nBiquads ) ;
	IIR( outputs, inputs, nInputs, nBiquads, coeffsStates ) ;
	
	free( ( void * ) coeffsStates ) ;
	
	return TRUE ;
}

/**** PerformLMS ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values and an array of coefficients, read in a set of desired
 * values from a file given by the user, get an adaption rate, LMS filter the data using
 * either ARM or C routines and return the filtered values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the data inputs
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   coeffs
 *   - an array referencing the coefficients to be used during the filter
 *   nCoeffs
 *   - the number of coefficients referenced by the array coeffs
 *   arm
 *   - 1 : use ARM Assembler routines to perform the filter
 *     0 : use C routines to perform the filter
 * Return Values
 * ------ ------
 *     int * - an array of filtered values with nInputs data points
 *     NULL  - some error occurred (memory allocation failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of integers
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int *PerformLMS( int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, Boolean arm )
{
	int 			*desired ;
	unsigned int	nDes ;
	double			adaptRate ;
	int				*outputs ;
	
	if( ( desired = ( int * )GetData( WORDBYTES, "desired", &nDes ) ) == NULL ) {
		return NULL ;
	}
	SIGNEXTENDARRAY( desired, nDes, 16 ) ;
	
	if( nDes != nInputs ) {
		fprintf( stderr, "The number of desired inputs != number of data inputs, aborting.\n\n" ) ;
		free( ( void * ) desired ) ;
		return NULL ;
	}
	
    printf( "Please choose an adaption rate for the filter.\n\n" ) ;
    
    printf( "The larger the adapation rate, the faster the filter will respond,\n" ) ;
    printf( "but the more likely it will also become unstable.\n\n" ) ;
    
    do {
    	printf( "Give an adaption rate, ar, such that 0 < ar < 1: " ) ;
    } while( ( ( adaptRate = ReadDouble( ) ) <= 0.0 ) || ( adaptRate >= 1.0 ) ) ;

    printf( "The adaption rate given is '%lf'\n\n", adaptRate ) ;
    
    /* fix-point the adaption rate */
    adaptRate = adaptRate * ( 1 << 14 ) ;
    
   	if( ( outputs = ( int * )calloc( nInputs, sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		free( ( void * ) desired ) ;
		return NULL ;
	}

	if( arm ) {
		printf( "ARM " ) ;
	}
	else {
		printf( "C " ) ;
	}
	printf( "LMS filtering data...\n\n" ) ;

    if( arm ) {
    	if( !( PerformLMSARM( outputs, inputs, nInputs, coeffs, nCoeffs, desired, ( unsigned int )adaptRate ) ) ) {
    		free( ( void * ) desired ) ;
    		free( ( void * ) outputs ) ;
    		return NULL ;
    	}
    }
    else {
    	LMSC( outputs, inputs, nInputs, coeffs, nCoeffs, desired, ( unsigned int )adaptRate ) ;
    }
    
	printf( "Data LMS filtered.\n\n" ) ;
	
	free( ( void * ) desired ) ;
	
	return outputs ;
}

/**** PerformLMSARM *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, an array of coefficients, an array of desired values
 * and an adaption rate, LMS filter the data using ARM routines and return the 
 * filtered values in the array given and update the coefficient array with the
 * modified values
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
 *     undefined if FALSE returned (see Return Values)
 *   coeffs
 *   - the updated coefficient values after the filtering has adapted them
 *     the original coefficinet values if FALSE returned (see Return Values)
 * Return Values
 * ------ ------
 *     TRUE  - the array outputs contains the filtered data, coeffs updated
 *     FALSE - some error occurred (memory allocation?) and outputs is undefined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformLMSARM( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs, int desired[ ], unsigned int adaptRate )
{
	int	*coeffsStates ;

	if( ( coeffsStates = ( int * )calloc( ( nCoeffs*2 ), sizeof( int ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for coefficients and states, aborting.\n\n" ) ;
		return FALSE ;
	}
	
	LMS_PowerUp( coeffsStates, coeffs, nCoeffs ) ;
	LMS( outputs, inputs, nInputs, desired, adaptRate, nCoeffs, coeffsStates ) ;
	LMS_PowerDown( coeffs, coeffsStates, nCoeffs ) ;
	
	free( ( void * ) coeffsStates ) ;

	return TRUE ;
}
	
