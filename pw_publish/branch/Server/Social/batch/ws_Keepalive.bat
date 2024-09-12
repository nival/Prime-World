cd ..
python -u client.load.py --server=127.0.0.1:88 --scenario=keepalive --num_threads=100 --num_queries=6 --log_file_prefix=logs/wsClient.log
pause