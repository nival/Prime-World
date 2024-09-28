#!/usr/bin/env bash

red='\e[0;31m'
green='\e[0;32m'
yellow='\e[1;33m'
NC='\e[0m' # No Color
echo -e "${green}\nStart...${NC}\n"

STATUS=""
Memcached1=8901
Memcached2=8902
Mongo=28017
Coordinator=8700
MatchMaker=8702
FiendService1=8714
FiendService2=8715

WServer1=8801
WServer2=8802

# CALL irc_stop.bat
# start /MIN mongo.bat

# start /MIN ws_Coordinator.bat
# echo waiting 1 second...

# echo launching person server and thrift agent...

# start /MIN ws_FriendService1.bat
# start /MIN ws_FriendService2.bat

# start /MIN ws_PartyService1.bat
# start /MIN ws_PartyService2.bat

# start /MIN ws_ThriftAgent.bat
# start /MIN ws_StatisticAgent.bat

# start /MIN ws_PwConnect.bat

# echo launching Redis ...
# start redis_start.bat
# echo waiting 1 second...

# echo launching work servers...

# start /MIN ws_8801.bat
# start /MIN ws_8802.bat

# call irc_start.bat

# start /MIN ws_ChatService1.bat
# start /MIN ws_ChatService2.bat
# start /MIN ws_PwConnectFrontend.bat
# start /MIN ws_Marketing.bat
# start /MIN ws_Events.bat
# start /MIN ws_DummyPs.bat

# echo launching x_coordinator...
# start /MIN xs_Coordinator.bat
# echo waiting 1 second...
# echo launching x_servers...

# start /MIN xs_8811.bat
# start /MIN xs_8812.bat
# start /MIN ws_GuildService1.bat
# start /MIN ws_GuildService2.bat
# start /MIN ws_MirrorDaemon1.bat
# start /MIN ws_Login.bat

# call nginx_reload.bat

echo -e "${red} launching caches and coordinator... ${NC}\n"

cd ../batch/ && echo -e "pwd: ${yellow}${PWD}${NC}\n"
echo -e "${green} irc.py --stop ${NC}\n"
python irc.py --stop
cd ../linux/ && echo -e "pwd: ${yellow}${PWD}${NC}\n"

STATUS="" && netstat -an | grep $Memcached1 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "${green}Memcached1: $Memcached2 already running ${NC}\n"
else
  nohup memcached -p 8901 -v -m 64 -c 1022 -u www-data 1>../logs/mc8901.log 2>../logs/mc8901.verb.log &
  echo $! >> .pid
  echo -e "${red}${Memcached1} is start...${NC}\n"
fi

STATUS="" && netstat -an | grep $Memcached2 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "${green}Memcached2: $Memcached2 already running ${NC}\n"
else
  nohup memcached -p $Memcached2 -v -m 64 -c 1022 -u www-data 1>../logs/mc8902.log 2>../logs/mc8902.verb.log &
  echo $! >> .pid
  echo -e "${red}${Memcached2} is start...${NC}\n"
fi

STATUS="" && netstat -an | grep $Mongo > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "Mongo: $Mongo already running\n"
else
  nohup mongod --dbpath ~/mongo/database 1> /dev/null 2>&1 &
  echo $! >> .pid
  echo -e "${red}${Mongo} is start...${NC}\n"
fi

cd .. && echo -e "pwd: ${yellow}${PWD}${NC}\n"

STATUS="" && netstat -an | grep $Coordinator > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "Coordinator: $Coordinator already running\n"
else
  nohup python -u coordinator.py --port=$Coordinator --log_level=info --log_file_prefix=logs/wsCoord.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  sleep 3
fi

cd linux && echo -e "pwd: ${yellow}${PWD}${NC}\n"

echo -e "\n"
STATUS="" && netstat -an | grep $MatchMaker > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "MatchMaker: $MatchMaker already running\n"
else
  echo $(pwd)
  nohup python -u mock_matchmaker.py --port=$MatchMaker --log_level=info --log_file_prefix=logs/wsMockMatchmaker.log 1> /dev/null 2>&1 &
  echo $! >> .pid
  sleep 2
fi

cd ..

echo -e "\n"
STATUS="" && netstat -an | grep $FiendService1 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "FiendService1: $FiendService1 already running\n"
else
  echo $(pwd)
  nohup python -u friend_service.py --port=$FiendService1 --log_level=info --server_name=friends1 --server_id="-21" --log_file_prefix=logs/wsFriendService1.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  sleep 2
fi

echo -e "\n"
STATUS="" && netstat -an | grep $FiendService2 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "FiendService2: $FiendService2 already running\n"
else
  echo $(pwd)
  nohup python -u friend_service.py --port=$FiendService2 --log_level=info --server_name=friends2 --server_id="-22" --log_file_prefix=logs/wsFriendService2.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  sleep 2
fi

exit
echo "***************************************"

echo -e "\n"
STATUS="" && netstat -an | grep $WServer1 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "WServer1: $WServer1 already running\n"
else
  nohup python wserver.py --port=$WServer1 --server_name=one --log_file_prefix=logs/ws1.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
fi

echo -e "\n"
STATUS="" && netstat -an | grep $WServer2 > /dev/null && STATUS="OK"
if [ -n "$STATUS" ]
then
  echo -e "WServer2: $WServer2 already running\n"
else
  nohup  python wserver.py --port=$WServer2 --server_name=two --log_file_prefix=logs/ws2.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
fi
