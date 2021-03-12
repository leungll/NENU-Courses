;
; Copyright (C) ARM Limited 1999. All rights reserved.
;

        AREA KernelVeneers, CODE, READONLY

        GBLL    Is_ARM
Is_ARM  SETL    {CODESIZE}=32

        MACRO
        Veneer  $name
        LCLS    subname
        LCLS    supname
subname SETS    "$name"
supname SETS    "|$$Super$$$$" :CC: subname :CC: "|"
subname SETS    "|$$Sub$$$$" :CC: subname :CC: "|"
        EXPORT  $subname
        IMPORT  $supname
        IF Is_ARM
            CODE32
$subname    LDR     pc, =$supname
            LTORG
        ELSE
            CODE16
$subname    BX      pc
            CODE32
            LDR     ip, {PC}+8
            BX      ip
            DCD     $supname+1
        ENDIF
        MEND

        Veneer kernel_Register
        Veneer kernel_Call
        Veneer  _printf

        END

