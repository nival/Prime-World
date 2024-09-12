#!/usr/bin/env bash

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
  nohup sudo python coordinator.py --port=8700 --log_file_prefix=logs/wsCoord.log 1> /dev/null 2>&1 &
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
  nohup sudo python -u mock_matchmaker.py --port=8702 --log_level=info --log_file_prefix=logs/wsMockMatchmaker.log 1> /dev/null 2>&1 &
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
  nohup sudo python wserver.py --port=8801 --server_name=one --log_file_prefix=logs/ws1.log 1> /dev/null 2>&1 &
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
  nohup sudo python wserver.py --port=8802 --server_name=two --log_file_prefix=logs/ws2.log 1> /dev/null 2>&1 &
  echo $! >> linux/.pid
  echo 'OK'
elif  [ $input == 'N' -o $input == 'S' ]
then
  echo "skip start WServer 2\n"
else
  echo 'exit'
  exit
fi
