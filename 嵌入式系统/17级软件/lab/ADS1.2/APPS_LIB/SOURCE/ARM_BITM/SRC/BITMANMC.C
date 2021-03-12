/*
 * Bit Manipulation test main
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "bitmtesc.h"

/**** main **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * pass control to application main loop
 *
 * Return Values
 * ------ ------
 *     int - returned value from application loop
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int main( int argc, char **argv )
{
	return bitm_main( argc, argv ) ;
}