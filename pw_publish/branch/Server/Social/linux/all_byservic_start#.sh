#!/usr/bin/env bash

red='\e[0;31m'
green='\e[0;32m'
yellow='\e[1;33m'
NC='\e[0m' # No Color
echo -e "${green}\nStart...${NC}\n"

cd ..

if [ -f venv/bin/activate ];
then
   echo -e "Use venv\n"
   . venv/bin/activate
else
   echo "Not use venv"
fi

echo -e "${red}\nStart sysyem service...${NC}\n"
/etc/init.d/mongodb start
/etc/init.d/mysql start
/etc/init.d/redis-server start
#nginx -c pw.conf
#/etc/init.d/nginx reload
#nginx -c pw.conf
if [ -n "$1" ] && [ $1 == 'n' ]
then
  echo "start nginx..."
  ./linux/nginx.sh
else
  echo 'skip start nginx'
fi

echo -e "${red}\nStart PW service...${NC}\n"
/etc/init.d/pw-coordinator# start

sleep 1

echo -e "${green}Launching services...${NC}\n"

/etc/init.d/pw-bro start

# start /MIN ws_FriendService1.bat
# start /MIN ws_FriendService2.bat
/etc/init.d/pw-friends start

# start /MIN ws_PartyService1.bat
# start /MIN ws_PartyService2.bat
/etc/init.d/pw-party start

# start /MIN ws_ThriftAgent.bat
/etc/init.d/pw-thrift start

# start /MIN ws_StatisticAgent.bat
/etc/init.d/pw-statistic start

# start /MIN ws_PwConnect.bat
/etc/init.d/pw-connect start

# start /MIN xs_Coordinator.bat
/etc/init.d/pw-xcoordinator start

# ws ws_8801 ws_8802
#cd linux/ && ./ws_8801.sh && ./ws_8802.sh && scd ..
# start /MIN ws_8801.bat
# start /MIN ws_8802.bat
/etc/init.d/pw-ws start

# call irc_start.bat
/etc/init.d/inspircd start
#echo -e "${green}python irc.py --start${NC}\n"
#cd linux/  && python irc_linux.py --start
#cd ..

# start /MIN ws_ChatService1.bat
# start /MIN ws_ChatService2.bat
/etc/init.d/pw-chat start

# start /MIN ws_PwConnectFrontend.bat
/etc/init.d/pw-cf start

# start /MIN ws_Marketing.bat
/etc/init.d/pw-ms start

# start /MIN xs_8811.bat
# start /MIN xs_8812.bat
/etc/init.d/pw-xs start

# start /MIN ws_GuildService1.bat
# start /MIN ws_GuildService2.bat
/etc/init.d/pw-guild start

# start /MIN ws_MirrorDaemon1.bat
/etc/init.d/pw-mirror start

# start /MIN ws_Events.bat
/etc/init.d/pw-es start

# start /MIN ws_DummyPs.bat
#python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsDummyPs.log --config=../../cfg/dummy_ps.cfg

# start /MIN ws_Login.bat
/etc/init.d/pw-login start

# start siege
/etc/init.d/pw-siege start

# start pw-dummyps
/etc/init.d/pw-dummyps start

# start status
#/etc/init.d/pw-status start
