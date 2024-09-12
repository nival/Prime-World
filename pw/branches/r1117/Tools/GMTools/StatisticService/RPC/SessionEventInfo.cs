
namespace StatisticService.RPC
{
  public class CommonSessionEventInfo : ISerializable
  {
    public long sessionId;
    public int playerId;
    public int step;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref playerId);
      s.Add(ref step);
    }
  }


  public class SessionEventInfo : ISerializable
  {
    public int intParam1;
    public int intParam2;
    public int intParam3;
    public int intParam4;
    public int intParam5;
    public string strParam1;
    public string strParam2;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref intParam1);
      s.Add(ref intParam2);
      s.Add(ref intParam3);
      s.Add(ref intParam4);
      s.Add(ref intParam5);
      s.Add(ref strParam1);
      s.Add(ref strParam2);
    }

    public override string ToString()
    {
      return string.Format("SessionEventInfo(IntParam1={0},IntParam2={1},IntParam3={2},IntParam4={3},IntParam5={4},StrParam1={5},StrParam2={6})",
                           intParam1, intParam2, intParam3, intParam4, intParam5, strParam1, strParam2);
    }
  }



  public class ClientCommonSessionEvent : ISerializable
  {
    public CommonSessionEventInfo common = new CommonSessionEventInfo();
    public float x;
    public float y;
    public int eventType;
    public SessionEventInfo info = new SessionEventInfo();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(common);
      s.Add(ref x);
      s.Add(ref y);
      s.Add(ref eventType);
      s.Add(info);
    }

    public override string ToString()
    {
      return string.Format("ClientCommonSessionEvent(common={0}, x={1}, y={2}, eventType={3}, info={4})",
                           common.ToString(), x, y, eventType, info.ToString());
    }
  }
}
