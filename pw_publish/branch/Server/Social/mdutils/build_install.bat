python setup.py sdist
cd unwrapped
"C:\Program Files\7-Zip\7z.exe" e -y ../dist/mdutils-1.0.zip
python setup.py install
copy /Y "build\lib.win32-2.6\*.*" "../dist/build/lib.win32-2.6/"
PAUSE