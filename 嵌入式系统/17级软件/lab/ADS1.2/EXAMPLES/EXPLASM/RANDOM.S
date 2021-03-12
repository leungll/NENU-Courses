; Random number generator
;
; This uses a 33-bit feedback shift register to generate a pseudo-randomly
; ordered sequence of numbers which repeats in a cycle of length 2^33 - 1
; NOTE: randomseed should not be set to 0, otherwise a zero will be generated
; continuously (not particularly random!).
;
; This is a good application of direct ARM assembler, because the 33-bit
; shift register can be implemented using RRX (which uses reg + carry).
; An ANSI C version would be less efficient as the compiler would not use RRX.

        AREA    |Random$$code|, CODE, READONLY

        EXPORT  randomnumber

randomnumber
; on exit:
;       a1 = low 32-bits of pseudo-random number
;       a2 = high bit (if you want to know it)
        LDR     ip, |seedpointer|
        LDMIA   ip, {a1, a2}
        TST     a2, a2, LSR#1           ; to bit into carry
        MOVS    a3, a1, RRX             ; 33-bit rotate right
        ADC     a2, a2, a2              ; carry into LSB of a2
        EOR     a3, a3, a1, LSL#12      ; (involved!)
        EOR     a1, a3, a3, LSR#20      ; (similarly involved!)
        STMIA   ip, {a1, a2}

        MOV     pc, lr

|seedpointer|
        DCD     seed


        AREA    |Random$$data|, DATA

        EXPORT  seed
seed
        DCD     &55555555
        DCD     &55555555

        END
