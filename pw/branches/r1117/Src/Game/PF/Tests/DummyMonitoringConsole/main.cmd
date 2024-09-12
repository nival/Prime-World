@echo off
..\..\..\..\..\Vendor\Thrift\thrift-0.6.0.exe --gen py ..\..\..\..\..\Tools\GMTools\MonitoringService\Thrift\MonitoringSummary.thrift
python main.py %*