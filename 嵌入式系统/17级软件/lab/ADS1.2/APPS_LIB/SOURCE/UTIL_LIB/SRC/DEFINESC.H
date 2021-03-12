/*
 * Utility Library: Definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _DEFINES_C_
#define _DEFINES_C_

/**** Defines ***********************************************************************
 *
 * Version & Date
 * -------   ----
 * 1.0.0, 30/06/1998
 *
 * Description
 * -----------
 * define some commonly used data values, data types and macros
 *
 * Data Values --
 *
 * Big endian flag (BIGENDIAN)
 * Pi (machine dependent & independent variations, PI)
 * Maximum size of static array defintion (LIMIT)
 * Default directory path (PATH)
 * Size of char, short and int data (BYTEBYTES, HWORDBYTES, WORDBYTES)
 *
 * Data Types --
 *
 * Boolean
 * Complex
 * Unsigned short
 * Unsigned integer
 * 64-bit signed & unsigned integers
 * 128-bit signed & unsigned integers
 * 2D integer array pointer
 * 2D unsigned character array pointer
 *
 * Macros --
 * 
 * Maximum
 *
 * History (with dates)
 * -------  ---- -----
 * 1.0.0, 30/06/1998    first release
 *
 ************************************************************************************/

#ifndef	BIGENDIAN
	#ifdef __BIG_ENDIAN
		#define	BIGENDIAN	1	/* in big-endian mode */
	#else
		#define	BIGENDIAN	0	/* in little-endian mode */
	#endif
#endif	/* BIGENDIAN */

#ifndef PIMI
	#define PIMI	3.14159265358
	/* definition is platform independent, always same value, used for PI */
#endif	/* PIMI */

#ifndef PIMD
	#define PIMD	4.0*atan( 1.0 )
	/* machine dependent difinition */
#endif	/* PIMD */

#ifndef	PI
	#define	PI	PIMI
#endif	/* PI */

#ifndef LIMIT
	#define LIMIT	1000
	/* LIMIT provides a fixed maximum size for strings during local declarations */
#endif	/* LIMIT */

#ifndef PATH
	#define PATH	""
#endif	/* PATH */

#ifndef BYTEBYTES
	#define BYTEBYTES	sizeof( char )
#endif	/* BYTEBYTES */

#ifndef HWORDBYTES
	#define	HWORDBYTES	sizeof( short )
#endif	/* HWORDBYTES */

#ifndef WORDBYTES
	#define	WORDBYTES	sizeof( int )
#endif	/* WORDBYTES */

#ifndef _BOOLEAN
#define _BOOLEAN

#if BIGENDIAN	/* counteract bug in ARM SDT 2.11a for enum cast to char */
	typedef unsigned char	Boolean ;
	#define FALSE	0
	#define	TRUE	1
#else
	typedef enum{ FALSE = 0, TRUE = 1 } Boolean ;
#endif

#endif	/* _BOOLEAN */

#ifndef _COMPLEX
#define _COMPLEX

typedef struct 	Complex	Complex ;
typedef 		Complex	*ComplexPtr ;

struct Complex {
	int r ;
	int	i ;
} ;

#endif	/* _COMPLEX */

#ifndef _USHORT
#define _USHORT

typedef unsigned short	ushort ;

#endif	/* _USHORT */

#ifndef _UINT
#define _UINT

typedef unsigned int	uint ;

#endif	/* _UINT */

#ifndef _UNSINT64
#define _UNSINT64

typedef struct	UnsInt64	UnsInt64 ;

struct UnsInt64 {
	unsigned int	lsw ;
	unsigned int	msw ;
} ;

#endif	/* _UNSINT64 */

#ifndef _INT64
#define _INT64

typedef struct Int64	Int64 ;

struct Int64 {
	int	lsw ;
	int	msw ;
} ;

#endif	/* _INT64 */

#ifndef _UNSINT128
#define _UNSINT128

typedef struct UnsInt128	UnsInt128 ;

struct UnsInt128 {
	unsigned int	llsw ;
	unsigned int	lsw ;
	unsigned int	msw ;
	unsigned int	mmsw ;
} ;

#endif	/* _UNSINT128 */

#ifndef _INT128
#define _INT128

typedef struct Int128	Int128 ;

struct Int128 {
	int	llsw ;
	int	lsw ;
	int	msw ;
	int	mmsw ;
} ;

#endif	/* _INT128 */

#ifndef _IARRAY
#define _IARRAY

typedef int **IArray ;

#endif	/* _IARRAY */

#ifndef _UCARRAY
#define _UCARRAY

typedef unsigned char **UCArray ;

#endif	/* _UCARRAY */

#ifndef MAX
	#define MAX( A, B )	( ( A ) >= ( B ) ? ( A ) : ( B ) )
#endif	/* MAX */

#endif	/* _DEFINES_C_ */