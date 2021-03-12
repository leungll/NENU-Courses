        AREA    StrCopy, CODE, READONLY
        ENTRY                   ; mark the first instruction to call

start
        LDR     r1, =srcstr     ; pointer to first string
        LDR     r0, =dststr     ; pointer to second string

        BL      strcopy         ; call subroutine to do copy

stop
        MOV     r0, #0x18       ; angel_SWIreason_ReportException
        LDR     r1, =0x20026    ; ADP_Stopped_ApplicationExit
        SWI     0x123456        ; ARM semihosting SWI


strcopy                 
        LDRB    r2, [r1],#1     ; load byte and update address
        STRB    r2, [r0],#1     ; store byte and update address;
        CMP     r2, #0          ; check for zero terminator
        BNE     strcopy         ; keep going if not
        MOV     pc,lr           ; Return


        AREA    Strings, DATA, READWRITE
srcstr  DCB "First string - source",0
dststr  DCB "Second string - destination",0

        END

