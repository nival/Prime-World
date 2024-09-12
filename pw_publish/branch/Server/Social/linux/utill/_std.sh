# на обычном http-порту (:80)
# NB: nohup niceCMD ... to change CMD priority
cd ../../
python wserver.py --port=8801 --server_name=one --coordinator=localhost:8700 --sql=none --log_file_prefix=logs/ws1.log
