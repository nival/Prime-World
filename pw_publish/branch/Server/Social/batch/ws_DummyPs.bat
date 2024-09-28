pushd ..\services\dummy_ps
python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsDummyPs.log --config=../../cfg/dummy_ps.cfg
popd
pause