/*
 * Utility Library: Data Type prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DATATYPE_C_
#define _DATATYPE_C_

#include "definesc.h"

Complex *CreateComplexFromInt( int dataInt[ ], unsigned int *size ) ;
int *CreateIntFromComplex( Complex dataComplex[ ], unsigned int *size ) ;

#endif	/* _DATATYPE_C_ */