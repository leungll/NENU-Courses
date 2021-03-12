/*
 * Utility Library: Unsigned Char Array
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "arrayc.h"

/**** MakeUCArray *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * allocate memory for an UCArray, clearing each entry
 *
 * each row references a one-dimensional unsigned char array of size width
 *
 * Inputs
 * ------
 *   width
 *   - the width (number of columns) for the UCArray
 *   height
 *   - the height (number of rows) for the UCArray
 * Return Values
 * ------ ------
 *     UCArray - an allocated, clear, UCArray
 *     NULL    - some error occurred (memory allocation failed)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned UCArray
 * deallocate after using the array using the FreeUCArray procedure
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
UCArray MakeUCArray( unsigned int width, unsigned int height )
{
    UCArray			uCArray ;
    unsigned int	j ;
  
    if( ( uCArray = ( unsigned char ** )calloc( height, sizeof( unsigned char * ) ) ) == NULL ) {
		fprintf( stderr, "[MakeUCArray] calloc error on 2D array\n\n" ) ;
		return NULL ;
    }
    
    for( j = 0 ; j < height ; j += 1 ) {
		if( ( uCArray[ j ] = ( unsigned char * )calloc( width, sizeof( unsigned char ) ) ) == NULL ) {
	    	fprintf( stderr, "[MakeUCArray] calloc error on 1D arrays in 2D array\n\n" ) ;
	    	FreeUCArray( uCArray, j ) ; /* clear those arrays previously made */
			return NULL ;
		}
    }

    return uCArray ;
}

/**** FreeUCArray *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * deallocate memory for an UCArray
 *
 * each row references a one-dimensional unsigned char array of size width thus only 
 * the height is required
 *
 * Inputs
 * ------
 *   UCArray
 *   - the UCArray to deallocate
 *   height
 *   - the height (number of rows) in the UCArray
 *
 * Memory deallocated (not allocated)
 * ------ -----------  --- ---------
 * the UCArray passed, created by a call to MakeUCArray
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void FreeUCArray( UCArray uCArray, unsigned int height )
{
	unsigned int	j ;
  
	if( !uCArray ) {
		return ;
	}

	for( j = 0 ; j < height ; j += 1 ) {
		if( uCArray[ j ] != NULL ) {
			free( ( void * ) uCArray[ j ] ) ;
		}
	}
	
	free( ( void * ) uCArray ) ;
}
