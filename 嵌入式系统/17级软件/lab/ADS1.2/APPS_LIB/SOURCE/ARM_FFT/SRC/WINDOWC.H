/*
 * Fast Fourier Transform window definitions and prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _WINDOWING_C_
#define _WINDOWING_C_

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

#ifndef HAMMING
	#define	HAMMING	0x1D70	/* 0.46 * 16384 */
#endif	/* HAMMING */

#ifndef HANNING
	#define	HANNING	0x2000	/* 0.50 * 16384 */
#endif	/* HANNING */

int *GenerateWindow( unsigned int windowCoeff, unsigned int nDataPoints ) ;
unsigned int HammingWindow( int outputs[ ], int inputs[ ], unsigned int nDataPoints ) ;
unsigned int HanningWindow( int outputs[ ], int inputs[ ], unsigned int nDataPoints ) ;

#endif	/* _WINDOWING_C_ */