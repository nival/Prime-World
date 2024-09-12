@echo off
@echo off
echo Remember that INSTALL operation need to perform ONLY in case of initial service deployment!
echo Do you really want to execute install?
choice
if errorlevel 2 goto cancelled
if errorlevel 1 goto begin
if errorlevel 0 exit

:begin

:: Set all database configurations, logins and passwords 
if exist dbconfiguration.gstat.cmd (call dbconfiguration.gstat.cmd) else (call dbconfiguration.cmd)

:: Replace templates in sql scripts
for /d %%f in (..\Utils\DBScripts\create_service_databases.sql, ..\Utils\DBScripts\create_analysis_databases.sql, ..\Utils\DBScripts\create_log_database.sql) do (
	echo processing file %%f
	cscript -nologo replace.vbs #LOGSDB_NAME# %LOGSDB_NAME% %%f
	cscript -nologo replace.vbs #MANAGEMENTDB_NAME# %MANAGEMENTDB_NAME% %%f
	cscript -nologo replace.vbs #LOGGING_PWD# %LOGGING_PWD% %%f
	cscript -nologo replace.vbs #REPORTING_PWD# %REPORTING_PWD% %%f
	cscript -nologo replace.vbs #ANALYSISDB_NAME# %ANALYSISDB_NAME% %%f
	cscript -nologo replace.vbs #PRODUCER_PWD# %PRODUCER_PWD% %%f
)

:: Create database pw_management, users and roles
set PGPASSWORD=%SERVICEDB_ADMIN_PWD%
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d postgres -U %SERVICEDB_ADMIN_USR% -f ..\Utils\DBScripts\create_service_databases.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed
:: Create database pw_logs, users and roles
set PGPASSWORD=%LOGSDB_ADMIN_PWD%
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d postgres -U %LOGSDB_ADMIN_USR% -f ..\Utils\DBScripts\create_log_database.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

:: Create all tables, constraints and grant rights in service databases
set PGPASSWORD=%SERVICEDB_ADMIN_PWD%
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d %MANAGEMENTDB_NAME% -U %SERVICEDB_ADMIN_USR% -1 -f ..\Utils\DBScripts\pw_management.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

set PGPASSWORD=%LOGSDB_ADMIN_PWD%
psql -h %SERVICEDB_HOST% -p %SERVICEDB_PORT% -d %LOGSDB_NAME% -U %LOGSDB_ADMIN_USR% -1 -f ..\Utils\DBScripts\pw_logs.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

:: Execute import from game database
..\Utils\GameDataImporter gstat
if errorlevel 1 goto failed

echo.
echo --- Update proccess succeed ---
goto :eof

:failed
echo.
echo --- Update process failed ---
goto :eof

:cancelled
echo.
echo --- Update process cancelled ---