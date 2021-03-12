/*
 * G.711 assembler prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _G711_S_
#define	_G711_S_

int G711_linear2alaw( int pcmSample ) ;
int G711_alaw2linear( int aLawSample );

int G711_linear2ulaw( int pcmSample ) ;
int G711_ulaw2linear( int uLawSample ) ;

int G711_alaw2ulaw( int aLawSample ) ;
int G711_ulaw2alaw( int uLawSample ) ;
 
int G711_linear2linear( int pcmSample ) ;

#endif	 /* _G711_S_ */
