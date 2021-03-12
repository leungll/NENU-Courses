    AREA InChannel, CODE, READONLY

    ENTRY

    MOV  r1,#3           ; Number of words to read
    LDR  r2, =indata     ; Address to store data read
pollin
    MRC  p14,0,r0,c0,c0  ; Read control register
    TST  r0, #1
    BEQ  pollin          ; If R bit clear then loop
read
    MRC  p14,0,r3,c1,c0  ; read word into r3
    STR  r3,[r2],#4      ; Store to memory and update pointer
    SUBS r1,r1,#1        ; Update counter
    BNE  pollin          ; Loop if more words to read

    MOV  r0, #0x18       ; Angel_SWIreason_ReportException
    LDR  r1, =0x20026    ; ADP_Stopped_ApplicationExit
    SWI  0x123456        ; ARM semihosting SWI

    AREA Storage, DATA, READWRITE
indata
    DCB "Duffmessage#"
    END

