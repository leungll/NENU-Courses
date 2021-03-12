/*
 * Bitstream
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bstreamc.h"

/*
define the structure used during coding and decoding for a bitstream

the structure is hidden from access external to the functions of this file so that it can contain
any entries that are required by an implementation without all functions that use the structure
needing to know that the structure has changed

the structure contains two extra elements over that that are required the first to maintain the
starting address of the stream, the second to maintain the number of bytes (chars) that have
been allocated to the stream
*/
struct BitStreamState {
	unsigned char	*bitstreamend ;
	unsigned int	freebits ;
	unsigned char	*bitstreamstart ;
	unsigned int	nstreambytes ;
} ;

/**** CreateBitStreamStatePtr *******************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * allocate memory to the bit stream structure and initialise it
 *
 * Inputs
 * ------
 *   nStreamBytes
 *   - the number of bytes (chars) that the stream should reference
 *     if bitstream is given, the parameter defines the number of elements in the given stream
 *   bitstream
 *   - an optional array of characters that will be copied into the stream created
 *     this can be used to create a decoding structure for a stream previously encoded
 *     if the stream is given, it is not simply referenced, it is copied so can be destroyed after
 * Return Values
 * ------ ------
 *     BitStreamStatePtr - a pointer to the bit stream state structure which has been initialised
 *                         if bitstream given was non-NULL, the returned stream contains the same data
 *     NULL			     - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned pointer to stream state structure
 * deallocate after use by calling DisposeBitStreamStatePtr
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static BitStreamStatePtr CreateBitStreamStatePtr( unsigned int nStreamBytes, unsigned char *bitstream )
{
	unsigned char		*newbitstream ;
	BitStreamStatePtr 	bitstreamstateptr ;
	unsigned int		i ;

	if( nStreamBytes == 0 ) {
		fprintf( stderr, "[CreateBitStreamStatePtr] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	nStreamBytes = ( ( nStreamBytes + 3 ) >> 2 ) << 2 ;		/* ensure number of bytes divisble by four - gives whole words */
	
	/*
	allocate space for the structure and the bitstream
	
	the bistream is allocated at the same time so that it starts in memory immediately after the last element in the 
	structure and thus the pointer initially is the first address past the end of the structure
	*/
	if( ( bitstreamstateptr = ( BitStreamStatePtr )calloc( 1, sizeof( BitStreamState ) + nStreamBytes*sizeof( unsigned char ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	/* set up the initial stream pointer as first address past end of structure */
	newbitstream = ( unsigned char * )( ( int )bitstreamstateptr + sizeof( BitStreamState ) ) ;
	
	/* initialise all structure elements */
	bitstreamstateptr->bitstreamstart = newbitstream ;
	bitstreamstateptr->freebits = 32 ;
	bitstreamstateptr->nstreambytes = nStreamBytes ;
	bitstreamstateptr->bitstreamend = bitstreamstateptr->bitstreamstart ;
	
	/* if a stream has been given, copy it's data into the stream created */
	if( bitstream != NULL ) {
		for( i = 0 ; i < nStreamBytes ; i += 1 ) {
			bitstreamstateptr->bitstreamstart[ i ] = bitstream[ i ] ;
		}
	}
	
	return bitstreamstateptr ;
}

/**** InitBitStreamStateDecoding ****************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * deallocate the memory that has been allocated to a given bit stream state structure
 *
 * Inputs
 * ------
 *   bitstreamstateptr
 *   - a bit stream state structure that has been allocated and is no longer required
 *     so its memory should be deallocated
 *
 * Memory deallocated (not allocated)
 * ------ -----------  --- ---------
 * the given bit stream state structure
 * allocated by InitBitStreamStateCoding or InitBitStreamStateDecoding
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void DisposeBitStreamStatePtr( BitStreamStatePtr bitstreamstateptr )
{
	if( bitstreamstateptr == NULL ) {
		return ;
	}
	
	free( ( void * ) bitstreamstateptr ) ;
}
	
/**** GetBitStreamFromState *********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get a reference to the bitstream from the given bit stream state structure
 *
 * Inputs
 * ------
 *   bitstreamstateptr
 *   - a bit stream state structure from which the bit stream should be retrieved
 *   nStreamBytes
 *   - a pointer to an unsigned int to hold the number of bytes referenced by the stream returned
 * Outputs
 * -------
 *   nStreamBytes
 *   - the number of bytes (chars) referenced by the returned stream
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     unsigned char * - a reference to the bit stream in the given structure
 *                       a copy is not returned, only a reference so do not deallocate it
 *     NULL            - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned char *GetBitStreamFromState( BitStreamStatePtr bitstreamstateptr, unsigned int *nStreamBytes )
{
	if( ( bitstreamstateptr == NULL ) || ( nStreamBytes == NULL ) ) {
		fprintf( stderr, "[GetBitStreamFromState] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	*nStreamBytes = bitstreamstateptr->nstreambytes ;
	
	return bitstreamstateptr->bitstreamstart ;
}

/**** GetNumberBitsInStream *********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * determine the actual number of coded bits referenced by the stream in the structure
 * given
 *
 * Inputs
 * ------
 *   bitstreamstateptr
 *   - a bit stream state structure from which the number of bits referenced by the bit stream 
 *     should be retrieved
 * Return Values
 * ------ ------
 *     unsigned int - the number of bits referenced by the bit stream in the given structure
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int GetNumberBitsInStream( BitStreamStatePtr bitstreamstateptr )
{
	unsigned int	numberbits ;
	
	if( bitstreamstateptr == NULL ) {
		fprintf( stderr, "[GetNumberBytesInStream] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	/* get number of whole bytes used */
	numberbits = ( unsigned int )( bitstreamstateptr->bitstreamend - bitstreamstateptr->bitstreamstart ) ;
	/* multiply by number of bits per byte */
	numberbits *= 8 ;
	/* add number of bits in the next four bytes that also contain coded data */
	numberbits += ( 32 - bitstreamstateptr->freebits ) ;
	
	return numberbits ;
}
	
/**** InitBitStreamStateCoding ******************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * allocate memory to a bit stream structure for coding and initialise it
 *
 * Inputs
 * ------
 *   nStreamBytes
 *   - the number of bytes (chars) that the stream should reference
 * Return Values
 * ------ ------
 *     BitStreamStatePtr - a pointer to the bit stream state structure which has been initialised
 *     NULL			     - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned pointer to stream state structure
 * deallocate after use by calling DisposeBitStreamStatePtr
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
BitStreamStatePtr InitBitStreamStateCoding( unsigned int nStreamBytes )
{
	return CreateBitStreamStatePtr( nStreamBytes, NULL ) ;
}

/**** InitBitStreamStateDecoding ****************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * allocate memory to a bit stream structure for decoding and initialise it
 *
 * Inputs
 * ------
 *   nStreamBytes
 *   - the number of bytes (chars) that the stream should reference
 *     if bitstream is given, the parameter also defines the number of elements in the given stream
 *   bitstream
 *   - an optional array of characters that will be copied into the stream created
 *     this stream if given should be previously encoded bit stream that is to be decoded
 *     if the stream is given, it is not simply referenced, it is copied so can be destroyed after
 *     bitstream is given a higher priority over codedbitstreamstateptr if given and this stream is used
 *   codedbitstreamstateptr
 *   - an optional bit stream state structure that has been used for coding and the stream referenced
 *     by it should now be decoded
 *     if the structure is given, the stream referenced is copied and so can be destroyed after passing here
 *     codedbitstreamstateptr has a lower priority than bitstream if given and bitstream is used
 * Return Values
 * ------ ------
 *     BitStreamStatePtr - a pointer to the bit stream state structure which has been initialised
 *                         if bitstream or codedbitstreamstateptr given were non-NULL, the returned structure
 *                         has the stream containing the same data
 *     NULL			     - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned pointer to stream state structure
 * deallocate after use by calling DisposeBitStreamStatePtr
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
BitStreamStatePtr InitBitStreamStateDecoding( unsigned char *bitstream, unsigned int nStreamBytes, BitStreamStatePtr codedbitstreamstateptr )
{
	unsigned char		*oldbitstream ;
	unsigned int		oldstreambytes ;

	if( bitstream != NULL ) {
		oldbitstream = bitstream ;
		oldstreambytes = nStreamBytes ;
	}
	else if( codedbitstreamstateptr != NULL ) {
		oldbitstream = GetBitStreamFromState( codedbitstreamstateptr, &oldstreambytes ) ;
	}
	else {
		oldbitstream = NULL ;
		oldstreambytes = 0 ;
	}
	
	return( CreateBitStreamStatePtr( oldstreambytes, oldbitstream ) ) ;
}

