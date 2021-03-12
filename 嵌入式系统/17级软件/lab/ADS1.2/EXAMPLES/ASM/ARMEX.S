        AREA ARMex, CODE, READONLY  ; name this block of code
        ENTRY                       ; mark first instruction
                                    ; to execute
start
        MOV     r0, #10             ; Set up parameters
        MOV     r1, #3
        ADD     r0, r0, r1          ; r0 = r0 + r1

stop
        MOV     r0, #0x18           ; angel_SWIreason_ReportException
        LDR     r1, =0x20026        ; ADP_Stopped_ApplicationExit
        SWI     0x123456            ; ARM semihosting SWI

        END                         ; Mark end of file
