        AREA    SCopy, CODE, READONLY

        EXPORT strcopy
strcopy                 
        ; r0 points to destination string
        ; r1 points to source string
        LDRB    r2, [r1],#1     ; load byte and update address
        STRB    r2, [r0],#1     ; store byte and update address;
        CMP     r2, #0          ; check for zero terminator
        BNE     strcopy         ; keep going if not
        MOV     pc,lr           ; Return

        END

