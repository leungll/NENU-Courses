/*
 * Discrete Cosine Transform C definitions and prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DCT_C_
#define _DCT_C_

#ifndef PIMI
	#define PIMI	3.14159265358
	/* definition is platform independent, always same value, used for PI */
#endif	/* PIMI */

#ifndef PIMD
	#define PIMD	4.0*atan( 1.0 )
	/* machine dependent difinition */
#endif	/* PIMD */

#ifndef	PI
	#define	PI	PIMI
#endif	/* PI */

#ifndef BLOCKSIZE
	#define	BLOCKSIZE	8
#endif	/* BLOCKSIZE */

typedef int		DCTArray[ BLOCKSIZE ][ BLOCKSIZE ] ;
/* define the array that holds a block of data to be DCT'd */
typedef double	DCTCosArray[ BLOCKSIZE ][ BLOCKSIZE ] ;
/* define the array that will hold the cosine lookup table for real DCT */

unsigned int DCTCosArrayInit( DCTCosArray dctCosArray ) ;
unsigned int FDCTReal( DCTCosArray dctCosArray, DCTArray dctIn, DCTArray dctOut ) ;
unsigned int RDCTReal( DCTCosArray dctCosArray, DCTArray dctIn, DCTArray dctOut ) ;

#endif	/* _DCT_C_ */