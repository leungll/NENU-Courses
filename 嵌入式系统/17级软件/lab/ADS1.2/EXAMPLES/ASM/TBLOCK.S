        AREA Tblock, CODE, READONLY     ; name this block of code

num     EQU     20                      ; Set number of words to be copied

        ENTRY                           ; mark first instruction to execute
        CODE32                          ; Subsequent instructions are ARM header
        MOV     sp, #0x400              ; set up user_mode stack pointer (r13)
        ADR     r0, start + 1           ; Processor starts in ARM state, 
        BX      r0                      ; so small ARM code header used 
                                        ; to call Thumb main program.
        CODE16                          ; Subsequent instructions are Thumb. 

start
        LDR     r0, =src                ; r0 = pointer to source block
        LDR     r1, =dst                ; r1 = pointer to destination block
        MOV     r2, #num                ; r2 = number of words to copy

blockcopy       
        LSR     r3,r2, #2               ; number of four word multiples
        BEQ     copywords               ; less than four words to move ?

        PUSH    {r4-r7}                 ; save some working registers
quadcopy
        LDMIA   r0!, {r4-r7}            ; load 4 words from the source
        STMIA   r1!, {r4-r7}            ; and put them at the destination
        SUB     r3, #1                  ; decrement the counter
        BNE     quadcopy                ; ... copy more

        POP     {r4-r7}                 ; don't need these now - restore originals

copywords
        MOV     r3, #3                  ; bottom two bits represent number...
        AND     r2, r3                  ; ...of odd words left to copy
        BEQ     stop                    ; No words left to copy ?
wordcopy
        LDMIA   r0!, {r3}               ; a word from the source
        STMIA   r1!, {r3}               ; store a word to the destination
        SUB     r2, #1                  ; decrement the counter
        BNE     wordcopy                ; ... copy more

stop
        MOV     r0, #0x18               ; angel_SWIreason_ReportException
        LDR     r1, =0x20026            ; ADP_Stopped_ApplicationExit
        SWI     0xAB                    ; Thumb semihosting SWI


        AREA BlockData, DATA, READWRITE

src     DCD     1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst     DCD     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

        END

