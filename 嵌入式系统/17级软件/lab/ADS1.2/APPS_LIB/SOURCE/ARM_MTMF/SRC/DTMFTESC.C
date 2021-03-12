/*
 * Dual-Tone Multi-Frequency Tone Detect/Generate test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mtmfc.h"

#include "dtmftesc.h"

#include "bitutilc.h"
#include "custredc.h"
#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"

#define	DTMF_OPTIONS	2

/* define the DTMF tones */
static const unsigned int DTMFTones[ 8 ] =	{
										697, /*   1	   2	 3	   A	*/
										770, /*   4	   5	 6	   B	*/
										852, /*   7	   8	 9	   C	*/
										941, /*   *	   0	 #	   D	*/
												1209, 1336, 1447, 1633
									} ;

/* define the DTMF values */
static const unsigned char DTMFValues[16] = 	{	
											'1', '2', '3', 'A',
											'4', '5', '6', 'B',
											'7', '8', '9', 'C',
											'*', '0', '#', 'D' 
										} ;

/* initialise memory for cosine and sines of DTMF tones */
static int DTMFCosines[ 9 ] ;
static int DTMFSines[ 9 ] ;

#define	NOISEFACTOR		( 1 << 11 )		/* maximum noise value used to scale random number to 0..NOISEFACTOR */
#define	SAMPLINGRATE	8000			/* the sampling rate in Hertz */
#define	SHIFT			15				/* the shift of cosine and sine values */
#define	TONEDISTINCTION	1				/* the distinction between valid tones and noise */
#define	MINMS			8				/* minimum number of milliseconds duration for tone, frequency or frame */
#define	FRAMESIZE		( SAMPLINGRATE/1000 )*MINMS		/* the default frame size in ms for sampling rate and min duration */

/* define tone generation structure to passing several pieces of information */
typedef struct	DTMFToneGenStruct	DTMFToneGenStruct ;
typedef			DTMFToneGenStruct	*DTMFToneGenStructPtr ;

struct DTMFToneGenStruct {
	unsigned int	toneperiod ;
	unsigned int	silenceperiod ;
	unsigned int	period ;
	unsigned int	hitonelevel ;
	unsigned int	lotonelevel ;
	unsigned int	framesize ;
} ;

/* define a type to identify whether to detect a tone or silence */
typedef enum{ TONE, SILENCE } ToneSilence ;

static Boolean DTMFTableGen( int table[ ], unsigned int samplingRate, unsigned int shift, double( *trig )( double ) ) ;
static Boolean DTMFValid( unsigned char dtmfValues[ ], unsigned int nValues ) ;
static short *GenerateDTMFSamples( unsigned char values[ ], unsigned int nValues, DTMFToneGenStructPtr dtmfToneGenStructPtr, Boolean noise, short samples[ ], unsigned int *nSamples ) ;
static void Menu( unsigned int numberOptions ) ;
static void PrintNumberPad( void ) ;
static ToneState *SetDTMFTones( ToneState toneStates[ ], unsigned char value, unsigned int lotonelevel, unsigned int hitonelevel, Boolean noise ) ;

/**** DetectDTMFTone ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * detect the next DTMF tone or silence in the given set of samples
 *
 * Inputs
 * ------
 *   samples
 *   - the set of samples to detect tone or silence in
 *   nSamples
 *   - the number of samples in the set to detect tone or silence in
 *   toneSilence
 *   - TONE    : detect a DTMF tone 0-9, a-d (or A-D), * and #
 *     SILENCE : detect silence
 *   toneDistinction
 *   - the number of bits to right shift the energies to distinguish a tone from
 *     background noise
 * Return Values
 * ------ ------
 *     if TONE
 *      unsigned char - the tone detected 0-9, A-D, * or #
 *      0             - no tone was detected
 *     if SILENCE
 *      1             - silence detected
 *      0             - no silence period detected
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned char DetectDTMFTone( short samples[ ], unsigned int nSamples, ToneSilence toneSilence, unsigned int toneDistinction )
{
	unsigned int	loMax = 0 ;
	unsigned int	hiMax = 0 ;
	int				loTone = -1 ;
	int				hiTone = -1 ;
	ToneState		toneStates[ 8 ] ;
	unsigned int	energies[ 8 ] ;
	unsigned int	i ;
	unsigned char	tone = 0 ;
	
	if( ( !samples ) || ( nSamples == 0 ) ) {
		fprintf( stderr, "[DetectDTMFTone] Error in input arguments, aborting.\n\n" ) ;
		return 0 ;
	}
	
	ToneDetectSetup( toneStates, ( int * )DTMFCosines, 8 ) ;
	ToneDetect( samples, nSamples, toneStates, 8 ) ;
	ToneDetectResults( energies, 2, toneStates, 8 ) ;
	
	for( i = 0 ; i < 4 ; i += 1 ) {
		if( ( energies[ i ] >> toneDistinction ) > loMax ) {		/* tone must be (1<<toneDistinction) greater than any other tone */
			loMax = energies[ i ] ;
			loTone = i ;
		}
		else if( ( loMax >> toneDistinction ) < energies[ i ] ) {	/* energy is within (1<<toneDistinction), previous max tone is not valid tone */
			loTone = -1 ;
			if( loMax < energies[ i ] ) {
				loMax = energies[ i ] ;
			}
		}
		if( ( energies[ i + 4 ] >> toneDistinction ) > hiMax ) {
			hiMax = energies[ i + 4 ] ;
			hiTone = i ;
		}
		else if( ( hiMax >> toneDistinction ) < energies[ i + 4 ] ) {
			hiTone = -1 ;
			if( hiMax < energies[ i + 4 ] ) {
				hiMax = energies[ i + 4 ] ;
			}
		}
	}
		
	/* ensure that both tones are close to each other */
	if( ( loMax < ( hiMax >> 1 ) ) || ( hiMax < ( loMax >> 1 ) ) ) {
		loTone = hiTone = -1 ;
	}
	
	tone = 0 ;
	if( ( loTone != -1 ) && ( hiTone != -1 ) ) {
		if( toneSilence == TONE ) {
			tone = DTMFValues[ hiTone + ( loTone << 2 ) ] ;
		}
	}
	else if( toneSilence == SILENCE ) {
		tone = 1 ;
	}
	
	return tone ;
}

/**** DetectDTMFTones ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * detect all the tones and silences in the given set of samples
 *
 * Inputs
 * ------
 *   samples
 *   - the set of samples to detect tones and silence in
 *   nSamples
 *   - the number of samples in the set to detect tones and silence in
 *   framesize
 *   - the size of the frame to detect tones in
 *     must be of sufficient size to allow energies to be accumulated and
 *     small enough to allow short duration of tone or silence to be detected
 *   toneDistinction
 *   - the number of bits to right shift the energies to distinguish a tone from
 *     background noise
 *   fulldetails
 *   - 1 : give samples where tone detected, silence detected or nothing detected
 *     0 : only give tones and silence detected and now by which samples or if nothing detected
 *   dtmfTones
 *   - an array to hold the tones detected
 *   maxTones
 *   - the maximum number of tones that can be detected before array exhausted
 * Outputs
 * -------
 *   dtmfTones
 *   - the tones detected if non-NULL returned
 *   maxTones
 *   - the number of tones detected if non-NULL returned
 * Return Values
 * ------ ------
 *     unsigned char * - a pointer to dtmfTones if tones detected
 *     NULL			   - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned char *DetectDTMFTones( short samples[ ], unsigned int nSamples, unsigned int framesize, unsigned int toneDistinction, unsigned int fulldetails, unsigned char dtmfTones[ ], unsigned int *maxTones )
{
	ToneSilence		toneSilence = TONE ;
	unsigned char	tone ;
	unsigned int	i ;
	unsigned int	j ;
	
	if( ( !samples ) || ( nSamples == 0 ) || ( framesize == 0 ) || ( !dtmfTones ) || ( !maxTones ) || ( *maxTones == 0 ) ) {
		fprintf( stderr, "[DetectDTMFTones] Error in input arguments, aborting.\n\n" ) ;
		return NULL ;
	}
	
	printf( "Using a %ums framesize, the DTMF values detected are :\n\n", ( framesize*1000 )/SAMPLINGRATE ) ;
	
	j = 0 ;
	for( i = 0 ; i < nSamples ; i += framesize ) {
		if( ( tone = DetectDTMFTone( samples + i, framesize, toneSilence, toneDistinction ) ) != 0 ) {
			printf( "\t" ) ;
			if( toneSilence == TONE ) {
				printf( "'%c' ", tone ) ;
				dtmfTones[ j++ ] = tone ;
				if( j == *maxTones ) {
					break ;
				}
				toneSilence = SILENCE ;
			}
			else {
				printf( "silence " ) ;
				toneSilence = TONE ;
			}
			if( fulldetails ) {
				printf( "in samples %u to %u.\n", i, i + framesize ) ;
			}
			else {
				printf( "\n" ) ;
			}
		}
	}
	printf( "\n" ) ;
	*maxTones = j ;
	
	return dtmfTones ;
}

/**** DTMF **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform a DTMF generation or detection
 *
 * generation:
 * get user information for DTMF values to generate waveform for, framesize to use
 * duration of tones and silence and peak values, generate discrete waveform samples
 * and save to a file given by the user
 *
 * detection:
 * read a file given by the user and using the framesize given by the user try to
 * detect DTMF values and silence
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 2 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines whether generating or detecting
 *     (respectively)
 * Return Values
 * ------ ------
 *     TRUE  - the process was successful
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean DTMF( unsigned int option )
{	
	DTMFToneGenStruct	dtmfToneGenStruct ;
	unsigned char		dtmfTones[ LIMIT ] ;
	unsigned int		nTones = LIMIT ;
	short				*samples = NULL ;
	unsigned int		framesize = FRAMESIZE ;
	unsigned int		nSamples ;
	unsigned int		is2 ;
	Boolean				noise ;
	unsigned int		i ;
	
	printf( "Perform DTMF...\n\n" ) ;
	
	if( option == 666 ) {
		printf( "Instigating hidden option: generate & detect DTMF.\n\n" ) ;
	}
	
	switch( option ) {
		case 1 :
		case 666 :
			do {
				printf( "Please give the DTMF values to generate.\n\n" ) ;
				PrintNumberPad( ) ;
				printf( "Values (0-9, A-D, *, #) : " ) ;
				ReadInString( stdin, ( char * )dtmfTones, LIMIT ) ;
				printf( "\n" ) ;
			} while( !DTMFValid( dtmfTones, strlen( ( char * )dtmfTones ) ) ) ;
			break ;
		case 2 :
			if( ( samples = ( short * )GetData( HWORDBYTES, "DTMF detection", &nSamples ) ) == NULL ) {
				return FALSE ;
			}
			break ;
		default :
			return TRUE ;
	}
	
	switch( option ) {
		case 1 :
		case 666 :
			/* define an example framesize to show multiple calls to generate the samples */
			dtmfToneGenStruct.framesize = FRAMESIZE ;
			
			/* get values as power of 2 to ease complexity in detector */
			printf( "Please give the duration of the tones.\n\n" ) ;
			do {
				printf( "Duration of tones (milliseconds, minimum %ums, power of 2) : ", MINMS ) ;
				dtmfToneGenStruct.toneperiod = ( int )ReadDouble( ) ;
				ISPOWEROF2( dtmfToneGenStruct.toneperiod, is2 ) ;
				if( !is2 ) {
					fprintf( stderr, "Value '%u' is not a power of 2.\n\n", dtmfToneGenStruct.toneperiod ) ;
				}
				else if( dtmfToneGenStruct.toneperiod < MINMS ) {
					fprintf( stderr, "Value '%u' is less than %u.\n\n", dtmfToneGenStruct.toneperiod, MINMS ) ;
				}
				else {
					break ;
				}
			} while( 1 ) ;
			dtmfToneGenStruct.toneperiod = ( int )( ( ( double )dtmfToneGenStruct.toneperiod/1000.0 )*( double )SAMPLINGRATE + 0.5 ) ;
			
			printf( "Please give the duration of silence between tones.\n\n" ) ;
			do {
				printf( "Duration of silence (milliseconds, minimum %ums, power of 2) : ", MINMS ) ;
				dtmfToneGenStruct.silenceperiod = ( int )ReadDouble( ) ;
				ISPOWEROF2( dtmfToneGenStruct.silenceperiod, is2 ) ;
				if( !is2 ) {
					fprintf( stderr, "Value '%u' is not a power of 2.\n\n", dtmfToneGenStruct.silenceperiod ) ;
				}
				else if( dtmfToneGenStruct.silenceperiod < MINMS ) {
					fprintf( stderr, "Value '%u' is less than %u.\n\n", dtmfToneGenStruct.silenceperiod, MINMS ) ;
				}
				else {
					break ;
				}
			} while( 1 ) ;
			dtmfToneGenStruct.silenceperiod = ( int )( ( ( double )dtmfToneGenStruct.silenceperiod/1000.0 )*( double )SAMPLINGRATE + 0.5 ) ;
	
			printf( "Please give the peak value for the DTMF tones.\n\n" ) ;
			do {
				printf( "Peak of DTMF tones (power of 2) : " ) ;
				dtmfToneGenStruct.lotonelevel = ( int )ReadDouble( ) ;
				ISPOWEROF2( dtmfToneGenStruct.lotonelevel, is2 ) ;
				if( is2 ) {
					break ;
				}
				fprintf( stderr, "Value '%d' is not a power of two.\n\n", dtmfToneGenStruct.lotonelevel ) ;
			} while( 1 ) ;
			dtmfToneGenStruct.hitonelevel = dtmfToneGenStruct.lotonelevel ;
			
			printf( "Random noise can be added to the generated values but this may stop the DTMF tones from being detectable.\n\n" ) ;
			if( YesNo( "Add noise to DTMF tones", "add noise", "don't add noise" ) ) {
				noise = TRUE ;
			}
			else {
				noise = FALSE ;
			}

			nSamples = strlen( ( char * )dtmfTones )*( dtmfToneGenStruct.toneperiod + dtmfToneGenStruct.silenceperiod ) ;
			if( ( samples = ( short * )calloc( nSamples, sizeof( short ) ) ) == NULL ) {
				fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
				return FALSE ;
			}
			if( !GenerateDTMFSamples( dtmfTones, strlen( ( char * )dtmfTones ), &dtmfToneGenStruct, noise, samples, &nSamples ) ) {
				free( ( void * ) samples ) ;
				return FALSE ;
			}
			break ;
		default :
			break ;
	}
	
	switch( option ) {
		case 1 :
			SaveData( samples, nSamples, HWORDBYTES, 0, "generated DTMF" ) ;
			break ;
		case 666 :
			printf( "Please give the size of the frame that determines the number of samples to search for\n" ) ;
			printf( "a tone or silence.\n\n" ) ;
			
			printf( "The frame size must not be greater than the minimum of the duration of the tones and\n" ) ;
			printf( "the duration of the silence.\n\n" ) ;
			
			printf( "For example if tone duration = 32ms, silence = 16ms then 8ms <= frame size <= 16ms.\n\n" ) ;
			
			do {
				printf( "Size of frame (milliseconds, minimum %ums, power of 2) : ", MINMS ) ;
				framesize = ( int )ReadDouble( ) ;
				ISPOWEROF2( framesize, is2 ) ;
				if( !is2 ) {
					fprintf( stderr, "Value '%u' is not a power of 2.\n\n", framesize ) ;
				}
				else if( framesize < MINMS ) {
					fprintf( stderr, "Value '%u' is less than %u.\n\n", framesize, MINMS ) ;
				}
				else {
					break ;
				}
			} while( 1 ) ;
			framesize = ( int )( ( ( double )framesize/1000.0 )*( double )SAMPLINGRATE + 0.5 ) ;
			/* drop through to continue */
		case 2 :
			DetectDTMFTones( samples, nSamples, framesize, TONEDISTINCTION, option == 666, dtmfTones, &nTones ) ;
			if( option == 666 ) {
				printf( "Detected tones :\n\n" ) ;
				for( i = 0 ; i < nTones ; i += 1 ) {
					printf( "'%c' ", dtmfTones[ i ] ) ;
					if( ( i > 0 ) && ( i%32 == 0 ) ) {
						printf( "\n" ) ;
					}
				}
				if( i%32 != 0 ) {
					printf( "\n\n" ) ;
				}
				else {
					printf( "\n" ) ;
				}
			}
			break ;
		default :
			break ;
	}
	
	free( ( void * ) samples ) ;
	
	if( option == 666 ) {
		printf( "Finished hidden option.\n\n" ) ;
	}
	
	return TRUE ;
}

/**** dtmf_main *********************************************************************
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
int dtmf_main( int argc, char **argv )
{
	unsigned int	option = 0 ;
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
	
	printf( "Program to test Multi-Tone Multi-Frequency (MTMF) generation and detection\n" ) ;
	printf( "using Dual-Tone Multi-Frequency (DTMF) as an example.\n\n" ) ;
	
	printf( "This application generates and detects 16-bit fixed-point DTMF data with the\n" ) ;
	printf( "point between bits 14 and 15.\n\n" ) ;
	
	DTMFTableGen( DTMFCosines, SAMPLINGRATE, SHIFT, &cos ) ;
	DTMFTableGen( DTMFSines, SAMPLINGRATE, SHIFT, &sin ) ;
	
	while( 1 ) {
		if( ( option = NextTask( DTMF_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		DTMF( option ) ;
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

/**** DTMFTableGen ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a constant table of DTMF trigonometric tones where
 * tone is cosTheta or sinTheta (given by trig function) and
 * Theta = 2 * pi * DTMFTone / sampling rate
 *
 * the resulting trig tone is shifted into fixed-point value
 *
 * a trig tone for silence as the last element is also created
 *
 * Inputs
 * ------
 *   table
 *   - an array of 9 entries for the 8 DTMF tones and 1 for silence
 *   samplingRate
 *   - the sampling rate for the entries e.g. 8000 Hz
 *   shift
 *   - the fixed-point shift e.g. 15 to create 16-bit fixed-point values with the
 *     bit between bits 14 and 15
 *   trig
 *   - a pointer to either the C cosine or C sine functions
 * Outputs
 * -------
 *   table
 *   - a table of 8 trigonometric DTMF tones and 1 silence tone
 * Return Values
 * ------ ------
 *     TRUE  - the DTMF trigonometric tones have been created, table is valid
 *     FALSE - table is invalid, some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean DTMFTableGen( int table[ ], unsigned int samplingRate, unsigned int shift, double( *trig )( double ) )
{
	unsigned int	i ;
	double			theta ;
	
	if( ( !table ) || ( samplingRate == 0 ) || ( !trig ) ) {
		fprintf( stderr, "[DTMFTableGen] Error in input arguments, aborting.\n\n" ) ;
		return FALSE ;
	}
	
	for( i = 0 ; i < 8 ; i += 1 ) {
		theta = ( 2.0 * PI * ( double )DTMFTones[ i ] )/( double )samplingRate ;
		table[ i ] = ( int )( ( *trig )( theta )*( ( double )( ( int )( 1 << shift ) ) ) ) ;
	}
	table[ 8 ] = 0 ;	/* add silence as last entry */
	
	return TRUE ;
}

/**** DTMFValid *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine if the given string of DTMF tones is valid in that it only contains
 * 0-9, a-d (or A-D), * and #
 *
 * all other values are unacceptable and a list of any unacceptable values are given
 * to the user
 *
 * Inputs
 * ------
 *   dtmfValues
 *   - a string of DTMF values to check for validity
 *   nValues
 *   - the number of DTMF values to check in the string from starting address given
 * Return Values
 * ------ ------
 *     TRUE  - the DTMF values are valid
 *     FALSE - some, or all, of the DTMF values are incorrect... reject the set
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean DTMFValid( unsigned char dtmfValues[ ], unsigned int nValues )
{
	Boolean			valid = TRUE ;
	unsigned char	dataarea[ 256 ] = "" ;
	unsigned char	*invalids = dataarea ;
	unsigned int	nInvalids = 0 ;
	unsigned int	i ;
	
	for( i = 0 ; i < nValues ; i += 1 ) {
		switch( dtmfValues[ i ] ) {
			case '#' :
			case '*' :
			case '0' :
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
			case '8' :
			case '9' :
			case 'A' :
			case 'B' :
			case 'C' :
			case 'D' :
			case 'a' :
			case 'b' :
			case 'c' :
			case 'd' :
				break ;
			default :
				/* only include value once and alphabetically */
				if( !invalids[ dtmfValues[ i ] ] ) {
					nInvalids += 1 ;
					invalids[ dtmfValues[ i ] ] = dtmfValues[ i ] ;
				}
				
				valid = FALSE ;
				break ;
		}
	}
	
	/* print all invalid DTMF values given in a "case sensitive" way */
	if( !valid ) {
		i = 0 ;
		if( nInvalids > 1 ) {
			while( i < nInvalids - 2 ) {
				while( !*invalids ) {
					invalids += 1 ;
				}
				printf( "'%c', ", *invalids++ ) ;
				i += 1 ;
			}
			while( !*invalids ) {
				invalids += 1 ;
			}
			printf( "'%c' and ", *invalids++ ) ;
		}
		while( !*invalids ) {
			invalids += 1 ;
		}
		printf( "'%c' ", *invalids++ ) ;
		if( nInvalids > 1 ) {
			printf( "are not" ) ;
		}
		else {
			printf( "is not a" ) ;
		}
		printf( " valid DTMF value" ) ;
		if( nInvalids > 1 ) {
			printf( "s" ) ;
		}
		printf( ".\n\n" ) ;
	}	
	
	return valid ;
}

/**** GenerateDTMFForValue **********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a set of discrete samples from the waveform to represent the DTMF tone for
 * given value or silence
 *
 * Inputs
 * ------
 *   value
 *   - a character value from the set 0-9, a-d (or A-D), * and # to generate DTMF samples for
 *     or 0 if silence should be generated
 *   dtmfToneGenStructPtr
 *   - a pointer to an initialised DTMFToneGenStruct that contains values to use
 *   noise
 *   - TRUE  : add random noise to generated samples
 *     FALSE : do not add noise to generated samples
 *   samples
 *   - an array to hold the discrete samples of the waveform generated
 * Outputs
 * -------
 *   samples
 *   - the discrete samples generated if non-NULL returned
 * Return Values
 * ------ ------
 *     short * - a pointer to the next location in the array 'samples' after the last generated sample
 *     NULL    - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static short *GenerateDTMFForValue( unsigned char value, DTMFToneGenStructPtr dtmfToneGenStructPtr, Boolean noise, short samples[ ] )
{
	short			*outputs = samples ;
	unsigned int	nSGenerate = 0 ;
	ToneState		toneStates[ 2 ] ;
	unsigned int	samplesRemaining = 0 ;
	unsigned int	period ;
	
	if(	( !dtmfToneGenStructPtr ) || ( dtmfToneGenStructPtr->framesize == 0 ) || ( !samples ) ) {
		fprintf( stderr, "[GenerateDTMFForTone] Error in input arguments, aborting.\n\n" ) ;
		return NULL ;
	}
	
	value = ( unsigned char )toupper( value ) ;
	
	printf( "\t" ) ;
	if( value ) {
		printf( "'%c'", value ) ;
	}
	else {
		printf( "silence" ) ;
	}
	printf( "\n" ) ;
	
	period = dtmfToneGenStructPtr->period ;
	SetDTMFTones( toneStates, value, dtmfToneGenStructPtr->lotonelevel, dtmfToneGenStructPtr->hitonelevel, noise ) ;
	while( period ) {
		if( samplesRemaining == 0 ) {
			samplesRemaining = dtmfToneGenStructPtr->framesize ;
		}
		
		if( period < samplesRemaining ) {
			nSGenerate = period ;
		}
		else {
			nSGenerate = samplesRemaining ;
		}
		if( ( outputs = ToneGenerate( outputs, nSGenerate, toneStates, 2 ) ) == NULL ) {
			return NULL ;
		}
		
		samplesRemaining -= nSGenerate ;
		period -= nSGenerate ;
	}
	
	return outputs ;
}

/**** GenerateDTMFSamples ***********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a set of discrete samples from the waveforms to represent the DTMF tones for
 * given values and silence between each DTMF tone
 *
 * Inputs
 * ------
 *   values
 *   - an array of character values from the set 0-9, a-d (or A-D), * and # to generate DTMF samples for
 *     silence will be generated after each tone
 *   nValues
 *   - the number of values to generate DTMF tones from
 *   dtmfToneGenStructPtr
 *   - a pointer to an initialised DTMFToneGenStruct that contains values to use
 *   noise
 *   - TRUE  : add random noise to generated samples
 *     FALSE : do not add noise to generated samples
 *   samples
 *   - an array to hold the discrete samples of the waveforms generated
 *   nSamples
 *   - a pointer to integer to hold the number of samples generated
 * Outputs
 * -------
 *   samples
 *   - the discrete samples generated if non-NULL returned
 *   nSamples
 *   - a pointer to the number of samples generated if non-NULL generated
 * Return Values
 * ------ ------
 *     short * - a pointer to the next location in the array 'samples' after the last generated sample
 *     NULL    - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static short *GenerateDTMFSamples( unsigned char values[ ], unsigned int nValues, DTMFToneGenStructPtr dtmfToneGenStructPtr, Boolean noise, short samples[ ], unsigned int *nSamples )
{
	short			*outputs = samples ;
	unsigned int	i ;
	
	if(	( !dtmfToneGenStructPtr ) || 
		( ( dtmfToneGenStructPtr->toneperiod == 0 ) && ( dtmfToneGenStructPtr->silenceperiod == 0 ) ) || 
		( !nSamples ) 
		) {
		fprintf( stderr, "[GenDTMFSamples] Error in input arguments, aborting.\n\n" ) ;
		return NULL ;
	}
	
	printf( "Generating DTMF samples " ) ;
	if( noise ) {
		printf( "(with noise) " ) ;
	}
	printf( "for :\n\n" ) ;
	
	*nSamples = 0 ;
	for( i = 0 ; i < nValues ; i += 1 ) {	/* for each value, generate tone followed by silence */
		dtmfToneGenStructPtr->period = dtmfToneGenStructPtr->toneperiod ;
		if( ( outputs = GenerateDTMFForValue( values[ i ], dtmfToneGenStructPtr, noise, outputs ) ) == NULL ) {
			return NULL ;
		}
		
		dtmfToneGenStructPtr->period = dtmfToneGenStructPtr->silenceperiod ;
		if( ( outputs = GenerateDTMFForValue( 0, dtmfToneGenStructPtr, noise, outputs ) ) == NULL ) {
			return NULL ;
		}
		
		*nSamples += dtmfToneGenStructPtr->toneperiod + dtmfToneGenStructPtr->silenceperiod ;
	}
	
	printf( "\nDTMF samples generated.\n\n" ) ;
	
	return outputs ;
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
	if( numberOptions == DTMF_OPTIONS ) {
		printf( " 1. Generate DTMF.\n" ) ;
		printf( " 2. Detect DTMF.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PrintNumberPad ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the DTMF value number pad to the screen
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void PrintNumberPad( void )
{
	printf( "\t ___ \t ___ \t ___ \t ___\n" ) ;
	printf( "\t| 1 |\t| 2 |\t| 3 |\t| A |\n" ) ;
	printf( "\n" ) ;
	printf( "\t ___ \t ___ \t ___ \t ___\n" ) ;
	printf( "\t| 4 |\t| 5 |\t| 6 |\t| B |\n" ) ;
	printf( "\n" ) ;
	printf( "\t ___ \t ___ \t ___ \t ___\n" ) ;
	printf( "\t| 7 |\t| 8 |\t| 9 |\t| C |\n" ) ;
	printf( "\n" ) ;
	printf( "\t ___ \t ___ \t ___ \t ___\n" ) ;
	printf( "\t| * |\t| 0 |\t| # |\t| D |\n" ) ;
	printf( "\n" ) ;
	printf( "\n" ) ;
}

/**** SetDTMFTones ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a set of discrete samples from the waveforms to represent the DTMF tones for
 * given values and silence between each DTMF tone
 *
 * Inputs
 * ------
 *   toneStates
 *   - an array of two ToneState structures to initialise for the two tones of the DTMF value
 *   value
 *   - a character value from the set 0-9, a-d (or A-D), * and # to generate DTMF samples for
 *     or 0 if silence should be generated
 *   lotonelevel
 *   - the peak value for the low tone of the DTMF value
 *   hitonelevel
 *   - the peak value for the high tone of the DTMF value
 *   noise
 *   - TRUE  : add random noise to tones
 *     FALSE : do not add noise to tones
 * Outputs
 * -------
 *   toneStates
 *   - an array of two initialised ToneState structures for the DTMF tones of the given value
 *     if non-NULL returned
 * Return Values
 * ------ ------
 *     ToneState * - a pointer to the initialised ToneStates
 *     NULL        - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static ToneState *SetDTMFTones( ToneState toneStates[ ], unsigned char value, unsigned int lotonelevel, unsigned int hitonelevel, Boolean noise )
{
	unsigned int	max = ( 1 << SHIFT ) - 1 ;
	unsigned int	lotone ;
	unsigned int	hitone ;
	unsigned int	random ;
	int				cosine ;
	int				sine ;
	
	if( !toneStates ) {
		fprintf( stderr, "[SetDTMFTones] Error in input arguments, aborting.\n\n" ) ;
		return NULL ;
	}

	switch( value ) {
		case '#' :
			lotone = 3 ;							/* 941 */
			hitone = 6 ;							/* 1447 */
			break ;
		case '*' :
			lotone = 3 ;							/* 941 */
			hitone = 4 ;							/* 1209 */
			break ;
		case '0' :
			lotone = 3 ;							/* 941 */
			hitone = 5 ;							/* 1336 */
			break ;
		case '1' :
		case '2' :
		case '3' :
			lotone = 0 ;							/* 697 */
			hitone = value - '1' + 4 ;
			break ;
		case '4' :
		case '5' :
		case '6' :
			lotone = 1 ;							/* 770 */
			hitone = value - '4' + 4 ;
			break ;
		case '7' :
		case '8' :
		case '9' :
			lotone = 2 ;							/* 852 */
			hitone = value - '7' + 4 ;
			break ;
		case 'A' :
		case 'B' :
		case 'C' :
		case 'D' :
		case 'a' :
		case 'b' :
		case 'c' :
		case 'd' :
			lotone = ( value & 0x5F ) - 'A' ;
			hitone = 7 ;							/* 1633 */
			break ;
		default :									/* silence */
			lotone = 8 ;
			hitone = 8 ;
			break ;
	}
	
	random = rand( )%NOISEFACTOR ;
	
	if( noise ) {
		cosine = DTMFCosines[ lotone ] + random ;
		if( cosine > max ) {
			cosine = max ;
		}
		sine = DTMFSines[ lotone ] + random ;
		if( sine > max ) {
			sine = max ;
		}
	}
	else {
		cosine = DTMFCosines[ lotone ] ;
		sine = DTMFSines[ lotone ] ;
	}
	ToneGenerateSetup( toneStates, cosine, sine, lotonelevel ) ;
	
	if( noise ) {
		cosine = DTMFCosines[ hitone ] + random ;
		if( cosine > max ) {
			cosine = max ;
		}
		sine = DTMFSines[ hitone ] + random ;
		if( sine > max ) {
			sine = max ;
		}
	}
	else {
		cosine = DTMFCosines[ hitone ] ;
		sine = DTMFSines[ hitone ] ;
	}
	ToneGenerateSetup( toneStates + 1, cosine, sine, hitonelevel ) ;

	return toneStates ;
}
