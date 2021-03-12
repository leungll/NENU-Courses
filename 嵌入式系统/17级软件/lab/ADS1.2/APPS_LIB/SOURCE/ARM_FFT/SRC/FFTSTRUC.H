/*
 * Fast Fourier Transform structure definition
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _FFTSTRUC_
#define _FFTSTRUC_

#ifndef _COMPLEX
#define _COMPLEX

typedef struct 	Complex	Complex ;
typedef 		Complex	*ComplexPtr ;

struct Complex {
	int r ;
	int	i ;
} ;

#endif	/* _COMPLEX   */

#endif	/* _FFTSTRUC_ */