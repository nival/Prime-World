namespace KontagentLib
{
  public class KontagentContext
  {
    public string MarketingServiceUrl { get; set; }
    public int RequestTimeout { get; set; }
    public int TimeoutAfterError { get; set; }
    public int QueueLength { get; set; }
    public float QueueDumpingPart { get; set; }
    public float QueueRestoringPoint { get; set; }
    public int SentRateMin { get; set; }
    public int SentRateMax { get; set; }
    public int SentRateChange { get; set; }
    public float MaxFailPercent { get; set; }
    public string TaskDumperFilename { get; set; }
  }
}