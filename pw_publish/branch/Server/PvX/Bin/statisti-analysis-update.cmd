@echo off

rem Set all database configurations, logins and passwords 
call dbconfiguration.cmd

rem Special variable, that stores a password to the postgres admin account
set PGPASSWORD=%ANALYSISDB_ADMIN_PWD%

rem Executing incremental update script
psql -h %ANALYSISDB_HOST% -p %ANALYSISDB_PORT% -d %ANALYSISDB_NAME% -U %ANALYSISDB_ADMIN_USR% -f ..\Utils\DBScripts\incremental_pw_analysis.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

@echo.
@echo --- Updated proccess succeed ---
goto :eof

:failed
@echo.
@echo --- Update process failed ---