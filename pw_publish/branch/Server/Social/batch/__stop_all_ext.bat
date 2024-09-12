@CALL __stop_all.bat

set now=%DATE: =0%_%TIME: =0%
set now=%now::=.%
set NEW_DIR=stop_at_%now:~0,16%
md ..\logs\%NEW_DIR%
move ..\logs\*.* ..\logs\%NEW_DIR%

rem pause