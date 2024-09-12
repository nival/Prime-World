namespace csharp MonitoringLib
namespace cpp Monitoring.Thrift

enum PerfCounterType {
  Bool         = 1,  // 0,1
  Byte         = 2,
  Int16        = 3,
  UInt16       = 4,
  Int32        = 5,
  UInt32       = 6,
  Int64        = 7,
  UInt64       = 8,
  Float        = 9,  // 99.999E+99
  Double       = 10, // 99.999E+99
  String       = 11, // UTF8
}

struct PerfCounterInfo {
  1: string name,
  2: i32 period
}

struct PerfCounterSample {
  1: string name,
  2: PerfCounterType type,
  3: string value,
  4: i32 timestamp
}

service Monitoring {
  list<PerfCounterInfo> GetPerfCounters(),
  
  i32 RegisterPerfCounters(1: list<PerfCounterInfo> counters),
  i32 UnregisterPerfCounters(1: list<string> counters),
  i32 UnregisterAllPerfCounters(),

  list<PerfCounterInfo> GetRegisteredPerfCounters(),
  list<PerfCounterSample> GetPerfCounterSamples(),
}
