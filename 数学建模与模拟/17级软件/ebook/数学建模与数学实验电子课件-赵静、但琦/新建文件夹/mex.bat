@echo off
rem MEX.BAT
rem
rem    Compile and link tool used for building MEX-files
rem
rem
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  set MEXARCH=win64
) else if "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  set MEXARCH=win64
) else (
  set MEXARCH=win32
)
if %MEXARCH% == win64 (
  if not exist "%~dp0\win64" (
    set MEXARCH=win32
  )
)
"%~dp0\%MEXARCH%\mex.exe" %*

