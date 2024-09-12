#!/usr/bin/env bash

red='\e[0;31m'
green='\e[0;32m'
yellow='\e[1;33m'
NC='\e[0m' # No Color
echo -e "${green}\nstop...${NC}\n"

cd ..

if [ -f venv/bin/activate ];
then
   echo "Use venv"
   . venv/bin/activate
else
   echo "Not use venv"
fi

#echo -e "${red}\nstop sysyem service...${NC}\n"
#/etc/init.d/mongodb stop
#/etc/init.d/mysql stop
#/etc/init.d/redis-server stop
if [ -n "$1" ] && [ $1 == 'n' ]
then
  echo "stop nginx..."
  #nginx -c pw.conf
  ./linux/ngstop.sh
else
  echo 'skip stop nginx'
fi

echo -e "${red}\nstop PW service...${NC}\n"
/etc/init.d/pw-coordinator stop
/etc/init.d/pw-coordinator# stop

sleep 1

echo -e "${green}stopping services...${NC}\n"

/etc/init.d/pw-bro stop

# stop /MIN ws_FriendService1.bat
# stop /MIN ws_FriendService2.bat
/etc/init.d/pw-friends stop

# stop /MIN ws_PartyService1.bat
# stop /MIN ws_PartyService2.bat
/etc/init.d/pw-party stop

# stop /MIN ws_ThriftAgent.bat
/etc/init.d/pw-thrift stop

# stop /MIN ws_StatisticAgent.bat
/etc/init.d/pw-statistic stop

# stop /MIN ws_PwConnect.bat
/etc/init.d/pw-connect stop

# stop /MIN xs_Coordinator.bat
/etc/init.d/pw-xcoordinator stop

# ws ws_8801 ws_8802
# cd linux/ && ./ws_8801.sh && ./ws_8802.sh && scd ..
# stop /MIN ws_8801.bat
# stop /MIN ws_8802.bat
/etc/init.d/pw-ws stop

# call irc_stop.bat
/etc/init.d/inspircd stop
#echo -e "${green}python irc.py --stop${NC}\n"
#cd linux/  && python irc_linux.py --stop
#cd ..

# stop /MIN ws_ChatService1.bat
# stop /MIN ws_ChatService2.bat
/etc/init.d/pw-chat stop

# stop /MIN ws_PwConnectFrontend.bat
/etc/init.d/pw-cf stop

# stop /MIN ws_Marketing.bat
/etc/init.d/pw-ms stop

# stop /MIN xs_8811.bat
# stop /MIN xs_8812.bat
/etc/init.d/pw-xs stop

# stop /MIN ws_GuildService1.bat
# stop /MIN ws_GuildService2.bat
/etc/init.d/pw-guild stop

# stop /MIN ws_MirrorDaemon1.bat
/etc/init.d/pw-mirror stop

# stop /MIN ws_Login.bat
/etc/init.d/pw-login stop

# stop /MIN ws_Events.bat
/etc/init.d/pw-es stop

# stop /MIN ws_DummyPs.bat
#python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsDummyPs.log --config=../../cfg/dummy_ps.cfg

# stop siege
/etc/init.d/pw-siege stop

# stop status
/etc/init.d/pw-status stop

# stop pw-dummyps
/etc/init.d/pw-dummyps stop

#ISSETLOGS = find . -type f -name "*.log" | wc -l
if [ -f logs/run/pw-coordinator.log.run ]
then
    PATHTMP="logs_history/stop_at_`date +'%m-%d-%y-%T'`"
    echo -e "${green}move log $(pwd)/logs to $PATHTMP ${NC}\n"
    mkdir -p $PATHTMP $PATHTMP/run
    find logs/ -maxdepth 1 -type f -exec mv {} $PATHTMP \;
    find logs/run -maxdepth 1 -type f -exec mv {} $PATHTMP/run \;
else
   echo "logs empty..."
fi


mkdir -p logs/run
