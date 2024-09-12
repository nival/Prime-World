cd ..
python main.py --scenario=load_login_keepalive --clients=40 --keepalive_count=10 --keepalive_period=1.0 --threads=20 --loglevel=warning --verbose=2 --login=http://127.0.0.1:88 --ping_wait=5.0 --period=0.3 --testkeypass=1237916993
pause