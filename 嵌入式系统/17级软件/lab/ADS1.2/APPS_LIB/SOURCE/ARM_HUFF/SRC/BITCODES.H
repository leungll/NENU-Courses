/*
 * Bit code assembler prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _BITCODE_S_
#define _BITCODE_S_

#include "datasize.h"
#include "bstreamc.h"

BitStreamStatePtr BitCodeSymbols( void *source, unsigned int n, BitStreamStatePtr bitstreamstateptr, unsigned int codetable[ ], unsigned int datatype ) ;

BitStreamStatePtr BitCodeByteSymbols( unsigned char source[ ], unsigned int n, BitStreamStatePtr bitstreamstateptr, unsigned int codetable[ ] ) ;
BitStreamStatePtr BitCodeHalfWordSymbols( unsigned short source[ ], unsigned int n, BitStreamStatePtr bitstreamstateptr, unsigned int codetable[ ] ) ;
BitStreamStatePtr BitCodeWordSymbols( unsigned int source[ ], unsigned int n, BitStreamStatePtr bitstreamstateptr, unsigned int codetable[ ] ) ;

#endif	/* _BITCODE_S_ */