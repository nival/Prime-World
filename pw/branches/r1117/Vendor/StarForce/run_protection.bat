@echo off

set CUR_DIR=%~dp0

set PROJECT_ID=9979
set LOG_PATH="%CUR_DIR%StarForce.log"
set PROJECT_PATH="%CUR_DIR%PrimeWorld_Settings.psf" 
set OUT_DIR="%CUR_DIR%Protection_Output"
set ANALYSE_DIR="%CUR_DIR%..\..\Src\_ShippingSingleExe"

call %CUR_DIR%\StripReloc.exe /B "%ANALYSE_DIR%\PW_Game.exe"
call :CheckError StripReloc Error
rem goto :FUNC_END

del %LOG_PATH% 

call "%ProgramFiles%\Protection Studio 2\ProtectionStudio.exe" ^
  -Action:Update -Log:%LOG_PATH% -Project:%PROJECT_PATH% ^
  -WorkspaceId:%PROJECT_ID%
  
call :CheckError Update Error

call "%ProgramFiles%\Protection Studio 2\ProtectionStudio.exe" ^
  -Action:ProtectFiles -Log:%LOG_PATH% -Project:%PROJECT_PATH% ^
  -WorkspaceId:%PROJECT_ID% -OutputFolder:%OUT_DIR% 
  rem -FolderWithExeFiles:%ANALYSE_DIR% приводит к защите всех exe файлов

:FUNC_END
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
   @echo  ERROR %ERRORLEVEL%: %*
   @echo ======================================================================
   @echo. 
   call :DoPause
   exit %ERRORLEVEL%
goto :EOF

rem ##########################################################################
:CheckError
    if %ERRORLEVEL% neq 0 (
       call :ShowError %* 
    )
goto :EOF

rem ##########################################################################
