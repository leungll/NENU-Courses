/*
 * Utility Library: Print macros
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _PRINTING_C_
#define _PRINTING_C_

#include <stdio.h>

#ifndef _PRINTTYPE
#define _PRINTTYPE

/* define the print types recognised by the printing macros
 *
 * HEX, UHEX	print format = 0x%.8x
 * HST, UHST	print format = 0x%.4x
 * HCH, UHCH	print format = 0x%.2x
 * INT, UINT	print format = %4d
 * SHT, USHT	print format = %4d
 * DEC			print format = %.8lf
 * CHA, UCHA	print format = %3c
 */
typedef enum {
	HEX  = 0,
	UHEX,
	HST,
	UHST,
	HCH,
	UHCH,
	INT,
	UINT,
	SHT,
	USHT,
	DEC,
	CHA,
	UCHA
} PrintType ;

#endif	/* _PRINTTYPE */

/**** PRINTARRAY ********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the required (consecutive) set of data items from the given array to the screen
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of values to print from
 *   OFFSET
 *   - an offset into the array to start printing from
 *     pass as zero to print from the beginning
 *   LENGTH
 *   - the number of values to print
 *     printing stops after element OFFSET + LENGTH - 1 has been printed
 *     to print the whole array pass OFFSET = 0, LENGTH = size of array
 *     OFFSET + LENGTH should not be greater than the size of the array
 *   TYPE
 *   - the type of the data and thus printing to be performed selected from PrintType above
 *   NEWLINE
 *   - the number of outputs to print before a new line is printed
 *     to print the entire set of data on one line pass LENGTH
 *     to print each entry on a new line pass 1
 *   DESCRIPTION
 *   - an optional string to describe the data being printed to the screen
 *     if string given, it will be printed terminated with ".\n\n"
 *     if no string required, pass NULL
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define PRINTARRAY( ARRAY, OFFSET, LENGTH, TYPE, NEWLINE, DESCRIPTION ) { \
	int	counter ; \
	if( DESCRIPTION != NULL ) { \
		printf( "%s.\n\n",  ( char * )DESCRIPTION ) ; \
	} \
	printf( "Number of data items '%d'.\n\n", LENGTH ) ; \
	for( counter = OFFSET ; counter < OFFSET + LENGTH ; counter += 1 ) { \
		PRINTTYPE( ARRAY[ counter ], TYPE ) \
		if( ( counter != OFFSET + LENGTH - 1 ) && ( ( counter - OFFSET + 1 )%( NEWLINE ) == 0 ) ) { \
			printf( "\n" ) ; \
		} \
	} \
	printf( "\n\n" ) ; \
}

/**** PRINTARRAY2D ******************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the required (consecutive) set of data items from the given array to the screen
 * working one row at a time - across the columns before incrementing the column
 *
 * Inputs
 * ------
 *   ARRAY
 *   - the array of values to print from
 *   XOFFSET
 *   - an offset into the column of the array to start printing from
 *     pass as zero to print from the first column
 *   WIDTH
 *   - the number of columns to print
 *     printing in a row stops after element XOFFSET + WIDTH - 1 has been printed
 *     to print all columns pass XOFFSET = 0, WIDTH = number of columns
 *     XOFFSET + WIDTH should not be greater than the number of columns
 *   YOFFSET
 *   - an offset into the row of the array to start printing from
 *     pass as zero to print from the first row
 *   HEIGHT
 *   - the number of rows to print
 *     printing in a column stops after element YOFFSET + HEIGHT - 1 has been printed
 *     to print all rows pass YOFFSET = 0, HEIGHT = number of rows
 *     YOFFSET + HEIGHT should not be greater than the number of rows
 *   TYPE
 *   - the type of the data and thus printing to be performed selected from PrintType above
 *   XNEWLINE
 *   - the number of items in a row to print before a new line is printed
 *     to print the entire row of data on one line pass WIDTH
 *     to print each entry on a new line pass 1
 *     (each new row starts on a new line)
 *   DESCRIPTION
 *   - an optional string to describe the data being printed to the screen
 *     if string given, it will be printed terminated with ".\n\n"
 *     if no string required, pass NULL
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define PRINTARRAY2D( ARRAY, XOFFSET, WIDTH, YOFFSET, HEIGHT, TYPE, XNEWLINE, DESCRIPTION ) { \
	int i ; \
	int j ; \
	if( DESCRIPTION != NULL ) { \
		printf( "%s.\n\n", ( char * )DESCRIPTION ) ; \
	} \
	printf( "Number of data items '%d' * '%d'.\n\n", WIDTH, HEIGHT ) ; \
	for( j = YOFFSET ; j < YOFFSET + HEIGHT ; j += 1 ) { \
		for( i = XOFFSET ; i < XOFFSET + WIDTH ; i += 1 ) { \
			PRINTTYPE( ARRAY[ j ][ i ], TYPE ) \
			if( ( i != XOFFSET + WIDTH - 1 ) && ( ( i - XOFFSET + 1 )%( XNEWLINE ) == 0 ) ) { \
				printf( "\n" ) ; \
			} \
		} \
		printf( "\n" ) ; \
	} \
	printf( "\n" ) ; \
}

/**** PRINTTYPE *********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * print the given data item in the given type to the screen
 *
 * Inputs
 * ------
 *   ELEMENT
 *   - the value to print
 *   TYPE
 *   - the type of the data and thus printing to be performed selected from PrintType above
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/
#define PRINTTYPE( ELEMENT, TYPE ) { \
	switch( TYPE ) { \
		case HST : \
			printf( "0x%.4x ", ( signed short )ELEMENT ) ; \
			break ; \
		case UHST : \
			printf( "0x%.4x ", ( unsigned short )ELEMENT ) ; \
			break ; \
		case HCH : \
			printf( "0x%.2x ", ( signed char )ELEMENT ) ; \
			break ; \
		case UHCH : \
			printf( "0x%.2x ", ( unsigned char )ELEMENT ) ; \
			break ; \
		case INT : \
			printf( "%4d ", ( signed int )ELEMENT ) ; \
			break ; \
		case UINT : \
			printf( "%4d ", ( unsigned int )ELEMENT ) ; \
			break ; \
		case SHT : \
			printf( "%4d ", ( signed short )ELEMENT ) ; \
			break ; \
		case USHT : \
			printf( "%4d ", ( unsigned short )ELEMENT ) ; \
			break ; \
		case DEC : \
			printf( "%.8lf ", ( double )ELEMENT ) ; \
			break ; \
		case CHA : \
			printf( "%3c ", ( signed char )ELEMENT ) ; \
			break ; \
		case UCHA : \
			printf( "%3c ", ( unsigned char )ELEMENT ) ; \
			break ; \
		case UHEX : \
			printf( "0x%.8x ", ( unsigned int )ELEMENT ) ; \
			break ; \
		case HEX : \
		default : \
			printf( "0x%.8x ", ( signed int )ELEMENT ) ; \
			break ; \
	} \
}

#endif	/* _PRINTING_C_ */