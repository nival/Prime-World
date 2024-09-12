@echo launching caches and coordinator...
@CALL irc_stop.bat
@start /MIN mongo.bat
@call python delay.py 3.0
@start /MIN ws_Coordinator.bat
@call python delay.py 10.0
@echo launching person server and thrift agent...
@start /MIN ws_FriendService1.bat
@call python delay.py 3.0
@start /MIN ws_FriendService2.bat
@call python delay.py 3.0
@start /MIN ws_PartyService1.bat
@call python delay.py 3.0
@start /MIN ws_PartyService2.bat
@call python delay.py 3.0
@start /MIN ws_ThriftAgent.bat
@call python delay.py 3.0
@start /MIN ws_StatisticAgent.bat
@call python delay.py 3.0
@start /MIN ws_PwConnect.bat
@call python delay.py 4.0
@echo launching Redis ...
@start /MIN redis_start.bat
@call python delay.py 2.0
@echo launching work servers...
@start /MIN ws_8801.bat
@call python delay.py 3.0
@start /MIN ws_8802.bat
@call python delay.py 3.0
@call irc_start.bat
@start /MIN ws_ChatService1.bat
@call python delay.py 2.0
@start /MIN ws_ChatService2.bat
@call python delay.py 2.0
@start /MIN ws_PwConnectFrontend.bat
@call python delay.py 2.0
@start /MIN ws_Marketing.bat
@call python delay.py 2.0
@start /MIN ws_Events.bat
@call python delay.py 2.0
@start /MIN ws_DummyPs.bat
@call python delay.py 2.0
@echo launching x_coordinator...
@start /MIN xs_Coordinator.bat
@call python delay.py 8.0
@echo launching x_servers...
@start /MIN xs_8811.bat
@call python delay.py 3.0
@start /MIN xs_8812.bat
@call python delay.py 3.0
@start /MIN ws_GuildService1.bat
@call python delay.py 1.0
@start /MIN ws_GuildService2.bat
REM @start /MIN ws_SiegeService1.bat
REM @start /MIN ws_SiegeService2.bat
@start /MIN ws_MirrorDaemon1.bat
@call python delay.py 2.0
@start /MIN ws_MirrorDaemon2.bat
@call python delay.py 2.0
@start /MIN ws_MirrorDaemon3.bat
@call python delay.py 2.0
@start /MIN ws_Login.bat
@call nginx_reload.bat

