CALL nginx_shutdown.bat

CALL ws_stop.bat
python wait_for_ws_stop.py
DEL /F /Q ws.running.* 

CALL xs_stop.bat
python wait_for_ws_stop.py --filemask=xs
DEL /F /Q xs.running.* 

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_SiegeService1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_SiegeService2.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_GuildService1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_GuildService2.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_8801.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_8802.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Coordinator.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Coordinator#.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Coordinator#mono.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Bro.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_MockAggregator.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_ThriftAgent.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_StatisticAgent.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_MirrorDaemon1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_MirrorDaemon2.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_MirrorDaemon3.bat"

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_FriendService1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_FriendService2.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_PartyService1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_PartyService2.bat"

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - mongo.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_ChatService1.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_ChatService2.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_ChatService1#.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_ChatService2#.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_PwConnect.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_PwConnectFrontend.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Marketing.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Events.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_DummyPs.bat"

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - ws_Login.bat"

taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_8811.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_8812.bat"
taskkill /fi "WINDOWTITLE eq C:\WINDOWS\system32\cmd.exe - xs_Coordinator.bat"

CALL irc_stop.bat
CALL redis_shutdown.bat