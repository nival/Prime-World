@echo off

svn update ..\..\DBCodeGenExternals\Src\Game\PF\Tools

@Echo Generating Account API
pushd account_management
call api.build.bat
popd

@Echo Generating Statistics API
pushd statistics
call api.build.bat
popd

@Echo Generating ServerInfo API
pushd serverinfo
call api.build.bat
popd
