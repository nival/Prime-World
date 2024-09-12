using System;
using NUnit.Framework;

namespace MonitoringService.Tests
{
  [TestFixture]
  public class PerfCounterTests
  {
    [Test]
    public void FromStringTest()
    {
      var request = PerfCounterRequest.FromString("Cluster/Service/ID/Counter");
      Assert.AreEqual("Cluster", request.CounterCluster);
      Assert.AreEqual("Service", request.CounterService);
      Assert.AreEqual("ID", request.CounterServiceId);
      Assert.AreEqual("Counter", request.CounterName);

      request = PerfCounterRequest.FromString("*//ccu");
      Assert.AreEqual("*", request.CounterCluster);
      Assert.AreEqual("", request.CounterService);
      Assert.AreEqual(null, request.CounterServiceId);
      Assert.AreEqual("ccu", request.CounterName);

      request = PerfCounterRequest.FromString(null);
      Assert.IsNull(request);
      request = PerfCounterRequest.FromString(String.Empty);
      Assert.IsNull(request);
      request = PerfCounterRequest.FromString("");
      Assert.IsNull(request);
      request = PerfCounterRequest.FromString("fffuuuu");
      Assert.IsNull(request);
      request = PerfCounterRequest.FromString("foo/foo/foo/foo/fffuuuu");
      Assert.IsNull(request);
    }

    [Test]
    public void MatchTest()
    {
      var request = PerfCounterRequest.FromString("*/Service/CCU");

      Assert.That(request.Match("MySuperCluster/Service/CCU"));
      Assert.That(request.Match("/Service/CCU"));
      Assert.That(request.Match("cluster/service/ccu"));

      Assert.That(!request.Match(null));
      Assert.That(!request.Match(""));
      Assert.That(!request.Match("Random string"));
      Assert.That(!request.Match("CCU"));
      Assert.That(!request.Match("Cluster//CCU"));
      Assert.That(!request.Match("Cluster/Service//CCU"));
      Assert.That(!request.Match("Cluster/Service/123/CCU"));
      Assert.That(!request.Match("Cluster/ololo/CCU"));
      Assert.That(!request.Match("Cluster/Service/ololo"));
    }
  }
}