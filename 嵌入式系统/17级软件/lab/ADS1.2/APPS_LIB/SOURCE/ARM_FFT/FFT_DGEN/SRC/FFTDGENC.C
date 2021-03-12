/*
 * Fast Fourier Transform test data generation
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bitutilc.h"
#include "custredc.h"
#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define	FFT_DGEN_OPTIONS	2

#define	DEFAULTNDP	256
/* define the default number of data points */
#define	DEFAULTL	1.0
/* define default output bin (fractional) */

static void Menu( unsigned int numberOptions ) ;

/**** DataSetUp *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the users filename to save test data to and open it
 *
 * also give the user three chances to give the number of data points that should
 * be in the output data and if they do not supply valid data after the third attempt
 * set the number of points to the default value
 *
 * Inputs
 * ------
 *   dataType
 *   - an optional string the describes the data being created which is printed to
 *     the screen before asking the user for a file name
 *     to be non-specific pass NULL
 *   fileName
 *   - a string that will hold the filename given by the user
 *   limit
 *   - the maximum length of filename that can be read into the string (including '\0')
 *   n
 *   - a pointer to an integer to store the number of data points
 * Outputs
 * -------
 *   fileName
 *   - the fileName given by the user which is the name of the file opened
 *     undefined if NULL returned (see Return Values)
 *   n
 *   - the number of data points that are required
 *     will be power of 2 i.e. n = 2^x
 *     undefined if NULL returned (see Return Values)
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file, should be closed after use
 *     NULL   - some error occurred
 *
 * n will hold the number of data points required
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static FILE *DataSetUp( char *dataType, char *fileName, unsigned int limit, unsigned int *n )
{
	FILE			*fp ;
	unsigned int	counter ;
	unsigned int	is2 ;
	
	if( ( !fileName ) || ( !n ) ) {
		fprintf( stderr, "[DataSetUp] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( dataType != NULL ) {
		printf( "A set of data will be created to represent a %s.\n\n", dataType ) ;
	}
	
	while( 1 ) {
		printf( "Please give the name of the file (with directory path) to save the " ) ;
		if( dataType != NULL ) {
			printf( "%s ", dataType ) ;
		}
		printf( "data.\n\n" ) ;
		if( GetFileName( fileName, limit, "writing" ) != NULL ) {
			if( ( fp = OpenFileWrite( "w", fileName ) ) != NULL ) {
				break ;
			}
		}
	}
	
	counter = 3 ;
	while( 1 ) {
		printf( "Please give the number of data points for the %s which must be a multiple of 2.\n\n", dataType ) ;
		
		printf( "Number of data points (power of 2) : " ) ;
		*n = ( int )ReadDouble( ) ;
		ISPOWEROF2( *n, is2 ) ;
		if( is2 ) {
			break ;
		}
		printf( "The number '%d' is not a power of 2.\n\n", *n ) ;
		counter -= 1 ;
		if( counter == 0 ) {
			printf( "The default value of '%d' data points will be used.\n\n", DEFAULTNDP ) ;
			*n = DEFAULTNDP ;
			break ;
		}
	}
	
	return fp ;
}

/**** GenerateLine *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a file containing a set of complex 14-bit fixed-point values that represent
 * a straight line in the complex plane
 *
 * the file name and number of data points for the line are given by the user at run
 * time
 *
 * Return Values
 * ------ ------
 *     TRUE  - a file has been created which holds the data for a straight line
 *     FALSE - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean GenerateLine( void )
{
	char			lineFName[ LIMIT ] ;
	unsigned int	n ;
	FILE			*fp ;
	unsigned int	halfway ;
	unsigned int	inputs ;
	double			real ;
	double			imaginary ;
	
	fp = DataSetUp( "straight line", lineFName, LIMIT, &n ) ;
	
	printf( "Creating line data file '%s' with '%d' complex points...\n\n", lineFName, n ) ;
	
	halfway = n/2 ;
	for( inputs = 0 ; inputs < n ; inputs += 1 ) {
		real = ( double )( ( int )( ( ( int )( inputs - halfway ) )* 2 ) )/( ( double ) n ) ;	/* gives range -n..n */
		real *= ( double )( 1 << 14 ) ;	/* set as 14-bit fixed point precision */
		imaginary = real / 2 ;
		
		REMOVESIGNEXTEND( real, 16 ) ;
		REMOVESIGNEXTEND( imaginary, 16 ) ;
		/* ensures data is 16 bit */
		
		fprintf( fp, "0x%.4x\n0x%.4x\n", ( int )real, ( int )imaginary ) ;
	}
	
	fclose( fp ) ;
	
	printf( "Straight line created.\n\n" ) ;

	return TRUE ;
}

/**** GenerateSine *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a file containing a set of complex 14-bit fixed-point values that represent
 * a sinewave in the complex plane
 *
 * the file name, number of data points and bin value (maybe be fractional) for the 
 * sinewave are given by the user at run time
 *
 * Return Values
 * ------ ------
 *     TRUE  - a file has been created which holds the data for a sinewave
 *     FALSE - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean GenerateSine( void )
{
	char			sineFName[ LIMIT ] ;
	unsigned int	n ;
	double			l ;
	FILE			*fp ;
	unsigned int	counter ;
	double			omega ;
	unsigned int	inputs ;
	double			cosr ;
	double			sinr ;
	
	fp = DataSetUp( "sine wave", sineFName, LIMIT, &n ) ;

	counter = 3 ;
	while( 1 ) {
		printf( "Please give the bin (input data point) for the sine wave (may be fractional).\n\n" ) ;
		
		printf( "Bin (input data point) : " ) ;
		l = ReadDouble( ) ;
		if( l < 0 ) {
			printf( "The bin value must be positive, choose again.\n\n" ) ;
			counter -= 1 ;
		}
		else if( l > n ) {
			printf( "The bin value cannot be greater than number of data points '%d', choose again.\n\n", n ) ;
			counter -= 1 ;
		}
		else {
			break ;
		}
		if( counter == 0 ) {
			printf( "The default bin value of '%lf' will be used.\n\n", DEFAULTL ) ;
			l = DEFAULTL ;
			break ;
		}
	}
	
	printf( "Creating sine data file '%s' with '%d' complex points in bin '%lf'...\n\n", sineFName, n, l ) ;
	
	omega = 2.0 * PI /( double )n ;
	for( inputs = 0 ; inputs < n ; inputs += 1 ) {
		cosr = cos( inputs * l * omega ) ;
		cosr *= ( double )( 1 << 14 ) ;
		REMOVESIGNEXTEND( cosr, 16 ) ;
		
		sinr = sin( inputs * l * omega ) ;
		sinr *= ( double )( 1 << 14 ) ;
		REMOVESIGNEXTEND( sinr, 16 ) ;

		fprintf( fp, "0x%.4x\n0x%.4x\n", ( int )cosr, ( int )sinr ) ;
	}
	
	fclose( fp ) ;
	
	printf( "Sine wave created.\n\n" ) ;
	
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
int main( int argc, char **argv )
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
	
	printf( "Application to create a set of complex data for testing the FFT.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( FFT_DGEN_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		switch( option ) {
			case 1 :
				GenerateSine( ) ;
				break ;
			case 2 :
				GenerateLine( ) ;
				break ;
			default :
				break ;
		}
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
	if( numberOptions == FFT_DGEN_OPTIONS ) {
		printf( " 1. Sine wave\n" ) ;
		printf( " 2. Straight line\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}


