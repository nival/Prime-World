::env builtins                 
::set dir_list_env=accessibility display events filters system ui utils text sound
set dir_list_env=display
for %%i in (%dir_list_env%) do CALL _build_env.bat %%i

::simple builtins
::set dir_list=geom net xml testing
::for %%i in (%dir_list%) do CALL _compile_file.bat %%i.as
::for %%i in (%dir_list%) do CALL _generate_headers.bat %%i.abc

::special calls for ByteArray
::CALL _compile_file.bat ByteArray_builtin.as
::CALL _generate_headers_without_BA.bat ByteArray_builtin.abc

CALL _copy_and_clear.bat