@echo off
pushd ..\tools\redis\64bit
for /f "tokens=2" %%G in ('findstr /b port redis.conf') do set port=%%G
start redis-cli.exe -p %port% shutdown
popd
