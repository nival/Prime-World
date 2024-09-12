using libdb.DB;
using System.ComponentModel;
using System.Collections.Generic;

namespace PF_Types.SocialClient
{
  [Custom("Social")]
  [NoCode]
  public class CurrencyItem
  {
    [NameMapValue]
    public string Id;
    [NameMapValue]
    public int Value;
  }

  [Custom("Social")]
  [NoCode]
  public class ResourcesTable
  {
    [NameMapValue]
    public int Resource1 = 0;
    [NameMapValue]
    public int Resource2 = 0;
    [NameMapValue]
    public int Resource3 = 0;
    public int Resource1_Rare = 0;
    public int Resource2_Rare = 0;
    public int Resource3_Rare = 0;
    [NameMapValue]
    public int Perl = 0;
    [NameMapValue]
    public int RedPerl = 0;
    [NameMapValue]
    public int Silver = 0;
    [NameMapValue]
    public int Gold = 0;
    [NameMapValue]
    public int Population = 0;
    [NameMapValue]
    public int CWPoints_Clan = 0;
    [NameMapValue]
    public int CWPoints_Player = 0;
    [NameMapValue]
    public int Shard = 0;
    [NameMapValue]
    public List<CurrencyItem> Currencies = null;
  }

  [Custom("Social")]
  [NoCode]
  public class ResourcesCoefTable
  {
    public float Resource1 = 0;
    public float Resource2 = 0;
    public float Resource3 = 0;
    public float Resource1_Rare = 0;
    public float Resource2_Rare = 0;
    public float Resource3_Rare = 0;
    public float Perl = 0;
    public float RedPerl = 0;
    public float Silver = 0;
    public float Gold = 0;
    public float Population = 0;
    public float CWPoints_Clan = 0;
    public float CWPoints_Player = 0;
    public float Shard = 0;
    public float Currencies = 0;
  }
}
