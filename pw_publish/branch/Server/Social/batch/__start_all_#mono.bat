@echo launching caches and coordinator...
@CALL irc_stop.bat
@start /MIN mongo.bat
@start ws_Coordinator#mono.bat
@start /MIN ws_Bro.bat
@call python delay.py 2.0
@echo launching person server and thrift agent...
@start /MIN ws_FriendService1.bat
@start /MIN ws_FriendService2.bat
@start /MIN ws_PartyService1.bat
@start /MIN ws_PartyService2.bat
@start /MIN ws_ThriftAgent.bat
@start /MIN ws_StatisticAgent.bat
@start /MIN ws_PwConnect.bat
@echo launching Redis ...
@start /MIN redis_start.bat
@call python delay.py 2.0
@echo launching work servers...
@start /MIN ws_8801.bat
@start /MIN ws_8802.bat
@call irc_start.bat
@start /MIN ws_ChatService1.bat
@start /MIN ws_ChatService2.bat
@start /MIN ws_PwConnectFrontend.bat
@start /MIN ws_Marketing.bat
@start /MIN ws_Events.bat
@start /MIN ws_DummyPs.bat
@echo launching x_coordinator...
@call python delay.py 2.0
@start /MIN xs_Coordinator.bat
@call python delay.py 2.0
@echo launching x_servers...
@start /MIN xs_8811.bat
@start /MIN xs_8812.bat
@start /MIN ws_GuildService1.bat
@start /MIN ws_GuildService2.bat
@start /MIN ws_SiegeService1.bat
@start /MIN ws_SiegeService2.bat

@call python delay.py 5.0

@start /MIN ws_MirrorDaemon1.bat
@start /MIN ws_MirrorDaemon2.bat
@start /MIN ws_MirrorDaemon3.bat

@start /MIN ws_Login.bat

@call nginx_reload.bat
