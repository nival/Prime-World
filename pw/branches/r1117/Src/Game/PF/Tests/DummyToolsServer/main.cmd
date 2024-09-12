@echo off
..\..\..\..\..\Vendor\Thrift\thrift-0.9.1.exe --gen py ..\..\Tools\Management\ClusterLib\ClusterManagementAPI.thrift
..\..\..\..\..\Vendor\Thrift\thrift-0.9.1.exe --gen py ..\..\Tools\Management\AccountLib\AccountManagementAPI.thrift
..\..\..\..\..\Vendor\Thrift\thrift-0.9.1.exe --gen py ..\..\..\..\..\Tools\GMTools\MonitoringLib\Monitoring.thrift
python main.py %*