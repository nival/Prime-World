@echo off
set "RegKey=HKEY_CURRENT_USER\Software\Classes\pwclassic\GameDir"
set "ValueName=path"

set WorkingDir=
for /f "tokens=2*" %%A in ('reg query "%RegKey%" /v "%ValueName%" 2^>nul ^| findstr /i "%ValueName%"') do (
   set "WorkingDir=%%B"
)

cd /d "%WorkingDir%Bin"
call "%WorkingDir%Bin\PW_Game.exe" %1
