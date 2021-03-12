/*
 * Adaptive Differential Pulse Code Modulation structure definition
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ADPCM_STRUCTURE_
#define _ADPCM_STRUCTURE_

#ifndef _ADPCMSTATE
#define _ADPCMSTATE

typedef struct	ADPCMState	ADPCMState ;
typedef 		ADPCMState	*ADPCMStatePtr ;

struct ADPCMState {
    int  stepIndex ;
    int  prediction ;
} ;
/* define the structure required internally during function calls */

/* must be initialised before the first call of a sequence */


#endif	/* _ADPCMSTATE */

#endif	/* _ADPCM_STRUCTURE_ */
