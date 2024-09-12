set billpwd=password
call dbconfiguration.cmd
sqlcmd -S localhost\SQLEXPRESS -U bill -P %billpwd% -d PWBilling -i billing_database.sql
if errorlevel 1 goto failed
sqlcmd -S localhost\SQLEXPRESS -U bill -P %billpwd% -d PWBilling -i billing_dictionaries.sql
if errorlevel 1 goto failed
sqlcmd -S localhost\SQLEXPRESS -U bill -P %billpwd% -d PWBilling -i billing_schedule.sql
if errorlevel 1 goto failed
@echo.
@echo --- Updated proccess succeed ---
@goto :eof
:failed
@echo.
@echo --- Update process failed ---