/*
 * Discrete Cosine Transform assembler support definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DCT_S_
#define _DCT_S_

#include <stdlib.h>

#define AANBITS 14
/* define the fixed-point shift applied to AANScales data in FDCTScales and RDCTScales */

#define FCOLBITS 1
/* define the fixed-point precision applied to input data for ARM FDCT */

#define RQNTBITS 4
/* define the fixed-point precision applied to input data for ARM RDCT */
#define RDCTBITS ( RQNTBITS + 3 )
/* define the fixed-point precision removal after ARM RDCT */

static unsigned int FDCTScales[ 64 ] = {
	0xe400145d, 0xc4000b89, 0xf40039ff, 0xd4000d9b, 0xc8000c3e, 0xe8001d90, 0xb8001000, 0xd8001000, 
	0xe000145d, 0xc0000b89, 0xf00039ff, 0xd0000d9b, 0xc4000c3e, 0xe4001d90, 0xb4001000, 0xd4001000, 
	0xd6000f96, 0xb60008d4, 0xe6002c62, 0xc6000a6a, 0xba00095f, 0xda0016a0, 0xaa000c3e, 0xca000c3e, 
	0xd20025a0, 0xb2001550, 0xe2006b2c, 0xc2001924, 0xb60016a0, 0xd600369f, 0xa6001d90, 0xc6001d90, 
	0xc90019eb, 0xa9000eae, 0xd90049cd, 0xb9001151, 0xad000f96, 0xcd0025a0, 0x9d00145d, 0xbd00145d, 
	0xbd000eae, 0x9d000851, 0xcd0029cf, 0xad0009cf, 0xa10008d4, 0xc1001550, 0x91000b89, 0xb1000b89, 
	0xbb0049cd, 0x9b0029cf, 0xcb00d238, 0xab003152, 0x9f002c62, 0xbf006b2c, 0x8f0039ff, 0xaf0039ff, 
	0xaf001151, 0x8f0009cf, 0xbf003152, 0x9f000b92, 0x93000a6a, 0xb3001924, 0x83000d9b, 0xa3000d9b
} ;

static unsigned int RDCTScales[ 64 ] = {
	0x00004000, 0x140058c5, 0x0800539f, 0x1c004b42, 0x04004000, 0x10003249, 0x0c0022a3, 0x180011a8, 
	0xa00058c5, 0xb4007b21, 0xa80073fc, 0xbc006862, 0xa40058c5, 0xb00045bf, 0xac00300b, 0xb800187e, 
	0x4000539f, 0x540073fc, 0x48006d41, 0x5c006254, 0x4400539f, 0x500041b3, 0x4c002d41, 0x58001712, 
	0xe0004b42, 0xf4006862, 0xe8006254, 0xfc00587e, 0xe4004b42, 0xf0003b21, 0xec0028ba, 0xf80014c3, 
	0x20004000, 0x340058c5, 0x2800539f, 0x3c004b42, 0x24004000, 0x30003249, 0x2c0022a3, 0x380011a8, 
	0x80003249, 0x940045bf, 0x880041b3, 0x9c003b21, 0x84003249, 0x90002782, 0x8c001b37, 0x98000de0, 
	0x600022a3, 0x7400300b, 0x68002d41, 0x7c0028ba, 0x640022a3, 0x70001b37, 0x6c0012bf, 0x7800098e, 
	0xc00011a8, 0xd400187e, 0xc8001712, 0xdc0014c3, 0xc40011a8, 0xd0000de0, 0xcc00098e, 0xd80004df
} ;
/* constant tables required for scalings and re-ordering the data for both the
   forward and inverse ARM-based DCT algorithms */

typedef unsigned int SCALETABLE[ 64 ] ;
/* data type required by the forward ARM DCT to hold scaling and reordering info */

/**** CREATEDCTBLOCK ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create a 256-byte aligned pointer to a start of a sequence of blocks of 8*8 integers
 * that is suitable for passing to either the forward or reverse ARM DCT's
 *
 * Inputs
 * ------
 *   DCTBLOCKPTR
 *   - an unallocated pointer to an integer
 *   DCTBLOCK
 *   - an unallocated pointer to an integer
 *   NUMBERBLOCKS
 *   - number of blocks required to be referenced by DCTBLOCK once allocated
 * Outputs
 * -------
 *   DCTBLOCKPTR
 *   - a pointer to enough memory to hold (NUMBERBLOCKS+1)/2+2 block pairs, each
 *     block pair of size 256 bytes (64 integers of 4 bytes each)
 *     NULL if memory allocation failed
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to enough memory to hold (NUMBERBLOCKS+1)/2+1
 *     block pairs, each block pair of size 256 bytes (64 integers of 4 bytes each)
 *     NULL if memory allocation failed
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * DCTBLOCKPTR references the actual block of memory allocated
 * deallocate after use (do not try use DCTBLOCK for deallocation)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define CREATEDCTBLOCK( DCTBLOCKPTR, DCTBLOCK, NUMBERBLOCKS ) { \
	DCTBLOCKPTR = ( int * )malloc( ( ( ( NUMBERBLOCKS + 1 )/2 + 2 ) * 256 ) ) ; \
	if( DCTBLOCKPTR != NULL ) { \
		DCTBLOCK = ( int * )( ( int )( DCTBLOCKPTR + 63 ) & ~255 ) ; \
	} \
	else { \
		DCTBLOCK = NULL ; \
	} \
}

/**** CREATEFDCTSTABLEARRAY *********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create the third parameter required in a call to fdct_fast, an array of pointers
 * to the type SCALETABLE
 *
 * Inputs
 * ------
 *   FDCTSTABLEARRAYPTRS
 *   - an unallocated pointer to a pointer to the type SCALETABLE
 *   NUMBERBLOCKS
 *   - number of blocks that are to be passed through to each forward DCT call
 * Outputs
 * -------
 *   FDCTSTABLEARRAYPTRS
 *   - an array of (NUMBERBLOCKS+1)/2 pointers to the type SCALETABLE, each array
 *     entry containg a pointer to the table referenced by FDCTScales
 *     NULL if memory allocation failed
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * FDCTSTABLEARRAYPTRS references the allocated array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define CREATEFDCTSTABLEARRAY( FDCTSTABLEARRAYPTRS, NUMBERBLOCKS ) { \
	unsigned int	blockPairs = ( NUMBERBLOCKS + 1 )/2 ; \
	unsigned int	x ; \
	if( ( FDCTSTABLEARRAYPTRS = ( SCALETABLE ** )calloc( blockPairs, sizeof( SCALETABLE * ) ) ) != NULL ) { \
		for( x = 0 ; x < blockPairs ; x += 1 ) { \
			FDCTSTABLEARRAYPTRS[ x ] = &FDCTScales ; \
		} \
	} \
}

/**** PREFDCT ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * add data in the correct format and order into a structure suitable for passing
 * to the function fdct_fast
 *
 * Inputs
 * ------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that is to hold the data that will be passed to the function fdct_fast
 *   INTVALUE
 *   - the current integer value in the range 0..255 to be added into DCTBLOCK
 *   X, Y
 *   - the column and row co-ordinates respecitvely into the current block for
 *     storing INTVALUE
 *   BCOUNTER
 *   - the current block number in the sequence of blocks in DCTBLOCK where INTVALUE
 *     is to be added
 * Outputs
 * -------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that hold the data that is to be passed through to the forward DCT, inlcuding
 *     INTVALUE stored in the block BCOUNTER at position (X,Y)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define PREFDCT( DCTBLOCK, INTVALUE, X, Y, BCOUNTER ) { \
	if( ( int * )DCTBLOCK != NULL ) { \
		if( BCOUNTER%2 == 0 ) { \
			DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] = INTVALUE << FCOLBITS ; \
		} \
		else { \
			DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] += INTVALUE << ( 16 + FCOLBITS ) ; \
		} \
	} \
}

/**** POSTFDCT **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * extract data from a structure that was passed through to the function fdct_fast
 * and now contains data that has been processed using the forward DCT
 *
 * Inputs
 * ------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that holds the data that has been generated by the function fdct_fast
 *   INTVALUE
 *   - an integer value to hold the current value read from DCTBLOCK
 *   X, Y
 *   - the column and row co-ordinates respecitvely into the current block for
 *     retrieving and storing in INTVALUE
 *   BCOUNTER
 *   - the current block number in the sequence of blocks in DCTBLOCK from which the
 *     integer value is to be retrieved and stored in INTVALUE
 * Outputs
 * -------
 *   INTVALUE
 *   - the integer INTVALUE contains the value read form the block BCOUNTER in
 *     DCTBLOCK, at position (X,Y)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define POSTFDCT( DCTBLOCK, INTVALUE, X, Y, BCOUNTER ) { \
	if( ( int * )DCTBLOCK != NULL ) { \
		if( BCOUNTER%2 == 0 ) { \
			INTVALUE = ( DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] << 16 ) >> 16 ; \
		} \
		else { \
			INTVALUE = DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] >> 16 ; \
		} \
	} \
}

/**** PRERDCT ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * add data in the correct format and order into a structure suitable for passing
 * to the function rdct_fast
 *
 * this process is usually performed in the entropy decoder
 *
 * Inputs
 * ------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that is to hold the data that will be passed to the function rdct_fast with the
 *   INTVALUE
 *   - the current (post FDCT) integer value to be added into DCTBLOCK
 *   X, Y
 *   - the column and row co-ordinates respecitvely into the current block for
 *     storing INTVALUE
 *   BCOUNTER
 *   - the current block number in the sequence of blocks in DCTBLOCK where INTVALUE
 *     is to be added
 * Outputs
 * -------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that hold the data that is to be passed through to the inverse DCT, inlcuding
 *     INTVALUE stored in the block BCOUNTER at position (X,Y)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define PRERDCT( DCTBLOCK, INTVALUE, X, Y, BCOUNTER ) { \
	unsigned int	sTableEntry = RDCTScales[ X + ( Y << 3 ) ] ; \
	if( ( int * )DCTBLOCK != NULL ) { \
		if( BCOUNTER%2 == 0 ) { \
			DCTBLOCK[ 64 + ( sTableEntry >> 26 ) + ( ( BCOUNTER/2 ) * 64 ) ] \
			            	= ( signed )( INTVALUE * ( sTableEntry & 0x00ffffff ) ) >> ( AANBITS - RQNTBITS ) ; \
			/* RDCT expects data shifted out by one block hence 64 added */ \
			/* the DCTBLOCK reference is stored in the top 6-bits of table value */ \
			/* hence the shift by 26 with the actual multiplier stored in the */ \
			/* bottom 24-bit hence these are masked off */ \
			/* the table values were shifted by 14 bits for precision thus reverse */ \
			/* this bu retain some precision in actual value used */ \
		} \
		else { \
			DCTBLOCK[ 64 + ( sTableEntry >> 26 ) + ( ( BCOUNTER/2 ) * 64 ) ] \
			            	+= ( ( signed )( INTVALUE * ( sTableEntry & 0x00ffffff ) ) >> ( AANBITS - RQNTBITS ) ) << 16 ; \
		} \
	} \
}

/**** POSTRDCT **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * extract data from a structure that was passed through to the function rdct_fast
 * and now contains data that has been processed using the inverse DCT
 *
 * Inputs
 * ------
 *   DCTBLOCK
 *   - a 256-byte aligned pointer to the start of a sequence of blocks of 8*8 integers
 *     that holds the data that has been generated by the function rdct_fast
 *   INTVALUE
 *   - an integer value to hold the current value read from DCTBLOCK
 *   X, Y
 *   - the column and row co-ordinates respecitvely into the current block for
 *     retrieving and storing in INTVALUE
 *   BCOUNTER
 *   - the current block number in the sequence of blocks in DCTBLOCK from which the
 *     integer value is to be retrieved and stored in INTVALUE
 * Outputs
 * -------
 *   INTVALUE
 *   - the integer INTVALUE contains the value read form the block BCOUNTER in
 *     DCTBLOCK, at position (X,Y)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define POSTRDCT( DCTBLOCK, INTVALUE, X, Y, BCOUNTER ) { \
	if( ( int * )DCTBLOCK != NULL ) { \
		if( BCOUNTER%2 == 0 ) { \
			INTVALUE = ( ( ( ( DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] << 16 ) >> 16 ) \
							+ ( 1 << RDCTBITS - 1 ) ) >> RDCTBITS ) + 128 ; \
			/* (1<<RDCTBITS-1) rounds to nearest integer with RDCTBITS being shift */ \
			/* back from fixed-point precision */ \
			/* values in DCTBLOCK are AC in the range -128..127 thus need scaling */ \
			/* to the range 0..255 for unsigned chars */ \
		} \
		else { \
			INTVALUE = ( ( ( DCTBLOCK[ Y + ( X << 3 ) + ( ( BCOUNTER/2 ) * 64 ) ] >> 16 ) \
							+ ( 1 << RDCTBITS - 1 ) ) >> RDCTBITS ) + 128 ; \
		} \
	} \
}

void fdct_fast( int *dctBlock, unsigned int nBlocks, SCALETABLE *sTable[ ] ) ;
void rdct_fast( int *dctBlock, unsigned int nBlocks ) ;

#endif	/* _DCT_S_ */