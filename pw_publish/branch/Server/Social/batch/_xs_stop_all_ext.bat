@CALL _xs_stop_all.bat

set NEW_FL=x_stop_at_%date:~6,4%_%date:~3,2%_%date:~0,2%_%time:~0,2%.%time:~3,2%
md ..\logs\%NEW_FL%
move ..\logs\xs* ..\logs\%NEW_FL%

pause
