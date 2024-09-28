#!/usr/bin/env bash

red='\e[0;31m'
green='\e[0;32'
NC='\e[0m' # No Color
echo -e "${green}Start${NC}\n"

# echo launching caches and coordinator...
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

cd ../batch/
python irc.py --stop
cd ..

echo -e "\n\n"
read -p "start Memcached 1 .............   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup memcached -p 8901 -v -m 64 -c 1022 -u www-data 1>../logs/mc8901.log 2>../logs/mc8901.verb.log &
  echo $! > .pid
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start Memcached 1\n"
else
  echo 'exit'
  exit
fi

echo -e "\n\n"
read -p "start Memcached 2 .............   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup memcached -p 8902 -v -m 64 -c 1024 -u www-data 1>../logs/mc8902.log 2>../logs/mc8902.verb.log &
  echo $! > .pid
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start Memcached 2\n"
else
  echo 'exit'
  exit
fi

echo -e "\n\n"
read -p "start Mongo ................   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup mongod --dbpath ~/mongo/database 1> /dev/null 2>&1 &
  echo $! >> .pid
  sleep 1
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start Memcached 2\n"
else
  echo 'exit'
  exit
fi

cd ..

echo -e "\n\n"
read -p "start Coordinator ................   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup  python coordinator.py --port=8700 --log_file_prefix=logs/wsCoord.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  sleep 3
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start Coordinator\n"
else
  echo 'exit'
  exit
fi

echo -e "\n\n"
read -p "start Match maker ................   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup  python -u mock_matchmaker.py --port=8702 --log_level=info --log_file_prefix=logs/wsMockMatchmaker.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  sleep 2
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start Match maker \n"
else
  echo 'exit'
  exit
fi

echo -e "\n\n"
read -p "start WServer 1 ................   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup  python wserver.py --port=8801 --server_name=one --log_file_prefix=logs/ws1.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start WServer 1 \n"
else
  echo 'exit'
  exit
fi


echo -e "\n\n"
read -p "start WServer 2 ................   Yes/No/Skip/Exit: " -e input
if [ $input == 'Y' ]
then
  nohup  python wserver.py --port=8802 --server_name=two --log_file_prefix=logs/ws2.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start WServer 2\n"
else
  echo 'exit'
  exit
fi
