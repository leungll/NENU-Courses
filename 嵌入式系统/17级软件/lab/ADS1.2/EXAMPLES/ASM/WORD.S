        AREA Word, CODE, READONLY       ; name this block of code

num     EQU     20              ; Set number of words to be copied

        ENTRY                   ; mark the first instruction to call

start
        LDR     r0, =src        ; r0 = pointer to source block
        LDR     r1, =dst        ; r1 = pointer to destination block
        MOV     r2, #num        ; r2 = number of words to copy
        
wordcopy
        LDR     r3, [r0], #4    ; a word from the source
        STR     r3, [r1], #4    ; store a word to the destination
        SUBS    r2, r2, #1      ; decrement the counter
        BNE     wordcopy        ; ... copy more

stop
        MOV     r0, #0x18       ; angel_SWIreason_ReportException
        LDR     r1, =0x20026    ; ADP_Stopped_ApplicationExit
        SWI     0x123456        ; ARM semihosting SWI

        AREA BlockData, DATA, READWRITE

src     DCD     1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst     DCD     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

        END

