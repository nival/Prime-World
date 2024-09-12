cd ..
cd tests
python -u async.load.py --server=127.0.0.1:8703 --scenario=aggregator --num_threads=2 --log_level=debug --log_file_prefix=../logs/wsMockAggClient.log
pause