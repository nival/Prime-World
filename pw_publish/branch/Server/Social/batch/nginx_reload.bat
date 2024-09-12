@cd ..\tools\nginx
@nginx -s reload
@IF %errorlevel% == 0 GOTO ReloadOk

@echo Reload failed, starting new nginx..
@start nginx.exe

:ReloadOk
@echo OK.
