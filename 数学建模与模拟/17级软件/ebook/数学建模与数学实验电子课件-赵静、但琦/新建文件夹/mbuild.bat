@echo off
rem MBUILD.BAT
rem Compile and link tool 

rem Decide the bit-ness of 
rem mex.exe file to be executed
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

rem display Help

SETLOCAL
set helpFlag=%1

if "%helpFlag%"=="" goto :displayHelp
if "%helpFlag%"=="-h" goto :displayHelp
if "%helpFlag%"=="-help" goto :displayHelp

ENDLOCAL

rem This is useful when -win32 flag is provided  
rem along with MCC to develop 32 bit application
rem Switch between creating a shared library, executable or COM components.
for %%i in (%1 %2 %3) do (
if "%%i"=="-win32" (set MEXARCH=win32
)
if "%%i"=="mbuild" goto :buildLibrary
if "%%i"=="mbuild_com" goto :buildCOM
)

goto :buildEXE

:buildLibrary
:buildCOM

"%~dp0\%MEXARCH%\mex.exe" -largeArrayDims %*
goto DONE  

:buildEXE
"%~dp0\%MEXARCH%\mex.exe" -largeArrayDims -client mbuild %* 
goto DONE

:displayHelp
"%~dp0\%MEXARCH%\mbuildHelp.exe"
goto DONE

:DONE
"%SystemRoot%\system32\cmd" /c exit %errorlevel%
