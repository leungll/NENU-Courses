        AREA ThumbSub, CODE, READONLY   ; Name this block of code
        ENTRY                           ; Mark first instruction to execute
        CODE32                          ; Subsequent instructions are ARM 
header
        ADR     r0, start + 1           ; Processor starts in ARM state, 
        BX      r0                      ; so small ARM code header used 
                                        ; to call Thumb main program.

        CODE16                          ; Subsequent instructions are Thumb. 
start
        MOV     r0, #10                 ; Set up parameters
        MOV     r1, #3
        BL      doadd                   ; Call subroutine

stop
        MOV     r0, #0x18               ; angel_SWIreason_ReportException
        LDR     r1, =0x20026            ; ADP_Stopped_ApplicationExit
        SWI     0xAB                    ; Thumb semihosting SWI 

doadd
        ADD     r0, r0, r1              ; Subroutine code
        MOV     pc, lr                  ; Return from subroutine.

        END                             ; Mark end of file

