cd ..\thrift_pw\account_management
python -u client.test.py

@REM PAUSE 

@echo EXITING..
@ping -n 3 localhost:80 > null