cd %~dp0

:: Read database configurations, logins and passwords
call dbconfiguration.cmd

:: Create directory for logs and generate time suffixes for filename
if not exist logs mkdir logs

set datetokens=2-4
echo %date% | findstr /r "[A-Za-z]"
if errorlevel 1 set datetokens=1-3

For /f "tokens=%datetokens% delims=/. " %%a in ('date /t') do (set mydate=%%c-%%b-%%a)
For /f "tokens=1-2 delims=/: " %%a in ('time /t') do (set mytime=%%a%%b)

:: Run management job 
set logfile=%~dp0/logs/dictionaries_%mydate%_%mytime%.log
call %kettlepath%\kitchen.bat /file:%~dp0/job-import-pw_management.kjb /level:Detailed /param:analysis_host=%ANALYSISDB_HOST% /param:analysis_port=%ANALYSISDB_PORT% /param:analysis_dbname=%ANALYSISDB_NAME% /param:analysis_usr=%ANALYSISDB_ADMIN_USR% /param:analysis_pwd=%ANALYSISDB_ADMIN_PWD% /param:logs_host=%SERVICEDB_HOST% /param:logs_port=%SERVICEDB_PORT% /param:logs_dbname=%LOGSDB_NAME% /param:logs_usr=%LOGSDB_ADMIN_USR% /param:logs_pwd=%LOGSDB_ADMIN_PWD% /param:manage_host=%SERVICEDB_HOST% /param:manage_port=%SERVICEDB_PORT% /param:manage_dbname=%MANAGEMENTDB_NAME% /param:manage_usr=%REPORTING_USR% /param:manage_pwd=%REPORTING_PWD% /logfile:%logfile%

@echo.
@if errorlevel 1 echo !!! FAILED !!!