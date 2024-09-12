@echo off
rem Set all database configurations, logins and passwords

call dbconfiguration.cmd

..\Utils\DataCleanup.exe %* -mu=%SERVICEDB_ADMIN_USR% -mp=%SERVICEDB_ADMIN_PWD% -lu=%SERVICEDB_ADMIN_USR% -lp=%SERVICEDB_ADMIN_PWD% -au=%ANALYSISDB_ADMIN_USR% -ap=%ANALYSISDB_ADMIN_PWD%