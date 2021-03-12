/*
 * Huffman test harness
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <ctype.h>
#include <stdlib.h>

#include "hufftesc.h"

#include "bitcodes.h"
#include "bitdcods.h"
#include "bstreamc.h"
#include "counts.h"
#include "huffmanc.h"
#include "makct8c.h"
#ifdef	_MAKE_CT_C_
	#undef	_MAKE_CT_C_	/* undefine makctc.h against multiple inclusion */
#endif
#ifdef	MCTPROTOTYPE
	#undef	MCTPROTOTYPE	/* undefine prototype for next inclusion */
#endif
#ifdef	MCTFUNCTIONDECLARATION
	#undef	MCTFUNCTIONDECLARATION	/* undefine declaration for next inclusion */
#endif
#include "makct16c.h"
#ifdef	_MAKE_CT_C_
	#undef	_MAKE_CT_C_	/* undefine makctc.h against multiple inclusion */
#endif
#ifdef	MCTPROTOTYPE
	#undef	MCTPROTOTYPE	/* undefine prototype for next inclusion */
#endif
#ifdef	MCTFUNCTIONDECLARATION
	#undef	MCTFUNCTIONDECLARATION	/* undefine declaration for next inclusion */
#endif
#include "makct32c.h"
#include "mkdct8c.h"
#ifdef	_MAKE_DCT_C_
	#undef	_MAKE_DCT_C_	/* undefine makctc.h against multiple inclusion */
#endif
#ifdef	MDCTPROTOTYPE
	#undef	MDCTPROTOTYPE	/* undefine prototype for next inclusion */
#endif
#ifdef	MDCTFUNCTIONDECLARATION
	#undef	MDCTFUNCTIONDECLARATION	/* undefine declaration for next inclusion */
#endif
#include "mkdct16c.h"
#ifdef	_MAKE_DCT_C_
	#undef	_MAKE_DCT_C_	/* undefine makctc.h against multiple inclusion */
#endif
#ifdef	MDCTPROTOTYPE
	#undef	MDCTPROTOTYPE	/* undefine prototype for next inclusion */
#endif
#ifdef	MDCTFUNCTIONDECLARATION
	#undef	MDCTFUNCTIONDECLARATION	/* undefine declaration for next inclusion */
#endif
#include "mkdct32c.h"

#include "custredc.h"
#include "definesc.h"
#include "fileutlc.h"
#include "optionsc.h"
#include "printinc.h"

#define	HUFFMAN_OPTIONS	3

/* this defines the number of times Bit(De)CodeSymbols will be called for encoding/decoding to prove this feature */
#ifndef CODECSPLIT
	#define CODECSPLIT	11
#endif	/* CODECSPLIT */

/* the maximum length of codeword in bits that will be looked up in table for decoding - rest are tree-decoded */
#ifndef TABLEBITS
	#define	TABLEBITS	10
#endif	/* TABLEBITS */

/*
define maximum number of Fibonacci terms in the data
maximum possible Fibonacci value with 20-bits of data is F27 = 317811 with 832039 total entries
*/
#ifndef MAXFIBTERMS
	#define MAXFIBTERMS		28
#endif	/* MAXFIBTERMS */

/* maximum possible Fibonacci value in 8-bit data is F12 = 233 with 609 total entries (10-bits of data) */
#ifndef MAXFIB8TERMS
	#define MAXFIB8TERMS	13
#endif	/* MAXFIB8TERMS */

/* maximum possible Fibonacci value in 16-bit data is F23 = 46368 with 121392 total entries (17-bits of data) */
#ifndef MAXFIB16TERMS
	#define MAXFIB16TERMS	24
#endif	/* MAXFIB16TERMS */

/* define symbol union - only one symbol type will exist at any time */
typedef union	SymbolUnion	SymbolUnion ;
typedef			SymbolUnion	*SymbolUnionPtr ;

union SymbolUnion {
	unsigned char	byte ;
	unsigned short	hword ;
	unsigned int	word ;
} ;

/* define a symbol as structure of union (actual symbol) and identifier tag to determine symbol type */
typedef struct	Symbol		Symbol ;
typedef			Symbol		*SymbolPtr ;

typedef enum{ BYTE, HWORD, WORD } SymbolType ;

struct Symbol {
	SymbolType	symboltype ;
	SymbolUnion	symbol ;
} ;

/* set up symbol with frequency count structure */
typedef struct	SymbolCount	SymbolCount ;
typedef			SymbolCount	*SymbolCountPtr ;

struct SymbolCount {
	unsigned int	count ;
	Symbol			symbol ;
} ;

static void *CreateFibonacci( unsigned int datatype, unsigned int *n ) ;
static void *HuffmanDecode( void *symbols, unsigned int nSymbols, unsigned int nInputs, BitStreamStatePtr encodedBitStreamDataPtr, unsigned int datatype, unsigned int freqCodeLen[ ], unsigned int maxcwlen ) ;
static BitStreamStatePtr HuffmanEncode( void *inputs, unsigned int nInputs, void *symbols, unsigned int nSymbols, unsigned int datatype, unsigned int freqCodeLen[ ], unsigned int maxcwlen, unsigned int *bitlength ) ;
static void Menu( unsigned int numberOptions ) ;
static unsigned int *PrepareHuffman( void *inputs, unsigned int nInputs, unsigned int datatype, unsigned int maxSymbol, unsigned int maxcwlen, void **symbolsptr ) ;
static int SymbolCountSort( const void *symbolcount1, const void *symbolcount2 ) ;

/**** Code **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * obtains a set of data from user (either from test file or Fibonacci data created
 * in this routine), Huffman encodes it, Huffman decodes this immediately and compares
 * the results
 *
 * the decoded data is also written to a file if decoding was successful
 *
 * Inputs
 * ------
 *   option
 *   - a value that should be between 1 and 3 and returned from a call to NextTask
 *     the value corresponds to a menu choice and determines the type of data to be
 *     Huffman encoded/decoded
 *     1 = byte data
 *     2 = half word data
 *     3 = word data
 * Return Values
 * ------ ------
 *     TRUE  - the entire coding process was successful and data written
 *     FALSE - some error occurred during process (memory problems?)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static Boolean Code( unsigned int option )
{
	void				*inputs = NULL ;
	unsigned int		nInputs ;
	unsigned int		datatype ;
	unsigned int		isFib ;
	unsigned int		maxSymbol ;
	unsigned int		*freqCodeLen ;
	void				*symbols ;
	BitStreamStatePtr	encodedBitStreamStatePtr ;
	unsigned int		encodedBitLength ;
	void				*decoded ;
	unsigned int		i ;
	Boolean				failed ;

	printf( "Perform Huffman encoding and decoding...\n\n" ) ;
	
	datatype = 8 << ( option - 1 ) ;
	
	isFib = YesNo( "Huffman encode/decode on a set of Fibonacci data", "Fibonacci", "open test file" ) ;
	switch( isFib ) {
		case 0 :
        	if( ( inputs = GetData( datatype/8, "input", &nInputs ) ) == NULL ) {
        		return FALSE ;
        	}
       		break ;
		case 1 :
        	if( ( inputs = CreateFibonacci( datatype, &nInputs ) ) == NULL ) {
        		return FALSE ;
        	}
        	break ;
		default :
			break ;
	}
	
	printf( "Number of data items for Huffman encoding/decoding is '%d'\n\n", nInputs ) ;
	
	printf( "Determining the maximum symbol value in data...\n\n" ) ;
	
	maxSymbol = 0 ;
	for( i = 0 ; i < nInputs ; i += 1 ) {
		switch( datatype ) {
			case BYTEDATA :
				maxSymbol = MAX( maxSymbol, ( unsigned int )( ( ( unsigned char * )inputs )[ i ] ) ) ;
				break ;
			case HWORDDATA :
				maxSymbol = MAX( maxSymbol, ( unsigned int )( ( ( unsigned short * )inputs )[ i ] ) ) ;
				break ;
			case WORDDATA :
				maxSymbol = MAX( maxSymbol, ( unsigned int )( ( ( unsigned int * )inputs )[ i ] ) ) ;
				break ;
			default :
				break ;
		}
	}
	
	printf( "The maximum symbol value in the input data is 0x" ) ;
	switch( datatype ) {
		case BYTEDATA :
			printf( "%.2x", maxSymbol ) ;
			break ;
		case HWORDDATA :
			printf( "%.4x", maxSymbol ) ;
			break ;
		case WORDDATA :
			printf( "%.8x", maxSymbol ) ;
			break ;
		default :
			break ;
	}
	printf( "\n\n" ) ;
	
	maxSymbol += 1 ;
	
	if( ( freqCodeLen = PrepareHuffman( inputs, nInputs, datatype, maxSymbol, MAXCODEBITS, &symbols ) ) == NULL ) {
		free( inputs ) ;
		return FALSE ;
	}

	encodedBitStreamStatePtr = HuffmanEncode( inputs, nInputs, symbols, maxSymbol, datatype, freqCodeLen, MAXCODEBITS, &encodedBitLength ) ;
	if( !encodedBitStreamStatePtr ) {
		free( inputs ) ;
		free( freqCodeLen ) ;
		free( symbols ) ;
		return FALSE ;
	}
	
	decoded = HuffmanDecode( symbols, maxSymbol, nInputs, encodedBitStreamStatePtr, datatype, freqCodeLen, MAXCODEBITS ) ;

	free( freqCodeLen ) ;
	free( symbols ) ;
	free( encodedBitStreamStatePtr ) ;
	if( !decoded ) {
		free( inputs ) ;
		return FALSE ;
	}

	printf( "Comparing the data input to the Huffam encoder and the data output from the Huffman decoder...\n\n" );
	
	failed = FALSE ;
	for( i = 0 ; i < nInputs ; i += 1 ) {
		switch( datatype ) {
			case BYTEDATA :
				if( ( ( unsigned char * )inputs )[ i ] != ( ( unsigned char * )decoded )[ i ] ) {
					printf( "error in output %d: original value 0x%.2x, retrieved value 0x%.2x\n", i, ( ( unsigned char * )inputs )[ i ], ( ( unsigned char * )decoded )[ i ] ) ;
					failed = TRUE ;
				}
				break ;
			case HWORDDATA :
				if( ( ( unsigned short * )inputs )[ i ] != ( ( unsigned short * )decoded )[ i ] ) {
					printf( "error in output %d: original value 0x%.4x, retrieved value 0x%.4x\n", i, ( ( unsigned short * )inputs )[ i ], ( ( unsigned short * )decoded )[ i ] ) ;
					failed = TRUE ;
				}
				break ;
			case WORDDATA :
				if( ( ( unsigned int * )inputs )[ i ] != ( ( unsigned int * )decoded )[ i ] ) {
					printf( "error in output %d: original value 0x%.8x, retrieved value 0x%.8x\n", i, ( ( unsigned int * )inputs )[ i ], ( ( unsigned int * )decoded )[ i ] ) ;
					failed = TRUE ;
				}
				break ;
			default :
				break ;
		}
	}
	
	if( !failed ) {
		printf( "The input and output data are equal.\n\n" ) ;
		
		if( ( !isFib ) || ( isFib && YesNo( "Do you want to save the Fibonacci data", "save Fibonacci", "don't save Fibonacci" ) ) ) {
			SaveData( decoded, nInputs, datatype/8, 1, "decoded" ) ;
		}
	}
	else {
		printf( "\n" ) ;
		printf( "Errors occurred in Huffman encoding/decoding the data.\n\n" ) ;
	}
	
	free( inputs ) ;
	free( decoded ) ;
	
	if( !failed ) {
		return FALSE ;
	}
	else {
		return TRUE ;
	}
}

/**** CreateFibonacci ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create a set of Fibonacci data such that for each Fibonacci value, it is placed
 * into the data array as many times as its value e.g. F4 = 5 has five array entries
 * 
 * Inputs
 * ------
 *   datatype
 *   - the type of data to create
 *     BYTEDATA		create byte-size data
 *     HWORDDATA 	create halfword-size data
 *     WORDDATA		create word-size data
 *   n
 *   - pointer to unsigned int to hold the number of data items created
 * Outputs
 * -------
 *   n
 *   - pointer to unsigned int that defines number of data items referenced by array returned
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     void * - the created array of data
 *              array is unsigned char, unsigned short or unsigned int data according to value 
 *              of datatype and needs casting to appropriate type before it can be used
 *     NULL   - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void *CreateFibonacci( unsigned int datatype, unsigned int *n )
{
	void			*fib ;
	unsigned int	fibn, fibn1 ;
	unsigned int	maxfibterms ;
	unsigned int	fibterms ;
	unsigned int	i, j ;
	
	if( n == NULL ) {
		fprintf( stderr, "[CreateFibonacci] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	printf( "Please give the number of Fibonacci terms in the data.\n\n" ) ;
	
	switch( datatype ) {
		case BYTEDATA :
			maxfibterms = MAXFIB8TERMS ;
			break ;
		case HWORDDATA :
			maxfibterms = MAXFIB16TERMS ;
			break ;
		case WORDDATA :
			maxfibterms = MAXFIBTERMS ;
			break ;
		default :
			fprintf( stderr, "[CreateFibonacci] Error in input arguments, aborting.\n\n" ) ;
			/* function name given since intended as internal error for programmer */
			return NULL ;
	}
	
	do {
		printf( "Number of of Fibonacci terms (2 to %d) : ", maxfibterms ) ;
		fibterms = ( int )ReadDouble( ) ;
		if( ( fibterms < 2 ) || ( fibterms > maxfibterms ) ) {
			printf( "'%d' is outside of the valid Fibonacci range, please choose again.\n\n", fibterms ) ;
		}
		else {
			break ;
		}
	} while( 1 ) ;
	
	if( fibterms < 17 ) {
		*n = ( 1 << ( fibterms - ( ( fibterms + 1 )/3 ) + 1 ) ) ;
	}
	else {
		*n = ( 1 << ( fibterms - ( fibterms/3 ) + 2 ) ) ;
	}
	
	printf( "Creating Fibonacci sequence...\n\n" ) ;
	
	if( ( fib = calloc( *n, datatype/8 ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	switch( datatype ) {
		case BYTEDATA :
			( ( unsigned char * )fib )[ 0 ] = ( ( unsigned char * )fib )[ 1 ] = 1 ;
			break ;
		case HWORDDATA :
			( ( unsigned short * )fib )[ 0 ] = ( ( unsigned short * )fib )[ 1 ] = 1 ;
			break ;
		case WORDDATA :
			( ( unsigned int * )fib )[ 0 ] = ( ( unsigned int * )fib )[ 1 ] = 1 ;
			break ;
		default :
			free( fib ) ;
			return NULL ;
	}
	fibterms -= 2 ;
	
	fibn1 = 1 ;
	fibn = 2 ;
	for( i = 2 ; ( fibterms > 0 ) && ( i < *n ) ; ) {
		for( j = i ; j < ( ( ( i + fibn ) < *n ) ? ( i + fibn ) : *n ) ; j += 1 ) {
			switch( datatype ) {
				case BYTEDATA :
					( ( unsigned char * )fib )[ j ] = ( unsigned char )fibn ;
					break ;
				case HWORDDATA :
					( ( unsigned short * )fib )[ j ] = ( unsigned short )fibn ;
					break ;
				case WORDDATA :
					( ( unsigned int * )fib )[ j ] = fibn ;
					break ;
			}
		}
		fibn = fibn + fibn1 ;
		fibn1 = fibn - fibn1 ;
		i = j ;
		fibterms -= 1 ;
	}
	if( i < *n ) {
		*n = i ;
	}
	
	printf( "A Fibonacci sequence has been created with %d entries.\n\n", *n ) ;
	
	return fib ;
}

/**** GetSymbolsFromSymbolCount *****************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the array of sorted symbols from an array of structures of symbols and frequency of occurrence
 * for each symbol
 * 
 * Inputs
 * ------
 *   symbolcountptr
 *   - an array of symbol count structures that references the sorted symbols and frequencies
 *   nSymbols
 *   - the number of structures referenced by the array given
 * Return Values
 * ------ ------
 *     void * - the created array of sorted symbols with nSymbols entries
 *              array is unsigned char, unsigned short or unsigned int data according to symbol type
 *              given in the structures and needs casting to the appropriate type before it can be used
 *     NULL   - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void *GetSymbolsFromSymbolCount( SymbolCountPtr symbolcountptr, unsigned int nSymbols )
{
	void			*symbols ;
	unsigned int	i ;
	
	if( ( symbolcountptr == NULL ) || ( nSymbols == 0 ) ) {
		fprintf( stderr, "[GetSymbolsFromSymbolCount] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	switch( symbolcountptr[ 0 ].symbol.symboltype ) {
		case BYTE :
			symbols = calloc( nSymbols, sizeof( unsigned char ) ) ;
			break ;
		case HWORD :
			symbols = calloc( nSymbols, sizeof( unsigned short ) ) ;
			break ;
		case WORD :
			symbols = calloc( nSymbols, sizeof( unsigned int ) ) ;
			break ;
		default :
			fprintf( stderr, "[GetSymbolsFromSymbolCount] Error in input arguments, aborting.\n\n" ) ;
			/* function name given since intended as internal error for programmer */
			return NULL ;
	}
	if( symbols == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}

	for( i = 0 ; i < nSymbols ; i += 1 ) {
		switch( symbolcountptr[ i ].symbol.symboltype ) {
			case BYTE :
				( ( unsigned char * )symbols )[ i ] = symbolcountptr[ i ].symbol.symbol.byte ;
				break ;
			case HWORD :
				( ( unsigned short * )symbols )[ i ] = symbolcountptr[ i ].symbol.symbol.hword ;
				break ;
			case WORD :
				( ( unsigned int * )symbols )[ i ] = symbolcountptr[ i ].symbol.symbol.word ;
				break ;
			default :
				break ;
		}
	}
	
	return symbols ;
}

/**** huff_main *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * initialise the application then loop whilst the user is still working
 *
 * Return Values
 * ------ ------
 *     0 - application terminated correctly
 *     1 - some error occurred
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int huff_main( int argc, char **argv )
{
	unsigned int	option ;
#ifdef	__BIG_ENDIAN
	char			newStdIn[ ] = "stdinb" ;
	char			newStdOut[ ] = "stdoutb" ;
	char			newStdErr[ ] = "stderrb" ;
#else
	char			newStdIn[ ] = "stdinl" ;
	char			newStdOut[ ] = "stdoutl" ;
	char			newStdErr[ ] = "stderrl" ;
#endif
	unsigned int	stdio = 0 ;
	
	if( ChangeStdIO( &argc, &argv, newStdIn, stdin ) == STDINID ) {
		stdio |= ( 1 << STDINID ) ;
	}
	if( ChangeStdIO( &argc, &argv, newStdOut, stdout ) == STDOUTID ) {
		stdio |= ( 1 << STDOUTID ) ;
	}
	if( ChangeStdIO( &argc, &argv, newStdErr, stderr ) == STDERRID ) {
		stdio |= ( 1 << STDERRID ) ;
	}
	
	printf( "Program to perform Huffman encoding and decoding.\n\n" ) ;
	
	while( 1 ) {
		if( ( option = NextTask( HUFFMAN_OPTIONS, &Menu ) ) == 0 ) {
			break ;
		}
		
		Code( option ) ;
	}
	
	/* redirection based on trying to open files that don't exist do using defaults */
	if( stdio & ( 1 << STDINID ) ) {
		ResetStdIO( stdin ) ;
	}
	if( stdio & ( 1 << STDOUTID ) ) {
		ResetStdIO( stdout ) ;
	}
	if( stdio & ( 1 << STDERRID ) ) {
		ResetStdIO( stderr ) ;
	}
	
	return 0 ;
}

/**** HuffmanDecode *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * decode a previously Huffman encoded bit stream to retrieve the original data before
 * coding
 * 
 * Inputs
 * ------
 *   symbols
 *   - an array of symbols that occurred in the original data sorted into increasing order
 *     of frequency of occurrence
 *     the symbols should be unsigned char, unsigned short or unsigned int determined by datatype
 *   nSymbols
 *   - the number of symbols referenced by the array
 *   nOutputs
 *   - the number of symbols to retrieve from the encoded data
 *     this value is normally the number of symbols that have been encoded
 *   encodedBitStreamDataPtr
 *   - a pointer to a bit stream state structure that contains the bit stream to decode
 *   datatype
 *   - the type of the symbols and data to retrieve
 *     BYTEDATA		byte-size data
 *     HWORDDATA 	halfword-size data
 *     WORDDATA		word-size data
 *   freqCodeLen
 *   - an array of frequency of occurrence for each length of codeword
 *   maxcodewlen
 *   - the maximum length of codeword in the coded data
 *     (maxcodewlen+1) also defines the maximum index into the array freqCodeLen
 * Return Values
 * ------ ------
 *     void * - the decoded array of data
 *              array is unsigned char, unsigned short or unsigned int data according to datatype
 *              and needs casting to the appropriate type before it can be used
 *     NULL   - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void *HuffmanDecode( void *symbols, unsigned int nSymbols, unsigned int nOutputs, BitStreamStatePtr encodedBitStreamDataPtr, unsigned int datatype, unsigned int freqCodeLen[ ], unsigned int maxcwlen )
{
	BitStreamStatePtr	bitStreamStatePtr ;
	void				*decoded ;
	void				*decodeTable ;
	unsigned char		*codedLengths ;
	unsigned int		nDecodes ;
	unsigned int		i ;
	
	if( ( symbols == NULL ) || ( nSymbols == 0 ) || ( nOutputs == 0 ) || ( encodedBitStreamDataPtr == NULL ) || ( freqCodeLen == NULL ) || ( maxcwlen == 0 ) || ( maxcwlen > MAXCODEBITS ) ) {
		fprintf( stderr, "[HuffmanDecode] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	printf( "Initialising the Huffman stream for decoding...\n\n" ) ;
	
	/* could dispose of encodedBitStreamDataPtr after creating decoding structure, however this is not done here */
	if( ( bitStreamStatePtr = InitBitStreamStateDecoding( NULL, 0, encodedBitStreamDataPtr ) ) == NULL ) {
		return NULL ;
	}
	
	printf( "Stream for decoding initialised.\n\n" ) ;
	
	switch( datatype ) {
		case BYTEDATA :
			decoded = calloc( nOutputs, sizeof( unsigned char ) ) ;
			break ;
		case HWORDDATA :
			decoded = calloc( nOutputs, sizeof( unsigned short ) ) ;
			break ;
		case WORDDATA :
			decoded = calloc( nOutputs, sizeof( unsigned int ) ) ;
			break ;
		default :
			fprintf( stderr, "[HuffmanDecode] Error in input arguments, aborting.\n\n" ) ;
			decoded = NULL ;
	}
	
	if( decoded == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		DisposeBitStreamStatePtr( bitStreamStatePtr ) ;
		return NULL ;
	}
	
	printf( "Generating the Huffman decoding table and tree...\n\n" ) ;
	
	switch( datatype ) {
		case BYTEDATA :
			decodeTable = MakeHuffDecodeTable8( ( unsigned char * )symbols, nSymbols, freqCodeLen, maxcwlen, TABLEBITS, &codedLengths ) ;
			break ;
		case HWORDDATA :
			decodeTable = MakeHuffDecodeTable16( ( unsigned short * )symbols, nSymbols, freqCodeLen, maxcwlen, TABLEBITS, &codedLengths ) ;
			break ;
		case WORDDATA :
			decodeTable = MakeHuffDecodeTable32( ( unsigned int * )symbols, nSymbols, freqCodeLen, maxcwlen, TABLEBITS, &codedLengths ) ;
			break ;
		default :
			fprintf( stderr, "[HuffmanDecode] Error in input arguments, aborting.\n\n" ) ;
			decodeTable = NULL ;
	}
	if( decodeTable == NULL ) {
		DisposeBitStreamStatePtr( bitStreamStatePtr ) ;
		free( decoded ) ;
		return NULL ;
	}
	
	printf( "Huffman decoding table and tree generated.\n\n" ) ;
	
	printf( "Huffman decoding the data...\n\n" ) ;

	for( i = 0 ; i < CODECSPLIT ; i += 1 ) {
		if( i == CODECSPLIT - 1 ) {
			nDecodes = nOutputs - ( i * ( nOutputs/CODECSPLIT ) ) ;
		}
		else {
			nDecodes = nOutputs/CODECSPLIT ;
		}
		switch( datatype ) {
			case BYTEDATA :
				bitStreamStatePtr = BitDecodeSymbols( bitStreamStatePtr, nDecodes, ( ( unsigned char * )decoded ) + ( i * ( nOutputs/CODECSPLIT ) ), codedLengths, decodeTable, datatype ) ;
				break ;
			case HWORDDATA :
				bitStreamStatePtr = BitDecodeSymbols( bitStreamStatePtr, nDecodes, ( ( unsigned short * )decoded ) + ( i * ( nOutputs/CODECSPLIT ) ), codedLengths, decodeTable, datatype ) ;
				break ;
			case WORDDATA :
				bitStreamStatePtr = BitDecodeSymbols( bitStreamStatePtr, nDecodes, ( ( unsigned int * )decoded ) + ( i * ( nOutputs/CODECSPLIT ) ), codedLengths, decodeTable, datatype ) ;
				break ;
			default :
				break ;
		}
	}
	
	printf( "Data has been Huffman decoded.\n\n" ) ;
	
	free( decodeTable ) ;
	free( ( void * ) codedLengths ) ;
	DisposeBitStreamStatePtr( bitStreamStatePtr ) ;

	return decoded ;
}

/**** HuffmanEncode *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * Huffman encode the given data to a bit stream 
 * 
 * Inputs
 * ------
 *   inputs
 *   - an array of data to encode
 *     the data is unsigned char, unsigned short or unsigned int determined by datatype
 *   nInputs
 *   - the number of data items from the array to encode
 *   symbols
 *   - an array of symbols that occurred in the original data sorted into increasing order
 *     of frequency of occurrence
 *     the symbols should be unsigned char, unsigned short or unsigned int determined by datatype
 *   nSymbols
 *   - the number of symbols referenced by the array
 *   datatype
 *   - the type of the symbols and data to retrieve
 *     BYTEDATA		byte-size data
 *     HWORDDATA 	halfword-size data
 *     WORDDATA		word-size data
 *   freqCodeLen
 *   - an array of frequency of occurrence for each length of codeword
 *   maxcodewlen
 *   - the maximum length of codeword in the coded data
 *     (maxcodewlen+1) also defines the maximum index into the array freqCodeLen
 *   bitlength
 *   - a pointer to an unsigned int to hold the number of bits referenced by the bitstream returned
 * Outputs
 * -------
 *   bitlength
 *   - a pointer to the number of bits in the encoded stream returned
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     BitStreamStatePtr - a pointer to a bit stream state structure that references the encoded stream
 *     NULL              - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned structure
 * deallocate after use by DisposeBitStreamStatePtr
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static BitStreamStatePtr HuffmanEncode( void *inputs, unsigned int nInputs, void *symbols, unsigned int nSymbols, unsigned int datatype, unsigned int freqCodeLen[ ], unsigned int maxcwlen, unsigned int *bitlength )
{
	unsigned int		numberBytes ;
	BitStreamStatePtr	bitStreamStatePtr ;
	unsigned int		*encodeTable ;
	unsigned int		i ;
	int					cwlen ;
	unsigned int		nCodes ;
	
	if( ( inputs == NULL ) || ( nInputs == 0 ) || ( symbols == NULL ) || ( nSymbols == 0 ) || ( freqCodeLen == NULL ) || ( maxcwlen == 0 ) || ( maxcwlen > MAXCODEBITS ) || ( bitlength == NULL ) ) {
		fprintf( stderr, "[HuffmanEncode] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/* get maximum length of codeword in bits */
	numberBytes = 0 ;
	for( i = 1 ; i <= maxcwlen ; i += 1 ) {
		numberBytes = ( ( freqCodeLen[ i ] > 0 ) ? i : numberBytes ) ;
	}
	/* assume all codewords of max length, then require following number of bits */
	numberBytes *= nInputs ;
	/* get nearest whole number of bytes to hold maximum number of bits */
	numberBytes = ( ( numberBytes + 7 )/8 ) ;
	
	if( ( bitStreamStatePtr = InitBitStreamStateCoding( numberBytes ) ) == NULL ) {
		return NULL ;
	}
	
	printf( "Generating the Huffman encoding table...\n\n" ) ;
	
	switch( datatype ) {
		case BYTEDATA :
			encodeTable = MakeHuffCodeTable8( ( unsigned char * )symbols, nSymbols, freqCodeLen, maxcwlen ) ;
			break ;
		case HWORDDATA :
			encodeTable = MakeHuffCodeTable16( ( unsigned short * )symbols, nSymbols, freqCodeLen, maxcwlen ) ;
			break ;
		case WORDDATA :
			encodeTable = MakeHuffCodeTable32( ( unsigned int * )symbols, nSymbols, freqCodeLen, maxcwlen ) ;
			break ;
		default :
			fprintf( stderr, "[HuffmanEncode] Error in input arguments, aborting.\n\n" ) ;
			encodeTable = NULL ;
	}
	
	if( encodeTable == NULL ) {
		DisposeBitStreamStatePtr( bitStreamStatePtr ) ;
		return NULL ;
	}
	
	printf( "Huffman encoding table generated.\n\n" ) ;
	
	for( i = 0 ; i < nSymbols ; i += 1 ) {
		if( encodeTable[ i ] != 0 ) {
			printf( "symbol 0x" ) ;
			switch( datatype ) {
				case BYTEDATA :
					printf( "%.2x", i ) ;
					break ;
				case HWORDDATA :
					printf( "%.4x", i ) ;
					break ;
				case WORDDATA :
					printf( "%.8x", i ) ;
					break ;
				default :
					break ;
			}
			printf( " has codeword " ) ;
			cwlen = ( encodeTable[ i ] >> MAXCODEBITS ) - 1 ;
			while( cwlen >= 0 ) {
				printf( "%d", ( ( encodeTable[ i ] & ( 1 << cwlen ) ) >> cwlen ) ) ;
				cwlen -= 1 ;
			}
			printf( " (0x%.8x) of length %2d\n", encodeTable[ i ] & ( ( ( unsigned int )0xFFFFFFFF ) >> ( 32 - MAXCODEBITS ) ), encodeTable[ i ] >> MAXCODEBITS ) ;
		}
	}
	printf( "\n" ) ;

	printf( "Huffman encoding the data...\n\n" ) ;
	
	for( i = 0 ; i < CODECSPLIT ; i += 1 ) {
		if( i == CODECSPLIT - 1 ) {
			nCodes = nInputs - ( i * ( nInputs/CODECSPLIT ) ) ;
		}
		else {
			nCodes = nInputs/CODECSPLIT ;
		}
		switch( datatype ) {
			case BYTEDATA :
				bitStreamStatePtr = BitCodeSymbols( ( ( unsigned char * )inputs ) + ( i * ( nInputs/CODECSPLIT ) ), nCodes, bitStreamStatePtr, encodeTable, datatype ) ;
				break ;
			case HWORDDATA :
				bitStreamStatePtr = BitCodeSymbols( ( ( unsigned short * )inputs ) + ( i * ( nInputs/CODECSPLIT ) ), nCodes, bitStreamStatePtr, encodeTable, datatype ) ;
				break ;
			case WORDDATA :
				bitStreamStatePtr = BitCodeSymbols( ( ( unsigned int * )inputs ) + ( i * ( nInputs/CODECSPLIT ) ), nCodes, bitStreamStatePtr, encodeTable, datatype ) ;
				break ;
			default :
				break ;
		}
	}
	
	printf( "Data has been Huffman encoded.\n\n" ) ;
	
	free( ( void * ) encodeTable ) ;
	
	*bitlength = GetNumberBitsInStream( bitStreamStatePtr ) ;
	
	printf( "Coded data in bits = %d, original data in bits = %d, percentage reduction = %d%%\n\n", *bitlength, nInputs*datatype, ( ( nInputs*datatype - *bitlength )*100 )/( nInputs*datatype ) ) ;

	return bitStreamStatePtr ;
}

/**** InitSymbolCount ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * create an array of symbol count structures and initialise it with each symbol value and
 * zero count for symbols
 * 
 * Inputs
 * ------
 *   datatype
 *   - the type of the symbols in the data to be counted
 *     BYTEDATA		byte-size data
 *     HWORDDATA 	halfword-size data
 *     WORDDATA		word-size data
 *   maxSymbol
 *   - the maximum symbol value that occurs in the data + 1
 *     the value therefore defines the number of symbols in the data from 0 to maxSymbol
 * Return Values
 * ------ ------
 *     SymbolCountPtr - the created array of symbol count structures
 *     NULL   		  - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static SymbolCountPtr InitSymbolCount( unsigned int datatype, unsigned int maxSymbol )
{
	SymbolCountPtr	symbolcountptr ;
	unsigned int	i ;
	
	if( maxSymbol == 0 ) {
		fprintf( stderr, "[InitSymbolCount] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( symbolcountptr = ( SymbolCountPtr )calloc( maxSymbol, sizeof( SymbolCount ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	printf( "Initialising all possible symbols...\n\n" ) ;
	
	for( i = 0 ; i < maxSymbol ; i += 1 ) {
		symbolcountptr[ i ].count = 0 ;
		switch( datatype ) {
			case BYTEDATA :
				symbolcountptr[ i ].symbol.symboltype = BYTE ;
				symbolcountptr[ i ].symbol.symbol.byte = ( unsigned char )i ;
				break ;
			case HWORDDATA :
				symbolcountptr[ i ].symbol.symboltype = HWORD ;
				symbolcountptr[ i ].symbol.symbol.hword = ( unsigned short )i ;
				break ;
			case WORDDATA :
				symbolcountptr[ i ].symbol.symboltype = WORD ;
				symbolcountptr[ i ].symbol.symbol.word = i ;
				break ;
			default :
				fprintf( stderr, "[InitSymbolCount] Error in input arguments, aborting.\n\n" ) ;
				free( ( void * ) symbolcountptr ) ;
				return NULL ;
		}
	}
	
	printf( "Symbols initialised.\n\n" ) ;
	
	return symbolcountptr ;
}

/**** Menu **************************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the menu of options to the screen (defined in standard way for NextTask 
 * function and will be called by NextTask)
 *
 * Inputs
 * ------
 *   numberOptions
 *   - the number of menu options that should be printed
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static void Menu( unsigned int numberOptions )
{
	if( numberOptions == HUFFMAN_OPTIONS ) {
		printf( " 1. Huffman encode & decode data of type 'unsigned char'.\n" ) ;
		printf( " 2. Huffman encode & decode data of type 'unsigned short'.\n" ) ;
		printf( " 3. Huffman encode & decode data of type 'unsigned int'.\n" ) ;
	}
	else {
		fprintf( stderr, "[Menu] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
	}
}

/**** PrepareHuffman ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * count the frequency of occurrence of each symbol in the data to be encoded, create
 * an array of all possible symbols, sort this into increasing order of frequency of
 * occurrence and generate frequency of occurrence for each length of codeword 
 * 
 * Inputs
 * ------
 *   inputs
 *   - an array of data that will be encoded
 *     the data is unsigned char, unsigned short or unsigned int determined by datatype
 *   nInputs
 *   - the number of data items from the array to encode
 *   datatype
 *   - the type of the data to be encoded
 *     BYTEDATA		byte-size data
 *     HWORDDATA 	halfword-size data
 *     WORDDATA		word-size data
 *   maxSymbol
 *   - the maximum symbol value that occurs in the data + 1
 *     the value therefore defines the number of symbols in the data from 0 to maxSymbol
 *   maxcodewlen
 *   - the maximum length of codeword that can be created for encoding
 *   symbolsptr
 *   - a pointer to unallocated array to hold the sorted symbols
 * Outputs
 * -------
 *   symbolsptr
 *   - a pointer to an array of symbols sorted into increasing order of frequency of occurrence
 *     with maxSymbol entries
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     unsigned int * - a pointer to an array of frequency of occurrence for each length of codeword
 *                      the returned array has (maxcodewlen+1) entries, the first is always zero
 *     NULL           - some error occurred (memory problems?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned array of frequencies for codeword lengths and sorted symbol array
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static unsigned int *PrepareHuffman( void *inputs, unsigned int nInputs, unsigned int datatype, unsigned int maxSymbol, unsigned int maxcwlen, void **symbolsptr )
{
	SymbolCountPtr	symbolcountptr ;
	unsigned int	*frequency ;
	unsigned int	i ;
	unsigned int	*freqCodeLen ;
	
	if( ( inputs == NULL ) || ( nInputs == 0 ) || ( maxcwlen == 0 ) || ( maxcwlen > MAXCODEBITS ) || ( symbolsptr == NULL ) ) {
		fprintf( stderr, "[PrepareHuffman] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( symbolcountptr = InitSymbolCount( datatype, maxSymbol ) ) == NULL ) {
		return NULL ;
	}

	if( ( frequency = ( unsigned int * )calloc( maxSymbol, sizeof( unsigned int ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory to hold data, aborting.\n\n" ) ;
		free( ( void * ) symbolcountptr ) ;
		return NULL ;
	}
	
	printf( "Counting the frequency of occurrence for each symbol...\n\n" ) ;
	
	CountSymbols( inputs, nInputs, frequency, 1, datatype ) ;
	
	printf( "Frequency of occurrence for each symbol counted.\n\n" ) ;
	
	for( i = 0 ; i < maxSymbol ; i += 1 ) {
		if( frequency[ i ] != 0 ) {
			printf( "symbol 0x" ) ;
			switch( datatype ) {
				case BYTEDATA :
					printf( "%.2x", i ) ;
					break ;
				case HWORDDATA :
					printf( "%.4x", i ) ;
					break ;
				case WORDDATA :
					printf( "%.8x", i ) ;
					break ;
				default :
					break ;
			}
			printf( " has frequency 0x%.8x\n", frequency[ i ] ) ;
		}
	}
	printf( "\n" ) ;
	printf( "All other possible symbols do not occur and thus have zero frequency.\n\n" ) ;

	printf( "Sorting all possible symbols into ascending order of frequency of occurrence...\n\n" ) ;
	
	for( i = 0 ; i < maxSymbol ; i += 1 ) {
		symbolcountptr[ i ].count = frequency[ i ] ;
	}
	
	qsort( symbolcountptr, maxSymbol, sizeof( SymbolCount ), &SymbolCountSort ) ;
	
	for( i = 0 ; i < maxSymbol ; i += 1 ) {
		frequency[ i ] = symbolcountptr[ i ].count ;
	}
	
	printf( "Symbols have been sorted.\n\n" ) ;
	
	*symbolsptr = GetSymbolsFromSymbolCount( symbolcountptr, maxSymbol ) ;
	free( ( void * ) symbolcountptr ) ;
	if( *symbolsptr == NULL ) {
		free( ( void * ) frequency ) ;
		return NULL ;
	}

	printf( "Generating the frequency for each length of codeword...\n\n" ) ;

	freqCodeLen = Huffman( frequency, maxSymbol, maxcwlen ) ;
	free( ( void * ) frequency ) ;
	if( freqCodeLen == NULL ) {
		return NULL ;
	}
	
	printf( "Frequency of codeword length generated.\n\n" ) ;
	
	for( i = 1 ; i <= maxcwlen ; i += 1 ) { /* can't have codeword of length 0! */
		printf( "number of codewords of length %2d is %d\n", i, freqCodeLen[ i ] ) ;
	}
	printf( "\n" ) ;

	return freqCodeLen ;
}

/**** SymbolCountSort ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * sort the current two symbol count structures by increasing count value then for equal
 * count by increasing symbol value
 *
 * define in standard way for C qsort routine
 * 
 * Inputs
 * ------
 *   symbolcount1
 *   - the first symbol count structure (needs casting)
 *   symbolcount2
 *   - the second symbol count structure (needs casting)
 * Return Values
 * ------ ------
 *     1	the first structure is greater than the second
 *     0	the two structures are equal (should never occur since symbols are unique)
 *     -1	the second structure is greater than the first
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static int SymbolCountSort( const void *symbolcount1, const void *symbolcount2 )
{
	if( ( *( SymbolCount * )symbolcount1 ).count == ( *( SymbolCount * )symbolcount2 ).count ) {
		switch( ( *( SymbolCount * )symbolcount1 ).symbol.symboltype ) {
			case BYTE :
				if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.byte == ( *( SymbolCount * )symbolcount2 ).symbol.symbol.byte ) {
					return 0 ;
				}
				else if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.byte > ( *( SymbolCount * )symbolcount2 ).symbol.symbol.byte ) {
					return 1 ;
				}
				else {
					return -1 ;
				}
			case HWORD :
				if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.hword == ( *( SymbolCount * )symbolcount2 ).symbol.symbol.hword ) {
					return 0 ;
				}
				else if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.hword > ( *( SymbolCount * )symbolcount2 ).symbol.symbol.hword ) {
					return 1 ;
				}
				else {
					return -1 ;
				}
			case WORD :
				if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.word == ( *( SymbolCount * )symbolcount2 ).symbol.symbol.word ) {
					return 0 ;
				}
				else if( ( *( SymbolCount * )symbolcount1 ).symbol.symbol.word > ( *( SymbolCount * )symbolcount2 ).symbol.symbol.word ) {
					return 1 ;
				}
				else {
					return -1 ;
				}
			default :
				return 0 ;
		}
	}
	else if( ( *( SymbolCount * )symbolcount1 ).count > ( *( SymbolCount * )symbolcount2 ).count ) {
		return 1 ;
	}
	else {
		return -1 ;
	}
}

