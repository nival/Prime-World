call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"

rem echo %path%

rem set

nmake /f makefile.vc USE_SSPI=no mode=static VC=9 USE_IPV6=no USE_IDN=no

rem Debug
nmake /f makefile.vc USE_SSPI=no mode=static VC=9 USE_IPV6=no USE_IDN=no DEBUG=yes
