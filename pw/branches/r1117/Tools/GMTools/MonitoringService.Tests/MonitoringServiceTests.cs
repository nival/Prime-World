using System.Linq;
using log4net;
using MonitoringLib;
using Moq;
using NUnit.Framework;

namespace MonitoringService.Tests
{
  [TestFixture]
  public class MonitoringServiceTests
  {
    [Test]
    public void RunAsyncTest()
    {
      var mockMonitoringProvider = new Mock<IMonitoringProvider>();
      mockMonitoringProvider
        .Setup(m => m.GetCounters())
        .Returns(new[]
                   {
                     new PerfCounterInfo {Name = "Cluster/CCU", Period = 1},
                     new PerfCounterInfo {Name = "Cluster/MatchmakingUsers", Period = 5},
                     new PerfCounterInfo {Name = "Cluster/etc", Period = 100}
                   });
      mockMonitoringProvider
        .Setup(m => m.RegisterPerfCounters(new[]
                                             {
                                               new PerfCounterInfo {Name = "Cluster/CCU", Period = 1}
                                             }.ToList()))
        .Returns(true);

      var mockSummaryHost = new Mock<IMonitoringSummaryHost>();

//      var monitoring = new MonitoringService(mockMonitoringProvider.Object, null, mockSummaryHost.Object);

//      var requests = new[] {new PerfCounterRequest {Name = "CCU"}};
//      Assert.That(monitoring.RunAsync(requests, null));
//
//      requests = new[] {new PerfCounterRequest {Name = "etc"}, new PerfCounterRequest {Name = "MatchmakingUsers"}};
//      Assert.That(monitoring.RunAsync(requests, null));
//
//      requests = new[] {new PerfCounterRequest {Name = "CPULoading"}};
//      Assert.That(!monitoring.RunAsync(requests, null));
//
//      requests = new[] {new PerfCounterRequest {Name = "CPULoading"}, new PerfCounterRequest {Name = "etc"}};
//      Assert.That(!monitoring.RunAsync(requests, null));
    }


  }
}