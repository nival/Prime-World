@echo off
echo Remember that INSTALL operation need to perform ONLY in case of initial GM tools deployment!
echo Do you really want to execute install?
choice
if errorlevel 2 goto cancelled
if errorlevel 1 goto begin
if errorlevel 0 exit

:begin

rem Set all database configurations, logins and passwords 
call dbconfiguration.cmd

:: Replace templates in sql scripts
for /d %%f in (..\Utils\DBScripts\create_gm_databases.sql) do (
	echo processing file %%f
	cscript /nologo replace.vbs #GMADMINDB_NAME# %GMADMINDB_NAME% %%f
)

rem Special variable, that stores a password to the postgres admin account
set PGPASSWORD=%GMDB_ADMIN_PWD%

rem Create gmdb_admin database
psql -h %GMADMINDB_HOST% -p %GMADMINDB_PORT% -d postgres -U %GMDB_ADMIN_USR% -f ..\Utils\DBScripts\create_gm_databases.sql
if errorlevel 1 goto failed

rem Create all tables, constraints and grant rights on GM database
psql -h %GMADMINDB_HOST% -p %GMADMINDB_PORT% -d %GMADMINDB_NAME% -U %GMDB_ADMIN_USR% -f ..\Utils\DBScripts\gmdb_admin.sql
if errorlevel 1 goto failed

@echo.
@echo --- Updated proccess succeed ---
exit

:failed
@echo.
@echo --- Update process failed ---
exit

:cancelled
@echo.
@echo --- Update process cancelled ---