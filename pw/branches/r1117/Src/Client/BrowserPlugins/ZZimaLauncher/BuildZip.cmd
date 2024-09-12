pushd
RD  /Q /S "C:\Documents and Settings\name.lastname\Local Settings\Application Data\Nival\"
cd .auto\%1
copy ..\..\NN.bmp 
del ZZimaLauncher.zip 
zip -D ZZimaLauncher.zip ZZimaLauncher.dll NewDelete.dll zlib1.dll NN.bmp
popd