/*
 * Huffman word decode table
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

/*
define the size of the symbol data as 32 bits and include
the generic function to create the codeword-to-symbol lookup tables
*/
#define	SIZE	32
#include "mkdctm.h"
#undef	SIZE