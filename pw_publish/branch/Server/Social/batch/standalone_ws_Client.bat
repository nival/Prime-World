cd ..
python -u client.load.py --scenario=keepalive --server=127.0.0.1:8801 --num_threads=10 --num_queries=2 --log_file_prefix=logs/wsClient.log
pause