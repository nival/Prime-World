cd ..
python main.py --scenario=load_guest_gtc --game="/Maps/Multiplayer/PFmap/Training.ADMPDSCR" --clients=100 --threads=50 --client=C:\Work\pw-trunk\Src\Game\PF\Tests\GameTestClient\GameTestClientApp.auto\debug\ --client_exe=GameTestClientApp.exe --game_duration=15.0 --session_key_dir=C:\Work\Tornado\tornado.clean\tests\SocialTestClient\gtc_session_keys\ --verbose=2 --login=http://pw.nivalnetwork.com:88 --ping_wait=5.0 --period=0.3 --loglevel=warning --send_timeout=30.0 --logfile=guest.PWN.log 
pause
