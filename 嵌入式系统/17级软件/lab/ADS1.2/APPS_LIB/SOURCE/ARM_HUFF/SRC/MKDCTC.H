/*
 * Huffman decode table prototype definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _MAKE_DCT_C_
#define _MAKE_DCT_C_

/*
protect file from multiple inclusion with same size data
*/
#if SIZE == 8
	#ifdef _MAKE_DCT_C_G8_
		#define	GUARD
	#else
		#define _MAKE_DCT_C_G8_
	#endif
#elif SIZE == 16
	#ifdef _MAKE_DCT_C_G16_
		#define	GUARD
	#else
		#define _MAKE_DCT_C_G16_
	#endif
#elif SIZE == 32
	#ifdef _MAKE_DCT_C_G32_
		#define	GUARD
	#else
		#define _MAKE_DCT_C_G32_
	#endif
#endif

#ifndef	GUARD

#include "datasize.h"

/* TYPE is undefined here rather than at the end after declaration since it is used after the header inclusion */
#ifdef TYPE
	#undef	TYPE
#endif

#if SIZE == 8
	#define TYPE	BYTESYMBOL
#elif SIZE == 16
	#define TYPE	HWORDSYMBOL
#elif SIZE == 32
	#define TYPE	WORDSYMBOL
#endif

/* require both #defines below since nested preprocessor # statements */
#define MDCTPROTOTYPE( SYMBOLSIZE, SYMBOLTYPE ) \
	SYMBOLTYPE *MakeHuffDecodeTable ## SYMBOLSIZE( SYMBOLTYPE symbols[ ], unsigned int nsymbols, unsigned int freqcodelen[ ], unsigned int maxcodewlen, unsigned int tablebits, unsigned char **lentable )

#define MDCTFUNCTIONDECLARATION( SYMBOLSIZE, SYMBOLTYPE ) MDCTPROTOTYPE( SYMBOLSIZE, SYMBOLTYPE )

MDCTFUNCTIONDECLARATION( SIZE, TYPE ) ;

#endif	/* !GUARD */

#endif	/* _MAKE_DCT_C_ */
