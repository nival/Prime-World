using System.Configuration;

namespace StatisticService
{
  public class StatisticEventsSection : ConfigurationSection
  {
    [ConfigurationProperty("StatisticWriter")]
    public StatisticWriterElement StatisticWriter
    {
      get { return (StatisticWriterElement)this["StatisticWriter"]; }
    }

    [ConfigurationProperty("StatisticDebugWriter")]
    public StatisticDebugWriterElement StatisticDebugWriter
    {
      get { return (StatisticDebugWriterElement)this["StatisticDebugWriter"]; }
    }
  }

  public class StatisticWriterElement : ConfigurationElement
  {
    [ConfigurationProperty("LogSessionEvent")]
    public SessionEventTypeCollection LogSessionEvent
    {
      get { return (SessionEventTypeCollection)this["LogSessionEvent"]; }
    }

    [ConfigurationProperty("LogSessionDamage")]
    public EmptyConfigurationElement LogSessionDamage
    {
      get { return (EmptyConfigurationElement)this["LogSessionDamage"]; }
    }
  }

  public class SessionEventTypeCollection : ConfigurationElementCollection
  {
    protected override ConfigurationElement CreateNewElement()
    {
      return new SessionEventTypeElement();
    }

    protected override object GetElementKey(ConfigurationElement element)
    {
      return ((SessionEventTypeElement) element).Name;
    }
  }

  public class SessionEventTypeElement : ConfigurationElement
  {
    [ConfigurationProperty("name", IsKey = true)]
    public string Name
    {
      get { return (string) this["name"]; }
    }
  }

  public class StatisticDebugWriterElement : ConfigurationElement
  {
    [ConfigurationProperty("LogExceedingStepTime")]
    public EmptyConfigurationElement LogExceedingStepTime
    {
      get { return (EmptyConfigurationElement) this["LogExceedingStepTime"]; }
    }
    [ConfigurationProperty("LogExceedingPingTime")]
    public EmptyConfigurationElement LogExceedingPingTime
    {
      get { return (EmptyConfigurationElement)this["LogExceedingPingTime"]; }
    }
    [ConfigurationProperty("LogOfflineEvent")]
    public EmptyConfigurationElement LogOfflineEvent
    {
      get { return (EmptyConfigurationElement)this["LogOfflineEvent"]; }
    }
    [ConfigurationProperty("LogDebugVar")]
    public EmptyConfigurationElement LogDebugVar
    {
      get { return (EmptyConfigurationElement)this["LogDebugVar"]; }
    }
    [ConfigurationProperty("LogPvxLogin")]
    public EmptyConfigurationElement LogPvxLogin
    {
      get { return (EmptyConfigurationElement)this["LogPvxLogin"]; }
    }
    [ConfigurationProperty("LogPvxScreenResolution")]
    public EmptyConfigurationElement LogPvxScreenResolution
    {
      get { return (EmptyConfigurationElement)this["LogPvxScreenResolution"]; }
    }
  }

  public class EmptyConfigurationElement : ConfigurationElement
  {
  }
}