@echo off
..\..\..\..\..\..\Vendor\Thrift\thrift-0.9.1.exe --gen py ..\ClusterLib\ClusterManagementAPI.thrift
python main.py %*