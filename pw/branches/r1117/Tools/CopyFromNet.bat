@echo off
SET DESTDIR=\\DINTER_SERVER\public\PrimalForces\NetGame
if [%1]==[] echo First parameter (destination directory) is required
if [%1]==[] goto finalize
echo D | xcopy %DESTDIR%\bin  %1\bin   /K /F /Y /Z /S
echo D | xcopy %DESTDIR%\data %1\data  /K /F /Y /Z /S
echo D | xcopy %DESTDIR%\Profiles %1\Profiles  /K /F /Y /Z /S
echo D | xcopy %DESTDIR%\src\_Debug %1\src\_Debug  /K /F /Y /Z
echo D | xcopy %DESTDIR%\src\_Release %1\src\_Release  /K /F /Y /Z
echo F | xcopy %DESTDIR%\src\RunDebug.bat %1\src\RunDebug.bat  /K /F /Y /Z
echo F | xcopy %DESTDIR%\src\RunRelease.bat %1\src\RunRelease.bat  /K /F /Y /Z

:finalize 
exit -1
