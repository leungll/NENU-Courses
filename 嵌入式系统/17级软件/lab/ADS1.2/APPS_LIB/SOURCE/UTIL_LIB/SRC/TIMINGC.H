/*
 * Utility Library: Timing prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _TIMING_C_
#define _TIMING_C_

#ifndef _TIMESTRUCT
#define _TIMESTRUCT

typedef struct	TimeStruct	TimeStruct ;
typedef 		TimeStruct	*TimePtr ;

struct TimeStruct {
	unsigned int	timeStart ;
	unsigned int	totalTDiff ;
	unsigned int	tDiffCounter ;
} ;
/* define the timing structure used for the timing routintes */

#endif	/* _TIMESTRUCT_C_ */

void GetHrsMinsSecs( unsigned int totalSecs, unsigned int *hrs, unsigned int *mins, unsigned int *secs ) ;
void InitialiseTimeStructure( TimePtr timePtr ) ;
void PrintIterationTimes( unsigned int itersRemain, unsigned int itersPerLoop, TimePtr timePtr ) ;

#endif	/* _TIMING_C_ */