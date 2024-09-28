@echo off

set index=%1

set count=250
set login_addr=SITE.com:35071
set soc_url=http://SITE.com
set mm_type=Maps/Multiplayer/PFmap/PVP.ADMPDSCR
set game_dur=180
set sleep_sec=10

echo Starting %count% GTC #%index% 
start GameTestClientApp.exe -l %login_addr% -s prodemu --scenarioduration %game_dur% -m 15 -c %count% --socialmmtype %mm_type% --gatewayurl %soc_url%:34090 --partyfreq 0
sleep %sleep_sec%

echo Starting %count% GTC #%index%
start GameTestClientApp.exe -l %login_addr% -s prodemu --scenarioduration %game_dur% -m 15 -c %count% --socialmmtype %mm_type% --gatewayurl %soc_url%:34091 --partyfreq 0
sleep %sleep_sec%
