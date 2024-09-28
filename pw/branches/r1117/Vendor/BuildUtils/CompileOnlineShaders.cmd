@echo off
pushd ..\..\Src\Render\OnlineShaders

for %%i in (*.vsh) do (
rem    echo.
rem    echo ###############################################################################
    echo ## vs: %%~nxi
    del ..\..\..\Data\Shaders\OnlineShaders\%%~ni.vsb
    ..\..\..\Vendor\BuildUtils\fxc.exe /nologo /Tvs_3_0 /EVS_main /Fo..\..\..\Data\Shaders\OnlineShaders\%%~ni.vsb %%i
)

for %%i in (*.psh) do (
rem    echo.
rem    echo ###############################################################################
    echo ## ps: %%~nxi
    del ..\..\..\Data\Shaders\OnlineShaders\%%~ni.psb
    ..\..\..\Vendor\BuildUtils\fxc.exe /nologo /Tps_3_0 /EPS_main /Fo..\..\..\Data\Shaders\OnlineShaders\%%~ni.psb %%i
)


for %%i in (*.pss) do (
rem    echo.
rem    echo ###############################################################################
    echo ## ps: %%~nxi
    del ..\..\..\Data\Shaders\OnlineShaders\%%~ni.psb
    ..\..\..\Vendor\BuildUtils\fxc.exe /nologo /Tps_3_0 /EPS_main /Gfa /Fo..\..\..\Data\Shaders\OnlineShaders\%%~ni.psb %%i
)

popd