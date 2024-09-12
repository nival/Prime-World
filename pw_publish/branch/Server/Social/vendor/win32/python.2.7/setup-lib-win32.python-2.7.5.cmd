@echo off
:start_all_install
set PYTHON_PATH=
for %%I in ("python.exe") do set PYTHON_PATH=%%~dp$PATH:I
if NOT "%PYTHON_PATH%" == "" goto check_python_version
echo python.exe not found in PATH variable
echo install python-2.7.5.msi
.\lib\python-2.7.5.msi
goto start_all_install
:check_python_version
"%PYTHON_PATH%\python.exe" -V 2>pyver.txt
find "Python 2.7" pyver.txt > NUL
set PY27=%ERRORLEVEL%
del pyver.txt
if %PY27% == 0 goto start_install
echo python should be version 2.7.x
echo install python-2.7.5.msi
.\lib\python-2.7.5.msi
:start_install
echo install pip
python get-pip.py
echo install lib by pip
pip install -r requirements.2.7.5.txt
echo install lib
.\lib\MySQL-python-1.2.3.win32-py2.7.exe
.\lib\pycurl-7.19.0.5.win32-py2.7.msi
.\lib\ujson-1.33.win32-py2.7.exe
:exit
@pause