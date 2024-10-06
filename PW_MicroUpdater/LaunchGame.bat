@echo off
set "RegKey=HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Uninstall\{869C346D-5682-4A41-BA14-DE721CA43B24}_is1"
set "ValueName=InstallLocation"

set WorkingDir=
for /f "tokens=2*" %%A in ('reg query "%RegKey%" /v "%ValueName%" 2^>nul ^| findstr /i "%ValueName%"') do (
   set "WorkingDir=%%B"
)

cd /d "%WorkingDir%Bin"
start PW_Game.exe %1
