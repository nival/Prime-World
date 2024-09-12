@echo off
pushd "%~dp0"
call __stop_all.bat
del /Q /A-H ..\logs\*.*
call __start_all.bat
popd
rundll32 user32.dll,MessageBeep 64
rundll32 user32.dll,MessageBeep 64