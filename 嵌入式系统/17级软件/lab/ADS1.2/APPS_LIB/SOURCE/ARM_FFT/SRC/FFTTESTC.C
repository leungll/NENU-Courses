/*
 * Fast Fourier Transform test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "ffts.h"
#include "fftc.h"
#include "windowc.h"

#include "ffttestc.h"

#include "bitutilc.h"
#include "custredc.h"
#include "datatypc.h"
#include "fileutlc.h"
#include "optionsc.h"
#include "printinc.h"
#include "timingc.h"

#define FFT_OPTIONS	10

#define PIDOFFSET	1
/* result printing adjustment for PID card */
/* for example, set to 4 for an ARM7TDMI PID card or 1 for ARMulator */

static void Menu( unsigned int numberOptions ) ;
static Boolean Transform( unsigned int option ) ;
static Complex *Window( Complex inputs[ ], unsigned int nInputs ) ;

/**** fft_main **********************************************************************
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
int fft_main( int argc, char **argv )
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
	
	printf( "Program to perform Fast Fourier Transform.\n\n" ) ;
	
	printf( "This application provides access to the FFT with input data\n" ) ;
	printf( "in hexadecimal format, each data item being 16-bit with fixed point precision\n" ) ;
	printf( "and the decimal point being between bits 13 and 14 so that dividing the hexadecimal\n" ) ;
	printf( "number by (1 << 14) provides the actual decimal value.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( FFT_OPTIONS, &Menu ) ) == 0 ) {
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

/**** GetComplexData ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the file name from the user and open the file for reading in normal mode, 
 * read in integer data (interleaved real and imaginary parts of complex number )
 * close the file, create complex array and return the complex array created
 *
 * Inputs
 * ------
 *   dataType
 *   - an optional string that defines the data that is to read in
 *     displayed to the user during file selection time
 *     pass NULL if non-specific data is to be read
 *	 size
 *   - a pointer to an integer location to store the number of data points read
 * Outputs
 * -------
 *   size
 *   - the number of complex numbers in the returned array
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     Complex * - an array of complex data read from the file
 *     NULL      - some error occurred, size is not valid
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the array returned
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Complex *GetComplexData( char *dataType, unsigned int *size )
{
	int		*dataInt ;
	Complex	*dataComplex ;

	if( ( dataInt = ( int * )GetData( WORDBYTES, dataType, size ) ) == NULL ) {
		return NULL ;
	}
	
	SIGNEXTENDARRAY( dataInt, *size, 16 ) ;

	dataComplex = CreateComplexFromInt( dataInt, size ) ;
	free( ( void * ) dataInt ) ;
	
	return dataComplex ;	/* may be NULL */
}

/**** HasWindow *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine from the user whether windowing should be done, and if so whether the
 * windowing is Hamming or Hanning and return the option chosen
 *
 * Return Values
 * ------ ------
 *     0   - no windowing is required
 *     1   - perform Hamming window
 *     2   - perform Hanning window
 *     int - anything else, do not perform window, error in user's selection
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int HasWindow( void )
{
	printf( "The FFT can be performed with windowing.\n\n" ) ;
	
	printf( "Perform FFT with...\n\n" ) ;
	
	printf( " 1. Hamming Window\n" ) ;
	printf( " 2. Hanning Window\n" ) ;
	printf( "\n" ) ;
	printf( " 0. No window (standard FFT)\n" ) ;
	printf( "\n" ) ;
	printf( "Please choose 'window' option (0 to 2) : " ) ;
	
	return( int )ReadDouble( ) ;
}

/**** IsInPlace *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine from the user whether the ARM FFT should be performed in place or out
 * of place and return the choice
 *
 * Return Values
 * ------ ------
 *     TRUE  - perform in place
 *     FALSE - perform out of place (either user chosen or error in choice)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean IsInPlace( void )
{
	char	inPlaceString[ 2 ] ;
	
	printf( "If the input and output data buffers coincide\n" ) ;
	printf( "(i.e. reference the same block of memory), the FFT\n" ) ;
	printf( "is said to be performed 'in place'.  If they reference\n" ) ;
	printf( "different blocks of memory it is said to be 'out of place'.\n\n" ) ;
	
	printf( "Perform the ARM Assembler FFT 'in place'?\n\n" ) ;
	
	printf( "In place (y or n) : " ) ;
	ReadInString( stdin, inPlaceString, 2 ) ;
	printf( "\n" ) ;
	
	switch( inPlaceString[ 0 ] ) {
		case 'y' :
			printf( "The FFT will be performed 'in place'.\n\n" ) ;
			return TRUE ;
		case 'n' :
			printf( "The FFT will be performed 'out of place'.\n\n" ) ;
			return FALSE ;
		default :
			printf( "That was not a valid choice, FFT will be performed 'out of place'.\n\n" ) ;
			return FALSE ;
	}
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
	if( numberOptions == FFT_OPTIONS ) {
		printf( " 1. Forward ARM Assembler FFT\n" ) ;
		printf( " 2. Forward C FFT\n" ) ;
		printf( " 3. Inverse ARM Assembler FFT\n" ) ;
		printf( " 4. Inverse C FFT\n" ) ;
		printf( "\n" ) ;
		printf( " 5. Forward ARM Assembler FFT followed by inverse ARM Assembler FFT.\n" ) ;
		printf( " 6. Forward C FFT followed by inverse C FFT.\n" ) ;
		printf( " 7. Forward ARM Assembler FFT followed by inverse C FFT.\n" ) ;
		printf( " 8. Forward C FFT followed by inverse ARM Assembler FFT.\n" ) ;
		printf( "\n" ) ;
		printf( " 9: Real forward ARM Assembler FFT\n" ) ;
		printf( "10: Real forward C FFT\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PerformARMFFTs ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform either a forward or inverse FFT on the data given using ARM routines where
 * the data can be either an array of complex or real integers
 *
 * the data should have been windowed as appropriate before passing here
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised complex array that should reference as many complex points as
 *     there are in the complex data given or half the number of points as there are
 *     in the inputs if the data is real
 *   inputs
 *   - an array of either complex data or real integer data to be FFT'd
 *   nInputs
 *   - the number of data points (complex or integer) in the array inputs
 *     the value must be power of 2 else the FFT will be incomplete
 *   forward
 *   - TRUE  : forward FFT the given data
 *     FALSE : inverse FFT the given data
 *   real
 *   - TRUE  : the input data is an array of real integers and the real routines 
 *             will be used
 *             forward must be TRUE else will abort
 *     FALSE : the input data is complex and complex routines are used
 * Outputs
 * -------
 *   outputs
 *   - the complex result of the FFT
 *     contains nInputs data points if inputs is complex
 *     contains nInputs/2 data points if inputs is real
 *     outputs is undefined if FALSE returned (see Return Values)
 * Return Values
 * ------ ------
 *     TRUE  - FFT performed successfully, outputs is valid
 *     FALSE - FFT failed, outputs is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformARMFFTs( Complex outputs[ ], void *inputs, unsigned int nInputs, Boolean forward, Boolean real )
{
	unsigned int	maxBit ;
	unsigned int	outCounter ;
	
	if( ( !outputs ) || ( !inputs ) || ( !forward & real ) ) {
		fprintf( stderr, "[PerformARMFFTs] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}

	MAXBITSET( ( int )nInputs, maxBit ) ;
	if( real ) {
		REALFFT( ( int * )inputs, outputs, maxBit ) ;
	}
	else {
		if( FFT( ( Complex * )inputs, outputs, maxBit, forward ) != 0 ) {
			fprintf( stderr, "FFT trigonometry table is not large enough for size of input data.\n\n" ) ;
			fprintf( stderr, "Regenerate the trigonometry table and re-assemble the FFT.\n\n" ) ;
			return FALSE ;
		}
	
		if( !forward ) {
			for( outCounter = 0 ; outCounter < nInputs ; outCounter += 1 ) {
				outputs[ outCounter ].r *= nInputs ;
				outputs[ outCounter ].i *= nInputs ;
			}
		}
	}
	
	return TRUE ;
}

/**** PerformCFFTs ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform either a forward or inverse FFT on the data given using C routines where
 * the data can be either an array of complex or real integers
 *
 * timing information is provided to the user to inform them of the progress
 *
 * the data should have been windowed as appropriate before passing here
 *
 * Inputs
 * ------
 *   outputs
 *   - an initialised complex array that should reference as many complex points as
 *     there are in the complex data given or half the number of points as there are
 *     in the inputs if the data is real
 *   inputs
 *   - an array of either complex data or real integer data to be FFT'd
 *   nInputs
 *   - the number of data points (complex or integer) in the array inputs
 *   forward
 *   - TRUE  : forward FFT the given data
 *     FALSE : inverse FFT the given data
 *   real
 *   - TRUE  : the input data is an array of real integers and the real routines 
 *             will be used
 *             forward must be TRUE else will abort
 *     FALSE : the input data is complex and complex routines are used
 * Outputs
 * -------
 *   outputs
 *   - the complex result of the FFT
 *     contains nInputs data points if inputs is complex
 *     contains nInputs/2 data points if inputs is real
 *     outputs is undefined if FALSE returned (see Return Values)
 * Return Values
 * ------ ------
 *     TRUE  - FFT performed successfully, outputs is valid
 *     FALSE - FFT failed, outputs is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean PerformCFFTs( Complex outputs[ ], void *inputs, unsigned int nInputs, Boolean forward, Boolean real )
{
	unsigned int	nOutputs = nInputs ;
	unsigned int	itersPerLoop = 1024*PIDOFFSET ;
	unsigned int	iterations = 0 ;
	TimeStruct		timeStruct ;
	unsigned int	outCounter ;
	
	if( ( !outputs ) || ( !inputs ) || ( !forward & real ) ) {
		fprintf( stderr, "[PerformCFFTs] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}
	
	InitialiseTimeStructure( &timeStruct ) ;

	if( real ) {
		nOutputs /= 2 ;
		itersPerLoop /= 2 ;
	}
	
	for( outCounter = 0 ; outCounter < nOutputs ; outCounter += 1 ) {
		if( !FFTC( inputs, nInputs, real, forward, outCounter, &outputs[ outCounter ] ) ) {
			return FALSE ;
		}
		if( ( iterations > 0 ) && ( iterations%itersPerLoop == 0 ) ) {
			PrintIterationTimes( ( nOutputs - outCounter )* nOutputs, itersPerLoop, &timeStruct ) ;
		}
		iterations += nOutputs ;
	}
	printf( "\n" ) ;
		
	return TRUE ;
}

/**** PerformFFT ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform either a forward or inverse FFT on the data given using either ARM or C
 * routines giving the user choices for windowing (if complex) and performing 
 * the FFT in place or out of place (if using the ARM routines)
 *
 * Inputs
 * ------
 *   inputs
 *   - an array of complex data to be FFT'd
 *   nInputs
 *   - the number of complex data points in the array inputs
 *   arm
 *   - TRUE  : use ARM Assembler routines to perform FFT (has in place option)
 *     FALSE : use C routines to perform FFT (no in place option)
 *   forward
 *   - TRUE  : forward FFT the given data
 *     FALSE : inverse FFT the given data
 *   real
 *   - TRUE  : the complex data is actually all real (zero imaginary part) and
 *             the real routines will be used
 *             forward must be TRUE else will abort
 *     FALSE : the complex data really is complex and complex routines are used
 * Return Values
 * ------ ------
 *     Complex * - an array of nInputs complex data points result of FFT
 *     NULL      - some error occurred (memory allocation?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned Complex array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Complex *PerformFFT( Complex inputs[ ], unsigned int nInputs, Boolean arm, Boolean forward, Boolean real )
{
	int				*inputsInt = NULL ;
	Complex			*windowInputs = NULL ;
	Complex			*outputs ;
	unsigned int	outCounter ;
	void			*inputID ;
	Complex			*outputID ;
	Boolean			inPlace ;
	
	if( ( !inputs ) || ( !forward && real ) ) {
		fprintf( stderr, "[PerformFFT] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( outputs = ( Complex * )calloc( nInputs, sizeof( Complex ) ) ) == NULL ) {
		fprintf( stderr, "Failure to create array for output data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	inputID = inputs ;
	if( ( forward ) && ( !real ) ) {
		if( ( windowInputs = Window( inputs, nInputs ) ) != NULL ) {
			inputID = windowInputs ;
		}
	}
	
	if( real ) {
		if( ( inputsInt = CreateIntFromComplex( inputs, &nInputs ) ) == NULL ) {
			fprintf( stderr, "Failure to create array for FFT, aborting.\n\n" ) ;
			free( ( void * ) outputs ) ;
			return NULL ;
		}
		inputID = inputsInt ;
	}
	
	printf( "Calculating the " ) ;
	if( real ) {
		printf( "real " ) ;
	}
	if( forward ) {
		printf( "forward FFT " ) ;
	}
	else {
		printf( "inverse FFT " ) ;
	}
	if( arm ) { 
		printf( "(ARM-based)" ) ; 
	} 
	else { 
		printf( "(C-based)" ) ; 
	}
	printf( "...\n\n" ) ;

	if( arm ) {
		inputID = inputs ;
		outputID = outputs ;
		if( real ) {
			inputID = inputsInt ;
			nInputs /= 2 ;
			inPlace = FALSE ;
		}
		else if( ( inPlace = IsInPlace( ) ) == TRUE ) {
			outputID = inputs ;
		}
		
		if( !PerformARMFFTs( outputID, inputID, nInputs, forward, real ) ) {
			free( ( void * ) outputs ) ;
			outputs = NULL ;
		}
		else if( inPlace ) {
			for( outCounter = 0 ; outCounter < nInputs; outCounter += 1 ) {
				outputs[ outCounter ].r = inputs[ outCounter ].r ;
				outputs[ outCounter ].i = inputs[ outCounter ].i ;
			}
		}
	}
	else {
		inputID = inputs ;
		if( real ) {
			inputID = inputsInt ;
		}
		
		if( !PerformCFFTs( outputs, inputID, nInputs, forward, real ) ) {
			free( ( void * ) outputs ) ;
			outputs = NULL ;
		}
	}
	
	if( real ) {
		free( ( void * ) inputsInt ) ;
	}
	else if( windowInputs != NULL ) {
		free( ( void * ) windowInputs ) ;
	}

	if( outputs != NULL ) {
		if( real ) {
			printf( "Real " ) ;
		}
		printf( "FFT calculated.\n\n" ) ;
	}

	return outputs ;
}

/**** SaveComplexData ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the file name from the user and open the file for writing in normal mode, 
 * remove the sign extension from the data, write the complex data as integers 
 * (interleaved real and imaginary parts) and close the file
 *
 * Inputs
 * ------
 *   dataComplex
 *   - an array of complex data to write to the file
 *   size
 *   - the number of complex data points in the array passed
 *   dataType
 *   - an optional string that defines the data that is to written out
 *     displayed to the user during file selection time
 *     pass NULL if non-specific data is to be written
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void SaveComplexData( Complex dataComplex[ ], unsigned int size, char *dataType )
{
	int		*dataInt ;

	if( ( dataInt = CreateIntFromComplex( dataComplex, &size ) ) == NULL ) {
		return ;
	}
	
	REMOVESIGNEXTENDARRAY( dataInt, size, 16 ) ;
	
	SaveData( dataInt, size, WORDBYTES, 0, dataType ) ;
	
	free( ( void * ) dataInt ) ;
}

/**** Transform *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform the coding from reading the users data in to performing the forward FFT,
 * inverse FFT or both forward FFT immediately followed by the inverse FFT, 
 * and write the data back to a users file
 *
 * all files are given by the user during the operations at run time
 *
 * Inputs
 * ------
 *   option
 *   - the coding option being performed : when to use ARM or C routines and if
 *     inverting immediately
 * Return Values
 * ------ ------
 *     TRUE  - the coding operation and all file operations were successful
 *     FALSE - some error occurred, operations failed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Transform( unsigned int option )
{
	Complex			*inputs ;
	unsigned int	nInputs ;
	unsigned int	is2 ;
	Complex			*outputs = NULL ;
	Boolean			arm ;
	Boolean			forward ;
	Boolean			real ;
	
	printf( "Perform Fast Fourier Transform...\n\n" ) ;
	
	if( ( inputs = GetComplexData( "input", &nInputs ) ) == NULL ) {
		return FALSE ;
	}
	
	ISPOWEROF2( nInputs, is2 ) ;
	if( !is2 ) {
		printf( "The number of inputs to the FFT must a multiple of 2 (given '%d'), aborting.\n\n", nInputs ) ;
		free( ( void * ) inputs ) ;
		return FALSE ;
	}
	
	switch( option ) {
		case  1 :
			arm = TRUE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  2 :
			arm = FALSE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  3 :
			arm = TRUE ;
			forward = FALSE ;
			real = FALSE ;
			break ;
		case  4 :
			arm = FALSE ;
			forward = FALSE ;
			real = FALSE ;
			break ;
		case  5 :
			arm = TRUE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  6 :
			arm = FALSE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  7 :
			arm = TRUE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  8 :
			arm = FALSE ;
			forward = TRUE ;
			real = FALSE ;
			break ;
		case  9 :
			arm = TRUE ;
			forward = TRUE ;
			real = TRUE ;
			break ;
		case 10 :
			arm = FALSE ;
			forward = TRUE ;
			real = TRUE ;
			break ;
		default :
			free( ( void * ) inputs ) ;
			return FALSE ;
	}

	if( ( option == 9 ) || ( option == 10 ) ) {
		printf( "Number of inputs to FFT is '%d'\n\n", nInputs*2 ) ;
	}
	else {
		printf( "Number of inputs to FFT is '%d'\n\n", nInputs ) ;
	}
	
	outputs = PerformFFT( inputs, nInputs, arm, forward, real ) ;
	free( ( void * ) inputs ) ;
	if( !outputs ) {
		return FALSE ;
	}
	
	if( ( option >= 5 ) && ( option <= 8 ) ) {
		switch( option ) {
			case 5 :
				arm = TRUE ;
				forward = FALSE ;
				real = FALSE ;
				break ;
			case 6 :
				arm = FALSE ;
				forward = FALSE ;
				real = FALSE ;
				break ;
			case 7 :
				arm = FALSE ;
				forward = FALSE ;
				real = FALSE ;
				break ;
			case 8 :
				arm = TRUE ;
				forward = FALSE ;
				real = FALSE ;
				break ;
		}
		inputs = PerformFFT( outputs, nInputs, arm, forward, real ) ;
	}
	
	switch( option ) {
		case  1 :
		case  2 :
		case  3 :
		case  4 :
		case  9 :
		case 10 :
			SaveComplexData( outputs, nInputs, "output" ) ;
			free( ( void * ) outputs ) ;
			break ;
		case  5 :
		case  6 :
		case  7 :
		case  8 :
			if( !inputs ) {
				return FALSE ;
			}
			SaveComplexData( inputs, nInputs, "fully transformed" ) ;
			free( ( void * ) inputs ) ;
			break ;
		default :
			break ;
	}
	
	return TRUE ;
}

/**** Window ************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine from the user whether windowing should be done, and if so whether the
 * windowing is Hamming or Hanning
 *
 * if windowing is required, perform the window on the given data and return the
 * windowed data
 *
 * if no windowing is required NULL is returned
 *
 * Inputs
 * ------
 *   inputs
 *   - a complex array containing the data before FFT performed that may have a
 *     window applied to it
 *   nInputs
 *   - the number of complex data points in the array inputs
 * Return Values
 * ------ ------
 *     Complex * - the complex data after a window has been applied
 *     NULL      - no window was required by the user or some error occurred
 *                 (no test for error possible, just assume no window)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the return Complex array, if not NULL
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Complex *Window( Complex inputs[ ], unsigned int nInputs )
{
	Complex			*windowInputs = NULL ;
	unsigned int	window ;
	int				*inputsInt ;
	
	if( !inputs ) {
		fprintf( stderr, "[Window] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	switch( window = HasWindow( ) ) {
		case 0 :
			printf( "No windowing will be performed.\n\n" ) ;
			break ;
		case 1 :
		case 2 :
			if( ( inputsInt = CreateIntFromComplex( inputs, &nInputs ) ) == NULL ) {
				fprintf( stderr, "Failure to create array for windowing.\n" ) ;
				fprintf( stderr, "Unable to perform windowing, aborting.\n\n" ) ;
				break ;
			}
			
			if( window == 1 ) {
				printf( "FFT with Hamming Window.\n\n" ) ;
				HammingWindow( inputsInt, inputsInt, nInputs ) ;
			}
			else {
				printf( "FFT with Hanning Window.\n\n" ) ;
				HanningWindow( inputsInt, inputsInt, nInputs ) ;
			}
			
			windowInputs = CreateComplexFromInt( inputsInt, &nInputs ) ;
			free( ( void * ) inputsInt ) ;
			if( !windowInputs ) {
				fprintf( stderr, "Failure to create array for windowing.\n" ) ;
				fprintf( stderr, "Unable to perform windowing, aborting.\n\n" ) ;
			}
			break ;
		default :
			printf( "That was not a valid choice, no windowing will be performed.\n\n" ) ;
			break ;
	}
	
	return windowInputs ;
}