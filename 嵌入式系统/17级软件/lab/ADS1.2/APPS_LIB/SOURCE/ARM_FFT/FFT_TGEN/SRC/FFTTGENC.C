/*
 * Fast Fourier Transform table generation
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ffttgenc.h"

/**** CreateTable *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create and write the ARM Assembler FFT table to the given file with required 
 * number of entries to handle an FFT with the given number of maximum points
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the open file to write the data
 *   n
 *   - the maximum number of points that the FFT will be able to handle
 *     must be a power of 2 else the table will not handle the maximum FFT given
 *     (will only create a table of size upto the nearest power of 2 < n)
 *     table will have size n/2+4 bytes, n/8+1 words, each word with cos, sin pair
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release (based on code from Dominic.Symes@arm.com)
 *
 ************************************************************************************/
static void CreateTable( FILE *fp, int n )
{
	unsigned int	bits ;
	double			omega ;
	unsigned int	k ;
	double			theta ;
	int				cost ;
	int				sint ;
	
	if( !fp ) {
		fprintf( stderr, "[CreateTable] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return ;
	}
	
	for( bits = 0 ; n > ( 1 << bits ) ; bits += 1 ) ;	/* calculate LogN */
	
	fprintf( fp, ";/*\n" ) ;
	fprintf( fp, "; * Fast Fourier Transform lookup table\n" ) ;
	fprintf( fp, "; * Copyright (C) ARM Limited 1998-1999. All rights reserved.\n" ) ;
	fprintf( fp, "; */\n" ) ;
	fprintf( fp, "\n" ) ;
	fprintf( fp, "; %s\n", TABLEFNAME ) ;
	fprintf( fp, ";\n" ) ;
	fprintf( fp, "; Table for %d point FFT.\n", n ) ;
	fprintf( fp, "; Table size = %d bytes.\n", ( ( n/8 )+ 1 )* 4 ) ;
	fprintf( fp, "; Table stores sin in top 16-bits, cos in bottom 16-bits.\n\n" ) ;
	fprintf( fp, "TABLE_N       EQU %d\n", n ) ;
	fprintf( fp, "TABLE_LOGN    EQU %d\n\n", bits ) ;

	omega = ( 2.0 * PI/( double )n ) ;
  
	for( k = 0 ; k <= n/8 ; k += 1 ) {
		theta = ( double )k * omega ;
		cost = ( int )( ( double )( 1 << 14 ) * cos( theta ) ) ;
		/* 0x4000 = 2^14 = 16384 maximum shift possible ( -1<=cos<=1 ) */
		sint = ( int )( ( double )0x4000 * sin( theta ) ) ;
		cost |= sint << 16 ;
		fprintf( fp, "\tDCD\t0x%08x\n", cost ) ;
	}
	fprintf( fp, "\n\tEND\n" ) ;
}

/**** main **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * write the file of table data necessary for the ARM Assembler FFT routines
 *
 * read the command line arguments, check their validity, open a file to write the
 * table, calculate the table and write it to the file, close the file and terminate
 *
 * Inputs
 * ------
 *   argc
 *   - the number of command line arguments given
 *     may be 0 in which case defaults used (defined in header)
 *   argv
 *   - an array containing the command line arguments (if any) given as strings
 * Return Values
 * ------ ------
 *     0 - application terminated correctly
 *     1 - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.1.0, 30/06/1998	reworked and created CreateTable separate function
 * 1.0.0, 05/10/1995    first release
 *
 ************************************************************************************/
int main( int argc, char **argv )
{
	char	path[ 256 ] = "" ;
	FILE	*fp ;
	int		n = N ;

	printf( "Program to create the lookup table for FFT.\n\n" ) ;
	
	if( --argc > 0 ) {
		sscanf( *( ++argv ), "%d", &n ) ;	/* read n */
	}
	
	if( ( n == 0 ) || ( n != ( n & ( -n ) ) ) ) {	/* test for power of 2 */
		fprintf( stderr, "The number of points given is not a power of 2, aborting.\n\n" ) ;
		return 1 ;
	}
	
	printf( "The table will be created for a maximum '%d' point FFT.\n\n", n ) ;
	
	if( --argc > 0 ) {
		strcpy( path, *( ++argv ) ) ;		/* read new path */
	}
	strcat( path, TABLEFNAME ) ;
	
	if( ( fp = fopen( path, "w" ) ) == NULL ) {
		fprintf( stderr, "Cannot create the file '%s' to save the table, aborting.\n\n", path ) ;
		return 1 ;
	}
	
	printf( "The table will be saved to the file (with path) '%s'.\n\n", path ) ;
			
	printf( "Creating table...\n\n" ) ;
	
	CreateTable( fp, n ) ;
	
	printf( "Table created.\n\n" ) ;
	
	fclose( fp ) ;
	
	return 0 ;
}


