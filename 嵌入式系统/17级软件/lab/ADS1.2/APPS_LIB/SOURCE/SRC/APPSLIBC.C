/*
 * Applications Library test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <string.h>

#include "appslibc.h"

#include "adpcmtec.h"
#include "bitmtesc.h"
#include "dcttestc.h"
#include "ffttestc.h"
#include "filtestc.h"
#include "g711tesc.h"
#include "hufftesc.h"
#include "is54tesc.h"
#include "mathtesc.h"
#include "dtmftesc.h"

#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define	APPS_LIB_OPTIONS	10

static char	gDirectory[ LIMIT ] ;

static void Menu( unsigned int numberOptions ) ;
static unsigned int SimulatedNextTask( unsigned int component, void ( *Menu )( unsigned int numberOptions ) ) ;

/**** AppsLib ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * passes control to each section of applications library until they are quit
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 10 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines which Applications
 *     Library component should be executed
 * Return Values
 * ------ ------
 *     int - return value from component run (always 0?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int AppsLib( unsigned int option, int argc, char **argv )
{
	int	result ;
	
	switch( option ) {
		case  1 :
			strcpy( gDirectory, "arm_adpm/" ) ;
			result = adpcm_main( argc, argv ) ;
			break ;
		case  2 :
			strcpy( gDirectory, "arm_bitm/" ) ;
			result = bitm_main( argc, argv ) ;
			break ;
		case  3 :
			strcpy( gDirectory, "arm_dct/" ) ;
			result = dct_main( argc, argv ) ;
			break ;
		case  4 :
			strcpy( gDirectory, "arm_fft/" ) ;
			result = fft_main( argc, argv ) ;
			break ;
		case  5 :
			strcpy( gDirectory, "arm_fil/" ) ;
			result = fil_main( argc, argv ) ;
			break ;
		case  6 :
			strcpy( gDirectory, "arm_g711/" ) ;
			result = g711_main( argc, argv ) ;
			break ;
		case  7 :
			strcpy( gDirectory, "arm_huff/" ) ;
			result = huff_main( argc, argv ) ;
			break ;
		case  8 :
			strcpy( gDirectory, "arm_is54/" ) ;
			result = is54_main( argc, argv ) ;
			break ;
		case  9 :
			strcpy( gDirectory, "arm_math/" ) ;
			result = math_main( argc, argv ) ;
			break ;
		case 10 :
			strcpy( gDirectory, "arm_mtmf/" ) ;
			result = dtmf_main( argc, argv ) ;
			break ;
		default :
			fprintf( stderr, "[AppsLib] Error in input arguments, aborting.\n\n" ) ;
			result = -1 ;
			break ;
	}
	
	return result ;
}

/**** CustomFOpen *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open the file in the given mode using fopen after adjusting the directory path
 * to the files
 *
 * Inputs
 * ------
 *   filename
 *   - an array of characters that is the file name of the file to open
 *   filemode
 *   - file mode as necessary for fopen
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file with file name filename
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *CustomFOpen( const char *filename, const char *filemode )
{
	char	modfilename[ LIMIT ] ;

	strcpy( modfilename, gDirectory ) ;
	strcat( modfilename, filename ) ;
	
	return fopen( ( const char * )modfilename, filemode ) ;
}

/**** CustomFreOpen *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open the file in the given mode using freopen after adjusting the directory path
 * to the files
 *
 * Inputs
 * ------
 *   filename
 *   - an array of characters that is the file name of the file to open
 *   filemode
 *   - file mode as necessary for freopen
 *   stream
 *   - the stream to associate with the open file
 * Return Values
 * ------ ------
 *     FILE * - the stream associated with the opened file with file name filename
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the stream is non-NULL, the stream should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *CustomFreOpen( const char *filename, const char *filemode, FILE *stream )
{
	char	modfilename[ LIMIT ] ;

	strcpy( modfilename, gDirectory ) ;
	strcat( modfilename, filename ) ;
	
	return freopen( ( const char * )modfilename, filemode, stream ) ;
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
	int				argccopy = argc ;
	char			**argvcopy = argv ;
	int				automagic ;
	unsigned int	components = 1 ;

	/* first argument is the binary and location being run */
	if( --( argccopy ) > 0 ) {
		sscanf( *( ++( argvcopy ) ), "%d", &automagic ) ;
	}
	
	while( 1 ) {
		printf( "ARM Applications Library.\n\n" ) ;
	
		if( automagic == 666 ) {
			if( components > APPS_LIB_OPTIONS ) {
				components = 0 ;
			}
			if( ( option = SimulatedNextTask( components, &Menu ) ) == 0 ) {
				break ;
			}
			components += 1 ;
		}
		else {
			if( ( option = NextTask( APPS_LIB_OPTIONS, &Menu ) ) == 0 ) {
				break ;
			}
		}
		
		argccopy = argc ;
		argvcopy = argv ;
		AppsLib( option, argccopy, argvcopy ) ;
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
	if( numberOptions == APPS_LIB_OPTIONS ) {
		printf( " 1. Adaptive Differential Pulse Code Modulation.\n" ) ;
		printf( " 2. Bit Manipulation.\n" ) ;
		printf( " 3. Discrete Cosine Transform.\n" ) ;
		printf( " 4. Fast Fourier Transform.\n" ) ;
		printf( " 5. Finite & Infinite Impulse Response and Least Mean Square Filters.\n" ) ;
		printf( " 6. G.711.\n" ) ;
		printf( " 7. Huffman Encoding & Decoding.\n" ) ;
		printf( " 8. IS54 Convolutional Encoding.\n" ) ;
		printf( " 9. Mathematics.\n" ) ;
		printf( "10. Multi-Tone Multi-Frequency.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** SimulatedNextTask *************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * simulates NextTask( ) in the utility library returning option given
 *
 * the list of available options is defined by a function pointer given with the 
 * addition of quitting the program
 *
 * Inputs
 * ------
 *   component
 *   - the component number to simulate selection of including exiting the program
 *   Menu
 *   - a pointer to the procedure Menu which is called to print the menu of available
 *     options for the user to select from
 *     procedure takes one input - components - and returns no values
 *     it should solely print a list of options available to the end user which does 
 *     not include 0 to exit the program, that being printed after the other options
 *     by this procedure when Menu has returned  
 * Return Values
 * ------ ------
 *     unsigned int - (simulated) option chosen by the user which will be component
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int SimulatedNextTask( unsigned int component, void ( *Menu )( unsigned int numberOptions ) )
{
	printf( "What do you want to do next?\n\n" ) ;

	Menu( APPS_LIB_OPTIONS ) ;

	printf( "\n" ) ;
	printf( " 0. Exit the program.\n\n" ) ;

	printf( "Please enter your choice (0 to %d) :\n", APPS_LIB_OPTIONS ) ;

	if( component == 0 ) {
		printf( "The program will now terminate.\n\n" ) ;
	}

	return component ;
}

