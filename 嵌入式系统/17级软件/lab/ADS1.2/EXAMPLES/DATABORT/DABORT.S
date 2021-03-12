;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Data abort veneer: Assembler source file
; Copyright 1997 Advanced RISC Machines Limited. All rights reserved.
;
; Feb 2000 - fixed 'PCOffset_Undef' "wrong address" problem

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Definitions that do not depend on assembly-time options
; =======================================================
;
; Error- and warning-related: the following are used as the first
; parameter to the INFO directive.

WARNING         EQU     0
ERROR           EQU     4

; Verbatim vertical bars in source text can cause problems in symbolic
; manipulations, due to their interactions with $-introduced symbol
; substitutions. To avoid this problem, we define a string variable
; here containing a vertical bar, which we will use instead of a
; literal vertical bar in most places.

                GBLS    VBar
VBar            SETS    "|"

; The following definition is to get around some rather over-
; enthusiastic assembler error messages. (For maximum future-proofing,
; it is set to "_fsxc", but earlier assemblers objected to this)

                GBLS    all_fields
all_fields      SETS    "_fsxc"

; ARM register numbers declared in such a way as to make code of the
; form R$ArithVar work.

R00000000       RN      R0
R00000001       RN      R1
R00000002       RN      R2
R00000003       RN      R3
R00000004       RN      R4
R00000005       RN      R5
R00000006       RN      R6
R00000007       RN      R7
R00000008       RN      R8
R00000009       RN      R9
R0000000A       RN      R10
R0000000B       RN      R11
R0000000C       RN      R12
R0000000D       RN      R13
R0000000E       RN      R14
R0000000F       RN      R15

; ARM PSR bits

I_bit           EQU     0x80
T_bit           EQU     0x20

; ARM processor mode numbers

Mode_User       EQU     0x10
Mode_Supervisor EQU     0x13
Mode_Abort      EQU     0x17
Mode_Undef      EQU     0x1B
Mode_System     EQU     0x1F

Mode_FullMask   EQU     0x1F    ; Mask to isolate full mode number
Mode_MainMask   EQU     0x0F    ; Mask to isolate non-26/32 mode no.

; ARM PC offsets.

PCOffset_DAbort EQU     8       ; R14_abort - address(aborting instr)
PCOffset_UndefA EQU     4       ; R14_undef - address(undefined instr) ARM
PCOffset_UndefT EQU     2       ; R14_undef - address(undefined instr) Thumb

; ARM instruction bits. The "M bit" is one that conveniently
; distinguishes multiple transfers from single transfers for the
; purpose of the "early aborts" model and other purposes.

ARM_M_bit       EQU     0x08000000      ;Multiple vs. single transfer
ARM_P_bit       EQU     0x01000000      ;Pre- vs. post-indexing
ARM_U_bit       EQU     0x00800000      ;Down vs. up
ARM_S_bit       EQU     0x00400000      ;S bit in LDM/STM
ARM_W_bit       EQU     0x00200000      ;Writeback vs. no writeback
ARM_L_bit       EQU     0x00100000      ;Load vs. store

; ARM instruction fields.

ARM_Rn_pos      EQU     16
ARM_Rn_mask     EQU     0xF :SHL: ARM_Rn_pos

ARM_Rd_pos      EQU     12
ARM_Rd_mask     EQU     0xF :SHL: ARM_Rd_pos

ARM_Rm_pos      EQU     0
ARM_Rm_mask     EQU     0xF :SHL: ARM_Rm_pos

; Thumb instruction fields

Thumb_unusual_reg_pos   EQU     8
Thumb_unusual_reg_mask  EQU     0x7 :SHL: Thumb_unusual_reg_pos

Thumb_usual_Rm_pos      EQU     6
Thumb_usual_Rm_mask     EQU     0x7 :SHL: Thumb_usual_Rm_pos

Thumb_usual_Rn_pos      EQU     3
Thumb_usual_Rn_mask     EQU     0x7 :SHL: Thumb_usual_Rn_pos

Thumb_usual_Rd_pos      EQU     0
Thumb_usual_Rd_mask     EQU     0x7 :SHL: Thumb_usual_Rd_pos

Thumb_Imm5_pos          EQU     6
Thumb_Imm5_mask         EQU     0x1F :SHL: Thumb_Imm5_pos

Thumb_Imm8_pos          EQU     0
Thumb_Imm8_mask         EQU     0xFF :SHL: Thumb_Imm8_pos

Thumb_L_bit             EQU     0x0800

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Processing of assembly-time options
; ===================================
;
; The following code supplies default values for assembly-time
; options, checks for illegal or meaningless combinations, etc.
;
; * 'VeneerEntry' is mandatory, and will be treated as a label. We
;    reprocess it at this stage to ensure that it is surrounded by
;    vertical bars. (These clean-ups and similar ones later are *not*
;    intended to catch all possible syntactic errors - just to allow
;    the symbol to be specified with or without the vertical bars and
;    to catch the most obvious syntactic errors.)

        [ :LNOT::DEF:VeneerEntry
                GBLS    VeneerEntry
VeneerEntry     SETS    ""
        ]

        [ VeneerEntry = ""
                INFO    ERROR, \
                        "'VeneerEntry' has not been defined."
        ]

        [ ((VeneerEntry:LEFT:1) = VBar) \
          :LEOR: ((VeneerEntry:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'VeneerEntry'"
        ]
        [ (VeneerEntry:LEFT:1) <> VBar
VeneerEntry     SETS    VBar:CC:VeneerEntry:CC:VBar
        ]

; * 'AreaName' is optional, defaulting to "DataAbortVeneerCode". (Done
;    via an empty string to also catch cases where it has been defined
;    as the empty string.) It gets the usual vertical bar
;    reprocessing.

        [ :LNOT::DEF:AreaName
                GBLS    AreaName
AreaName        SETS    ""
        ]

        [ AreaName = ""
AreaName        SETS    "DataAbortVeneerCode"
        ]

        [ ((AreaName:LEFT:1) = VBar) \
          :LEOR: ((AreaName:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'AreaName'"
        ]
        [ (AreaName:LEFT:1) <> VBar
AreaName        SETS    VBar:CC:AreaName:CC:VBar
        ]

; * 'BaseUpdated', 'BaseRestored' and 'EarlyAbort' are each optional,
;   defaulting to {FALSE}. However, at least one of them must be
;   {TRUE}, and we're interested in how many are {TRUE} for the
;   purpose of determining whether we are supporting multiple abort
;   models.

        [ :LNOT::DEF:BaseUpdated
                GBLL    BaseUpdated
BaseUpdated     SETL    {FALSE}
        ]

        [ :LNOT::DEF:BaseRestored
                GBLL    BaseRestored
BaseRestored    SETL    {FALSE}
        ]

        [ :LNOT::DEF:EarlyAbort
                GBLL    EarlyAbort
EarlyAbort      SETL    {FALSE}
        ]

                GBLA    AbortModelCount
AbortModelCount SETA    0

        [ BaseUpdated
AbortModelCount SETA    AbortModelCount+1
        ]

        [ BaseRestored
AbortModelCount SETA    AbortModelCount+1
        ]

        [ EarlyAbort
AbortModelCount SETA    AbortModelCount+1
        ]

        [ AbortModelCount = 0
                INFO    ERROR, \
                        "Must specify at least one abort model."
        ]

; * 'AbortModelVar' and 'AbortModelInit' can both default to the empty
;   string regardless of the number of abort models supported. (In the
;   case of 'AbortModelVar', this empty string will later generate an
;   error if more than 1 abort model is specified.)
;     If more than one abort model is specified, 'AbortModelVar' is
;   mandatory.

        [ :LNOT::DEF:AbortModelVar
                GBLS    AbortModelVar
AbortModelVar   SETS    ""
        ]

        [ :LNOT::DEF:AbortModelInit
                GBLS    AbortModelInit
AbortModelInit  SETS    ""
        ]

        [ (AbortModelCount > 1) :LAND: (AbortModelVar = "")
                INFO    ERROR, \
                        "'AbortModelVar' has not been defined."
        ]

        [ AbortModelVar <> ""
          [ ((AbortModelVar:LEFT:1) = VBar) \
            :LEOR: ((AbortModelVar:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'AbortModelVar'."
          ]
          [ (AbortModelVar:LEFT:1) <> VBar
AbortModelVar   SETS    VBar:CC:AbortModelVar:CC:VBar
          ]
        ]

        [ AbortModelInit <> ""
          [ AbortModelVar = ""
                INFO    ERROR, \
                        "'AbortModelInit' without 'AbortModelVar'."
          ]

          [ ((AbortModelInit:LEFT:1) = VBar) \
            :LEOR: ((AbortModelInit:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'AbortModelInit'."
          ]
          [ (AbortModelInit:LEFT:1) <> VBar
AbortModelInit  SETS    VBar:CC:AbortModelInit:CC:VBar
          ]
        ]

; * 'HandlerCallStd' defaults to "APCS_NOSWST".

        [ :LNOT::DEF:HandlerCallStd
                GBLS    HandlerCallStd
HandlerCallStd  SETS    ""
        ]

        [ HandlerCallStd = ""
HandlerCallStd  SETS    "APCS_NOSWST"
        ]

                GBLL    CallStdKnown
CallStdKnown    SETL    {FALSE}

                GBLL    CallStdHasLabel
CallStdHasLabel SETL    {FALSE}

        [ HandlerCallStd = "APCS_NOSWST"
CallStdKnown    SETL    {TRUE}
CallStdHasLabel SETL    {TRUE}
        ]

        [ HandlerCallStd = "APCS_SWST"
CallStdKnown    SETL    {TRUE}
CallStdHasLabel SETL    {TRUE}
        ]

        [ HandlerCallStd = "APCS_MACRO"
CallStdKnown    SETL    {TRUE}
        ]

        [ :LNOT:CallStdKnown
                INFO    ERROR, \
                        "Unknown 'HandlerCallStd' requested"
        ]

; * 'HandlerName' is mandatory, and undergoes the usual vertical bar
;   clean-ups if it is to be treated as a label.

        [ :LNOT::DEF:HandlerName
                GBLS    HandlerName
HandlerName     SETS    ""
        ]

        [ HandlerName = ""
                INFO    ERROR, \
                        "'HandlerName' has not been defined."
        ]

        [ CallStdHasLabel
          [ ((HandlerName:LEFT:1) = VBar) \
            :LEOR: ((HandlerName:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'HandlerName'"
          ]
          [ (HandlerName:LEFT:1) <> VBar
HandlerName     SETS    VBar:CC:HandlerName:CC:VBar
          ]
        ]

; * 'HandlerCallMode' defaults to "Supervisor" or "Abort", depending
;   on the procedure calling standard used, and has three legal values
;   - which we also translate here to mode numbers.

        [ :LNOT::DEF:HandlerCallMode
                GBLS    HandlerCallMode
HandlerCallMode SETS    ""
        ]

        [ HandlerCallMode = ""
          [ HandlerCallStd = "APCS_MACRO"
HandlerCallMode SETS    "Abort"
          |
HandlerCallMode SETS    "Supervisor"
          ]
        ]

                GBLL    CallModeKnown
CallModeKnown   SETL    {FALSE}

        [ HandlerCallMode = "Supervisor"
CallModeKnown   SETL    {TRUE}
Mode_Callee     EQU     Mode_Supervisor
        ]

        [ HandlerCallMode = "System"
CallModeKnown   SETL    {TRUE}
Mode_Callee     EQU     Mode_System
        ]

        [ HandlerCallMode = "Abort"
CallModeKnown   SETL    {TRUE}
Mode_Callee     EQU     Mode_Abort
        ]

        [ :LNOT:CallModeKnown
                INFO    ERROR, \
                        "Unknown 'HandlerCallMode' requested"
        ]

; * The stack limit variable specified by "HandlerSL" is mandatory for
;   the "APCS_SWST" procedure calling standard, unnecessary and unused
;   otherwise.

        [ :LNOT::DEF:HandlerSL
                GBLS    HandlerSL
HandlerSL       SETS    ""
        ]

        [ HandlerCallStd = "APCS_SWST"

          [ HandlerSL = ""
                INFO    ERROR, \
                        "'HandlerSL' has not been specified."
          ]

          [ ((HandlerSL:LEFT:1) = VBar) \
            :LEOR: ((HandlerSL:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'HandlerSL'"
          ]
          [ (HandlerSL:LEFT:1) <> VBar
HandlerSL       SETS    VBar:CC:HandlerSL:CC:VBar
          ]

        |

          [ HandlerSL <> ""
                INFO    WARNING, \
                        "'HandlerSL' will not be used."
          ]

        ]

; * The parameter-passing options 'PassSPSR', 'PassInstrAddr',
;   'PassRegDumpAddr' and 'PassXferAddr' all default to {FALSE}.

        [ :LNOT::DEF:PassSPSR
                GBLL    PassSPSR
PassSPSR        SETL    {FALSE}
        ]

        [ :LNOT::DEF:PassInstrAddr
                GBLL    PassInstrAddr
PassInstrAddr   SETL    {FALSE}
        ]

        [ :LNOT::DEF:PassRegDumpAddr
                GBLL    PassRegDumpAddr
PassRegDumpAddr SETL    {FALSE}
        ]

        [ :LNOT::DEF:PassXferAddr
                GBLL    PassXferAddr
PassXferAddr    SETL    {FALSE}
        ]

; * The 'allowed return values' options all default to not allowing
;   the return value, but some must be specified, including at least
;   one that is legitimate when an error occurs.

        [ :LNOT::DEF:ReturnNormal
                GBLL    ReturnNormal
ReturnNormal    SETL    {FALSE}
        ]

        [ :LNOT::DEF:ReturnUndef
                GBLS    ReturnUndef
ReturnUndef     SETS    ""
        ]

        [ (ReturnUndef <> "") :LAND: ((ReturnUndef:LEFT:2) <> "0x")
          [ ((ReturnUndef:LEFT:1) = VBar) \
            :LEOR: ((ReturnUndef:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'ReturnUndef'"
          ]
          [ (ReturnUndef:LEFT:1) <> VBar
ReturnUndef     SETS    VBar:CC:ReturnUndef:CC:VBar
          ]
        ]

        [ :LNOT::DEF:ReturnToNext
                GBLS    ReturnToNext
ReturnToNext    SETS    ""
        ]

        [ ReturnToNext <> ""
          [ ((ReturnToNext:LEFT:1) = VBar) \
            :LEOR: ((ReturnToNext:RIGHT:1) = VBar)
                INFO    ERROR, \
                        "Vertical bar error in 'ReturnToNext'"
          ]
          [ (ReturnToNext:LEFT:1) <> VBar
ReturnToNext    SETS    VBar:CC:ReturnToNext:CC:VBar
          ]
        ]

        [ :LNOT::DEF:ReturnAddress
                GBLL    ReturnAddress
ReturnAddress   SETL    {FALSE}
        ]

        [ (ReturnUndef = "") :LAND: (:LNOT:ReturnAddress)
                INFO    ERROR, \
                        "No legitimate return value for errors."
        ]

; * 'SuptThumb' defaults to {TRUE}.

        [ :LNOT::DEF:SuptThumb
                GBLL    SuptThumb
SuptThumb       SETL    {TRUE}
        ]

; * 'StrictErrors' defaults to {TRUE}.

        [ :LNOT::DEF:StrictErrors
                GBLL    StrictErrors
StrictErrors    SETL    {TRUE}
        ]

; * The defined-but-not-implemented options 'SuptBaseEqIndex' and
;   'SuptLoadBaseWB' get their default values, with errors/warnings if
;   the as-yet-unsupported option is chosen.

        [ :LNOT::DEF:SuptBaseEqIndex
                GBLL    SuptBaseEqIndex
SuptBaseEqIndex SETL    {FALSE}
        ]

        [ SuptBaseEqIndex
                INFO    ERROR, \
                        "'SuptBaseEqIndex' option not yet implemented"
        ]

        [ :LNOT::DEF:SuptLoadBaseWB
                GBLL    SuptLoadBaseWB
SuptLoadBaseWB  SETL    {FALSE}
        ]

        [ SuptLoadBaseWB
                INFO    ERROR, \
                        "'SuptLoadBaseWB' option not yet implemented"
        ]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Definitions that depend on assembly-time options
; ================================================
;
; The following macro does the final stages of the call to the
; OS-specific handler.

                MACRO
$label          HandlerInternalMacro
                ALIGN
$label
        [ HandlerCallStd = "APCS_MACRO"
                $HandlerName
        |
          [ HandlerCallStd = "APCS_SWST"
                LDR     R10, =$HandlerSL
          ]
                IMPORT  $HandlerName
                BL      $HandlerName
        ]
                MEND

; Specific return values allowed from OS-specific handler. These
; definitions are made dependent on the relevant assembly-time option
; in order to catch coding errors.

        [ ReturnNormal
DABORT_RETVAL_NORMAL    EQU     0x0
        ]

        [ ReturnUndef <> ""
DABORT_RETVAL_UNDEF     EQU     0x4
        ]

        [ ReturnToNext <> ""
DABORT_RETVAL_TONEXT    EQU     0x10
        ]

; Error codes.

DABORT_ERROR_BAD_REQUEST        EQU     -1
DABORT_ERROR_NONE               EQU     0
DABORT_ERROR_BASEEQINDEX_PRE    EQU     1
DABORT_ERROR_BASEEQINDEX_POST   EQU     2
DABORT_ERROR_R15_WB             EQU     3
DABORT_ERROR_BASE_R15           EQU     4
DABORT_ERROR_INDEX_R15          EQU     5
DABORT_ERROR_LOAD_WB            EQU     6
DABORT_ERROR_LDMSTM_EMPTY       EQU     7
DABORT_ERROR_USERBANK_WB        EQU     8
DABORT_ERROR_BAD_INSTR          EQU     9

; Abort models.

        [ BaseRestored
DABORT_MODEL_BASERESTORED       EQU     0
        ]

        [ EarlyAbort
DABORT_MODEL_EARLYABORT         EQU     1
        ]

        [ BaseUpdated
DABORT_MODEL_BASEUPDATED        EQU     3
        ]

        [ AbortModelInit <> ""
DABORT_MODEL_INITIALISATION     EQU     0x40000000      ; And higher
        ]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Start of generated code
; =======================
;
; Start by declaring the area.

                AREA    $AreaName, CODE, REL

; The main entry point
; ====================

$VeneerEntry
                EXPORT  $VeneerEntry

; First thing the code must do is set up its register dump. This has
; to be done carefully, to ensure that the correct mode's registers
; are stored. We start by reserving the right amount of space and
; dumping the unbanked registers, to give ourselves some space to work
; in. We also get the return link and SPSR into callee-saved registers
; at this point, adjusting the return link to point to the aborting
; instruction in the process.

                SUB     R13, R13, #15*4
                STMIA   R13, {R0-R7}
                SUB     R4, R14, #PCOffset_DAbort
                MRS     R5, SPSR

; Now do the rest of the registers. This usually involves switching to
; the mode concerned (or strictly speaking, to its 32-bit equivalent),
; dumping the registers and switching back. However, if the mode
; concerned is a user mode, we must instead use a "user bank" STM, to
; avoid getting trapped in user mode.

                ADD     R0, R13, #8*4   ; Place to dump registers

                ANDS    R1, R5, #Mode_MainMask
                ASSERT  (Mode_User:AND:Mode_MainMask) = 0
                STMEQIA R0, {R8-R14}^
                BEQ     RegsDumped

                MRS     R2, CPSR
                BIC     R3, R2, #Mode_MainMask
                ORR     R1, R3, R1
                MSR     CPSR$all_fields, R1
                STMIA   R0, {R8-R14}
                MSR     CPSR$all_fields, R2

RegsDumped

; *** Live register values at this point are:
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R13: Stack pointer (pointing to register dump)
;
; Find out what abort model we're using (if relevant) and initialise
; the error code.

        [ AbortModelVar <> ""
                IMPORT  $AbortModelVar
                LDR     R6, =$AbortModelVar
                LDR     R8, [R6]
          [ AbortModelInit <> ""
                CMP     R8, #DABORT_MODEL_INITIALISATION
                BHS     Initialisation_Handler
          ]
        ]

                MOV     R6, #DABORT_ERROR_NONE

; We need to obtain and analyse the aborting instruction in any of the
; following circumstances:
;
; * If "StrictErrors" is set.
;
; * If we're expected to pass the instruction's transfer address as a
;   parameter to the OS-specific handler.
;
; * If we're dealing with anything other than the Base Restored Abort
;   Model.

        [ StrictErrors \
          :LOR: PassXferAddr \
          :LOR: (:LNOT:BaseRestored) \
          :LOR: (AbortModelCount > 1)

          [ (:LNOT:StrictErrors) \
            :LAND: (:LNOT:PassXferAddr) \
            :LAND: BaseRestored

                ASSERT  AbortModelVar <> ""     ; So R8 was loaded
                CMP     R8, #DABORT_MODEL_BASERESTORED
                BEQ     CallOSHandlerWithError

          ]

          [ SuptThumb
; Test for whether the instruction is a Thumb instruction, and branch
; off to separate code to handle it if so.

                TST     R5, #T_bit
                BNE     ThumbInstruction
          ]

ARMInstruction

; ARM instruction analysis
; ========================
;
; Get the instruction. We can use a normal LDR instruction to do this,
; not an LDRT, even if we were invoked from user mode, because:
;
; * The fact that a data abort occurred on the offending instruction,
;   not a prefetch abort, indicates that the instruction was
;   accessible from user mode.
;
; * User mode programs cannot fake a data abort vector entry in order
;   to create a security loophole. (They can branch to location 0x10,
;   but cannot also get into a privileged mode unless they take the
;   data abort trap.)

                LDR     R0, [R4]

; *** Live register values at this point are:
;     R0:  Aborting instruction
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; Now start analysing the instruction. The objective of this stage is
; to end up with:
;
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;          L bit (bit 20) indicating whether a load or a store, at least
;            when writeback is involved or there is a potential "user bank"
;            LDM.
;     R1:  Number of base register, still in instruction position.
;     R2:  Offset value.
;     R3:  Number of destination register, still in instruction
;          position (for all but LDM/STM/LDC/STC).
;
; In many cases, R0 will be the unchanged instruction; however, it
; does get changed in some circumstances to "standardise" the meanings
; of the bits.
;
; R1 and R3 are particularly simple, since the base register field is
; in the same position for all ARM load/store instructions, and the
; destination field is in the same position for all single load
; instructions.

                AND     R1, R0, #ARM_Rn_mask
                AND     R3, R0, #ARM_Rd_mask

; Now split according to the major class of the instruction - i.e.
; bits 27:25.

                AND     R2, R0, #(0x7:SHL:25)
                ADD     PC, PC, R2, LSR #23

                NOP                             ;Branch table padding

                B       ARM_Odds_And_Ends       ;SWP, LDRH, etc.
                B       ARM_Should_Not_Happen   ;(Data processing)
                B       ARM_LDR_STR_Immed
                B       ARM_LDR_STR_Reg
                B       ARM_LDM_STM
                B       ARM_Should_Not_Happen   ;(B/BL)
                B       ARM_LDC_STC
ARM_Should_Not_Happen                           ;(CDP/MRC/MCR/SWI)
                MOV     R6, #DABORT_ERROR_BAD_INSTR
                B       CallOSHandlerWithError

; Analysis of ARM SWP/SWPB/LDRH/LDRSB/LDRSH/STRH instructions
; -----------------------------------------------------------
;
; Start by distinguishing SWP instructions from the rest.

ARM_Odds_And_Ends

                TST     R0, #0x3 :SHL: 5
                BNE     ARM_LDRH_etc

; Analysis of ARM SWP/SWPB instructions
; -------------------------------------
;
; This will behave like a pre-indexed instruction with an offset of 0
; and no writeback - i.e. P=1, U=don't care, W=0. SWP/SWPB
; instructions should already be like this, and it is an error if they
; are not.

ARM_SWP

                AND     R7, R0, #ARM_P_bit + ARM_W_bit
                CMP     R7, #ARM_P_bit
                BNE     ARM_Should_Not_Happen

; A base register of R15 is also an error.

                CMP     R1, #0xF :SHL: ARM_Rn_pos
                MOVEQ   R6, #DABORT_ERROR_BASE_R15
                BEQ     CallOSHandlerWithError

; Set an offset of 0 and continue.

                MOV     R2, #0          ;Set offset of 0
                B       RegisterAdjust

; Analysis of ARM LDRH/LDRSB/LDRSH/STRH instructions
; --------------------------------------------------
;
; First thing is to force writeback to be set if post-indexed; then
; split into immediate and register forms.

ARM_LDRH_etc

                TST     R0, #ARM_P_bit
                ORREQ   R0, R0, #ARM_W_bit

                TST     R0, #ARM_S_bit
                BEQ     ARM_LDRH_etc_Reg

ARM_LDRH_etc_Immed

; We just have to generate the correct offset.

                AND     R2, R0, #0xF
                AND     R7, R0, #0xF00
                ORR     R2, R2, R7, LSR #4
                B       RegisterAdjust

ARM_LDRH_etc_Reg

; There are a number of errors to detect:
;
; * An index register of R15.

                AND     R2, R0, #ARM_Rm_mask
                CMP     R2, #0xF :SHL: ARM_Rm_pos
                MOVEQ   R6, #DABORT_ERROR_INDEX_R15
                BEQ     CallOSHandlerWithError

; * Base register = index register, with writeback.

                CMP     R2, R1, LSR #(ARM_Rn_pos - ARM_Rm_pos)
                BNE     ARM_LDRH_etc_Reg_OK
                TST     R0, #ARM_W_bit
                BNE     ARM_LDR_STR_Reg_NotOK   ;To shared error code

ARM_LDRH_etc_Reg_OK

; Get the index register value and go to common code.

                LDR     R2, [R13, R2, LSL #(2 - ARM_Rm_pos)]
                B       RegisterAdjust

; Analysis of ARM LDC/STC instructions
; ------------------------------------
;
; Offset comes direct from the instruction. M, P, U, W and L bits are
; already right.

ARM_LDC_STC
                AND     R2, R0, #0xFF
                MOV     R2, R2, LSL #2
                B       RegisterAdjust2 ;Avoid "load and w/back" check

; Analysis of ARM LDM/STM instructions
; ------------------------------------
;
; Offset is implied by number of set bits in register mask; M, U, W
; and L bits are set correctly. P bit cannot be set in a manner that
; corresponds properly to the other instructions, so this case doesn't
; share all of the standard "RegisterAdjust" code.

ARM_LDM_STM

; Need to check for some error conditions:
;
; * Base register of R15.

                CMP     R1, #0xF :SHL: ARM_Rn_pos
                MOVEQ   R6, #DABORT_ERROR_BASE_R15
                BEQ     CallOSHandlerWithError

; * Register mask empty. (Calculate register mask at the same time and
;   put it into top end of R3.)

                MOVS    R3, R0, LSL #16         ;Isolate register mask
                MOVEQ   R6, #DABORT_ERROR_LDMSTM_EMPTY
                BEQ     CallOSHandlerWithError

; * Writeback and load of same register.

                TST     R0, #ARM_W_bit          ;Writeback?
                TSTNE   R0, #ARM_L_bit          ;And a load?
                MOVNE   R7, R1, LSR #ARM_Rn_pos
                MOVNE   R7, R3, LSR R7
                TSTNE   R7, #0x10000            ;And base in list?
                MOVNE   R6, #DABORT_ERROR_LOAD_WB
                BNE     CallOSHandlerWithError

; * Writeback in user bank form.

                TST     R0, #ARM_W_bit          ;Writeback?
                TSTNE   R0, #ARM_S_bit          ;Potentially user bank?
                BEQ     ARM_LDM_STM_OK
                TST     R3, #0x10000 :SHL: 15   ;Is it loading R15?
                TSTNE   R0, #ARM_L_bit          ;And a load?
                MOVEQ   R6, #DABORT_ERROR_USERBANK_WB
                BEQ     CallOSHandlerWithError

ARM_LDM_STM_OK

; *** Live register values at this point are:
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;     R1:  Number of base register, still in instruction position.
;     R3:  Register list mask (only the number of set bits matters).
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; Calculate offset from mask, by repeatedly isolating and removing the
; least significant bit in the mask until it is zero. Note we know the
; mask is non-zero.

                MOV     R2, #0

ARM_LDM_STM_OffsetLoop
                ADD     R2, R2, #4
                RSB     R7, R3, #0      ;Unequal above lowest 1, equal
                                        ; at lowest 1 and below
                BICS    R3, R3, R7      ;So this clears lowest 1
                BNE     ARM_LDM_STM_OffsetLoop

        [ PassXferAddr

; We need to know what the difference between the transfer address and
; the (possibly corrected) base address is. This is given by the
; following table:
;
;   P bit  U bit  Addressing mode  Transfer address - base address
;   --------------------------------------------------------------
;     0      0         DA           4 - R2
;     0      1         IA           0
;     1      0         DB           -R2
;     1      1         IB           4
;
; The following code puts the appropriate value in R3.

                TST     R0, #ARM_P_bit
                MOVEQ   R3, #4
                MOVNE   R3, #0
                TST     R0, #ARM_U_bit
                SUBEQ   R3, R3, R2
                RSBNE   R3, R3, #4

        ]

                B       RegisterAdjust3

; Analysis of ARM LDR/STR instructions with register offset
; ---------------------------------------------------------
;
; Offset is Rm, shifted appropriately; force writeback if
; post-indexed. M, P, U and L bits are already right.

ARM_LDR_STR_Reg

                TST     R0, #ARM_P_bit
                ORREQ   R0, R0, #ARM_W_bit
                AND     R2, R0, #ARM_Rm_mask

; Need to check for some error conditions:
;
; * An invalid instruction.

                TST     R0, #0x00000010
                BNE     ARM_Should_Not_Happen

; * An index register of R15.

                CMP     R2, #0xF :SHL: ARM_Rm_pos
                MOVEQ   R6, #DABORT_ERROR_INDEX_R15
                BEQ     CallOSHandlerWithError

; * Base register = index register, with writeback.

                CMP     R2, R1, LSR #(ARM_Rn_pos - ARM_Rm_pos)
                BNE     ARM_LDR_STR_Reg_OK
                TST     R0, #ARM_W_bit
                BNE     ARM_LDR_STR_Reg_NotOK

ARM_LDR_STR_Reg_OK

; Get the index register value.

                LDR     R2, [R13, R2, LSL #(2 - ARM_Rm_pos)]

; Now we need to apply the shift. Split according to the shift type.

                AND     R7, R0, #3 :SHL: 5
                ADD     PC, PC, R7, LSR #3

                NOP                             ;Branch table padding

                B       ARM_LDR_STR_Reg_LSL
                B       ARM_LDR_STR_Reg_LSR
                B       ARM_LDR_STR_Reg_ASR
ARM_LDR_STR_Reg_ROR
                ANDS    R7, R0, #0x1F :SHL: 7
                MOVNE   R7, R7, LSR #7          ;If amount non-zero,
                MOVNE   R2, R2, ROR R7          ; ROR correctly
                BNE     RegisterAdjust

; We've got an RRX shift. This has got to be silly, but it's just as
; easy to handle it correctly as to produce an error.

                MOVS    R7, R5, LSL #3          ;Caller's C -> C
                MOV     R2, R2, RRX
                B       RegisterAdjust

ARM_LDR_STR_Reg_ASR
                ANDS    R7, R0, #0x1F :SHL: 7
                MOVNE   R7, R7, LSR #7          ;If amount non-zero,
                MOVNE   R2, R2, ASR R7          ; ASR correctly
                MOVEQ   R2, R2, ASR #32         ;Else ASR by 32
                B       RegisterAdjust

ARM_LDR_STR_Reg_LSR
                ANDS    R7, R0, #0x1F :SHL: 7
                MOVNE   R7, R7, LSR #7          ;If amount non-zero,
                MOVNE   R2, R2, LSR R7          ; LSR correctly
                MOVEQ   R2, R2, LSR #32         ;Else LSR by 32
                B       RegisterAdjust

ARM_LDR_STR_Reg_LSL
                AND     R7, R0, #0x1F :SHL: 7
                MOV     R7, R7, LSR #7
                MOV     R2, R2, LSL R7
                B       RegisterAdjust

ARM_LDR_STR_Reg_NotOK
                TST     R0, #ARM_P_bit
                MOVEQ   R6, #DABORT_ERROR_BASEEQINDEX_POST
                MOVNE   R6, #DABORT_ERROR_BASEEQINDEX_PRE
                B       CallOSHandlerWithError

; Analysis of ARM LDR/STR instructions with immediate offset
; ----------------------------------------------------------
;
; Offset comes direct from the instruction; force writeback if
; post-indexed. M, P, U and L bits are already right.

ARM_LDR_STR_Immed
                MOV     R2, R0, LSL #20
                MOV     R2, R2, LSR #20
                TST     R0, #ARM_P_bit
                ORREQ   R0, R0, #ARM_W_bit

; Fall through to RegisterAdjust if following code isn't assembled.

          [ SuptThumb

                B       RegisterAdjust

                LTORG

ThumbInstruction

; Thumb instruction analysis
; ==========================
;
; Get the instruction. We can use a normal LDRH instruction to do this,
; rather than faking an "LDRHT" from an LDRT, for the same reasons that we
; can use LDR rather than LDRT to fetch an ARM instruction - see "ARM
; instruction analysis" above.

                LDRH    R0, [R4]

; *** Live register values at this point are:
;     R0:  Aborting instruction
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; Now start analysing the instruction. The objective of this stage is
; to end up with the same register contents as the ARM instruction analysis,
; i.e.:
;
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;          [ L bit (bit 20) indicating whether a load or a store, at least
;            when writeback is involved or there is a potential "user bank"
;            LDM. Not needed in general for Thumb instructions - the
;            writebacks for LDM/POP/PUSH/STM will be dealt with specially. ]
;     R1:  Number of base register, in ARM instruction position.
;     R2:  Offset value.
;     R3:  Number of destination register, in ARM instruction position
;          (for all but LDM/POP/PUSH/STM).
;
; Unlike the ARM instruction case, we will have to do a lot of "faking" to
; get things right. We do at least have the advantage that all the relevant
; bits of R0 are known to be zero at this point.
;
; Set R1 and R3 from the most usual positions of the base and destination
; registers in Thumb instructions.

                AND     R1, R0, #Thumb_usual_Rn_mask
                MOV     R1, R1, LSL #(ARM_Rn_pos - Thumb_usual_Rn_pos)
                AND     R3, R0, #Thumb_usual_Rd_mask
                MOV     R3, R3, LSL #(ARM_Rd_pos - Thumb_usual_Rd_pos)

; Now split according to the major class of the instruction - i.e.
; bits 15:12.

                AND     R2, R0, #(0xF:SHL:12)
                ADD     PC, PC, R2, LSR #10

                NOP                             ;Branch table padding

                B       ARM_Should_Not_Happen   ;(Shift imm.)
                B       ARM_Should_Not_Happen   ;(Shift imm., add/sub)
                B       ARM_Should_Not_Happen   ;(Add/sub/compare/move
                B       ARM_Should_Not_Happen   ; immediate)
                B       Thumb_PCbased           ;(Also data processing)
                B       Thumb_RegOffset
                B       Thumb_LDR_STR
                B       Thumb_LDRB_STRB
                B       Thumb_LDRH_STRH
                B       Thumb_SPbased
                B       ARM_Should_Not_Happen   ;(ADR from PC/SP)
                B       Thumb_PUSH_POP          ;(Also SP adjust/Undef)
                B       Thumb_LDM_STM
                B       ARM_Should_Not_Happen   ;(Bcc/SWI/Undef)
                B       ARM_Should_Not_Happen   ;(Uncond. branch/Undef)
                B       ARM_Should_Not_Happen   ;(BL high/low)

; Analysis of Thumb PC-based PUSH/POP instructions
; ------------------------------------------------

Thumb_PUSH_POP

; Checks for errors:
;
; * Instruction not in fact PUSH/POP:

                TST     R0, #0x0400
                BEQ     ARM_Should_Not_Happen

; * Empty register mask - register mask gets calculated at the same
;   time and put in R3. Note that only the number of set bits in the
;   register mask matters, so we don't have to shift the LR/PC bit to
;   the correct position.

                BICS    R3, R0, #0xFE00
                MOVEQ   R6, #DABORT_ERROR_LDMSTM_EMPTY
                BEQ     CallOSHandlerWithError

; We will branch into the ARM LDM/STM code at the point where all
; error checks have been performed. Things we still need to do are:
;
; * Set the M, P, U and W bits correctly in R0 (1/0/1/1 for POP,
;   1/1/0/1 for PUSH).
; * Set R1 to the correct base register number (R13).

                BIC     R3, R0, #0xFE00
                MOV     R1, #(0xD :SHL: ARM_Rn_pos)
                TST     R0, #Thumb_L_bit
                ORREQ   R0, R0, #ARM_M_bit + ARM_P_bit + ARM_W_bit
                ORRNE   R0, R0, #ARM_M_bit + ARM_U_bit + ARM_W_bit
                B       ARM_LDM_STM_OK

; Analysis of Thumb PC-based LDM/STM instructions
; -----------------------------------------------

Thumb_LDM_STM

; Checks for errors:

; * Empty register mask - register mask gets calculated at the same
;   time and put in R3.

                BICS    R3, R0, #0xFF00
                MOVEQ   R6, #DABORT_ERROR_LDMSTM_EMPTY
                BEQ     CallOSHandlerWithError

; * Writeback and load of the same register. We've definitely got
;   writeback, so it's just a question of whether the base register
;   appears in the register list. First, get the base register number
;   into R1 and put it into ARM base register position (where it is
;   needed later anyway). Then check whether it appears in the
;   register list.

                AND     R1, R0, #Thumb_unusual_reg_mask
                MOV     R1, R1, LSL #(ARM_Rn_pos - Thumb_unusual_reg_pos)

                MOV     R7, R1, LSR #ARM_Rn_pos
                MOV     R7, R3, LSR R7
                TST     R7, #1
                MOVNE   R6, #DABORT_ERROR_LOAD_WB
                BNE     CallOSHandlerWithError

; We will branch into the ARM LDM/STM code at the point where all
; error checks have been performed. The only thing we still need to do
; is set the M, P, U and W bits correctly in R0 (1/0/1/1 for both LDM
; and STM).

                ORR     R0, R0, #ARM_M_bit + ARM_U_bit + ARM_W_bit
                B       ARM_LDM_STM_OK

; Analysis of Thumb LDRx/STRx with register offset
; ------------------------------------------------
;
; R0 bits should be M=0, P=1, U=1, W=0. R1 and R3 are right; R2 value
; should be obtained from the Thumb instruction's Rm field. There are
; no problems with an index register of R15 or with writeback with
; index = base, since the Thumb instruction doesn't permit a "high"
; index register or base register writeback.

Thumb_RegOffset
                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                AND     R2, R0, #Thumb_usual_Rm_mask
                LDR     R2, [R13, R2, LSR #(Thumb_usual_Rm_pos - 2)]
                B       RegisterAdjust

; Analysis of Thumb SP-based LDR/STR
; ----------------------------------
;
; R0 bits should be M=0, P=1, U=1, W=0. R1 should indicate R13. R3
; should be calculated from the variant Rd position used for this
; instruction. Finally, the offset is extracted from the instruction
; and shifted into "times 4" position.

Thumb_SPbased
                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                MOV     R1, #(0xD :SHL: ARM_Rn_pos)
                AND     R3, R0, #Thumb_unusual_reg_mask
                MOV     R3, R3, LSL #(ARM_Rd_pos - Thumb_unusual_reg_pos)
                AND     R2, R0, #Thumb_Imm8_mask
                MOV     R2, R2, LSL #(2 - Thumb_Imm8_pos)
                B       RegisterAdjust

; Analysis of Thumb PC-based LDR
; ------------------------------

Thumb_PCbased

; Check instruction is right (not the data processing instructions
; with the same major opcode, which look like PC-based STRs).

                TST     R0, #Thumb_L_bit
                BEQ     ARM_Should_Not_Happen

; R0 bits should be M=0, P=1, U=1, W=0. R1 should indicate R15; the
; "RegisterAdjust" code below will apply the appropriate
; Thumb-specific modifications to it. R3 should be calculated from the
; variant Rd position used for this instruction. Finally, the offset
; is extracted from the instruction and shifted into "times 4"
; position.

                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                MOV     R1, #(0xF :SHL: ARM_Rn_pos)
                AND     R3, R0, #Thumb_unusual_reg_mask
                MOV     R3, R3, LSL #(ARM_Rd_pos - Thumb_unusual_reg_pos)
                AND     R2, R0, #Thumb_Imm8_mask
                MOV     R2, R2, LSL #(2 - Thumb_Imm8_pos)
                B       RegisterAdjust

; Analysis of Thumb LDR/STR with immediate offset
; -----------------------------------------------
;
; R1 and R3 values are already correct; R0 bits should be M=0, P=1,
; U=1, W=0; offset needs to be extracted from the instruction and
; shifted into "times 4" position.

Thumb_LDR_STR
                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                AND     R2, R0, #Thumb_Imm5_mask
                MOV     R2, R2, LSR #(Thumb_Imm5_pos - 2)
                B       RegisterAdjust

; Analysis of Thumb LDRB/STRB with immediate offset
; -------------------------------------------------
;
; R1 and R3 values are already correct; R0 bits should be M=0, P=1,
; U=1, W=0; offset needs to be extracted from the instruction and
; shifted into "times 1" position.

Thumb_LDRB_STRB
                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                AND     R2, R0, #Thumb_Imm5_mask
                MOV     R2, R2, LSR #(Thumb_Imm5_pos - 0)
                B       RegisterAdjust

; Analysis of Thumb LDRH/STRH with immediate offset
; -------------------------------------------------
;
; R1 and R3 values are already correct; R0 bits should be M=0, P=1,
; U=1, W=0; offset needs to be extracted from the instruction and
; shifted into "times 2" position.

Thumb_LDRH_STRH
                ORR     R0, R0, #ARM_P_bit + ARM_U_bit
                AND     R2, R0, #Thumb_Imm5_mask
                MOV     R2, R2, LSR #(Thumb_Imm5_pos - 1)

; Fall through to RegisterAdjust.

          ] ; of SuptThumb section

RegisterAdjust

; *** Live register values at this point are:
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;          L bit (bit 20) indicating whether a load or a store, at
;            least when writeback is occurring.
;     R1:  Number of base register, still in ARM instruction position.
;     R2:  Offset value.
;     R3:  Number of destination register, still in ARM instruction
;          position.
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; This code is shared between all instructions except LDM/STMs and
; LDCs/STCs. First, check for the "Load and write back to same
; register" case.

                CMP     R3, R1, LSR #(ARM_Rn_pos - ARM_Rd_pos)
                BNE     RegisterAdjust2
                TST     R0, #ARM_W_bit
                TSTNE   R0, #ARM_L_bit
                MOVNE   R6, #DABORT_ERROR_LOAD_WB
                BNE     CallOSHandlerWithError

RegisterAdjust2

; *** Live register values at this point are:
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;     R1:  Number of base register, still in ARM instruction position.
;     R2:  Offset value.
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; If we're required to produce the transfer address, calculate the
; offset from the base address (after it has been corrected) to the
; transfer address.

          [ PassXferAddr
                TST     R0, #ARM_U_bit
                MOVNE   R3, R2
                RSBEQ   R3, R2, #0
                TST     R0, #ARM_P_bit
                MOVEQ   R3, #0
          ]

RegisterAdjust3

; *** Live register values at this point are:
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          P bit (bit 24) indicating pre- vs. post-indexing.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;     R1:  Number of base register, still in ARM instruction position.
;     R2:  Offset value.
;     R3:  Transfer address - base address (if "PassXferAddr"
;          specified).
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; There is one more error to check for, namely use of a base register
; of R15 with writeback. We will get hold of the base register value
; at the same time, as it happens to be convenient to use the R15 test
; for that purpose as well.

                CMP     R1, #0xF :SHL: ARM_Rn_pos
                LDRNE   R7, [R13, R1, LSR #(ARM_Rn_pos - 2)]
                BNE     RegisterAdjust4

                TST     R0, #ARM_W_bit
                MOVNE   R6, #DABORT_ERROR_R15_WB
                BNE     CallOSHandlerWithError

; Add correct offset to instruction pointer to get the right R15 base
; value. For Thumb, the only PC-based load/store instruction also
; clears bit 1.

                ADD     R7, R4, #8
        [ SuptThumb
                TST     R5, #T_bit
                ADDNE   R7, R4, #4
                BICNE   R7, R7, #2
        ]

RegisterAdjust4

; *** Live register values at this point are:
;     R0:  M bit (bit 27) indicating multiple vs. single transfer.
;          U bit (bit 23) indicating whether indexing is up or down.
;          W bit (bit 21) indicating whether base register writeback
;            is required.
;     R1:  Number of base register, still in ARM instruction position.
;     R2:  Offset value.
;     R3:  Transfer address - base address (if "PassXferAddr"
;          specified).
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R7:  Value of base register
;     R8:  Abort model (if relevant)
;     R13: Stack pointer (pointing to register dump)
;
; We're finally ready to do base register restoration if required. The
; rules here are:
;
; * If we've got just a single abort model, follow its dictates about
;   base register restoration.
;
; * Otherwise, use the appropriate bit of the abort model number in R8.

          [ AbortModelCount = 1
            [ BaseRestored
                ; Fall through (next chunk of code won't be assembled).
            ]
            [ BaseUpdated
                ; Fall through
            ]
            [ EarlyAbort
                TST     R0, #ARM_M_bit
                BEQ     CallOSHandlerNoError
            ]
          |
                TST     R0, #ARM_M_bit
                MOVEQ   R8, R8, LSR #1
                TST     R8, #1
                BEQ     CallOSHandlerNoError
          ]

          [ :LNOT:((AbortModelCount = 1) :LAND: BaseRestored)

; If we get here, we need to restore the base register value
; appropriately, provided it has actually been written back.

                TST     R0, #ARM_W_bit
                BEQ     CallOSHandlerNoError

                TST     R0, #ARM_U_bit
                ADDEQ   R7, R7, R2      ;Add if originally subtracted
                SUBNE   R7, R7, R2      ; and vice versa
                STR     R7, [R13, R1, LSR #(ARM_Rn_pos - 2)]

          ]

CallOSHandlerNoError

          [ PassXferAddr

; Produce transfer address from corrected base address and previously
; calculated difference.

                ADD     R7, R7, R3

          ]

        ] ; of complex condition saying whether to analyse instruction

CallOSHandlerWithError

; OS-specific handler call
; ========================
;
; *** Live register values at this point are:
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R7:  Transfer address (if wanted & relevant; otherwise junk)
;     R13: Stack pointer (pointing to register dump)
;
; Switch into the correct mode (if necessary) - but first we may need
; to put the register dump pointer somewhere safe. R8 is a suitable
; callee-save register.

        [ PassRegDumpAddr :LOR: (HandlerCallMode <> "Abort")
                MOV     R8, R13
        ]

        [ HandlerCallMode <> "Abort"
                MRS     R3, CPSR
                BIC     R3, R3, #Mode_FullMask
                ORR     R3, R3, #Mode_Callee
                MSR     CPSR$all_fields, R3
        ]

; Marshall the arguments required. This uses some rather messy
; conditional assembly, the idea of which is to marshall the arguments
; in reverse order in R0-R3, dumping partial lists to the stack. First
; count the arguments.

                GBLA    ArgCount
ArgCount        SETA    1
        [ PassSPSR
ArgCount        SETA    ArgCount+1
        ]
        [ PassInstrAddr
ArgCount        SETA    ArgCount+1
        ]
        [ PassRegDumpAddr
ArgCount        SETA    ArgCount+1
        ]
        [ PassXferAddr
ArgCount        SETA    ArgCount+1
        ]

; Now ArgVar counts down through the arguments; ArgVar2 determines
; which register each should go to; ArgString contains the arguments
; not yet on the stack, each preceded by a comma (the first comma
; needs stripping before using ArgString in an STMFD instruction.

                GBLA    ArgVar
ArgVar          SETA    ArgCount
                GBLA    ArgVar2
                GBLS    ArgString
ArgString       SETS    ""

        [ PassXferAddr
ArgVar          SETA    ArgVar-1
ArgVar2         SETA    ArgVar :AND: 3
ArgString       SETS    ",R$ArgVar2" :CC: ArgString
                MOV     R$ArgVar2, R7
          [ ArgVar2 = 0 :LAND: ArgVar <> 0
ArgString       SETS    ArgString :RIGHT: (:LEN:ArgString - 1)
                STMFD   R13!,{$ArgString}
ArgString       SETS    ""
          ]
        ]

        [ PassRegDumpAddr
ArgVar          SETA    ArgVar-1
ArgVar2         SETA    ArgVar :AND: 3
ArgString       SETS    ",R$ArgVar2" :CC: ArgString
                MOV     R$ArgVar2, R8
          [ ArgVar2 = 0 :LAND: ArgVar <> 0
ArgString       SETS    ArgString :RIGHT: (:LEN:ArgString - 1)
                STMFD   R13!,{$ArgString}
ArgString       SETS    ""
          ]
        ]

        [ PassInstrAddr
ArgVar          SETA    ArgVar-1
ArgVar2         SETA    ArgVar :AND: 3
ArgString       SETS    ",R$ArgVar2" :CC: ArgString
                MOV     R$ArgVar2, R4
          [ ArgVar2 = 0 :LAND: ArgVar <> 0
ArgString       SETS    ArgString :RIGHT: (:LEN:ArgString - 1)
                STMFD   R13!,{$ArgString}
ArgString       SETS    ""
          ]
        ]

        [ PassSPSR
ArgVar          SETA    ArgVar-1
ArgVar2         SETA    ArgVar :AND: 3
ArgString       SETS    ",R$ArgVar2" :CC: ArgString
                MOV     R$ArgVar2, R5
          [ ArgVar2 = 0 :LAND: ArgVar <> 0
ArgString       SETS    ArgString :RIGHT: (:LEN:ArgString - 1)
                STMFD   R13!,{$ArgString}
ArgString       SETS    ""
          ]
        ]

ArgVar          SETA    ArgVar-1
ArgVar2         SETA    ArgVar :AND: 3
ArgString       SETS    ",R$ArgVar2" :CC: ArgString
                MOV     R$ArgVar2, R6
          [ ArgVar2 = 0 :LAND: ArgVar <> 0
ArgString       SETS    ArgString :RIGHT: (:LEN:ArgString - 1)
                STMFD   R13!,{$ArgString}
ArgString       SETS    ""
          ]

; Check all the above conditional assembly is self-consistent.

                ASSERT ArgVar = 0

; Finally, we're ready to issue the procedure call.
;
; *** Live register values at this point are:
;     R0-R3: Arguments as appropriate
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R7:  Transfer address
;     R8:  R13_abort value (if calling in other than abort mode)
;     R13: Stack pointer (pointing to any arguments over four)

                HandlerInternalMacro

; If we needed to use some stack for the argument list, release it.

        [ ArgCount > 4
                ADD     R13, R13, #(ArgCount-4)*4
        ]

; If we switched modes, restore abort mode and R13_abort.

        [ HandlerCallMode <> "Abort"
                MRS     R3, CPSR
                BIC     R3, R3, #Mode_FullMask
                ORR     R3, R3, #Mode_Abort
                MSR     CPSR$all_fields, R3

                MOV     R13, R8
        ]

; Deal with the OS-specific handler's return value
; ================================================

        [ ReturnNormal

; Code to return and retry the aborting instruction
; -------------------------------------------------
;
; *** Live register values at this point are:
;     R0:  Return value from OS-specific handler
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R13: Stack pointer (pointing to register dump)

                CMP     R0, #DABORT_RETVAL_NORMAL
                BNE     NotReturnNormal

; This return value isn't valid unless there was no error originally.

                CMP     R6, #DABORT_ERROR_NONE
                BNE     ReturnInvalid

; We need to take care about how we return if we're to get all the
; registers right. First thing to do is restore the banked registers -
; this needs the same precautions about user modes as the
; corresponding entry code.

                ADD     R7, R13, #8*4   ; Place to find reg values

                ANDS    R1, R5, #Mode_MainMask
                ASSERT  (Mode_User:AND:Mode_MainMask) = 0
                LDMEQIA R7, {R8-R14}^
                BEQ     RegsRestored_Normal

                MRS     R2, CPSR
                BIC     R3, R2, #Mode_MainMask
                ORR     R1, R3, R1
                MSR     CPSR$all_fields, R1
                LDMIA   R7, {R8-R14}
                MSR     CPSR$all_fields, R2

RegsRestored_Normal

; PC value wanted is the address of the aborting instruction, CPSR
; value wanted is the entry SPSR value.

                STR     R4, [R13, #14*4]
                MSR     SPSR$all_fields, R5

; Now we're ready to restore the rest of the registers and return.

                LDMIA   R13, {R0-R7}
                ADD     R13, R13, #14*4
                LDMIA   R13!, {PC}^

                LTORG

NotReturnNormal

        ]

        [ ReturnUndef <> ""

; Code to fake an undefined instruction trap
; ------------------------------------------
;
; *** Live register values at this point are:
;     R0:  Return value from OS-specific handler
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R13: Stack pointer (pointing to register dump)

                CMP     R0, #DABORT_RETVAL_UNDEF
                BNE     NotReturnUndef

; There are a number of CPSR manipulations in what follows, so get it
; into a register. Also produce a "main mode number blanked" version
; of it.

                MRS     R2, CPSR
                BIC     R3, R2, #Mode_MainMask

; We need to take care about how we return if we're to get all the
; registers right. First thing to do is restore the banked registers -
; this needs the same precautions about user modes as the
; corresponding entry code.

                ADD     R7, R13, #8*4   ; Place to find reg values

                ANDS    R1, R5, #Mode_MainMask
                ASSERT  (Mode_User:AND:Mode_MainMask) = 0
                LDMEQIA R7, {R8-R14}^
                BEQ     RegsRestored_Undef

                ORR     R1, R3, R1
                MSR     CPSR$all_fields, R1
                LDMIA   R7, {R8-R14}

; N.B. No need to shift back to the original mode at this point.

RegsRestored_Undef

; Next, we need to shift over to undefined instruction mode in order
; to get R14_undef and SPSR_undef right, then shift back so that we
; can do the rest of the work on the abort mode stack.

                ORR     R1, R3, #Mode_Undef
                MSR     CPSR$all_fields, R1
                MSR     SPSR$all_fields, R5
                TST     R5, #T_bit
                ADDEQ   R14, R4, #PCOffset_UndefA
                ADDNE   R14, R4, #PCOffset_UndefT
                MSR     CPSR$all_fields, R2

; Now put the CPSR we want to end up with in SPSR_abort, and the PC
; value we want to end up with in the top used word of the stack.

                BIC     R0, R5, #Mode_FullMask + T_bit
                ORR     R0, R0, #Mode_Undef + I_bit
                MSR     SPSR$all_fields, R0

                LDR     R0, =$ReturnUndef
                STR     R0, [R13, #14*4]

; Now we're ready to finish "returning".

                LDMIA   R13, {R0-R7}
                ADD     R13, R13, #14*4
                LDMIA   R13!, {PC}^

                LTORG

NotReturnUndef

        ]

        [ ReturnToNext <> ""

; Code to chain to a second data abort handler
; --------------------------------------------
;
; *** Live register values at this point are:
;     R0:  Return value from OS-specific handler
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R13: Stack pointer (pointing to register dump)

                CMP     R0, #DABORT_RETVAL_TONEXT
                BNE     NotReturnToNext

; This return value isn't valid unless there was no error originally.

                CMP     R6, #DABORT_ERROR_NONE
                BNE     ReturnInvalid

; We need to take care about how we return if we're to get all the
; registers right. First thing to do is restore the banked registers -
; this needs the same precautions about user modes as the
; corresponding entry code.

                ADD     R7, R13, #8*4   ; Place to find reg values

                ANDS    R1, R5, #Mode_MainMask
                ASSERT  (Mode_User:AND:Mode_MainMask) = 0
                LDMEQIA R7, {R8-R14}^
                BEQ     RegsRestored_ToNext

                MRS     R2, CPSR
                BIC     R3, R2, #Mode_MainMask
                ORR     R1, R3, R1
                MSR     CPSR$all_fields, R1
                LDMIA   R7, {R8-R14}
                MSR     CPSR$all_fields, R2

RegsRestored_ToNext

; Restore R14_abort, SPSR_abort and the CPSR to their entry values.

                ADD     R14, R4, #PCOffset_DAbort
                MSR     SPSR$all_fields, R5
                BIC     R0, R5, #Mode_FullMask + T_bit
                ORR     R0, R0, #Mode_Abort + I_bit
                MSR     CPSR$all_fields, R0

; Now put the PC value we want to end up with in the top used word of
; the stack.

                IMPORT  $ReturnToNext
                LDR     R0, =$ReturnToNext
                STR     R0, [R13, #14*4]

; Now we're ready to finish "returning".

                LDMIA   R13, {R0-R7}
                ADD     R13, R13, #14*4
                LDMIA   R13!, {PC}

                LTORG

NotReturnToNext

        ]

        [ ReturnAddress

; Code to transfer to the R0-specified address
; --------------------------------------------
;
; *** Live register values at this point are:
;     R0:  Return value from OS-specific handler
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R13: Stack pointer (pointing to register dump)
;
; We need to take care about how we return if we're to get all the
; registers right. First thing to do is restore the banked registers
; to the correct mode's registers. Also set SPSR_abort to produce the
; desired final mode, if it isn't abort mode.

                ADD     R7, R13, #8*4   ; Place to find reg values

          [ HandlerCallMode = "Abort"
                LDMIA   R7, {R8-R14}
          |
                MRS     R2, CPSR
                BIC     R1, R2, #Mode_FullMask
                ORR     R1, R1, #Mode_Callee
                MSR     SPSR$all_fields, R1
                MSR     CPSR$all_fields, R1
                LDMIA   R7, {R8-R14}
                MSR     CPSR$all_fields, R2
          ]

; Now put the PC value we want to end up with in the top used word of
; the stack.

                STR     R0, [R13, #14*4]

; Now we're ready to finish "returning", with a mode change if
; necessary.

                LDMIA   R13, {R0-R7}
                ADD     R13, R13, #14*4
          [ HandlerCallMode = "Abort"
                LDMIA   R13!, {PC}
          |
                LDMIA   R13!, {PC}^
          ]

                LTORG

        ]

        [ (:LNOT:ReturnAddress) \
          :LOR: ReturnNormal \
          :LOR: (ReturnToNext <> "")

; Code to deal with invalid requests
; ----------------------------------
;
; This code can either be fallen through to (if the "ReturnAddress"
; option isn't requested), or branched to from the "ReturnNormal" or
; "ReturnToNext" code.

ReturnInvalid

; *** Live register values at this point are:
;     R0:  Return value from OS-specific handler
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Error code
;     R13: Stack pointer (pointing to register dump)
;
; We need to issue a second call to the OS-specific handler at this
; point, with the "bad request" error code as its first parameter. The
; remaining parameters can be junk, so will simply be whatever happens
; to be in the registers concerned. (Most will in fact be OK.)

                MOV     R6, #DABORT_ERROR_BAD_REQUEST
                B       CallOSHandlerWithError

                LTORG
        ]

        [ AbortModelInit <> ""

Initialisation_Handler

; Special handler for initialisation routine
; ==========================================
;
; *** Live register values at this point are:
;     
;     R4:  Pointer to aborting instruction
;     R5:  SPSR value
;     R6:  Address of abort model variable
;     R8:  Abort model variable value
;     R13: Stack pointer (pointing to register dump)
;
; The abort model identifier is initialised to 0x40000000. Each entry
; to this handler shifts the value left by one bit, shifting in a zero
; if the base register was not changed and a 1 if it was. After two
; such entries, the high order bit is shifted out and we should be in
; a normal abort model. The first time round is done with an LDR
; instruction, the second with an LDM, in order to test the behaviour
; for both single and multiple transfers (needed to distinguish the
; "early aborts" model).
;   Both instructions will use R1 as their base register and will set
; R0 to a copy of the original base register, so the test for a
; changed base register is simply to compare the R0 and R1 values in
; the register dump.

                LDMIA   R13, {R0, R1}
                MOV     R8, R8, LSL #1
                CMP     R0, R1
                ORRNE   R8, R8, #1
                STR     R8, [R6]

; Now we're ready to return. We need to take care about how we return
; if we're to get all the registers right. First thing to do is
; restore the banked registers - this needs the same precautions about
; user modes as the corresponding entry code.

                ADD     R7, R13, #8*4   ; Place to find reg values

                ANDS    R1, R5, #Mode_MainMask
                ASSERT  (Mode_User:AND:Mode_MainMask) = 0
                LDMEQIA R7, {R8-R14}^
                BEQ     RegsRestored_Init

                MRS     R2, CPSR
                BIC     R3, R2, #Mode_MainMask
                ORR     R1, R3, R1
                MSR     CPSR$all_fields, R1
                LDMIA   R7, {R8-R14}
                MSR     CPSR$all_fields, R2

RegsRestored_Init

; PC value wanted is the address of the aborting instruction plus 4
; (we don't want to retry it), CPSR value wanted is the entry SPSR
; value.

                ADD     R4, R4, #4
                STR     R4, [R13, #14*4]
                MSR     SPSR$all_fields, R5

; Now we're ready to restore the rest of the registers and return.

                LDMIA   R13, {R0-R7}
                ADD     R13, R13, #14*4
                LDMIA   R13!, {PC}^

; The initialisation routine
; ==========================
;
; This is as outlined above.

$AbortModelInit
                EXPORT  $AbortModelInit

; Initialise the abort model variable, and set the NE condition in the
; process.

                IMPORT  $AbortModelVar
                LDR     R3, =$AbortModelVar
                MOVS    R2, #DABORT_MODEL_INITIALISATION
                STR     R2, [R3]

; Try an aborting LDR.

                MOV     R1, R0
                LDR     R2, [R1], #4

; Try an aborting LDM.

                MOV     R1, R0
                LDMIA   R1!, {R2}

; Get the abort model variable and check whether it is valid. Note we
; still have the NE condition at this point.

                LDR     R2, [R3]
        [ BaseRestored
                CMPNE   R2, #DABORT_MODEL_BASERESTORED
        ]
        [ EarlyAbort
                CMPNE   R2, #DABORT_MODEL_EARLYABORT
        ]
        [ BaseUpdated
                CMPNE   R2, #DABORT_MODEL_BASEUPDATED
        ]

; Set the return value and return.

                MOVEQ   R0, #0
                MOVNE   R0, #1
                MOV     PC, LR

        ]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; The end
; =======
;

                END
