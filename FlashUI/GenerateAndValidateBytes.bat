@echo off
set bytes_path=..\UnityClient\unity\Assets\Resources\FlashUI

set xmlswf="xmlswf"
set converter="xmlswf\swfmill.exe"

set name=main
%converter% -v xml2swf "%xmlswf%\%name%.swf.xml" "%xmlswf%\%name%.swf"

set name=selectFraction
%converter% -v xml2swf "%xmlswf%\%name%.swf.xml" "%xmlswf%\%name%.swf"

set name=loginQueue
%converter% -v xml2swf "%xmlswf%\%name%.swf.xml" "%xmlswf%\%name%.swf"


"SwfValidator.exe" "GameScreen.xml->%xmlswf%\main.swf" "SelectFractionDispatcher.xml->%xmlswf%\selectFraction.swf" "QueueForLogin.xml->%xmlswf%\loginQueue.swf"

if "%ERRORLEVEL%" == "0" GOTO COPY_FILES
GOTO END_PROGRAMM

:COPY_FILES

set name=main
ECHO Copy %xmlswf%\%name%.swf
if Exist "%bytes_path%\%name%.bytes" (del "%bytes_path%\%name%.bytes")
if Exist "%bytes_path%\%name%.bin.bytes" (del "%bytes_path%\%name%.bin.bytes")
if Exist "%bytes_path%\%name%.atlas.bytes" (del "%bytes_path%\%name%.atlas.bytes")
if Exist "%bytes_path%\%name%.png" (del "%bytes_path%\%name%.png")
copy "%xmlswf%\%name%.swf" "%bytes_path%\%name%.bytes"
del "%xmlswf%\%name%.swf"

set name=selectFraction
ECHO Copy %xmlswf%\%name%.swf
if Exist "%bytes_path%\%name%.bytes" (del "%bytes_path%\%name%.bytes")
if Exist "%bytes_path%\%name%.bin.bytes" (del "%bytes_path%\%name%.bin.bytes")
if Exist "%bytes_path%\%name%.atlas.bytes" (del "%bytes_path%\%name%.atlas.bytes")
if Exist "%bytes_path%\%name%.png" (del "%bytes_path%\%name%.png")
copy "%xmlswf%\%name%.swf" "%bytes_path%\%name%.bytes"
del "%xmlswf%\%name%.swf"

set name=loginQueue
ECHO Copy %xmlswf%\%name%.swf
if Exist "%bytes_path%\%name%.bytes" (del "%bytes_path%\%name%.bytes")
if Exist "%bytes_path%\%name%.bin.bytes" (del "%bytes_path%\%name%.bin.bytes")
if Exist "%bytes_path%\%name%.atlas.bytes" (del "%bytes_path%\%name%.atlas.bytes")
if Exist "%bytes_path%\%name%.png" (del "%bytes_path%\%name%.png")
copy "%xmlswf%\%name%.swf" "%bytes_path%\%name%.bytes"
del "%xmlswf%\%name%.swf"

:END_PROGRAMM
PAUSE
Exit