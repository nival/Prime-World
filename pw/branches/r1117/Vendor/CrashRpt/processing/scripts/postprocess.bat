@echo off
rem Process a group of ZIP error report files

set INPUT_DIR="E:\ErrorReports"
set INPUT_FILE_PATTERN="*.zip"
set ACCEPTABLE_APPNAME="CrashRpt Tests"
set ACCEPTABLE_APPVERSION="1.2.0"
set SYM_SEARCH_DIRS="D:\Projects\CrashRpt\CrashRptSaved\1.2.0"
set SAVE_RESULTS_TO_DIR="valid_reports\"
set SAVE_INVALID_REPORTS_TO_DIR="invalid_reports\"
set CRPROBER_PATH="D:\Projects\CrashRpt\bin\crprober.exe"

mkdir %SAVE_RESULTS_TO_DIR%

for /R %INPUT_DIR% %%f in ( %INPUT_FILE_PATTERN% ) do call :process_report "%%f"
erase temp.txt
exit 

:process_report

  echo Processing file: %1

  if %ACCEPTABLE_APPNAME%=="" goto appname_ok
  rem Get application name from the crash report file and write it to "temp.txt"
  %CRPROBER_PATH% /f %1 /o "temp.txt" /get XmlDescMisc AppName 0
  if not %errorlevel%==0 goto failed
 
  set /p app_name=<temp.txt
  if "%app_name%"==%ACCEPTABLE_APPNAME% goto appname_ok
  goto done

:appname_ok

  if %ACCEPTABLE_APPVERSION%=="" goto appversion_ok
  rem Get application version from the crash report file and write it to "temp.txt"
  %CRPROBER_PATH% /f %1 /o "temp.txt" /get XmlDescMisc AppVersion 0
  if not %errorlevel%==0 goto failed
 
  set /p app_version=<temp.txt
  if "%app_version%"==%ACCEPTABLE_APPVERSION% goto appversion_ok

  goto done

:appversion_ok

  set stack_md5=NoExceptionInfo
  %CRPROBER_PATH% /f %1 /o "temp.txt" /sym %SYM_SEARCH_DIRS%  /get MdmpMisc ExceptionThreadStackMD5 0
  if not %errorlevel%==0 goto save_results
  set /p stack_md5=<temp.txt
  erase temp.txt

  if %stack_md5%=="" set stack_md5=NoSymbolsLoaded

:save_results

  mkdir %SAVE_RESULTS_TO_DIR%%stack_md5%
  

  rem Process report and write results to text file
  %CRPROBER_PATH% /f %1 /o %1.txt /sym %SYM_SEARCH_DIRS% 
  echo Return code=%errorlevel%
  if not %errorlevel%==0 goto failed

:ok
  move %1 %SAVE_RESULTS_TO_DIR%%stack_md5%
  move %1.txt %SAVE_RESULTS_TO_DIR%%stack_md5%
  goto done

:failed

 mkdir %SAVE_INVALID_REPORTS_TO_DIR%
 move %1 %SAVE_INVALID_REPORTS_TO_DIR%
 
:done
  
rem Return from subroutine
goto :eof
