using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web.Mvc;
using System.Web.UI.HtmlControls;
using AccountLib;
using ControlCenter.Helpers;
using DAL.Entities;
using DAL.Repositories;

namespace ControlCenter.Areas.GM.Models
{
  public enum FractionEnum
  {
    doct = 0,
    adornian = 1,
    notSelected = 2,
  }
  public enum GenderEnum
  {
    unknown = 0,
    male = 1,
    female = 2,
    other = 3,
  }
  public class AccountInfoModel : IDataErrorInfo
  {
    public string SNid { get; set; }
    public string SNUid { get; set; }
    public string Login { get; set; }
    public string Email { get; set; }
    public string NickName { get; set; }
    public long Auid { get; set; }
    public long GuildId { get; set; }
    [DisplayName("Guild")]
    public string GuildFullName { get; set; }
    [DisplayName("Guild building")]
    public int GuildBuildingLevel { get; set; }
    [DisplayName("Joined social networks")]
    public List<String> JoinedSNids { get; set; }

    public bool Online { get; set; }
    [DisplayName("Current session id")]
    public long CurrentSession { get; set; }

    public int Gold { get; set; }
    public int Silver { get; set; }
    [DisplayName("Wood/Silk")]
    public int Resource1 { get; set; }
    [DisplayName("Ore/Sap")]
    public int Resource2 { get; set; }
    [DisplayName("Food")]
    public int Resource3 { get; set; }
    public int Perl { get; set; }
    public int RedPerl { get; set; }
    [DisplayName("ClanWar points")]
    public int CWPoints { get; set; }
    [DisplayName("Shards")]
    public int Shard { get; set; }
    public List<ASPNETKeyValuePair<string, int>> Currencies { get; set; }

    public DateTime? RegisterDate { get; set; }
    public int Fame { get; set; }
    public int Reliability { get; set; }
    public FractionEnum Fraction { get; set; }
    public string Location { get; set; }
    public string Locale { get; set; }
    public string Muid { get; set; }
    public string Banned { get; set; }
    public string Muted { get; set; }
    public bool IsDeveloper { get; set; }
    public bool IsSpectator { get; set; }
    public bool IsRegularMMAllowed { get; set; }
    public bool HasLamp { get; set; }
    public GenderEnum Gender { get; set; }
    [DisplayName("Available faction changes")]
    public int SwitchQuant { get; set; }
    public int HiddenSwitchQuant { get; set; }
    public string HiddenNickName { get; set; }
    [DisplayName("Available nick changes")]
    public int NickChangesQuant { get; set; }
    public int HiddenNickChanges { get; set; }
    public int MaxFractionChangesQuant { get; set; }
    public int MaxNickChangesQuant { get; set; }
    public double LordRating { get; set; }
    public double DailyRating { get; set; }
    public double NumberOfWins { get; set; }
    public long NumberOfWinsForPR { get; set; }
    public int Dodges { get; set; }
    [DisplayName( "Premium account" )]
    public DateTime? PremiumAccountDate { get; set; }
    [DisplayName( "Retired time" )]
    public DateTime? RetiredTime { get; set; }
    [DisplayName("Last payment time ")]
    public DateTime? LastPaymentTime { get; set; }
    [DisplayName("Last lamp drop time")]
    public DateTime? LastLampDropTime { get; set; }
    public int TimeZone { get; set; }

    public string Country { get; set; }
    public string Region { get; set; }
    public string City { get; set; }
    [DisplayName("Country")]
    public string GMCountry { get; set; }
    [DisplayName("Region")]
    public string GMRegion { get; set; }
    [DisplayName("City")]
    public string GMCity { get; set; }

    public int LeaverPoints { get; set; }
    public bool IsLeaver { get; set; }
    public bool IsBadBehaviour { get; set; }

    public string ErrorIfExistToShow { get; set; }
     [DisplayName( "Can mute users in castle" )]
    public bool CanMute { get; set; }
    public int PlayerRating { get; set; }
    public string PlayerRatingHero { get; set; }
    public DateTime? PlayerRatingHeroLastPlayed { get; set; }

    public int ExtraComplaints { get; set; }
    public int ExtraSessionComplaints { get; set; }

    [DisplayName("Reason:")]
    public string MessageToUser { get; set; }

    public List<SeasonAwardsModel> ListSeasonsAwards;
 
    public AccountInfoModel()
    {
    }

        

      public AccountInfoModel( AccountInfo info )
    {
      //if ( info == null )
      //  throw new ArgumentNullException( "info" );
      this.Login = info.Login;
      this.SNid = info.Snid;
      this.SNUid = info.Snuid;
      this.Auid = info.Auid;
      this.NickName = info.Nickname;
      this.GuildId = info.Guildid;
      this.GuildFullName = String.Empty; // info.GuildFullName;
      this.GuildBuildingLevel = info.GuildBuildingLevel;
      this.JoinedSNids = info.JoinedSnids ?? new List<string>();
      this.Email = info.Email;
      this.CurrentSession = info.Currentsession;
      this.Online = info.Online;
      this.RegisterDate = info.Registerdate.FromUnixTimestamp();
      if (info.BanFlag != 0)
      {
        var ts = info.Banned.FromUnixTimestamp();
        this.Banned = info.BanFlag == 2 
          ? "forever" 
          : ts > DateTime.UtcNow ? ts.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) : null;
      }
      if ( info.MuteFlag != 0 )
      {
        var ts = info.Muted.FromUnixTimestamp();
        this.Muted = info.MuteFlag == 2 
          ? "forever" 
          : ts > DateTime.UtcNow ? ts.ToString( "dd'.'MM'.'yyyy HH:mm:ss" ) : null;
      }
      this.Fame = info.Fame;
      this.Fraction = (FractionEnum)info.Fraction;
      this.Location = info.Location;
      this.Locale = info.Locale;
      this.Muid = info.Muid;
      this.Reliability = info.Reliability;
      this.Gold = info.Gold;
      this.Silver = info.Silver;
      this.Resource1 = info.Resource1;
      this.Resource2 = info.Resource2;
      this.Resource3 = info.Resource3;
      this.Shard = info.Shard;
      if (info.Currencies == null)
          this.Currencies = new List<ASPNETKeyValuePair<string, int>>();
      else
          this.Currencies = info.Currencies.ToList().Select(c => new ASPNETKeyValuePair<string, int>() { Key = c.Key, Value = c.Value}).ToList();
      //this.Currencies = new Dictionary<string, int>() { { "curr1", 410 }, { "curr2", 14 } }; //for tests
      this.Perl = info.Perl;
      this.RedPerl = info.RedPerl;
      this.CWPoints = info.Cwplayerpoints;
      this.IsRegularMMAllowed = info.IsRegularMMAllowed;
      this.IsDeveloper = info.IsDeveloper;
      this.IsSpectator = info.IsSpectator;
      this.HasLamp = info.HasLamp;
      this.Gender = (GenderEnum)info.Gender;
      this.SwitchQuant = ( info.FractionChangesFree - info.FractionChanges );
      this.HiddenSwitchQuant = this.SwitchQuant;
      this.HiddenNickName = this.NickName;
      this.NickChangesQuant = ( info.NickChangesFree - info.NickChanges );
      this.HiddenNickChanges = this.NickChangesQuant;
      this.MaxFractionChangesQuant = info.FractionChangesFree;
      this.MaxNickChangesQuant = info.NickChangesFree;
      this.LordRating = info.LordRating;
      this.DailyRating = info.DailyRating;
      this.NumberOfWins = info.NumberOfWins;
      this.Dodges = info.Dodges;
      this.PremiumAccountDate = info.PremiumAccountDate != 0 ? (DateTime?)info.PremiumAccountDate.FromUnixTimestamp() : null;
      this.RetiredTime = info.RetiredTime != 0 ? (DateTime?)info.RetiredTime.FromUnixTimestamp() : null;
      this.LastPaymentTime = info.LastPaymentTime != 0 ? (DateTime?)info.LastPaymentTime.FromUnixTimestamp() : null;
      this.LastLampDropTime = info.LastLampDropTime != 0 ? (DateTime?)info.LastLampDropTime.FromUnixTimestamp() : null;
      this.Country = !String.IsNullOrEmpty(info.Country) ? info.Country : null;
      this.Region = !String.IsNullOrEmpty(info.Region) ? info.Region : null;
      this.City = !String.IsNullOrEmpty(info.City) ? info.City : null;
      this.GMCountry = !String.IsNullOrEmpty(info.Gmcountry) ? info.Gmcountry : null;
      this.GMRegion = !String.IsNullOrEmpty(info.Gmregion) ? info.Gmregion : null;
      this.GMCity = !String.IsNullOrEmpty(info.Gmcity) ? info.Gmcity : null;
      this.IsLeaver = info.IsLeaver;
      this.IsBadBehaviour = info.IsBadBehaviour;
      this.LeaverPoints = info.LeaverPoints;
      this.CanMute = info.CanMute;
      this.PlayerRating = info.PlayerRating;
      this.PlayerRatingHeroLastPlayed = info.PlayerRatingHeroLastPlayed != 0 ? (DateTime?)info.PlayerRatingHeroLastPlayed.FromUnixTimestamp() : null;
      var hero = HeroesCatalog.HeroesWithStaticData.FirstOrDefault(h => h.HeroClassId == info.PlayerRatingHero);
      if (hero != null)
        this.PlayerRatingHero = hero.HeroName;
      else
        this.PlayerRatingHero = "Unknow hero";
      this.NumberOfWinsForPR = info.NumberOfWinsForPR;
      this.ExtraComplaints = info.ExtraComplaints;
      this.ExtraSessionComplaints = info.ExtraSessionComplaints;
      this.MessageToUser = string.Empty;
      this.ListSeasonsAwards = new List<SeasonAwardsModel>();
      foreach( SeasonAwards season_item in info.ListSeasonsAwards) {
        SeasonAwardsModel season_model_item = new SeasonAwardsModel();
        season_model_item.SeasonId = season_item.SeasonId;
        season_model_item.SeasonName = !String.IsNullOrEmpty(season_item.SeasonName) ? season_item.SeasonName : null;
        season_model_item.StartDate = season_item.StartDate != 0 ? (DateTime?)season_item.StartDate.FromUnixTimestamp() : null;
        season_model_item.EndDate = season_item.EndDate != 0 ? (DateTime?)season_item.EndDate.FromUnixTimestamp() : null;
        season_model_item.Perls = season_item.Perls;
        season_model_item.Skin = season_item.Skin;
        season_model_item.Flag = season_item.Flag;
        season_model_item.Talents = season_item.Talents;
        season_model_item.Lootboxes = season_item.Lootboxes;
        this.ListSeasonsAwards.Add(season_model_item);
      }
    }

    public string Error { get { return null; } }
    public string this[string propName]
    {
      get
      {
        if ( ( propName == "NickName" ) && string.IsNullOrEmpty( NickName ) )
          return "enter NickName";

        if ( ( propName == "Silver" ) && Silver < 0 )
          return "enter valid Silver value";

        return null;
      }
    }
  }

  public class AccountShortInfoModel
  {
    public string SNid { get; set; }
    public string SNUid { get; set; }
    public string Login { get; set; }
    [DisplayName("Email/Login")]
    public string Email { get; set; }
    public string NickName { get; set; }

    public AccountShortInfoModel()
    {
    }

    public AccountShortInfoModel( AccountShortInfo info )
    {
      if ( info == null )
        throw new ArgumentNullException( "info" );

      this.SNid = info.Snid;
      this.SNUid = info.Snuid;
      this.Login = info.Login;
      this.Email = info.Email;
      this.NickName = info.Nickname;
    }

  }

  public class HeroInfoModel : IDataErrorInfo
  {
    public int HeroClassId { get; set; }
    public long HeroInstanceId { get; set; }
    public string HeroName { get; set; }
    public int Experience { get; set; }
    public double Rating { get; set; }
    public int EpicWins { get; set; }
    public List<SeasonInfoModel> ListSeasonsInfo;

    public HeroInfoModel()
    {
    }

    public HeroInfoModel( HeroInfo info )
    {
      if ( info == null )
        throw new ArgumentNullException( "construct HeroInfoModel from HeroInfo" );

      this.HeroClassId = info.HeroClassId;
      this.HeroInstanceId = info.HeroInstanceId;
      this.Experience = info.Experience;
      this.Rating = info.Rating;
      this.EpicWins = info.EpicWins;      
    }
    public HeroInfoModel( Character hero )
    {
      if ( hero == null )
        throw new ArgumentNullException( "construct HeroInfoModel from Character" );
      this.HeroClassId = hero.Id;
      this.HeroName = hero.Name;
    }

    public string Error { get { return null; } }
    public string this[string propName]
    {
      get
      {
        if ( ( propName == "Experience" ) && Experience < 0 )
          return "enter valid Gold value";
        return null;
      }
    }
  }

  public class SkinInfoModel : IDataErrorInfo
  {
    public string PersistentId { get; set; }
    public int HeroClassId { get; set; }
    public string HeroClassName { get; set; }
    public bool Owned { get; set; }
    public bool Available { get; set; }
    public int Cost { get; set; }

    public string Error { get { return null; } }
    public string this[string columnName]
    {
      get { return null; }
    }
  }

  public enum TalentUpgradeEntityType
  {
    Rune = 0,
    Catalist = 1,
  }

  public class TalentUpgradeEntityInfoModel : IDataErrorInfo
  {
    public long InstanceId { get; set; }
    public string PersistentId { get; set; }
    public int Chance { get; set; }
    public TalentUpgradeEntityType Type { get; set; }
    public int TalentLevelLimit { get; set; }

    public string Error { get { return null; } }
    public string this[string columnName]
    {
      get { return null; }
    }
  }


  public class TalentInfoModel : IDataErrorInfo
  {
    public int TalentClassId { get; set; }
    public long TalentInstanceId { get; set; }
    public string TalentName { get; set; }
    public string Description { get; set; }
    [Range( 0, int.MaxValue, ErrorMessage = "Value for {0} must be more than {1}." )]
    public int RefineRate { get; set; }
    public int BoundHeroClassId { get; set; }
    [Description("Bounded to hero")]
    public string BoundHeroClassName { get; set; }
    public long BoundHeroInstanceId { get; set; }
    public bool Selected { get; set; }
    public TalentRarity Rarity { get; set; }
    public int Tour { get; set; }
    public List<bool> TalentSets { get; set; }

    public TalentInfoModel()
    {
        TalentSets = new List<bool>(){false,false,false};
    }

    public TalentInfoModel(TalentInfo info)
    {
      if (info == null)
        throw new ArgumentNullException("info");

      this.TalentClassId = info.TalentClassId;
      this.TalentInstanceId = info.TalentInstanceId;
      this.RefineRate = info.RefineRate;
      this.BoundHeroClassId = info.BoundHeroClassId;
      this.BoundHeroInstanceId = info.BoundHeroInstanceId;
      TalentSets = new List<bool>() { false, false, false };
    }

    public TalentInfoModel(Talent t)
    {
      this.TalentClassId = t.Id;
      this.TalentName = t.Name;
      this.Description = t.Description;
      this.Rarity = t.Rarity;
      this.Tour = t.Tour;
      TalentSets = new List<bool>() { false, false, false };
    }

    public string Error { get { return null; } }
    public string this[string propName]
    {
      get
      {
        //if ( ( propName == "TalentName" ) && string.IsNullOrEmpty( TalentName ) )
        //  return "enter Talent Name";
        return null;
      }
    }
  }


  public class TalentAddModel
  {
    //public bool Checked { get; set; }
    public int Count{ get; set; }
    public int TalentClassId { get; set; }
    public string TalentName { get; set; }
    public TalentRarity Rarity { get; set; }

    public override string ToString()
    {
      return String.Format("Count: {0}, TalentClassId: {1}, TalentName: {2}, Rarity: {3}", Count, TalentClassId, TalentName, Rarity);
    }
  }


  public class BuildingInfoModel
  {
    public int ClassId { get; set; }
    public long InstanceId { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public int Level { get; set; }
    public int MaxLevel { get; set; }
    public bool InStorage { get; set; }

    public BuildingInfoModel(BuildingInfo info, CastleBuilding dbinfo)
    {
      if (dbinfo == null) throw new ArgumentNullException("dbinfo");
      if (info != null && info.Classid != dbinfo.Id)
        throw new ArgumentException(String.Format("Invalid db info {0} for object {1}", dbinfo, info ), "dbinfo");

      this.ClassId = dbinfo.Id;
      this.Name = dbinfo.Name;
      this.Description = dbinfo.Description;
      this.MaxLevel = dbinfo.MaxLevel;
      if (info != null)
      {
        this.InstanceId = info.Instanceid;
        this.Level = info.Level + 1; // Потому что в сервере уровни здания начинаются с 0
        this.InStorage = info.Instorage;
      }
      else
      {
        this.Level = 1;
        this.InStorage = true;
      }
    }
  }

  public class BuildingAddModel
  {
    public long Auid { get; set; }
    public int ClassId { get; set; }
    public int Level { get; set; }

    public BuildingAddModel()
    {
    }

    public BuildingAddModel(long auid)
    {
      this.Auid = auid;
      this.Level = 1;
    }
  }


  public class SendMessageModel : IDataErrorInfo
  {
    public string MessageTitle { get; set; }
    public string MessageText { get; set; }

    public string Error { get { return null; } }
    public string this[string propName]
    {
      get
      {
        if ( ( propName == "MessageTitle" ) && string.IsNullOrEmpty( MessageTitle ) )
          return "enter valid Message Title";
        if (propName == "MessageTitle" && string.IsNullOrEmpty( MessageTitle.Trim() ))
          return "enter valid Message Title";
        if ( ( propName == "MessageText" ) && string.IsNullOrEmpty( MessageText ) )
          return "enter valid Message Text";
        if ( ( propName == "MessageText" ) && string.IsNullOrEmpty( MessageText.Trim() ) )
          return "enter valid Message Text";
        return null;
      }
    }
  }


  public class UserOperationModel
  {
    public UserOperationType Type { get; set; }
    [Range(0, Int32.MaxValue)]
    public int Value { get; set; }
    /// <summary>
    /// Не добавить, а вычесть
    /// </summary>
    public bool Negative { get; set; }
    public string Reason { get; set; }
    public List<UserInfo> Users { get; set; }
    
    public struct UserInfo
    {
      public long Auid { get; set; }
      public string Nickname { get; set; }
      public int Complaints { get; set; }
    }
  }


  public class LoginInfoModel
  {
    public long SocialSessionId { get; set; }
    public string PlayerIp { get; set; }
    public string Cluster { get; set; }
    public DateTime LoginTime { get; set; }
    public DateTime? LogoutTime { get; set; }

    public LoginInfoModel()
    {
    }
    public LoginInfoModel(SocialSession session)
    {
      if (session == null) throw new ArgumentNullException("session");

      SocialSessionId = session.Id;
      PlayerIp = session.PlayerIp;
      Cluster = session.Cluster;
      LoginTime = session.StartTime;
      LogoutTime = session.EndTime == new DateTime( 1, 1, 1 ) ? (DateTime?)null : session.EndTime;
    }
  }

  public class BanOrMuteHistoryModel
  {
    public int Id { get; set; }
    public long Auid { get; set; }
    public DateTime Time { get; set; }
    public string EventType { get; set; }
    public int? Minutes { get; set; }
    public int? Points { get; set; }
    public string Reason { get; set; }
    public int Complaints { get; set; }
    public string GMLogin { get; set; }

    public BanOrMuteHistoryModel()
    {
    }

    public BanOrMuteHistoryModel(GMUserOperation op)
    {
      if (op == null)
        throw new ArgumentNullException("op");

      Id = op.Id;
      Auid = op.Player.Id;
      EventType = op.Type.ToString();
      Reason = op.Reason;
      Minutes = op.Type == GMUserOperationType.Ban || op.Type == GMUserOperationType.Mute || op.Type == GMUserOperationType.ModeratorMute
                  ? op.Minutes
                  : (int?) null;
      Points = op.Points;
      Time = op.Timestamp;
      GMLogin = op.GMLogin;
    }
  }

  public class FractionChangeHistoryModel
  {
    public DateTime Date { get; set; }
    public String ChangeDetails { get; set; }
    public String Tool { get; set; }
  }

  public class GMOperationInfoModel
  {
    public long Auid { get; set; }
    public string Type { get; set; }
    public string Data { get; set; }
    public string GMLogin { get; set; }
    public DateTime Timestamp { get; set; }
  }


  public class PagedModel
  {
    public const int PAGE_SIZE = 30;
    public int Page { get; set; }
    public int TotalPages { get; set; }

    public int Offset
    {
      get
      {
        if (Page <= 0)
          throw new Exception("Incorrect Page value = " + Page);
        return (Page - 1) * PAGE_SIZE;
      }
    }

    public void SetTotalRows(int rows)
    {
      TotalPages = (int) Math.Ceiling((float) rows / PAGE_SIZE);
    }

    public PagedModel()
    {
      Page = 1;
      TotalPages = 1;
    }

  }




  public class PlayerResourceFilterModel : PagedModel
  {
    public long Auid { get; set; }
    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }
    [DisplayName("Resource change type")]
    public ChangeType Type { get; set; }
    [DisplayName("Spent Gold")]
    public bool SpentGold { get; set; }
    [DisplayName("Spent Silver")]
    public bool SpentSilver { get; set; }
    [DisplayName("Spent Perl")]
    public bool SpentPerl { get; set; }
    [DisplayName( "Spent RedPerl" )]
    public bool SpentRedPerl { get; set; }
    [DisplayName("Spent other resources")]
    public bool SpentResourceN { get; set; }
    [DisplayName("Talents change")]
    public bool TalentsChange { get; set; }
    [DisplayName("Talent name or id")]
    public String TalentName { get; set; }
    [DisplayName("Resources event")]
    public String ResourcesEventIndex { get; set; }
    public SelectList ResourcesEventList { get; set; }
    [DisplayName("Talents event")]
    public String TalentsEventIndex { get; set; }
    public SelectList TalentsEventList { get; set; }

    public String MessageToUser { get; set; }
    public List<PlayerResourceInfoModel> Results { get; set; }

    public enum ChangeType
    {
      Any,
      Income,
      Expense
    }

    public SelectList GetAllTypes()
    {
      var values = from ChangeType t in Enum.GetValues(typeof (ChangeType))
                   select new {Id = t, Name = t.ToString()};
      return new SelectList(values, "Id", "Name");
    }

    public bool? Gain
    {
      get
      {
        switch (Type)
        {
          case ChangeType.Any:
            return null;
          case ChangeType.Income:
            return true;
          case ChangeType.Expense:
            return false;
          default:
            return null;
        }
      }
    }

    public PlayerResourceFilterModel()
    {
      SpentGold = true;
      SpentSilver = true;
      SpentPerl = true;
      SpentRedPerl = true;
      SpentResourceN = true;
      TalentsChange = true;
      TalentName = "";
      MessageToUser = "";
      ResourcesEventIndex = "";
      TalentsEventIndex = "";
    }
  }


  public class PlayerResourceInfoModel
  {
    public DateTime Timestamp { get; set; }
    public string Type { get; set; }
    public string Info { get; set; }
    public int? GoldChange { get; set; }
    public int? SilverChange { get; set; }
    public int? PerlChange { get; set; }
    public int? RedPerlChange { get; set; }
    public int? Resource1Change { get; set; }
    public int? Resource2Change { get; set; }
    public int? Resource3Change { get; set; }
    public int? ShardChange { get; set; }
    public string CurrencyChange { get; set; }
    public int? CurrencyChangeValue { get; set; }
    public int? GoldBefore { get; set; }
    public int? SilverBefore { get; set; }
    public int? PerlBefore { get; set; }
    public int? RedPerlBefore { get; set; }
    public int? Resource1Before { get; set; }
    public int? Resource2Before { get; set; }
    public int? Resource3Before { get; set; }
    public int? ShardBefore { get; set; }
    public string CurrencyBefore { get; set; }
    public int? CurrencyBeforeValue { get; set; }

    public PlayerResourceInfoModel()
    {
    }

    public PlayerResourceInfoModel(PlayerResourcesDTO dto)
    {
      Timestamp = dto.Timestamp;
      Type = dto.Type;
      Info = dto.Info;
      GoldChange = dto.GoldChange;
      SilverChange = dto.SilverChange;
      PerlChange = dto.PerlChange;
      RedPerlChange = dto.RedPerlChange;
      Resource1Change = dto.Resource1Change;
      Resource2Change = dto.Resource2Change;
      Resource3Change = dto.Resource3Change;
      ShardChange = dto.ShardChange;
      CurrencyChange = dto.CurrencyChange;
      CurrencyChangeValue = dto.CurrencyChangeValue;
      GoldBefore = dto.GoldBefore;
      SilverBefore = dto.SilverBefore;
      PerlBefore = dto.PerlBefore;
      RedPerlBefore = dto.RedPerlBefore;
      Resource1Before = dto.Resource1Before;
      Resource2Before = dto.Resource2Before;
      Resource3Before = dto.Resource3Before;
      ShardBefore = dto.ShardBefore;
      CurrencyBefore = dto.CurrencyBefore;
      CurrencyBeforeValue = dto.CurrencyBeforeValue;
    }
  }

  public class PayEditNicknameModel
  {
    [Required]
    public string Login { get; set; }
    
    [Required]
    [DisplayName("New nickname")]
    public string Nickname { get; set; }
  }

  public class PayChangeFactionModel
  {
    [Required]
    public string Login { get; set; }
    
    [Required]
    [DisplayName("New faction")]
    public FractionEnum NewFaction { get; set; }
  }

  public class LampInfoModel
  {
    [Required]
    public string Login { get; set; }

    [Required]
    [DisplayName( "Bonus" )]
    public int Bonus { get; set; }

    [Required]
    [DisplayName( "Gold bonus" )]
    public int Gold { get; set; }

    [Required]
    [DisplayName( "Transaction" )]
    public int Transaction { get; set; }

    [Required]
    [DisplayName( "Duration" )]
    public long Duration { get; set; }
  }

  public class UpgradeHeroTalentsInfoModel
  {
      [Required]
      public string Login { get; set; }

      [Required]
      [DisplayName("Count runes")]
      public int CountRunes { get; set; }
  }

  public class PayServiceModel
  {
    [Required]
    public string Login { get; set; }
    [Required]
    public int ServiceTypeId { get; set; }
    [Required, Range(1, Int32.MaxValue)]
    public int Days { get; set; }

    public DateTime? PremiumAccountDate { get; set; }

    public class ServiceTypeModel
    {
      public int Id { get; set; }
      public string Desc { get; set; }
      public PayServiceType Type { get; set; }
    }

    private readonly List<ServiceTypeModel> types;

    public PayServiceModel()
    {
      types = new List<ServiceTypeModel>
                {
                  new ServiceTypeModel {Id = 1, Desc = "Add premium account", Type = PayServiceType.PremiumAccount},
                  new ServiceTypeModel {Id = 2, Desc = "Withdraw premium account", Type = PayServiceType.PremiumAccount},
                };
    }

    public List<ServiceTypeModel> GetAllTypes()
    {
      return types;
    }
  }

  public enum TicketStateEnum
  {
    NotActivated = 0,
    InTournament = 1,
    TournamentLost = 2,
  }

  public enum TicketPriseStateEnum
  {
    HasNoPrise = 0,
    PriseInProgress = 1,
    HasPrise = 2,
  }

  public enum TicketBoughtTypeEnum
  {
    BoughtForGold = 0,
    BoughtForSilver = 1,
    GiftedWithPayment = 2,
    GivenByGM = 3,
  }

  public class TournamentInfoModel
  {
    [Required]
    public long Auid { get; set; }

    [Required]
    public string Login { get; set; }

    [Required]
    [DisplayName("Wins")]
    public int Wins { get; set; }

    [Required]
    [DisplayName("Losses")]
    public int Losses { get; set; }

    [Required]
    [DisplayName("Time of last tournament game")]
    public DateTime LastGameTime { get; set; }

    [Required]
    [DisplayName("Has prise for tournament")]
    public TicketPriseStateEnum TicketPriseState { get; set; }

    [Required]
    [DisplayName( "TicketBoughtType" )]
    public TicketBoughtTypeEnum TicketBoughtType { get; set; }

    [Required]
    [DisplayName("Ticket state")]
    public TicketStateEnum State { get; set; }

    [Required]
    [DisplayName("Missed Games")]
    public int MissedGames { get; set; }

    [Required]
    [DisplayName("Is synchronized")]
    public bool IsSynchronized { get; set; }
  }

  public class GiveTournamentTicketModel
  {
     
  }

  public class TournamentGamesInfoModel
  {
    public long Auid { get; set; }
    public DateTime GameStartTime { get; set; }
    public int GameDuration { get; set; }
    public string SessionId { get; set; }
  }

  public class QuestInfoModel
  {
    public long Auid { get; set; }

    public int QuestId { get; set; }
    public string Name { get; set; }
    [DisplayName("Description")]
    public string Desc { get; set; }
    public QuestStatus Status { get; set; }

    public QuestInfoModel(QuestInfo info)
    {
      Auid = info.Auid;
      QuestId = info.Questid;
      Name = info.Name;
      Status = info.Status;
    }
  }

  public class FlagModel
  {
    public string FlagPersistentId { get; set; }
    public int FlagPrice { get; set; }
  }

  public class AdminMessageInfoModel
  {
    public string MessageTitle { get; set; }
    public string MessageText { get; set; }
    public string GMLogin { get; set; }
    public DateTime Timestamp { get; set; }
  }


  public class GeolocationInfoModel
  {
    public long Auid { get; set; }
    public string Country { get; set; }
    public string CountryName { get; set; }
    public string Region { get; set; }
    public string RegionName { get; set; }
    public string City { get; set; }
    public string GMCountry { get; set; }
    public string GMCountryName { get; set; }
    public string GMRegion { get; set; }
    public string GMRegionName { get; set; }
    public string GMCity { get; set; }
  }


  public class BindGeolocationModel
  {
    public long Auid { get; set; }
    public string Country { get; set; }
    public string Region { get; set; }
    public string City { get; set; }
  }


  public class CWPlayerResourcesFilterModel : PagedModel
  {
    public long Auid { get; set; }
    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }

    public List<CWPlayerPointsDTO> Results { get; set; }
  }


  public class CWGuildResourcesFilterModel : PagedModel
  {
    public long GuildId { get; set; }
    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }

    public List<CWGuildPointsDTO> Results { get; set; }
  }


  public class LeavePointsFilterModel : PagedModel
  {
    public long Auid { get; set; }
    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }

    public int LeaverCount { get; set; }
    public int LeaverGMCount { get; set; }
    public List<LeaverPointsLog> Results { get; set; }
  }


  public class RuneOperationsFilterModel
  {
    public long Auid { get; set; }
    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }

    public List<RuneOperationDTO> Results { get; set; }
  }

  public class FriendInfoModel : IDataErrorInfo
  {
    public long Auid { get; set; }
    public string Nickname { get; set; }
    public string GuildShortName { get; set; }

    public string Error { get { return null; } }
    public string this[string columnName]
    {
      get { return null; }
    }
  }

  public class BrokenAccountsModel
  {
    public string BackupDate { get; set; }
    public string Login { get; set; }
    public string Nickname { get; set; }
  }

  public partial class SeasonAwardsModel
  {
    public int SeasonId { get; set; }    
    public string SeasonName { get; set; }
    public DateTime? StartDate { get; set; }
    public DateTime? EndDate { get; set; }
    [DisplayName("Perls")]
    public int Perls { get; set; }
    [DisplayName("Skin")]
    public string Skin { get; set; }
    [DisplayName("Flag")]
    public string Flag { get; set; }
    [DisplayName("Talents")]
    public string Talents { get; set; }
    [DisplayName("Lootboxes")]
    public string Lootboxes { get; set; }
  }

  public partial class SeasonInfoModel
  {
      public int SeasonId { get; set; }
      [DisplayName("SeasonName")]
      public string SeasonName { get; set; }
      public DateTime? StartDate { get; set; }
      public DateTime? EndDate { get; set; }
      [DisplayName("SeasonRating")]
      public int SeasonRating { get; set; }
      [DisplayName("LeagueIndex")]
      public int LeagueIndex { get; set; }
      [DisplayName("CurLeaguePlace")]
      public int CurLeaguePlace { get; set; }
      [DisplayName("BestLeaguePlace")]
      public int BestLeaguePlace { get; set; }
  }
    
}