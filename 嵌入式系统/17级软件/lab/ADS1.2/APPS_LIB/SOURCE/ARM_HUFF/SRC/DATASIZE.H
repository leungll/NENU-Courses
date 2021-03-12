/*
 * Data size definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DATASIZE_
#define _DATASIZE_

#ifndef BYTEDATA
	#define BYTEDATA	8
#endif	/* BYTEDATA */

#ifndef HWORDDATA
	#define	HWORDDATA	16
#endif	/* HWORDDATA */

#ifndef	WORDDATA
	#define	WORDDATA	32
#endif	/* WORDDATA */

#ifndef BYTESYMBOL
	#define	BYTESYMBOL	unsigned char
#endif	/* BYTESYMBOL */

#ifndef HWORDSYMBOL
	#define	HWORDSYMBOL	unsigned short
#endif	/* HWORDSYMBOL */

#ifndef WORDSYMBOL
	#define	WORDSYMBOL	unsigned int
#endif	/* WORDSYMBOL */

#ifndef VOIDSYMBOL
	#define	VOIDSYMBOL	void
#endif	/* VOIDSYMBOL */

/*
maximum possible length of codeword that can be created by pure Huffman coding
which, if taking a Fibonnaci sequence as worst case data, would allow
a file of approximately 25,000,000,000,000 bytes in length!

as an idea, 6 terabytes (6,000bn bytes) is approximately:

1.5bn pages of text
120,000 four-drawer filing cabinets
102,000 CD-Roms
3,000,000 standard diskettes
*/
#ifndef MAXPUREHCODEBITS
	#define MAXPUREHCODEBITS	64
#endif	/* MAXPUREHCODEBITS */

/*
the actual maximum number of bits for a codeword after adjusting pure Huffman coding as necessary

27 bits for codeword with 5 bits for length (mininum number of bits of length required for 27)
*/
#ifndef MAXCODEBITS
	#define MAXCODEBITS	27
#endif	/* MAXCODEBITS */

#endif	/* _DATASIZE_ */