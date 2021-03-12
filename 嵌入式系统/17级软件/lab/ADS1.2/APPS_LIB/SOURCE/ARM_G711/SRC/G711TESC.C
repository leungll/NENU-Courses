/*
 * G.711 C test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>

#include "g711c.h"
#include "g711s.h"

#include "g711tesc.h"

#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define	G711_OPTIONS	28

#define	ALAWBYTES	1
#define LINEARBYTES	2
#define	ULAWBYTES	1
/* define the number of bytes for data types */

static void Menu( unsigned int numberOptions ) ;
static char *ProcessConvert( char inputs[ ], unsigned int numberBytesIn, unsigned int option, unsigned int *numberBytesOut ) ;

/**** Convert ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read a file of PCM or A/u-law data samples given by the user, encode them into 
 * one of A-law, u-law or PCM samples (depending on choice made from menu) using 
 * ARM or C routines, then if chosen, immediately decode them back
 * to the original PCM or A/u-law samples using ARM or C routines, and write
 * the new values calculated to a file given by the user
 *
 * information is also calculated including the number of bits in both the original
 * data and encoded data (after one stage if fully transforming) with the percentage 
 * reduction between the original and new samples given
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 28 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines which of ARM or C routines
 *     are used for the encoding and possible decoding
 * Return Values
 * ------ ------
 *     TRUE  - the transformation process was successful and data written
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Convert( unsigned int option )
{
	char			*origInputs ;
	unsigned int	numberBytesIn ;
	char			*outputs = NULL ;
	unsigned int	numberBytesOut ;
	char			*decodedInputs = NULL ;
	unsigned int	numberBytesDecoded ;
	
	printf( "Perform conversion...\n\n" ) ;
	
	if( ( origInputs = ( char * )GetData( BYTEBYTES, "input", &numberBytesIn ) ) == NULL ) {
		return FALSE ;
	}
	
	switch( option ) {
		case  1 :
		case  2 :
		case  3 :
		case  4 :
		case  5 :
		case  6 :
		case  7 :
		case  8 :
			printf( "Converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option, &numberBytesOut ) ;
			break ;
		case  9 :
		case 10 :
		case 13 :
		case 14 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 8, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 6, &numberBytesDecoded ) ;
			break ;
		case 11 :
		case 15 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 10, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 7, &numberBytesDecoded ) ;
			break ;
		case 12 :
		case 16 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 10, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 9, &numberBytesDecoded ) ;
			break ;
		case 17 :
		case 18 :
		case 19 :
		case 20 :
			printf( "Converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 8, &numberBytesOut ) ;
			break ;
		case 21 :
		case 22 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 12, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 10, &numberBytesDecoded ) ;
			break ;
		case 23 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 14, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 11, &numberBytesDecoded ) ;
			break ;
		case 24 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 14, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 13, &numberBytesDecoded ) ;
			break ;
		case 25 :
		case 26 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 14, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 16, &numberBytesDecoded ) ;
			break ;
		case 27 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 16, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 17, &numberBytesDecoded ) ;
			break ;
		case 28 :
			printf( "Forward converting...\n\n" ) ;
			outputs = ProcessConvert( origInputs, numberBytesIn, option - 16, &numberBytesOut ) ;
			printf( "Inverse converting...\n\n" ) ;
			decodedInputs = ProcessConvert( outputs, numberBytesOut, option - 19, &numberBytesDecoded ) ;
			break ;
		case  0 :
		default :
			free( ( void * ) origInputs ) ;
			if( decodedInputs != NULL ) {
				free( ( void * ) decodedInputs ) ;
			}
			return TRUE ;
	}
	
	if( !outputs ) {
		free( ( void * ) origInputs ) ;
		return FALSE ;
	}

    switch( option ) {
    	case  1 :
    	case  2 :
    	case  3 :
    	case  4 :
    	case  5 :
    	case  6 :
    	case  7 :
    	case  8 :
    	case 17 :
    	case 18 :
    	case 19 :
    	case 20 :
    		SaveData( outputs, numberBytesOut, BYTEBYTES, 0, "converted" ) ;
    		break ;
		case  9 :
		case 10 :
		case 11 :
		case 12 :
		case 13 :
		case 14 :
		case 15 :
		case 16 :
		case 21 :
		case 22 :
		case 23 :
		case 24 :
		case 25 :
		case 26 :
		case 27 :
		case 28 :
			if( !decodedInputs ) {
				free( ( void * ) origInputs ) ;
				if( outputs != NULL ) {
					free( ( void * ) outputs ) ;
				}
				return FALSE ;
			}
			SaveData( decodedInputs, numberBytesDecoded, BYTEBYTES, 0, "fully converted" ) ;
			break ;
    	case  0 :
    	default :
    		break ;
    }
    	
	free( ( void * ) origInputs ) ;
	free( ( void * ) outputs ) ;	
	if( decodedInputs != NULL ) {
		free( ( void * ) decodedInputs ) ;
	}
	
	return TRUE ;
}

/**** g711_main *********************************************************************
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
int g711_main( int argc, char **argv )
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
	
	printf( "Program to perform A-law, u-law conversions.\n\n" ) ;
	
	printf( "This application provides access to the conversions with\n" ) ;
	printf( "16-bit binary PCM input data or 8-bit A-law or u-law binary input data.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( G711_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		Convert( option ) ;
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
	if( numberOptions == G711_OPTIONS ) {
		printf( " 1. Convert linear PCM -> A-law using ARM Assembler.\n" ) ;
		printf( " 2. Convert linear PCM -> A-law using C.\n" ) ;
		printf( " 3. Convert A-law      -> linear PCM using ARM Assembler.\n" ) ;
		printf( " 4. Convert A-law      -> linear PCM using C.\n" ) ;
		printf( "\n" ) ;
		printf( " 5. Convert linear PCM -> u-law using ARM Assembler.\n" ) ;
		printf( " 6. Convert linear PCM -> u-law using C.\n" ) ;
		printf( " 7. Convert u-law      -> linear PCM using ARM Assembler.\n" ) ;
		printf( " 8. Convert u-law      -> linear PCM using ARM Assembler.\n" ) ;
		printf( "\n" ) ;
		printf( " 9. Convert linear PCM -> A-law using ARM Assembler -> linear PCM using ARM Assembler.\n" ) ;
		printf( "10. Convert linear PCM -> A-law using C             -> linear PCM using C.\n" ) ;
		printf( "11. Convert linear PCM -> A-law using ARM Assembler -> linear PCM using C.\n" ) ;
		printf( "12. Convert linear PCM -> A-law using C             -> linear PCM using ARM Assembler.\n" ) ;
		printf( "\n" ) ;
		printf( "13. Convert linear PCM -> u-law using ARM Assembler -> linear PCM using ARM Assembler.\n" ) ;
		printf( "14. Convert linear PCM -> u-law using C             -> linear PCM using C.\n" ) ;
		printf( "15. Convert linear PCM -> u-law using ARM Assembler -> linear PCM using C.\n" ) ;
		printf( "16. Convert linear PCM -> u-law using C             -> linear PCM using ARM Assembler.\n" ) ;
		printf( "\n" ) ;
		printf( "17. Convert A-law      -> u-law using ARM Assembler.\n" ) ;
		printf( "18. Convert A-law      -> u-law using C.\n" ) ;
		printf( "\n" ) ;
		printf( "19. Convert u-law      -> A-law using ARM Assembler.\n" ) ;
		printf( "20. Convert u-law      -> A-law using C.\n" ) ;
		printf( "\n" ) ;
		printf( "21. Convert A-law      -> u-law using ARM Assembler -> A-law using ARM Assembler.\n" ) ;
		printf( "22. Convert A-law      -> u-law using C             -> A-law using C.\n" ) ;
		printf( "23. Convert A-law      -> u-law using ARM Assembler -> A-law using C.\n" ) ;
		printf( "24. Convert A-law      -> u-law using C             -> A-law using ARM Assembler.\n" ) ;
		printf( "\n" ) ;
		printf( "25. Convert u-law      -> A-law using ARM Assembler -> u-law using ARM Assembler.\n" ) ;
		printf( "26. Convert u-law      -> A-law using C             -> u-law using C.\n" ) ;
		printf( "27. Convert u-law      -> A-law using ARM Assembler -> u-law using C.\n" ) ;
		printf( "28. Convert u-law      -> A-law using C             -> u-law using ARM Assembler.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PerformConversion *************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, either PCM or A/u-law, encode or decode them into
 * the required PCM, A-law or u-law values and return these new values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the inputs either PCM or A/u-law samples
 *   numberBytes
 *   - the number of data points referenced by the array inputs (each entry 1 byte)
 *     this is not necessarily the number of inputs, since data may not be 1 byte each
 *   inBytes
 *   - the size in bytes of each input data item
 *     numberBytes/inBytes is the number of input data items being passed
 *   outBytes
 *   - the size in bytes for the output data items
 *   numberBytesOut
 *   - a pointer to an integer to hold the actual number of bytes written out
 *     this value gives the size of the character array returned
 *   ConvRoutine
 *   - a pointer to the conversion routine to be applied to the data
 *     the conversion routine should take one integer input with all unused top 
 *     bits clear
 *     the conversion routine should return one integer the result of the conversion
 *     with all unused top bits clear
 *     this routine will perform the actual conversion between the data
 * Outputs
 * -------
 *   numberBytesOut
 *   - the number of bytes referenced by the returned character array
 *     the actual number of data items is numberBytesOut/outBytes
 *     undefined if NULL returned (see Return Values)
 * Return Values
 * ------ ------
 *     char * - an array of samples of PCM, A-law or u-law dependent on conversion
 *     NULL   - some error occurred (memory allocation failed?)
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
static char *PerformConversion( char inputs[ ], unsigned int numberBytes, unsigned int inBytes, unsigned int outBytes, unsigned int *numberBytesOut, int ( *ConvRoutine )( int ) )
{
	unsigned char	*ucinputs = ( unsigned char * )inputs ;
	unsigned int	numberInSamples ;
	char			*outputs ;
	unsigned char	*ucoutputs ;
	unsigned int	counter ;
	int				input ;
	int				output ;
	
	if( ( !inputs ) || ( !numberBytesOut ) || ( !ConvRoutine ) ) {
		fprintf( stderr, "[PerformConversion] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}

	numberInSamples = numberBytes/inBytes ;
	*numberBytesOut = numberInSamples * outBytes ;
	
	if( ( outputs = ( char * )calloc( *numberBytesOut, sizeof( char ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		*numberBytesOut = -1 ;
		return NULL ;
	}
	ucoutputs = ( unsigned char * )outputs ;
	
	for( counter = 0 ; counter < numberInSamples ; counter += 1 ) {
		switch( inBytes ) {
			case 1 :
				input = ucinputs[ counter ] ;
				input <<= 24 ;
				input >>= 24 ;
				break ;
			case 2 :
				input = ucinputs[ counter << 1 ] + ( ucinputs[ ( counter << 1 ) + 1 ] << 8 ) ;
				input <<= 16 ;
				input >>= 16 ;
				break ;
			case 4 :
				input = ucinputs[ counter << 2 ] + ( ucinputs[ ( counter << 2 ) + 1 ] << 8 )
						+ ( ucinputs[ ( counter << 2 ) + 2 ] << 16 )
						+ ( ucinputs[ ( counter << 2 ) + 3 ] << 24 ) ;
				break ;
			default :
				free( ( void * ) outputs ) ;
				return NULL ;
		}
		
		output = ConvRoutine( input ) ;
		
		switch( outBytes ) {
			case 1 :
				ucoutputs[ counter ] = ( unsigned char )output ;
				break ;
			case 2 :
				ucoutputs[ ( counter << 1 ) ] = ( unsigned char )output ;
				output >>= 8 ;
				ucoutputs[ ( counter << 1 ) + 1 ] = ( unsigned char )output ;
				break ;
			case 4 :
				ucoutputs[ ( counter << 2 ) ] = ( unsigned char )output ;
				output >>= 8 ;
				ucoutputs[ ( counter << 2 ) + 1 ] = ( unsigned char )output ;
				output >>= 8 ;
				ucoutputs[ ( counter << 2 ) + 2 ] = ( unsigned char )output ;
				output >>= 8 ;
				ucoutputs[ ( counter << 2 ) + 3 ] = ( unsigned char )output ;
				break ;
			default :
				break ;
		}
	}
	
	return outputs ;
}

/**** ProcessConvert ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an array of data values, either PCM or A/u-law, determine the type of
 * conversion required, set up the conversion routine and byte sizes for input and
 * output data and then encode or decode the data into the required PCM, A-law or
 * u-law values and return these new values
 *
 * Inputs
 * ------
 *   inputs
 *   - an array referencing the inputs either PCM or A/u-law samples
 *   numberBytes
 *   - the number of data points referenced by the array inputs (each entry 1 byte)
 *     this is not necessarily the number of inputs, since data may not be 1 byte each
 *   option
 *   - the conversion to be performed determined from that given by the user adjusted
 *     to the range 1 to 12 as only performs one transformation here
 *     this defines whether data is PCM, A-law or u-law and thus byte size
 *     for the input data and the resulting data type and byte size
 *   numberBytesOut
 *   - a pointer to an integer to hold the actual number of bytes written out
 *     this value gives the size of the character array returned
 * Outputs
 * -------
 *   numberBytesOut
 *   - the number of bytes referenced by the returned character array
 *     the actual number of data items can be determined from numberBytesOut and
 *     option which defines the sample type returned and thus byte size for data
 *     undefined if NULL returned (see Return Values)
 * Return Values
 * ------ ------
 *     char * - an array of samples of PCM, A-law or u-law dependent on conversion
 *     NULL   - some error occurred (memory allocation failed?)
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
static char *ProcessConvert( char inputs[ ], unsigned int numberBytesIn, unsigned int option, unsigned int *numberBytesOut )
{
	unsigned int		inBytes ;
	unsigned int		outBytes ;
	int					( *convRoutine )( int ) ;
	
	if( ( !inputs ) || ( !numberBytesOut ) ) {
		fprintf( stderr, "[ProcessConvert] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}

	switch( option ) {
		case  1 :
			inBytes = LINEARBYTES ;
			outBytes = ALAWBYTES ;
			convRoutine = G711_linear2alaw ;
			break ;
		case  2 :
			inBytes = LINEARBYTES ;
			outBytes = ALAWBYTES ;
			convRoutine = linear2alaw ;
			break ;
		case  3 :
			inBytes = ALAWBYTES ;
			outBytes = LINEARBYTES ;
			convRoutine = G711_alaw2linear ;
			break ;
		case  4 :
			inBytes = ALAWBYTES ;
			outBytes = LINEARBYTES ;
			convRoutine = alaw2linear ;
			break ;
		case  5 :
			inBytes = LINEARBYTES ;
			outBytes = ULAWBYTES ;
			convRoutine = G711_linear2ulaw ;
			break ;
    	case  6 :
			inBytes = LINEARBYTES ;
			outBytes = ULAWBYTES ;
			convRoutine = linear2ulaw ;
			break ;
    	case  7 :
			inBytes = ULAWBYTES ;
			outBytes = LINEARBYTES ;
			convRoutine = G711_ulaw2linear ;
			break ;
    	case  8 :
			inBytes = ULAWBYTES ;
			outBytes = LINEARBYTES ;
			convRoutine = ulaw2linear ;
			break ;
    	case  9 :
			inBytes = ALAWBYTES ;
			outBytes = ULAWBYTES ;
			convRoutine = G711_alaw2ulaw ;
			break ;
		case 10 :
			inBytes = ALAWBYTES ;
			outBytes = ULAWBYTES ;
			convRoutine = alaw2ulaw ;
			break ;
    	case 11 :
			inBytes = ULAWBYTES ;
			outBytes = ALAWBYTES ;
			convRoutine = G711_ulaw2alaw ;
			break ;
    	case 12 :
			inBytes = ULAWBYTES ;
			outBytes = ALAWBYTES ;
			convRoutine = ulaw2alaw ;
			break ;
		default :
			return NULL ;
	}
	
	printf( "Number of samples for conversion is '%d'\n\n", numberBytesIn/inBytes ) ;
	return PerformConversion( inputs, numberBytesIn, inBytes, outBytes, numberBytesOut, convRoutine ) ;
}

