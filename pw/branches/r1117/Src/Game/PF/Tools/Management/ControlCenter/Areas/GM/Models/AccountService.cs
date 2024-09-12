using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Areas.MassOperations.Models;
using ControlCenter.Helpers;
using DAL.Repositories;
using log4net;
using DAL.Entities;
using System.Configuration;
using System.Linq.Expressions;
using MassOperationType = ControlCenter.Areas.MassOperations.Models.MassOperationType;

namespace ControlCenter.Areas.GM.Models
{
  public class GetTalentInfoListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<TalentInfoModel> talentsList { get; set; }
  }
  public class GetSeasonInfoListResp
  {
      public string ErrorIfExistToShow { get; set; }
      public List<SeasonInfoModel> seasonInfoList { get; set; }
  }
  public class GetHeroInfoListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<HeroInfoModel> heroesList { get; set; }
  }
  public class GetBroadcastMessageListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<BroadcastModel> broadcastList { get; set; }
  }
  public class GetAccountsResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<AccountInfoModel> accountsList { get; set; }
  }
  public class StringUIResponse
  {
    public string ErrorIfExistToShow { get; set; }
    public string Data { get; set; }
  }

  public class GetFriendsInfoListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<FriendInfoModel> Friends { get; set; }
  }

  public class GetTournamentGamesListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<TournamentGamesInfoModel> tournamentGamesList { get; set; }
  }

  public class GetBackupDatesListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<string> BackupDates { get; set; }
  }

  public class GetFlagListResp
  {
    public string ErrorIfExistToShow { get; set; }
    public List<FlagModel> OwnedFlagsList { get; set; }
    public List<FlagModel> NotOwnedFlagsList { get; set; }
    public List<FlagModel> AdminFlagsList { get; set; }

    public GetFlagListResp()
    {
      OwnedFlagsList = new List<FlagModel>();
      NotOwnedFlagsList = new List<FlagModel>();
      AdminFlagsList = new List<FlagModel>();
    }
  }

  public class PlayerWipeResp
  {
    public AccountShortInfoModel PlayerModel;
    public string ErrorIfExistToShow;
  }

  public interface IAccountService
  {
    AccountInfoModel GetAccountBySNUid( string snid, string snuid );
    AccountInfoModel GetAccountByAuid( long auid );
    GetAccountsResp GetAccountsByNickName( string nickName );
    string EditAccount( AccountInfoModel editAcc, string gmLogin );
    GetTalentInfoListResp GetAccountLibrary( string login );
    List<string> SocialNetworks { get; }

      string EditQuestForTalent(string login, QuestForTalentModel editModel, string gmLogin);
      QuestsForTalentsInfoResponse GetQuestsForTalentsByAuid(string login);
    
    bool CheckLocalePermissionByAuid(GMToolsPrincipal user, long auid, out string error);
    bool CheckLocalePermissionBySNUid(GMToolsPrincipal user, string snid, string snuid, out string error);

    List<QuestInfoModel> GetQuests(long auid, out string error);
    string QuestChange(long auid, int questid, string action, string gmlogin);
    
    List<HeroInfoModel> GetHeroesCatalog();
    GetHeroInfoListResp GetAccountHeroes( string login );
    string UnlockHero( string login, int heroClassId, string gmLogin );
    string EditHero( string login, HeroInfoModel heroEdit, string gmLogin );
    string LockHero( string login, long heroInstanceId, string gmLogin );

    string EditSeasonAwards(string login, SeasonAwardsModel awardEdit, string gmLogin);
    string EditSeasonInfo(string login, long heroInstanceId, SeasonInfoModel seasonEdit, string gmLogin);

    List<SkinInfoModel> GetAccountSkins(long auid);
    string AddSkin(long auid, string skinPersistentId, string gmLogin);
    string DeleteSkin(long auid, string skinPersistentId, string gmLogin);

    List<TalentUpgradeEntityInfoModel> GetAccountTalentUpgradeEntities(long auid);
    string DeleteTalentUpgradeEntity(long auid, long instanceId, string gmLogin);

    List<BuildingInfoModel> GetAccountBuildings(long auid);
    string MoveBuildingToStorage(long auid, long buildingInstanceId, string gmLogin);
    string AddBuilding(long auid, int buildingClassId, int level, string gmLogin);
    string DeleteBuilding(long auid, long buildingInstanceId, string gmLogin);

    List<TalentInfoModel> GetTalentsCatalog();
    List<TalentInfoModel> GetTalentsByRarity(TalentRarity rarity);

    GetTalentInfoListResp GetHeroTalentSet( string login, long heroInstanceId );
    GetSeasonInfoListResp GetHeroSeasonsInfo(string login, long heroInstanceId);
    string UnlockTalent( string login, long heroInstanceId, int talentClassId, string gmLogin );
    string UnlockTalents( string login, long heroInstanceId, int[] talentIds, string gmLogin );
    string EditTalent( string login, TalentInfoModel editTalent, string gmLogin );
    string LockTalent( string login, long heroInstanceId, long talentInstanceId, string gmLogin );

    string MoveTalentFromTalentSetToLibrary( string login, long heroInstanceId, long talentInstanceId, string gmLogin );
    string MoveTalentFromLibraryToTalentSet( string login, long heroInstanceId, long talentInstanceId, string gmLogin );
    string RemoveTalentFromTalentSet( string login, long heroInstanceId, long talentInstanceId, int talentSetId, string gmLogin );    

    string GiveLamp( string login, int bonus, int gold, int transaction, long duration, string gmLogin );
    string GiveUpgradeHeroTalents(string login, int usesLeft, string gmLogin);
    LampInfoResponse GetLampInfo( string login );
    UpgradeHeroTalentsInfoResponse GetUpgradeHeroTalentsInfo(string login);

    string DisjointSN(long auid, string sn);
    string ChangeFSN( long auid, string sn );
    string RemoveSaAccount(long auid);

    string SendMessageToUser( long auid, string login, string messageTitle, string messageText, string gmLogin );
    RequestResult UserOperation(long auid, UserOperationType type, int minutes, string reason, List<int> claims, string gmLogin, List<long> claimAuids);
    string ResetUserAccount( string login, string gmLogin );
    string KickUser( string login, string gmLogin );

    string CreateBroadcastMessage( BroadcastModel createModel, string gmLogin );
    List<string> GetBroadcastLocales();
    List<string> GetBroadcastLocales(GMToolsPrincipal user);
    string EditBroadcastMessage( BroadcastModel editModel, string gmLogin );
    string DeleteBroadcastMessage(int id, string gmLogin);
    GetBroadcastMessageListResp GetBroadcastList(GMToolsPrincipal user, int page, int pageSize, out int totalpages);
    BroadcastModel GetBroadcastById(int id, GMToolsPrincipal user);
    string StartMessageRotation(int id, string gmLogin);
    string StopMessageRotation(int id, string gmLogin);

    string GetSocServerVersion();
    StringUIResponse GetFullUserDump( string login, bool zip );
    string ApplyFullUserDump( string login, string dumpdata );
    string RemoveFakeAuid( string login );
    string ActivateEmail( string email, string gmLogin );
    GetBackupDatesListResp GetBackups();
    StringUIResponse GetBrokenUserDump( string login, string date, bool zip );
    StringUIResponse GetBrokenUserDumpByNickname( string nickname, string date, bool zip );

    string EditFreeChanges( string login, string gmLogin, int nickChanges, int fractionChanges );
    string EditNickname( string login, string gmLogin, string nickname );

    StringUIResponse CheckAccountValidity( string login );
    string FixAccount( string login, string gmLogin );

    string PayEditNickname(string login, string nickname);
    string PayChangeFraction(string login, int fraction);
    string PayService(string login, PayServiceType type, int days, string gmLogin);

    TournamentInfoResponse GetAccountTournamentInfo( string login );
    string EditTournamentInfo( string login, int wins, int losses, long lastGameTime, TicketPriseState ticketPriseState, TicketState state, TicketBoughtType boughtType, int missedGames, bool isSynchronized, string gmLogin );
    GiveTournamentTicketResponse GiveTournamentTicket(string login);
    GetTournamentGamesListResp GetAccountTournamentGames(string login);

    GetFlagListResp GetAccountFlags(string login);
    string LockFlag( string login, string flagPersistentId, string gmLogin );
    string UnlockFlag( string login, string flagPersistentId, string gmLogin );

    List<AdminMessageInfoModel> GetAccountAdminMessages( string login, int pageNum, int pageSize, out int pageQuant );

    string BindGeolocation(long auid, string country, string region, string city, string gmlogin);
    string ResetGeolocation(long auid, string gmlogin);

    List<String> GetTalentsEvents();
    List<String> GetResourceEvents();

    GetFriendsInfoListResp GetAccountFriends( long auid );
    string RemoveFriend( long auid, long friendAuid );
    OperationDetails<string> ProcessMassOperation(MassOperationsModel model, List<long> auidsInt, string gmlogin);
    List<MassOperationInfoModel> GetMassOperationsInfo();
    string DeleteMassOperationInfo(int operationId);

    PlayerWipeResp FindPlayerByNickname(string nickname);
    PlayerWipeResp FindPlayerByEmail(string email);
    PlayerWipeResp PlayerChangeEmail(string email, string newEmail, string newPass);
    //wipe
    PlayerWipeResp PlayerRemoveNickname(string email, string nickname);
  }

  public class AccountService : IAccountService
  {
    private static ILog _log = LogManager.GetLogger( typeof( AccountService ) );

    private IAccountManagementService accountManagementService;

    public static string GmAccountingAddress { get; set; }

    public static string GetVerboseErrorMessage( RequestResult result )
    {
      if ( result == RequestResult.TransportException )
        return "Transport exception during server request";
      if ( result == RequestResult.LoginNotExist )
        return "This Login doesn't exist";
      if ( result == RequestResult.SnUidNotExist )
        return "This SN Uid doesn't exist";
      if ( result == RequestResult.AuidNotExist )
        return "This Auid doesn't exist";
      if ( result == RequestResult.ServerReturnedNull )
        return "Server returned null result";
      return Enum.GetName( typeof( RequestResult ), result );
    }


    public AccountService()
    {
      Uri gmAccounting_url;
      if ( GmAccountingAddress != null && Uri.TryCreate( GmAccountingAddress, UriKind.Absolute, out gmAccounting_url ) )
      {
        accountManagementService = new AccountManagementService( gmAccounting_url );
      }
      else
      {
        _log.ErrorFormat( "Invalid cluster address {0}", GmAccountingAddress ?? "(null)" );
      }
    }


    public AccountService( IAccountManagementService svc )
    {
      this.accountManagementService = svc;
    }


    private static string PerformAndGetError( Expression<Func<RequestResult>> function )
    {
      string errorString = null;
      Func<RequestResult> toExecute = function.Compile();
      RequestResult requestResult = toExecute();
      if ( requestResult != RequestResult.Success )
      {
        errorString = GetVerboseErrorMessage( requestResult );
        _log.Error( string.Format( "{0}, was in : {1}", errorString, ( (MethodCallExpression)function.Body ).Method ) );
      }
      return errorString;
    }

    private static RequestResult PerformAndGetErrorCode(Expression<Func<RequestResult>> function)
    {
      var toExecute = function.Compile();
      var requestResult = toExecute();
      if (requestResult == RequestResult.Success) return requestResult;
      var errorString = GetVerboseErrorMessage(requestResult);
      _log.Error(string.Format("{0}, was in : {1}", errorString, ((MethodCallExpression)function.Body).Method));
      return requestResult;
    }


    private static readonly object _locker = new object();
    private static List<string> _socialNetworks;
    public List<string> SocialNetworks
    {
      get
      {
        lock (_locker)
        {
          if (_socialNetworks == null)
          {
            var resp = accountManagementService.GetSocialNetworks();
            if (resp == null || resp.Result != RequestResult.Success || resp.Socialnetworks.Count == 0)
            {
              _log.Error("Failed to get social networks list from server, RequestResult = " + (resp != null ? resp.Result : RequestResult.ServerReturnedNull));
              return new List<string>();
            }
            _socialNetworks = resp.Socialnetworks;
          }
        }
        return _socialNetworks;
      }
    }

    public bool CheckLocalePermissionByAuid(GMToolsPrincipal user, long auid, out string error)
    {
      error = null;
      if (!user.IsBoundedByLocale)
        return true;

      var resp = accountManagementService.GetLocaleInfoByAuid(auid);
      if (resp.Result != RequestResult.Success)
      {
        error = GetVerboseErrorMessage(resp.Result);
        return false;
      }
      return user.HasLocale(resp.Info.Locale) && user.HasMuid(resp.Info.Muid);
    }

    public bool CheckLocalePermissionBySNUid(GMToolsPrincipal user, string snid, string snuid, out string error)
    {
      error = null;
      if (!user.IsBoundedByLocale)
        return true;

      var resp = accountManagementService.GetLocaleInfoBySNUid(snid, snuid);
      if (resp.Result != RequestResult.Success)
      {
        error = GetVerboseErrorMessage(resp.Result);
        return false;
      }
      return user.HasLocale(resp.Info.Locale) && user.HasMuid(resp.Info.Muid);
    }

    public List<QuestInfoModel> GetQuests(long auid, out string error)
    {
      error = null;
      var response = accountManagementService.GetQuests(auid);
      if (response.Result != RequestResult.Success)
      {
        error = GetVerboseErrorMessage(response.Result);
        return null;
      }

      var result = response.Quests.Select(q => new QuestInfoModel(q)).ToList();
      var allquests = QuestsCatalog.GetAll();
      if (allquests != null)
        foreach (var model in result)
        {
          var quest = allquests.SingleOrDefault(q => q.QuestId == model.Name && !q.Deleted);
          if (quest != null)
            model.Desc = quest.Name;
        }
      return result;
    }

    public string QuestChange(long auid, int questid, string action, string gmlogin)
    {
      QuestChangeAction actionenum;
      try
      {
        actionenum = (QuestChangeAction) Enum.Parse(typeof (QuestChangeAction), action, true);
      }
      catch (Exception)
      {
        return String.Format("Invalid action = '{0}'", action);
      }
      var response = accountManagementService.ChangeQuest(auid, questid, actionenum, gmlogin);
      if (response.Result != RequestResult.Success)
        return response.Error ?? GetVerboseErrorMessage(response.Result);
      return null;
    }

    public AccountInfoModel GetAccountBySNUid( string snid, string snuid )
    {
      AccountInfoModel model = new AccountInfoModel();
      AccountInfoResponse accResp = accountManagementService.GetAccountBySNUid( snid, snuid );
      if ( accResp.Result != RequestResult.Success )
      {
        model.ErrorIfExistToShow = GetVerboseErrorMessage( accResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountBySNUid: " + snid + ", " + snuid ) );
        return model;
      }
      if ( accResp.AccountInfo == null )
      {
        model.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.ServerReturnedNull );
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountBySNUid: " + snid + ", " + snuid ) );
        return model;
      }
      //if ( accResp.AccountInfo.Auid == 0)
      //{
      //  model.ErrorIfExistToShow = "Auid cannot be equal zero";
      //  _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountBySNUid: " + snid + ", " + snuid ) );
      //  return model;
      //}
      if ( string.IsNullOrEmpty( accResp.AccountInfo.Login ) )
      {
        model.ErrorIfExistToShow = "Server returned empty(or null) login";
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountBySNUid: " + snid + ", " + snuid ) );
        return model;
      }

      model = new AccountInfoModel(accResp.AccountInfo);
      if (model.GuildId != 0)
      {
        var guildresp = accountManagementService.GetGuildById(model.GuildId);
        if (guildresp.Result == RequestResult.Success)
          model.GuildFullName = String.Format("[{0}] {1}", guildresp.Guild.Shortname, guildresp.Guild.Fullname);
      }
      return model;
    }


    public AccountInfoModel GetAccountByAuid( long auid )
    {
      AccountInfoModel model = new AccountInfoModel();
      AccountInfoResponse accResp = accountManagementService.GetAccountByAuid( auid );
      if ( accResp.Result != RequestResult.Success )
      {
        if ( accResp.Result == RequestResult.SnUidNotExist )
          accResp.Result = RequestResult.AuidNotExist;
        model.ErrorIfExistToShow = GetVerboseErrorMessage( accResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountByAuid: " + auid ) );
        return model;
      }
      if ( accResp.AccountInfo == null )
      {
        model.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.AuidNotExist );
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountByAuid: " + auid ) );
        return model;
      }
      if ( string.IsNullOrEmpty( accResp.AccountInfo.Login ) )
      {
        model.ErrorIfExistToShow = "Server returned empty(or null) login";
        _log.Error( string.Format( "{0}, was got by : {1}", model.ErrorIfExistToShow, "GetAccountByAuid: " + auid ) );
        return model;
      }

      model = new AccountInfoModel(accResp.AccountInfo);
      if (model.GuildId != 0)
      {
        var guildresp = accountManagementService.GetGuildById(model.GuildId);
        if (guildresp.Result == RequestResult.Success)
          model.GuildFullName = String.Format("[{0}] {1}", guildresp.Guild.Shortname, guildresp.Guild.Fullname);
      }
      return model;
    }


    public GetAccountsResp GetAccountsByNickName( string nickName )
    {
      // Изначально метод был написан для обработки группы результатов,
      // но т.к. этого функционала нет на сервере, то подперто таким образом,
      // что метод работает только с одним результатом.

      GetAccountsResp uiResp = new GetAccountsResp();
      NickSnidResponse thriftResp = accountManagementService.FindNicknameExact( nickName );

      if ( thriftResp.Result != RequestResult.Success )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( thriftResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountsByNickName: " + nickName) );
        return uiResp;
      }
      if ( thriftResp.FoundAccount == null )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.NoUsersWithThatNickname );
        _log.Error( string.Format( "{0}, was got by : {1}", "Server returned accountsList == null or Count == 0", "GetAccountsByNickName: " + nickName) );
        return uiResp;
      }
      /*if ( thriftResp.FoundAccounts.Count == 0 )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.NoUsersWithThatNickname );
        _log.Error( string.Format( "{0}, was got by : {1}", "Server returned accountsList == null or Count == 0", "GetAccountsByNickName: " + nickName ) );
        return uiResp;
      }*/
      uiResp.accountsList = new List<AccountInfoModel> { new AccountInfoModel {Login = thriftResp.FoundAccount.Login} };
      return uiResp;
    }

    public string EditAccount( AccountInfoModel editAcc, string gmLogin )
    {
      string errorIfExistToShow = null;
      AccountEdit editInfo = new AccountEdit();
      editInfo.Snid = editAcc.SNid;
      editInfo.Snuid = editAcc.SNUid;
      editInfo.Login = editAcc.Login;
      editInfo.Email = editAcc.Email;
      editInfo.Nickname = editAcc.NickName;
      editInfo.Gold = editAcc.Gold;
      editInfo.Silver = editAcc.Silver;
      editInfo.Resource1 = editAcc.Resource1;
      editInfo.Resource2 = editAcc.Resource2;
      editInfo.Resource3 = editAcc.Resource3;
      editInfo.Perl = editAcc.Perl;
      editInfo.RedPerl = editAcc.RedPerl;
      editInfo.Cwplayerpoints = editAcc.CWPoints;
      editInfo.Shard = editAcc.Shard;
      if (editAcc.Currencies != null)
        editInfo.Currencies = editAcc.Currencies.ToDictionary(x => x.Key, x => x.Value);
      editInfo.Fame = editAcc.Fame;
      editInfo.Reliability = editAcc.Reliability;
      editInfo.Fraction = (int)editAcc.Fraction;
      editInfo.Location = editAcc.Location;
      editInfo.IsRegularMMAllowed = editAcc.IsRegularMMAllowed;
      editInfo.IsDeveloper = editAcc.IsDeveloper;
      editInfo.IsSpectator = editAcc.IsSpectator;
      editInfo.CanMute = editAcc.CanMute;
      editInfo.LordRating = editAcc.LordRating;
      editInfo.DailyRating = editAcc.DailyRating;
      editInfo.NumberOfWins = editAcc.NumberOfWins;
      editInfo.PlayerRating = editAcc.PlayerRating;
      editInfo.Dodges = editAcc.Dodges;
      editInfo.RetiredTime = editAcc.RetiredTime.HasValue ? editAcc.RetiredTime.Value.AddHours(-editAcc.TimeZone).ToUnixTimestamp() : 0;
      editInfo.Auid = editAcc.Auid;
      editInfo.Gender = (AccountLib.Gender)(int)editAcc.Gender;
      editInfo.SwitchQuant = editAcc.SwitchQuant;
      editInfo.LastPaymentTime = editAcc.LastPaymentTime.HasValue ? editAcc.LastPaymentTime.Value.AddHours(-editAcc.TimeZone).ToUnixTimestamp() : 0;
      editInfo.LastLampDropTime = editAcc.LastLampDropTime.HasValue ? editAcc.LastLampDropTime.Value.AddHours(-editAcc.TimeZone).ToUnixTimestamp() : 0;
      //editInfo.Result = RequestResult.Success;
      editInfo.NumberOfWinsForPR = editAcc.NumberOfWinsForPR;
      editInfo.ExtraComplaints = editAcc.ExtraComplaints;
      editInfo.ExtraSessionComplaints = editAcc.ExtraSessionComplaints;
      RequestResult result = accountManagementService.EditAccount( editAcc.Login, editInfo, gmLogin );
      if ( result != RequestResult.Success )
      {
        errorIfExistToShow = GetVerboseErrorMessage( result );
        _log.Error( string.Format( "{0}, was got by : {1}", errorIfExistToShow, "EditAccount: " + editAcc.Login ) );
      }

      return errorIfExistToShow;
    }

    public string EditQuestForTalent(string login, QuestForTalentModel editModel, string gmLogin)
    {
        var thEditModel = new QuestForTalentEdit();

        thEditModel.QuestId = editModel.QuestId;
        thEditModel.StartTime = editModel.StartTime.ToUnixTimestamp();
        thEditModel.EndTime = editModel.EndTime.ToUnixTimestamp();
        thEditModel.CurrentObjectiveValue = editModel.CurrentObjectiveValue;
        thEditModel.CurrentObjectiveData = editModel.CurrentObjectiveData;
        thEditModel.TalentAwardName = editModel.TalentAwardName;
        thEditModel.EditAwardId = editModel.AwardId;
        thEditModel.EditObjectiveId = editModel.ObjectiveId;

        string errorIfExistToShow = null;
        RequestResult result = accountManagementService.EditQuestForTalent(login, thEditModel, gmLogin);
        if (result != RequestResult.Success)
        {
            errorIfExistToShow = GetVerboseErrorMessage(result);
            _log.Error(string.Format("{0}, was got by : {1}", errorIfExistToShow, "EditAccount: " + login));
        }

        return errorIfExistToShow;
    }

      public QuestsForTalentsInfoResponse GetQuestsForTalentsByAuid(string login)
      {
          var response = accountManagementService.GetQuestsForTalentsByAuid(login);
          if (response.Result != RequestResult.Success)
          {
              var errorIfExistToShow = GetVerboseErrorMessage(response.Result);
              _log.Error(string.Format("{0}, was got by : {1}", errorIfExistToShow, "EditAccount: " + login));
          }

          return response;
      }


    public GetTalentInfoListResp GetAccountLibrary( string login )
    {
      GetTalentInfoListResp uiResp = new GetTalentInfoListResp();
      var libResp = accountManagementService.GetAccountLibrary( login );
      if ( libResp.Result != RequestResult.Success )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( libResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountLibrary: " + login ) );
        return uiResp;
      }
      if ( libResp.LibraryList == null )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.ServerReturnedNull );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountLibrary: " + login ) );
        return uiResp;
      }

      List<TalentInfoModel> alltalents = GetTalentsCatalog();
      List<HeroInfoModel> allheroes = GetHeroesCatalog();

      uiResp.talentsList = new List<TalentInfoModel>();
      foreach (var item in libResp.LibraryList)
      {
          try
          {
              var talent = alltalents.Single(t => t.TalentClassId == item.TalentClassId);
              uiResp.talentsList.Add(new TalentInfoModel(item)
              {
                  TalentName = talent.TalentName,
                  Description = talent.Description,
                  Rarity = talent.Rarity,
                  Tour = talent.Tour,
                  BoundHeroClassName = item.BoundHeroInstanceId == 0
                      ? null
                      : allheroes.Single(h => h.HeroClassId == item.BoundHeroClassId).HeroName
              });
          }
          catch (Exception e)
          {
          }
        
      }
      uiResp.talentsList.Sort((m1, m2) => String.CompareOrdinal(m1.TalentName, m2.TalentName));

      return uiResp;
    }


    public List<HeroInfoModel> GetHeroesCatalog()
    {
      return HeroesCatalog.HeroesWithStaticData.OrderBy(h => h.HeroName).ToList();
    }
    public GetHeroInfoListResp GetAccountHeroes( string login )
    {
      GetHeroInfoListResp uiResp = new GetHeroInfoListResp();
      var heroesResp = accountManagementService.GetAccountHeroes( login );
      if ( heroesResp.Result != RequestResult.Success )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( heroesResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountHeroes: " + login ) );
        return uiResp;
      }
      if ( heroesResp.HeroesList == null )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.ServerReturnedNull );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountHeroes: " + login ) );
        return uiResp;
      }
      List<HeroInfo> userHeroes = heroesResp.HeroesList;
      List<HeroInfoModel> catalog = GetHeroesCatalog();
      var filled = from userHero in userHeroes
                   join catalogItem in catalog on userHero.HeroClassId equals catalogItem.HeroClassId
                   select
                     new HeroInfoModel
                       {
                         HeroClassId = userHero.HeroClassId,
                         HeroInstanceId = userHero.HeroInstanceId,
                         Experience = userHero.Experience,
                         Rating = userHero.Rating,
                         HeroName = catalogItem.HeroName,
                         EpicWins = userHero.EpicWins,
                       };
      uiResp.heroesList = filled.OrderBy(h => h.HeroName).ToList();
      return uiResp;
    }
    public string UnlockHero( string login, int heroClassId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.UnlockHero( login, heroClassId, gmLogin ) );
    }

    public string EditHero( string login, HeroInfoModel heroEdit, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.EditHero( login, new HeroInfo { HeroClassId = heroEdit.HeroClassId, HeroInstanceId = heroEdit.HeroInstanceId, Experience = heroEdit.Experience, Rating = heroEdit.Rating, EpicWins = heroEdit.EpicWins }, gmLogin ) );
    }
    public string LockHero( string login, long heroInstanceId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.LockHero( login, heroInstanceId, gmLogin ) );
    }

    public string EditSeasonAwards(string login, SeasonAwardsModel awardEdit, string gmLogin)
    {
        return PerformAndGetError(() => accountManagementService.EditSeasonAwards(login, new SeasonAwards { SeasonId = awardEdit.SeasonId, Perls = awardEdit.Perls, Flag = awardEdit.Flag, Skin = awardEdit.Skin, Talents = awardEdit.Talents }, gmLogin));
    }

    public string EditSeasonInfo(string login, long heroClassId, SeasonInfoModel seasonEdit, string gmLogin)
    {
        return PerformAndGetError(() => accountManagementService.EditSeasonInfo(login, heroClassId, new SeasonInfo { SeasonId = seasonEdit.SeasonId, SeasonName = seasonEdit.SeasonName, SeasonRating = seasonEdit.SeasonRating, LeagueIndex = seasonEdit.LeagueIndex, BestLeaguePlace = seasonEdit.BestLeaguePlace }, gmLogin));
    }

    public List<SkinInfoModel> GetAccountSkins(long auid)
    {
      var response = accountManagementService.GetAccountSkins(auid);
      if (response == null || response.Skins == null || response.Result != RequestResult.Success)
        return null;

      return response.Skins.Select(s => new SkinInfoModel
                                          {
                                            PersistentId = s.PersistentId,
                                            HeroClassId = s.HeroClassId,
                                            HeroClassName = GetHeroesCatalog().Single(h => h.HeroClassId == s.HeroClassId).HeroName,
                                            Owned = s.Owned,
                                            Available = s.Available,
                                            Cost = s.Cost
                                          }).ToList();
    }

    public string AddSkin(long auid, string skinPersistentId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.AddSkin(auid, skinPersistentId, gmLogin));
    }
    public string DeleteSkin(long auid, string skinPersistentId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.DeleteSkin(auid, skinPersistentId, gmLogin));
    }

    public List<TalentUpgradeEntityInfoModel> GetAccountTalentUpgradeEntities(long auid)
    {
      var response = accountManagementService.GetAccountTalentUpgradeEntities(auid);
      if (response == null || response.Entities == null || response.Result != RequestResult.Success)
        return null;

      return response.Entities.Select(entityInfo => new TalentUpgradeEntityInfoModel()
      {
        InstanceId = entityInfo.InstanceId,
        PersistentId = entityInfo.PersistentId,
        Chance = entityInfo.Chance,
        Type = (TalentUpgradeEntityType)entityInfo.Type,
        TalentLevelLimit = entityInfo.TalentLevelLimit,
      }).ToList();
    }

    public string DeleteTalentUpgradeEntity(long auid, long instanceId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.DeleteTalentUpgradeEntity(auid, instanceId, gmLogin));
    }

    public List<BuildingInfoModel> GetAccountBuildings(long auid)
    {
      var response = accountManagementService.GetAccountBuildings(auid);
      if (response == null || response.Buildings == null || response.Result != RequestResult.Success)
        return null;

      var allbuildings = CastleBuildingsCatalog.GetAll();
      var result = new List<BuildingInfoModel>();
      foreach (var info in response.Buildings)
      {
        var dbinfo = allbuildings.SingleOrDefault(b => b.Id == info.Classid);
        if (dbinfo == null)
        {
          _log.Error("Can't find dbinfo for object " + info);
          return null;
        }
        result.Add(new BuildingInfoModel(info, dbinfo));
      }
      return result;
    }

    public string MoveBuildingToStorage(long auid, long buildingInstanceId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.MoveBuildingToStorage(auid, buildingInstanceId, gmLogin));
    }

    public string AddBuilding(long auid, int buildingClassId, int level, string gmLogin)
    {
      // level-1 потому что в GM Tools UI уровни начинаются с 1 (как в замке), а в сервере с 0
      return PerformAndGetError(() => accountManagementService.AddBuilding(auid, buildingClassId, level-1, gmLogin));
    }

    public string DeleteBuilding(long auid, long buildingInstanceId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.DeleteBuilding(auid, buildingInstanceId, gmLogin));
    }

    public List<TalentInfoModel> GetTalentsCatalog()
    {
      return TalentsCatalog.GetAllTalents().OrderBy(t => t.TalentName).ToList();
    }
    public List<TalentInfoModel> GetTalentsByRarity(TalentRarity rarity)
    {
      return TalentsCatalog.GetTalentsByRarity(rarity).OrderBy(t => t.TalentName).ToList();
    }
    public GetTalentInfoListResp GetHeroTalentSet( string login, long heroInstanceId )
    {
      GetTalentInfoListResp uiResp = new GetTalentInfoListResp();
      var talentSet = accountManagementService.GetHeroTalentSet( login, heroInstanceId );
      if ( talentSet.Result != RequestResult.Success )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( talentSet.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetHeroTalentSet: " + login ) );
        return uiResp;
      }
      if ( talentSet.TalentSetList == null )
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( RequestResult.ServerReturnedNull );
        _log.Error( string.Format( "{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetHeroTalentSet: " + login ) );
        return uiResp;
      }

      List<TalentInfoModel> alltalents = GetTalentsCatalog();
      List<HeroInfoModel> allheroes = GetHeroesCatalog();

      uiResp.talentsList = new List<TalentInfoModel>();
      foreach ( var talentSetInfo in talentSet.TalentSetList )
      {
        foreach (var talentInfo in talentSetInfo.Talents)
        {
          var talent = uiResp.talentsList.Find(item => item.TalentInstanceId == talentInfo.TalentInstanceId);
          if (talent == null)
          {
            talent = new TalentInfoModel(talentInfo)
                                     {
                                         TalentName =
                                             alltalents.Single(t => t.TalentClassId == talentInfo.TalentClassId).
                                             TalentName,
                                         Description =
                                             alltalents.Single(t => t.TalentClassId == talentInfo.TalentClassId).
                                             Description,
                                         BoundHeroClassName =
                                             allheroes.Single(h => h.HeroClassId == talentInfo.BoundHeroClassId).
                                             HeroName,
                                     };
            uiResp.talentsList.Add( talent );
          }
          talent.TalentSets[
            talent.TalentSets.Count >= talentSetInfo.TalentSetId ? talentSetInfo.TalentSetId : 0] = true;
              
        }
      }

      return uiResp;
    }

    public GetSeasonInfoListResp GetHeroSeasonsInfo(string login, long heroInstanceId)
    {
        GetSeasonInfoListResp uiResp = new GetSeasonInfoListResp();
        var listSeasonInfo = accountManagementService.GetHeroSeasonsInfo(login, heroInstanceId);
        if (listSeasonInfo.Result != RequestResult.Success)
        {
            uiResp.ErrorIfExistToShow = GetVerboseErrorMessage(listSeasonInfo.Result);
            _log.Error(string.Format("{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetHeroSeasonsInfo: " + login));
            return uiResp;
        }
        if (listSeasonInfo.SeasonInfoList == null)
        {
            uiResp.ErrorIfExistToShow = GetVerboseErrorMessage(RequestResult.ServerReturnedNull);
            _log.Error(string.Format("{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetHeroSeasonsInfo: " + login));
            return uiResp;
        }

        uiResp.seasonInfoList = new List<SeasonInfoModel>();
        foreach (var seasonInfo in listSeasonInfo.SeasonInfoList)
        {
            var add_seasonInfo = new SeasonInfoModel();
            add_seasonInfo.SeasonId = seasonInfo.SeasonId;
            add_seasonInfo.SeasonName = !String.IsNullOrEmpty(seasonInfo.SeasonName) ? seasonInfo.SeasonName : null;
            add_seasonInfo.StartDate = seasonInfo.StartDate != 0 ? (DateTime?)seasonInfo.StartDate.FromUnixTimestamp() : null;
            add_seasonInfo.EndDate = seasonInfo.EndDate != 0 ? (DateTime?)seasonInfo.EndDate.FromUnixTimestamp() : null;
            add_seasonInfo.SeasonRating = seasonInfo.SeasonRating;
            add_seasonInfo.LeagueIndex = seasonInfo.LeagueIndex;
            add_seasonInfo.CurLeaguePlace = seasonInfo.CurLeaguePlace;
            add_seasonInfo.BestLeaguePlace = seasonInfo.BestLeaguePlace;

            uiResp.seasonInfoList.Add(add_seasonInfo);
        }

        return uiResp;
    }
    public string UnlockTalent( string login, long heroInstanceId, int talentClassId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.UnlockTalent( login, heroInstanceId, talentClassId, gmLogin ) );
    }
    public string UnlockTalents( string login, long heroInstanceId, int[] talentIds, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.UnlockTalents( login, heroInstanceId, talentIds, gmLogin ) );
    }
    public string EditTalent( string login, TalentInfoModel editTalent, string gmLogin )
    {
      return PerformAndGetError(() => accountManagementService.EditTalent(login, new TalentInfo
                                                                                   {
                                                                                     TalentClassId = editTalent.TalentClassId,
                                                                                     TalentInstanceId = editTalent.TalentInstanceId,
                                                                                     RefineRate = editTalent.RefineRate,
                                                                                     BoundHeroInstanceId = editTalent.BoundHeroInstanceId
                                                                                   },
                                                                          gmLogin));
    }
    public string LockTalent( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.LockTalent( login, heroInstanceId, talentInstanceId, gmLogin ) );
    }
    public string MoveTalentFromTalentSetToLibrary( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.MoveTalentFromTalentSetToLibrary( login, heroInstanceId, talentInstanceId, gmLogin ) );
    }
    public string MoveTalentFromLibraryToTalentSet( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.MoveTalentFromLibraryToTalentSet( login, heroInstanceId, talentInstanceId, gmLogin ) );
    }

    public string RemoveTalentFromTalentSet( string login, long heroInstanceId, long talentInstanceId, int talentSetId, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.RemoveTalentFromTalentSet( login, heroInstanceId, talentInstanceId, talentSetId, gmLogin ) );
    }    

    public string DisjointSN(long auid, string sn)
    {
      return PerformAndGetError(() => accountManagementService.DisjointSN(auid, sn));
    }

    public string ChangeFSN( long auid, string sn )
    {
      return PerformAndGetError( () => accountManagementService.ChangeFSN( auid, sn ) );
    }

    public string RemoveSaAccount(long auid)
    {
      return PerformAndGetError(() => accountManagementService.DeleteSaAccount(auid));
    }

    public string SendMessageToUser( long auid, string login, string messageTitle, string messageText, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.SendMessageToUser( auid, login, messageTitle, messageText, gmLogin ) );
    }

    public RequestResult UserOperation(long auid, UserOperationType type, int minutes, string reason, List<int> claims, string gmLogin, List<long> claimAuids)
    {
      return PerformAndGetErrorCode(() => accountManagementService.UserOperation(auid, type, minutes, reason, claims, gmLogin, claimAuids));
    }

    public string ResetUserAccount( string login, string gmLogin )
    {
      if (String.IsNullOrEmpty(login)) return "Cannot perform reset account for empty login";
      return PerformAndGetError( () => accountManagementService.ResetUserAccount( login, gmLogin ) );
    }

    public string KickUser( string login, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.KickUser( login, gmLogin ) );
    }


    public string CreateBroadcastMessage(BroadcastModel createModel, string gmLogin)
    {
      var resp = accountManagementService.CreateBroadcast(
        new BroadcastInfo
          {
            Title = createModel.Title,
            Messages = createModel.Messages
                                  .Where(m => !String.IsNullOrEmpty(m.Text))
                                  .Select(m => new BroadcastMessage {Locale = m.Locale, Text = m.Text}).ToList(),
            TimeStart = createModel.TimeStart.AddHours(-createModel.TimeZone).ToUnixTimestamp(),
            TimeFinish = createModel.TimeFinish.AddHours(-createModel.TimeZone).ToUnixTimestamp(),
            Interval = createModel.Interval,
            EnabledNow = createModel.EnabledNow
          }, gmLogin);

      if (resp.Result != RequestResult.Success)
        return GetVerboseErrorMessage(resp.Result);

      return null;
    }


    public List<string> GetBroadcastLocales()
    {
        var resp = accountManagementService.GetBroadcastLocales();
        if (resp != null)
        {
            if (resp.Result != RequestResult.Success || resp.Locales.Count == 0)
                throw new Exception("Failed to get broadcast locales list from server");

            return resp.Locales;
        }
        return null;
    }


    public List<string> GetBroadcastLocales(GMToolsPrincipal user)
    {
      return GetBroadcastLocales().Where(user.HasLocale).ToList();
    }


    public string EditBroadcastMessage(BroadcastModel editModel, string gmLogin)
    {
      var info =
        new BroadcastInfo
          {
            Id = editModel.Id,
            Title = editModel.Title,
            Messages = editModel.Messages
                                .Where(m => !String.IsNullOrEmpty(m.Text))
                                .Select(m => new BroadcastMessage {Locale = m.Locale, Text = m.Text}).ToList(),
            TimeStart = editModel.TimeStart.AddHours(-editModel.TimeZone).ToUnixTimestamp(),
            TimeFinish = editModel.TimeFinish.AddHours(-editModel.TimeZone).ToUnixTimestamp(),
            Interval = editModel.Interval,
            EnabledNow = editModel.EnabledNow
          };

      return PerformAndGetError(() => accountManagementService.EditBroadcast(info, gmLogin));
    }


    public string DeleteBroadcastMessage(int id, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.DeleteBroadcast(id, gmLogin));
    }


    public GetBroadcastMessageListResp GetBroadcastList(GMToolsPrincipal user, int page, int pageSize, out int totalpages)
    {
      totalpages = -1;
      GetBroadcastMessageListResp uiResp = new GetBroadcastMessageListResp();
      BroadcastListResponse broadcast = accountManagementService.GetBroadcastList(0, Int32.MaxValue);
      if (broadcast.Result != RequestResult.Success)
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage(broadcast.Result);
        _log.Error(string.Format("{0}, has got by : {1}", uiResp.ErrorIfExistToShow, "GetBroadcastList"));
        return uiResp;
      }
      if (broadcast.BroadcastList == null)
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage(RequestResult.ServerReturnedNull);
        _log.Error(string.Format("{0}, has got by : {1}", uiResp.ErrorIfExistToShow, "GetBroadcastList"));
        return uiResp;
      }

      // Выбираем бродкасты по разрешенным ГМу локалям
      broadcast.BroadcastList =
        broadcast.BroadcastList.Where(b => b.Messages.All(m => user.HasLocale(m.Locale))).ToList();

      totalpages = broadcast.BroadcastList.Count / pageSize + (broadcast.BroadcastList.Count % pageSize == 0 ? 0 : 1);
      var locales = GetBroadcastLocales(user);

      uiResp.broadcastList = broadcast
        .BroadcastList
        .Skip((page-1) * pageSize).Take(pageSize)
        .Select(info => new BroadcastModel(locales, info)).OrderBy(b => b.Id).ToList();
      return uiResp;
    }

    public BroadcastModel GetBroadcastById(int id, GMToolsPrincipal user)
    {
      var response = accountManagementService.GetBroadcastList(0, Int32.MaxValue);
      if (response.Result != RequestResult.Success || response.BroadcastList == null)
        return null;

      var locales = GetBroadcastLocales(user);
      var info = response.BroadcastList.Find(b => b.Id == id && b.Messages.All(m => user.HasLocale(m.Locale)));
      if (info == null)
        return null;

      return new BroadcastModel(locales, info);
    }


    public string StartMessageRotation(int id, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.StartMessageRotation(id, gmLogin));
    }


    public string StopMessageRotation(int id, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.StopMessageRotation(id, gmLogin));
    }


    public string GetSocServerVersion()
    {
      SocServerVersionResponse socVersionResp = accountManagementService.GetSocServerVersion();
      if ( socVersionResp.Result != RequestResult.Success )
      {
        string errorIfExistToShow = GetVerboseErrorMessage( socVersionResp.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", errorIfExistToShow, "GetSocServerVersion" ) );
        return errorIfExistToShow;
      }
      string result = socVersionResp.Version;
      if ( string.IsNullOrEmpty( result ) )
        result = "empty response";
      return result;
    }
    public StringUIResponse GetFullUserDump( string login, bool zip )
    {
      StringDataResponse fullDumpResp = accountManagementService.GetFullUserDump( login, zip );
      StringUIResponse uiResp = new StringUIResponse();
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
    public string ApplyFullUserDump( string login, string dumpdata )
    {
      return PerformAndGetError( () => accountManagementService.ApplyFullUserDump(login, dumpdata) );
    }
    public string RemoveFakeAuid( string login )
    {
      return PerformAndGetError( () => accountManagementService.RemoveFakeAuid( login ) );
    }
    public string ActivateEmail( string email, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.ActivateEmail( email, gmLogin ) );
    }  
    public GetBackupDatesListResp GetBackups()
    {
      UserDumpsDataResponse backupResp = accountManagementService.GetBackups();
      GetBackupDatesListResp resp = new GetBackupDatesListResp();
      if (backupResp.Result != RequestResult.Success)
      {
        resp.ErrorIfExistToShow = GetVerboseErrorMessage(backupResp.Result);
        return resp;
      }
      resp.BackupDates = backupResp.AvaialbleBackups;
      return resp;
    }
    public StringUIResponse GetBrokenUserDump( string login, string date, bool zip )
    {
      StringDataResponse fullDumpResp = accountManagementService.GetBrokenUserDump( login, date, zip );
      StringUIResponse uiResp = new StringUIResponse();
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
    public StringUIResponse GetBrokenUserDumpByNickname( string nickname, string date, bool zip )
    {
      StringDataResponse fullDumpResp = accountManagementService.GetBrokenUserDumpByNickname( nickname, date, zip );
      StringUIResponse uiResp = new StringUIResponse();
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
    public string EditFreeChanges( string login, string gmLogin, int nickChanges, int fractionChanges )
    {
      return PerformAndGetError( () => accountManagementService.EditFreeChanges(login, gmLogin, nickChanges, fractionChanges) ); 
    }
    public string EditNickname( string login, string gmLogin, string nickname )
    {
      StringDataResponse editNickResp = accountManagementService.EditNickname( login, gmLogin, nickname );
      if ( editNickResp.Result != RequestResult.Success )
        return GetVerboseErrorMessage( editNickResp.Result );
      if ( !string.IsNullOrEmpty( editNickResp.Data ) )
        return editNickResp.Data;
      return null;
    }

    public StringUIResponse CheckAccountValidity( string login )
    {
      StringDataResponse checkResp = accountManagementService.CheckAccountValidity( login );
      StringUIResponse uiResp = new StringUIResponse();
      if ( checkResp.Result != RequestResult.Success )
      {
        if ( checkResp.Result == RequestResult.BadResult )
        {
          uiResp.Data = "Account is invalid. " + checkResp.Data;
          return uiResp;
        }
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage( checkResp.Result );
        return uiResp;
      }
      return uiResp;
    }
    public string FixAccount( string login, string gmLogin )
    {
      return PerformAndGetError( () => accountManagementService.FixAccount( login, gmLogin ) );
    }

    public string PayEditNickname(string login, string nickname)
    {
      var response = accountManagementService.PayEditNickname(login, nickname);
      return GetErrorMessage(response, "PayEditNickname");
    }

    public string PayChangeFraction(string login, int fraction)
    {
      var response = accountManagementService.PayChangeFraction(login, fraction);
      return GetErrorMessage(response, "PayChangeFraction");
    }

    public string GiveLamp( string login, int bonus, int gold, int transaction, long duration, string gmLogin )
    {
      LampInfo lampInfo = new LampInfo();
      lampInfo.Bonus = bonus;
      lampInfo.GoldBonus = gold;
      lampInfo.Transaction = transaction;
      lampInfo.Duration = duration;
      return PerformAndGetError( () => accountManagementService.GiveLamp( login, lampInfo, gmLogin ) );
    }

    public string GiveUpgradeHeroTalents(string login, int usesLeft, string gmLogin)
    {
        UpgradeHeroTalentsInfo upgradeHeroTalentsInfo = new UpgradeHeroTalentsInfo();
        upgradeHeroTalentsInfo.UsesLeft = usesLeft;
        return PerformAndGetError(() => accountManagementService.GiveUpgradeHeroTalents(login, upgradeHeroTalentsInfo, gmLogin));
    }

    public LampInfoResponse GetLampInfo( string login )
    {
      return accountManagementService.GetLampInfo( login );
    }

    public UpgradeHeroTalentsInfoResponse GetUpgradeHeroTalentsInfo(string login)
    {
      return accountManagementService.GetUpgradeHeroTalentsInfo( login );
    }

    public string PayService(string login, PayServiceType type, int days, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.PayService(login, type, days, gmLogin));
    }

    public string EditTournamentInfo( string login, int wins, int losses, long lastGameTime, TicketPriseState ticketPriseState, TicketState state, TicketBoughtType boughtType, int missedGames, bool isSynchronized, string gmLogin )
    {
      TournamentInfo tournamentInfo = new TournamentInfo();
      tournamentInfo.Wins = wins;
      tournamentInfo.Losses = losses;
      tournamentInfo.LastGameTime = lastGameTime;
      tournamentInfo.TicketPriseState = ticketPriseState;
      tournamentInfo.TicketBoughtType = boughtType;
      tournamentInfo.State = state;
      tournamentInfo.MissedGames = missedGames;
      tournamentInfo.IsSynchronized = isSynchronized;
      return PerformAndGetError( () => accountManagementService.EditTournamentInfo(login, tournamentInfo, gmLogin ));
    }

    public TournamentInfoResponse GetAccountTournamentInfo(string login)
    {
      return accountManagementService.GetAccountTournamentInfo(login);
    }

    public GiveTournamentTicketResponse GiveTournamentTicket(string login)
    {
      return accountManagementService.GiveTournamentTicket(login);
    }

    public GetTournamentGamesListResp GetAccountTournamentGames(string login)
    {
      GetTournamentGamesListResp uiResp = new GetTournamentGamesListResp();
      var tournamentGamesResp = accountManagementService.GetAccountTournamentGames(login);
      if (tournamentGamesResp.Result != RequestResult.Success)
      {
        uiResp.ErrorIfExistToShow = GetVerboseErrorMessage(tournamentGamesResp.Result);
        _log.Error(string.Format("{0}, was got by : {1}", uiResp.ErrorIfExistToShow, "GetAccountTournamentGames: " + login));
        return uiResp;
      }
      List<TournamentGamesInfo> userGames = tournamentGamesResp.TournamentGames;
      var filled = from userGame in userGames
                   select
                     new TournamentGamesInfoModel
                     {
                       GameStartTime = userGame.GameStartTime.FromUnixTimestamp(),
                       GameDuration = userGame.GameDuration,
                       SessionId = userGame.SessionId
                     };
      uiResp.tournamentGamesList = filled.OrderBy(g => g.GameStartTime).ToList();
      return uiResp;
    }

    public GetFlagListResp GetAccountFlags(string login)
    {
      var result = new GetFlagListResp();
      var flagsResponse = accountManagementService.GetAccountFlags( login );
      if (flagsResponse.Result != RequestResult.Success)
      {
        result.ErrorIfExistToShow = GetVerboseErrorMessage(flagsResponse.Result);
        _log.Error(string.Format("{0}, was got by : {1}", result.ErrorIfExistToShow, "GetAccountFlags: " + login));
        return result;
      }
      if (flagsResponse.OwnedFlags == null || flagsResponse.NotOwnedFlags == null || flagsResponse.AdminFlags == null)
      {
        result.ErrorIfExistToShow = GetVerboseErrorMessage(RequestResult.ServerReturnedNull);
        _log.Error(string.Format("{0}, was got by : {1}", result.ErrorIfExistToShow, "GetAccountFlags: " + login));
        return result;
      }
      foreach( var notOwnedFlag in flagsResponse.NotOwnedFlags )
      {
        result.NotOwnedFlagsList.Add( new FlagModel
                                  {
                                    FlagPersistentId = notOwnedFlag.FlagPersistentId,
                                    FlagPrice = notOwnedFlag.FlagPrice
                                  } );
      }
      foreach (var adminFlag in flagsResponse.AdminFlags)
      {
        result.AdminFlagsList.Add(new FlagModel
        {
          FlagPersistentId = adminFlag.FlagPersistentId,
          FlagPrice = adminFlag.FlagPrice
        });
      }
      foreach (var ownedFlag in flagsResponse.OwnedFlags)
      {
        result.OwnedFlagsList.Add(new FlagModel
        {
          FlagPersistentId = ownedFlag.FlagPersistentId,
          FlagPrice = ownedFlag.FlagPrice
        });
      }
      return result;
    }

    public string LockFlag( string login, string flagPersistentId, string gmLogin )
    {
      return PerformAndGetError(() => accountManagementService.LockFlag(login, flagPersistentId, gmLogin));
    }

    public string UnlockFlag(string login, string flagPersistentId, string gmLogin)
    {
      return PerformAndGetError(() => accountManagementService.UnlockFlag(login, flagPersistentId, gmLogin));
    }

    public List<AdminMessageInfoModel> GetAccountAdminMessages(string login, int pageNum, int pageSize, out int pageQuant)
    {
      pageQuant = 0;
      try
      {
        var accountMessages = accountManagementService.GetAccountAdminMessages(login).AdminMessages
              .Select(op => new AdminMessageInfoModel
              {
                MessageText = op.MessageText,
                MessageTitle = op.MessageTitle,
                GMLogin = op.GmLogin,
                Timestamp = op.Timestamp.FromUnixTimestamp(),
              }).ToList();
        pageQuant = (int)Math.Ceiling((double)accountMessages.Count() / pageSize);
        return accountMessages.OrderBy(h => h.Timestamp).Skip((pageNum - 1) * pageSize).Take(pageSize).ToList();
      }
      catch (Exception ex)
      {
        _log.Error("Failed to get adminmessages history from SQL for account = " + login, ex);
        return null;
      }
    }

    public string BindGeolocation(long auid, string country, string region, string city, string gmlogin)
    {
      return PerformAndGetError(() => accountManagementService.BindGeolocation(auid, country, region, city, gmlogin));
    }

    public string ResetGeolocation(long auid, string gmlogin)
    {
      return BindGeolocation(auid, null, null, null, gmlogin);
    }

    private static string GetErrorMessage(ServerActionResponse response, string method)
    {
      if (response == null)
        return String.Format("Execution of {0} has failed", method);
      if (response.Result != RequestResult.Success)
        return String.Format("{0} in method {1}: {2} (errorcode={3})", response.Result, method, response.Error, response.Ec);
      return null;
    }

    public List<String> GetTalentsEvents()
    {
      var resp = accountManagementService.GetTalentsEvents();
      if (resp == null || resp.Result != RequestResult.Success || resp.TalentsEvents.Count == 0)
      {
        _log.Error("Failed to get talent events list from server, RequestResult = " + (resp != null ? resp.Result : RequestResult.ServerReturnedNull));
        return new List<String>();
      }
      return resp.TalentsEvents;
    }

    public List<String> GetResourceEvents()
    {
      var resp = accountManagementService.GetResourceEvents();
      if (resp == null || resp.Result != RequestResult.Success || resp.ResourceEvents.Count == 0)
      {
        _log.Error("Failed to get resource events list from server, RequestResult = " + (resp != null ? resp.Result : RequestResult.ServerReturnedNull));
        return new List<String>();
      }
      return resp.ResourceEvents;
    }

    public GetFriendsInfoListResp GetAccountFriends(long auid)
    {
      var friendsResponse = new GetFriendsInfoListResp();
      friendsResponse.Friends = new List<FriendInfoModel>();

      var friendsInfo = accountManagementService.GetAccountFriends( auid );
      if ( friendsInfo.Result != RequestResult.Success )
      {
        friendsResponse.ErrorIfExistToShow = GetVerboseErrorMessage( friendsInfo.Result );
        _log.Error( string.Format( "{0}, was got by : {1}", friendsResponse.ErrorIfExistToShow, "GetAccountLibrary: " + auid ) );
        return friendsResponse;
      }

      foreach ( var friend in friendsInfo.Friends )
      {
        friendsResponse.Friends.Add( new FriendInfoModel( ){ Auid = friend.Auid, Nickname = friend.Nickname, GuildShortName = friend.GuildShortName} );
      }
      return friendsResponse;
    }

    public string RemoveFriend(long auid, long friendAuid)
    {
      return PerformAndGetError(() => accountManagementService.RemoveFriend( auid, friendAuid ) );
    }

      private OperationDetails<Dictionary<string, int>> convertStringCurrenciesToDictionary(string rawCurrencies)
      {
          try
          {
              var currencyDict = new Dictionary<string, int>();
              if (string.IsNullOrEmpty(rawCurrencies))
                  return new OperationDetails<Dictionary<string, int>>(currencyDict, true);

              var slicedCurrencies = rawCurrencies.Replace(" ", string.Empty).Split(',');
              foreach (var slicedCurrency in slicedCurrencies) //slicedCurrency - "CC_Oscar:20"
              {
                  var currencyParts = slicedCurrency.Split(':'); //currencyParts - "[CC_Oscar, 20]"

                  if (currencyParts.Length != 2)
                      return new OperationDetails<Dictionary<string, int>>(string.Format("Bad currency pattern \"{0}\". It should be: \"currencyName:currencyCount\"", slicedCurrency));

                  var keyCurrency = currencyParts[0];
                  int valueCurrency;
                  if (!int.TryParse(currencyParts[1], out valueCurrency))
                      return new OperationDetails<Dictionary<string, int>>(string.Format("Bad count currency in \"{0}\" : \"{1}\"", currencyParts[0], currencyParts[1]));
                  currencyDict.Add(keyCurrency, valueCurrency);
              }

              return new OperationDetails<Dictionary<string, int>>(currencyDict, true);
          }
          catch (Exception e)
          {
              return new OperationDetails<Dictionary<string, int>>(e.Message + " " + e.StackTrace);
          }
      }

    public OperationDetails<string> ProcessMassOperation(MassOperationsModel model, List<long> auidsInt, string gmlogin)
    {
      var heroClassId = 0;
      var buildingId = 0;
      var hero = HeroesCatalog.HeroesWithStaticData.FirstOrDefault( h => h.HeroName == model.HeroClassId );
      if (hero != null) heroClassId = hero.HeroClassId;
      var building = CastleBuildingsCatalog.GetAll().Find(b => b.Name == model.BuildingPersistentId);

      var currencyConvertDetails = convertStringCurrenciesToDictionary(model.AccountSettings.Currencies);
      if (!currencyConvertDetails.SuccessStatus)
          return new OperationDetails<string>(currencyConvertDetails.ErrorDetails);

      if (building != null) buildingId = building.Id;
      var massOpInfo = new MassOperationInfo()
                               {
                                 AccountEdit = new AccountEdit()
                                                 {
                                                   Cwplayerpoints = model.AccountSettings.CWPoints,
                                                   Fraction = (int) model.AccountSettings.Fraction,
                                                   Silver = model.AccountSettings.Silver,
                                                   Perl = model.AccountSettings.Perl,
                                                   RedPerl = model.AccountSettings.RedPerl,
                                                   Resource1 = model.AccountSettings.Resource1,
                                                   Resource2 = model.AccountSettings.Resource2,
                                                   Resource3 = model.AccountSettings.Resource3,
                                                   Currencies = currencyConvertDetails.ObjectToReturn
                                                 },
                                 Auids = auidsInt,
                                 HeroId = heroClassId,
                                 SkinId = model.HeroSkinId,
                                 BuildingId = buildingId,
                                 FlagId = model.FlagId,
                                 Days = model.PremiumDays,
                                 Message = model.UserMessage,
                                 Type = (AccountLib.MassOperationType) ((int) model.MassOperationType),
                                 TalentId = model.Talent,
                                 TalentIds = model.GetTalents(),
                                 LampInfo = new LampInfo()
                                              {
                                                Bonus = model.LampSettings.Bonus,
                                                Duration = model.LampSettings.Duration,
                                                GoldBonus = model.LampSettings.Gold,
                                                Transaction = model.LampSettings.Transaction
                                              }
                               };
      return new OperationDetails<string>(PerformAndGetError(() => accountManagementService.AddMassOperation(massOpInfo, gmlogin)), true);
    }

    public List<MassOperationInfoModel> GetMassOperationsInfo()
    {
      var serverOperations = accountManagementService.GetMassOperationsInfo();
      var massOperations = serverOperations.MassOperations.Select(serverOperation => new MassOperationInfoModel()
                                                                                       {
                                                                                         EndTime = serverOperation.EndTime.FromUnixTimestamp(), 
                                                                                         StartTime = serverOperation.StartTime.FromUnixTimestamp(), 
                                                                                         Finished = serverOperation.Finished, 
                                                                                         FailedAuids = serverOperation.FailedAuids, 
                                                                                         OperationType = (MassOperationType) ((int) serverOperation.Type), 
                                                                                         OperationId = serverOperation.OperationId
                                                                                       }).ToList();
      return massOperations;
    }
    public string DeleteMassOperationInfo( int operationId )
    {
      return PerformAndGetError( () => accountManagementService.DeleteMassOperationInfo( operationId ) );
    }

    public PlayerWipeResp FillPlayerRespModel(NickSnidResponse nickSnidResponse)
    {
      var response = new PlayerWipeResp();
      if (nickSnidResponse.Result != RequestResult.Success)
      {
        response.ErrorIfExistToShow = GetVerboseErrorMessage(nickSnidResponse.Result);
        _log.Error(string.Format("{0}, was got by : {1}", response.ErrorIfExistToShow, "FillPlayerRespModel"));
        return response;
      }

      if (nickSnidResponse.FoundAccount != null)
        response.PlayerModel = new AccountShortInfoModel(nickSnidResponse.FoundAccount);

      return response;
    }

    public PlayerWipeResp FindPlayerByNickname(string nickname)
    {
      var playerResponseFromServer = accountManagementService.FindPlayerByNickname(nickname);
      return FillPlayerRespModel(playerResponseFromServer);
    }

    public PlayerWipeResp FindPlayerByEmail(string email)
    {
      var playerResponseFromServer = accountManagementService.FindPlayerByEmail(email);
      return FillPlayerRespModel(playerResponseFromServer);
    }

    public PlayerWipeResp PlayerChangeEmail(string email, string newEmail, string newPass)
    {
      var playerResponseFromServer = accountManagementService.PlayerChangeEmail(email, newEmail, newPass);
      return FillPlayerRespModel(playerResponseFromServer);
    }

    public PlayerWipeResp PlayerRemoveNickname(string email, string nickname)
    {
      var playerResponseFromServer = accountManagementService.PlayerRemoveNickname(email, nickname);
      return FillPlayerRespModel(playerResponseFromServer);
    }
  }  


  public class HeroesCatalog
  {
    private static ILog _log = LogManager.GetLogger( typeof( HeroesCatalog ) );
    private static List<HeroInfoModel> heroesCatalog;
    private HeroesCatalog() { }
    private static object locker = new object();
    public static List<HeroInfoModel> HeroesWithStaticData
    {
      get
      {
        lock ( locker )
        {
          List<HeroInfoModel> deepCatalogCopy = new List<HeroInfoModel>( heroesCatalog );
          return deepCatalogCopy;
        }
      }
    }
    static HeroesCatalog()
    {
      RefreshHeroesCatalog();
    }
    public static void RefreshHeroesCatalog()
    {
      lock ( locker )
      {
        if ( !Convert.ToBoolean( ConfigurationManager.AppSettings["useFakeCatalogs"] ) )
        {
          try
          {
            using ( var heroRepo = new CharacterRepository() )
            {
              heroesCatalog = heroRepo.GetAll().Select<Character, HeroInfoModel>( h => new HeroInfoModel( h ) ).ToList();
            }
          }
          catch
          {
            _log.Error( "Failed to get Heroes Catalog" );
            heroesCatalog = new List<HeroInfoModel>();
          }
        }
        else
        {
          heroesCatalog = new List<HeroInfoModel>
          {
            new HeroInfoModel { HeroClassId = 10, HeroInstanceId = -1, HeroName = "HumaMountain", Experience = 0, EpicWins = 0 },
            new HeroInfoModel { HeroClassId = 20, HeroInstanceId = -1, HeroName = "Firefox", Experience = 0, EpicWins = 0 },
            new HeroInfoModel { HeroClassId = 30, HeroInstanceId = -1, HeroName = "Lightning", Experience = 0, EpicWins = 0 },
            new HeroInfoModel { HeroClassId = 40, HeroInstanceId = -1, HeroName = "SnowQueen", Experience = 0, EpicWins = 0 },
            new HeroInfoModel { HeroClassId = 50, HeroInstanceId = -1, HeroName = "Vedun", Experience = 0, EpicWins = 0 },
          };
        }
      }
    }
  }
  public class TalentsCatalog
  {
    private static ILog _log = LogManager.GetLogger( typeof( TalentsCatalog ) );
    private TalentsCatalog() { }
    private static readonly object locker = new object();

    private static List<TalentInfoModel> talentsCatalog;
    
    public static List<TalentInfoModel> GetAllTalents()
    {
      lock (locker)
        return new List<TalentInfoModel>(talentsCatalog);
    }

    public static List<TalentInfoModel> GetTalentsByRarity(TalentRarity rarity)
    {
      lock (locker)
        return new List<TalentInfoModel>(talentsCatalog.Where(t => t.Rarity == rarity));
    }

    static TalentsCatalog()
    {
      RefreshTalentsCatalog();
    }
    public static void RefreshTalentsCatalog()
    {
      lock ( locker )
      {
        if ( !Convert.ToBoolean( ConfigurationManager.AppSettings["useFakeCatalogs"] ) )
        {
          try
          {
            using ( var talentRepo = new TalentRepository() )
            {
              talentsCatalog = talentRepo.GetAll().Where(t => !t.Deleted && t.TalentId != null).Select(t => new TalentInfoModel(t)).ToList();
            }
          }
          catch
          {
            _log.Error( "Failed to get Talents Catalog" );
            talentsCatalog = new List<TalentInfoModel>();
          }
        }
        else
        {
          talentsCatalog = new List<TalentInfoModel> 
          {
            new TalentInfoModel{TalentClassId = 1, TalentInstanceId = -1, TalentName = "fireResist", Description = "fireResist", RefineRate = 18, Rarity = TalentRarity.Class },
            new TalentInfoModel{TalentClassId = 2, TalentInstanceId = -1, TalentName = "superHit", Description = "superHit", RefineRate = 18, Rarity =TalentRarity.Ordinary },
            new TalentInfoModel{TalentClassId = 3, TalentInstanceId = -1, TalentName = "megaHit", Description = "megaHit", RefineRate = 18, Rarity = TalentRarity.Ordinary },
            new TalentInfoModel{TalentClassId = 4, TalentInstanceId = -1, TalentName = "ultraHit", Description = "ultraHit", RefineRate = 18, Rarity = TalentRarity.Good },
            new TalentInfoModel{TalentClassId = 5, TalentInstanceId = -1, TalentName = "frostEffect", Description = "frostEffect", RefineRate = 18, Rarity = TalentRarity.Good },
            new TalentInfoModel{TalentClassId = 6, TalentInstanceId = -1, TalentName = "magicEffect", Description = "magicEffect", RefineRate = 18, Rarity = TalentRarity.Excellent},
            new TalentInfoModel{TalentClassId = 7, TalentInstanceId = -1, TalentName = "acidEffect", Description = "acidEffect", RefineRate = 18, Rarity = TalentRarity.Magnificent},
            new TalentInfoModel{TalentClassId = 8, TalentInstanceId = -1, TalentName = "poisonEffect", Description = "poisonEffect", RefineRate = 18, Rarity = TalentRarity.Exclusive},
          };
        }
      }
    }
  }

  public static class CastleBuildingsCatalog
  {
    private static ILog _log = LogManager.GetLogger(typeof(TalentsCatalog));
    private static readonly object locker = new object();

    private static List<CastleBuilding> castleBuildings;

    public static List<CastleBuilding> GetAll()
    {
      if (castleBuildings == null && !RefreshCatalog())
        return null;

      lock (locker)
        return new List<CastleBuilding>(castleBuildings);
    }

    public static SelectList GetSelectList()
    {
      var items = GetAll().Select(b => new
                                         {
                                           id = b.Id,
                                           name = String.Format("{0} ({1}), max lvl = {2}",
                                                                b.Name, b.Description, b.MaxLevel)
                                         });
      return new SelectList(items, "id", "name");
    }

    public static SelectList GetPersistentIdOnlySelectList()
    {
      var items = GetAll().Select(b => new
      {
        id = b.Id,
        name = b.Name
      });
      return new SelectList(items, "id", "name");
    }

    static CastleBuildingsCatalog()
    {
      RefreshCatalog();
    }

    public static bool RefreshCatalog()
    {
      lock (locker)
      {
        try
        {
          using (var cbrepo = new Repository<CastleBuilding>())
            castleBuildings = cbrepo.GetAll().ToList();
          return true;
        }
        catch(Exception ex)
        {
          _log.Error("Failed to get castle buildings from statistic database", ex);
          castleBuildings = null;
          return false;
        }
      }
    }
  }

  public static class QuestsCatalog
  {
    private static ILog _log = LogManager.GetLogger(typeof(QuestsCatalog));
    private static readonly object locker = new object();

    private static List<Quest> quests;

    public static List<Quest> GetAll()
    {
      if (quests == null && !RefreshCatalog())
        return null;

      lock (locker)
        return new List<Quest>(quests);
    }

    static QuestsCatalog()
    {
      RefreshCatalog();
    }

    public static bool RefreshCatalog()
    {
      lock (locker)
      {
        try
        {
          using (var qrepo = new Repository<Quest>())
            quests = qrepo.GetAll().ToList();
          return true;
        }
        catch (Exception ex)
        {
          _log.Error("Failed to get quests from statistic database", ex);
          quests = null;
          return false;
        }
      }
    }
  }

}