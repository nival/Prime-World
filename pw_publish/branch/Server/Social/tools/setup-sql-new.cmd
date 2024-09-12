@echo off
if not "%~1" == "" goto continue
@echo Usage: setup-sql-new.cmd ^<root_password^> ^[^<mysql_path^>^]
goto exit
:continue
set PASSWORD=%1
set MYSQLPATH=%ProgramFiles%\MySQL\MySQL Server 5.6\bin\
if not "%~2" == "" set MYSQLPATH=%2
"%MYSQLPATH%\mysql.exe" -u root --password=%PASSWORD% <pw_12_full.sql
"%MYSQLPATH%\mysql.exe" -u root --password=%PASSWORD% <pw_exchange.sql
"%MYSQLPATH%\mysql.exe" -u root --password=%PASSWORD% <pw_stat_full.sql
"%MYSQLPATH%\mysql.exe" -u root --password=%PASSWORD% <pw_mirror_full.sql
:exit