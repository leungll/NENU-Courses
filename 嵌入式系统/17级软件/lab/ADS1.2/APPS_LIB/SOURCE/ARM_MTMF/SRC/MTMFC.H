/*
 * Multi-Tone Multi-Frequency Tone Detect/Generate prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _MULTITONE_S_
#define _MULTITONE_S_

typedef struct	ToneState	ToneState ;
typedef	struct	ToneState	*ToneStatePtr ;

struct ToneState {
	int tone ;
	int	w0 ;
	int	w1 ;
} ;

void ToneDetectSetup( ToneState toneStates[ ], int tones[ ], unsigned int nTones ) ;
short *ToneDetect( short *inputs, unsigned int nInputs, ToneState toneStates[ ], unsigned int nTones ) ;
void ToneDetectResults( unsigned int outputs[ ], unsigned int shift, ToneState toneStates[ ], unsigned int nTones ) ;
void ToneGenerateSetup( ToneStatePtr toneStatePtr, int tone, int correction, unsigned int level ) ;
short *ToneGenerate( short outputs[ ], unsigned int nOutputs, ToneState toneStates[ ], unsigned int nTones ) ;

#endif	/* _MULTITONE_S_ */

