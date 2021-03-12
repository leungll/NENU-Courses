/*
 * Discrete Cosine Transform definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DCT_TABLE_GENERATION_C_
#define _DCT_TABLE_GENERATION_C_

#define AANBITS 14
/* define the fixed-point shift applied to AANScales table (below) */

static const unsigned int AANScales[ 64 ] = {
	16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
	21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
	19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
	16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
	 8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
	 4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
} ;
/* constant table that performs the scalings of the Arai, Agui, Nakajima method
   each entry fixed-point scaled by AANBITS
   
   table is incorporated into both FDCTScales and RDCTScales */

#ifndef DCTBLOCK
	#define DCTBLOCK	8
#endif	/* BLOCKSIZE */

#ifndef TABLEFNAME
	#define	TABLEFNAME	"dcttablc.h"
#endif	/* TABLEFNAME */

#endif	/* _DCT_TABLE_GENERATION_C_ */