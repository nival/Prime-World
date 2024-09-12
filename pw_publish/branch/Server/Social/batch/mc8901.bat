REM -p port :8901
REM -vv debug (very verbose) or -v (not really verbose)
REM -m 64 MB memory
REM -c 1024 connections

cd ..\tools\memcache
memcached -p 8901 -v -m 64 -c 1024

REM "-M" option: NEVER THROW AWAY DATA (return error when exhausted)
