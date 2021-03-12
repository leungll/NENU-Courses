/*
 * Least Mean Square filter assembler prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _LMS_S_
#define _LMS_S_

void LMS_PowerUp( int coeffsStates[ ], int coeffs[ ], unsigned int nCoeffs ) ;
void LMS( int outputs[ ], int inputs[ ], unsigned int nInputs, int desired[ ], unsigned int adaptRate, unsigned int nCoeffs, int coeffsStates[ ] ) ;
void LMS_PowerDown( int coeffs[ ], int coeffsStates[ ], unsigned int nCoeffs ) ;

#endif	/* _LMS_S_ */