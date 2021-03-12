;/*
; * IS-54-B Convolutional Encoder assembler macro
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;---Convolutional Encoder-----------------------------------------------
;
; Purpose   : An implementation of the IS-54 FEC speech Convolutional 
;             encoder that interlaces two
;             16-bit words to produce a 32-bit word.
;
; Date      : 1/4/98
;
;-----------------------------------------------------------------------

	INCLUDE regchekm.h


; Macro Parameters 
; $in    = input register, contains input[i] in top 16-bits,
;                          and input[i+1] in bottom 16-bits.
; $G0    = temporary register (for G0, one of the convoluted words)
; $G1    = temporary register (for G1, one of the convoluted words)
; $msk1  = input register, must contain the binary mask 0x0F000F00
; $msk2  = input register, must contain the binary mask 0x30303030
; $msk3  = input register, must contain the binary mask 0x44444444
; $out   = register into which output is placed (can be the same as 
;          any of the others)
;
; Only $G0, $G1, and $out are corrupted.


 MACRO
 ConvolutionalEncoderKernelMacro  $in, $G0, $G1, $msk1, $msk2, $msk3, $out
 
 DISTINCT $G0, $G1, $in
 DISTINCT $G0, $G1, $msk1, $msk2, $msk3
 
 EOR	$G1, $in, $in, LSR #2	; G1 = D0^D2
 EOR	$G0, $in, $G1, LSR #3	; G0 = D0^D3(D0^D2) 		= D0^D3^D5
 EOR	$G1, $G0, $G1, LSR #2	; G1 = (D0^D3^D5)^D2(D0^D2) = D0^D2^D3^D4^D5
 EOR	$G0, $G0, $in, LSR #1	; G0 = (D0^D3^D5)^D1		= D0^D1^D3^D5

; The Aim of the next bit is to combine the 16-bit values G0 and G1 into
; one 32-bit value by interlacing their bits.

; First remove rubbish from top of words by shifting left 16 places.
 MOV   $G0,  $G0,  LSL #16      ;  G0 = ABCD0000
 MOV   $G1,  $G1,  LSL #16      ;  G1 = WXYZ0000

; We want AWBXCYDZ, we will achieve this by constructing:
; G0 = A0B0C0D0, and
; G1 = W0X0Y0Z0, and then OR'ing them together.

; Dealing at the byte level   (Mask = 0x00FF0000)

 ORR    $G0, $G0, $G0, LSR #8   ; G0 = AB??CD00
 ORR    $G1, $G1, $G1, LSR #8   ; G1 = WX??YZ00
 BIC    $G0, $G0, #0x00FF0000   ; G0 = AB00CD00
 BIC    $G1, $G1, #0x00FF0000   ; G1 = WX00YZ00

; Dealing at the nybble level (Mask = 0x0F000F00)
 ORR    $G0, $G0, $G0, LSR #4   ; G0 = A?B0C?D0
 ORR    $G1, $G1, $G1, LSR #4   ; G1 = W?X0Y?Z0
 BIC    $G0, $G0, $msk1         ; G0 = A0B0C0D0
 BIC    $G1, $G1, $msk1         ; G1 = W0X0Y0Z0

; Dealing at the 2-bit level  (Mask = 0x30303030)
 ORR    $G0, $G0, $G0, LSR #2
 ORR    $G1, $G1, $G1, LSR #2
 BIC    $G0, $G0, $msk2
 BIC    $G1, $G1, $msk2

; Dealing at the 1-bit level  (Mask = 0x44444444)
 ORR    $G0, $G0, $G0, LSR #1
 ORR    $G1, $G1, $G1, LSR #1
 BIC    $G0, $G0, $msk3
 BIC    $G1, $G1, $msk3

; Now to OR the two together to interleave.
 ORR    $out, $G1, $G0, LSR #1

 MEND

;=========================================================================
 END

