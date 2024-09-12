using System;
using System.Collections.Generic;

namespace MonitoringService
{
  public class MonitoringContext
  {
    public Uri MonitoringUrl { get; set; }
    public Uri StatisticServiceUrl { get; set; }
    public string MonitoringSummaryUrlPrefix { get; set; }

    public Dictionary<string, PerfCounterRequest> Requests { get; set; }
    public int StatPeriod { get; set; }

    public MonitoringContext()
    {
      Requests = new Dictionary<string, PerfCounterRequest>();
    }
  }
}