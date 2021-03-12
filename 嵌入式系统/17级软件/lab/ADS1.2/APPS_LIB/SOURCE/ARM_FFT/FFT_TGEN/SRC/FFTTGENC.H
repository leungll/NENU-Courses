/*
 * Fast Fourier Transform C definitions
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FFTTGEN_C_
#define _FFTTGEN_C_

#ifndef TABLEFNAME
	#define	TABLEFNAME	"ffttabls.h"
#endif	/* TABLEFNAME */

#ifndef N
	#define N	1024
#endif	/* N */

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

#endif	/* _FFTTGEN_C_ */