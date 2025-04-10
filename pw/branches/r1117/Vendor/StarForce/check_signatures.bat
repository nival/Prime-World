@echo off 

SET CUR_DIR="%~dp0"
cd %CUR_DIR%
if EXIST SF_Settings.htm call :CheckError rm SF_Settings.htm

call :CheckError CScript.exe XsltConvert.js PrimeWorld_Settings.psf SF_Settings.xslt SF_Settings.htm

set LineCount=0 
call :SetFromOutput LineCount call svn status SF_Settings.htm

if !%LineCount%! neq !0! (
  call :ShowError Function signatures are differernt!
)

echo All operations completed successfully
call :DoPause
exit 0
goto :EOF

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

rem ##########################################################################
rem Set Lines count in output with name %1 to result of output command %2 with parameters %3, %4, ...
:SetFromOutput
    set rezVarName=%1
    set CallStr=%~2

    :SetFromOutput_REPEAT

    if not "%~3"=="" (
        set CallStr=%CallStr% %~3
        shift
        goto :SetFromOutput_REPEAT
    ) 

    set count=0
    for /f "tokens=*" %%i in ('"%CallStr%"') do (
        echo %%i
        set %rezVarName%=%%i
        set /a count+=1
    )
 
    set %rezVarName%=%count%
    
goto :EOF