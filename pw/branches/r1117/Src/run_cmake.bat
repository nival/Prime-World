@echo off

set SRC_DIR=%CD%
set OUT_DIR=%CD%\..\CMakeOutput

if not exist "%OUT_DIR%" md "%OUT_DIR%"

cd "%OUT_DIR%"

call "%VS90COMNTOOLS%\vsvars32.bat" > nul

set JOM_INSTALLED=1

if defined JOM_INSTALLED (
  rem ftp://ftp.qt.nokia.com/jom/jom.zip
  set MAKE_TOOL=jom
  set MAKE_STR="NMake Makefiles JOM"
)else (
  set MAKE_TOOL=nmake
  set MAKE_STR="NMake Makefiles"
)

cmake -G %MAKE_STR% "%SRC_DIR%" -DCMAKE_BUILD_TYPE=Release
%MAKE_TOOL% PrimeWorld\fast