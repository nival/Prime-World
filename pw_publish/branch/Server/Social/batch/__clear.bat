@echo off

@call __stop_all.bat

rem echo Deleting logs
del /Q /A-H ..\logs\*.*

del /Q /A-H *.log

rem echo Deleting mongodb database
FOR /F %%d IN ('dir ..\tools\mongodb\database\ /B /AD') DO IF NOT %%d==.svn RMDIR /S /Q ..\tools\mongodb\database\%%d
del /Q /A-H ..\tools\mongodb\database\*.*

rem echo Deleting nginx temp files
FOR /F %%d IN ('dir ..\tools\nginx\temp\ /B /AD') DO IF NOT %%d==.svn RMDIR /S /Q ..\tools\nginx\temp\%%d
del /Q /A-H ..\tools\nginx\temp\*.*

del /Q /A-H ..\tools\redis\64bit\*.rdb

rd /Q ..\tools\nginx\scgi_temp
rd /Q ..\tools\nginx\uwsgi_temp