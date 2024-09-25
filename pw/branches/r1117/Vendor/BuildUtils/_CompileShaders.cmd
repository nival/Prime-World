cd %~dp0

cd ../../Bin
..\Src\%1\ShaderCompiler.exe ../Src/Render/Shaders/MaterialSpec.xml --out../Data/Shaders/UberShaders/ %2 %3 %4

:Finish
cd ../Vendor/BuildUtils
