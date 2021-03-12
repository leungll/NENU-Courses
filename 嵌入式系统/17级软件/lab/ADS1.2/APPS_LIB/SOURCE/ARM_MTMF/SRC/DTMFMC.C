/*
 * Dual-Tone Multi-Frequency test main
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include "dtmftesc.h"

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
	return dtmf_main( argc, argv ) ;
}