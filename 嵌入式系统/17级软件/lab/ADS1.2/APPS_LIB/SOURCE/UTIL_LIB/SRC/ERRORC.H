/*
 * Utility Library: Error macros
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ERROR_C_
#define _ERROR_C_

#include <stdlib.h>

#include "definesc.h"

/**** ELEMENTERROR ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * calculate the difference (error) between two given values and update the given
 * maximum absolute value based on this new error value
 *
 * Inputs
 * ------
 *   ORIG
 *   - the original data value
 *   NEW
 *   - the new data value
 *   ERROR
 *   - an entity to hold the difference between the values
 *   MAXABSERR
 *   - the current maximum absolute error over all previous error values
 *     pass set to zero is first call to macro
 *   TYPE
 *   - the type of ORIG, i.e. byte, short or int
 * Outputs
 * -------
 *   ERROR
 *   - the calculated difference (error) between ORIG and NEW
 *   MAXABSERR
 *   - the updated maximum absolute error over all error values thus calculated including
 *     the current error value
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define ELEMENTERROR( ORIG, NEW, ERROR, MAXABSERR, TYPE ) { \
	ERROR = ( TYPE )( ORIG - NEW ) ; \
	MAXABSERR = MAX( MAXABSERR, ( unsigned int )abs( ERROR ) ) ; \
}

/**** ARRAYERROR ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * calculate the difference (error) between two given arrays, calculating the difference
 * on a per element basis and calculate both the maximum absolute error over all the
 * errors and the mean square error between the original and new array
 *
 * Inputs
 * ------
 *   ORIGARRAY
 *   - the original array of data values
 *   NEWARRAY
 *   - the new array of data values
 *   ERRORARRAY
 *   - an array to hold the difference between each entry of ORIG and NEW arrays
 *   SIZE
 *   - the number of entries in both ORIG and NEW arrays and the number of entries
 *     that will be in the ERROR array
 *     each array must reference at least this many values
 *   MAXABSERR
 *   - an integer to hold the maximum absolute error over all the error values
 *   MSE
 *   - an integer to hold the mean squared error between the ORIG and NEW arrays
 *   TYPE
 *   - the type of ORIGARRAY, i.e. byte, short or int
 * Outputs
 * -------
 *   ERRORARRAY
 *   - the calculated differences (errors) between the ORIG and NEW arrays
 *   MAXABSERR
 *   - the maximum absolute error over all error values in the error array
 *   MSE
 *   - the mean squared error between the ORIG and NEW arrays
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define ARRAYERROR( ORIGARRAY, NEWARRAY, ERRORARRAY, SIZE, MAXABSERR, MSE, TYPE ) { \
	unsigned int counter ; \
	for( MAXABSERR = 0, MSE = 0, counter = 0 ; counter < SIZE ; counter += 1 ) { \
		ELEMENTERROR( ORIGARRAY[ counter ], NEWARRAY[ counter ], ERRORARRAY[ counter ], MAXABSERR, TYPE ) ; \
		MSE += ( unsigned int )( ERRORARRAY[ counter ] * ERRORARRAY[ counter ] ) ; \
	} \
	MSE = ( unsigned int )( ( float )MSE/( ( float )( ( int )( SIZE * SIZE ) ) ) ) ; \
}

/**** ARRAYERROR2D ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * calculate the difference (error) between two given arrays, calculating the difference
 * on a per element basis and calculate both the maximum absolute error over all the
 * errors and the mean square error between the original and new array
 *
 * Inputs
 * ------
 *   ORIGARRAY
 *   - the original array of data values
 *   NEWARRAY
 *   - the new array of data values
 *   ERRORARRAY
 *   - an array to hold the difference between each entry of ORIG and NEW arrays
 *   WIDTH
 *   - the number of columns in both ORIG and NEW arrays and the number of columns
 *     that will be in the ERROR array
 *     each array must reference at least this many columns
 *   HEIGHT
 *   - the number of rows in both ORIG and NEW arrays and the number of rows
 *     that will be in the ERROR array
 *     each array must reference at least this many rows
 *   MAXABSERR
 *   - an integer to hold the maximum absolute error over all the error values
 *   MSE
 *   - an integer to hold the mean squared error between the ORIG and NEW arrays
 *   TYPE
 *   - the type of ORIGARRAY, i.e. byte, short or int
 * Outputs
 * -------
 *   ERRORARRAY
 *   - the calculated differences (errors) between the ORIG and NEW arrays
 *   MAXABSERR
 *   - the maximum absolute error over all error values in the error array
 *   MSE
 *   - the mean squared error between the ORIG and NEW arrays
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define ARRAYERROR2D( ORIGARRAY, NEWARRAY, ERRORARRAY, WIDTH, HEIGHT, MAXABSERR, MSE, TYPE ) { \
	unsigned int x ; \
	unsigned int y ; \
	for( MAXABSERR = 0, MSE = 0, y = 0 ; y < HEIGHT ; y += 1 ) { \
		for( x = 0 ; x < WIDTH ; x += 1 ) { \
			ELEMENTERROR( ORIGARRAY[ y ][ x ], NEWARRAY[ y ][ x ], ERRORARRAY[ y ][ x ], MAXABSERR, TYPE ) ; \
			MSE += ( unsigned int )( ERRORARRAY[ y ][ x ] * ERRORARRAY[ y ][ x ] ) ; \
		} \
	} \
	MSE = ( unsigned int )( ( float )MSE/( ( float )( ( unsigned int )( WIDTH * HEIGHT ) ) ) ) ; \
}

#endif	/* _ERROR_C_ */