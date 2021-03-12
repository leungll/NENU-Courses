/*
 * Utility Library: Custom Read prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _CUSTREAD_C_
#define _CUSTREAD_C_

#include <stdio.h>

int GetIntFromString( char *string, int *number ) ;
unsigned int ReadInString( FILE *stream, char *string, unsigned int limit ) ; 
double ReadDouble( void ) ;

#endif	/* _CUSTREAD_C_ */