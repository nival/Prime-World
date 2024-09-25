call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"

rem echo %path%

rem set

nmake /f makefile.vc mode=dll VC=9
