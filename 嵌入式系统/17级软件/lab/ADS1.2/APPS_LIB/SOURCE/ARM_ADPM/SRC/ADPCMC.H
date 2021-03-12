/*
 * Adaptive Differential Pulse Code Modulation C test prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _ADPCM_C_
#define _ADPCM_C_

#include "adpstruc.h"

#ifndef MAXBITS
	/* define the maximum number of bits for a PCM value */
	#define	MAXBITS	16
#endif	/* MAXBITS */

int DecodeADPCMC( int adpcmSample, ADPCMStatePtr decodeStatePtr ) ;
int EncodeADPCMC( int pcmSample, int previousADPCMEncoded, ADPCMStatePtr statePtr ) ;

#endif	/* _ADPCM_C_ */
