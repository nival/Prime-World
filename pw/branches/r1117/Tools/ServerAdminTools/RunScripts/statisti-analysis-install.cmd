@echo off
echo Remember that INSTALL operation need to perform ONLY in case of initial service deployment!
echo Do you really want to execute install?
choice
if errorlevel 2 goto cancelled
if errorlevel 1 goto begin
if errorlevel 0 exit

:begin

:: Set all database configurations, logins and passwords 
call dbconfiguration.cmd

:: Replace templates in sql scripts
for /d %%f in (..\Utils\DBScripts\create_service_databases.sql, ..\Utils\DBScripts\create_analysis_databases.sql) do (
	echo processing file %%f
	cscript -nologo replace.vbs #LOGSDB_NAME# %LOGSDB_NAME% %%f
	cscript -nologo replace.vbs #MANAGEMENTDB_NAME# %MANAGEMENTDB_NAME% %%f
	cscript -nologo replace.vbs #LOGGING_PWD# %LOGGING_PWD% %%f
	cscript -nologo replace.vbs #REPORTING_PWD# %REPORTING_PWD% %%f
	cscript -nologo replace.vbs #ANALYSISDB_NAME# %ANALYSISDB_NAME% %%f
	cscript -nologo replace.vbs #PRODUCER_PWD# %PRODUCER_PWD% %%f
)

:: Special variable, that stores a password to the postgres admin account
set PGPASSWORD=%ANALYSISDB_ADMIN_PWD%

:: Create analysis database (pw_analysis), users and roles
psql -h %ANALYSISDB_HOST% -p %ANALYSISDB_PORT% -d postgres -U %ANALYSISDB_ADMIN_USR% -f ..\Utils\DBScripts\create_analysis_databases.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

:: Create all tables, constraints and grant rights in analysis database
psql -h %ANALYSISDB_HOST% -p %ANALYSISDB_PORT% -d %ANALYSISDB_NAME% -U %ANALYSISDB_ADMIN_USR% -1 -f ..\Utils\DBScripts\pw_analysis.sql --set ON_ERROR_STOP=on
if errorlevel 1 goto failed

@echo.
@echo --- Updated proccess succeed ---
goto :eof

:failed
@echo.
@echo --- Update process failed ---
goto :eof

:cancelled
@echo.
@echo --- Update process cancelled ---