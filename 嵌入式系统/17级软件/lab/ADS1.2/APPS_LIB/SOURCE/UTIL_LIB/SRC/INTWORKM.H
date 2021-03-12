;/*
; * Utility Library: Interworking assembler macros
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;==========================================================================
;  ARM Interworking Macros
;==========================================================================
;
; Version:	2.0
; Date:		28/06/1999
;
;==========================================================================
; This source file contains ARM algorithms for interworking.
; Each is implemented in the form of a MACRO so that it can inlined.
;

; Decide whether ARM code is to be interworked with thumb
; On entry:
; if ADS:
;  If INTER=0 then we do not interwork
;  If INTER=1 then we interwork and add ,INTERWORK to area definitions
;  If INTER=2 then we interwork but do not change the area defs
; else:
;  If INTERWORK is defined we force interwork
;  If NOINTERWORK is defined we force no interwork
;  Otherwise we choose whether to interwork based on {CONFIG} and
;   whether this is 16 or 32
; endif
; On exit we set 'interwork' to be "" or ",INTERWORK" depending on
; whether we are using interworking. This format is useful for the
; AREA declarations.

	MACRO
	DECIDE_INTERWORKING
	GBLS interwork
interwork SETS ""
 IF :DEF: INTER
 	; under ADS
 	; ,INTERWORK on areas?
	IF INTER=1
interwork SETS ",INTERWORK"
	ENDIF
 ELSE
	; is INTERWORK defined?
	IF :DEF: INTERWORK
interwork SETS ",INTERWORK"
	  MEXIT
	ENDIF
	; is NO INTERWORK defined ?
	IF :DEF:NOINTERWORK
	  MEXIT
	ENDIF
	; look at config
	IF {CONFIG}=16
interwork SETS ",INTERWORK"
	ENDIF
 ENDIF	; :DEF: INTER
	MEND
	
	DECIDE_INTERWORKING
	
; Now force ARM code mode on all assemblers

	CODE32

; interworking requires a BX to return to Thumb state whilst
; non-interworking can return using APCS thus use this macro to return
; from all ARM Assembler routines
;
; $rlist : (optional) list of registers to restore from stack before return
; $stack : (optional) stack pointer to load registers from, other than sp
;                     ignored if $rlist = ""
; $link  : (optional) register to read value to put into pc, other than lr
;                     ignored if $rlist <> "" and interwork = ""
; $cond  : (optional) conditional return
;
	MACRO
	RETURN $rlist, $stack, $link, $cond
 IF :DEF: INTER
 	IF INTER = 0
		IF "$rlist" = ""
			IF "$link" = ""
				MOV$cond pc, lr
			ELSE
				MOV$cond pc, $link
			ENDIF
		ELSE
			IF "$stack" = ""
				LDM$cond.FD sp!, { $rlist, pc }
			ELSE
				LDM$cond.FD $stack, { $rlist, pc }
			ENDIF
		ENDIF
	ELSE
		IF "$rlist" <> ""
			IF "$stack" = ""
				LDM$cond.FD sp!, { $rlist, lr }
			ELSE
				LDM$cond.FD $stack, { $rlist, lr }
			ENDIF
		ENDIF
		IF "$link" = ""
			BX$cond lr
		ELSE
			BX$cond $link
		ENDIF
	ENDIF
 ELSE
	IF interwork = ""
		IF "$rlist" = ""
			IF "$link" = ""
				MOV$cond pc, lr
			ELSE
				MOV$cond pc, $link
			ENDIF
		ELSE
			IF "$stack" = ""
				LDM$cond.FD sp!, { $rlist, pc }
			ELSE
				LDM$cond.FD $stack, { $rlist, pc }
			ENDIF
		ENDIF
	ELSE
		IF "$rlist" <> ""
			IF "$stack" = ""
				LDM$cond.FD sp!, { $rlist, lr }
			ELSE
				LDM$cond.FD $stack, { $rlist, lr }
			ENDIF
		ENDIF
		IF "$link" = ""
			BX$cond lr
		ELSE
			BX$cond $link
		ENDIF
	ENDIF
 ENDIF	; :DEF: INTER
	MEND
	
; end
	
	END
