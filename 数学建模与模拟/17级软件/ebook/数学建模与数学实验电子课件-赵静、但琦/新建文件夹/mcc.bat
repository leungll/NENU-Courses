@echo off
rem MCC.BAT
SETLOCAL
set MCCARCH=win32
set MCCPATH=%~dp0
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  set MCCARCH=win64
) else if "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  set MCCARCH=win64
)
if %MCCARCH%==win64 (
  if not exist "%MCCPATH%win64" (
    set MCCARCH=win32
  )
)
set MWArgs=
:LOOP
if "%~1"=="" GOTO CONTINUE
if %1==-win32 (
  set MCCARCH=win32
) else (
  if not defined MWArgs (
    set MWArgs=%1
  ) else (
    set MWArgs=%MWArgs% %1
  )
)
shift
goto LOOP
:CONTINUE
if %MCCARCH%==win32 (
  if not exist "%MCCPATH%win32" (
    @echo Unable to find a suitable install area
    set errorlevel=1
    goto DONE
  )
)
set PATH="%MCCPATH%%MCCARCH%";%PATH%
"%MCCPATH%%MCCARCH%\mcc" %MWArgs%
:DONE
ENDLOCAL
"%SystemRoot%\system32\cmd" /c exit %errorlevel%
