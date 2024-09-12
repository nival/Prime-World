CALL xs_stop.bat
python wait_for_ws_stop.py --filemask=xs
DEL /F /Q xs.running.* 

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_8811.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_8812.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_Coordinator.bat"
