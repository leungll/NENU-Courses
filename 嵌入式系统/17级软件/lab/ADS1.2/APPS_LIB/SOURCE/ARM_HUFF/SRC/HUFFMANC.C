/*
 * Huffman
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "huffmanc.h"

/*
define the structure used for each node in the tree

the tree is an internal construction and is not required by any other functions hence
the structure declaration can also be hidden
*/
typedef struct	TreeNode	TreeNode ;
typedef			TreeNode	*TreePtr ;

struct TreeNode {
	unsigned int	freq ;
	unsigned int	nextnode ;
} ;

static TreePtr MakeHuffmanTree( unsigned int freq[ ], unsigned int nfreqs, unsigned int *treesize ) ;

/**** GetFreqCodeLen ****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate an array of frequency of occurrence for each length of codeword in the given
 * tree
 *
 * Inputs
 * ------
 *   tree
 *   - a binary Huffman tree
 *   treesize
 *   - the number of nodes in the tree including leaves
 *   maxcodewlen
 *   - the maximum length of codeword that can be created
 * Return Values
 * ------ ------
 *     unsigned int * - the created array of frequency of occurrence for each length of codeword
 *						with (maxcodewlen + 1) entries, the first, however, is always zero
 *     NULL			  - some error occurred (memory failed?)
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
static unsigned int *GetFreqCodeLen( TreePtr tree, unsigned int treesize, unsigned int maxcodewlen )
{
	/*
	create a stack where each addition will include a node to return to and the current length of
	tree traversed to reach that node where the maximum possible length is MAXPUREHCODEBITS thus
	the stack requires MAXPUREHCODEBITS + 1 entry for length + same again for node
	*/
	unsigned int	s[ 2*( MAXPUREHCODEBITS + 1 ) ] ;
	unsigned int	*stack = s ;
	/*
	create a fixed array of frequency of occurrence for each length of codeword that allows the maximum
	possible codeword length to be created that is possible by pure Huffman
	*/
	unsigned int	maxfreqcodelen[ MAXPUREHCODEBITS + 1 ] ;
	unsigned int	*bitfreq ;
	unsigned int 	length ;
	unsigned int	node, nextnode ;
	unsigned int	i, j ;
	
	if( ( tree == NULL ) || ( treesize < 1 ) || ( maxcodewlen < 1 ) || ( maxcodewlen > MAXPUREHCODEBITS ) ) {
		fprintf( stderr, "[GetFreqCodeLen] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/*
	initialise the memory required for the final array of occurrences for each codeword length 
	*/
	if( ( bitfreq = ( unsigned int * )calloc( maxcodewlen + 1, sizeof( unsigned int ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	/*
	initialise array with zeros so that number of occurrences for each length of codeword
	is by default 0 i.e. no codeword of a given length exists
	*/
	for( i = 0 ; i <= MAXPUREHCODEBITS ; i += 1 ) {
		maxfreqcodelen[ i ] = 0 ;
	}

	/*
	initialise the first stacked node and length to (treesize - 2) and 0 respectively
	
 	the last element of the tree, (treesize - 1) should be have node = -1 since tree contains (2*number of frequencies - 1)
 	entries thus last valid node, the actual root node, is (treesize - 2)

	(treesize - 2) then gives the last node read from the stack as the root node which is the tree-traversal 
	termination node with zero codeword length (which could also be used to determine the cessation of tree traversal)
	*/
	*stack ++ = treesize - 2 ;
	*stack ++ = 0 ;
 
 	/*
 	starting at the left child of the root node (treesize - 4), traverse the tree taking the right children at each
 	stage if not leaf nodes, stacking the left children to return to when right children exhausted
 	
 	continue until the traversal unwinds back to the root node
 	*/
	for( node = treesize - 4, length = 1 ; node != treesize - 2 ; /* no default increment */ ) {
		nextnode = tree[ node ].nextnode ;	/* get the next node to branch to from given left node in the tree */
		if( nextnode != 0 ) {				/* if non-zero, node is an internal node (not a leaf node) */
			*stack ++ = nextnode ;			/* stack the node to enable returning to it for branching */
			*stack ++ = length + 1 ; 		/* stack the length of the codeword reached, adding 1 for current internal node */
		}
		else { 								/* node reached is a leaf node so codeword length reached for frequency */
			maxfreqcodelen[ length ] += 1 ; /* increment the number of codewords of the given length */
		}
		
		nextnode = tree[ node + 1 ].nextnode ;	/* get the next node to branch to from given right node in the tree */
		if( nextnode != 0 ) {				/* if non-zero, node is an internal node (not a leaf node) */
			node = nextnode ;				/* set branch to this node with next iteration to continue tree traversal */
			length += 1 ;					/* increment the length of the codewords down to this node */
		}
		else { 								/* node reached is a leaf node so codeword length reached for frequency */
			maxfreqcodelen[ length ] += 1 ; /* increment the number of codewords of the given length */
			length = *--stack ; 			/* reached leaf, decrement stack and restore length for node returning to */
			node = *--stack ; 				/* reached a leaf so decrement stack pointer and set node to branch to */
		}
	}
	
	/*
	require codewords of maximum length maxcodewlen, but tree did not know this when constructed thus codewords
	can be any length and if pure Huffman procedure above assigned any codewords too long, the
	coding must be adjusted
	
	for the longest Huffman code, symbols are paired and thus are removed from this length two at a time with the
	prefix for the pair (which is one bit shorter) allocated to one of the pair then, skipping the codeword length
	entry for the prefix length, a code word from the next shortest non-zero entry is converted into a
	prefix for two code words one bit longer
	*/
	for( i = MAXPUREHCODEBITS ; i > maxcodewlen ; i -= 1 ) {
		while( maxfreqcodelen[ i ] > 0 ) {	/* whilst there exist codewords above maximum length allowed */
			j = i - 2 ;						/* find prefix from next shortest non-zero entry */
			while( maxfreqcodelen[ j ] == 0 ) {
				j -= 1 ;
			}
			maxfreqcodelen[ i ] -= 2 ;		/* remove the pair of codewords */
			maxfreqcodelen[ i - 1 ] += 1 ;	/* add prefix to this length */
			maxfreqcodelen[ j + 1 ] += 2 ;	/* add two new codewords to this length... */
			maxfreqcodelen[ j ] -= 1 ;		/* ...generated with prefix from this length */
		}
	}

	/* initialise the returned array with the frequency of occurrence for each length of codewords upto the maximum */
	for( i = 0 ; i <= maxcodewlen ; i += 1 ) {
		bitfreq[ i ] = maxfreqcodelen[ i ] ;
	}
	
	return bitfreq ;
}

/**** Huffman ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate an array of frequency of occurrence for each length of codeword that will
 * exist in the codewords for the given data
 *
 * Inputs
 * ------
 *   freq
 *   - an array of frequency of occurrence for each symbol in the data to be coded
 *     sorted into increasing order of frequency
 *   nfreqs
 *   - the number of frequencies referenced by the array
 *   maxcodewlen
 *   - the maximum length of codeword that can be created
 * Return Values
 * ------ ------
 *     unsigned int * - the created array of frequency of occurrence for each length of codeword
 *						with (maxcodewlen + 1) entries, the first, however, is always zero
 *     NULL			  - some error occurred (memory failed?)
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
unsigned int *Huffman( unsigned int freq[ ], unsigned int nfreqs, unsigned int maxcodewlen )
{
	unsigned int	i ;
	TreePtr			tree ;
	unsigned int	treesize ;
	unsigned int	*freqcodelen ;
		
	if( ( freq == NULL ) || ( nfreqs == 0 ) || ( maxcodewlen > MAXCODEBITS ) ) {
		fprintf( stderr, "[Huffman] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/*
	find the first non-zero frequency in the array "freq" with data ordered with increasing frequency
	*/
	i = 0 ;
	while( ( freq[ i ] == 0 ) && ( i < nfreqs ) ) {
		i += 1 ;
	}

	/*
	( ( 1 << maxcodewlen ) -1 ) gives the total number of codewords possible which should be at least
	as large as the number of non-zero frequencies that need codewords
	
	this test need not always be true for the coding to still be accomplished but if the test is true
	coding will always be possible, if it fails it may not thus testing ensures that coding will succeed
	*/
	if( ( ( 1 << maxcodewlen ) - 1 ) < ( nfreqs - i ) ) {
		fprintf( stderr, "[Huffman] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( tree = MakeHuffmanTree( freq, nfreqs, &treesize ) ) == NULL ) {
		return NULL ;
	}
	
	/* get the frequency of occurrence for each length of codeword */
	if( ( freqcodelen = GetFreqCodeLen( tree, treesize, maxcodewlen ) ) == NULL ) {
		;
	}
	
	free( ( void * ) tree ) ;
	
	return freqcodelen ;
}

/**** MakeHuffmanTree ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * generate a binary Huffman tree to create codewords from
 *
 * Inputs
 * ------
 *   freq
 *   - an array of frequency of occurrence for each symbol in the data to be coded
 *     sorted into increasing order of frequency
 *   nfreqs
 *   - the number of frequencies referenced by the array
 *   treesize
 *   - a pointer to an unsigned int to hold the number of entries referenced by the tree
 * Outputs
 * -------
 *   treesize
 *   - the number of nodes referenced by the tree returned
 *     undefined if NULL returned for the tree
 * Return Values
 * ------ ------
 *     TreePtr - the created Huffman tree with *treesize nodes
 *     NULL	   - some error occurred (memory failed?)
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----------
 * the returned tree
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static TreePtr MakeHuffmanTree( unsigned int freq[ ], unsigned int nfreqs, unsigned int *treesize )
{
	TreePtr			treeptr ;
	TreePtr			tree ;
	unsigned int	*freqend ;
	TreeNode		node, child ;
	TreePtr			p, parent ;
	unsigned int	i ;
	
	if( ( treesize == NULL ) || ( freq == NULL ) || ( nfreqs == 0 ) ) {
		fprintf( stderr, "[MakeHuffmanTree] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	/*
	initialise enough space to hold the tree
	
	the tree will have (2*nfreqs - 1) nodes which contain actual tree data, however an extra node is
	used during the tree creation to determine the current final element in the tree
	*/
	if( ( treeptr = ( TreePtr )calloc( nfreqs*2, sizeof( TreeNode ) ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
		*treesize = -1 ;
		return NULL ;
	}
	*treesize = nfreqs * 2 ;
	
	tree = treeptr ;					/* tree will be incremented whilst creating the tree but need pointer to start */
	
	/*
	find the first non-zero frequency in the array "freq" with data ordered with increasing frequency
	*/
	i = 0 ;
	while( ( freq[ i ] == 0 ) && ( i < nfreqs ) ) {
		i += 1 ;
	}
	
	if( i == nfreqs ) {					/* ensure frequency array contains non-zero frequencies */
		fprintf( stderr, "[MakeHuffmanTree] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		free( ( void * ) treeptr ) ;
		*treesize = -1 ;
		return NULL ;
	}
	
	freqend = freq + nfreqs ;			/* save the end location for the frequency array for termination use */
	
	freq += i ;							/* shift starting address of freq to first non-zero frequency entry */
	
	/*
	shift starting address of tree pointer so that last 2*i entries of array will contain the tree
	with all the entries before this point being zero
	
	the tree will consist of all data with non-zero frequency counts as leaves and for each pair of
	nodes a parent node will be created and thus the tree requires 2*i - 1 nodes where i is the
	number of non-zero frequency count nodes
	*/
	tree += ( i << 1 ) ;		
	
	/*
	initialise parent and p to point to first entry in tree that will contain the first internal node of the
	tree, those entries prior to this point contain the non-zero frequencies as leaves
	*/
	parent = tree + ( nfreqs - i ) ;	/* allow space for non-zero frequencies as first tree elements */
	p = parent ;						/* likewise */

	( *p ).freq = ( unsigned int )-1 ;	/* initialise the last tree entry with default termination values */
	( *p ).nextnode = ( unsigned int )-1 ;
	
	/*
	beginning with first non-zero frequency, terminating when all non-zero frequency elements have been used
	(next element past that referenced by i is read, hence i stops at nfreqs -1), construct the tree
	*/
	for( ; i < nfreqs - 1 ; i += 1 ) {
		/*
		frequencies are ordered so the following test is true if both freq[ 0 ] and freq[ 1 ] are less than parent[ 0 ] thus 
		these two frequencies are the two smallest frequency counts in the tree and should be added to create
		the next parent node
		*/
		if( ( ( freqend - freq ) > 1 ) && ( freq[ 1 ] < parent[ 0 ].freq ) ) {	/* ensure not past end of frequency array */
			node.nextnode = 0 ;
			node.freq = *freq ++ ;
			
			child.nextnode = 0 ;
			child.freq = *freq ++ ;
		}
		/*
		frequencies are ordered so the following test is true if both freq[ 0 ] and freq[ 1 ] are greater than parent[ 0 ] thus
		the two parent nodes (constructed from other frequencies being added) are the two smallest frequency
		counts in the tree and should be added to create the next parent node
		*/
		else if( ( ( freqend - freq ) == 0 ) || ( freq[ 0 ] > parent[ 1 ].freq ) ) {	/* check if last frequency, then always true */
			node = *parent ++ ;
			
			child = *parent ++ ;
		}
		/*
		otherwise it is always true that freq[ 0 ] and parent[ 0 ] are the two smallest frequency counts in the tree
		(although not necessarily uniquely the smallest) and thus these should be added to create the next node
		*/
		else {	/* true for case freqend - freq == 1 as well and the last frequency is not greater than last two parents */
			node.nextnode = 0 ;
			node.freq = *freq ++ ;
			
			child = *parent ++ ;
		}

		*tree ++ = node ;					/* set next two tree node values */
		*tree ++ = child ;
		
		/*
		node now becomes the parent node data 
		*/
		node.freq += child.freq ;			/* set parent nodes frequency as sum of childrens */
		node.nextnode = i << 1 ;			/* set next node entry as accessor to left child belonging to parent */
		*p ++ = node ;						/* set newest internal node for the tree and increment to next tree element */
		if( p - treeptr < *treesize ) {		/* if the tree is incomplete re-initialise the last node reference */
			( *p ).freq = ( unsigned int )-1 ;
			( *p ).nextnode = ( unsigned int )-1 ;
		}
		else {								/* else, tree complete, cease tree construction */
			break ;
		}
	}
	
	return treeptr ;						/* return the constructed tree */
}

