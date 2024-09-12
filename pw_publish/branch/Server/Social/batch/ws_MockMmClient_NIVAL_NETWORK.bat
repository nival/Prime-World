cd ..
cd tests
python -u async.load.py --server=pw.nivalnetwork.com:88 --num_threads=40 --num_queries=2 --log_level=info --log_file_prefix=../logs/wsMockMmClient.log
pause