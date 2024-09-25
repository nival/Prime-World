REM Delete all temporary files 

erase /A H *.suo
erase *.ncb
erase *.opt
erase *.ilk
erase *.sdf
erase ZERO_CHECK.*

erase bin\*.pdb
erase bin\*.ilk
erase bin\*d.exe
erase bin\*d.dll
erase bin\*LIB.exe

erase bin\x64\*.pdb
erase bin\x64\*.ilk
erase bin\x64\*d.exe
erase bin\x64\*d.dll
erase bin\x64\*LIB.exe

erase docs\Warnings.txt

erase lib\*d.lib
erase lib\*.exp
erase lib\*LIB.lib

rmdir /S /Q thirdparty\lib

rmdir /S /Q demos\ConsoleDemo\Debug
rmdir /S /Q demos\ConsoleDemo\Release
rmdir /S /Q "demos\ConsoleDemo\Release LIB"
rmdir /S /Q demos\ConsoleDemo\x64
rmdir /S /Q demos\ConsoleDemo\CMakeFiles
rmdir /S /Q demos\ConsoleDemo\ConsoleDemo.dir
erase /A H demos\ConsoleDemo\*.user
erase demos\ConsoleDemo\*.aps

rmdir /S /Q demos\WTLDemo\Debug
rmdir /S /Q demos\WTLDemo\Release
rmdir /S /Q "demos\WTLDemo\Release LIB"
rmdir /S /Q demos\WTLDemo\x64
rmdir /S /Q demos\WTLDemo\CMakeFiles
rmdir /S /Q demos\WTLDemo\WTLDemo.dir
erase /A H demos\WTLDemo\*.user
erase demos\WTLDemo\*.aps

rmdir /S /Q demos\MFCDemo\Debug
rmdir /S /Q demos\MFCDemo\Release
rmdir /S /Q "demos\MFCDemo\Release LIB"
rmdir /S /Q demos\MFCDemo\x64
rmdir /S /Q demos\MFCDemo\CMakeFiles
rmdir /S /Q demos\MFCDemo\MFCDemo.dir
erase /A H demos\MFCDemo\*.user
erase demos\MFCDemo\*.aps

rmdir /S /Q reporting\crashrpt\Debug
rmdir /S /Q reporting\crashrpt\Release
rmdir /S /Q reporting\crashrpt\x64
erase /A H reporting\crashrpt\*.user
erase reporting\crashrpt\*.aps

rmdir /S /Q reporting\CrashSender\Debug
rmdir /S /Q reporting\CrashSender\Release
rmdir /S /Q "reporting\CrashSender\Release LIB"
rmdir /S /Q reporting\CrashSender\x64
erase /A H reporting\CrashSender\*.user
erase reporting\CrashSender\*.aps
erase reporting\CrashSender\*.aps

rmdir /S /Q thirdparty\zlib\Debug
rmdir /S /Q thirdparty\zlib\Release
rmdir /S /Q "thirdparty\zlib\Release LIB"
rmdir /S /Q thirdparty\zlib\x64
erase /A H thirdparty\zlib\*.user
erase thirdparty\zlib\*.aps

rmdir /S /Q thirdparty\libpng\Debug
rmdir /S /Q thirdparty\libpng\Release
rmdir /S /Q "thirdparty\libpng\Release LIB"
rmdir /S /Q thirdparty\libpng\x64
erase /A H thirdparty\libpng\*.user
erase thirdparty\libpng\*.aps

rmdir /S /Q thirdparty\minizip\Debug
rmdir /S /Q thirdparty\minizip\Release
rmdir /S /Q "thirdparty\minizip\Release LIB"
rmdir /S /Q thirdparty\minizip\x64
erase /A H thirdparty\minizip\*.user
erase thirdparty\minizip\*.aps

rmdir /S /Q thirdparty\jpeg\Debug
rmdir /S /Q thirdparty\jpeg\Release
rmdir /S /Q "thirdparty\jpeg\Release LIB"
rmdir /S /Q thirdparty\jpeg\x64
erase /A H thirdparty\jpeg\*.user
erase thirdparty\jpeg\*.aps

rmdir /S /Q thirdparty\tinyxml\Debug
rmdir /S /Q thirdparty\tinyxml\Release
rmdir /S /Q "thirdparty\tinyxml\Release LIB"
rmdir /S /Q thirdparty\tinyxml\x64
erase /A H thirdparty\tinyxml\*.user
erase thirdparty\tinyxml\*.aps

rmdir /S /Q thirdparty\libogg\win32\VS2010\Debug
rmdir /S /Q thirdparty\libogg\win32\VS2010\Release
rmdir /S /Q "thirdparty\libogg\win32\VS2010\Release LIB"
rmdir /S /Q thirdparty\libogg\win32\VS2010\x64
erase /A H thirdparty\libogg\win32\VS2010\*.user
erase thirdparty\libogg\win32\VS2010\*.aps

rmdir /S /Q thirdparty\libtheora\win32\VS2010\libtheora\Debug
rmdir /S /Q thirdparty\libtheora\win32\VS2010\libtheora\Release
rmdir /S /Q "thirdparty\libtheora\win32\VS2010\libtheora\Release LIB"
rmdir /S /Q thirdparty\libtheora\win32\VS2010\libtheora\x64
erase /A H thirdparty\libtheora\win32\VS2010\libtheora\*.user
erase thirdparty\libtheora\win32\VS2010\libtheora\*.aps

rmdir /S /Q processing\CrashRptProbe\Debug
rmdir /S /Q processing\CrashRptProbe\Release
rmdir /S /Q "processing\CrashRptProbe\Release LIB"
rmdir /S /Q processing\CrashRptProbe\x64
erase /A H processing\CrashRptProbe\*.user
erase processing\CrashRptProbe\*.aps

rmdir /S /Q processing\crprober\Debug
rmdir /S /Q processing\crprober\Release
rmdir /S /Q processing\"crprober\Release LIB"
rmdir /S /Q processing\crprober\x64
erase /A H processing\crprober\*.user
erase processing\crprober\*.aps

rmdir /S /Q tests\Debug
rmdir /S /Q tests\Release
rmdir /S /Q "tests\Release LIB"
rmdir /S /Q tests\x64
erase /A H tests\*.user
erase tests\*.aps

rmdir /S /Q ipch