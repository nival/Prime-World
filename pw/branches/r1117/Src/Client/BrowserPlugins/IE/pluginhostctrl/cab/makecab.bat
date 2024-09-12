@echo off

set OLDPATH=%PATH%
set CABSDKBIN=..\..\..\..\..\Vendor\cabsdk\bin

set OUTDIR=.\..\..\..\FireFox35\deploy\cab
set OUTCAB=.\..\..\..\FireFox35\deploy\nivalhostctrl.cab

set nivalhostctrlDLL=%1
set CERTFILE=%2
set KEYFILE=%3
set SPCFILE=%4

REM === Check arguments ===

if NOT .%nivalhostctrlDLL%.==.. goto have_nivalhostctrl
echo Usage : %0 nivalhostctrl [certfile keyfile spcfile]
echo .
echo Specify the path to the nivalhostctrl.dll file as the first argument
echo and optionally the certificate and keyfile as extra arguments.
goto end
:have_nivalhostctrl
if EXIST %nivalhostctrlDLL% goto valid_nivalhostctrl
echo ERROR: The specified nivalhostctrl.dll file "%nivalhostctrlDLL%" does not exist.
goto end
:valid_nivalhostctrl


REM === Make the CAB file ===

echo Please use "Sunset" without quotes whenever you are asked for password.

mkdir %OUTDIR%
copy %nivalhostctrlDLL% %OUTDIR%
copy redist\*.* %OUTDIR%
copy nivalhostctrl.inf %OUTDIR%
%CABSDKBIN%\cabarc -s 6144 -r -P %OUTDIR%\ N %OUTCAB% %OUTDIR%\*.*


REM === Generate a test certificate to sign this thing with ===

if NOT .%TESTCERT%.==.. goto end_testcert
echo Generating a test certificate...
set KEYFILE=.\test.key
set CERTFILE=.\test.cer
set SPCFILE=.\test.spc
if EXIST %CERTFILE% goto end_certfile
"%VS80COMNTOOLS%bin\makecert" -sv %KEYFILE% -n "CN=testcert.untrusted.org" %CERTFILE%
:end_certfile
if EXIST %SPCFILE% goto end_testcert
"%VS80COMNTOOLS%bin\cert2spc" %CERTFILE% %SPCFILE%
:end_testcert

REM === Sign the CAB file ===

if .%CERTFILE%.==.. goto the_end
if .%KEYFILE%.==.. goto the_end
if .%SPCFILE%.==.. goto the_end
if NOT EXIST %CERTFILE% goto the_end
if NOT EXIST %KEYFILE% goto the_end
if NOT EXIST %SPCFILE% goto the_end
echo Signing %OUTCAB%
%CABSDKBIN%\signcode-pwd.exe -m Sunset
%CABSDKBIN%\signcode -spc %SPCFILE% -v %KEYFILE% -n "Nival hosting ActiveX control" %OUTCAB%
%CABSDKBIN%\signcode-pwd.exe -t


REM == THE END ===

:the_end
rem set PATH=%OLDPATH%
set OLDPATH=
set OUTCAB=
set CERTFILE=
set KEYFILE=
set SPCFILE=
echo y | del %OUTDIR%\*.*
rmdir %OUTDIR%