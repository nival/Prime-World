using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Models
{
  public class GuildSearchModel
  {
    public long? GuildId { get; set; }
    public string ShortName { get; set; }
    public string FullName { get; set; }
  }

  public class GuildMemberModel
  {
    public long GuildId { get; set; }
    [DisplayName("Auid")]
    public long Auid { get; set; }
    [DisplayName("Nickname")]
    public string Nickname { get; set; }
    [DisplayName("Is Officer")]
    public bool IsOfficer { get; set; }
    [DisplayName("Added today")]
    public int AddedTalentsDailyCount { get; set; }
    [DisplayName("Taken today")]
    public int TakenTalentsDailyCount { get; set; }

    public string Error { get; set; }

    public GuildMemberModel()
    {
    }

    public GuildMemberModel(GuildMemberInfoResponse response, long guildid)
    {
      if (response.Result != RequestResult.Success)
      {
        Error = response.Result.ToString();
        return;
      }
      GuildId = guildid;
      Auid = response.GuildMember.Auid;
      Nickname = response.GuildMember.Nickname;
      IsOfficer = response.GuildMember.Isofficer;
      AddedTalentsDailyCount = response.GuildMember.AddedTalentsDailyCount;
      TakenTalentsDailyCount = response.GuildMember.TakenTalentsDailyCount;
    }
  }

  public class GuildShortInfoModel
  {
    public long GuildId { get; set; }
    public string ShortName { get; set; }
    public string FullName { get; set; }

    public GuildShortInfoModel(long guildId, string shortName, string fullName)
    {
      GuildId = guildId;
      ShortName = shortName;
      FullName = fullName;
    }

    public GuildShortInfoModel()
      : this(0, "", "") {}

    public GuildShortInfoModel(GuildShortInfo guild)
    {
      if (guild != null)
      {
        GuildId = guild.Guildid;
        ShortName = guild.Shortname;
        FullName = guild.Fullname;
      }
      else
      {
        GuildId = 0;
        ShortName = "";
        FullName = "";
      }
    }
  }

  public class GuildInfoModel
  {
    public long GuildId { get; set; }
    public string ShortName { get; set; }
    public string FullName { get; set; }
    public string MessageOfTheDay { get; set; }
    public long LeaderAuid { get; set; }
    public string LeaderNickname { get; set; }
    public List<GuildMemberModel> Members { get; set; }
    [DisplayName("Experience")]
    public long GuildExperience { get; set; }
    public int IconChangesCount { get; set; }
    public int GuildLevel { get; set; }
    public int GuildBankAddLimit { get; set; }
    public int GuildBankTakeLimit { get; set; }
    public int CWPoints { get; set; }
    public int CWRating { get; set; }
    public GuildShortInfoModel Suzerain { get; set; }
    public List<GuildShortInfoModel> Vassals { get; set; }
    public DateTime? SiegeEndTime { get; set; }
    public DateTime? ReleaseLockTime { get; set; }

    public string Error { get; set; }

    public GuildInfoModel()
    {
    }

    public GuildInfoModel(GuildInfoResponse response)
    {
      if (response.Result != RequestResult.Success)
      {
        Error = response.Result.ToString();
        return;
      }

      GuildId = response.Guild.Guildid;
      ShortName = response.Guild.Shortname;
      FullName = response.Guild.Fullname;
      MessageOfTheDay = response.Guild.Messageoftheday;
      LeaderAuid = response.Guild.Leaderauid;
      LeaderNickname = response.Guild.Leadernickname;
      GuildExperience = response.Guild.GuildExperience;
      IconChangesCount = response.Guild.IconChangesCount;
      GuildLevel = response.Guild.GuildLevel;
      GuildBankAddLimit = response.Guild.GuildBankAddLimit;
      GuildBankTakeLimit = response.Guild.GuildBankTakeLimit;
      CWPoints = response.Guild.Cwguildpoints;
      CWRating = response.Guild.Cwrating;
      Suzerain = new GuildShortInfoModel(response.Guild.Suzerain);
      if (Suzerain.GuildId == -1)
      {
        Suzerain.ShortName = "npc";
        Suzerain.FullName = "Suzerain";
      }

      if (response.Guild.Vassals != null)
      {
        Vassals = response.Guild.Vassals.Select(v => new GuildShortInfoModel
        {
          GuildId = v.Guildid,
          ShortName = v.Guildid == -1 ? "npc" : v.Shortname,
          FullName = v.Guildid == -1 ? "Vassal" : v.Fullname
        }).ToList();
      }
      SiegeEndTime = response.Guild.Siegeendtime != 0 ? (DateTime?)response.Guild.Siegeendtime.FromUnixTimestamp() : null;
      ReleaseLockTime = response.Guild.Releaselocktime != 0 ? (DateTime?)response.Guild.Releaselocktime.FromUnixTimestamp() : null;

      if (response.Guild.Members != null)
        Members = response.Guild.Members
          .Select(m => new GuildMemberModel { GuildId = response.Guild.Guildid, Auid = m.Auid, Nickname = m.Nickname, 
            IsOfficer = m.Isofficer, AddedTalentsDailyCount = m.AddedTalentsDailyCount, TakenTalentsDailyCount = m.TakenTalentsDailyCount})
          .ToList();
    }
  }

  public class GuildEditModel
  {
    public long GuildId { get; set; }
    [Required]
    public string ShortName { get; set; }
    [Required]
    public string FullName { get; set; }
    public string MessageOfTheDay { get; set; }
    [DisplayName("Experience (will not affect player's guild building)")]
    public long GuildExperience { get; set; }
    [DisplayName("Guild rating")]
    public int GuildRating { get; set; }
    [DisplayName("Clan War points")]
    public int CWPoints { get; set; }
  }

  public class GuildSetIconModel
  {
    public string FullName { get; set; }
    public long GuildId { get; set; }
    public int IconChangesCount { get; set; }
    public long LeaderAuid { get; set; }
    public HttpPostedFileBase Image { get; set; }
  }

  public class GuildChangeLeaderModel
  {
    public long GuildId { get; set; }
    public string FullName { get; set; }
    public long OldLeader { get; set; }
    public long NewLeader { get; set; }
    public IEnumerable<GuildMemberModel> Members { get; set; }
  }

  public class GuildRemoveMembersModel
  {
    public long GuildId { get; set; }
    public string FullName { get; set; }
    public IEnumerable<GuildMemberModel> Members { get; set; }
    public IEnumerable<long> RemoveMembers { get; set; }
  }

  public class GuildTalentModel
  {
    public long InstanceId { get; set; }
    public int PersistentId { get; set; }
    public string Name { get; set; }
    public long HolderAuid { get; set; }
    public long OwnerAuid { get; set; }
    public string HeroClassId { get; set; }
    public int Points { get; set; }
  }

  public class GuildTalentsListModel
  {
    public long GuildId { get; set; }
    public List<GuildTalentModel> Talents { get; set; }
    public string Error { get; set; }

    public GuildTalentsListModel()
    {
    }

    public GuildTalentsListModel(long auid)
    {
      GuildId = auid;
      Talents = new List<GuildTalentModel>();
    }
  }

  public class GuildChangeSuzerainModel
  {
    public long GuildId { get; set; }
    public string ShortName { get; set; }
    public string FullName { get; set; }
    public long SuzerainId { get; set; }
  }
}