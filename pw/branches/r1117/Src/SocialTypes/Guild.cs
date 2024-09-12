using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBStats;
using SocialTypes.DBTypes;
using PF_GameLogic.DBServer;


namespace SocialTypes.Guild
{
  // Здесь только замковые гильдийские награды.
  public class GuildProduction : GuildBonus
  {
    [Description("Всегда только 1 цикл. Доступен для namemap'а")]
    [NameMapValue]
    public GuildCycle cycle;
  }

  public class GuildStatsBonus : GuildBonus
  {
    [Description("Количество мастер поинтов (inc). Доступен для namemap'а")]
    [NameMapValue]
    public int MasterPoints;
  }

  public class GuildMemberBonus : GuildBonus
  {
    [Description("Количество дополнительных игроков гильдии (const). Доступен для namemap'а")]
    [NameMapValue]
    public int members;
  }

    public class GuildOpenBankBonus : GuildBonus
  {
  }

    public class GuildBankSlotsBonus : GuildBonus
  {
    [Description("Количество дополнительных слотов банка гильдии (const). Доступен для namemap'а")]
    [NameMapValue]
    public int slots;
  }

  public class HeroEnergyRestoreBonus : GuildBonus
  {
    [Description("Коэффициет бонуса пассивного восстановления энергии героя (const). Доступен для namemap'а")]
    [NameMapValue]
    public float coef;
  }

  public class GuildCycle : CycleType
  {
    [Description("Процент выдачи одного из типов ресурса по окончанию цикла")]
    [EnumArray(typeof(EResourceType))]
    public List<int> percents;
  }

  public class GuildVisibleBonusesCount : DBResource
  {
      [Description("Количество плашек бонусов, показываемых на определённом уровня клана (const)")]
      public int defaultBonusCount;
      public int additionalBonusCount;
  }

  public class GuildSuzerenLevel
  {
    [Description("Экспа для достижения данного уровня")]
    public long requiredExp = 0;
  }
}
