//#include "..\PF_Types\DBGuild.cs"
//#include "..\PF_Types\DBServerPvPRoll.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBUnit;
using libdb.DB;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBConsumable;
using PF_Types.SocialClient;
using Foundation.DBSystem;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBGuild;
using PF_GameLogic.DBServer;


namespace SocialTypes.DBTypes
{

  [NonTerminal]
  public class GuildShopItemTarget : DBResource
  {
    [Description("Максимальное кол-во игроков гильдиий, на которых можно распространить баф")]
    public int NumPlayers;
  }

  public class Buyer : GuildShopItemTarget
  {
    
  }

  public class OnlineGuildMembers : GuildShopItemTarget
  {
    
  }

  public class AllGuildMembers : GuildShopItemTarget
  {

  }

  public class HoldGuild: GuildShopItemTarget
  {

  }


  public class RankedGuildMembers : GuildShopItemTarget
  {
    [Description("Рейтинг, с которого начинает действовать баф")]
    public int minRating;
    [Description("Рейтинг, после которого прекращает действовать баф")]
    public int maxRating;
  }

  public class BestGuildInvesters : GuildShopItemTarget
  {
    [Description("Период за который считаем лучшими")]
    public int daysToCount;
  }

  public class WorstGuildInvesters : GuildShopItemTarget
  {
    [Description("Период за который считаем худшими")]
    public int daysToCount;
  }

  public class BestRankedPlayers : GuildShopItemTarget
  {
  }

  public class WorstRankedPlayers : GuildShopItemTarget
  {
  }


  public class CastleResourceBonus : GuildShopItemBonus
  {
    public EResourceType resource;
    [Description("Производственный цикл")]
    public EBuildingProductionCycle cycle;
    [Description("Здания, на которые распространяется бонус")]
    public List<DBPtr<Constructon>> buildingsToAffect;

    public ValueProps modifiers;
  }

  public class ShopLevelToItemsAmount
  {
    [Description("Уровень магазина")]
    public int shopLevel;
    [Description("Максимальное количество за сутки")]
    public int buysPerTime;
  }

  [NonTerminal]
  [IndexField("persistentId")]
  public class GuildShopItem : DBResource
  {
    [Description("ID товара")]
    public string persistentId = null;
    public TextRef description = new TextRef();
    public TextRef tooltip = new TextRef();
    [Description("Иконка")]
    public DBPtr<Render.DBRenderResources.Texture> icon;
    [Description("Цена")]
    public ResourcesTable price;
    [Description("Скидка в процентах")]
    public int discount;
    [Description("Кол-во доступных айтемов в зависимости от уровня магазина. Если айтемы бесконечны, не заполняем")]
    public List<ShopLevelToItemsAmount> shopLevelToItemsAmount;
    [Description("Требуем ранг магазина с которого становится доступным")]
    public int levelToUnlock;
    [Description("Категория в магазине")]
    public GuildShopCategoryType shopCategory;
  }

  public class OneTimeGuildShopItem : GuildShopItem
  {
    [Description("На кого воздействует бонус")]
    public List<DBPtr<GuildShopItemTarget>> target;
    [Description("Баф для этого айтема")]
    public DBPtr<GuildBuff> guildBuff;
  }

  public class SkinGuildShopItem : GuildShopItem
  {
    [Description("Скин")]
    public DBPtr<HeroSkin> skin;
  }

  public class TalentGuildShopItem : GuildShopItem
  {
    [Description("Талант")]
    public DBPtr<Talent> talent;
  }

  public class FlagGuildShopItem : GuildShopItem
  {
    [Description("Флаг для выдачи")]
    public DBPtr<CustomFlag> flag;
  }

  public class Lootbox : DBResource
  {
    public string persistentId;
    public DBPtr<Render.DBRenderResources.Texture> image;
    public TextRef name = new TextRef();
    public TextRef tooltip = new TextRef();
    public DBPtr<RollContainer> rollContainer;
  }

  public class LootboxGuildShopItem : GuildShopItem
  {
    public DBPtr<Lootbox> lootbox;
  }

}
