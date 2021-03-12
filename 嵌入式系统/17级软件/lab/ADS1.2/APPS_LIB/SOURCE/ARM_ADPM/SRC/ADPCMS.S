;/*
; * Adaptive Differential Pulse Code Modulation assembler
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;=============================================================================
;
; ARM ADPCM implementation
;
;=============================================================================

				INCLUDE intworkm.h

                AREA    |ADPCM$$Code|, CODE, READONLY $interwork


;============================================================================
; --- adpcm_encode ---
;============================================================================
;
; Arguments:    a1 (r0) == input sample (16-bit linear PCM)
;               a2 (r1) == pointer to 8 byte state block
;
; Returns:      a1 (r0) == output sample (4-bit ADPCM)
;
; C varient:    char adpcm_encode(int indata, adpcm_state *state);
;
; Notes:        The state block should be clear on the first call.
;============================================================================


                EXPORT  adpcm_encode
adpcm_encode    ROUT

                ; Free up a few scratch registers: v1,v2,lr 
                ; Registers already available are: a2,a3,ip
                STMFD   sp!,{v1-v2, lr}

                ; --- Load in the saved state, and use the lookup table

                LDMIA   a2,{ip,lr}              ;Load index/Previous val
                ADR     v1,stepSizeTable        ;Point to the step size table
                LDR     v1,[v1,ip, LSL#2]       ;Load the step size

                ; --- If the sample were still in 8-bit A-law/u-law PCM then    ---
                ; --- must add a conversion routine/macro here to 16-bit linear ---

                ; --- Compute difference with previous value ---
                SUBS    a4,a1,lr                ;Compute the difference
                MOVLT   a1,#8                   ;If diff<0, sign is -ve
                RSBLT   a4,a4,#0                ;...and make it +ve
                MOVGE   a1,#0                   ;Otherwise it's +ve

                ; --- Divide and clamp ---
                ;
                ; This code approxiately computes:
                ;
                ;    delta =  diff*4/step
                ;    vpdiff = (delta+0.5)*step/4

                MOV     a3,#0                   ;Delta is 0
                MOV     v2,v1,LSR #3            ;Get vpdiff = step/8

                CMP     a4,v1                   ;Compare diff with step
                MOVGE   a3,#4                   ;Make delta 4
                SUBGE   a4,a4,v1                ;...subract step from delta
                ADDGE   v2,v2,v1                ;...and step to vpdiff

                CMP     a4,v1,LSR #1            ;Compare diff with step
                ORRGE   a3,a3,#2                ;OR delta with 2
                SUBGE   a4,a4,v1,LSR #1         ;...subract step from delta
                ADDGE   v2,v2,v1,LSR #1         ;...and step to vpdiff

                CMP     a4,v1,LSR #2            ;Compare diff with step
                ORRGE   a3,a3,#1                ;OR delta with 1
                ADDGE   v2,v2,v1,LSR #2         ;...and step to vpdiff

                ; --- Now update the previous value ---

                CMP     a1,#0                   ;What was the sign?
                SUBNE   lr,lr,v2                ;-ve?  Subtract vpdiff
                ADDEQ   lr,lr,v2                ;+ve?  Add vpdiff

                ; --- Clamp previous value to 16 bits ---

                MOV     v1,#&8000               ;Clamp value
                CMP     lr,v1                   ;Is it out of range?
                SUBGE   lr,v1,#1                ;Yes, MAX it
                CMN     lr,v1                   ;Out of range other way?
                RSBLE   lr,v1,#1                ;Yes -- Clamp

                ; --- Assemble value, update index and step values ---

                SUBS    v1,a3,#3
                MOVLE   v1,#-1
                MOVGT   v1,v1,LSL #1
                ADDS    ip,ip,v1                ;Add the value
                ORR     a3,a3,a1                ;OR delta with the sign
                MOVLT   ip,#0                   ;No lower than 0
                CMP     ip,#88                  ;Greater than 88?
                MOVGT   ip,#88                  ;Yes, make it same size

                ; --- Ensure value is 4-bits wide whilst returning in R0 ---
                AND     a1, a3, #0x0F

                ; --- Update the users state, and return ---
                STMIA   a2,{ip,lr}              ; Store index/previous val for next time

				RETURN "v1-v2","","",""	; return (rlist, sp, lr, no condition)

                LTORG


;============================================================================
; --- adpcm_decode ---
;============================================================================
;
; Arguments:    a1 (r0) == input sample (4-bit ADPCM delta)
;               a2 (r1) == pointer to 8 byte state block:
;
; Returns:      a1 (r0) == output sample (16-bit linear PCM)

; C varient:    adpcm_decode(int indata, adpcm_state state);
;
; Notes:        The state block should be clear on the first call.
;============================================================================

                EXPORT  adpcm_decode
adpcm_decode    ROUT

                ; Free up a few scratch registers: v1,v2,lr 
                ; Registers already available    : a3,a4,ip
                STMFD   sp!,{v1-v2, lr}

                LDMIA   a2,{a3,ip}              ; Load index/Previous val
                ADR     v1,stepSizeTable        ; Point to the step size table
                LDR     v1,[v1,a3, LSL #2]      ; Load the step size

                ; Get the delta value
                AND     a4,a1,#&7               ; Get the magnitude (we'll check
                                                ; the sign later...

                ; --- Find the new index value ---

                SUBS    v2,a4,#3
                MOVLE   v2,#-1
                MOVGT   v2,v2,LSL #1
                ADDS    a3,a3,v2                ;Add on the index value

                MOVLT   a3,#0                   ;Ensure that it is >= 0
                CMP     a3,#88                  ;Greater than 88?
                MOVGT   a3,#88                  ;Not any more

                ; --- Compute difference and new predicted value ---
                ;
                ; Computes 'vpdiff = (delta+0.5)*step/4

                MOV     v2,v1,LSR #3

                ORRS    a4,a4,a4,LSL #30
                ADDCS   v2,v2,v1                ;Yes, add step
                ADDMI   v2,v2,v1,LSR #1         ;Yes, add step>>1
                TST     a4,#1                   ;Is bit 0 set?
                ADDNE   v2,v2,v1,LSR #2         ;Yes, add step>>2

                TST     a1, #0x8                ;Was the sign -ve?
                SUBNE   ip,ip,v2                ;Yes -- subtract vpdiff
                ADDEQ   ip,ip,v2                ;No -- add it on then

                ; --- Clamp the output value ---

                MOV     v1,#&8000               ;Clamp to this value
                CMP     ip,v1                   ;Is it out of range?
                SUBGE   ip,v1,#1                ;Yes, MAX it
                CMN     ip,v1                   ;Out of range other way?
                RSBLE   ip,v1,#1                ;Yes, then clamp...

                ; --- Update the step value ---

                ADR     v1,stepSizeTable        ;Point to the step size table
                LDR     v1,[v1,a3,LSL #2]       ;Load the new step size

                ; --- If output is required to be in A-law/u-law format, as  ---
                ; --- opposed to 16-bit linear, then should add a conversion ---
                ; --- routine/macro here.                                    ---


                ; --- Place the decoded sample in r0 ---
                MOV     a1, ip

                STMIA   a2,{a3,ip}              ; Store index/previous val for next time

				RETURN "v1-v2","","",""	; return (rlist, sp, lr, no condition)

                LTORG

;============================================================================

                ; --- Define the state block layout ---

                ^       0
state_index     #       4
state_prevValue #       4


                ; --- The lookup table ---
                ; --- Note: for those desperate to reduce code size, this table
                ; ---       could be represented by 16-bit words, instead of
                ; ---       32-bit words (use DCW instead of DCD). The code would 
                ; ---       have to be changed slightly, and performance would be 
                ; ---       slightly hurt on early ARM processors. 

stepSizeTable   DCD     7, 8, 9, 10, 11, 12, 13, 14, 16, 17
                DCD     19, 21, 23, 25, 28, 31, 34, 37, 41, 45
                DCD     50, 55, 60, 66, 73, 80, 88, 97, 107, 118
                DCD     130, 143, 157, 173, 190, 209, 230, 253, 279, 307
                DCD     337, 371, 408, 449, 494, 544, 598, 658, 724, 796
                DCD     876,963,1060,1166,1282,1411,1552,1707,1878,2066
                DCD     2272,2499,2749,3024,3327,3660,4026,4428,4871,5358
                DCD     5894,6484,7132,7845,8630,9493,10442,11487,12635,13899
                DCD     15289,16818,18500,20350,22385,24623,27086,29794,32767

                END

