/*
 * Utility Library: Array prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ARRAY_C_
#define _ARRAY_C_

#include "definesc.h"

/* intarray.c */
IArray MakeIArray( unsigned int width, unsigned int height ) ;
void FreeIArray( IArray iArray, unsigned int height ) ;

/* ucharray.c */
UCArray	MakeUCArray( unsigned int width, unsigned int height );
void FreeUCArray( UCArray uCArray, unsigned int height ) ;

#endif	/* _ARRAY_C_ */
