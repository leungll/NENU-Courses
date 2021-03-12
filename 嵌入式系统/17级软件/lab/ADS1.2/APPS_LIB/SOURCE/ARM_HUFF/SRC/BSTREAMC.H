/*
 * Bitstream prototype and definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _BITSTREAM_C_
#define _BITSTREAM_C_

#ifndef __BITSTREAMSTATE
#define __BITSTREAMSTATE

typedef struct	BitStreamState	BitStreamState ;
typedef			BitStreamState	*BitStreamStatePtr ;

/*
struct BitStreamState {
	unsigned char	*bitstreamend ;
	unsigned int	freebits ;
	...
} ;
*/

#endif	/* __BITSTREAMSTATE */

void DisposeBitStreamStatePtr( BitStreamStatePtr bitstreamstateptr ) ;
unsigned char *GetBitStreamFromState( BitStreamStatePtr bitstreamstateptr, unsigned int *nStreamBytes ) ;
unsigned int GetNumberBitsInStream( BitStreamStatePtr bitstreamstateptr ) ;
BitStreamStatePtr InitBitStreamStateCoding( unsigned int nStreamBytes ) ;
BitStreamStatePtr InitBitStreamStateDecoding( unsigned char *bitstream, unsigned int nStreamBytes, BitStreamStatePtr codedbitstreamstateptr ) ;

#endif	/* _BITSTREAM_C_ */