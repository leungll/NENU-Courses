/*
 * Bit Manipulation assembler test harness prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _BIT_MANIPULATION_TEST_S_
#define _BIT_MANIPULATION_TEST_S_

int init_BCDADD( int a, int b ) ;

int init_BITREV( int word ) ;
int init_BITREVC( int word ) ;

int init_BYTEREV( int word ) ;
int init_BYTEREVC( int word ) ;

int init_BYTEWISEMAX( int a, int b ) ;

int init_LSBSET( int word ) ;
int init_MSBSET( int word ) ;

int init_POPCOUNT( int word ) ;
int init_POPCOUNT7( int word, int word2, int word3, int word4, int word5, int word6, int word7 ) ;

#endif	/* _BIT_MANIPULATION_TEST_S_ */