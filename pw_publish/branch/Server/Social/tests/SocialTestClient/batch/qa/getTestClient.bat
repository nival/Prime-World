echo "Download test clients".

SET REVISION_SOCIAL=HEAD
SET REVISION_PVX=HEAD

IF NOT .%1.==.. SET REVISION_SOCIAL=%1
IF NOT .%2.==.. SET REVISION_PVX=%2

SET ROOT_DIR=%~dp0
SET PVXTESTCLIENT_DIR=%ROOT_DIR%PvXTestClient
SET SOCIALTESTCLIENT_DIR=%ROOT_DIR%SocialTestClient
SET SVN_ROOT=https://svn.zzima.net/pw_publish/r1101/Server

:: Export files from protected repository
del /F /Q /S %PVXTESTCLIENT_DIR%
del /F /Q /S %SOCIALTESTCLIENT_DIR%

svn export -r %REVISION_SOCIAL% %SVN_ROOT%/Social/tests/SocialTestClient %SOCIALTESTCLIENT_DIR% --force --no-auth-cache
svn export -r %REVISION_SOCIAL% %SVN_ROOT%/Social/MM.py %SOCIALTESTCLIENT_DIR%\MM.py --force --no-auth-cache
svn export -r %REVISION_SOCIAL% %SVN_ROOT%/Social/party_const.py %SOCIALTESTCLIENT_DIR%\party_const.py --force --no-auth-cache
svn export -r %REVISION_SOCIAL% %SVN_ROOT%/Social/version.py %SOCIALTESTCLIENT_DIR%\version.py --force --no-auth-cache
svn export -r %REVISION_SOCIAL% %SVN_ROOT%/Social/base %SOCIALTESTCLIENT_DIR%\base --force --no-auth-cache

svn export -r %REVISION_PVX% %SVN_ROOT%/PvX/tests/GameTestClient %PVXTESTCLIENT_DIR% --force --no-auth-cache
