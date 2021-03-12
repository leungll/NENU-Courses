/*
 * Adaptive Differential Pulse Code Modulation ASM prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ADPCM_S_
#define _ADPCM_S_

#include "adpstruc.h"

int adpcm_encode( int pcmSample, ADPCMStatePtr encodeStatePtr ) ;
int adpcm_decode( int adpcmSample, ADPCMStatePtr decodeStatePtr ) ;

#endif	/* _ADPCM_S_ */
