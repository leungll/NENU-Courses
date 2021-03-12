;;  Copyright ARM Ltd 2001. All rights reserved.
;;
;;  This code provides basic initialization for an ARM740T including:  
;;  
;;  - creation of memory protection regions
;;  - enabling the unified caches and write buffer
;;  - enabling Memory Protection Unit
;;
;;  This code must be run from a privileged mode

        AREA   INIT740, CODE, READONLY      ; name this block of code

        ENTRY

        EXPORT Cache_Init

Cache_Init

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean
;
;
;       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
;       BIC     r0, r0, #0x1                ; clear bit 0 
;       MCR     p15, 0, r0, c1, c0, 0       ; write value back

;       MOV     r0,#0                       ; disable any other regions 
;       MCR     p15, 0, r0, c6, c1, 0
;       MCR     p15, 0, r0, c6, c2, 0
;       MCR     p15, 0, r0, c6, c3, 0
;       MCR     p15, 0, r0, c6, c4, 0
;       MCR     p15, 0, r0, c6, c5, 0
;       MCR     p15, 0, r0, c6, c6, 0
;       MCR     p15, 0, r0, c6, c7, 0  

;

; Region 0: Background: Base = 0x0, Size = 4Gb, NCNB, No access
; Region 1: SRAM: Base = 0x0, Size = 0x4000, WB, Full access
; Region 2: FLASH: Base = 0x24000000, Size = 0x02000000, WB, Full access
; Region 3: Peripherals: Base = 0x10000000, Size = 0x10000000, NCNB, Full access

; Set up region 0 and enable
        MOV     r0,#2_111111
        MCR     p15, 0, r0, c6, c0, 0       ; region 0

; Set up region 1 and enable
        MOV     r0,#2_100011
        MCR     p15, 0, r0, c6, c1, 0       ; region 1

; Set up region 2 and enable
        LDR     r0,=2_110001+0x24000000
        MCR     p15, 0, r0, c6, c2, 0       ; region 2

; Set up region 3 and enable
        LDR     r0,=2_110111 + 0x10000000
        MCR     p15, 0, r0, c6, c3, 0       ; region 3


; Set up cacheable/bufferable attributes
        MOV     r0, #2_0110
        MCR     p15, 0, r0, c2, c0, 0       ; cacheable
        MCR     p15, 0, r0, c3, c0, 0       ; bufferable


; Set up access permissions
        MOV     r0, #2_11111100
        MCR     p15, 0, r0, c5, c0, 0       ; access permissions

;
; set global core configurations 
;
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        
        ORR     r0, r0, #(0x1 <<2)          ; enable Cache        
        ORR     r0, r0, #0x1                ; enable MPU

;
; additional configuration options      
;        
;       ORR     r0, r0, #(0x1 <<13)         ; enable Hi Vectors
;       ORR     r0, r0, #(0x1 <<7)          ; enable Big Endian


        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1

        MOV     pc,lr                       ; return

        END

