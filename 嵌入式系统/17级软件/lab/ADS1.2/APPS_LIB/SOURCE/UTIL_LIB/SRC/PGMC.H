/*
 * Utility Library: PGM prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _PGM_C_
#define _PGM_C_

#include "definesc.h"

/* readpgm.c */
UCArray ReadPGM( char *functionType, unsigned int *width, unsigned int *height ) ;

/* writepgm.c */
unsigned int WritePGM( UCArray uCArray, unsigned int width, unsigned int height, char *imageType ) ;

#endif	/* _PGM_C_ */
