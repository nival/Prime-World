//Run tests
@echo on

SET SERVER_HOST_PORT=http://ru.pwcastle.nivalnetwork.com:88

IF not .%1. == .. SET SERVER_HOST_PORT=%1

SET ROOT_DIR=%~dp0
SET PVXTESTCLIENT_DIR=%ROOT_DIR%PvXTestClient
SET SOCIALTESTCLIENT_DIR=%ROOT_DIR%SocialTestClient
rem SET PYTHON_DIR=%SOCIALTESTCLIENT_DIR%/vendor/Python26/

rem SET PATH=%PYTHON_DIR%;%PATH%

cd %SOCIALTESTCLIENT_DIR%
python main.py --scenario=load_guest_gtc --game=train --clients=1 --threads=1 --client=%PVXTESTCLIENT_DIR% --client_exe=GameTestClientApp.exe --game_duration=15.0 --session_key_dir=%PVXTESTCLIENT_DIR% --loglevel=info --verbose=2 --login=%SERVER_HOST_PORT% --ping_wait=5.0 --period=0.3
pause

cd %ROOT_DIR%