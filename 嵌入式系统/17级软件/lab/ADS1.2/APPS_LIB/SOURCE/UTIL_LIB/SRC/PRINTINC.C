/*
 * Utility Library: Print Utility
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "printinc.h"

void ProvePrinting( void ) ;

/**** ProvePrinting *****************************************************************
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
void ProvePrinting( void )
{
	int	array[ 1 ] ;
	int	array2D[ 1 ][ 1 ] ;
	
	PRINTARRAY( array, 0, 1, INT, 1, NULL ) ;
	PRINTARRAY2D( array2D, 0, 1, 0, 1, INT, 1, NULL ) ;
}