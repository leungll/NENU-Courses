/*
 * Discrete Cosine Transform table generation
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>

#include "dcttgenc.h"

typedef int Table[ DCTBLOCK*DCTBLOCK ] ;
/* define a Table type for holding the data tables */

static unsigned int WriteTableToFile( FILE *fp, Table table, char *typeAndName ) ;

/**** CreateFDCTSTable **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create the FDCTScales table
 *
 * Inputs
 * ------
 *   sTable
 *   - an initialised Table data type that will be used to hold the table created
 * Outputs
 * -------
 *   sTable
 *   - the FDCTScales table created
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the table is created, sTable valid
 *     0 - some error occurred, sTable does not contain valid data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int CreateFDCTSTable( Table sTable )
{
    const char		FDCTOrder1[ 8 ] = {  0, 32, 16, 48, 40,  8, 56, 24 } ;
    /* = { 0*8, 4*8, 2*8, 6*8, 5*8, 1*8, 7*8, 3*8 } */
    /* output from Arai, Agui and Nakajima flowgraph, multiplied */
    /* by 8 to compensate for first horizontal 1-D DCT */
    const char		FDCTOrder2[ 8 ] = {  5,  1,  7,  3,  2,  6,  0,  4 } ;
    /* output from registers after second 1-D DCT, bottom 4 */
    /* results first, then top half of second four, then last two */
    /* re-ordering of flowgraph output order for register outputs */
    /* in order to gain extra registers */
    unsigned int	i ;
    unsigned int	index, zig, value ;
   
    if( !sTable ) {
		fprintf( stderr, "[CreateFDCTSTable] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
    	return 0 ;
    }

    for( i = 0; i < 64; i += 1 ) {
        index = FDCTOrder1[ i >> 3 ] + FDCTOrder2[ i & 7 ] ;
        /* get current position dealing with */
        index = ( index >> 3 ) | ( ( index & 7 ) << 3 ) ;
        /* transpose index to re-order DCT output block into */
        /* 'expected' order, a process normally performed during */
        /* the JPEG calculations */
        value = AANScales[ index ] ;
        value = ( 1 << ( AANBITS+AANBITS - 2 ) )/ value ;
        /* require 1/AANScales */
        /* 2^14 * (1/cosx) == 2^(2*14) * (1/(2^14 * cosx)) thus */
        /* AANBITS+AANBITS = 2^(2*14) */
        /* -2 removed from 2^28 to account for overflow, */
        /* 16384/value requiring 4-bits, thus maximum shift is */
        /* 12-bits */
         
		zig = -64 ;	
		/* offset to output block from curr block, current block */
		/* before output being next block in sequence */
		zig -= 8 * ( i >> 3 ) ;	
		/* offset to output block from curr pos being on row i, */
		/* thus require 8 * number rows offset */
		/* this result gives the start offset of the output block, */
		/* in top-left corner, but require actual offset... */
		zig += index ;
		/* to move from top-left add on index to current position */
        zig -= ( i & 7 ) >= 4 ? 8 : 4 ;
        /* from way values are read in, location of pointer will */
        /* be half way through row or at end */
        /* if half way through row or above, add on another row */
        /* for compensation of block pointer */
        sTable[ i ] = ( zig << 24 ) | value ;
        /* put the offset for output block position in top 8-bits, */
        /* the post-DCT multiplier in bottom 24-bits */
    }
    
    return 1 ;
}

/**** CreateRDCTSTable **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create the RDCTScales table
 *
 * Inputs
 * ------
 *   sTable
 *   - an initialised Table data type that will be used to hold the table created
 * Outputs
 * -------
 *   sTable
 *   - the RDCTScales table created
 *     undefined if 0 returned (see Return Values)
 * Return Values
 * ------ ------
 *     1 - the table is created, sTable valid
 *     0 - some error occurred, sTable does not contain valid data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int CreateRDCTSTable( Table sTable )
{
    char const		RDCTOrder[ 8 ] = { 0, 5, 2, 7, 1, 4, 3, 6 } ;
    /* order of rdct - the inverse of the flowgraph */
    /* now work out pos to be at end of DCT flowgraph */
    /* also need to transpose to compensate for the */
    /* last flip of the IDCT */
    /* this makes sure that the pixels do not */
    /* appear transposed at the end! */
	unsigned int	tmp ;
    unsigned int	index ;
    unsigned int	i ;

    if( !sTable ) {
		fprintf( stderr, "[CreateRDCTSTable] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
    	return 0 ;
    }

    for( i = 0; i < 64; i += 1 ) { 
		index = RDCTOrder[ i & 7 ] | ( RDCTOrder[ i >> 3 ] << 3 ) ;
	    /* index this time is for current block, so no offset */
	    /* from another block is required */        
    	tmp = AANScales[ i ] ;
        /* multiply by the scales this time for inverse, */
        /* not divide */ 
        sTable[ i ] = tmp | ( index << 26 ) ;
        /* in top 6-bits put the index, 26 being used to count */
        /* for byte offset for each entry */
        /* in bottom 24-bits will be the multiplier value */
    }
    
    return 1 ;
}

static void FooterFile( FILE *fp )
{
	if( !fp ) {
		return ;
	}
	
	fprintf( fp, "#endif\t/* _TABLES_ */\n" ) ;
}

static void HeaderFile( FILE *fp )
{
	if( !fp ) {
		return ;
	}
	
	fprintf( fp, "/*\n" ) ;
	fprintf( fp, " * Discrete Cosine Transform table generation\n" ) ;
	fprintf( fp, " * Copyright (C) ARM Limited 1998-1999. All rights reserved.\n" ) ;
	fprintf( fp, " */\n" ) ;
	fprintf( fp, "\n" ) ;
	fprintf( fp, "#ifndef _TABLES_\n" ) ;
	fprintf( fp, "#define _TABLES_\n" ) ;
	fprintf( fp, "\n" ) ;
}


/**** main **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open the file specified by TABLEFNAME for writing, create the FDCTScales and
 * RDCTScales tables, write them to the file, close the file and terminate
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
int main( void )
{
	FILE	*fp ;
	Table	fdctSTable ;
	Table	rdctSTable ;
	
	if( ( fp = fopen( TABLEFNAME, "w" ) ) == NULL ) {
		fprintf( stderr, "Error in creating file '%s' to write tables to.\n\n", TABLEFNAME ) ;
		return 0 ;
	}
	
	printf( "Creating tables FDCTScales and RDCTScales in the file '%s'...\n\n", TABLEFNAME ) ;
	
	HeaderFile( fp ) ;
	
	CreateFDCTSTable( fdctSTable ) ;
	CreateRDCTSTable( rdctSTable ) ;
	
	fprintf( fp,
	"/* constant tables required for scalings and re-ordering the data for both the\n" ) ;
	fprintf( fp, 
	"   forward and inverse ARM-based DCT algorithms */\n" ) ;
	WriteTableToFile( fp, fdctSTable, "unsigned int FDCTScales" ) ;
	WriteTableToFile( fp, rdctSTable, "unsigned int RDCTScales" ) ;
	
	FooterFile( fp ) ;
	
	fclose( fp ) ;
	
	printf( "Tables complete.\n\n" ) ;
	
	return 1 ;
}

/**** WriteTableToFile **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * write the given table data to the given file creating the table with the C type
 * and name by the given string
 *
 * the data is written in hex format with leading 0x
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the opened file for writing the table
 *   table
 *   - the table to write to the file
 *   typeAndName
 *   - a string that must contain the C type and data name for the table
 * Return Values
 * ------ ------
 *     1 - the table has been written to the file
 *     0 - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int WriteTableToFile( FILE *fp, Table table, char *typeAndName )
{
	unsigned int	i ;
	
	if( ( !fp ) || ( !table ) || ( !typeAndName ) ) {
		fprintf( stderr, "[WriteTableToFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
  
	fprintf( fp, "%s[ %d ] = {\n", typeAndName, DCTBLOCK * DCTBLOCK ) ;
	for( i = 0 ; i < DCTBLOCK*DCTBLOCK ; i += 1 ) {
		if( ( i%DCTBLOCK == 0 ) && ( i != 0 ) ) {
			fprintf( fp, "\n" ) ;
		}
		if( ( i%DCTBLOCK == 0 ) ) {
			fprintf( fp, "\t" ) ;
		}
		fprintf( fp, "0x%08x", table[ i ] ) ;
		if( i != DCTBLOCK*DCTBLOCK - 1 ) {
			fprintf( fp, ", " ) ;
		}
	}
	fprintf( fp, "\n} ;\n\n" ) ;
	
	return 1 ;
}

