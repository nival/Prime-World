@echo off

rem Set all database configurations, logins and passwords 
if exist dbconfiguration.gstat.cmd (call dbconfiguration.gstat.cmd) else (call dbconfiguration.cmd)

rem Special variable, that stores a password to the postgres admin account
set PGPASSWORD=%SERVICEDB_ADMIN_PWD%

rem Executing incremental update scripts
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d %MANAGEMENTDB_NAME% -U %SERVICEDB_ADMIN_USR% -f ..\Utils\DBScripts\incremental_pw_management.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed
set PGPASSWORD=%LOGSDB_ADMIN_PWD%
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d %LOGSDB_NAME% -U %LOGSDB_ADMIN_USR% -f ..\Utils\DBScripts\incremental_pw_logs.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

rem Execute import from game database
..\Utils\GameDataImporter gstat
if errorlevel 1 goto failed

@echo.
@echo --- Updated proccess succeed ---
goto :eof

:failed
@echo.
@echo --- Update process failed ---