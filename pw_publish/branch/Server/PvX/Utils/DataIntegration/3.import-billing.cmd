cd %~dp0

:: Read database configurations, logins and passwords
call dbconfiguration.cmd

:: Create directory for logs and generate time suffixes for filename
if not exist logs mkdir logs

:: Drop fail marker
if exist logs\.failed-billing del logs\.failed-billing

set datetokens=2-4
echo %date% | findstr /r "[A-Za-z]"
if errorlevel 1 set datetokens=1-3

For /f "tokens=%datetokens% delims=/. " %%a in ('date /t') do (set mydate=%%c-%%b-%%a)
For /f "tokens=1-2 delims=/: " %%a in ('time /t') do (set mytime=%%a%%b)

:: Run management job 
set logfile=%~dp0logs\billing_%mydate%_%mytime%.log
call %kettlepath%\kitchen.bat /file:%~dp0/job-start-billing.kjb /level:Detailed /param:analysis_host=%ANALYSISDB_HOST% /param:analysis_port=%ANALYSISDB_PORT% /param:analysis_dbname=%ANALYSISDB_NAME% /param:analysis_usr=%ANALYSISDB_ADMIN_USR% /param:analysis_pwd=%ANALYSISDB_ADMIN_PWD% /param:billing_host=%BILLINGDB_HOST% /param:billing_dbname=%BILLINGDB_NAME% /param:billing_usr=%BILLING_USR% /param:billing_pwd=%BILLING_PWD% /logfile:%logfile%

@echo.
@if errorlevel 1 (
  echo !!! FAILED !!!
  echo %logfile% > logs\.failed-billing
)