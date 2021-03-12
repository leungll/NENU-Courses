/*
 * Utility Library: Integer Array
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrayc.h"

/**** MakeIArray ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * allocate memory for an IArray, clearing each entry
 *
 * each row references a one-dimensional integer array of size width
 *
 * Inputs
 * ------
 *   width
 *   - the width (number of columns) for the IArray
 *   height
 *   - the height (number of rows) for the IArray
 * Return Values
 * ------ ------
 *     IArray - an allocated, clear, IArray
 *     NULL   - some error occurred (memory allocation failed)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned IArray
 * deallocate after using the array using the FreeIArray procedure
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
IArray MakeIArray( unsigned int width, unsigned int height )
{
    IArray			iArray ;
    unsigned int	j ;
    
    if( ( iArray = ( int ** )calloc( height, sizeof( int * ) ) ) == NULL ) {
		fprintf( stderr, "Cannot make array for data, aborting.\n\n" ) ;
		return NULL ;
    }
    
    for( j = 0 ; j < height ; j += 1 ) {
		if( ( iArray[ j ] = ( int * )calloc( width, sizeof( int ) ) ) == NULL ) {
	    	fprintf( stderr, "Cannot make array for data, aborting.\n\n" ) ;
	    	FreeIArray( iArray, j ) ;	/* clear those arrays previously made */
			return NULL ;
		}
    }

    return iArray ;
}

/**** FreeIArray ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * deallocate memory for an IArray
 *
 * each row references a one-dimensional integer array of size width thus only the
 * height is required
 *
 * Inputs
 * ------
 *   IArray
 *   - the IArray to deallocate
 *   height
 *   - the height (number of rows) in the IArray
 *
 * Memory deallocated (not allocated)
 * ------ -----------  --- ---------
 * the IArray passed, created by a call to MakeIArray
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void FreeIArray( IArray iArray, unsigned int height )
{
	unsigned int	j ;
  
	if( !iArray ) {
		return ;
	}

	for( j = 0 ; j < height ; j += 1 ) {
		if( iArray[ j ] != NULL ) {
			free( ( void * ) iArray[ j ] ) ;
		}
	}
	
	free( ( void * ) iArray ) ;
}
