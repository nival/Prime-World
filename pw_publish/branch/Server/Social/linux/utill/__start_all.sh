echo -n 'Memcached 1 ... '
nohup memcached -p 8901 -v -m 64 -c 1022 1>../logs/mc8901.log 2>../logs/mc8901.verb.log &
echo $! > .pid
echo 'OK'

echo -n 'Memcached 2 ... '
nohup memcached -p 8902 -v -m 64 -c 1024 1>../logs/mc8902.log 2>../logs/mc8902.verb.log &
echo $! >> .pid
echo 'OK'

echo -n 'Mongo ... '
nohup ~/mongo/bin/mongod --dbpath ~/mongo/database 1> /dev/null 2>&1 &
echo $! >> .pid
sleep 1
echo 'OK'

echo -n 'Coordinator ...'
cd ~/pw
nohup sudo python ~/pw/coordinator.py --port=8700 --log_file_prefix=logs/wsCoord.log 1> /dev/null 2>&1 &
echo $! >> ~/pw/linux/.pid
sleep 3
echo 'OK'

echo -n 'Match maker ...'
nohup sudo python -u ~/pw/mock_matchmaker.py --port=8702 --log_level=info --log_file_prefix=logs/wsMockMatchmaker.log 1> /dev/null 2>&1 &
echo $! >> ~/pw/linux/.pid
sleep 2
echo 'OK'

echo -n 'WServer 1 ...'
nohup sudo python ~/pw/wserver.py --port=8801 --server_name=one --log_file_prefix=logs/ws1.log 1> /dev/null 2>&1 &
echo $! >> ~/pw/linux/.pid
echo 'OK'

echo -n 'WServer 2 ...'
nohup sudo python ~/pw/wserver.py --port=8802 --server_name=two --log_file_prefix=logs/ws2.log 1> /dev/null 2>&1 &
echo $! >> ~/pw/linux/.pid
echo 'OK'
