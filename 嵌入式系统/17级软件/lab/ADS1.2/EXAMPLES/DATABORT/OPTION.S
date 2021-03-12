;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Header file for the data abort veneer
; =====================================
;
; This is an example of an options-setting file for
; the data abort veneer.
;

                GBLS    VeneerEntry
VeneerEntry     SETS    "To_Be_Filled_In_1"

                GBLL    BaseUpdated
BaseUpdated     SETL    {TRUE}

                GBLL    BaseRestored
BaseRestored    SETL    {TRUE}

                GBLS    HandlerCallStd
HandlerCallStd  SETS    "APCS_MACRO"

                GBLS    HandlerName
HandlerName     SETS    "HandlerMacro"

                MACRO
                HandlerMacro
                CMP     R0,#DABORT_ERROR_NONE
                MOVEQ   R0,#DABORT_RETVAL_TONEXT
                MOVNE   R0,#DABORT_RETVAL_UNDEF
                MEND

                GBLS    ReturnUndef
ReturnUndef     SETS    "0x00000004"

                GBLS    ReturnToNext
ReturnToNext    SETS    "To_Be_Filled_In_2"

                GBLS    AbortModelVar
AbortModelVar   SETS    "To_Be_Filled_In_3"

                GBLS    AbortModelInit
AbortModelInit  SETS    "To_Be_Filled_In_4"

                INCLUDE dabort.s

                END
