/*
 * Huffman short decode table
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

/*
define the size of the symbol data as 16 bits and include
the generic function to create the codeword-to-symbol lookup tables
*/
#define	SIZE	16
#include "mkdctm.h"
#undef	SIZE