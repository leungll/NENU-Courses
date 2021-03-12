;/*
; * G.711 assembler lookup tables
; * Copyright (C) ARM Limited 1998-1999. All rights reserved.
; */

;===========================================================================
;
; CCITT A-law <-> u-law converter tables.
;
; Date   : 31/03/1998
;
;===========================================================================

	EXPORT	G711_u2a_lookup
	EXPORT	G711_a2u_lookup
	
	AREA	|C$$DATA|, DATA, READONLY
	
;-----------------------------------------------------------------------
;
; G711_a2u_lookup
;
; Lookup table used to convert 8-bit A-law values to 8-bit u-law values.
;
;-----------------------------------------------------------------------
;
G711_a2u_lookup
	DCB	1
	DCB	3
	DCB	5
	DCB	7
	DCB	9
	DCB	11
	DCB	13
	DCB	15
	DCB	16
	DCB	17
	DCB	18
	DCB	19
	DCB	20
	DCB	21
	DCB	22
	DCB	23
	DCB	24
	DCB	25
	DCB	26
	DCB	27
	DCB	28
	DCB	29
	DCB	30
	DCB	31
	DCB	32
	DCB	32
	DCB	33
	DCB	33
	DCB	34
	DCB	34
	DCB	35
	DCB	35
	DCB	36
	DCB	37
	DCB	38
	DCB	39
	DCB	40
	DCB	41
	DCB	42
	DCB	43
	DCB	44
	DCB	45
	DCB	46
	DCB	47
	DCB	48
	DCB	48
	DCB	49
	DCB	49
	DCB	50
	DCB	51
	DCB	52
	DCB	53
	DCB	54
	DCB	55
	DCB	56
	DCB	57
	DCB	58
	DCB	59
	DCB	60
	DCB	61
	DCB	62
	DCB	63
	DCB	64
	DCB	64
	DCB	65
	DCB	66
	DCB	67
	DCB	68
	DCB	69
	DCB	70
	DCB	71
	DCB	72
	DCB	73
	DCB	74
	DCB	75
	DCB	76
	DCB	77
	DCB	78
	DCB	79
	DCB	79
	DCB	80
	DCB	81
	DCB	82
	DCB	83
	DCB	84
	DCB	85
	DCB	86
	DCB	87
	DCB	88
	DCB	89
	DCB	90
	DCB	91
	DCB	92
	DCB	93
	DCB	94
	DCB	95
	DCB	96
	DCB	97
	DCB	98
	DCB	99
	DCB	100
	DCB	101
	DCB	102
	DCB	103
	DCB	104
	DCB	105
	DCB	106
	DCB	107
	DCB	108
	DCB	109
	DCB	110
	DCB	111
	DCB	112
	DCB	113
	DCB	114
	DCB	115
	DCB	116
	DCB	117
	DCB	118
	DCB	119
	DCB	120
	DCB	121
	DCB	122
	DCB	123
	DCB	124
	DCB	125
	DCB	126
	DCB	127

;-----------------------------------------------------------------------
;
; G711_u2a_lookup
;
; Lookup table used to convert 8-bit u-law values to 8-bit A-law values.
;
;-----------------------------------------------------------------------
;
G711_u2a_lookup
	DCB	1
	DCB	1
	DCB	2
	DCB	2
	DCB	3
	DCB	3
	DCB	4
	DCB	4
	DCB	5
	DCB	5
	DCB	6
	DCB	6
	DCB	7
	DCB	7
	DCB	8
	DCB	8
	DCB	9
	DCB	10
	DCB	11
	DCB	12
	DCB	13
	DCB	14
	DCB	15
	DCB	16
	DCB	17
	DCB	18
	DCB	19
	DCB	20
	DCB	21
	DCB	22
	DCB	23
	DCB	24
	DCB	25
	DCB	27
	DCB	29
	DCB	31
	DCB	33
	DCB	34
	DCB	35
	DCB	36
	DCB	37
	DCB	38
	DCB	39
	DCB	40
	DCB	41
	DCB	42
	DCB	43
	DCB	44
	DCB	46
	DCB	48
	DCB	49
	DCB	50
	DCB	51
	DCB	52
	DCB	53
	DCB	54
	DCB	55
	DCB	56
	DCB	57
	DCB	58
	DCB	59
	DCB	60
	DCB	61
	DCB	62
	DCB	64
	DCB	65
	DCB	66
	DCB	67
	DCB	68
	DCB	69
	DCB	70
	DCB	71
	DCB	72
	DCB	73
	DCB	74
	DCB	75
	DCB	76
	DCB	77
	DCB	78
	DCB	79
	DCB	81
	DCB	82
	DCB	83
	DCB	84
	DCB	85
	DCB	86
	DCB	87
	DCB	88
	DCB	89
	DCB	90
	DCB	91
	DCB	92
	DCB	93
	DCB	94
	DCB	95
	DCB	96
	DCB	97
	DCB	98
	DCB	99
	DCB	100
	DCB	101
	DCB	102
	DCB	103
	DCB	104
	DCB	105
	DCB	106
	DCB	107
	DCB	108
	DCB	109
	DCB	110
	DCB	111
	DCB	112
	DCB	113
	DCB	114
	DCB	115
	DCB	116
	DCB	117
	DCB	118
	DCB	119
	DCB	120
	DCB	121
	DCB	122
	DCB	123
	DCB	124
	DCB	125
	DCB	126
	DCB	127
	DCB	128

	END