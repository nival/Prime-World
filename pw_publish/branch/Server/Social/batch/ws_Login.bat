pushd ..\services\login
python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsLogin.log --config=../../cfg/login.cfg
popd
pause