/*
 * Utility Library: Errors
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "errorc.h"

void ProveError( void ) ;

/**** ProveError ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * using some simple test data call an instance of each of the macros so that they
 * are test compiled to at least prove compilation for the given test data
 *
 * this procedure is only included for testing purposes and has no real use outside
 * of this and should be ignored
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void ProveError( void )
{
	int				data = 0 ;
	unsigned int	maxabs = 0 ;
	int				array[ 1 ] ;
	int				newarray[ 1 ] ;
	int 			errorarray[ 1 ] ;
	unsigned int	mse ;
	int				array2D[ 1 ][ 1 ] ;
	int				newarray2D[ 1 ][ 1 ] ;
	int				errorarray2D[ 1 ][ 1 ] ;
	
	ELEMENTERROR( data, 0, data, maxabs, int ) ;
	ARRAYERROR( array, newarray, errorarray, 1, maxabs, mse, int ) ;
	ARRAYERROR2D( array2D, newarray2D, errorarray2D, 1, 1, maxabs, mse, int ) ;
}