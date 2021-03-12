/*
 * Fast Fourier Transform C definitions and prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FFT_C_
#define _FFT_C_

#include "fftstruc.h"
/* import the Complex structure type */

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

unsigned int FFTC( void *inputs, unsigned int nInputs, unsigned int realOnly, unsigned int forward, unsigned int outputCounter, Complex *output ) ;

#endif	/* _FFT_C_ */