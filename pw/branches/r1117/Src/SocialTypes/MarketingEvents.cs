using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;
using System.ComponentModel;
using PF_GameLogic.DBServer;
using PF_GameLogic.DBTalent;

namespace SocialTypes.DBTypes
{
  public class MarketingEvent : BaseMarketingEvent
  {
    public DBPtr<Render.DBRenderResources.Texture> iconA;
    public DBPtr<Render.DBRenderResources.Texture> iconB;

    public DBPtr<Render.DBRenderResources.Texture> imageA;
    public DBPtr<Render.DBRenderResources.Texture> imageB;

    public TextRef tooltipA;
    public TextRef tooltipB;

    public TextRef nameA;
    public TextRef nameB;

    public TextRef sloganA;
    public TextRef sloganB;

    public TextRef buttonActionTextA;
    public TextRef buttonActionTextB;

    public TextRef cancelButtonActionText;

    public bool isSpecial = false;
    public bool visible = true;
  }

  public class PremiumEvent : MarketingEvent
  {
    public TextRef prolongMessageText;
    public TextRef buyMessageText;
    public TextRef messageButtonText;
  }

  public class BuyHeroEvent : MarketingEvent
  {
    public TextRef youAlreadyBoughtAllEventHeroes;
    public TextRef youAlreadyUsedEvent;
  }

  public class FirstBuyEvent : MarketingEvent
  {
    public TextRef youAlreadyBoughtAllFirstBuyHouses;
    public TextRef youAlreadyBoughtAllFirstBuyHousesAndPutItInPocket;
  }

  //пока пустой. сложнее возможно переделывать будет на новый класс. поэтому завел новый
  public class BuySpecialHeroEvent : MarketingEvent
  {
  }

  //пока пустой. сложнее возможно переделывать будет на новый класс. поэтому завел новый
  public class BuySteamGoldEvent : MarketingEvent
  {
  }

  public class BuySteamDLCEvent : MarketingEvent
  {
  }

  public class BuyAeriaGoldEvent : MarketingEvent
  {
  }

  public class BuyArcGamesGoldEvent : MarketingEvent
  {
  }

  public class BuyZZimaGoldEvent : MarketingEvent
  {
  }

  public class BuyGoldHeroEvent : MarketingEvent
  {
    public TextRef youAlreadyBoughtAllEventHeroes;
  }

  public class BuildGoldenLodgeEvent : MarketingEvent
  {
  }

  public class BuyGoldenLodgeEvent : MarketingEvent
  {
  }

  public class BuyTournamentTicketEvent : MarketingEvent
  {
  }

  public class BeginnersPack : MarketingEvent
  {

  }

  public class UpgradeHeroTalentsEvent : MarketingEvent
  {
  }
  
  public class PrimeArenaEvent : MarketingEvent
  {
  }

  public class TournamentInProgressEvent : MarketingEvent
  {
      public DBPtr<Render.DBRenderResources.Texture> tournamentLostImage;
      public DBPtr<Render.DBRenderResources.Texture> tournamentLostIcon;
      public TextRef tournamentLostTooltip;
      public TextRef inTournamentButtonText;
      public string inTournamentButtonUrl;
      public TextRef tournamentLostButtonText;
      public string tournamentLostButtonUrl;
  }

  public class GoldLampEvent : MarketingEvent
  {
    [Description("бонусное золотов процентах в целых числах")]
    public int bonusPersent;
    [Description("максимальная рарность таланта, который можно отвязать этой лампой")]
    public ETalentRarity unsoulBoundRarity = ETalentRarity.ordinary;

    [Description("иконка-нотификатор в замке")]
    public DBPtr<Render.DBRenderResources.Texture> lampIcon;

    [Description("баннер в акции пополнения счета")]
    public DBPtr<Render.DBRenderResources.Texture> banner;
  }

  public class BuyFlagEvent : MarketingEvent
  {
  }

  public class MarketingEvents
  {
    public DBPtr<PremiumEvent> premiumAccEvent;
    public DBPtr<BuyHeroEvent> buyHero;
    public DBPtr<FirstBuyEvent> firstBuy;
    public DBPtr<BuySpecialHeroEvent> buySpecialHero;
    public DBPtr<BuyGoldHeroEvent> buyGoldHero;
    public DBPtr<BuildGoldenLodgeEvent> buildGoldenLodge;
    public DBPtr<BuyGoldenLodgeEvent> buyGoldenLodge;
    public DBPtr<BuySteamGoldEvent> buySteamGold;
    public DBPtr<BuySteamDLCEvent> buySteamDLC;
    public DBPtr<BuyAeriaGoldEvent> buyAeriaGold;
    public DBPtr<BuyArcGamesGoldEvent> buyArcGamesGold;
    public DBPtr<BuyZZimaGoldEvent> buyZZimaGold;

    public List<DBPtr<GoldLampEvent>> lampEvents = new List<DBPtr<GoldLampEvent>>();

    public DBPtr<BuyTournamentTicketEvent> tournamentEvent;
    public DBPtr<TournamentInProgressEvent> tournamentInProgressEvent;

    public DBPtr<BuyFlagEvent> buyFlag;
    public DBPtr<BeginnersPack> beginnersPack;
    public DBPtr<UpgradeHeroTalentsEvent> upgradeHeroTalentsEvent;
    public DBPtr<PrimeArenaEvent> primeArenaEvent;

  }


}
