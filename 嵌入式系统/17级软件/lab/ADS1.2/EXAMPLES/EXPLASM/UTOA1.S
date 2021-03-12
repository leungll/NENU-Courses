; This demonstrates recursion in ARM assembler.
; this version does not perform stack checking.
;
; Converting a number to a string can be expressed using a divide-and-
; conquer algorithm:
; <string> = "<number/10><number%10>"

  AREA |utoa$$code|, CODE, READONLY

  EXPORT dtoa
  EXPORT utoa

  IMPORT udiv10

dtoa
; converts signed word to string
; a1 = char *buffer
; a2 = signed int number
; on exit:
; a1 = char *end_of_string

  CMP    a2, #0
  RSBMI  a2, a2, #0;              make a2 positive
  MOVMI  ip, #'-'
  STRMIB ip, [ a1 ], #1  ; add minus sign to buffer

; *** intentional drop-through to utoa ***

utoa
; recursive routine to convert unsigned word to string
; on entry:
; a1 = char *buffer
; a2 = unsigned int number
; on exit:
; a1 = char *end_of_string      ; character after last digit
; all other registers preserved

  STMFD  sp!, {v1, v2, lr}      ; save 2 variable registers and
                                ; the return address

  MOV    v1, a1                 ; keep char *buffer for later
  MOV    v2, a2                 ; and keep the number for later
  MOV    a1, a2
  BL     udiv10                 ; on return, the quotient is in a1

  SUB    v2, v2, a1, LSL #3     ; number - 8*quotient
  SUB    v2, v2, a1, LSL #1     ;        - 2*quotient = remainder
      
  CMP    a1, #0                 ; quotient non-zero?
  MOVNE  a2, a1                 ; quotient to a2...
  MOV    a1, v1                 ; buffer pointer unconditionally to a1
  BLNE   utoa                   ; conditional recursive call to utoa

  ADD    v2, v2, #'0'           ; final digit
  STRB   v2, [a1], #1           ; store digit at end of buffer

  LDMFD  sp!, {v1, v2, pc}      ; restore and return

  END

