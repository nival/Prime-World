@echo off

SET CLUSTER_NAME=%1

IF NOT .%CLUSTER_NAME%.==.. GOTO have_dir
echo Usage : setupSocialCluster CLUSTER_NAME
echo Example: setupSocialCluster PROD
echo .
REM echo ! 
REM echo ! must have valid ../cfg/Profiles/CLUSTER_NAME/ folder
REM echo ! 

echo Probable cluster names:
echo -----------------------
DIR /B .\..\Profiles\Social\*
echo -----------------------

GOTO end

:have_dir

:: Export configs from protected repository
del /F /Q /S .\..\cfg\profiles
svn export -r head https://svn.zzima.net/pw_cluster_configs/_deployments/%CLUSTER_NAME%/Social .\..\cfg\profiles\%CLUSTER_NAME% --force --no-auth-cache

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\batch\*.*
SET OUTPATH=.\..\batch
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\cfg\*.*
SET OUTPATH=.\..\cfg
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\config\*.*
SET OUTPATH=.\..\config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\mail\*.*
SET OUTPATH=.\..\mail
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\nginx\nginx.conf
SET OUTPATH=.\..\tools\nginx\conf\nginx.conf
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\redis\redis.conf
SET OUTPATH=.\..\tools\redis\64bit\redis.conf
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\cfg\Profiles\%CLUSTER_NAME%\services\marketing\templates\urlconf.js
SET OUTPATH=.\..\services\marketing\templates\urlconf.js
COPY /Y %SRCPATH% %OUTPATH%

:end
PAUSE
