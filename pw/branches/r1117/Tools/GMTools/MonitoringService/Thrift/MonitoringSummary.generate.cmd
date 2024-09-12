..\..\..\..\Vendor\Thrift\thrift-0.6.0.exe -gen csharp -o %~dp0 MonitoringSummary.thrift
..\..\..\..\Vendor\Thrift\thrift-0.6.0.exe -gen csharp -o %~dp0..\..\..\..\Src\Game\PF\Tools\Management\MonitoringSummaryLib\ MonitoringSummary.thrift
..\..\..\..\Vendor\Thrift\thrift-0.6.0.exe -gen csharp -o %~dp0..\..\..\..\Src\Game\PF\Tools\Management\DummyMonitoringService\Thrift\ MonitoringSummary.thrift