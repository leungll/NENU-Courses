/*
 * Infinite Impulse Response filter assembler prototype
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _IIR_S_
#define _IIR_S_

void IIR_PowerUp( int coeffsStates[ ], int coeffs[ ], unsigned int nBiquads ) ;
void IIR( int outputs[ ], int inputs[ ], unsigned int nInputs, unsigned int nBiquads, int coeffsStates[ ] ) ;

#endif	/* _IIR_S_ */