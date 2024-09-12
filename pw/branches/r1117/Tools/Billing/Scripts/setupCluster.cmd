@echo off

SET CONFIGURATION_NAME=%1
SET CLUSTER_NAME=%2

IF NOT .%CONFIGURATION_NAME%.==.. GOTO have_cfg_name
GOTO usage 

:have_cfg_name
IF NOT .%CLUSTER_NAME%.==.. GOTO have_cluster_name
GOTO usage 

:have_cluster_name
:: Export configs from protected repository
if not exist .\..\configs mkdir .\..\configs
DEL /Q /S .\..\configs\*.*
if not exist .\..\configs\%CONFIGURATION_NAME% mkdir .\..\configs\%CONFIGURATION_NAME%
svn export -r head https://svn.zzima.net/pw_cluster_configs/_deployments/%CONFIGURATION_NAME%/%CLUSTER_NAME% .\..\configs\%CONFIGURATION_NAME%\%CLUSTER_NAME% --force --no-auth-cache

SET SRCPATH=.\..\configs\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Web.config
SET OUTPATH=.\..\WebApp\Web.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\configs\%CONFIGURATION_NAME%\%CLUSTER_NAME%\dbconfiguration.cmd
SET OUTPATH=dbconfiguration.cmd
COPY /Y %SRCPATH% %OUTPATH%

GOTO end

:usage
echo Usage : setupCluster CONFIGURATION_NAME CLUSTER_NAME 
echo Example: setupCluster trunk_pwn88 pvx_mm
echo .
REM echo ! 
REM echo ! must have valid ../Profiles/Server/CLUSTER_NAME/cluster.cfg file
REM echo ! 

echo Probable cluster names:
echo -----------------------
DIR /B .\..\configs\*
echo -----------------------

:end
PAUSE
