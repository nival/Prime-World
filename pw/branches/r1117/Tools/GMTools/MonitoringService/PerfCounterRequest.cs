using System;
using System.Configuration;

namespace MonitoringService
{
  public class PerfCounterRequest
  {
    private const string ANY = "*";

    public string CounterCluster { get; set; }
    public string CounterService { get; set; }
    public string CounterServiceId { get; set; }
    public string CounterName { get; set; }
    
    public int Period { get; set; }

    public bool Match(string counterString)
    {
      PerfCounterRequest param = FromString(counterString);

      if (param == null) return false;
      if ((CounterCluster == null ^ param.CounterCluster == null) ||
          (CounterService == null ^ param.CounterService == null) ||
          (CounterServiceId == null ^ param.CounterServiceId == null) ||
          (CounterName == null ^ param.CounterName == null))
        return false;

      return ((CounterCluster == null && param.CounterCluster == null) || CounterCluster == ANY ||
              String.Compare(CounterCluster, param.CounterCluster, true) == 0)
             &&
             ((CounterService == null && param.CounterService == null) || CounterService == ANY ||
              String.Compare(CounterService, param.CounterService, true) == 0)
             &&
             ((CounterServiceId == null && param.CounterServiceId == null) || CounterServiceId == ANY ||
              String.Compare(CounterServiceId, param.CounterServiceId, true) == 0)
             &&
             ((CounterName == null && param.CounterName == null) || CounterName == ANY ||
              String.Compare(CounterName, param.CounterName, true) == 0);
    }

    public override string ToString()
    {
      return String.Format("PerfCounterRequest(Counter={0}/{1}/{2}/{3},period={4})",
                           CounterCluster, CounterService, CounterService, CounterName, Period);
    }

    public static PerfCounterRequest FromString(string counterString)
    {
      if (counterString == null) return null;
      
      var request = new PerfCounterRequest();
      
      string[] counter_parts = counterString.Split('/');
      switch (counter_parts.Length)
      {
        case 2:
          request.CounterCluster = counter_parts[0];
          request.CounterName = counter_parts[1];
          break;
        case 3:
          request.CounterCluster = counter_parts[0];
          request.CounterService = counter_parts[1];
          request.CounterName = counter_parts[2];
          break;
        case 4:
          request.CounterCluster = counter_parts[0];
          request.CounterService = counter_parts[1];
          request.CounterServiceId = counter_parts[2];
          request.CounterName = counter_parts[3];
          break;

        default:
          return null;
      }
      return request;
    }
  }

  public class PerfCounterRequestSection : ConfigurationSection
  {
    [ConfigurationProperty("pvx")]
    public CounterCollection PvxCounters
    {
      get { return (CounterCollection)this["pvx"]; }
    }
    [ConfigurationProperty("social")]
    public CounterCollection SocialCounters
    {
      get { return (CounterCollection)this["social"]; }
    }
    [ConfigurationProperty("statperiod")]
    public StatisticPeriod StatPeriod
    {
      get { return (StatisticPeriod)this["statperiod"]; }
    }
  }

  public class CounterCollection : ConfigurationElementCollection
  {
    protected override ConfigurationElement CreateNewElement()
    {
      return new CounterElement();
    }
    protected override object GetElementKey(ConfigurationElement element)
    {
      return ((CounterElement)element).Field;
    }
  }

  public class CounterElement : ConfigurationElement
  {
    [ConfigurationProperty("field")]
    public string Field
    {
      get { return (String)this["field"]; }
    }
    [ConfigurationProperty("counter")]
    public string Counter
    {
      get { return (String)this["counter"]; }
    }
  }

  public class StatisticPeriod : ConfigurationElement
  {
    [ConfigurationProperty("value")]
    public int Value
    {
      get { return Int32.Parse(this["value"].ToString()); }
    }
  }
}