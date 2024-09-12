using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using log4net;
using MonitoringLib;
using ThreadState=System.Threading.ThreadState;

namespace MonitoringService
{
  public class MonitoringService
  {
    private static ILog _log = LogManager.GetLogger(typeof(MonitoringService));

    private const int MONITORING_REQUEST_INTERVAL = 5000; // ms

    private readonly MonitoringContext context;
    private readonly MonitoringStorage storage;
    private readonly IMonitoringProvider provider;

    public enum Status
    {
      NotInitialized,
      Running,
      Stopped
    }
    public Status CurrentStatus { get; private set; }

    private Thread workingThread;
    private volatile bool stopFlag;


    public MonitoringService(MonitoringContext context, MonitoringStorage storage)
    {
      this.context = context;
      this.storage = storage;
      this.provider = new MonitoringProvider(context.MonitoringUrl);

      this.CurrentStatus = Status.NotInitialized;
    }

    public bool Init()
    {
      if (CurrentStatus != Status.NotInitialized)
      {
        _log.Warn("Monitoring is already initialized, status = " + CurrentStatus);
        return true;
      }
      _log.InfoFormat("Monitoring service(url={0}) initialization...", context.MonitoringUrl);

      _log.Info("Counter requests:");
      foreach (var key in context.Requests.Keys)
        _log.InfoFormat("  {0} : {1}", key, context.Requests[key] != null ? context.Requests[key].ToString() : "(null)");

      Dictionary<string, PerfCounterInfo> matchedCounters = GetMatchedCounters(provider, context.Requests);
      if (matchedCounters != null && matchedCounters.Count != 0)
      {
        _log.Info("Registering counters");
        if (!provider.RegisterPerfCounters(matchedCounters.Values.ToList()))
          return false;
        if (!storage.RegisterCounters(matchedCounters))
          return false;
      }
      else
      {
        _log.ErrorFormat("Cannot register counters for monitoring service(url={0})", context.MonitoringUrl);
        return false;
      }

      CurrentStatus = Status.Stopped;
      return true;
    }

    /// <summary>
    /// Receive from monitoring provider list of counters, that are matching our requests
    /// </summary>
    private Dictionary<string, PerfCounterInfo> GetMatchedCounters(IMonitoringProvider monitoringProvider, Dictionary<string, PerfCounterRequest> requests)
    {
      _log.Info("Get counters from server:");
      IEnumerable<PerfCounterInfo> allcounters = monitoringProvider.GetCounters();
      if (allcounters == null)
      {
        _log.Error("Cannot get any counter");
        return null;
      }
      foreach (var p in allcounters)
        _log.Info("  " + p);

      // Список каунтеров которые соответствуют входному запросу
      var matchedCounterInfos = new Dictionary<string, PerfCounterInfo>();

      foreach (var rkey in requests.Keys)
      {
        PerfCounterInfo matched = allcounters.FirstOrDefault(info => requests[rkey].Match(info.Name));
        if (matched == null)
        {
          _log.Error("Cannot match any PerfCounterInfo for request " + requests[rkey]);
          continue;
        }
        if (requests[rkey].Period >= matched.Period)
          matched.Period = requests[rkey].Period;
        matchedCounterInfos.Add(rkey, matched);
      }

      return matchedCounterInfos;
    }

    public bool RunAsync()
    {
      if (CurrentStatus != Status.Stopped)
        return false;
      _log.InfoFormat("Run monitoring service(url={0})", context.MonitoringUrl);
      CurrentStatus = Status.Running;

      workingThread = new Thread(Run);
      workingThread.Start();

      return true;
    }

    private void Run()
    {
      var watch = new Stopwatch();
      while (!stopFlag)
      {
        watch.Start();

        IEnumerable<PerfCounterSample> samples = provider.GetPerfCounterSamples();
        if (samples != null && samples.Count() > 0)
        {
          _log.DebugFormat("Monitoring result from {0}:\n\t{1}", context.MonitoringUrl,
                           String.Join("\n\t", samples.Select(s => s.ToString()).ToArray()));

          foreach (PerfCounterSample sample in samples)
            storage.UpdateCounters(sample);
        }

        watch.Stop();
        int remain_time = MONITORING_REQUEST_INTERVAL - (int)watch.ElapsedMilliseconds;
        if (remain_time > 0)
          Thread.Sleep(remain_time);
        watch.Reset();
      }

      _log.InfoFormat("Stopped monitoring service(url={0})", context.MonitoringUrl);

      if (!provider.UnregisterAllPerfCounters())
        _log.Warn("Failed to unregister all counters from game cluster");
    }

    public void Stop()
    {
      if (CurrentStatus != Status.Running)
      {
        _log.WarnFormat("Cannot stop monitoring service(url={0}), because service in status {1}", context.MonitoringUrl, CurrentStatus);
        return;
      }
      var threadState = workingThread.ThreadState;
      if ((threadState != ThreadState.Running) && (threadState != ThreadState.WaitSleepJoin))
      {
        _log.WarnFormat("Cannot stop game statistic, thread is in {0} state", threadState);
        return;
      }

      stopFlag = true;
      workingThread.Join();
    }
  }
}
