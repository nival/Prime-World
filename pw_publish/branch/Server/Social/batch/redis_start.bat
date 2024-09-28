@echo off
pushd ..\tools\redis\64bit
start /B redis-server.exe redis.conf
popd
exit
