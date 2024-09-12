cd ..
cd tests
python -u async.load.py --server=ec2-50-17-51-230.compute-1.amazonaws.com:88 --num_threads=20 --num_queries=2 --log_level=info --log_file_prefix=../logs/wsMockMmClient.log
pause