/*
 * Adaptive Differential Pulse Code Modulation test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdlib.h>

#include "adpcmc.h"
#include "adpcms.h"

#include "adpcmtec.h"

#include "errorc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define ADPCM_OPTIONS	4

static void Menu( unsigned int numberOptions ) ;
static Boolean PerformADPCMARM( short outputs[ ], short inputs[ ], unsigned int nInputs, Boolean encode ) ;
static Boolean PerformADPCMC( short outputs[ ], short inputs[ ], unsigned int nInputs, Boolean encode ) ;
static Boolean Transform( unsigned int option ) ;

/**** adpcm_main ********************************************************************
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
int adpcm_main( int argc, char **argv )
{
	unsigned int	option ;
#ifdef	__BIG_ENDIAN
	char			newStdIn[ ] = "stdinb" ;
	char			newStdOut[ ] = "stdoutb" ;
	char			newStdErr[ ] = "stderrb" ;
#else
	char			newStdIn[ ] = "stdinl" ;
	char			newStdOut[ ] = "stdoutl" ;
	char			newStdErr[ ] = "stderrl" ;
#endif
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
	
	printf( "Program to perform ADPCM.\n\n" ) ;
	
	printf( "This application provides access to the ADPCM with 16 bit binary input data.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( ADPCM_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		Transform( option ) ;
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
	if( numberOptions == ADPCM_OPTIONS ) {
		printf( " 1. Forward ARM Assembler ADPCM followed by inverse ARM Assembler ADPCM.\n" ) ;
		printf( " 2. Forward C ADPCM followed by inverse C ADPCM.\n" ) ;
		printf( " 3. Forward ARM Assembler ADPCM followed by inverse C ADPCM.\n" ) ;
		printf( " 4. Forward C ADPCM followed by inverse ARM Assembler ADPCM.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PerformADPCM ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, either PCM or ADPCM, encode or decode them into
 * their corresponding ADPCM or PCM values respectively and return these new values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the inputs either PCM or ADPCM samples
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *   arm
 *   - true  : use ARM Assembler routines to encode or decode
 *     false : use C routines to encode or decode
 *   encode
 *   - true  : values given are PCM samples and are to be encoded
 *     false : values given are ADPCM samples and are to be decoded
 * Return Values
 * ------ ------
 *     short * - an array of samples
 *               if encode = true array contains encoded ADPCM samples
 *               if encode = false array contains decoded PCM sampled
 *     NULL    - some error occurred (memory allocation failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of shorts
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static short *PerformADPCM( short inputs[ ], unsigned int nInputs, Boolean arm, Boolean encode )
{
	short	*outputs ;
	
	if( !inputs ) {
		fprintf( stderr, "[PerformADPCM] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( outputs = ( short * )calloc( nInputs, sizeof( short ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	if( arm ) {
		printf( "ARM " ) ;
	}
	else {
		printf( "C " ) ;
	}
	if( encode ) {
		printf( "encoding PCM data...\n\n" ) ;
	}
	else {
		printf( "decoding ADPCM data...\n\n" ) ;
	}
	
	if( arm ) {
		if( !PerformADPCMARM( outputs, inputs, nInputs, encode ) ) {
			free( ( void * ) outputs ) ;
			return NULL ;
		}
	}
	else {
		if( !PerformADPCMC( outputs, inputs, nInputs, encode ) ) {
			free( ( void * ) outputs ) ;
			return NULL ;
		}
	}
	
	if( encode ) {
		printf( "PCM data encoded.\n\n" ) ;
	}
	else {
		printf( "ADPCM data decoded.\n\n" ) ;
	}

	return outputs ;
}

/**** PerformADPCMARM ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, either PCM or ADPCM, encode or decode them into
 * their corresponding ADPCM or PCM values respectively using ARM Assembler routines
 * and place the results in the given array
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array to hold the encoded or decoded values
 *     must reference at least as many entries as input samples given
 *   inputs
 *   - an array referencing the inputs either PCM or ADPCM samples
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *     also gives the number of outputs that will be produced and thus minimum size
 *     of array outputs
 *   encode
 *   - true  : values given are PCM samples and are to be encoded
 *     false : values given are ADPCM samples and are to be decoded
 * Outputs
 * -------
 *   outputs
 *   - the nInputs samples output from the function call
 *     if encode = true arary will contain ADPCM samples
 *     if encode = false array will contain PCM samples
 *     if FALSE returned, entries are undefined (see Return Values below)
 * Return Values
 * ------ ------
 *     TRUE  - the array outputs is valid and contains the required data
 *     FALSE - some error occurred, outputs does not contain valid data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformADPCMARM( short outputs[ ], short inputs[ ], unsigned int nInputs, Boolean encode )
{
	unsigned int	counter ;
	ADPCMState		state = { 0, 0 } ;
	
	if( ( !outputs ) || ( !inputs ) ) {
		fprintf( stderr, "[PerformADPCMARM] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}

	for( counter = 0 ; counter < nInputs ; counter += 1 ) {
		if( encode ) {
			outputs[ counter ] = ( short )adpcm_encode( ( int )inputs[ counter ], &state ) ;
			/* zero the top 4-bits, just to prove it is only 4-bits wide */
			outputs[ counter ] = ( short )( outputs[ counter ] & 0xF ) ;
		}
		else {
			outputs[ counter ] = ( short )adpcm_decode( ( int )inputs[ counter ], &state ) ;
		}
	}

	return TRUE ;
}

/**** PerformADPCMC *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, either PCM or ADPCM, encode or decode them into
 * their corresponding ADPCM or PCM values respectively using C routines
 * and place the results in the given array
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised array to hold the encoded or decoded values
 *     must reference at least as many entries as input samples given
 *   inputs
 *   - an array referencing the inputs either PCM or ADPCM samples
 *   nInputs
 *   - the number of data points referenced by the array inputs
 *     also gives the number of outputs that will be produced and thus minimum size
 *     of array outputs
 *   encode
 *   - true  : values given are PCM samples and are to be encoded
 *     false : values given are ADPCM samples and are to be decoded
 * Outputs
 * -------
 *   outputs
 *   - the nInputs samples output from the function call
 *     if encode = true arary will contain ADPCM samples
 *     if encode = false array will contain PCM samples
 *     if FALSE returned, entries are undefined (see Return Values below)
 * Return Values
 * ------ ------
 *     TRUE  - the array outputs is valid and contains the required data
 *     FALSE - some error occurred, outputs does not contain valid data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformADPCMC( short outputs[ ], short inputs[ ], unsigned int nInputs, Boolean encode )
{
	ADPCMState		state = { 0, 0 } ;
	unsigned int	counter ;
	int				previousADPCMEncoded ;
		
	if( ( !outputs ) || ( !inputs ) ) {
		fprintf( stderr, "[PerformADPCMC] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}

	for( counter = 0 ; counter < nInputs ; counter += 1 ) {
		if( encode ) {
			previousADPCMEncoded = 0 ;
			if( counter > 0 ) {
				previousADPCMEncoded = outputs[ counter - 1 ] ;
			}
			outputs[ counter ] = ( short )EncodeADPCMC( ( int )inputs[ counter ], previousADPCMEncoded, &state ) ;
		}
		else {
			outputs[ counter ] = ( short )DecodeADPCMC( ( int )inputs[ counter ], &state ) ;
		}
	}
	
	return TRUE ;
}

/**** Transform *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read a file of PCM data samples given by the user, encode them into ADPCM samples
 * using ARM or C routines, based on value of parameter, immediately decode them back
 * to PCM samples using ARM or C routines, again based on value of paramter and write
 * the new PCM values to a file given by the user
 *
 * information is also calculated including the number of bits in both the original
 * PCM data and encoded ADPCM data, percentage reduction and error information
 * between the original and new PCM samples which is written to a file given by the
 * user
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 4 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines which of ARM or C routines
 *     are used for the encoding and decoding
 * Return Values
 * ------ ------
 *     TRUE  - the entire transformation process was successful and data written
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Transform( unsigned int option )
{
	short			*origInputs ;
	unsigned int	nInputs ;
	Boolean			armF ;
	Boolean			armI ;
	short			*outputs = NULL ;
	short			*decodedInputs = NULL ;
	unsigned int	mse ;
	unsigned int	maxAbsErr ;
	
	printf( "Perform Adaptive Differential Pulse Code Modulation...\n\n" ) ;
	
	if( ( origInputs = ( short * )GetData( HWORDBYTES, "input", &nInputs ) ) == NULL ) {
		return FALSE ;
	}
	
	switch( option ) {
		case  1 :
			armF = TRUE ;
			armI = TRUE ;
			break ;
		case  2 :
			armF = FALSE ;
			armI = FALSE ;
			break ;
		case  3 :
			armF = TRUE ;
			armI = FALSE ;
			break ;
		case  4 :
			armF = FALSE ;
			armI = TRUE ;
			break ;
		case 0 :
		default :
			free( ( void * ) origInputs ) ;
			return TRUE ;	/* don't return error, just assume ok */
	}
	
	printf( "Number of samples is '%d'\n\n", nInputs ) ;
	outputs = PerformADPCM( origInputs, nInputs, armF, TRUE ) ;
	if( !outputs ) {
		free( ( void * ) origInputs ) ;
		return FALSE ;
	}
	
	decodedInputs = PerformADPCM( outputs, nInputs, armI, FALSE ) ;
	
	free( ( void * ) outputs ) ;
	
	if( !decodedInputs ) {
		free( ( void * ) origInputs ) ;
		return FALSE ;
	}
	
	SaveData( decodedInputs, nInputs, HWORDBYTES, 0, "fully transformed" ) ;
	
	printf( "Calculating error information...\n\n" ) ;
		
	ARRAYERROR( origInputs, decodedInputs, decodedInputs, nInputs, maxAbsErr, mse, short ) ;
	printf( "Maximum absolute error value calculated as '%d'\n\n", maxAbsErr ) ;
	printf( "The mean squared error between the original and decoded PCM data is '%d'\n\n", mse ) ;

	SaveData( decodedInputs, nInputs, HWORDBYTES, 0, "error" ) ;

	free( ( void * ) origInputs ) ;
	free( ( void * ) decodedInputs ) ;
	
	return TRUE ;
}

