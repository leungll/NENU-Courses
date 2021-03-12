        AREA Loadcon, CODE, READONLY
        ENTRY                           ; Mark first instruction to execute

start
        BL      func1                   ; Branch to first subroutine
        BL      func2                   ; Branch to second subroutine

stop
        MOV     r0, #0x18               ; angel_SWIreason_ReportException
        LDR     r1, =0x20026            ; ADP_Stopped_ApplicationExit
        SWI     0x123456                ; ARM semihosting SWI
        
func1
        LDR     r0, =42                 ; => MOV R0, #42
        LDR     r1, =0x55555555         ; => LDR R1, [PC, #offset to
                                        ; Literal Pool 1]
        LDR     r2, =0xFFFFFFFF         ; => MVN R2, #0
        MOV     pc, lr

        LTORG                           ; Literal Pool 1 contains 
                                        ; literal &55555555
func2
        LDR     r3, =0x55555555         ; => LDR R3, [PC, #offset to
                                        ; Literal Pool 1]
        ; LDR r4, =0x66666666           ; If this is uncommented it
                                        ; fails, because Literal Pool 2
                                        ; is out of reach
        MOV     pc, lr

LargeTable
        SPACE   4200                    ; Clears a 4200 byte area of memory, 
                                        ; starting at the current location,
                                        ; to zero.

        END                             ; Literal Pool 2 is empty

