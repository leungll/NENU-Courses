/*
 * Utility Library: Custom Read Utility
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "custredc.h" 

/**** GetIntFromString **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read the next integer from a given string and return it
 *
 * Inputs
 * ------
 *   string
 *   - the string from which the integer is to be read
 *     string should access the location from which conversion should begin
 *   number
 *   - pointer to the location in which the integer read should be stored
 * Outputs
 * -------
 *   number
 *   - the integer converted from the string
 *     undefined if conversion failed (EOF returned)
 * Return Values
 * ------ ------
 *     1   - an integer was successfully read from the string
 *     EOF - end of string reached or an error occurred before conversion
 *           also returned if string or number are NULL
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int GetIntFromString( char *string, int *number )
{
	if( ( !string ) ||  ( !number ) ) {
		fprintf( stderr, "[GetIntFromString] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return EOF ;
	}
	
	return sscanf( string, "%d", number ) ;
}

/**** ReadInString ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * reads from the stream a character at a time putting character into the given string
 * until EOF, '\n' or 't' read (not placed in string) or string exhausted
 *
 * the string is properly terminated with a '\0'
 *
 * Inputs
 * ------
 *   stream
 *   - the stream from which to read
 *     stdin = keyboard
 *   string
 *   - an array of characters into which the characters from the stream are written
 *   limit
 *   - the maximum number of characters that can be read into the string which includes
 *     the string termination
 *     minimum possible value is 1, in which case the string will simply be "\0"
 * Outputs
 * -------
 *   string
 *   - the array of characters read from stream terminated by '\0'
 * Return Values
 * ------ ------
 *     unsigned int - the number of characters returned in the string (not including '\0')
 *     0            - stream or string were not valid or no chars read
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int ReadInString( FILE *stream, char *string, unsigned int limit )
{
	unsigned int	numberRead ;
    int 			c ;
    
    if( ( !stream ) || ( !string ) || ( limit == 0 ) ) {
		fprintf( stderr, "[ReadInString] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
    	return 0 ;
    }
	
	numberRead = 0 ;
    while(   ( ( c = getc( stream ) ) != EOF )
    		&& ( c != '\n' )
    		&& ( c != '\r' ) 
    		&& ( c != '\t' ) ) {
        if( limit > 1 ) {
        	*string++ = ( char )c ;
        	numberRead += 1 ;
        	limit -= 1 ;
        }
    }

    *string = '\0' ;
    
    return numberRead ;
}

/**** ReadDouble ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * read the next double from the keyboard skipping over anything that is not of
 * the type double (or short, integer, float)
 *
 * user is informed of incorrect entry of number and prompted to provide it again
 *
 * any characters given after the double are flushed from the stream
 *
 * Return Values
 * ------ ------
 *     double - the double read from the keyboard
 *
 * Notes
 * -----
 * will not return until a valid double has been entered via the keyboard
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
double ReadDouble( void )
{
	double	number ;
	int		dumbChar ;
	
	while( scanf( "%lf", &number ) != 1 ) {
		while(   ( ( dumbChar = getchar( ) ) != '\n' ) 
				&& ( dumbChar != '\r' ) 
				&& ( dumbChar != '\t' )
				&& ( dumbChar != EOF  ) ) {
		}	/* clean up stdin of incorrect characters given (fflush unpredictable) */
		fprintf( stderr, "\nThat was not a valid number, please enter the number again: " ) ;
	}
	
	while(   ( ( dumbChar = getchar( ) ) != '\n' ) 
			&& ( dumbChar != '\r' ) 
			&& ( dumbChar != '\t' )
			&& ( dumbChar != EOF  ) ) {
	}	/* clean up stdin removing anything (fflush unpredictable) */
	printf( "\n" ) ;
	
	return number ;
}

