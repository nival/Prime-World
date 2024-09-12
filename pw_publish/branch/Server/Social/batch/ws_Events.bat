pushd ..\services\events
python -u main.py --loglevel=debug --logrotate=60 --log=../../logs/wsEvents.log --config=../../cfg/events.cfg
popd
pause