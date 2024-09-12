using System;
using System.Collections.Generic;
using System.ComponentModel;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBUnit;
using PF_Types.SocialClient;
using SocialTypes.DBTypes;
using libdb.DB;

namespace SocialTypes.RerollShop
{
  public enum ERerollShopResources
  {
    Resource1,
    Resource2,
    Resource3,
    Perl,
    RedPerl,
    Silver,
    Gold,
    Shard
  }

  [Flags]
  [Custom("DBServer", "Social")]
  public enum ERerollShopResourceType
  {
    Resource1 = 1 << 0,
    Resource2 = 1 << 1,
    Resource3 = 1 << 2,
    Perl = 1 << 3,
    RedPerl = 1 << 4,
    Silver = 1 << 5,
    Gold = 1 << 6,
    Shard = 1 << 7,
    All = Resource1 | Resource2 | Resource3 | Perl | RedPerl | Silver | Gold | Shard,
  }

  [NonTerminal]
  public class RerollShopSlot : DBResource
  {
    [Description("Id слота")]
    public string persistentId;

    [Description("Id кадра с подложкой (-1 - стандартная подложка)")]
    public int backgroundId = -1;
  }

  public class ResourceRerollSlot : RerollShopSlot
  {
    // УСТАРЕЛО! используй resource
    [Browsable(false)]
    [Description("Количество ресурса")]
    [NameMapValue]
    public int amount;

    // УСТАРЕЛО! используй resource
    [Browsable( false )]
    [Description("Тип ресурса")]
    public ERerollShopResources resourceType;

    [Description("ресурс")]
    public ResourcesTable resource;

    public TextRef nameA = new TextRef();
    public TextRef tooltipA = new TextRef();
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> iconA;
    public TextRef nameB = new TextRef();
    public TextRef tooltipB = new TextRef();
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> iconB;
  }

  public class PremiumRerollSlot : RerollShopSlot
  {
    [Description("Количество дней")]
    [NameMapValue]
    public int days;

    public TextRef nameA = new TextRef();
    public TextRef tooltipA = new TextRef();
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> iconA;
    public TextRef nameB = new TextRef();
    public TextRef tooltipB = new TextRef();
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> iconB;
  }

  public class TalentRerollSlot : RerollShopSlot
  {
    [Description("Талант")]
    public DBPtr<Talent> talent;
  }

  public class TalentsListRerollSlot : RerollShopSlot
  {
    [Description("Таланты")]
    public List<DBPtr<Talent>> talents;
  }

  public class SkinRerollSlot : RerollShopSlot
  {
    [Description("Скин")]
    public DBPtr<HeroSkin> skin;
  }

  public class HeroRerollSlot : RerollShopSlot
  {
    [Description("Герой")]
    public DBPtr<Hero> hero;
  }

  public class UpgradeHeroTalentsRerollSlot : RerollShopSlot
  {
    [Description("Add UpgradeHeroTalentsEvent to this field")]
    public DBPtr<UpgradeHeroTalentsEvent> upgradeHeroTalents;
    public TextRef tooltip = new TextRef();
    [Description("Count adding uses")]
    [NameMapValue]
    public int uses;
  }

  public class LootboxRerollSlot : RerollShopSlot 
  {
    [Description( "Add Lootbox to this field" )]
    public DBPtr<Lootbox> lootbox;

    [Description( "Lootboxes count" )]
    [NameMapValue]
    public int count;
  }

  public class LampRerollSlot : RerollShopSlot
  {
    [Description("Акция")]
    public DBPtr<GoldLampEvent> lamp;

    public TextRef tooltip = new TextRef();

    [Description("Время действия (в секундах)")]
    public int lifeTime;

    [Description("Максимальный бонус")]
    [NameMapValue]
    public int maxBonus;

    [Description("Количество транзакций")]
    [NameMapValue]
    public int transactions;
  }

  public class RerollTimesToDropProbabilty
  {
    [Description("Сколько раз нужно сделать реролл")]
    public int rerollTime;

    [Description("Новая вероятность после rerollTime раз")]
    public float newProbability;
  }

  public class GroupSlot
  {
    public DBPtr<RerollShopSlot> slot;

    [Description("Ресурсы, за которые можно купить этот слот")]
    public ERerollShopResourceType currencies;

    [Description("Минимальная цена в очках")]
    public int minPoints = 0;

    [Description("Максимальная цена в очках")]
    public int maxPoints = 0;
  }

  [IndexField("persistentId")]
  public class RerollShopGroup : DBResource
  {
    [Description("ID группы")]
    public string persistentId = null;

    [Description("Доступные слоты")]
    public List<GroupSlot> slots;

    [Description("Вероятности появления группы после n рероллов")]
    public List<RerollTimesToDropProbabilty> rerollTimesToDropProbabilties;

    [Description("Ресурсы, за которые можно купить товары из группы")]
    public ERerollShopResourceType currencies;

    [Description("Минимальная цена в очках")]
    public int minPoints;

    [Description("Максимальная цена в очках")]
    public int maxPoints;

    [Description("Минимальная заточка талантов в этой группе (1-10), 0 - не используется")]
    public int minUpgradeLevel = 0;

    [Description("Максимальная заточка талантов в этой группе (1-10), 0 - не используется")]
    public int maxUpgradeLevel = 0;
  }

  public class ResourceToPointsConversion
  {
    [Description("Тип ресурса")]
    public ERerollShopResources resource;

    [Description("Цена в очках")]
    public float priceInPoints;

    [Description("Порядок округления (если стоит 1000, то цена 1541 станет 2000)")]
    public int roundToDigits;
  }

  public class RerollShopSettings
  {
    [Description("Группы слотов")]
    public List<DBPtr<RerollShopGroup>> groups;

    [Description("Таблица стоимости ресурсов в очках")]
    public List<ResourceToPointsConversion> resourcesToPointsTable;

    [Description("Кол-во обычных слотов")]
    public int usualSlots;

    [Description("Дополнительное кол-во слотов для ЗВ")]
    public int premiumSlots;

    [Description("Максимальное кол-во неактивных слотов")]
    public int maxInactiveUsualSlots;

    [Description("Максимальное кол-во неактивных слотов с ЗВ")]
    public int maxInactivePremiumSlots;

    [Description("Цена реролла")]
    public ResourcesTable rerollPrice;

    [Description("Выгорают ли ЗВ слоты")]
    public bool premiumNotInactive;

    [Description("Раз в сколько секунд подсвечивается произвольный некупленный слот")]
    public int slotBlinkTime;
  }
}