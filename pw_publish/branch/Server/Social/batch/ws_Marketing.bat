pushd ..\services\marketing
python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsMarketing.log --config=../../cfg/marketing.cfg
popd
pause