@echo off

set dstPath=%CD%
set instPath=%CD%
if EXIST "%dstPath%\nat" (	set instPath=%CD%\nat)

set svnUrl=https://svn.SITE/nat/

if NOT EXIST "%dstPath%\bin\TortoiseProc.exe" goto noTortue
if NOT EXIST "%dstPath%\bin\Shortcut.exe" goto noShortcut

if EXIST "%instPath%\.svn\" goto updateVersion

:chekOutVersion
cd "%dstPath%"
"%dstPath%\bin\TortoiseProc.exe" /command:checkout /path:. /url:"%svnUrl%"
if EXIST "%dstPath%\nat" (	set instPath=%CD%\nat)

:updateVersion
cd "%instPath%"
"%dstPath%\bin\TortoiseProc.exe" /command:update /path:. /closeonend:2

if EXIST "%Userprofile%\Desktop\"  goto setMayaShortcutEng  
if EXIST "%Userprofile%\Рабочий стол\" goto setMayaShortcutRus 
goto unknownWin

:setMayaShortcutRus
echo Russian Winda
"%dstPath%\bin\Shortcut.exe" /f:"%Userprofile%\Рабочий стол\MayaNAT Launcher.lnk" /a:c /t:"%instPath%\startMayaNat.cmd" /w:"%instPath%" /i:"%instPath%\icons\MayaNAT.ico"
goto end

:setMayaShortcutEng
echo English Winda
"%dstPath%\bin\Shortcut.exe" /f:"%Userprofile%\Desktop\MayaNAT Launcher.lnk" /a:c /t:"%instPath%\startMayaNat.cmd" /w:"%instPath%"  /i:"%instPath%\icons\MayaNAT.ico"
goto end

:unknownWin
echo This script can detect russion or english windows version. Cannot detect version of your windows. Shortcut cannot continue.
pause
goto end

:noTortue
echo ERROR: Tortue SVN command line can't be located. Copy TortoiseProc.exe to %dstPath%\bin\ folder.
pause
goto end

:noShortcut
echo ERROR: Shortcut command line can't be located. Copy Shortcut.exe to %dstPath%\bin\ folder.
pause
goto end

:end