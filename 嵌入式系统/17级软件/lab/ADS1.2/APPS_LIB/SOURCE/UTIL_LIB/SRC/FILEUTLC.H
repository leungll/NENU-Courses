/*
 * Utility Library: File Utility prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FILEUTIL_C_
#define _FILEUTIL_C_

#include <stdio.h>

/*
define the type CustomFOpenFn as
	pointer to function (of two const char * arguments) returning FILE *
*/
//typedef FILE * ( *CustomFOpenFn )( const char *filename, const char *mode ) ;

/*
define the type CustomFreOpenFn as
	pointer to function (of two const char * arguments, one FILE * argument) returning FILE *
*/
//typedef FILE * ( *CustomFreOpenFn )( const char *filename, const char *mode, FILE *stream ) ;

#define	STDIN	"stdin"
#define	STDOUT	"stdout"
#define STDERR	"stderr"
#define STDOE	"stdoe"

#define STDINID		0
#define STDOUTID	1
#define STDERRID	2

int ChangeStdIO( int *argc, char ***argv, char *newStdIO, FILE *oldStdIO ) ;
int ResetStdIO( FILE *stdIO ) ;

void *GetData( unsigned int bytes, char *dataType, unsigned int *n ) ;
void SaveData( void *data, unsigned int n, unsigned int bytes, unsigned int isUnsigned, char *dataType ) ;

FILE *FreOpenFileRead( char *fileMode, char iFName[ ], FILE *stream ) ;
FILE *OpenFileRead( char *fileMode, char iFName[ ] ) ;
FILE *OpenFileWrite( char *fileMode, char oFName[ ] ) ;

void *ReadBinaryFromFile( FILE *fp, char *fileName, unsigned int bytes, unsigned int bigendian, unsigned int *n ) ;
void WriteBinaryToFile( FILE *fp, char *fileName, void *data, unsigned int n, unsigned int bytes, unsigned int bigendian ) ;

void *ReadTextFromFile( FILE *fp, char *fileName, unsigned int bytes, unsigned int bigendian, unsigned int *n ) ;
void WriteTextToFile( FILE *fp, char *fileName, void *data, unsigned int n, unsigned int bytes, unsigned int isUnsigned, unsigned int bigendian ) ;

char *GetFileName( char iFName[ ], unsigned int limit, char *readwrite ) ;
char *GetPathNameForFile( char fName[ ], char path[ ], unsigned int limit, char *readwrite ) ;

unsigned int GetLineFromFile( FILE *fp, void *line, unsigned int isUnsigned, unsigned int limit, void *skipThis, unsigned int skipLength ) ;

FILE *TestFileForOverwrite( char *fileMode, char oFName[ ], unsigned int *fileStatus ) ;

#endif	/* _FILEUTIL_C_ */