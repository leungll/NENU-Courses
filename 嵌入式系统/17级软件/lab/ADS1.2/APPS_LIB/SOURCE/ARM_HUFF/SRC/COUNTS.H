/*
 * Count prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _COUNT_S_
#define _COUNT_S_

#include "datasize.h"

void CountSymbols( void *source, unsigned int n, unsigned int counts[ ], int add, unsigned int datatype ) ;

void CountByteSymbols( unsigned char source[ ], unsigned int n, unsigned int counts[ ], int add ) ;
void CountHalfWordSymbols( unsigned short source[ ], unsigned int n, unsigned int counts[ ], int add ) ;
void CountWordSymbols( unsigned int source[ ], unsigned int n, unsigned int counts[ ], int add ) ;

#endif	/* _COUNT_S_ */