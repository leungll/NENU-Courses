/*
 * Utility Library: Options prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _OPTIONS_C_
#define _OPTIONS_C_

unsigned int NextTask( unsigned int numberOptions, void ( *Menu )( unsigned int numberOptions ) ) ;
int SetStatus( char wordString[ ], char *statusString, unsigned int limit ) ;
unsigned int YesNo( char *question, char *yes, char *no ) ;

#endif	/* _OPTIONS_C_ */