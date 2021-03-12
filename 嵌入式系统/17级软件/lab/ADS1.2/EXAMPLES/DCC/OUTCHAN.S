    AREA OutChannel, CODE, READONLY

    ENTRY
                
    MOV  r1,#3           ; Number of words to send
    ADR  r2, outdata     ; Address of data to send
pollout
    MRC  p14,0,r0,c0,c0  ; Read control register
    TST  r0, #2
    BNE  pollout         ; if W set, register still full
write
    LDR  r3,[r2],#4      ; Read word from outdata
                         ; into r3 and update the pointer
    MCR  p14,0,r3,c1,c0  ; Write word from r3
    SUBS r1,r1,#1        ; Update counter
    BNE  pollout         ; Loop if more words to be written

    MOV  r0, #0x18       ; Angel_SWIreason_ReportException
    LDR  r1, =0x20026    ; ADP_Stopped_ApplicationExit
    SWI  0x123456        ; ARM semihosting SWI

outdata
    DCB "Hello there!"
    END

