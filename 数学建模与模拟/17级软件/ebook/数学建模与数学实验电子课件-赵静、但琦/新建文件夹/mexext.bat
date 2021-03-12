@echo off
rem MEXEXT.BAT
rem
rem    Script for returning MEX-file extension on the executing platform.
rem
rem    Example:  The following is a fragment of a GNU makefile that uses
rem              the mexext script to obtain the MEX-file extension: 
rem 
rem              ext = $(shell mexext)
rem
rem              yprime.$(ext) : yprime.c 
rem                     mex yprime.c
rem
rem    Copyright 1984-2008 The MathWorks, Inc.
rem    $Revision: 1.1.8.3 $  $Date: 2008/04/06 18:59:03 $
rem  __________________________________________________________________________
rem

setlocal
if NOT (%1) == () (
	echo Error: MEXEXT: No arguments are allowed. 1>&2
	goto end:
)

rem Capture machine architecture in the %BINARCH% variable
rem Batch variable %~dps0 resolves to $MATLAB\bin
call %~dps0\util\arch.bat

rem Define matching MEX-file extension
if "%BINARCH%" == "win32" (
	set temp_mexext=mexw32
) else if "%BINARCH%" == "win64" (
	set temp_mexext=mexw64
) else (
	echo Error: MEXEXT: Unsupported platform. 1>&2
	goto end:
)

echo %temp_mexext%
endlocal
:end
