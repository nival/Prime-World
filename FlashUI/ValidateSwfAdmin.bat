@echo off
set bytes_path=..\UnityClient\unity\Assets\Resources\FlashUI

set name=main
ECHO Copy %name%.swf
if Exist "%bytes_path%\%name%.bytes" (del "%bytes_path%\%name%.bytes")
if Exist "%bytes_path%\%name%.bin.bytes" (del "%bytes_path%\%name%.bin.bytes")
if Exist "%bytes_path%\%name%.atlas.bytes" (del "%bytes_path%\%name%.atlas.bytes")
if Exist "%bytes_path%\%name%.png" (del "%bytes_path%\%name%.png")
copy "%name%.swf" "%bytes_path%\%name%.bytes"

set name=selectFraction
ECHO Copy %name%.swf
if Exist "%bytes_path%\%name%.bytes" (del "%bytes_path%\%name%.bytes")
if Exist "%bytes_path%\%name%.bin.bytes" (del "%bytes_path%\%name%.bin.bytes")
if Exist "%bytes_path%\%name%.atlas.bytes" (del "%bytes_path%\%name%.atlas.bytes")
if Exist "%bytes_path%\%name%.png" (del "%bytes_path%\%name%.png")
copy "%name%.swf" "%bytes_path%\%name%.bytes"