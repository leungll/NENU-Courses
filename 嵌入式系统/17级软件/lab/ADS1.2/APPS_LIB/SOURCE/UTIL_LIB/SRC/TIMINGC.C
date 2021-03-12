/*
 * Utility Library: Timing
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <math.h>
#include <stdio.h>
#include <time.h>

#include "timingc.h"

/**** GetHrsMinsSecs ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine the number of hours, minutes and seconds from the given number of seconds
 *
 * Inputs
 * ------
 *   totalSecs
 *   - the total number of seconds to be translated
 *   hrs
 *   - a pointer to the location to store the number of hours
 *   mins
 *   - a pointer to the location to store the number of minutes
 *   secs
 *   - a pointer to the location to store the number of seconds
 * Outputs
 * -------
 *   hrs
 *   - the complete number of hours referenced by totalSecs
 *   mins
 *   - the complete number of minutes remaining in totalSecs after hours removed
 *   secs
 *   - the complete number of seconds remaining in totalSecs after hours & minutes
 *     removed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void GetHrsMinsSecs( unsigned int totalSecs, unsigned int *hrs, unsigned int *mins, unsigned int *secs )
{
	if( ( !hrs ) || ( !mins ) || ( !secs ) ) {
		fprintf( stderr, "[GetHrsMinsSecs] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return ;
	}
	
	/* all integer division */
	*hrs = totalSecs / ( 60 * 60 ) ;
	*mins = ( totalSecs - ( *hrs * 60 * 60 ) )/ 60 ;
	*secs = totalSecs - ( *hrs * 60 * 60 ) - ( *mins * 60 ) ;
}

/**** InitialiseTimeStructure *******************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * initialise each of the elements in a given timing structure
 *
 * timeStart is set as the current number of seconds since processor start up and
 * totalTDiff and tDiffCounter are both zeroed
 *
 * Inputs
 * ------
 *   timePtr
 *   - a pointer to the timing structure to initialise
 * Outputs
 * -------
 *   timePtr
 *   - an initialised timing structure
 *     timeStart = clock( )/CLOCKS_PER_SEC
 *     totalTDiff = 0
 *     tDiffCounter = 0
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void InitialiseTimeStructure( TimePtr timePtr )
{
	if( !timePtr ) {
		fprintf( stderr, "[InitialiseTimeStructure] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return ;
	}
	
	timePtr->timeStart = clock( )/CLOCKS_PER_SEC ;
	timePtr->totalTDiff = 0 ;
	timePtr->tDiffCounter = 0 ;
}	

/**** PrintIterationTimes ***********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the number of iterations remaining, the time taken in hrs, mins & secs for the
 * last section of iterations and the approximate time remaining to perform the
 * number of iterations remaining
 *
 * the procedure is desiged for giving the end user some idea of how long the process
 * is likely to take and is ideal for use in complex loops
 *
 * Inputs
 * ------
 *   itersRemain
 *   - the number of iterations remaining to perform before completion
 *   itersPerLoop
 *   - the number of iterations since the last call to the procedure
 *     this should be a constant number with each call else the timings will not
 *     be correct as they work on averages and this value is not maintained
 *   timePtr
 *   - a pointer to the timing structure which is used between procedure calls to
 *     maintain the necessary information
 *     this structure should be initialised before calling the procedure for the first
 *     time using the procedure InitialiseTimeStructure
 * Outputs
 * -------
 *   timePtr
 *   - the updated timing structure with the information gathered from the current
 *     procedure call added
 *
 * Notes
 * -----
 * the more times the procedure is called the more accurate the approximate time
 * remaining will be since it works on averages, thus initially it may not be a very 
 * good estimate until the timings have settled
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void PrintIterationTimes( unsigned int itersRemain, unsigned int itersPerLoop, TimePtr timePtr )
{
	unsigned int	timeEnd ;
	unsigned int	timeDiff ;
	unsigned int	avgTimeDiff ;
	unsigned int	hrs, mins, secs ;
	
	if( !timePtr ) {
		fprintf( stderr, "[PrintIterationTimes] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return ;
	}

	printf( "    '%d' iterations remaining\n", itersRemain ) ;

	timeEnd = timePtr->timeStart ;
	timePtr->timeStart = clock( )/CLOCKS_PER_SEC ;
	timeDiff = timePtr->timeStart - timeEnd ;
	
	timePtr->totalTDiff += timeDiff ;
	timePtr->tDiffCounter += 1 ;
	
	avgTimeDiff = ( unsigned int )floor( ( ( ( double )timePtr->totalTDiff ) / ( ( double )timePtr->tDiffCounter ) ) + 0.5 ) ;
								
	GetHrsMinsSecs( timeDiff, &hrs, &mins, &secs ) ;
	printf( "    time taken for last '%d' iterations %d hrs %d mins %d secs\n", itersPerLoop, hrs, mins, secs ) ;
	
	GetHrsMinsSecs( ( unsigned int )( ( double )avgTimeDiff * ( ( double )itersRemain / ( double )itersPerLoop ) ), &hrs, &mins, &secs ) ;
	printf( "    approximate time remaining %d hrs %d mins %d secs\n", hrs, mins, secs ) ;
}

