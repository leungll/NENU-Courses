/*
 * IS-54-B Convolutional Encoder test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdlib.h>

#include "is54cec.h"
#include "is54ces.h"

#include "is54tesc.h"

#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define	IS54_OPTIONS	1

static void Menu( unsigned int numberOptions ) ;

/**** Encode ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read file given by the user for unsigned short IS54 input datam and for each set
 * given (a set containing 7 integer words) convolutionally encode the data using
 * both ARM and C versions and print the results to the screen for comparison
 *
 * Inputs
 * ------
 *   option
 *   - reserved for future use
 * Return Values
 * ------ ------
 *     TRUE  - the encoding process was successful
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Encode( unsigned int option )
{
	ushort			*inputs ;
	unsigned int	nInputs ;
	uint			outputsARM[ 6 ] ;
	uint			outputsC[ 6 ] ;
	unsigned int	sets ;
	unsigned int	counter ;
	unsigned int	is54counter ;
	
	if( option > IS54_OPTIONS ) {
		fprintf( stderr, "[Encode] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}
	
	if( ( inputs = ( ushort * )GetData( HWORDBYTES, "input", &nInputs ) ) == NULL ) {
		return FALSE ;
	}
	
	if( nInputs%7 != 0 ) {
		fprintf( stderr, "Error in number of inputs (%d), must be multiple of 7, aborting.\n\n", nInputs ) ;
		free( ( void * ) inputs ) ;
		return FALSE ;
	}
	
	sets = nInputs/7 ;
	printf( "%d set(s) of data to encode.\n\n", sets ) ;
	
	for( is54counter = 0 ; is54counter < sets ; is54counter += 1 ) {	
		printf( "Encoding set '%d' in ARM...\n\n", is54counter ) ;
		
		ConvolutionalEncoder( outputsARM, inputs + is54counter*7 ) ;
		
		printf( "Encoding set '%d' in C (for comparison)...\n\n", is54counter ) ;
		
		ConvEncoderC( outputsC, inputs + is54counter*7 ) ;
		
		printf( "Result of encoding set '%d'...\n\n", is54counter ) ;
		
		for( counter = 0 ; counter < 6 ; counter += 1 ) {
			printf( "ARM = 0x%.8x, C = 0x%.8x   ", outputsARM[ counter ], outputsC[ counter ] ) ;
			printf( "(error = %3d)", outputsARM[ counter ] - outputsC[ counter ] ) ;
			printf( "\n" ) ;
		}
		printf( "\n" ) ;
	}
	
	free( ( void * ) inputs ) ;
	
	printf( "Program complete.\n\n" ) ;
	
	return TRUE ;
}

/**** main **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform one iteration of the IS54 convolutional encoder then quit
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
int is54_main( int argc, char **argv )
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
	
	printf( "Program to perform IS 54 convolution encoding.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( IS54_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		Encode( option ) ;
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
	if( numberOptions == IS54_OPTIONS ) {
		printf( " 1. IS54 Convolutional Encoding.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

