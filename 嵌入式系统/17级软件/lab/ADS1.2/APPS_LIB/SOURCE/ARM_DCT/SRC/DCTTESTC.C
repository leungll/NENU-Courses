/*
 * Discrete Cosine Transform test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <time.h>

#include "dctc.h"
#include "dcts.h"

#include "dcttestc.h"

#include "arrayc.h"
#include "custredc.h"
#include "errorc.h"
#include "fileutlc.h"
#include "optionsc.h"
#include "pgmc.h"
#include "printinc.h"
#include "timingc.h"

#define	DCT_OPTIONS	6

#define PIDOFFSET	1
/* result printing adjustment for PID card */
/* for example, set to 4 for an ARM7TDMI PID card or 1 for ARMulator */

/* define global variables ('g' prefix) for user options */
static char gStatus[ LIMIT ] = "1" ;
static char gResults[ LIMIT ] = "1" ;

static unsigned int GetN( unsigned int width, unsigned int height ) ;
static unsigned int GetNumberBlocks( unsigned int N ) ;
static void Menu( unsigned int numberOptions ) ;
static void PerformOption( unsigned int option ) ;
static int SetMaxXYPosition( IArray iArray, unsigned int N, unsigned int *x, unsigned int *y ) ;
static Boolean Transform( IArray outIArray, IArray inIArray, unsigned int N, unsigned int numberBlocks, Boolean arm, Boolean forward ) ;


/**** Codec *************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * perform the entire coding image from reading the users image in to performing both
 * the forward dct immediately followed by the inverse dct, write the fully transformed
 * image back to a users file, calculate error information and write an error image to
 * to the users file
 *
 * all files are given by the user during the operations at run time
 *
 * a set of image data is printed to the screen after coding to show the results if
 * the global option for users results printing has been set (the block printed is that
 * which contains the maximum DCT value
 *
 * Inputs
 * ------
 *   option
 *   - the coding option being performed (when to use ARM or C routines)
 *   pgmReadString
 *   - an optional string containing the operation that is be performed on the image
 *     to be non-specific pass NULL
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
static Boolean Codec( unsigned int option, char *pgmReadString )
{
	UCArray			charIn ;
	unsigned int	width ;
	unsigned int	height ;
	unsigned int	N ;
	IArray			inIArray ;
	IArray			dctIArray ;
	IArray			idctIArray ;
	UCArray			charOut ;
	IArray			errIArray ;
	UCArray			charError ;
	unsigned int	i, j ;
	unsigned int	x, y ;
	unsigned int	procBeforeCoding ;
	unsigned int	procAfterCoding ;
	unsigned int	procTimeCoding ;
	unsigned int	procBeforeDecoding ;
	unsigned int	procAfterDecoding ;
	unsigned int	procTimeDecoding ;
	unsigned int	hrs, mins, secs ;
	Boolean			arm ;
	int				iCharOut ;
	unsigned int	maxAbsErr ;
	unsigned int	mse ;
	unsigned int	numberBlocks ;
	
	if( ( charIn = ReadPGM( pgmReadString, &width, &height ) ) == NULL ) {
		return FALSE ;
	}
	
	if( ( N = GetN( width, height ) ) == 0 ) {
		FreeUCArray( charIn, N ) ;
		return FALSE ;
	}
	
	inIArray = MakeIArray( N, N ) ;
	dctIArray = MakeIArray( N, N ) ;
	idctIArray = MakeIArray( N, N ) ;
	charOut = MakeUCArray( N, N ) ;
	errIArray = MakeIArray( N, N ) ;
	charError = MakeUCArray( N, N ) ;
	
	if( ( !inIArray ) || 
	    ( !dctIArray ) ||
	    ( !idctIArray ) ||
	    ( !charOut ) ||
	    ( !errIArray ) ||
	    ( !charError ) ) {
	    /* FreeXArray aborts correctly if NULL, so just pass on and let FreeXArray check */
	    FreeUCArray( charIn, N ) ;
		FreeIArray( inIArray, N ) ;
		FreeIArray( dctIArray, N ) ;
		FreeIArray( idctIArray, N ) ;
		FreeUCArray( charOut, N ) ;
		FreeIArray( errIArray, N ) ;
		FreeUCArray( charError, N ) ;
		return FALSE ;
	}
	
	for( j = 0; j < N; j += 1 ) {
		for( i = 0; i < N; i += 1 ) {
			inIArray[ j ][ i ] = ( int )charIn[ j ][ i ] ;
		}
	}
	
	switch( option ) {
		case 2 :
		case 3 :
		case 4 :
			numberBlocks = GetNumberBlocks( N ) ;
			break ;
		default :
			numberBlocks = 1 ;
			break ;
	}
	
	printf( "Coding the image.\n\n" ) ;
			
	switch( option ) {
		case 2 :
		case 4 :
			arm = TRUE ;
			break ;
		case 1 :
		case 3 :
		default :
			arm = FALSE ;
			break ;
	}

	procBeforeCoding = clock( )/CLOCKS_PER_SEC ;
	/* important that the clock retrieval is done either side of transformation so
	   that most accurate clock for actual coding is obtained */
			
	if( !Transform( dctIArray, inIArray, N, numberBlocks, arm, TRUE ) ) {
		FreeUCArray( charIn, N ) ;
		FreeIArray( inIArray, N ) ;
		FreeIArray( dctIArray, N ) ;
		FreeIArray( idctIArray, N ) ;
		FreeUCArray( charOut, N ) ;
		FreeIArray( errIArray, N ) ;
		FreeUCArray( charError, N ) ;
		return FALSE ;
	}
	
	procAfterCoding = clock( )/CLOCKS_PER_SEC ;
	
	SetMaxXYPosition( dctIArray, N, &x, &y ) ;
	if( gResults[ 0 ] == '1' ) {
		printf( "Position of maximum value in DCT array is (%d, %d)\n\n", x, y ) ;
	}
	x -= x%BLOCKSIZE ;	/* want top left corner of block containing max */
	y -= y%BLOCKSIZE ;
	
	printf( "Decoding the image.\n\n" ) ;

	switch( option ) {
		case 2 :
		case 3 :
			arm = TRUE ;
			break ;
		case 1 :
		case 4 :
		default :
			arm = FALSE ;
			break ;
	}

	procBeforeDecoding = clock( )/CLOCKS_PER_SEC ;
	
	if( !Transform( idctIArray, dctIArray, N, numberBlocks, arm, FALSE ) ) {
		FreeUCArray( charIn, N ) ;
		FreeIArray( inIArray, N ) ;
		FreeIArray( dctIArray, N ) ;
		FreeIArray( idctIArray, N ) ;
		FreeUCArray( charOut, N ) ;
		FreeIArray( errIArray, N ) ;
		FreeUCArray( charError, N ) ;
		return FALSE ;
	}
	
	procAfterDecoding = clock( )/CLOCKS_PER_SEC ;
	
	if( procBeforeCoding != -1 ) {	/* clock not available if -1 */
		procTimeCoding = procAfterCoding - procBeforeCoding ;
		GetHrsMinsSecs( procTimeCoding, &hrs, &mins, &secs ) ;
		printf( "The time to code the image was %d hrs %d mins %d secs\n\n", hrs, mins, secs ) ;
		
		procTimeDecoding = procAfterDecoding - procBeforeDecoding ;
		GetHrsMinsSecs( procTimeDecoding, &hrs, &mins, &secs ) ;
		printf( "The time to decode the image was %d hrs %d mins %d secs\n\n", hrs, mins, secs ) ;
		
		GetHrsMinsSecs( procTimeCoding + procTimeDecoding, &hrs, &mins, &secs ) ;
		printf( "The total time to code/decode the image was %d hrs %d mins %d secs\n\n", hrs, mins, secs ) ;
	}

	for( j = 0 ; j < N ; j += 1 ) {
		for( i = 0 ; i < N ; i += 1 ) {
			iCharOut = idctIArray[ j ][ i ] ;
			if( iCharOut < 0 ) {
				iCharOut = 0 ;
			}
			else if( iCharOut > 255 ) {
				iCharOut = 255 ;
			}
			charOut[ j ][ i ] = ( unsigned char )iCharOut ;
		}
	}

	while( !WritePGM( charOut, N, N, "transformed" ) ) ;
	
	ARRAYERROR2D( inIArray, idctIArray, errIArray, N, N, maxAbsErr, mse, int ) ;
	
	printf( "Maximum absolute error value calculated as '%d'\n\n", maxAbsErr ) ;
	printf( "The mean squared error between the original and decoded images is '%d'\n\n", mse ) ;

	if( gResults[ 0 ] == '1' ) {
		printf( "Calculating error image information...\n\n" ) ;
	}
	
	for( j = 0 ; j < N ; j += 1 ) {
		for( i = 0 ; i < N ; i += 1 ) {
			/* move all values to range 0..255 */
			charError[ j ][ i ] = ( unsigned char )( ( int )( ( ( ( float )( abs( errIArray[ j ][ i ] ) ) )/( ( float ) maxAbsErr ) ) * 255.0 ) ) ;
		}
	}

	while( !WritePGM( charError, N, N, "error" ) ) ;
	
	if( gResults[ 0 ] == '1' ) { 
		printf( "The block printouts for each stage refer to the block with DC at (%d, %d).\n", x, y ) ;

		PRINTARRAY2D( charIn, x, BLOCKSIZE, y, BLOCKSIZE, CHA, BLOCKSIZE,
		"The original 'character' image.\nNOTE:  some characters are invisible, one causes the system bell to sound" ) ;

		PRINTARRAY2D( inIArray, x, BLOCKSIZE, y, BLOCKSIZE, INT, BLOCKSIZE, "The 'character' image as 'int's" ) ;

		PRINTARRAY2D( dctIArray, x, BLOCKSIZE, y, BLOCKSIZE, INT, BLOCKSIZE, "The DCT of the 'int' image" ) ;

		PRINTARRAY2D( idctIArray, x, BLOCKSIZE, y, BLOCKSIZE, INT, BLOCKSIZE, "The IDCT image (back to image as 'int's)" ) ;

		PRINTARRAY2D( charOut, x, BLOCKSIZE, y, BLOCKSIZE, CHA, BLOCKSIZE,
		"The final 'character' image.\nNOTE:  some characters are invisible, one causes the system bell to sound" ) ;

		PRINTARRAY2D( charError, x, BLOCKSIZE, y, BLOCKSIZE, CHA, BLOCKSIZE,
		"The 'error' image.\nNOTE:  some characters are invisible, one causes the system bell to sound" ) ;
	}

	FreeUCArray( charIn, N ) ;
	FreeIArray( inIArray, N ) ;
	FreeIArray( dctIArray, N ) ;
	FreeIArray( idctIArray, N ) ;
	FreeUCArray( charOut, N ) ;
	FreeIArray( errIArray, N ) ;
	FreeUCArray( charError, N ) ;

	return TRUE ;
} 

/**** dct_main **********************************************************************
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
int dct_main( int argc, char **argv )
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
	
	printf( "A program to code still images in 'pgm' format.\n\n" ) ;
	
	printf( "The coding operation is carried out using the Discrete Cosine Transform.\n\n" ) ;
	
	printf( "The block size used in the DCT is 8 x 8.\n\n" ) ;
	
	printf( "There are two 'options' available:\n\n" ) ;
	
	printf( "1. Status messages can be given to display the codec's process.\n" ) ;
	printf( "   These identify the current process being performed on the image,\n" ) ;
	printf( "   however, the coding/decoding process will take more time.\n" ) ;
	printf( "2. The block with the maximum DCT value can be used to display results at\n" ) ;
	printf( "   the end of the coding process and how the image has been affected.\n\n" ) ;
	
	printf( "Both these options can be turned on or off, independently and by default they are on.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( DCT_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		PerformOption( option ) ;
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

/**** FDCTFast **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given a set of blocks for forward DCT'ing, construct the structures necessary
 * for the ARM forward DCT, including tranfering the data to the appropriate type,
 * forward DCT the data using the ARM routines and retrieve the data afterwards
 * placing it in the array given
 *
 * Inputs
 * ------
 *   in
 *   - an array of DCTArray entities, each of which contains a block to be DCT'd
 *   out
 *   - an initialised array of DCTArray entries to hold the result of the DCT'ing
 *     the number of entries in the array must be at least the number of entries
 *     referenced by the array in
 *   numberBlocks
 *   - the number of DCTArray entries in the array in and the number of blocks returned
 *     after the function call in out
 * Return Values
 * ------ ------
 *     TRUE  - the coding operation was successful
 *     FALSE - some error occurred (memory allocation?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean FDCTFast( DCTArray in[ ], DCTArray out[ ], unsigned int numberBlocks )
{   
	int				*dctBlockPtr ;
	int				*dctBlock ;
	unsigned int 	x, y ;
 	SCALETABLE		**fdctSTableArrayPtrs ;
 	unsigned int	bCounter ;
 	
 	if( ( !in ) || ( !out ) ) {
		fprintf( stderr, "[FDCTFast] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
 		return FALSE ;
 	}

	CREATEFDCTSTABLEARRAY( fdctSTableArrayPtrs, numberBlocks ) ;
	
	if( !fdctSTableArrayPtrs ) {
		return FALSE ;
	}
	
	CREATEDCTBLOCK( dctBlockPtr, dctBlock, numberBlocks ) ;

	if( !dctBlock ) {
		free( ( void * ) fdctSTableArrayPtrs ) ;
		return FALSE ;
	}

  	for( bCounter = 0 ; bCounter < numberBlocks ; bCounter += 1 ) {
		for( y = 0; y < 8; y += 1 ) {
	    	for( x = 0; x < 8; x += 1 ) {
	    		PREFDCT( dctBlock, in[ bCounter ][ y ][ x ], x, y, bCounter ) ;
			}
		}
	}
	
	fdct_fast( dctBlock, numberBlocks, fdctSTableArrayPtrs ) ;
        
  	for( bCounter = 0 ; bCounter < numberBlocks ; bCounter += 1 ) {
		for( y = 0; y < 8; y += 1 ) {
	    	for( x = 0; x < 8; x += 1 ) {
	    		POSTFDCT( dctBlock, out[ bCounter ][ y ][ x ], x, y, bCounter ) ;
			}
		}
	}

	free( ( void * ) dctBlockPtr ) ;
	free( ( void * ) fdctSTableArrayPtrs ) ;
    
	return TRUE ;           
}

/**** GetN **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * check the width and height given to ensure that they are equal (only square images
 * can be used) and that the dimensions are even numbers and if so return the length
 * of any column or row for N
 *
 * Inputs
 * ------
 *   width
 *   - the width (number of columns) of the image read in
 *   height
 *   - the height (number of rows) of the image read in
 * Return Values
 * ------ ------
 *     unsigned int - the dimension of the image that is both the width and height
 *     0            - the dimensions given are not valid, cannot accept image, abort
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int GetN( unsigned int width, unsigned int height )
{
	if( width != height ) {
		fprintf( stderr, "This implementation of the codec only accepts square images.\n\n" ) ;
		return 0 ;
	}
	else if( width%2 != 0 ) { 
		fprintf( stderr, "This implementation of the codec only accepts images with even dimensions.\n\n" ) ;
		return 0 ;
	}
	
	return width ;
}

/**** GetNumberBlocks ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the user's choice for the number of blocks to perform with each iteration of the
 * ARM DCT routines
 *
 * the returned value will be a multiple of (N*N)/(BLOCKSIZE*BLOCKSIZE) as required
 * by the function Transform
 *
 * Inputs
 * ------
 *   N
 *   - the size of one of the dimensions of the array being worked on (number of rows
 *     or number of columns)
 * Return Values
 * ------ ------
 *     int - the number of blocks given by the user to perform with each iteration of
 *           of the ARM routines
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int GetNumberBlocks( unsigned int N )
{
	unsigned int	totalNoBlocks ;
	unsigned int	numberBlocks ;
	
	printf( "The ARM Assembler routines can perform (I)DCT on any number of blocks with each call.\n\n" ) ;
	
	printf( "The number of blocks, by default, is a multiple of 2 since the functions operate on pairs\n" ) ;
	printf( "of blocks.  The number of blocks specified, however, need not be a multiple of 2, but it must\n" ) ;
	printf( "divide exactly into the total number of blocks that make up an image.\n\n" ) ;
	
	printf( "Please give the number of blocks for the ARM Assembler routines to code at a time.\n\n" ) ;
	
	totalNoBlocks = ( N * N )/( BLOCKSIZE * BLOCKSIZE ) ;
	
	printf( "This number must be a divisor of %d.\n\n", totalNoBlocks ) ;
	
	printf( "Number of blocks: " ) ;
	
	while( ( totalNoBlocks%( numberBlocks = ( int )ReadDouble( ) ) ) != 0 ) {
		printf( "The number given, %d, is not a divisor of %d.\n\n", numberBlocks, totalNoBlocks ) ;
		
		printf( "Please give another number: " ) ;
	}
	
	printf( "The ARM Assembler routines will code using %d blocks at a time.\n\n", numberBlocks ) ;
	
	return numberBlocks ;
}

/**** MakeDCTArrayPtr ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create an array of DCTArray's to hold the data for ARM coding
 *
 * Inputs
 * ------
 *   option
 *   - the number of blocks in the DCTArray (number of entries for array) that will
 *     be coded with each call to ARM routines
 * Return Values
 * ------ ------
 *     DCTArray * - the allocated array with numberBlocks entries
 *     NULL       - an error occurred in allocating the memory
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of DCTArray's
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static DCTArray *MakeDCTArrayPtr( unsigned int numberBlocks )
{
	return( ( DCTArray * )calloc( numberBlocks, sizeof( DCTArray ) ) ) ;
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
	if( numberOptions == DCT_OPTIONS ) {
		printf( " 1. I/DCT transform an image using C functions\n" ) ;
		printf( " 2. I/DCT transform an image using ARM Assembler functions\n" ) ;
		printf( " 3. DCT transform an image using C, IDCT using ARM Assembler\n" ) ;
		printf( " 4. DCT transform an image using ARM Assembler, IDCT using C\n" ) ;
		printf( "\n" ) ;
		printf( " 5. Change 'codec status messages' option\n" ) ;
		printf( " 6. Change 'max block sample output' option\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PerformOption *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * check the option given and perform the correct task accordingly - either code
 * some set of data or change the status of the one of the global options
 *
 * Inputs
 * ------
 *   option
 *   - the option to be performed chosen by the user (returned by NextTask)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void PerformOption( unsigned int option )
{
    switch( option ) {
    	case 1 :
    		Codec( 1, "perform C (I)DCT on" ) ;
    		break ;
        case 2 :
			Codec( 2, "perform ARM Assembler (I)DCT on" ) ;
			break ;
		case 3 :
			Codec( 3, "perform C DCT, ARM Assembler IDCT on" ) ;
			break ;
		case 4 :
			Codec( 4, "perform ARM Assembler DCT, C IDCT on" ) ;
			break ;
       	case 5 :
       		SetStatus( "status messages option", gStatus, LIMIT ) ;
       		break ;
       	case 6 :
       		SetStatus( "image results option", gResults, LIMIT ) ;
       		break ;
        default :
            fprintf( stderr, "[PerformOption] Some internal error has occured, suggest quitting!\n\n" ) ;
            break ;
    }
}

/**** RDCTFast **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given a set of blocks for inverse DCT'ing, construct the structures necessary
 * for the ARM inverse DCT, including tranfering the data to the appropriate type,
 * inverse DCT the data using the ARM routines and retrieve the data afterwards
 * placing it in the array given
 *
 * Inputs
 * ------
 *   in
 *   - an array of DCTArray entities, each of which contains a block to be inverse DCT'd
 *   out
 *   - an initialised array of DCTArray entries to hold the result of the inverse DCT'ing
 *     the number of entries in the array must be at least the number of entries
 *     referenced by the array in
 *   numberBlocks
 *   - the number of DCTArray entries in the array in and the number of blocks returned
 *     after the function call in out
 * Return Values
 * ------ ------
 *     TRUE  - the coding operation was successful
 *     FALSE - some error occurred (memory allocation?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean RDCTFast( DCTArray in[ ], DCTArray out[ ], unsigned int numberBlocks )
{   
	int				*dctBlockPtr ;
	int				*dctBlock ;
	unsigned int	x, y ;
	unsigned int	bCounter ;

	if( ( !in ) || ( !out ) ) {
		fprintf( stderr, "[RDCTFast] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}

	CREATEDCTBLOCK( dctBlockPtr, dctBlock, numberBlocks ) ;

	if( !dctBlock ) {
		return FALSE ;
	}

  	for( bCounter = 0 ; bCounter < numberBlocks ; bCounter += 1 ) {
		for( y = 0; y < 8; y += 1 ) {
	    	for( x = 0; x < 8; x += 1 ) {
	    		PRERDCT( dctBlock, in[ bCounter ][ y ][ x ], x, y, bCounter ) ;
			}
		}
	}
	
	rdct_fast( dctBlock, numberBlocks ) ;

	for( bCounter = 0 ; bCounter < numberBlocks ; bCounter += 1 ) {
		for( y = 0; y < 8; y += 1 ) {
	    	for( x = 0; x < 8; x += 1 ) {
	    		POSTRDCT( dctBlock, out[ bCounter ][ y ][ x ], x, y, bCounter ) ;
			}
		}
	}

	free( ( void * ) dctBlockPtr ) ;

	return TRUE ;
}

/**** SetMaxXYPosition **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * find the position for the maximum value in the given 2D square array and return 
 * both the position and the calculated maximum value
 *
 * Inputs
 * ------
 *   in
 *   - a square 2D array of integers to find the maximum value in and position
 *   N
 *   - the size of one dimension of the given array which equates to both the number
 *     of rows and columns in the given array (thus only square arrays work)
 *   x, y
 *   - pointers to integer locations to hold the x and y coordinates into the array
 *     where the maximum value is to be found
 * Outputs
 * -------
 *   x, y
 *   - the (x,y) location for the returned maximum value in the given array
 * Return Values
 * ------ ------
 *     int - the maximum value found (not absolute)
 *     0   - some error occurred, no test available since max may be zero
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int SetMaxXYPosition( IArray iArray, unsigned int N, unsigned int *x, unsigned int *y )
{
	unsigned int	i, j ;
	int				max = 0 ;
	int				newMax ;
	
	if( ( !iArray ) || ( !x ) || ( !y ) ) {
		fprintf( stderr, "[SetMaxXYPosition] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	for( j = 0 ; j < N ; j += 1 ) {
		for( i = 0 ; i < N ; i += 1 ) {
			if( ( newMax = MAX( max, iArray[ j ][ i ] ) ) > max ) {
				max = newMax ;
				*x = i ;
				*y = j ;
			}
		}
	}
	
	return max ;
}

/**** Transform *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * forward or inverse DCT transform the given array of data using either ARM or C
 * routines and if the global option for status messages is on, print the codecs
 * current process at appropriate times
 *
 * Inputs
 * ------
 *   outIArray
 *   - an initialised 2D array of integers to hold the result of the coding process
 *     which should reference at least as many 2D entries as the input array
 *   inIArray
 *   - a square 2D array of input integers that are to be (i)DCT coded
 *   N
 *   - the size of one dimension of the given array which equates to both the number
 *     of rows and columns in the given array (thus only square arrays work)
 *     also defines the dimensions for the output array and hence number of entries
 *   numberBlocks
 *   - the number of blocks that should be coded with each call to the ARM routines
 *     this value should be divide exactly into (N*N)/(BLOCKSIZE*BLOCKSIZE) else the 
 *     coding will be incomplete (not all blocks will be coded, outputs less than
 *     expected)
 *   arm
 *   - TRUE  : use the ARM routines for transform
 *     FALSE : use the C routines for transform (much much slower!)
 *   forward
 *   - TRUE  : the input data should be forward DCT'd
 *     FALSE : the input data is the result of a forward DCT and should be inverse DCT'd
 * Outputs
 * -------
 *   outIArray
 *   - a square 2D array of N*N integers that are the result of the coding
 *     undefined if FALSE returned (see Return Values)
 * Return Values
 * ------ ------
 *     TRUE  - the coding process was successful, outIArray is valid
 *     FALSE - some error occurred, outIArray does not contain valid data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Transform( IArray outIArray, IArray inIArray, unsigned int N, unsigned int numberBlocks, Boolean arm, Boolean forward )
{
	unsigned int	nDivBlock = N/BLOCKSIZE ;
	unsigned int 	itersPerLoop = -1 ;
	unsigned int 	iterations = 0 ;
	unsigned int 	iBlock, jBlock ;
	unsigned int 	i, j ;
	unsigned int	rowi ;
	unsigned int	columnj ;
	DCTArray		dctIn, dctOut ;
	DCTArray		*dctInArrayPtr, *dctOutArrayPtr ;
	DCTCosArray		dctCosArray ;
	TimeStruct		timeStruct ;
	unsigned int	blockIters ;
	unsigned int	noBCounter ;
	unsigned int	totNumBlocks ;
	unsigned int	blocksRemaining ;
	
	if( ( !inIArray ) || ( !outIArray ) ) {
		fprintf( stderr, "[Transform] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return FALSE ;
	}
	
	if( gStatus[ 0 ] == '1' ) {
		if( arm ) {
			itersPerLoop = N * N * PIDOFFSET ;
			/* this will not give any timing information during coding set as is */
		}
		else {
			itersPerLoop = 4*PIDOFFSET ;
		}
	}
	
	printf( "Calculating the " ) ;
	if( forward ) {
		printf( "forward DCT " ) ;
	}
	else {
		printf( "inverse DCT " ) ;
	}
	printf( "for the image " ) ;
	if( arm ) {
		printf( "(ARM-based)" ) ;
	}
	else {
		printf( "(C-based)" ) ;
	}
	printf( "...\n" ) ;

	if( arm ) {
		if( ( dctInArrayPtr = MakeDCTArrayPtr( numberBlocks ) ) == NULL ) {
			fprintf( stderr, "\nError in memory allocation, aborting.\n\n" ) ;
			return FALSE ;
		}
		if( ( dctOutArrayPtr = MakeDCTArrayPtr( numberBlocks ) ) == NULL ) {
			fprintf( stderr, "\nError in memory allocation, aborting.\n\n" ) ;
			free( ( void * ) dctInArrayPtr ) ;
			return FALSE ;
		}
		
		blockIters = ( N * N )/( BLOCKSIZE * BLOCKSIZE ) ;
		
		for( noBCounter = 0 ; noBCounter < blockIters ; noBCounter += numberBlocks ) {
			blocksRemaining = numberBlocks ;
			while( blocksRemaining ) {
				totNumBlocks = noBCounter + ( numberBlocks - blocksRemaining ) ;
				rowi = ( totNumBlocks / nDivBlock ) * BLOCKSIZE ;
				columnj = ( totNumBlocks % nDivBlock ) * BLOCKSIZE ;
				for( j = 0 ; j < BLOCKSIZE ; j += 1 ) {
					for( i = 0 ; i < BLOCKSIZE ; i += 1 ) {
						dctInArrayPtr[ numberBlocks - blocksRemaining ][ j ][ i ] = inIArray[ j + columnj ][ i + rowi ] ;
					}
				}
				blocksRemaining -= 1 ;
				
				if( gStatus[ 0 ] == '1' ) {
					if( iterations%itersPerLoop == 0 ) {
						if( iterations > 0 ) {
							PrintIterationTimes( ( nDivBlock * nDivBlock ) - totNumBlocks, itersPerLoop, &timeStruct ) ;
						}
						else {
							InitialiseTimeStructure( &timeStruct ) ;
						}
					}
					iterations += 1 ;
				}
			}
			
			if( forward ) {
				if( !FDCTFast( dctInArrayPtr, dctOutArrayPtr, numberBlocks ) ) {
					free( ( void * ) dctInArrayPtr ) ;
					free( ( void * ) dctOutArrayPtr ) ;
					return FALSE ;
				}
			}
			else {
				if( !RDCTFast( dctInArrayPtr, dctOutArrayPtr, numberBlocks ) ) {
					free( ( void * ) dctInArrayPtr ) ;
					free( ( void * ) dctOutArrayPtr ) ;
					return FALSE ;
				}
			}

			blocksRemaining = numberBlocks ;
			while( blocksRemaining ) {
				totNumBlocks = noBCounter + ( numberBlocks - blocksRemaining ) ;
				rowi = ( totNumBlocks / nDivBlock ) * BLOCKSIZE ;
				columnj = ( totNumBlocks % nDivBlock ) * BLOCKSIZE ;
				for( j = 0 ; j < BLOCKSIZE ; j += 1 ) {
					for( i = 0 ; i < BLOCKSIZE ; i += 1 ) {
						outIArray[ j + columnj ][ i + rowi ] = dctOutArrayPtr[ numberBlocks - blocksRemaining ][ j ][ i ] ;
					}
				}
				blocksRemaining -= 1 ;
			}
		}				
	
		free( ( void * ) dctInArrayPtr ) ;
		free( ( void * ) dctOutArrayPtr ) ;
	}
	else {
		DCTCosArrayInit( dctCosArray ) ;

		for( jBlock = 0 ; jBlock < nDivBlock ; jBlock += 1 ) {
			for( iBlock = 0 ; iBlock < nDivBlock ; iBlock += 1 ) {
			
				rowi = iBlock * BLOCKSIZE ;
				columnj = jBlock * BLOCKSIZE ;
				
				for( j = 0 ; j < BLOCKSIZE ; j += 1 ) {
					for( i = 0 ; i < BLOCKSIZE ; i += 1 ) {
						dctIn[ j ][ i ] = inIArray[ j + columnj ][ i + rowi ] ;
					}
				}
		
				if( gStatus[ 0 ] == '1' ) {
					if( iterations%itersPerLoop == 0 ) {
						if( iterations > 0 ) {
							PrintIterationTimes( ( nDivBlock * nDivBlock ) - ( jBlock * nDivBlock + iBlock ), itersPerLoop, &timeStruct ) ;
						}
						else {
							InitialiseTimeStructure( &timeStruct ) ;
						}
					}
					
					iterations += 1 ;
				}

				if( forward ) {
					FDCTReal( dctCosArray, dctIn, dctOut ) ;
				}
				else {
					RDCTReal( dctCosArray, dctIn, dctOut ) ;
				}
		
				for( j = 0 ; j < BLOCKSIZE ; j += 1 ) {
					for( i = 0 ; i < BLOCKSIZE ; i += 1 ) {
						outIArray[ j + columnj ][ i + rowi ] = dctOut[ j ][ i ] ;
					}
				}
			}
		}
	}
	
	printf( "\nThe " ) ;
	if( forward ) {
		printf( "forward DCT " ) ;
	}
	else {
		printf( "inverse DCT " ) ;
	}
	printf( "has been calculated.\n\n" ) ;
	
	return TRUE ;
}

