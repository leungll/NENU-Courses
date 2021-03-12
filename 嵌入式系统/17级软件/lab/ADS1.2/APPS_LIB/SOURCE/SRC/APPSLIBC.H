/*
 * Applications Library prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ARM_APPLICATIONS_LIBRARY_
#define _ARM_APPLICATIONS_LIBRARY_

#include <stdio.h>

FILE *CustomFOpen( const char *filename, const char *filemode ) ;
FILE *CustomFreOpen( const char *filename, const char *filemode, FILE *stream ) ;

#endif	/* _ARM_APPLICATIONS_LIBRARY_ */
