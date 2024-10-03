@timeout /t 1 /nobreak  >nul 2>&1
@del PW_MiniLauncher.exe  >nul 2>&1
@ren PW_MiniLauncher_tmp.exe PW_MiniLauncher.exe  >nul 2>&1
@echo Launcher was updated  >nul 2>&1
@start PW_MiniLauncher.exe %1 >nul 2>&1