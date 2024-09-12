copy /Y C:\Work\pw_lobby\SocialServer\config\ConfigData.py C:\Work\Tornado\tornado.clean\config\
@IF ERRORLEVEL 1 GOTO labelFAIL

copy /Y C:\Work\pw_lobby\SocialServer\friendsdata\Friend.py C:\Work\Tornado\tornado.clean\friendsdata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\friendsdata\FriendError.py C:\Work\Tornado\tornado.clean\friendsdata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\friendsdata\FriendsData.py C:\Work\Tornado\tornado.clean\friendsdata\
@IF ERRORLEVEL 1 GOTO labelFAIL

copy /Y C:\Work\pw_lobby\SocialServer\modeldata\Construction.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\ConstructionPosition.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\Hero.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\HeroStats.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\ModelData.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\ResourceTable.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\Talent.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\modeldata\Version.py C:\Work\Tornado\tornado.clean\modeldata\
@IF ERRORLEVEL 1 GOTO labelFAIL

copy /Y C:\Work\pw_lobby\SocialServer\party\PartyData.py C:\Work\Tornado\tornado.clean\party\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\party\PartyError.py C:\Work\Tornado\tornado.clean\party\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\party\PartyMember.py C:\Work\Tornado\tornado.clean\party\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\party\Person.py C:\Work\Tornado\tornado.clean\party\
@IF ERRORLEVEL 1 GOTO labelFAIL

copy /Y C:\Work\pw_lobby\SocialServer\testdata\AgregatorType.py C:\Work\Tornado\tornado.clean\testdata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\testdata\KeeperType.py C:\Work\Tornado\tornado.clean\testdata\
@IF ERRORLEVEL 1 GOTO labelFAIL
copy /Y C:\Work\pw_lobby\SocialServer\testdata\TestData.py C:\Work\Tornado\tornado.clean\testdata\
@IF ERRORLEVEL 1 GOTO labelFAIL


:labelFAIL
PAUSE