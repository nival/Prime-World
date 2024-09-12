cd ..\
.\vendor\x64\MySQL-python-1.2.3.win-amd64-py2.6.exe
.\vendor\x64\thrift-0.8.0.win-amd64-py2.6
.\vendor\x64\pycurl-7.19.0.win-amd64-py2.6
.\vendor\x64\setuptools-0.6c12dev.win-amd64-py2.6


cd .\vendor\pymongo-src-1.10\
setup.py install
cd ..\..\
.\vendor\x64\Base-12.1.1.win-amd64-py2.6.exe
cd .\vendor\leporo-tornado-redis-e0fc1f3\
setup.py install

copy ..\..\vendor\x64\ujson-1.8\ujson.pyd C:\Python26\Lib

cd ..\..\vendor\win32\argparse-1.2.1\
setup.py install

cd ..\..\..\doc\
