/*
 * Mathematics assembler test prototypes
 * Copyright (C) ARM Limited 1998-1999. All rights reserved.
 */

#ifndef _MATHS_TEST_S_
#define _MATHS_TEST_S_

typedef	unsigned int	u32 ;
/* all functions take two arrays of u32's with lowest significant bit first */
/* each index of the array holds a 32-bit part of number being used */

void init_ADDABS( u32 *arg1, u32 *arg2 ) ;
void init_SIGNSAT( u32 *arg1, u32 *arg2 ) ;

void init_UMUL_32x32_64( u32 *arg1, u32 *arg2 ) ;
void init_SMUL_32x32_64( u32 *arg1, u32 *arg2 ) ;
void init_MUL_64x64_64( u32 *arg1, u32 *arg2 ) ;
void init_UMUL_64x64_128( u32 *arg1, u32 *arg2 ) ;
void init_SMUL_64x64_128( u32 *arg1, u32 *arg2 ) ;

void init_UDIV_32d16_16r16( u32 *arg1, u32 *arg2 ) ;
void init_SDIV_32d16_16r16( u32 *arg1, u32 *arg2 ) ;
void init_UDIV_32d32_32r32( u32 *arg1, u32 *arg2 ) ;
void init_SDIV_32d32_32r32( u32 *arg1, u32 *arg2 ) ;
void init_UDIV_64d32_32r32( u32 *arg1, u32 *arg2 ) ;
void init_SDIV_64d32_32r32( u32 *arg1, u32 *arg2 ) ;
void init_UDIV_64d64_64r64( u32 *arg1, u32 *arg2 ) ;
void init_SDIV_64d64_64r64( u32 *arg1, u32 *arg2 ) ;

void init_SQR_32_16r17( u32 *arg1, u32 *arg2 ) ;
void init_CBR_32_11( u32 *arg1, u32 *arg2 ) ;

void init_UDIVF_32d32_32( u32 *arg1, u32 *arg2 ) ;
void init_SDIVF_32d32_32( u32 *arg1, u32 *arg2 ) ;

void init_ARMCOS( u32 *arg1, u32 *arg2 ) ;
void init_ARMSIN( u32 *arg1, u32 *arg2 ) ;

#endif	/* _MATHS_TEST_S_ */