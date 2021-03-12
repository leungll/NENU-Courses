;;; Copyright ARM Ltd 1998. All rights reserved.

    AREA SWI_Area, CODE, READONLY

    EXPORT SWI_Handler
    IMPORT C_SWI_Handler

T_bit EQU 0x20

SWI_Handler

    STMFD   sp!, {r0-r3, r12, lr}  ; Store registers
    MOV     r1, sp                 ; Set pointer to parameters
    MRS     r0, spsr               ; Get spsr
    STMFD   sp!, {r0}              ; Store spsr onto stack
    TST     r0, #T_bit             ; Occurred in Thumb state?
    LDRNEH  r0, [lr,#-2]           ; Yes: Load halfword and...
    BICNE   r0, r0, #0xFF00        ; ...extract comment field
    LDREQ   r0, [lr,#-4]           ; No: Load word and...
    BICEQ   r0, r0, #0xFF000000    ; ...extract comment field

        ; r0 now contains SWI number
        ; r1 now contains pointer to stacked registers

    BL      C_SWI_Handler          ; Call main part of handler
    LDMFD   sp!, {r0}              ; Get spsr from stack
    MSR     spsr_cf, r0            ; Restore spsr
    LDMFD   sp!, {r0-r3, r12, pc}^ ; Restore registers and return

    END

