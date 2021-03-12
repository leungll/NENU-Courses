        AREA adrlabel, CODE, READONLY
        ENTRY                           ; Mark first instruction to execute
Start
        BL func                         ; Branch to subroutine

stop
        MOV     r0, #0x18               ; angel_SWIreason_ReportException
        LDR     r1, =0x20026            ; ADP_Stopped_ApplicationExit
        SWI     0x123456                ; ARM semihosting SWI

        LTORG                           ; Create a literal pool

func
        ADR     r0, Start               ; => SUB r0, PC, #offset to Start
        ADR     r1, DataArea            ; => ADD r1, PC, #offset to DataArea
        ; ADR r2, DataArea+4300         ; This would fail as the offset
                                        ; cannot be expressed by operand2 
                                        ; of an ADD
        ADRL    r2, DataArea+4300       ; => ADD r2, PC, #offset1
                                        ;    ADD r2, r2, #offset2

        MOV     pc, lr                  ; Return

DataArea SPACE  8000                    ; Clears a 8000 byte area of memory, 
                                        ; starting at the current location,
                                        ; to zero.
      END

