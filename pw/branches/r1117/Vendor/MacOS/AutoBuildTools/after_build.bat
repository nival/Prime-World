@echo off 

SET CUR_DIR="%~dp0"
SET BIN_DIR=%~1

SET SVN_USER="%~2"
SET SVN_PASS="%~3"
SET DO_NOT_PAUSE=%~4

SET SVN_DEFAULTS=--force --non-interactive --trust-server-cert --no-auth-cache
SET SVN_AUTH=--username %SVN_USER% --password %SVN_PASS%

if not exist "%BIN_DIR%" call :ShowError Dir "%BIN_DIR%" doesn't exist 

REM call :CheckError copy "%CUR_DIR%\..\..\Terabit\lib\IOTerabitWine.dll" "%BIN_DIR%\IOTerabit.dll"
REM call :CheckError copy "%CUR_DIR%\..\..\Terabit\lib\TProactorWine.dll" "%BIN_DIR%\TProactor.dll"

call :CheckError svn export https://svn.nivalnetwork.com/pw/trunk/Vendor/Terabit/lib/IOTerabitWine.dll "%BIN_DIR%\IOTerabit.dll" %SVN_DEFAULTS% %SVN_AUTH%
call :CheckError svn export https://svn.nivalnetwork.com/pw/trunk/Vendor/Terabit/lib/TProactorWine.dll "%BIN_DIR%\TProactor.dll" %SVN_DEFAULTS% %SVN_AUTH%

echo All operations completed successfully
call :DoPause
goto :EOF

rem ##########################################################################
:DoPause
    if "%DO_NOT_PAUSE%" neq "true" pause
goto :EOF

rem ##########################################################################
:ShowError
   @echo.
   @echo ======================================================================
   @echo  ERROR: %*
   @echo ======================================================================
   @echo. 
   call :DoPause
   exit 1
goto :EOF

rem ##########################################################################
:CheckError
    %*
    if %ERRORLEVEL% neq 0 (
       call :ShowError %* 
    )
goto :EOF

rem ##########################################################################