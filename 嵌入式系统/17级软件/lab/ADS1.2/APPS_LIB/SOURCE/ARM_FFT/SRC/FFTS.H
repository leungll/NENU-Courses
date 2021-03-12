/*
 * Fast Fourier Transform assembler prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FFT_S_
#define _FFT_S_

#include "fftstruc.h"

int FFT( Complex *input, Complex *output, int logN, unsigned int direction ) ;
int REALFFT( int *input, Complex *output, int logN ) ;

#endif	/* _FFT_S_ */