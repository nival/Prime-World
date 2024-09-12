@echo off
set PYTHON_PATH=
for %%I in ("python.exe") do set PYTHON_PATH=%%~dp$PATH:I
if NOT "%PYTHON_PATH%" == "" goto check_python_version
echo python.exe not found in PATH variable
goto exit
:check_python_version
"%PYTHON_PATH%\python.exe" -V 2>pyver.txt
find "Python 2.6" pyver.txt > NUL
set PY26=%ERRORLEVEL%
del pyver.txt
if %PY26% == 0 goto start_install
echo python should be version 2.6.x
:start_install
cd /d "%~dp0"
cd .\..\vendor\win32
MySQL-python-1.2.3c1.win32-py2.6.exe
pycurl-ssl-7.19.0.win32-py2.6.exe
Thrift-0.6.1.win32-py2.6.exe
cd .\..\suds
setuptools-0.6c11.win32-py2.6.exe
cd .\..\pymongo-src-1.10
python setup.py install
cd .\..\leporo-tornado-redis-e0fc1f3
python setup.py install
cd .\..\win32\argparse-1.2.1
python setup.py install
cd .\..\tools
copy .\ujson-1.8\_site_packages.win32\*.* "%PYTHON_PATH%\Lib\site-packages" /Y
:exit
@pause
