# REM -p port :8901
# REM -vv debug (very verbose) or -v (not really verbose)
# REM -m 64 MB memory
# REM -c 1024 connections
memcached -p 8901 -v -m 64 -c 1022 1>../logs/mc8901.log 2>../logs/mc8901.verb.log

# REM "-M" option: NEVER THROW AWAY DATA (return error when exhausted)
