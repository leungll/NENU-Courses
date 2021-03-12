;;  Copyright ARM Ltd 2001. All rights reserved.
;;
;;  This code provides basic initialization for an ARM940T including:  
;;  
;;  - creation of memory protection regions
;;  - enabling the Instruction and Data caches and Write buffer
;;  - setting clocking mode and enabling Memory Protection Unit
;;
;;  This code must be run from a privileged mode

        AREA   INIT940, CODE, READONLY      ; name this block of code

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
;       MCR     p15, 0, r0, c6, c1, 1
;       MCR     p15, 0, r0, c6, c2, 0
;       MCR     p15, 0, r0, c6, c2, 1 
;       MCR     p15, 0, r0, c6, c3, 0
;       MCR     p15, 0, r0, c6, c3, 1 
;       MCR     p15, 0, r0, c6, c4, 0
;       MCR     p15, 0, r0, c6, c4, 1 
;       MCR     p15, 0, r0, c6, c5, 0
;       MCR     p15, 0, r0, c6, c5, 1 
;       MCR     p15, 0, r0, c6, c6, 0
;       MCR     p15, 0, r0, c6, c6, 1 
;       MCR     p15, 0, r0, c6, c7, 0  
;       MCR     p15, 0, r0, c6, c7, 1  
;

; Data region 0: Background: Base = 0x0, Size = 4Gb, NCNB, No access
; Data region 1: SRAM: Base = 0x0, Size = 0x4000, WB, Full access
; Data region 2: FLASH: Base = 0x24000000, Size = 0x02000000, WB, Full access
; Data region 3: Peripherals: Base = 0x10000000, Size = 0x10000000, NCNB, Full access

; Inst region 0: Background: Base = 0x0, Size = 4Gb, Not cached, No access
; Inst region 1: SRAM: Base = 0x0, Size = 0x4000, Cached, Full access
; Inst region 2: FLASH: Base = 0x24000000, Size = 0x02000000, Cached, Full access



; Set up region 0 and enable
        MOV     r0,#2_111111
        MCR     p15, 0, r0, c6, c0, 0        ; data region 0
        MCR     p15, 0, r0, c6, c0, 1        ; inst region 0 See 940 TRM 2-13

; Set up region 1 and enable
        MOV     r0,#2_100011
        MCR     p15, 0, r0, c6, c1, 0        ; data region 1
        MCR     p15, 0, r0, c6, c1, 1        ; inst region 1 See 940 TRM 2-13

; Set up region 2 and enable
        LDR     r0,=2_110001+0x24000000
        MCR     p15, 0, r0, c6, c2, 0        ; data region 2
        MCR     p15, 0, r0, c6, c2, 1        ; inst region 2 See 940 TRM 2-13

; Set up region 3 and enable
        LDR     r0,=2_110111 + 0x10000000
        MCR     p15, 0, r0, c6, c3, 0        ; data region 3


; Set up cacheable/bufferable attributes
        MOV     r0, #2_0110
        MCR     p15, 0, r0, c2, c0, 0        ; data cacheable
        MCR     p15, 0, r0, c3, c0, 0        ; data bufferable 
        MCR     p15, 0, r0, c2, c0, 1        ; instr cacheable 

; Set up access permissions
        MOV     r0, #2_11111100
        MCR     p15, 0, r0, c5, c0, 0        ; data access permissions
        MCR     p15, 0, r0, c5, c0, 1        ; instr access permissions


;
; set global core configurations 
;
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache        
        ORR     r0, r0, #(2_11 <<30)        ; enable asynchronous clocking mode
        ORR     r0, r0, #0x1                ; enable MPU

;
; additional configuration options      
;        
;       ORR     r0, r0, #(0x1 <<13)         ; enable Hi Vectors
;       ORR     r0, r0, #(0x1 <<7)          ; enable Big Endian


        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1

        MOV   pc,lr                         ; return

        END

