;;  Copyright ARM Ltd 2001. All rights reserved.
;;
;;  This code initializes the Integrator Core Module Core Clock and Bus Clock 
;;  for the following cores:
;;  ARM740T
;;  ARM720T
;;  ARM920T
;;  ARM940T  

        AREA   CMclocks, CODE, READONLY     ; name this block of code

cm_base EQU    0x10000000
cm_osc  EQU    0x10000008
cm_lock EQU    0x10000014

        EXPORT Clock_Speed
Clock_Speed
;;
;; Enters with core clock value in MHz in R0 and core bus value in MHz in R1
;; Certain inappropriate values will cause incorrect operation
;;
        SUB     r0,r0,#8                    ; correction for MHz
        AND     r0,r0,#0xFF                 ; ensure byte value
;               
        MOV     r1,r1,LSL #1                ; multiply by 2 (see manuals)
        SUB     r1,r1,#0x8                  ; and sub to correct for MHz
        AND     r1,r1,#0xFF
        ORR     r0,r0,r1,LSL #12
;
;    
        LDR     r2,=cm_base                 ; read CM base value
        LDR     r1,[r2,#8]                  ; read CM_OSC
;
;         
        BIC     r1,r1,#0x0FF                ; clear bottom byte r1
        BIC     r1,r1,#0x700                ; clear bits 10:8 for clock divider                        
        ORR     r1,r1,#0x100                ; ensure default clock divide value for divide by 2                     
;
;                                                
        BIC     r1,r1,#0x0FF000             ; clear bits 19:12 r1
        BIC     r1,r1,#0x700000             ; clear bits 22:20 for clock divider
        ORR     r1,r1,#0x100000             ; ensure default clock divide value 
        
        ORR     r1,r1,r0                    ; write in new clock values
;                
        MOV     r0,#0xA000
        ORR     r0,r0, #0x5F                ; build 0xA05F in r0
        STR     r0,[r2,#0x14]               ; write to unlock CM_LOCK
        STR     r1,[r2,#8]                  ; write value back
        STR     r1,[r2,#0x14]               ; write in any value to relock CM_LOCK
 
        MOV     pc,lr
                    
        END

