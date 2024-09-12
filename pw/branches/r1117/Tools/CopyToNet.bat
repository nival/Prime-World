@echo off
SET DESTDIR=\\DINTER_SERVER\public\PrimalForces\NetGame
echo D | xcopy ..\bin "%DESTDIR%\bin" /K /F /Y /Z /S
echo D | xcopy ..\data %DESTDIR%\data /K /F /Y /Z /S
echo D | xcopy ..\Profiles %DESTDIR%\Profiles /K /F /Y /Z /S
echo D | xcopy ..\src\_Debug %DESTDIR%\src\_Debug /K /F /Y /Z /EXCLUDE:CopyToNetExcluded.txt
echo D | xcopy ..\src\_Release %DESTDIR%\src\_Release /K /F /Y /Z /EXCLUDE:CopyToNetExcluded.txt
echo F | xcopy ..\src\RunDebug.bat %DESTDIR%\src\RunDebug.bat /K /F /Y /Z
echo F | xcopy ..\src\RunRelease.bat %DESTDIR%\src\RunRelease.bat /K /F /Y /Z
