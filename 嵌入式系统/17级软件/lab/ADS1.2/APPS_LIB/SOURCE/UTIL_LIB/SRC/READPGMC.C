/*
 * Utility Library: Read PGM
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>

#include "pgmc.h"

#include "arrayc.h"
#include "fileutlc.h"

/**** ReadPGM ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open a file specified by the user, read in Type 2 or 5 PGM data into an array which
 * is returned and close the file
 *
 * the information read from the PGM file is written to the screen so that the end
 * user can see the image file reading progress and determine that image is in fact
 * that which was required
 *
 * Inputs
 * ------
 *   function
 *   - an optional string containing the operation that is be performed on the image
 *     to be non-specific pass NULL
 *   width
 *   - a pointer to the integer to store the width of the image
 *   height
 *   - a pointer to the integer to store the height of the image
 * Outputs
 * -------
 *   width
 *   - the width of the image read in
 *     undefined if NULL returned for the image data
 *   height
 *   - the height of the image read in
 *     undefined if NULL returned for the image data
 * Return Values
 * ------ ------
 *     UCArray - a 2-D array of unsigned chars of given width and height
 *               each entry corresponds to a pixel of the image
 *     NULL    - some error occurred
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned UCArray array
 * deallocate after using the data using FreeUCArray
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
UCArray ReadPGM( char function[ ], unsigned int *width, unsigned int *height )
{
	char			iFName[ LIMIT ] ;
	char			data[ LIMIT ] ;
    FILE			*ifp ;
    UCArray			pgm	;
    unsigned int	i, j ;
    unsigned int	typeno ;
    unsigned int	maxValue ;
    char 			comment ;
    unsigned int	tempInt ;
    
    if( ( !width ) || ( !height ) ) {
		fprintf( stderr, "[ReadPGM] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
    
 	printf( "Please give the name of the PGM file " ) ;
 	if( function != NULL ) {
 		printf( "containing the image to %s", function ) ;
 	}
 	else {
 		printf( "to open" ) ;
 	}
 	printf( ".\n\n" ) ;

	if( GetFileName( iFName, LIMIT, "reading" ) == NULL ) {
		return NULL ;
	}
	/* open binary to account for type P5 pgm's */
	if( ( ifp = OpenFileRead( "rb", iFName ) ) == NULL ) {
		return NULL ;
	}
    
    if( !fgets( data, LIMIT, ifp ) )
    {
    	fprintf( stderr, "Error reading PGM type, aborting\n\n" ) ;
    	return NULL ;
    }
    
    if( 1 != sscanf( &data[ 1 ], "%d", &typeno ) )
    {
		fprintf( stderr, "Error reading PGM type, aborting\n\n" ) ;
		return NULL ;
    }
    
    printf( "PGM type P%d\n", typeno ) ;
    
    while( fscanf( ifp, "#%c", &comment ) ) {
    	printf( "%c", comment ) ;
    	/* break if nothing scanned or end of line read */
		while( fscanf( ifp, "%c", &comment ), comment != '\n' ) {
			printf( "%c", comment ) ;
		} 
		printf( "\n" ) ;
    }
    
    if( !fgets( data, LIMIT, ifp ) )
    {
		fprintf( stderr, "Error reading PGM dimensions, aborting\n\n" ) ;
		return NULL ;
    }
    	
    if( 2 != sscanf( data, "%d %d", width, height ) )
    {
		fprintf( stderr, "Error reading PGM dimensions, aborting\n\n" ) ;
		return NULL ;
    }
    
    if( !fgets( data, LIMIT, ifp ) )
    {
		fprintf( stderr, "Error reading maximum value, aborting\n\n" ) ;
		return NULL ;
    }    
    
    if( 1 != sscanf( data, "%d", &maxValue ) )
    {
		fprintf( stderr, "Error reading maximum value, aborting\n\n" ) ;
		return NULL ;
    }
    
    printf( "Width '%d', height '%d', maximum value '%d'\n", *width, *height, maxValue ) ;
    
    switch( typeno ) {
		case 2:
		case 5:
			if( ( pgm = MakeUCArray( *width, *height ) ) == NULL ) {
				fprintf( stderr, "Unable to create array to store image, aborting\n" ) ;
				/* pgm == NULL, so safe to return it */
			}
			else {
				for( j = 0 ; j < *height ; j += 1 ) {
					if( typeno == 2 ) {
						for( i = 0 ; i < *width ; i += 1 ) {
							fscanf( ifp, "%d", &tempInt ) ;
							pgm[ j ][ i ] = ( unsigned char )tempInt ;
						}
					}
					else {
						if( ( fread( pgm[ j ], sizeof( unsigned char ), *width, ifp ) ) != *width ) {
							fprintf( stderr, "Error reading data for image from file, aborting\n\n" ) ;
							FreeUCArray( pgm, *height ) ;
							pgm = NULL ;
							break ;	/* for-loop */
						}
					}
				}
			}
			break;
    	default:
			fprintf( stderr, "Image type not implemented, aborting\n\n" ) ;
			pgm = NULL ;
			break ;
    }
    printf( "\n" ) ;
    
    fclose( ifp ) ;
    
    return pgm;
}
