
namespace StatisticService.RPC
{
  public class SessionDamageInfo : ISerializable
  {
    public bool dealt;
    public int opponentId;
    public int unitType;
    public int talentId;
    public float physicalDamage;
    public float magicalDamage;
    public float pureDamage;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref dealt);
      s.Add(ref opponentId);
      s.Add(ref unitType);
      s.Add(ref talentId);
      s.Add(ref physicalDamage);
      s.Add(ref magicalDamage);
      s.Add(ref pureDamage);
    }
  }



  public class ClientSessionDamageMessage : ISerializable
  {
    public CommonSessionEventInfo common = new CommonSessionEventInfo();
    public SessionDamageInfo info = new SessionDamageInfo();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(common);
      s.Add(info);
    }
  }
}
