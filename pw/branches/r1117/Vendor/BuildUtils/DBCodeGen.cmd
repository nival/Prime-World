set err=1

if "%1" == "" goto showUsage
if "%2" == "" goto showUsage
if "%3" == "" goto showUsage
if "%4" == "" goto showUsage
if "%5" == "" goto showUsage

set materials="--materials"
if NOT [%6]==[] set materials="--materials=%6"

copy %~dp0\DBCodeGen.exe DBCodeGen_Copy.exe /Y
echo %2 --solution="%1" --project="%2.DBTypes" %materials% --hash="%3" --hash=%4/%2Hash.h --hash=%5/%2Hash.cs
DBCodeGen_Copy.exe %2 --solution="%1" --project="%2.DBTypes" %materials% --hash="%3" --hash=%4/%2Hash.h --hash=%5/%2Hash.cs
if ERRORLEVEL 0 set err=0
@echo off
@echo off
@echo off
@echo off
@echo off
@echo off
@echo off
@echo off
del DBCodeGen_Copy.exe

goto exit

:showUsage
echo dbcodegen.cmd [solution_file] [source_project] [data_hash_path] [cpp_hash_project] [cs_hash_project] [[materials_project]]

:exit
exit %err%