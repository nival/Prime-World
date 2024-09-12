using System;
using System.ComponentModel;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  public class EventShortInfo
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }
    public EventType Type { get; set; }
    public string Description { get; set; }
    public bool Enabled { get; set; }
    public DateTime StartTime { get; set; }
    public DateTime EndTime { get; set; }
    public string Locale { get; set; }


    public EventShortInfo()
    {
    }


    public EventShortInfo(CommonEventInfo info)
    {
      Id = info.PersistentId;
      Type = (EventType)info.Type;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
    }

  }


  /// <summary>
  /// Enum для того чтобы имена экшонов и описания не зависели от трифтового ConfigEventType
  /// </summary>
  public enum EventType
  {

    [Description("Techs")]
    Techs = 0,

    [Description("Custom event")]
    Custom = 1,

    [Description("Map event")]
    CustomMap = 2,

    [Description("Talent drop")]
    TalentDrop = 3,

    [Description("News banner")]
    NewsBanner = 4,

    [Description("Skin price")]
    SkinPrice = 5,

    [Description("Hero price")]
    HeroPrice = 6,

    [Description("Transmutation")]
    Transmutation = 7,

    [Description("Reforge Talents")]
    ReforgeTalents = 8,

    [Description( "Reroll shop slots" )]
    RerollSlots = 9,

    [Description( "Reroll price" )]
    RerollPrice = 10,

    [Description( "Reroll group price" )]
    RerollGroupPrice = 11,

    [Description( "Reroll group currencies" )]
    RerollGroupCurrencies = 12,

    [Description( "Reroll group probability" )]
    RerollGroupProbabilities = 13,

    [Description( "Reroll slot prices" )]
    RerollSlotPrice = 14,

    [Description( "FirstBuy price" )]
    FirstBuyPrice = 15,

    [Description( "Premium slots not inactive" )]
    RerollShopPremiumNotInactive = 16,

    [Description( "Reroll slot amounts" )]
    RerollSlotAmount = 17,

    [Description( "Reroll group slots" )]
    RerollGroupSlots = 18,

    [Description( "Reroll shop banner" )]
    RerollShopBanner = 19,

    [Description( "Reroll shop tooltip" )]
    RerollShopTooltip = 20,

    [Description( "Roll events (Custom)" )]
    RollEvent = 21,

    [Description( "Quest events (Custom)" )]
    QuestEvent = 22,

    [Description("Trade events (Custom)")]
    TradeEvent = 23,

    [Description("Season events (Custom)")]
    SeasonEvent = 24,

    [Description("Donate event")]
    DonateEvent = 25,
  }


  public static class DescriptionHelper
  {

    public static string GetDescription(this EventType e)
    {
      var member = typeof(EventType).GetMember(e.ToString())[0];
      var attr = member.GetCustomAttributes(typeof(DescriptionAttribute), false)[0];
      return ((DescriptionAttribute) attr).Description;
    }

  }


}