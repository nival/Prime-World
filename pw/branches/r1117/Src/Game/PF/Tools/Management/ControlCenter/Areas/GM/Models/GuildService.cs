using System;
using System.Collections.Generic;
using System.Linq;
using AccountLib;

namespace ControlCenter.Areas.GM.Models
{
  public interface IGuildService
  {
    GuildInfoModel GetGuildInfoById(long guildid);
    GuildInfoModel GetGuildInfoByName(string shortname, string fullname);
    GuildMemberModel GetGuildMemberById( long guildid, long auid );
    string EditGuild(GuildEditModel model, string gmlogin);
    string EditMember( long guildid, GuildMemberModel member, string gmlogin );
    string RemoveMembers( long guildid, long[] auids, string gmlogin );
    string ChangeLeader( long guildid, long auid, string gmlogin );
    string SetIcon(long guildid, byte[] image);
    string SwitchToNewGuildIcon( long guildid, string gmlogin );
    string TryToPayForGuildIconChange( long leaderauid, int changeiter );
    GuildTalentsListModel GetFreeGuildBankTalents( long guildid );
    GuildTalentsListModel GetTakenGuildBankTalents(long guildid);
    string ReturnTalentToOwner( long guildid, long talentId, string gmlogin );
    string ReturnTalentToGuildBank( long guildid, long talentId, string gmlogin );
    string AcquireGuildLock(long guildid, string gmlogin);
    string ReleaseGuildLock(long guildid, string gmlogin);
    string StopGuildSiege(long targetguildid, string gmlogin);
    string AddGuildSuzerain(long guildid, long suzerainguildid, string gmlogin);
    string RemoveGuildSuzerain(long guildid, string gmlogin);
    StringUIResponse GetFullGuildDump( long guildid, bool zip );
  }
  
  public class GuildService : IGuildService
  {
    private static Uri gmaccountingAddress;
    public static string GmAccountingAddress
    {
      set
      {
        if (!Uri.TryCreate(value, UriKind.Absolute, out gmaccountingAddress))
          throw new ArgumentException("Invalid value for gmaccountingAddress = " + (value ?? "(null)"));
      }
    }

    private IAccountManagementService accountManagementService;

    public GuildService()
    {
      if (gmaccountingAddress == null)
        throw new InvalidOperationException("gmaccountingAddress is null");

      accountManagementService = new AccountManagementService(gmaccountingAddress);
    }

    public static string GetVerboseErrorMessage( RequestResult result )
    {
      if ( result == RequestResult.TransportException )
        return "Transport exception during server request";
      if ( result == RequestResult.LoginNotExist )
        return "This Login doesn't exist";
      if ( result == RequestResult.AuidNotExist )
        return "This Auid doesn't exist";
      if ( result == RequestResult.ServerReturnedNull )
        return "Server returned null result";
      return Enum.GetName( typeof( RequestResult ), result );
    }

    public GuildInfoModel GetGuildInfoById(long guildid)
    {
      var response = accountManagementService.GetGuildById(guildid);
      if (response == null)
        return new GuildInfoModel { Error = "Couldn't get response from server, see log for details." };
      
      return new GuildInfoModel(response);
    }

    public GuildInfoModel GetGuildInfoByName(string shortname, string fullname)
    {
      var response = accountManagementService.GetGuildByName(shortname, fullname);
      if (response == null)
        return new GuildInfoModel { Error = "Couldn't get response from server, see log for details." };

      return new GuildInfoModel(response);
    }

    public GuildMemberModel GetGuildMemberById(long guildid, long auid)
    {
      var response = accountManagementService.GetGuildMemberById(guildid, auid);
      if (response == null)
        return new GuildMemberModel{ Error = "Couldn't get response from server, see log for details." };

      return new GuildMemberModel(response, guildid);
    }

    public string EditGuild(GuildEditModel model, string gmlogin)
    {
      var guildEditInfo = new GuildEditInfo
      {
        Guildid = model.GuildId,
        Shortname = model.ShortName,
        Fullname = model.FullName,
        Messageoftheday = model.MessageOfTheDay,
        GuildExperience = model.GuildExperience,
        Cwguildpoints = model.CWPoints,
        Guildrating = model.GuildRating
      };
      var result = accountManagementService.EditGuild(guildEditInfo, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string EditMember( long guildid, GuildMemberModel member, string gmlogin )
    {
      GuildMemberInfo guildMember = new GuildMemberInfo
      {
        Auid = member.Auid,
        AddedTalentsDailyCount = member.AddedTalentsDailyCount,
        TakenTalentsDailyCount = member.TakenTalentsDailyCount,
        Isofficer = member.IsOfficer,
        Nickname = member.Nickname
      };

      var result = accountManagementService.EditGuildMember(guildid, guildMember, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string RemoveMembers( long guildid, long[] auids, string gmlogin )
    {
      if (auids == null || auids.Length == 0)
        return null;

      var result = accountManagementService.RemoveGuildMembers(guildid, auids.ToList(), gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string ChangeLeader( long guildid, long auid, string gmlogin )
    {
      var result = accountManagementService.ChangeGuildLeader(guildid, auid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string SetIcon(long guildid, byte[] image)
    {
      var result = accountManagementService.SetGuildIcon(guildid, image);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string SwitchToNewGuildIcon( long guildid, string gmlogin )
    {
      var result = accountManagementService.SwitchToNewGuildIcon( guildid, gmlogin );
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string TryToPayForGuildIconChange( long leaderauid,int changeiter )
    {
      var result = accountManagementService.TryToPayForGuildIconChange( leaderauid, changeiter );
      if ( result == null )
        return null;
      return result.Result == RequestResult.Success ? null : 
        string.Format("{0}: {1}", result.Result, result.Error);
    }

    public GuildTalentsListModel GetFreeGuildBankTalents( long guildid )
    {
      var response = accountManagementService.GetFreeGuildBankTalents(guildid);
      if (response == null)
        return new GuildTalentsListModel{Error = "Error in request processing"};

      List<TalentInfoModel> alltalents = GetTalentsCatalog();
      List<HeroInfoModel> allheroes = GetHeroesCatalog();

      var talentsModel = new GuildTalentsListModel(guildid);
      foreach (var freeTal in response.GuildBankTalents)
      {
        var modelFreeTalent = new GuildTalentModel
        {
          HeroClassId = freeTal.HeroClassId == 0 ? null : allheroes.Single(h => h.HeroClassId == freeTal.HeroClassId).HeroName, 
          HolderAuid = freeTal.Holder, Name = alltalents.Single( t => t.TalentClassId == freeTal.PersistentId ).TalentName, OwnerAuid = freeTal.Owner,
          PersistentId = freeTal.PersistentId, Points = freeTal.Points, InstanceId = freeTal.InstanceId};

        talentsModel.Talents.Add(modelFreeTalent);
      }
      return talentsModel;
    }

    public GuildTalentsListModel GetTakenGuildBankTalents(long guildid)
    {
      var response = accountManagementService.GetTakenGuildBankTalents(guildid);
      if (response == null)
        return new GuildTalentsListModel { Error = "Error in request processing" };

      List<TalentInfoModel> alltalents = GetTalentsCatalog();
      List<HeroInfoModel> allheroes = GetHeroesCatalog();

      var talentsModel = new GuildTalentsListModel(guildid);
      foreach (var takenTal in response.GuildBankTalents)
      {
        var modelTakenTalent = new GuildTalentModel
        {
          HeroClassId = takenTal.HeroClassId == 0 ? null : allheroes.Single(h => h.HeroClassId == takenTal.HeroClassId).HeroName,
          HolderAuid = takenTal.Holder,
          Name = alltalents.Single(t => t.TalentClassId == takenTal.PersistentId).TalentName,
          OwnerAuid = takenTal.Owner,
          PersistentId = takenTal.PersistentId,
          Points = takenTal.Points,
          InstanceId = takenTal.InstanceId
        };

        talentsModel.Talents.Add(modelTakenTalent);
      }
      return talentsModel;
    }

    public string ReturnTalentToOwner( long guildid, long talentId, string gmlogin )
    {
      var result = accountManagementService.ReturnTalentToOwner(guildid, talentId, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public string ReturnTalentToGuildBank( long guildid, long talentId, string gmlogin )
    {
      var result = accountManagementService.ReturnTalentToGuildBank(guildid, talentId, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public List<HeroInfoModel> GetHeroesCatalog()
    {
      return HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName).ToList();
    }

    public List<TalentInfoModel> GetTalentsCatalog()
    {
      return TalentsCatalog.GetAllTalents().OrderBy(t => t.TalentName).ToList();
    }

    public string AcquireGuildLock(long guildid, string gmlogin)
    {
      var result = accountManagementService.AcquireGuildLock(guildid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }
    public string ReleaseGuildLock(long guildid, string gmlogin)
    {
      var result = accountManagementService.ReleaseGuildLock(guildid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }
    public string StopGuildSiege(long targetguildid, string gmlogin)
    {
      var result = accountManagementService.StopGuildSiege(targetguildid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }
    public string AddGuildSuzerain(long guildid, long suzerainguildid, string gmlogin)
    {
      var result = accountManagementService.AddGuildSuzerain(guildid, suzerainguildid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }
    public string RemoveGuildSuzerain(long guildid, string gmlogin)
    {
      var result = accountManagementService.RemoveGuildSuzerain(guildid, gmlogin);
      return result == RequestResult.Success ? null : result.ToString();
    }

    public StringUIResponse GetFullGuildDump( long guildid, bool zip )
    {
      StringDataResponse fullDumpResp = accountManagementService.GetFullGuildDump( guildid, zip );
      var uiResp = new StringUIResponse();
      if ( fullDumpResp.Result != RequestResult.Success )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( fullDumpResp.Result );
        return uiResp;
      }
      if ( string.IsNullOrEmpty( fullDumpResp.Data ) )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.BadResult );
        return uiResp;
      }
      uiResp.Data = fullDumpResp.Data;
      return uiResp;
    }
  }
}