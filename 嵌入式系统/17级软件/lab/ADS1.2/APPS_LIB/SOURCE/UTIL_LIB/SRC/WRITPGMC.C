/*
 * Utility Library: Write PGM
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>

#include "pgmc.h"

#include "arrayc.h"
#include "fileutlc.h"

/**** SavePGM ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * write the given PGM data array to the given file
 *
 * Inputs
 * ------
 *   ofp
 *   - a pointer to the open file to write data to
 *   pgm
 *   - the 2-D array of unsigned char image data to write to the file
 *     if NULL is passed the file will be created with all data except PGM image data
 *     (type number, dimensions and maximum value)
 *   width
 *   - the width of the PGM array
 *     the number of columns of PGM pixels in the array (length of each row array)
 *   height
 *   - the height of the PGM array
 *     the number of row of PGM pixels in the array (number of row arrays)
 * Return Values
 * ------ ------
 *     1 - the image was written successfully
 *     0 - some error occurred (file corrupt or incorrect arguments)
 *
 * Notes
 * -----
 * no option is provided to write out type 2 PGM's since type 5 is the preferable type
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int SavePGM( FILE *ofp, UCArray pgm, unsigned int width, unsigned int height )
{
    unsigned int	j ;
    
    if( !ofp ) {
		fprintf( stderr, "[SavePGM] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	    
    fprintf( ofp, "P5\n" ) ;	/* the image will be made in type 5 */
    
    fprintf( ofp, "#Created by ARM PGM Writer (Drew.Pettican@arm.com).\n" ) ;
    
    fprintf( ofp, "%d %d\n", width, height ) ;
    
	/* maximum value for some packages is required as max, 255, not actual max */
	fprintf( ofp, "%d\n", 255 ) ; 
    
    if( !pgm ) {
    	return 1 ;
    }
  
    for( j = 0 ; j < height ; j += 1 ) {
    	if( ( fwrite( pgm[ j ], sizeof( unsigned char ), width, ofp ) ) != width ) {
    		fprintf( stderr, "Error writing image to file, file may be corrupt, aborting.\n\n" ) ;
    		return 0 ;
    	}
    }
    
    return 1 ;
}
	
/**** WritePGM **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open a file specified by the user, write type 5 PGM data from the given array 
 * and close the file
 *
 * Inputs
 * ------
 *   pgm
 *   - the 2-D array of unsigned char image data to write to the file
 *     if NULL is passed the file will be created with all data except PGM image data
 *     (type number, dimensions and maximum value)
 *   width
 *   - the width of the PGM array
 *     the number of columns of PGM pixels in the array (length of each row array)
 *   height
 *   - the height of the PGM array
 *     the number of rows of PGM pixels in the array (number of row arrays)
 *   inageString
 *   - an optional string containing the type of image data that is to be written
 *     to be non-specific pass NULL
 * Return Values
 * ------ ------
 *     1 - the image was written successfully
 *     0 - some error occurred (file corrupt or could not even open)
 *
 * Notes
 * -----
 * no option is provided to write out type 2 PGM's since type 5 is the preferable type
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int WritePGM( UCArray pgm, unsigned int width, unsigned int height, char imageString[ ] )
{
    char			oFName[ LIMIT ] ;
    FILE			*ofp ;
    unsigned int	saved ;
    
	printf( "Please give a name for saving the " ) ;
	if( imageString != NULL ) {
		printf( "%s ", imageString ) ;
	}
	printf( "PGM image.\n\n" ) ;
	
	if( GetFileName( oFName, LIMIT, "writing" ) == NULL ) {
		return 0 ;
	}
	if( ( ofp = OpenFileWrite( "wb", oFName ) ) == NULL ) {
		return 0 ;
	}
	
	saved = SavePGM( ofp, pgm, width, height ) ;
	
	fclose( ofp ) ;
	
	return saved ;
}

