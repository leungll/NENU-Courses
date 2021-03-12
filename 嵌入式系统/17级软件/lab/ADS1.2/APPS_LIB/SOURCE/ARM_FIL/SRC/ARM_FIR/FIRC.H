/*
 * Finite Impulse Response filter C prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FIR_C_
#define _FIR_C_

unsigned int FIRC( int outputs[ ], int inputs[ ], unsigned int nInputs, int coeffs[ ], unsigned int nCoeffs ) ;
int OneFIRC( int inputs[ ], unsigned int nInputs, unsigned int inputOffset, int coeffs[ ], unsigned int nCoeffs, unsigned int forward ) ;

#endif	/* _FIR_C_ */