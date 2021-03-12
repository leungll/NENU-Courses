/*
 * Utility Library: File Utility
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "fileutlc.h"

#include "bitutilc.h"
#include "custredc.h"
#include "definesc.h"
#include "optionsc.h"

/*
define weak function prototypes

if a CustomFOpen function does not exist, &CustomFOpen, is NULL
else if a CustomFOpen function exists the pointer points to it

likewise for CustomFreOpen
*/
#if	__ARMCC_VERSION >= 5.00
#define	___weak	__weak
#endif	/* __ARMCC_VERSION >= 5.00 */
extern ___weak FILE *CustomFOpen( const char *filename, const char *filemode ) ;
extern ___weak FILE *CustomFreOpen( const char *filename, const char *filemode, FILE *stream ) ;

static FILE *FreOpenFile( const char *filename, const char *filemode, FILE *stream ) ;

/**** ChangeStdIO *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * procedure to redirect stdin, stdout or stderr to files from command line arguments
 * at run time
 *
 * Inputs
 * ------
 *   argc
 *	 - pointer to number of command line arguments
 *	 argv
 *   - pointer to the command line arguments
 *     next argument after first argument referenced must be redirect option if given
 *	 newStdIO
 *   - new file name to open for redirection
 *   oldStdIO
 *	 - pointer to FILE descriptor
 *     stdin, stdout or stderr only
 * Outputs
 * -------
 *   argc
 *   - the number of arguments remaining after argument for redirection is removed
 *   argv
 *   - the input arguments referecing the last argument read
 * Return Values
 * ------ ------
 *     0     : stdin has been redirected
 *     1     : stdout has been redirected
 *     2     : stderr has been redirected
 *     -1    : stdio was not redirected which may or may not be an error
 *     other : stdio redirection was not required
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int ChangeStdIO( int *argc, char ***argv, char *newStdIO, FILE *oldStdIO )
{
	unsigned int	change = 0 ;
	char			fileMode[ 3 ] = "a+" ;
	int				stdio = 666 ;
	
	if( ( !argc ) || ( !argv ) || ( !( *argv ) ) || ( !newStdIO ) ||
		( !oldStdIO ) || ( ( oldStdIO != stdin ) && ( oldStdIO != stdout ) && ( oldStdIO != stderr ) )
		) {
		fprintf( stderr, "[ChangeStdIO] Error in input arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return -1 ;
	}
	
	/* first argument is the binary and location being run */
	if( --( *argc ) > 0 ) {
		if( sscanf( *( ++( *argv ) ), "%d", &change ) == EOF ) {
			( *argc )++ ;
			( *argv )++ ;
			return -1 ;
		}
	}
	else {
		( *argc )++ ;
		return stdio ;
	}
	
	if( change == 666 ) {
		if( oldStdIO == stdin ) {
			stdio = STDINID ;
			strcpy( fileMode, "r" ) ;
		}
		if( ( FreOpenFile( newStdIO, fileMode, oldStdIO ) ) == NULL ) {
			fprintf( stderr, "Could not open '%s', aborting.\n\n", newStdIO ) ;
			exit( 1 ) ;	/* quitting because nasty failure */
		}
		if( ( oldStdIO == stdout ) || ( oldStdIO == stderr ) ) {
			if( oldStdIO == stdout ) {
				stdio = STDOUTID ;
			}
			else {
				stdio = STDERRID ;
			}
			setbuf( oldStdIO, NULL ) ;
		}
	}
	else {
		( *argc ) += 1 ;
		( *argv ) += 1 ;
	}
	
	return stdio ;
}

/**** FreOpenFile *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * freopen's the file in the given mode using the custom freopen function if defined
 *
 * Inputs
 * ------
 *   filename
 *   - an array of characters that is the file name of the file to open
 *   filemode
 *   - file mode as necessary for freopen
 *   stream
 *   - the stream to associate with the file
 * Return Values
 * ------ ------
 *     FILE * - the stream associated with the opened file
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the stream is non-NULL, the stream should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static FILE *FreOpenFile( const char *filename, const char *filemode, FILE *stream )
{
	if( &CustomFreOpen == NULL ) {
		return freopen( filename, filemode, stream ) ;
	}
	else {
		return CustomFreOpen( filename, filemode, stream ) ;
	}
}

/**** FreOpenFileRead ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * freopen's the file for reading in the given mode
 *
 * Inputs
 * ------
 *   fileMode
 *   - "r" or "rb" as defined for reading by freopen
 *   iFName
 *   - an array of characters that is the file name of the file to open
 *   stream
 *   - the stream to associate with the open file
 * Return Values
 * ------ ------
 *     FILE * - the stream associated with the opened file with file name iFName
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the stream is non-NULL, the file stream be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *FreOpenFileRead( char *fileMode, char iFName[ ], FILE *stream )
{
	FILE	*openstream ;

	if( ( !fileMode ) || ( !iFName ) || ( !stream ) ) {
		fprintf( stderr, "[FreOpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( strncmp( fileMode, "r", 1 ) != 0 ) {	/* must begin "r..." if reading */
		fprintf( stderr, "[FreOpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( strncmp( fileMode, "r+", 2 ) == 0 ) {	/* writing mode, not reading */
		fprintf( stderr, "[FreOpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}

    printf( "Trying to open file '%s' to associate with stream...\n\n", iFName ) ;
    
    if( ( openstream = FreOpenFile( iFName, fileMode, stream ) ) == NULL ) {
		fprintf( stderr, "Error opening file '%s', aborting\n\n", iFName ) ;
		/* ifp = NULL, so just return this */
    }
    else {
		printf( "File '%s' opened and associated with stream.\n\n", iFName ) ;
	}
    
    return openstream ;
}

/**** GetData ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the file name from the user and open the file for reading in either binary or
 * text mode by user choice, read in the data of the required type, close the file 
 * and return the data read in
 *
 * Inputs
 * ------
 *   bytes
 *   - the number of bytes in the data that is to be read
 *     BYTEBYTES = char data
 *     HWORDBYTES = short data
 *     WORDBYTES = int data
 *     anything else is undefined and returns NULL
 *   isUnsigned
 *   - 1 (true) the data to be read is unsigned and returned unsigned
 *     0 (false) the data to be read is signed and returned signed
 *   dataType
 *   - an optional string that defines the data that is to read in
 *     displayed to the user during file selection time
 *     pass NULL if non-specific data is to be read
 *	 n
 *   - a pointer to an integer location to store the number of data points read
 * Outputs
 * -------
 *   n
 *   - the number of data points in the returned array
 *     undefined if NULL returned
 * Return Values
 * ------ ------
 *     (unsigned) char *  - an array of character data read from the file
 *     (unsigned) short * - an array of short data read from the file
 *     (unsigned) int *   - an array of integer data read from the file
 *     NULL    			  - some error occurred, size is not valid
 *
 * Notes
 * -----
 * the array returned is returned as void * and will need casting to appropriate type
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the array returned
 * deallocate after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define	ASKONLYONCEFORFILENAME		1

void *GetData( unsigned int bytes, char *dataType, unsigned int *n )
{
	char			fileMode[ 3 ] = "r" ;
	FILE			*fp ;
	char			fileName[ LIMIT ] ;
	void			*data = NULL ;
	unsigned int	binary ;
	unsigned int	bigendian ;
	
#if	!ASKONLYONCEFORFILENAME
	binary = 0 ;
	
	do {

	if( binary ) {
		fileMode[ 1 ] = '\0' ;					/* remove any previous binary addition */
	}
#endif
	
	printf( "Please give the name of the file to read " ) ;
	if( dataType != NULL ) {
		printf( "%s ", dataType ) ;
	}
	printf( "data from.\n\n" ) ;
	
	GetFileName( fileName, LIMIT, "reading" ) ;
	
	binary = YesNo( "Data in Binary mode", "binary", "hexadecimal text" ) ;
	if( binary ) {
		strcat( fileMode, "b" ) ;
	}
			
#if	!ASKONLYONCEFORFILENAME
	/* loop until valid file name given or... */
	} while( ( fp = OpenFileRead( fileMode, fileName ) ) == NULL ) ;
#else
	/* ...bail if if no file opened */
	if( ( fp = OpenFileRead( fileMode, fileName ) ) == NULL ) {
		return NULL ;
	}
#endif
	
	if( BIGENDIAN && binary ) {
		bigendian = !YesNo( "Data will be read in Big-Endian mode.  Convert to Little-Endian", "little-endian", "big-endian" ) ;
	}
	else {
		bigendian = YesNo( "Data will be read in Little-Endian mode.  Convert to Big-Endian", "big-endian", "little-endian" ) ;
	}
	
	if( binary ) {
		data = ReadBinaryFromFile( fp, fileName, bytes, bigendian, n ) ;
	}
	else {
		data = ReadTextFromFile( fp, fileName, bytes, bigendian, n ) ;
	}
	
	fclose( fp ) ;
	
	return data ;
}

/**** GetFileName *******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get a file name from the user
 *
 * Inputs
 * ------
 *   fName
 *   - an array of characters to hold the file name given by the user
 *   limit
 *   - the maximum number of characters that can be read into the filename which includes
 *     the string termination
 * Outputs
 * -------
 *   iFName
 *   - the file name given by the user
 *     undefined if some error occurrs (NULL returned)
 * Return Values
 * ------ ------
 *     char * - a pointer to the character array for the file name (pointer to fName)
 *     NULL   - some error occurred, fName is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
char *GetFileName( char fName[ ], unsigned int limit, char *readwrite )
{
	if( ( !fName ) || ( limit == 0 ) ) {
		fprintf( stderr, "[GetFileName] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
		
	printf( "Name of the file to open " ) ;
	if( readwrite != NULL ) {
		printf( "for %s ", readwrite ) ;
	}
	printf( ": " ) ;
	ReadInString( stdin, fName, limit ) ;
	/* ignore size of file name returned */
	printf( "\n" ) ;
	
	return fName ;
}

/**** GetLineFromFile ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the next line from the given file, upto the the maximum number of given characters
 * and skip any blank lines or any special lines that begin with sequence given
 *
 * Inputs
 * ------
 *   fp
 *   - pointer to the file to read the line from
 *     stdin = keyboard
 *   line
 *   - an array of characters to hold the line from the file
 *	 isUnsigned
 *   - 0 : the data should be read in signed
 *     1 : the data should be read in unsigned
 *   limit
 *   - the maximum number of characters that can be read into line which includes
 *     the string termination
 *   skipThis
 *   - a string for testing that if appears at the beginning of a line, the line is
 *     skipped over
 *     pass NULL if all lines of the file should be retrieved
 *   skipLength
 *   - the length of skipThis to compare with the retrieved line [not necessarily 
 *     strlen( skipThis )] or 0 if not lines to skip
 * Outputs
 * -------
 *   line
 *   - the line read from the given file
 *     undefined if some error occurrs (negative value returned)
 * Return Values
 * ------ ------
 *     unsigned int - the length of the line retrieved
 *     0  			- some error occurred, line may not be valid
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
unsigned int GetLineFromFile( FILE *fp, void *line, unsigned int isUnsigned, unsigned int limit, void *skipThis, unsigned int skipLength )
{
	unsigned int	counter ;
	int				cha ;
	unsigned int	ucha ;
	
	if( ( !fp ) || ( !line ) ) {
		fprintf( stderr, "[GetLineFromFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return 0 ;
	}
	
	counter = 0 ;
	if( isUnsigned ) {
		while(     ( --limit > 0 ) 
				&& ( ( ucha = fgetc( fp ) ) != EOF ) 
				&&   ( ucha != '\n' ) ) {
			( ( unsigned char * )line )[ counter++ ] = ( unsigned char )ucha ;
		}
		( ( unsigned char * )line )[ counter ] = '\0' ;

		if( ( ( unsigned char * )skipThis ) != NULL ) {
			if( strncmp( ( ( char * )skipThis ), ( ( char * )line ), skipLength ) == 0 ) {
				return GetLineFromFile( fp, line, isUnsigned, limit, skipThis, skipLength ) ;
			}
		}
	}
	else {
		while(     ( --limit > 0 ) 
				&& ( ( cha = fgetc( fp ) ) != EOF ) 
				&&   ( cha != '\n' ) ) {
			( ( char * )line )[ counter++ ] = ( char )cha ;
		}
		( ( char * )line )[ counter ] = '\0' ;

		if( ( ( char * )skipThis ) != NULL ) {
			if( strncmp( ( ( char * )skipThis ), ( ( char * )line ), skipLength ) == 0 ) {
				return GetLineFromFile( fp, line, isUnsigned, limit, skipThis, skipLength ) ;
			}
		}
	}
		
	return counter ;
}

/**** GetPathNameForFile ************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get a directory location for the given file
 *
 * Inputs
 * ------
 *   fName
 *   - the file name that the directory given is to relate
 *   path
 *   - an array of characters that will hold the path given by the user
 *   limit
 *   - the maximum number of characters that can be read into the path which includes
 *     the string termination
 * Outputs
 * -------
 *   path
 *   - the path given by the user for saving the file
 *     if path is empty then path required as current directory
 *     undefined if some error occurrs (NULL returned)
 * Return Values
 * ------ ------
 *     char * - a pointer to the character array for the path name (pointer to path)
 *     NULL   - some error occurred, path is not valid
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
char *GetPathNameForFile( char fName[ ], char path[ ], unsigned int limit, char *readwrite )
{
	if( ( !fName ) || ( !path ) || ( limit == 0 ) ) {
		fprintf( stderr, "[GetPathNameForFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
		
	printf( "Path for file '%s' ", fName ) ;
	if( readwrite != NULL ) {
		printf( "for %s ", readwrite ) ;
	}
	printf( "(<return> for no path) : " ) ;
	ReadInString( stdin, fName, limit ) ;
	if( strlen( fName ) + ReadInString( stdin, path, limit ) > LIMIT ) {
		fprintf( stderr, "Path and file name given are too long, aborting.\n\n" ) ;
		return NULL ;
	}
	printf( "\n" ) ;
	
	return path ;
}

/**** OpenFile **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open the file in the given mode using the custom fopen function if defined
 *
 * Inputs
 * ------
 *   filename
 *   - an array of characters that is the file name of the file to open
 *   filemode
 *   - file mode as necessary for fopen
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file with file name filename
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
static FILE *OpenFile( const char *filename, const char *filemode )
{
	if( &CustomFOpen == NULL ) {
		return fopen( filename, filemode ) ;
	}
	else {
		return CustomFOpen( filename, filemode ) ;
	}
}

/**** OpenFileRead ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * open the file for reading in the given mode
 *
 * Inputs
 * ------
 *   fileMode
 *   - "r" or "rb" as defined for reading by fopen
 *   iFName
 *   - an array of characters that is the file name of the file to open
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file with file name iFName
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *OpenFileRead( char *fileMode, char iFName[ ] )
{
	FILE	*ifp ;

	if( ( !fileMode ) || ( !iFName ) ) {
		fprintf( stderr, "[OpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( strncmp( fileMode, "r", 1 ) != 0 ) {	/* must begin "r..." if reading */
		fprintf( stderr, "[OpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( strncmp( fileMode, "r+", 2 ) == 0 ) {	/* writing mode, not reading */
		fprintf( stderr, "[OpenFileRead] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}

    printf( "Trying to open file '%s'...\n\n", iFName ) ;
    
    if( ( ifp = OpenFile( iFName, fileMode ) ) == NULL ) {
		fprintf( stderr, "Error opening file '%s', aborting\n\n", iFName ) ;
		/* ifp = NULL, so just return this */
    }
    else {
		printf( "File '%s' opened.\n\n", iFName ) ;
	}
    
    return ifp ;
}

/**** OpenFileWrite *****************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given the file + path name and the mode for writing, try to open the file in the
 * given mode testing it first for existence and possible overwriting
 *
 * if the file exists, the user is given a choice of overwriting the file or leaving it
 * unmodified in which case (NULL returned) the calling routine should try to save 
 * the file again giving the user another chance to specify a file name
 *
 * Inputs
 * ------
 *   fileMode
 *   - "w", "wb", "a", "ab", "r+", "r+b", "w+", "w+b", "a+", "a+b"
 *     as defined for writing by fopen
 *   oFName
 *   - the file + path name in which to open the file
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file with file + path name oFName
 *     NULL   - some error occurred (e.g. user may have declined overwrite)
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *OpenFileWrite( char *fileMode, char oFName[ ] )
{
 	FILE			*ofp ;
	unsigned int	fileStatus ;
	
	if( ( !fileMode ) || ( !oFName ) ) {
		fprintf( stderr, "[OpenFileWrite] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( strcmp( fileMode, "r" ) == 0 ) || ( strcmp( fileMode, "rb" ) == 0 ) ) {
	/* only two reading modes, all others are writing modes */
		fprintf( stderr, "[OpenFileWrite] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	ofp = TestFileForOverwrite( fileMode, oFName, &fileStatus ) ;
	/* incorporates test for fileMode validity */
    switch( fileStatus ) {
    	case 0 :
    	case 2 :
    		if( fileStatus == 0 ) {
    			printf( "The file '%s' has been created.\n\n", oFName ) ;
    		}
    		else if( fileStatus == 2 ) {
      			printf( "The file '%s' has been overwritten.\n\n", oFName ) ;
  			}
    		return ofp ;
    	case 1 :
            fprintf( stderr, "The file '%s' cannot be created.\n", oFName ) ;
            fprintf( stderr, "Possible reasons for this include: \n\n" ) ;
            
            fprintf( stderr, "a: the file may exist and be protected or in use.\n" ) ;
            fprintf( stderr, "b. the file name may not be valid for the system.\n" ) ;
            fprintf( stderr, "c. their may not be sufficient space to create the file.\n" ) ;
            fprintf( stderr, "d. you may not have sufficient access privileges.\n\n" ) ;
            
            fprintf( stderr, "Please check and try again.\n\n" ) ;
   			return NULL ;
  		case 3 :
            fprintf( stderr, "No data has been saved.\n" ) ;
            fprintf( stderr, "The file '%s' has not been altered.\n\n", oFName ) ;
            return NULL ;
    	case 4 :
            fprintf( stderr, "Cannot save to the file '%s'.\n", oFName ) ;
            fprintf( stderr, "The file may be write-protected.\n" ) ;
            fprintf( stderr, "Please check and try again.\n\n" ) ;
            return NULL ;
    	default :
    		fprintf( stderr, "Please check and try again.\n\n" ) ;
    		return NULL ;
    }
}

/**** ReadBinaryFromFile ************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an open file with the given file name (for error reporting), read the binary
 * data in from the file in the size of data given returning the results in an array that is
 * allocated internally
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the open file, as returned from fopen
 *   fileName
 *   - the file name that references the open file (for error reporting)
 *   bytes
 *   - the size of the data in bytes to read
 *	   1 : char data
 *     2 : short data
 *     4 : int data
 *   bigendian
 *   - 0 : the data is returned in little-endian format
 *         if file operation is big-endian, data is converted
 *     1 : the data is returned in big-endian format
 *         if file operation is little-endian data is converted
 *   n
 *   - a pointer to the location to store the number of data items read
 * Outputs
 * -------
 *   n
 *   - the number of data items read from the file
 *     undefined if some error occurred (NULL returned)
 * Return Values
 * ------ ------
 *     void * - an array that holds the data read from the file
 *              array is either signed (isUnsigned == 0) or unsigned (isUnsigned == 1)
 *              and of type char (bytes == 1), short (bytes == 2) or int (bytes == 4)
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * returned data requires casting to the appropriate type before it can be used
 *
 * if the file is not opened in binary mode, the result is undertermined
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of (unsigned) chars/shorts/ints
 * deallocate after using the data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void *ReadBinaryFromFile( FILE *fp, char *fileName, unsigned int bytes, unsigned int bigendian, unsigned int *n )
{
	void	*data ;

	if( ( !fp ) || ( !fileName ) || ( !n ) ) {
		fprintf( stderr, "[ReadBinaryFromFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	printf( "Reading binary data from file '%s'...\n\n", fileName ) ;
	
	if( fseek( fp, 0, SEEK_END ) != 0 ) {
		fprintf( stderr, "Cannot find the end of the file '%s', aborting.\n\n", fileName ) ;
		return NULL ;
	}
	
	*n = ( unsigned int )ftell( fp ) ;		/* get number of bytes in file */
	rewind( fp ) ;
	*n /= bytes ;
	
	if( ( data = calloc( *n, bytes ) ) == NULL ) {
		fprintf( stderr, "Cannot allocate memory to hold data, aborting.\n\n" ) ;
		return NULL ;
	}
	
	if( ( fread( data, bytes, *n, fp ) ) != *n ) {
		fprintf( stderr, "Error reading data from file '%s', aborting.\n\n", fileName ) ;
		free( data ) ;
		return NULL ;
	}
	
	if( bigendian != BIGENDIAN ) {
		data = SwitchEndian( data, *n, bytes, 1 ) ;
	}
	
	printf( "Binary data read from file '%s'.\n\n", fileName ) ;
	
	return data ;
}

/**** ReadTextFromFile **************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an open file with the given file name (for error reporting), read the
 * data in from the file assuming each entry is in hexadecimal format and is
 * separated by white space (such as space, newline or tab),
 * returning the results in an array that is allocated internally
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the open file, as returned from fopen
 *   fileName
 *   - the file name that references the open file (for error reporting)
 *   bytes
 *   - the size of the data in bytes to read
 *	   1 : char data
 *     2 : short data
 *     4 : int data
 *   bigendian
 *   - 0 : the data is returned in little-endian format
 *     1 : the data is returned in big-endian format
 *   n
 *   - a pointer to the location to store the number of data items read
 * Outputs
 * -------
 *   n
 *   - the number of data items read from the file
 *     undefined if some error occurred (NULL returned)
 * Return Values
 * ------ ------
 *     void * - an array that holds the data read from the file
 *              array is either signed (isUnsigned == 0) or unsigned (isUnsigned == 1)
 *              and of type char (bytes == 1), short (bytes == 2) or int (bytes == 4)
 *     NULL   - some error occurred
 *
 * Notes
 * -----
 * returned data requires casting to the appropriate type before it can be used
 *
 * Memory allocated (not deallocated)
 * ------ ---------  --- -----
 * the returned array of (unsigned) chars/shorts/ints
 * deallocate after using the data
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void *ReadTextFromFile( FILE *fp, char *fileName, unsigned int bytes, unsigned int bigendian, unsigned int *n )
{
	void 			*data ;
	void			*oldDataPtr ;
	unsigned int	tint ;
	unsigned int	nread ;

	if( ( !fp ) || ( !fileName ) || ( !n ) ) {
		fprintf( stderr, "[ReadTextFromFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	printf( "Reading hexadecimal 'text' data from file '%s'...\n\n", fileName ) ;
	
	*n = 0 ;
	data = NULL ;
	oldDataPtr = data ;
	while( ( nread = fscanf( fp, "%x", &tint ) ) != EOF ) {
		*n += 1 ;
		if( nread != 1 ) {
			fprintf( stderr, "Failed to read %d data value from file '%s', aborting.\n\n", *n, fileName ) ;
			if( oldDataPtr != NULL ) {
				free( oldDataPtr ) ;
			}
			*n = 0 ;
			return NULL ;
		}
		data = realloc( oldDataPtr, *n*bytes ) ;
		if( data == NULL ) {
			fprintf( stderr, "Cannot allocate memory for data, aborting.\n\n" ) ;
			if( oldDataPtr != NULL ) {
				free( oldDataPtr ) ;
			}
			*n = 0 ;
			return NULL ;
		}
		oldDataPtr = data ;
		switch( bytes ) {
			case BYTEBYTES :
				( ( unsigned char * )data )[ *n - 1 ] = ( unsigned char )tint ;
				break ;
			case HWORDBYTES :
				( ( unsigned short * )data )[ *n - 1 ] = ( unsigned short )tint ;
				break ;
			case WORDBYTES :
				( ( unsigned int * )data )[ *n - 1 ] = tint ;
				break ;
		}
	}
		
	if( *n == 0 ) {
		fprintf( stderr, "No data in file '%s', aborting.\n\n", fileName ) ;
		free( data ) ;
		return NULL ;
	}

	if( bigendian ) {
		data = SwitchEndian( data, *n, bytes, 1 ) ;
	}
	
	printf( "Hexadecimal data read from file '%s'.\n\n", fileName ) ;
	
	return data ;
}

/**** ResetStdIO ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * procedure to redirect stdin, stdout or stderr to their standard locations
 *
 * Inputs
 * ------
 *   stdIO
 *	 - pointer to FILE descriptor
 *     stdin, stdout or stderr only
 * Return Values
 * ------ ------
 *     0        : stdio successfully redirected to default location
 *     non-zero : some error occurred (stdio may or may not be redirected)
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
int ResetStdIO( FILE *stdIO )
{
	char	tmpname[ LIMIT ] ;
	
	if( stdIO == stdin ) {
		strcpy( tmpname, ":tt" ) ;
	}
	else {
		strcpy( tmpname, tmpnam( NULL ) ) ;
	}
	
	freopen( tmpname, "r", stdIO ) ;
	
	return remove( tmpname ) ;
}

/**** SaveData **********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * get the file name from the user and open the file for writing in either binary or
 * text mode (given the user), write the data of the required type and close the file
 *
 * Inputs
 * ------
 *   data
 *   - an array of data to write to the file cast to void *
 *   n
 *   - the number of data points in the array passed
 *   bytes
 *   - the number of bytes in the data that is to be written
 *     1 = char data
 *     2 = short data
 *     4 = int data
 *	 isUnsigned
 *   - 0 : the data to be written is signed
 *     1 : the data to be written is unsigned
 *   dataType
 *   - an optional string that defines the data that is to written out
 *     displayed to the user during file selection time
 *     pass NULL if non-specific data is to be written
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void SaveData( void *data, unsigned int n, unsigned int bytes, unsigned int isUnsigned, char *dataType )
{
	char			fileMode[ 3 ] = "w" ;
	FILE			*fp ;
	char			fileName[ LIMIT ] ;
	unsigned int	binary ;
	unsigned int	bigendian ;
	
	binary = 0 ;
	
	do {
		if( binary ) {
			fileMode[ 1 ] = '\0' ;					/* remove any previous binary addition */
		}
	
		printf( "Please give the name of the file to write " ) ;
		if( dataType != NULL ) {
			printf( "%s ", dataType ) ;
		}
		printf( "data to.\n\n" ) ;
	
		GetFileName( fileName, LIMIT, "writing" ) ;
		
		binary = YesNo( "Data in Binary mode", "binary", "hexadecimal text" ) ;
		if( binary ) {
			strcat( fileMode, "b" ) ;
		}

	} while( ( fp = OpenFileWrite( fileMode, fileName ) ) == NULL ) ;
	
	if( BIGENDIAN && binary ) {
		bigendian = !YesNo( "Data will be written in Big-Endian mode.  Write data in Little-Endian mode", "little-endian", "big-endian" ) ;
	}
	else {
		bigendian = YesNo( "Data will be written in Little-Endian mode.  Write data in Big-Endian mode", "big-endian", "little-endian" ) ;
	}
	
	if( binary ) {
		WriteBinaryToFile( fp, fileName, data, n, bytes, bigendian ) ;
	}
	else {
		WriteTextToFile( fp, fileName, data, n, bytes, isUnsigned, bigendian ) ;	
	}
	
	fclose( fp ) ;
}

/**** TestFileForOverwrite **********************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given the file + path name and the mode for writing, testing the file for existence
 * and possible overwriting and open for writing if possible
 *
 * if the file exists, the user is given a choice of overwriting the file or leaving it
 * unmodified in which case (NULL returned) the calling routine should try to save 
 * the file again giving the user another chance to specify a file name
 *
 * Inputs
 * ------
 *   fileMode
 *   - "w", "wb", "a", "ab", "r+", "r+b", "w+", "w+b", "a+", "a+b"
 *     as defined for writing by fopen
 *   oFName
 *   - the file + path name in which to open the file
 *   fileStatus
 *   - a pointer to a location to store the file's status
 * Outputs
 * -------
 *   fileStatus
 *   - 0.	file created for writing
 *     1.	file could not be created for writing (permissions?)
 *     2.	file already exists, overwriting contents
 *     3.	file already exists, not overwriting contents
 *     4.	file already exists, permission to overwrite denied
 * Return Values
 * ------ ------
 *     FILE * - a pointer to the opened file with file + path name oFName
 *     NULL   - some error occurred (e.g. user may have declined overwrite)
 *
 * Notes
 * -----
 * if the file pointer is non-NULL, the file should be closed after use
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
FILE *TestFileForOverwrite( char *fileMode, char oFName[ ], unsigned int *fileStatus )
{
	char			readMode[ 3 ] = "r" ;
	unsigned int	fileModeLength ;
	FILE			*ofp ;
	char			continued[ LIMIT ] ;
	
	if( ( !fileMode ) || ( !fileStatus ) || ( !oFName ) ) {
		fprintf( stderr, "[TestFileForOverwrite] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( strcmp( fileMode, "r" ) == 0 ) || ( strcmp( fileMode, "rb" ) == 0 ) ) {
	/* only two reading modes, all others are writing modes */
		fprintf( stderr, "[TestFileForOverwrite] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return NULL ;
	}
	
	if( ( ( fileModeLength = strlen( fileMode ) ) > 1 ) && ( fileMode[ 1 ] == 'b' ) ) {
		strcpy( readMode, "rb" ) ;
	}
	else if( ( fileModeLength > 2 ) && ( fileMode[ 2 ] == 'b' ) ) {
		strcpy( readMode, "rb" ) ;
	}
	
    if( ( ofp = OpenFile( oFName, readMode ) ) == NULL ) {
    /* this tests if the file already exists but does not alter it              */
    /* the test fails if it doesn't exist or the file is read protected         */
    
        if( ( ofp = OpenFile( oFName, fileMode ) ) == NULL ) {
        /* file may exist but be read & write protected */
        	*fileStatus = 1 ;
        	return NULL ;
        }
		else {	/* file created and opened */
			*fileStatus = 0 ;
            return ofp ;
		}    
    }
    else {	/* file exists, overwrite it? */
        fclose( ofp ) ;
        
        printf( "The file '%s' already exists.\n", oFName ) ;
        printf( "To save to this file will overwrite its contents.\n" ) ;
        printf( "Do you wish to continue to save to this file?\n\n" ) ;
        
        printf( "Please enter your choice (y or n) : " ) ;
        ReadInString( stdin, continued, LIMIT ) ;
        printf( "\n" ) ;
        
        switch( tolower( continued[ 0 ] ) ) {
            case 'y' :
                if( ( ofp = OpenFile( oFName, fileMode ) ) == NULL ) {
                /* tries to open the output file (which exists) to write to */
                	*fileStatus = 4 ;
                	return NULL ;
                    /* the file is write protected by some means so cannot save */
                }
                else {	/* opened file for saving */
                	*fileStatus = 2 ;
                    return ofp ;
                }
            case 'n' :
            default :
            	*fileStatus = 3 ;
            	return NULL ;
        }
    }
}

/**** WriteBinaryToFile *************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an open file with the given file name (for error reporting), write the given
 * data in binary mode to the file
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the open file, as returned from fopen
 *   fileName
 *   - the file name that references the open file (for error reporting)
 *   data
 *   - the array of data to write in binary mode to the file
 *   n
 *   - the number of data items to write
 *   bytes
 *   - the number of bytes in the data that is to be written
 *     1 = char data
 *     2 = short data
 *     4 = int data
 *   bigendian
 *   - 0 : the data must be written in little-endian format
 *         if file operation is big-endian, data is converted
 *     1 : the data must be written in big-endian format
 *         if file operation is little-endian data is converted
 *
 * Notes
 * -----
 * if the file is not opened in binary mode, the result is undertermined
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void WriteBinaryToFile( FILE *fp, char *fileName, void *data, unsigned int n, unsigned int bytes, unsigned int bigendian )
{
	void	*writeData ;
	
	if( ( !fp ) || ( !fileName ) || ( !data ) || ( n == 0 ) ) {
		fprintf( stderr, "[WriteBinaryToFile] Error in arguments, aborting.\n\n" ) ;
		/* function name given since intended as internal error for programmer */
		return ;
	}
	
	printf( "Writing binary data to file '%s'...\n\n", fileName ) ;
	
	if( bigendian != BIGENDIAN ) {
		writeData = SwitchEndian( data, n, bytes, 0 ) ;
	}
	else {
		writeData = data ;
	}
	
	if( ( fwrite( writeData, bytes, n, fp ) ) != n ) {
		fprintf( stderr, "Error writing data to file, file may be corrupted.\n\n" ) ;
	}
	
	if( bigendian != BIGENDIAN ) {
		free( writeData ) ;
	}	
	
	printf( "Binary data written to file '%s'.\n\n", fileName ) ;
}

/**** WriteTextToFile ***************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * given an open file with the given file name (for error reporting), write the given
 * data in hexadecimal text mode to the file
 *
 * Inputs
 * ------
 *   fp
 *   - a pointer to the open file, as returned from fopen
 *   fileName
 *   - the file name that references the open file (for error reporting)
 *   data
 *   - the array of data to write in hexadecimal text mode to the file
 *   n
 *   - the number of data items to write
 *   bytes
 *   - the number of bytes in the data that is to be written
 *     1 = char data
 *     2 = short data
 *     4 = int data
 *	 isUnsigned
 *   - 0 : the data to be written is signed
 *     1 : the data to be written is unsigned
 *   bigendian
 *   - 0 : the data must be written in little-endian format
 *     1 : the data must be written in big-endian format
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
void WriteTextToFile( FILE *fp, char *fileName, void *data, unsigned int n, unsigned int bytes, unsigned int isUnsigned, unsigned int bigendian )
{
	void			*writeData ;
	unsigned int	i ;
	
	if( ( !fp ) || ( !fileName ) || ( !data ) || ( n == 0 ) ) {
		fprintf( stderr, "[WriteTextToFile] Error in arguments, aborting.\n\n" ) ;
		return ;
	}
	
	printf( "Writing hexadecimal 'text' data to file '%s'...\n\n", fileName ) ;
	
	if( bigendian ) {
		writeData = SwitchEndian( data, n, bytes, 0 ) ;
	}
	else {
		writeData = data ;
	}
	
	for( i = 0 ; i < n ; i += 1 ) {
		switch( bytes ) {
			case BYTEBYTES :
				if( isUnsigned ) {
					fprintf( fp, "0x%.8x\n", ( ( unsigned char * )writeData )[ i ] ) ;
				}
				else {
					fprintf( fp, "0x%.8x\n", ( ( char * )writeData )[ i ] ) ;
				}
				break ;
			case HWORDBYTES :
				if( isUnsigned ) {
					fprintf( fp, "0x%.8x\n", ( ( unsigned short * )writeData )[ i ] ) ;
				}
				else {
					fprintf( fp, "0x%.8x\n", ( ( short * )writeData )[ i ] ) ;
				}
				break ;
			case WORDBYTES :
				if( isUnsigned ) {
					fprintf( fp, "0x%.8x\n", ( ( unsigned int * )writeData )[ i ] ) ;
				}
				else {
					fprintf( fp, "0x%.8x\n", ( ( int * )writeData )[ i ] ) ;
				}
				break ;
			default :
				fprintf( stderr, "[WriteTextToFile] Error in arguments, aborting.\n\n" ) ;
				/* function name given since intended as internal error for programmer */
				if( bigendian != BIGENDIAN ) {
					free( writeData ) ;
				}
				return ;
		}
	}
	
	if( bigendian ) {
		free( writeData ) ;
	}	
	
	printf( "Hexadecimal data written to file '%s'.\n\n", fileName ) ;
}
