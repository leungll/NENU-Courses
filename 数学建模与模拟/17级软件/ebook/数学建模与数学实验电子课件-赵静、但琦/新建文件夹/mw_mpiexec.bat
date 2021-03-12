@echo off
REM Simple wrapper around mpiexec to select the appropriate binary

SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION 

REM Copyright 2006 The MathWorks, Inc.
REM $Revision: 1.1.6.2 $   $Date: 2007/11/12 22:52:27 $

REM Choose whether we're on win32 or win64
set MATLAB_BIN_DIR=%~dp0
set CPU=x86
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  set CPU=x64
) else if "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  set CPU=x64
)

set MATLAB_ARCH=win32
if "%CPU%" == "x64" (
  if exist "!MATLAB_BIN_DIR!\win64" (
    set MATLAB_ARCH=win64
  )
)

REM Call the right mpiexec.exe
"!MATLAB_BIN_DIR!\!MATLAB_ARCH!\mpiexec" %*
