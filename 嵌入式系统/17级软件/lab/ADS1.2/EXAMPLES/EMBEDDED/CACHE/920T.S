;;  Copyright ARM Ltd 2001. All rights reserved.
;;
;;  This code provides basic initialization for an ARM920T including:  
;;  
;;  - creation of a 16KB level 1 page table in physical memory (this will probably 
;;    need to be changed for your target)
;;  - enabling the Instruction and Data caches and Write buffer
;;  - setting clocking mode and enabling MMU
;;
;;  This code must be run from a privileged mode

        AREA   INIT920, CODE, READONLY      ; name this block of code

ttb_first_level EQU     0x00004000          ; base address for level 1 translation table

        ENTRY

        EXPORT Cache_Init

Cache_Init

; If MMU/MPU enabled - disable (useful for ARMulator tests)
; possibly also need to consider data cache clean and TLB flush
;
;       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
;       BIC     r0, r0, #0x1                ; clear bit 0 
;       MCR     p15, 0, r0, c1, c0, 0       ; write value back
;
;
; The ARM920T can run with its instruction cache enabled but
; the MMU disabled. The code below performs this initialization
;
;       MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
;       ORR     r0, r0, #0xc0000000         ; set asynchronous clocking mode  
;       ORR     r0, r0, #0x1000             ; enable I cache
;       MCR     p15, 0, r0, c1, c0, 0       ; write back r0 into CP15 register 1

init_ttb
                
        LDR     r0,=ttb_first_level         ; set start of Translation Table base (16k Boundary)
        MCR     p15, 0, r0, c2, c0, 0       ; write to CP15 register 2
; 
;
; Create translation table for flat mapping
; Top 12 bits of VA is pointer into table
; Create 4096 entries from 000xxxxx to fffxxxxx
;
;
        LDR     r1,=0xfff                   ; loop counter
        MOV     r2,#2_110000000000          ; set access permissions (AP) for full access SVC/USR (11:10)
        ORR     r2,r2,#2_000111100000       ; set for domain 15 (8:5)
        ORR     r2,r2,#2_000000010000       ; must be 1 (4)
        ORR     r2,r2,#2_000000000000       ; set non cachable non bufferable (CB) (3:2)
        ORR     r2,r2,#2_000000000010       ; set for 1Mb section (1:0)
;
init_ttb_1
        ORR     r3,r2,r1,lsl#20             ; use loop counter to create individual table entries
        STR     r3,[r0,r1,lsl#2]            ; str r3 at TTB base + loopcount*4
        SUBS    r1,r1,#1                    ; decrement loop counter
        BPL     init_ttb_1
;
        ORR     r3,r3,#2_1100               ; set cachable and bufferable attributes for section 0 (3:2)
        STR     r3,[r0]                     ; ie lower 1MB - this will set cache to Write Back mode
;
;init_domains
        MOV     r0,#(2_01 << 30)            ; must define behaviour for domain 15 (31:30), set client
        MCR     p15, 0, r0, c3, c0, 0       ; write to CP15 register 5

;
; set global core configurations
;
        MRC     p15, 0, r0, c1, c0, 0       ; read CP15 register 1 into r0
        
        ORR     r0, r0, #(0x1 <<12)         ; enable I Cache
        ORR     r0, r0, #(0x1 <<2)          ; enable D Cache
        ORR     r0, r0, #(2_11 <<30)        ; enable asynchronous clocking mode
        ORR     r0, r0, #0x1                ; enable MMU

;
; additional configuration options      
;        
;       ORR     r0, r0, #(0x1 <<14)         ; enable Round Robin cache replacement
;       ORR     r0, r0, #(0x1 <<13)         ; enable Hi Vectors
;       ORR     r0, r0, #(0x1 <<1)          ; enable data address alignment checking

        MCR     p15, 0, r0, c1, c0, 0       ; write cp15 register 1

        MOV   pc,lr                         ; return

        END

