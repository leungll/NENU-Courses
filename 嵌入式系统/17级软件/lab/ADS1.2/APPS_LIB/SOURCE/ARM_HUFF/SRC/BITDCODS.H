/*
 * Bit decode assembler prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _BITDECODE_S_
#define _BITDECODE_S_

#include "datasize.h"
#include "bstreamc.h"

BitStreamStatePtr BitDecodeSymbols( BitStreamStatePtr bitstreamstateptr, unsigned int n, void *dest, unsigned char lentable[ ], void *symtable, unsigned int datatype ) ;

BitStreamStatePtr BitDecodeByteSymbols( BitStreamStatePtr bitstreamstateptr, unsigned int n, unsigned char dest[ ], unsigned char lentable[ ], unsigned char symtable[ ] ) ;
BitStreamStatePtr BitDecodeHalfWordSymbols( BitStreamStatePtr bitstreamstateptr, unsigned int n, unsigned short dest[ ], unsigned char lentable[ ], unsigned short symtable[ ] ) ;
BitStreamStatePtr BitDecodeWordSymbols( BitStreamStatePtr bitstreamstateptr, unsigned int n, unsigned int dest[ ], unsigned char lentable[ ], unsigned int symtable[ ] ) ;

#endif	/* _BITDECODE_S_ */