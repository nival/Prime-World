pushd ..\services\pwc_frontend
python -u main.py --loglevel=debug --log=../../logs/wsPwConnectFrontend.log --config=../../cfg/pwc_frontend.cfg
popd
pause