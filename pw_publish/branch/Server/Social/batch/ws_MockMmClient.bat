cd ..
cd tests
python -u async.load.py --server=127.0.0.1:88 --num_threads=2 --log_level=info --log_file_prefix=../logs/wsMockMmClient.log
pause