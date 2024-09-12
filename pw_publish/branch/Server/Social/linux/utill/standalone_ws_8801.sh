# на обычном http-порту (:80)
# NB: nohup niceCMD ... to change CMD priority
cd ../../
python wserver.py --port=3306 --server_name=one --coordinator=none --mc=none --sql=none --log_file_prefix=logs/ws1.log

