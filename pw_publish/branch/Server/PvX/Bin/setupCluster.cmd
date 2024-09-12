@echo off

:: backup Profiles/*.cfg files
PUSHD .\..\Profiles
IF not exist backups mkdir backups
for %%i in (*.*) do  (
    if "%%~xi" == ".cfg" (
        copy %%i backups > nul
    )
)
POPD

SET CONFIGURATION_NAME=%1
SET CLUSTER_NAME=%2

IF NOT .%CONFIGURATION_NAME%.==.. GOTO have_cfg_name
GOTO usage 

:have_cfg_name
IF NOT .%CLUSTER_NAME%.==.. GOTO have_cluster_name
GOTO usage 

:have_cluster_name
:: Export configs from protected repository
if not exist .\..\profiles\server mkdir .\..\profiles\server
DEL /Q /S .\..\profiles\server\*.*
if not exist .\..\profiles\server\%CONFIGURATION_NAME% mkdir .\..\profiles\server\%CONFIGURATION_NAME%
svn export -r head https://svn.zzima.net/pw_cluster_configs/_deployments/%CONFIGURATION_NAME%/%CLUSTER_NAME% .\..\profiles\server\%CONFIGURATION_NAME%\%CLUSTER_NAME% --force --no-auth-cache

REM //// SET SRCPATH=.\..\Profiles\Server\%CLUSTER_NAME%\cluster.cfg
REM //// SET OUTPATH=.\..\Profiles\cluster.cfg
SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\*.cfg
SET OUTPATH=.\..\Profiles\
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Statistic.datasources.config
SET OUTPATH=.\..\Bin\Statistic.datasources.config
COPY /Y %SRCPATH% %OUTPATH%
SET OUTPATH=.\..\Utils\Statistic.datasources.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Statistic.networking.config
SET OUTPATH=.\..\Bin\Statistic.networking.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Statistic.events.config
SET OUTPATH=.\..\Bin\Statistic.events.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Monitoring.networking.config
SET OUTPATH=.\..\Bin\Monitoring.networking.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\dbconfiguration.cmd
SET OUTPATH=.\..\Bin\dbconfiguration.cmd
COPY /Y %SRCPATH% %OUTPATH%
SET OUTPATH=.\..\Utils\DataIntegration\dbconfiguration.cmd
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Web.datasources.config
SET OUTPATH=.\..\ClusterManagement\ControlCenter\Web.datasources.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Web.cluster.config
SET OUTPATH=.\..\ClusterManagement\ControlCenter\Web.cluster.config
COPY /Y %SRCPATH% %OUTPATH%

SET SRCPATH=.\..\Profiles\Server\%CONFIGURATION_NAME%\%CLUSTER_NAME%\Web.gmAccounting.config
SET OUTPATH=.\..\ClusterManagement\ControlCenter\Web.gmAccounting.config
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
DIR /B .\..\Profiles\Server\*
echo -----------------------

:end
PAUSE
