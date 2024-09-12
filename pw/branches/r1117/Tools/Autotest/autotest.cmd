@ECHO OFF
call C:\Autotest\Autotest\StopPVX.bat
py\autotest.py 2>start_logz\autotest-err.txt
