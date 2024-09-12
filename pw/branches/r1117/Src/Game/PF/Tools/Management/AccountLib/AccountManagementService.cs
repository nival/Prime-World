using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Thrift.Protocol;
using Thrift.Transport;
using log4net;

namespace AccountLib
{
  public interface IAccountManagementService
  {
    AccountInfoResponse GetAccountBySNUid( string snid, string snuid );
    SocialNetworksResponse GetSocialNetworks();
    LocaleInfoResponse GetLocaleInfoBySNUid(string snid, string snuid);
    LocaleInfoResponse GetLocaleInfoByAuid(long auid);
    AccountInfoResponse GetAccountByAuid( long auid );
    NickSnidResponse FindNicknameExact(string nickName);
    RequestResult EditAccount( string login, AccountEdit accEdit, string gmLogin );
    RequestResult EditQuestForTalent(string login, QuestForTalentEdit accEdit, string gmLogin);
    QuestsForTalentsInfoResponse GetQuestsForTalentsByAuid(string login);
    LibraryResponse GetAccountLibrary( string login );
    GameSessionShortInfo GetGameSession( int sessionid );
    BruteForceAccountShortInfo GetBruteForceAccount(string email);
    RequestResult UnBanBruteForceAccount(string email);
    BannedIpFullListInfo GetBannedIp(int limit, int skip);
    RequestResult UnBanIp(string ip);

    QuestsInfoResponse GetQuests(long auid);
    ServerActionResponse ChangeQuest(long auid, int questid, QuestChangeAction action, string gmLogin);

    HeroesResponse GetAccountHeroes( string login );
    RequestResult UnlockHero( string login, int heroClassId, string gmLogin );
    RequestResult EditHero( string login, HeroInfo heroEdit, string gmLogin );
    RequestResult LockHero( string login, long heroInstanceId, string gmLogin );

    RequestResult EditSeasonAwards(string login, SeasonAwards awardEdit, string gmLogin);
    RequestResult EditSeasonInfo(string login, long heroInstanceId, SeasonInfo seasonEdit, string gmLogin);

    SkinsResponse GetAccountSkins(long auid);
    RequestResult AddSkin(long auid, string skinPersistentId, string gmLogin);
    RequestResult DeleteSkin(long auid, string skinPersistentId, string gmLogin);

    TalentUpgradeEntitiesResponse GetAccountTalentUpgradeEntities(long auid);
    RequestResult DeleteTalentUpgradeEntity(long auid, long instanceId, string gmLogin);

    TalentSetResponse GetHeroTalentSet( string login, long heroInstanceId );
    SeasonInfoResponse GetHeroSeasonsInfo(string login, long heroInstanceId);
    RequestResult UnlockTalent( string login, long heroInstanceId, int talentClassId, string gmLogin );
    RequestResult UnlockTalents( string login, long heroInstanceId, int[] talentIds, string gmLogin );
    RequestResult EditTalent( string login, TalentInfo editTalent, string gmLogin );
    RequestResult LockTalent( string login, long heroInstanceId, long talentInstanceId, string gmLogin );

    BuildingsInfoResponse GetAccountBuildings(long auid);
    RequestResult MoveBuildingToStorage(long auid, long buildingInstanceId, string gmLogin);
    RequestResult AddBuilding(long auid, int buildingClassId, int level, string gmLogin);
    RequestResult DeleteBuilding(long auid, long buildingInstanceId, string gmLogin);

    RequestResult MoveTalentFromTalentSetToLibrary( string login, long heroInstanceId, long talentInstanceId, string gmLogin );
    RequestResult MoveTalentFromLibraryToTalentSet( string login, long heroInstanceId, long talentInstanceId, string gmLogin );
    RequestResult RemoveTalentFromTalentSet( string login, long heroInstanceId, long talentInstanceId, int talentSetId, string gmLogin );    

    RequestResult GiveLamp( string login, LampInfo lampInfo, string gmLogin );
    LampInfoResponse GetLampInfo( string login );

    RequestResult GiveUpgradeHeroTalents(string login, UpgradeHeroTalentsInfo upgradeHeroTalentsInfo, string gmLogin);
    UpgradeHeroTalentsInfoResponse GetUpgradeHeroTalentsInfo(string login);

    RequestResult DisjointSN(long auid, string snid);
    RequestResult ChangeFSN( long auid, string snid );
    RequestResult DeleteSaAccount(long auid);

    RequestResult EditTournamentInfo( string login, TournamentInfo ticketInfo, string gmLogin );
    TournamentInfoResponse GetAccountTournamentInfo( string login );
    GiveTournamentTicketResponse GiveTournamentTicket(string login);
    TournamentGamesInfoResponse GetAccountTournamentGames(string login);

    GuildInfoResponse GetGuildById( long guildid );
    GuildInfoResponse GetGuildByName( string shortname, string fullname );
    RequestResult EditGuild(GuildEditInfo info, string gmlogin);
    RequestResult ChangeGuildLeader( long guildid, long auid, string gmlogin );
    RequestResult RemoveGuildMembers( long guildid, List<long> auids, string gmlogin );
    GuildMemberInfoResponse GetGuildMemberById(long guildid, long auid);
    RequestResult EditGuildMember( long guildid, GuildMemberInfo member, string gmlogin );
    RequestResult SetGuildIcon( long guildid, byte[] image );
    RequestResult SwitchToNewGuildIcon( long guildid, string gmlogin );
    ServerActionResponse TryToPayForGuildIconChange( long leaderauid, int changeiter );

    GuildBankTalentsResponse GetFreeGuildBankTalents(long guildid);
    GuildBankTalentsResponse GetTakenGuildBankTalents(long guildid);
    RequestResult ReturnTalentToOwner( long guildid, long talentId, string gmlogin );
    RequestResult ReturnTalentToGuildBank( long guildid, long talentId, string gmlogin );

    AdminMessagesResponse GetAccountAdminMessages(string login);
    RequestResult SendMessageToUser( long auid, string login, string messageTitle, string messageText, string gmLogin );
    RequestResult UserOperation(long auid, UserOperationType type, int value, string reason, List<int> claims, string gmLogin, List<long> claimAuids);
    RequestResult ResetUserAccount( string login, string gmLogin );
    RequestResult KickUser( string login, string gmLogin );

    RequestResult EditFreeChanges( string login, string gmLogin, int nickChanges, int fractionChanges );
    StringDataResponse EditNickname( string login, string gmLogin, string nickname );

    BroadcastCreateResponse CreateBroadcast(BroadcastInfo createInfo, string gmLogin);
    BroadcastLocalesResponse GetBroadcastLocales();
    RequestResult EditBroadcast(BroadcastInfo editInfo, string gmLogin);
    RequestResult DeleteBroadcast(int id, string gmLogin );
    BroadcastListResponse GetBroadcastList( int skipLines, int takeLines );
    RequestResult StartMessageRotation( int id, string gmLogin );
    RequestResult StopMessageRotation( int id, string gmLogin );
    SocServerVersionResponse GetSocServerVersion();

    StringDataResponse GetFullUserDump( string login, bool zip );
    RequestResult ApplyFullUserDump( string login, string dumpdata );
    RequestResult RemoveFakeAuid( string login );
    RequestResult ActivateEmail(string email, string gmLogin);
    UserDumpsDataResponse GetBackups();
    StringDataResponse GetBrokenUserDump( string login, string date, bool zip );
    StringDataResponse GetBrokenUserDumpByNickname( string nickname, string date, bool zip );

    StringDataResponse CheckAccountValidity( string login );
    RequestResult FixAccount( string login, string gmLogin );
    RequestResult FlushServerId( string login, string gmLogin );

    // платные операции
    ServerActionResponse PayEditNickname( string login, string nickname );
    ServerActionResponse PayChangeFraction( string login, int fraction );
    RequestResult PayService( string login, PayServiceType type, int param1, string gmLogin );

    RequestResult EditAccountDbValue( string login, string gmLogin, string key, string value );

    // динамические квесты
    DynamicQuestInfoResponse GetDynamicQuestInfo();
    AddDynamicQuestResponse AddDynamicQuest( string jsonQuestData, string locale, string gmLogin );
    RequestResult RemoveDynamicQuest( int questId, string locale );
    RequestResult EditDynamicQuest( int questId, string locale, string jsonQuestData );
    DynamicQuestPullsInfoResponse GetDynamicQuestPullsInfo();
    DynamicQuestPullByIdResponse GetDynamicQuestPullById( int pullId );
    RequestResult AddDynamicQuestPull( DynamicQuestPull questPull, string gmLogin );
    RequestResult EditDynamicQuestPull( DynamicQuestPull questPull, string gmLogin );
    RequestResult RemoveDynamicQuestPull( int pullId, string locale, string gmLogin );
    RequestResult AddDynamicQuestsToPull( int pullId, List<int> quests, string locale, string gmLogin );
    RequestResult RemoveDynamicQuestsFromPull( int pullId, List<int> quests, string locale, string gmLogin );

    // платные флаги
    FlagResponse GetAccountFlags( string login );
    RequestResult UnlockFlag( string login, string flagPersitentId, string gmLogin );
    RequestResult LockFlag(string login, string flagPersitentId, string gmLogin);

    // Изменение геолокации
    RequestResult BindGeolocation(long auid, string country, string region, string city, string gmLogin);

    TalentsEventsResponse GetTalentsEvents();
    ResourceEventsResponse GetResourceEvents();

    // Установить/убрать гм лок
    RequestResult AcquireGuildLock(long guildid, string gmlogin);
    RequestResult ReleaseGuildLock(long guildid, string gmlogin);

    // Остановить осаду
    RequestResult StopGuildSiege(long targetguildid, string gmlogin);

    // Добавить/убрать сюзерена
    RequestResult AddGuildSuzerain(long guildid, long suzerainguildid, string gmlogin);
    RequestResult RemoveGuildSuzerain(long guildid, string gmlogin);
    DynamicQuestByIdResponse GetDynamicQuestById(int id);

    AuidsListResponse GetAuidsLists();
    AuidsListByIdResponse GetAuidsListById(int index);
    RequestResult AddAuidsList(AuidsList auidsList, string gmLogin);
    RequestResult EditAuidsList(AuidsList auidsList, string gmLogin);
    RequestResult RemoveAuidsList(int index);

    FriendInfoResponse GetAccountFriends( long auid );
    RequestResult RemoveFriend( long auid, long friendAuid );

    RequestResult AddMassOperation(MassOperationInfo massOperation, string gmLogin);
    RequestResult DeleteMassOperationInfo(int operationId);
    MassOperationsResultResponse GetMassOperationsInfo();

    StringDataResponse GetFullGuildDump( long guildid, bool zip );

    // player data control
    NickSnidResponse FindPlayerByNickname(string nickname);
    NickSnidResponse FindPlayerByEmail(string email);
    NickSnidResponse PlayerChangeEmail(string email, string newEmail, string newPass);
    NickSnidResponse PlayerRemoveNickname(string email, string nickname);
  }

  public class AccountManagementService : IAccountManagementService
  {
    /// <summary>
    /// Таймаут соединения с сервисом (мс)
    /// </summary>
    public const int CONN_TIMEOUT = 30000;

    private AccountManagement.Client client;
    private static ILog _log = LogManager.GetLogger( typeof( AccountManagementService ) );

    public AccountManagementService( Uri address )
    {
      if ( address == null )
        throw new ArgumentNullException( "address" );
      // init thrift client
      TTransport transport = new THttpClient( address ) { ConnectTimeout = CONN_TIMEOUT };
      TProtocol proto = new TBinaryProtocol( transport );
      this.client = new AccountManagement.Client( proto );
    }

    private static T PerformAndHandle<T>( Func<T> function )
    {
      try
      {
        T result = function();
        _log.DebugFormat( "AccountManagement response: {0}", result );
        return result;
      }
      catch ( Exception ex )
      {
        _log.Error( "AccountManagement error", ex );
        return default( T );
      }
    }

    private static T PerformAndHandle<T>( Func<T> function, Converter<Exception, T> errhandle )
    {
      try
      {
        T result = function();
        _log.DebugFormat( "AccountManagement response: {0}", result );
        return result;
      }
      catch ( Exception ex )
      {
        _log.Error( "AccountManagement error", ex );
        if ( ex is TTransportException && ex.Message.Contains( "--->" ) ) // Специальная подпорка чтобы убрать callstack из message
        {
          var ex2 = new TTransportException( ex.Message.Remove( ex.Message.IndexOf( "--->" ) ) );
          ex = ex2;
        }
        return errhandle( ex );
      }
    }

    private static RequestResult PerformAndHandle( Func<RequestResult> function )
    {
      try
      {
        RequestResult result = function();
        _log.DebugFormat( "AccountManagement response: {0}", result );
        return result;
      }
      catch ( Exception ex )
      {
        _log.Error( "AccountManagement error", ex );
        return RequestResult.TransportException;
      }
    }

    public AccountInfoResponse GetAccountBySNUid( string snid, string snuid )
    {
      _log.DebugFormat( "AccountManagement request GetAccountBySNUid(snid={0},snuid={1})", snid, snuid );
      return PerformAndHandle( () => client.GetAccountBySNUid( snid, snuid ) ) ?? new AccountInfoResponse { Result = RequestResult.TransportException };
    }

    public SocialNetworksResponse GetSocialNetworks()
    {
      _log.Debug("AccountManagement request GetSocialNetworks()");
      return PerformAndHandle(() => client.GetSocialNetworks());
    }

    public LocaleInfoResponse GetLocaleInfoBySNUid(string snid, string snuid)
    {
      _log.DebugFormat("AccountManagement request GetLocaleInfoBySNUid(snid={0},snuid={1})", snid, snuid);
      return PerformAndHandle(() => client.GetLocaleInfoBySNUid(snid, snuid));
    }

    public LocaleInfoResponse GetLocaleInfoByAuid(long auid)
    {
      _log.DebugFormat("AccountManagement request GetLocaleInfoByAuid(auid={0})", auid);
      return PerformAndHandle(() => client.GetLocaleInfoByAuid(auid));
    }

    public AccountInfoResponse GetAccountByAuid( long auid )
    {
      _log.DebugFormat( "AccountManagement request GetAccountByAuid(auid={0})", auid );
      return PerformAndHandle( () => client.GetAccountByAuid( auid ) ) ?? new AccountInfoResponse { Result = RequestResult.TransportException };
    }
    public NickSnidResponse FindNicknameExact(string nickName)
    {
      _log.DebugFormat( "AccountManagement request GetAccountsByNickName(nickName={0})", nickName );
      return PerformAndHandle(() => client.FindNicknameExact(nickName)) ?? new NickSnidResponse { Result = RequestResult.TransportException };
    }
    public GameSessionShortInfo GetGameSession( int sessionid )
    {
      _log.DebugFormat( "AccountManagement request GetGameSession(sessionid={0})", sessionid );
      return PerformAndHandle( () => client.GetGameSession( sessionid ) ) ?? new GameSessionShortInfo { Result = RequestResult.TransportException };
    }

    public BruteForceAccountShortInfo GetBruteForceAccount(string email)
    {
        _log.DebugFormat("AccountManagement request GetBruteForceAccount(email={0})", email);
        return PerformAndHandle(() => client.GetBruteForceAccount(email)) ?? new BruteForceAccountShortInfo { Result = RequestResult.TransportException };
    }
    public RequestResult UnBanBruteForceAccount(string email)
    {
        _log.DebugFormat("AccountManagement request UnBanAccount(email={0})", email);
        return PerformAndHandle(() => client.UnBanBruteForceAccount(email));
    }

    public BannedIpFullListInfo GetBannedIp(int limit, int skip)
      {
          _log.DebugFormat("AccountManagement request GetBannedIp(limit={0}, skip={1})", limit, skip);
          return PerformAndHandle(() => client.GetBannedIp(limit, skip)) ?? new BannedIpFullListInfo() { Result = RequestResult.TransportException };          
      }

     public RequestResult UnBanIp(string ip)
      {
          _log.DebugFormat("AccountManagement request UnBanIp(email={0})", ip);
          return PerformAndHandle(() => client.UnBanIp(ip));          
      }

    public QuestsInfoResponse GetQuests(long auid)
    {
      _log.DebugFormat("AccountManagement request GetQuests(auid={0})", auid);
      return PerformAndHandle(() => client.GetQuests(auid)) ?? new QuestsInfoResponse { Result = RequestResult.TransportException };
    }

    public ServerActionResponse ChangeQuest(long auid, int questid, QuestChangeAction action, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request ChangeQuest(auid={0},questid={1},action={2},gmLogin={3})", auid, questid, action, gmLogin);
      return PerformAndHandle(() => client.ChangeQuest(auid, questid, action, gmLogin));
    }

    public HeroesResponse GetAccountHeroes( string login )
    {
      _log.DebugFormat( "AccountManagement request GetAccountHeroes(login={0})", login );
      return PerformAndHandle( () => client.GetAccountHeroes( login ) ) ?? new HeroesResponse { Result = RequestResult.TransportException };
    }
    public TalentSetResponse GetHeroTalentSet( string login, long heroInstanceId )
    {
      _log.DebugFormat( "AccountManagement request GetHeroTalentSet(login={0},heroInstanceId={1})", login, heroInstanceId );
      return PerformAndHandle( () => client.GetHeroTalentSet( login, heroInstanceId ) ) ?? new TalentSetResponse { Result = RequestResult.TransportException };
    }
    public SeasonInfoResponse GetHeroSeasonsInfo(string login, long heroInstanceId)
    {
        _log.DebugFormat("AccountManagement request GetHeroSeasonsInfo(login={0},heroInstanceId={1})", login, heroInstanceId);
        return PerformAndHandle(() => client.GetHeroSeasonsInfo(login, heroInstanceId)) ?? new SeasonInfoResponse { Result = RequestResult.TransportException };
    }

      public RequestResult EditQuestForTalent(string login, QuestForTalentEdit accEdit, string gmLogin)
      {
          _log.DebugFormat("AccountManagement request EditQuestForTalent(login={0},accEdit={1},gmLogin={2})", login, accEdit, gmLogin);
          return PerformAndHandle(() => client.EditQuestForTalent(login, accEdit, gmLogin, ""));
      }

      public QuestsForTalentsInfoResponse GetQuestsForTalentsByAuid(string login)
      {
          _log.DebugFormat("AccountManagement request GetQuestsForTalentsByAuid(login={0})", login);
          return PerformAndHandle(() => client.GetAccountQuestsForTalentsByAuid(login));
      }

      public LibraryResponse GetAccountLibrary( string login )
    {
      _log.DebugFormat( "AccountManagement request GetAccountLibrary(login={0})", login );
      return PerformAndHandle( () => client.GetAccountLibrary( login ) ) ?? new LibraryResponse { Result = RequestResult.TransportException };
    }
    public RequestResult EditAccount( string login, AccountEdit accEdit, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request EditAccount(login={0},accEdit={1},gmLogin={2})", login, accEdit, gmLogin );
      return PerformAndHandle( () => client.EditAccount( login, accEdit, gmLogin, "" ) );
    }
    public RequestResult EditHero( string login, HeroInfo heroEdit, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request EditHero(login={0},heroEdit={1},gmLogin={2})", login, heroEdit, gmLogin );
      return PerformAndHandle( () => client.EditHero( login, heroEdit, gmLogin ) );
    }
    public RequestResult LockHero( string login, long heroInstanceId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request LockHero(login={0},heroInstanceId={1},gmLogin={2})", login, heroInstanceId, gmLogin );
      return PerformAndHandle( () => client.LockHero( login, heroInstanceId, gmLogin ) );
    }
    public RequestResult EditSeasonAwards(string login, SeasonAwards awardEdit, string gmLogin)
    {
        _log.DebugFormat("AccountManagement request LockHero(login={0},awardEdit={1},gmLogin={2})", login, awardEdit, gmLogin);
        return PerformAndHandle(() => client.EditSeasonAwards(login, awardEdit, gmLogin));
    }
    public RequestResult EditSeasonInfo(string login, long heroInstanceId, SeasonInfo seasonEdit, string gmLogin)
    {
        _log.DebugFormat("AccountManagement request LockHero(login={0},heroInstanceId={1},awardEdit={2},gmLogin={3})", login, heroInstanceId, seasonEdit, gmLogin);
        return PerformAndHandle(() => client.EditSeasonInfo(login, heroInstanceId, seasonEdit, gmLogin));
    }

    public SkinsResponse GetAccountSkins(long auid)
    {
      try
      {
        _log.DebugFormat("AccountManagement.GetAccountSkins(auid={0}) request", auid);
        var result = client.GetAccountSkins(auid);
        _log.DebugFormat("AccountManagement.GetAccountSkins(auid={0}) response: {1} response.Skins: {2}",
                         auid, result, result.Skins == null ? "<null>" : String.Join(",", result.Skins.Select(s => s.ToString()).ToArray()));
        return result;
      }
      catch (TTransportException ex)
      {
        _log.Error("Transport exception in remote method GetAccountSkins", ex);
        return new SkinsResponse { Result = RequestResult.TransportException };
      }
      catch (Exception ex)
      {
        _log.Error("Failed to execute GetAccountSkins", ex);
        return null;
      }
    }
    public RequestResult AddSkin(long auid, string skinPersistentId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request AddSkin(auid={0},skinPersistentId={1},gmLogin={2})", auid, skinPersistentId, gmLogin);
      return PerformAndHandle(() => client.AddSkin(auid, skinPersistentId, gmLogin, ""));
    }
    public RequestResult DeleteSkin(long auid, string skinPersistentId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request DeleteSkin(auid={0},skinPersistentId={1},gmLogin={2})", auid, skinPersistentId, gmLogin);
      return PerformAndHandle(() => client.DeleteSkin(auid, skinPersistentId, gmLogin, ""));
    }

    public TalentUpgradeEntitiesResponse GetAccountTalentUpgradeEntities(long auid)
    {
      try
      {
        _log.DebugFormat("AccountManagement.GetAccountTalentUpgradeEntities(auid={0}) request", auid);
        var result = client.GetAccountTalentUpgradeEntities(auid);
        _log.DebugFormat("AccountManagement.GetAccountTalentUpgradeEntities(auid={0}) response: {1} response.Entities: {2}",
                         auid, result, result.Entities == null ? "<null>" : String.Join(",", result.Entities.Select(s => s.ToString()).ToArray()));
        return result;
      }
      catch (TTransportException ex)
      {
        _log.Error("Transport exception in remote method GetAccountTalentUpgradeEntities", ex);
        return new TalentUpgradeEntitiesResponse { Result = RequestResult.TransportException };
      }
      catch (Exception ex)
      {
        _log.Error("Failed to execute GetAccountTalentUpgradeEntities", ex);
        return null;
      }
    }

    public RequestResult DeleteTalentUpgradeEntity(long auid, long instanceId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request DeleteTalentUpgradeEntity(auid={0}, instanceId={1}, gmLogin={2})", auid, instanceId, gmLogin);
      return PerformAndHandle(() => client.DeleteTalentUpgradeEntity(auid, instanceId, gmLogin, ""));
    }

    public RequestResult UnlockHero( string login, int heroClassId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request UnlockHero(login={0},heroClassId={1},gmLogin={2})", login, heroClassId, gmLogin );
      return PerformAndHandle( () => client.UnlockHero( login, heroClassId, gmLogin, "" ) );
    }
    public RequestResult UnlockTalent( string login, long heroInstanceId, int talentClassId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request UnlockTalent(login={0},heroInstanceId={1},talentClassId={2},gmLogin={3})", login, heroInstanceId, talentClassId, gmLogin );
      return PerformAndHandle( () => client.AddTalent( login, talentClassId, gmLogin, "" ) );
    }
    public RequestResult UnlockTalents( string login, long heroInstanceId, int[] talentIds, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request UnlockTalents(login={0},heroInstanceId={1},talentIds=int[]({2}),gmLogin={3})", login, heroInstanceId, String.Join( ",", talentIds.Select( t => t.ToString() ).ToArray() ), gmLogin );
      List<int> talentIdsList = new List<int>( talentIds );
      return PerformAndHandle( () => client.AddTalents( login, talentIdsList, gmLogin, "" ) );
    }
    public RequestResult EditTalent( string login, TalentInfo editTalent, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request EditTalent(login={0},editTalent={1},gmLogin={2})", login, editTalent, gmLogin );
      return PerformAndHandle( () => client.EditTalent( login, editTalent, gmLogin ) );
    }
    public RequestResult LockTalent( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request LockTalent(login={0},heroInstanceId={1},talentInstanceId={2},gmLogin={3})", login, heroInstanceId, talentInstanceId, gmLogin );
      return PerformAndHandle( () => client.DeleteTalent( login, talentInstanceId, gmLogin ) );
    }

    public BuildingsInfoResponse GetAccountBuildings(long auid)
    {
      try
      {
        _log.DebugFormat("AccountManagement.GetAccountBuildings(auid={0}) request", auid);
        var result = client.GetAccountBuildings(auid);
        _log.DebugFormat("AccountManagement.GetAccountBuildings(guildid={0}) response: {1} response.guild.members: {2}",
                         auid, result, result.Buildings == null ? "<null>" : String.Join(",", result.Buildings.Select(m => m.ToString()).ToArray()));
        return result;
      }
      catch (TTransportException ex)
      {
        _log.Error("Transport exception in remote method GetAccountBuildings", ex);
        return new BuildingsInfoResponse { Result = RequestResult.TransportException };
      }
      catch (Exception ex)
      {
        _log.Error("Failed to execute GetAccountBuildings", ex);
        return null;
      }
    }

    public RequestResult MoveBuildingToStorage(long auid, long buildingInstanceId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request MoveBuildingToStorage(auid={0},buildingInstanceId={1},gmLogin={2})", auid, buildingInstanceId, gmLogin);
      return PerformAndHandle(() => client.MoveBuildingToStorage(auid, buildingInstanceId, gmLogin));
    }

    public RequestResult AddBuilding(long auid, int buildingClassId, int level, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request AddBuilding(login={0},buildingClassId={1},level={2},gmLogin={3})", auid, buildingClassId, level, gmLogin);
      return PerformAndHandle(() => client.AddBuilding(auid, buildingClassId, level, gmLogin, ""));
    }

    public RequestResult DeleteBuilding(long auid, long buildingInstanceId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request DeleteBuilding(auid={0},buildingInstanceId={1},gmLogin={2})", auid, buildingInstanceId, gmLogin);
      return PerformAndHandle(() => client.DeleteBuilding(auid, buildingInstanceId, gmLogin));
    }

    public RequestResult MoveTalentFromTalentSetToLibrary( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request MoveTalentFromTalentSetToLibrary(login={0},heroInstanceId={1},talentInstanceId={2},gmLogin={3})", login, heroInstanceId, talentInstanceId, gmLogin );
      return PerformAndHandle( () => client.MoveTalentFromTalentSetToLibrary( login, heroInstanceId, talentInstanceId, gmLogin ) );
    }
    public RequestResult MoveTalentFromLibraryToTalentSet( string login, long heroInstanceId, long talentInstanceId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request MoveTalentFromLibraryToTalentSet(login={0},heroInstanceId={1},talentInstanceId={2},gmLogin={3})", login, heroInstanceId, talentInstanceId, gmLogin );
      return PerformAndHandle( () => client.MoveTalentFromLibraryToTalentSet( login, heroInstanceId, talentInstanceId, -1, gmLogin ) );
    }

    public RequestResult RemoveTalentFromTalentSet( string login, long heroInstanceId, long talentInstanceId, int talentSetId, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request RemoveTalentFromTalentSet(login={0},heroInstanceId={1},talentInstanceId={2},talentSetId={3},gmLogin={4})", login, heroInstanceId, talentInstanceId, talentSetId, gmLogin );
      return PerformAndHandle( () => client.RemoveTalentFromTalentSet( login, heroInstanceId, talentInstanceId, talentSetId, gmLogin ) );
    }

    public RequestResult GiveLamp( string login, LampInfo lampInfo, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request GiveLamp(login={0},bonus={1},gold={2},transaction={3},duration={4},gmLogin={5})", login, lampInfo.Bonus, lampInfo.GoldBonus, lampInfo.Transaction, lampInfo.Duration, gmLogin );
      return PerformAndHandle( () => client.GiveLamp( login, lampInfo, gmLogin, "" ) );
    }

    public RequestResult GiveUpgradeHeroTalents(string login, UpgradeHeroTalentsInfo upgradeHeroTalentsInfo, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request UpgradeHeroTalentsInfo(usesLeft={0}, gmLogin={1})", login, upgradeHeroTalentsInfo.UsesLeft, gmLogin);
      return PerformAndHandle(() => client.GiveUpgradeHeroTalents(login, upgradeHeroTalentsInfo, gmLogin, ""));
    }

    public RequestResult DisjointSN(long auid, string snid)
    {
      _log.DebugFormat("AccountManagement.DisjointSN(auid={0},snid={1})", auid, snid);
      return PerformAndHandle(() => client.DisjointSN(auid, snid));
    }

    public RequestResult ChangeFSN( long auid, string snid )
    {
      _log.DebugFormat( "AccountManagement.ChangeFSN(auid={0},snid={1})", auid, snid );
      return PerformAndHandle( () => client.ChangeFSN( auid, snid ) );
    }

    public RequestResult DeleteSaAccount(long auid)
    {
      _log.DebugFormat("AccountManagement.DeleteSaAccount(auid={0})", auid);
      return PerformAndHandle(() => client.DeleteSAAccount(auid));
    }

    public RequestResult EditTournamentInfo(string login, TournamentInfo tournamentInfo, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request EditTournamentInfo(login={0},wins={1},losses={2},lastGameTime={3},ticketPriseState={4}, state={5}, gmLogin={6})", login, tournamentInfo.Wins, tournamentInfo.Losses, tournamentInfo.LastGameTime, tournamentInfo.TicketPriseState, tournamentInfo.State, gmLogin);
      return PerformAndHandle(() => client.EditTournamentInfo(login, tournamentInfo, gmLogin));
    }

    public GuildInfoResponse GetGuildById( long guildid )
    {
      try
      {
        _log.DebugFormat( "AccountManagement.GetGuildById(guildid={0}) request", guildid );
        var result = client.GetGuildById( guildid );
        _log.DebugFormat("AccountManagement.GetGuildById(guildid={0}) response: {1}\ninfo: {2}",
                         guildid, result.Result, Format(result.Guild));
        return result;
      }
      catch ( TTransportException ex )
      {
        _log.Error( "Transport exception in remote method GetGuildById", ex );
        return new GuildInfoResponse { Result = RequestResult.TransportException };
      }
      catch ( Exception ex )
      {
        _log.Error( "Failed to execute GetGuildById", ex );
        return null;
      }
    }

    public GuildInfoResponse GetGuildByName( string shortname, string fullname )
    {
      try
      {
        _log.DebugFormat( "AccountManagement.GetGuildByName(shortname={0},fullname={1}) request", shortname, fullname );
        var result = client.GetGuildByName( shortname, fullname );
        _log.DebugFormat("AccountManagement.GetGuildByName(shortname={0},fullname={1}) response: {2}\ninfo: {3}",
                         shortname, fullname, result.Result, Format(result.Guild));
        return result;
      }
      catch ( TTransportException ex )
      {
        _log.Error( "Transport exception in remote method GetGuildByName", ex );
        return new GuildInfoResponse { Result = RequestResult.TransportException };
      }
      catch ( Exception ex )
      {
        _log.Error( "Failed to execute GetGuildByName", ex );
        return null;
      }
    }


    private string Format(GuildInfo info)
    {
      var sb = new StringBuilder();
      sb.AppendFormat("GuildInfo({0})", info);
      if (info.Members != null)
      {
        sb.Append("\n\tMembers=List(");
        foreach (var m in info.Members)
          sb.Append(m + ",");
        sb.Append(")");
      }
      if (info.Vassals != null)
      {
        sb.Append("\n\tVassals=List(");
        foreach (var m in info.Vassals)
          sb.Append(m + ",");
        sb.Append(")");
      }
      return sb.ToString();
    }


    public RequestResult EditGuild(GuildEditInfo info, string gmlogin)
    {
      _log.DebugFormat("RequestResult request EditGuild(guildid={0},shortname={1},fullname={2}," +
                       "messageoftheday={3},guildExperience={4},cwguildpoints={5})",
        info.Guildid, info.Shortname, info.Fullname, info.Messageoftheday, info.GuildExperience, info.Cwguildpoints);
      return PerformAndHandle(() => client.EditGuild(info, gmlogin));
    }

    public RequestResult ChangeGuildLeader( long guildid, long auid, string gmlogin )
    {
      _log.DebugFormat( "RequestResult request ChangeGuildLeader(guildid={0},auid={1}, gmLogin={2})", guildid, auid, gmlogin );
      return PerformAndHandle( () => client.ChangeGuildLeader( guildid, auid, gmlogin ) );
    }

    public RequestResult RemoveGuildMembers( long guildid, List<long> auids, string gmlogin )
    {
      _log.DebugFormat( "RequestResult request RemoveGuildMembers(guildid={0},auids={1}, gmLogin={2})", guildid, auids, gmlogin );
      return PerformAndHandle( () => client.RemoveGuildMembers( guildid, auids, gmlogin ) );
    }

    public GuildMemberInfoResponse GetGuildMemberById(long guildid, long auid)
    {
      _log.DebugFormat("RequestResult request GetGuildMemberById(guildid={0},auid={1})", guildid, auid);
      return PerformAndHandle(() => client.GetGuildMemberById(guildid, auid));
    }

    public RequestResult EditGuildMember( long guildid, GuildMemberInfo member, string gmlogin )
    {
      _log.DebugFormat( "RequestResult request EditGuildMember(guildid={0},member={1}, gmLogin={2})", guildid, member, gmlogin );
      return PerformAndHandle( () => client.EditGuildMember( guildid, member, gmlogin ) );
    }

    public RequestResult SetGuildIcon( long guildid, byte[] image )
    {
      _log.DebugFormat( "RequestResult request SetGuildIcon(guildid={0},image=byte[{1}])", guildid, image.Length );
      return PerformAndHandle( () => client.SetGuildIcon( guildid, image ) );
    }

    public RequestResult SwitchToNewGuildIcon( long guildid, string gmlogin )
    {
      _log.DebugFormat( "RequestResult request SwitchToNewIcon(guildid={0}, gmLogin={1})", guildid, gmlogin );
      return PerformAndHandle( () => client.SwitchToNewGuildIcon( guildid, gmlogin ) );
    }

    public ServerActionResponse TryToPayForGuildIconChange( long leaderauid, int changeiter )
    {
      _log.DebugFormat( "RequestResult request TryToPayForGuildIconChange(leaderauid={0},changeiter={1})", leaderauid, changeiter );
      return PerformAndHandle( () => client.TryToPayForGuildIconChange( leaderauid, changeiter ) );
    }

    public AdminMessagesResponse GetAccountAdminMessages( string login )
    {
      _log.DebugFormat("AccountManagement request GetAccountAdminMessages(login={0})", login);
      return PerformAndHandle(() => client.GetAccountAdminMessages(login));
    }

    public RequestResult SendMessageToUser( long auid, string login, string messageTitle, string messageText, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request SendMessageToUser(auid={0},login={1},messageTitle={2},messageText={3},gmLogin={4})", auid, login, messageTitle, messageText, gmLogin );
      return PerformAndHandle( () => client.SendMessageToUser( login, auid, messageTitle, messageText, gmLogin, "" ) );
    }

    public RequestResult UserOperation(long auid, UserOperationType type, int value, string reason, List<int> claims, string gmLogin, List<long> claimAuids)
    {
      _log.DebugFormat("AccountManagement request UserOperation(type={0},auid={1},value={2},reason={3},claims=[{4}],gmLogin={5},claimAuids={6})",
                       type, auid, value, reason, ListToString(claims), gmLogin, ListToString(claimAuids));
      return type == UserOperationType.SetLeave
        ? PerformAndHandle(() => client.UserOperation(auid, type, 0, reason, claims, gmLogin, claimAuids, value))
        : PerformAndHandle(() => client.UserOperation(auid, type, value, reason, claims, gmLogin, claimAuids, 0));
    }

    public RequestResult KickUser( string login, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request KickUser(login={0},gmLogin={1})", login, gmLogin );
      return PerformAndHandle( () => client.KickUser( login, gmLogin ) );
    }
    public RequestResult ResetUserAccount( string login, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request ResetUserAccount(login={0},gmLogin={1})", login, gmLogin );
      return PerformAndHandle( () => client.ResetUserAccount( login, gmLogin ) );
    }

    public BroadcastCreateResponse CreateBroadcast(BroadcastInfo createInfo, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request CreateBroadcast(info={0},gmLogin={1})", createInfo, gmLogin);
      return PerformAndHandle(() => client.CreateBroadcast(createInfo, gmLogin)) ?? new BroadcastCreateResponse { Result = RequestResult.TransportException };
    }

    public BroadcastLocalesResponse GetBroadcastLocales()
    {
      _log.DebugFormat("AccountManagement request GetBroadcastLocales()");
      return PerformAndHandle(() => client.GetBroadcastLocales());
    }

    public RequestResult EditBroadcast(BroadcastInfo editInfo, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request EditBroadcastMessage(editMessage={0},gmLogin={1})", editInfo, editInfo);
      return PerformAndHandle(() => client.EditBroadcast(editInfo, gmLogin));
    }

    public RequestResult DeleteBroadcast(int id, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request DeleteBroadcastMessage(id={0},gmLogin={1})", id, gmLogin );
      return PerformAndHandle(() => client.DeleteBroadcast(id, gmLogin));
    }

    public BroadcastListResponse GetBroadcastList( int skipLines, int takeLines )
    {
      _log.DebugFormat( "AccountManagement request GetBroadcastList(skipLines={0},takeLines={1})", skipLines, takeLines );
      return PerformAndHandle( () => client.GetBroadcastList( skipLines, takeLines ) ) ?? new BroadcastListResponse { Result = RequestResult.TransportException };
    }

    public RequestResult StartMessageRotation( int id, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request StartMessageRotation(id={0},gmLogin={1})", id, gmLogin );
      return PerformAndHandle( () => client.StartMessageRotation( id, gmLogin ) );
    }

    public RequestResult StopMessageRotation( int id, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request StopMessageRotation(id={0},gmLogin={1})", id, gmLogin );
      return PerformAndHandle( () => client.StopMessageRotation( id, gmLogin ) );
    }

    public SocServerVersionResponse GetSocServerVersion()
    {
      _log.DebugFormat( "AccountManagement request GetSocServerVersion()" );
      return PerformAndHandle( () => client.GetSocServerVersion() ) ?? new SocServerVersionResponse { Result = RequestResult.TransportException };
    }
    public StringDataResponse GetFullUserDump( string login, bool zip )
    {
      _log.DebugFormat( "AccountManagement request GetFullUserDump(login={0},zip={1})", login, zip );
      return PerformAndHandle( () => client.GetFullUserDump( login, zip ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }
    public RequestResult ApplyFullUserDump( string login, string dumpdata )
    {
      _log.DebugFormat( "AccountManagement request ApplyFullUserDump(login={0},dumpdata={1})", login, dumpdata );
      return PerformAndHandle( () => client.ApplyFullUserDump( login, dumpdata ) );
    }
    public RequestResult RemoveFakeAuid( string login )
    {
      _log.DebugFormat( "AccountManagement request RemoveFakeAuid(login={0})", login );
      return PerformAndHandle( () => client.RemoveFakeAuid( login ) );
    }
    public RequestResult ActivateEmail( string email, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request ActivateEmail(email={0}, gmLogin={1})", email, gmLogin );
      return PerformAndHandle( () => client.ActivateEmail( email, gmLogin ) );
    }
    public UserDumpsDataResponse GetBackups()
    {
      _log.DebugFormat( "AccountManagement request GetBackups()" );
      return PerformAndHandle( () => client.GetBackups() ) ?? new UserDumpsDataResponse { Result = RequestResult.TransportException };
    }
    public StringDataResponse GetBrokenUserDump( string login, string date, bool zip )
    {
      _log.DebugFormat( "AccountManagement request GetBrokenUserDump(login={0},zip={1})", login, zip );
      return PerformAndHandle( () => client.GetBrokenUserDump( login, date, zip ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }
    public StringDataResponse GetBrokenUserDumpByNickname( string nickname, string date, bool zip )
    {
      _log.DebugFormat( "AccountManagement request GetBrokenUserDumpByNickname(nickname={0},zip={1})", nickname, zip );
      return PerformAndHandle( () => client.GetBrokenUserDumpByNickname( nickname, date, zip ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }
    public RequestResult EditFreeChanges( string login, string gmLogin, int nickChanges, int fractionChanges )
    {
      _log.DebugFormat( "AccountManagement request EditFreeChanges(login={0},gmLogin={1},nickChanges={2},fractionChanges={3})", login, gmLogin, nickChanges, fractionChanges );
      return PerformAndHandle( () => client.EditFreeChanges( login, gmLogin, nickChanges, fractionChanges ) );
    }
    public StringDataResponse EditNickname( string login, string gmLogin, string nickname )
    {
      _log.DebugFormat( "AccountManagement request EditNickname(login={0},gmLogin={1},nickname={2})", login, gmLogin, nickname );
      return PerformAndHandle( () => client.EditNickname( login, gmLogin, nickname ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }
    public StringDataResponse CheckAccountValidity( string login )
    {
      _log.DebugFormat( "AccountManagement request CheckAccountValidity(login={0})", login );
      return PerformAndHandle( () => client.CheckAccountValidity( login ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }
    public RequestResult FixAccount( string login, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request FixAccount(login={0},gmLogin={1})", login, gmLogin );
      return PerformAndHandle( () => client.FixAccount( login, gmLogin ) );
    }

    public RequestResult FlushServerId( string login, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request FlushServerId(login={0},gmLogin={1})", login, gmLogin );
      return PerformAndHandle( () => client.FlushServerId( login, gmLogin ) );
    }

    public ServerActionResponse PayEditNickname( string login, string nickname )
    {
      try
      {
        _log.DebugFormat( "AccountManagement request PayEditNickname(login={0},nickname={1})", login, nickname );
        var result = client.PayEditNickname( login, nickname );
        _log.DebugFormat( "AccountManagement.PayEditNickname response: {0}", result );
        return result;
      }
      catch ( TTransportException ex )
      {
        _log.Error( "Transport exception in remote method PayEditNickname", ex );
        return new ServerActionResponse { Result = RequestResult.TransportException, Error = ex.Message };
      }
      catch ( Exception ex )
      {
        _log.Error( "Failed to execute PayEditNickname", ex );
        return null;
      }
    }

    public ServerActionResponse PayChangeFraction( string login, int fraction )
    {
      try
      {
        _log.DebugFormat( "AccountManagement request PayChangeFraction(login={0},fraction={1})", login, fraction );
        var result = client.PayChangeFraction( login, fraction );
        _log.DebugFormat( "AccountManagement.PayChangeFraction response: {0}", result );
        return result;
      }
      catch ( TTransportException ex )
      {
        _log.Error( "Transport exception in remote method PayChangeFraction", ex );
        return new ServerActionResponse { Result = RequestResult.TransportException, Error = ex.Message };
      }
      catch ( Exception ex )
      {
        _log.Error( "Failed to execute PayChangeFraction", ex );
        return null;
      }
    }

    public RequestResult PayService(string login, PayServiceType type, int param1, string gmLogin)
    {
      _log.DebugFormat( "AccountManagement request PayService(login={0},PayServiceType={1})", login, type );
      return PerformAndHandle(() => client.PayService(login, type, param1, gmLogin));
      //                              ex => new ServerActionResponse {Result = RequestResult.TransportException, Error = ex.Message});
    }

    public RequestResult EditAccountDbValue( string login, string gmLogin, string key, string value )
    {
      _log.DebugFormat( "AccountManagement request EditAccountDbValue(login={0},gmLogin={1},key={2},key={3})", login, gmLogin, key, value );
      return PerformAndHandle( () => client.EditAccountDbValue( login, gmLogin, key, value ) );
    }

    public UpgradeHeroTalentsInfoResponse GetUpgradeHeroTalentsInfo(string login)
    {
        _log.DebugFormat("AccountManagement request GetUpgradeHeroTalentsInfo(login={0})", login);
        return PerformAndHandle(() => client.GetUpgradeHeroTalentsInfo(login)) ?? new UpgradeHeroTalentsInfoResponse { Result = RequestResult.TransportException };
    }

    public LampInfoResponse GetLampInfo( string login )
    {
      _log.DebugFormat( "AccountManagement request GetLampInfo(login={0})", login );
      return PerformAndHandle( () => client.GetLampInfo( login ) ) ?? new LampInfoResponse { Result = RequestResult.TransportException };
    }

    public TournamentInfoResponse GetAccountTournamentInfo(string login)
    {
      _log.DebugFormat("AccountManagement request GetAccountTournamentInfo(login={0})", login);
      return PerformAndHandle(() => client.GetAccountTournamentInfo(login)) ?? new TournamentInfoResponse { Result = RequestResult.TransportException };
    }

    public GiveTournamentTicketResponse GiveTournamentTicket(string login)
    {
      _log.DebugFormat("AccountManagement request GiveTournamentTicket(login={0})", login);
      return PerformAndHandle(() => client.GiveTournamentTicket(login)) ?? new GiveTournamentTicketResponse { Result = RequestResult.TransportException };
    }

    public TournamentGamesInfoResponse GetAccountTournamentGames(string login)
    {
      _log.DebugFormat("AccountManagement request GetAccountTournamentGames(login={0})", login);
      return PerformAndHandle(() => client.GetAccountTournamentGames(login)) ?? new TournamentGamesInfoResponse { Result = RequestResult.TransportException };
    }

    public GuildBankTalentsResponse GetFreeGuildBankTalents( long guildid )
    {
      _log.DebugFormat("AccountManagement request GetFreeGuildBankTalents(guildid={0})", guildid);
      return PerformAndHandle(() => client.GetFreeGuildBankTalents(guildid)) ?? new GuildBankTalentsResponse { Result = RequestResult.TransportException };
    }

    public GuildBankTalentsResponse GetTakenGuildBankTalents( long guildid )
    {
      _log.DebugFormat("AccountManagement request GetTakenGuildBankTalents(guildid={0})", guildid);
      return PerformAndHandle(() => client.GetTakenGuildBankTalents(guildid)) ?? new GuildBankTalentsResponse { Result = RequestResult.TransportException };
    }

    public RequestResult ReturnTalentToOwner( long guildid, long talentId, string gmlogin )
    {
      _log.DebugFormat( "AccountManagement request ReturnTalentToOwner(guildid={0}, talentId={1}, gmLogin={2})", guildid, talentId, gmlogin );
      return PerformAndHandle( () => client.ReturnTalentToOwner( guildid, talentId, gmlogin ) );
    }

    public RequestResult ReturnTalentToGuildBank( long guildid, long talentId, string gmlogin )
    {
      _log.DebugFormat( "AccountManagement request ReturnTalentToGuildBank(guildid={0}, talentId={1}, gmLogin={2})", guildid, talentId, gmlogin );
      return PerformAndHandle( () => client.ReturnTalentToGuildBank( guildid, talentId, gmlogin ) );
    }

    public DynamicQuestInfoResponse GetDynamicQuestInfo()
    {
      _log.DebugFormat("AccountManagement request GetDynamicQuestInfo");
      return PerformAndHandle(() => client.GetDynamicQuestInfo()) ?? new DynamicQuestInfoResponse { Result = RequestResult.TransportException };
    }

    public AddDynamicQuestResponse AddDynamicQuest(string jsonQuestData, string locale, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request AddDynamicQuest(jsonQuestData={0}, locale={1}, gmLogin={2})", jsonQuestData, locale, gmLogin);
      return PerformAndHandle(() => client.AddDynamicQuest(jsonQuestData, locale, gmLogin));
    }

    public RequestResult RemoveDynamicQuest(int questId, string locale)
    {
      _log.DebugFormat("AccountManagement request RemoveDynamicQuest(locale={0}, questId={1})", locale, questId);
      return PerformAndHandle(() => client.RemoveDynamicQuest(questId, locale));
    }

    public RequestResult EditDynamicQuest(int questId, string locale, string jsonQuestData)
    {
      _log.DebugFormat( "AccountManagement request EditDynamicQuest(locale={0}, questId={1}, jsonQuestData={2})", locale, questId, jsonQuestData );
      return PerformAndHandle( () => client.EditDynamicQuest( questId, locale, jsonQuestData ) );
    }

    public DynamicQuestPullsInfoResponse GetDynamicQuestPullsInfo()
    {
      _log.DebugFormat( "AccountManagement request GetDynamicQuestPullsInfo" );
      return PerformAndHandle( () => client.GetDynamicQuestPullsInfo() ) ?? new DynamicQuestPullsInfoResponse { Result = RequestResult.TransportException };
    }

    public DynamicQuestPullByIdResponse GetDynamicQuestPullById(int pullId)
    {
      _log.DebugFormat( "AccountManagement request GetDynamicQuestPullById" );
      return PerformAndHandle( () => client.GetDynamicQuestPullById(pullId) ) ?? new DynamicQuestPullByIdResponse { Result = RequestResult.TransportException };
    }

    public RequestResult AddDynamicQuestPull( DynamicQuestPull questPull, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request AddDynamicQuestPull(questPull={0}, gmLogin={1})", questPull, gmLogin );
      return PerformAndHandle( () => client.AddDynamicQuestPull( questPull, gmLogin ) );
    }

    public RequestResult RemoveDynamicQuestPull( int questId, string locale, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request RemoveDynamicQuestPull(locale={0}, questId={1}, gmLogin={2})", locale, questId, gmLogin );
      return PerformAndHandle( () => client.RemoveDynamicQuestPull( questId, locale, gmLogin ) );
    }

    public RequestResult EditDynamicQuestPull( DynamicQuestPull questPull, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request EditDynamicQuestPull(questPull={0}, gmLogin={1})", questPull, gmLogin );
      return PerformAndHandle( () => client.EditDynamicQuestPull( questPull, gmLogin ) );
    }

    public RequestResult AddDynamicQuestsToPull( int pullId, List<int> quests, string locale, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request AddDynamicQuestsToPull(pullId={0}, quests={1}, locale={2}, gmLogin={3})", pullId, quests, locale, gmLogin );
      return PerformAndHandle( () => client.AddDynamicQuestsToPull( pullId, quests, locale, gmLogin ) );
    }

    public RequestResult RemoveDynamicQuestsFromPull( int pullId, List<int> quests, string locale, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request RemoveDynamicQuestsFromPull(pullId={0}, quests={1}, locale={2}, gmLogin={3})", pullId, quests, locale, gmLogin );
      return PerformAndHandle( () => client.RemoveDynamicQuestsFromPull( pullId, quests, locale, gmLogin ) );
    }

    public FlagResponse GetAccountFlags(string login)
    {
      _log.DebugFormat("AccountManagement request GetAccountFlags(login={0})", login);
      return PerformAndHandle(() => client.GetAccountFlags(login)) ?? new FlagResponse { Result = RequestResult.TransportException };
    }

    public RequestResult LockFlag(string login, string flagPersistentId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request LockFlag(login={0}, flagPersistentId={1}, gmLogin={2})", login, flagPersistentId, gmLogin);
      return PerformAndHandle(() => client.LockFlag(login, flagPersistentId, gmLogin, ""));
    }

    public RequestResult BindGeolocation(long auid, string country, string region, string city, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request BindGeolocation(auid={0}, country={1}, region={2}, city={3}, gmLogin={4})", auid, country, region, city, gmLogin);
      return PerformAndHandle(() => client.BindToGeolocation(auid, country, region, city, gmLogin));
    }

    public RequestResult UnlockFlag(string login, string flagPersistentId, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request UnlockFlag(login={0}, flagPersistentId={1}, gmLogin={2})", login, flagPersistentId, gmLogin);
      return PerformAndHandle(() => client.UnlockFlag(login, flagPersistentId, gmLogin, ""));
    }

    public TalentsEventsResponse GetTalentsEvents()
    {
      _log.DebugFormat("AccountManagement request GetTalentsEvents()");
      return PerformAndHandle(() => client.GetTalentsEvents());
    }

    public ResourceEventsResponse GetResourceEvents()
    {
      _log.DebugFormat("AccountManagement request GetResourceEvents()");
      return PerformAndHandle(() => client.GetResourceEvents());
    }

    // Установить/убрать гм лок
    public RequestResult AcquireGuildLock(long guildid, string gmlogin)
    {
      _log.DebugFormat("AccountManagement request AcquireGuildLock()");
      return PerformAndHandle(() => client.AcquireGuildLock(guildid, gmlogin));
    }

    public RequestResult ReleaseGuildLock(long guildid, string gmlogin)
    {
      _log.DebugFormat("AccountManagement request ReleaseGuildLock()");
      return PerformAndHandle(() => client.ReleaseGuildLock(guildid, gmlogin));
    }

    // Остановить осаду
    public RequestResult StopGuildSiege(long targetguildid, string gmlogin)
    {
      _log.DebugFormat("AccountManagement request StopGuildSiege()");
      return PerformAndHandle(() => client.StopGuildSiege(targetguildid, gmlogin));
    }

    // Добавить/убрать сюзерена
    public RequestResult AddGuildSuzerain(long guildid, long suzerainguildid, string gmlogin)
    {
      _log.DebugFormat("AccountManagement request AddGuildSuzerain()");
      return PerformAndHandle(() => client.AddGuildSuzerain(guildid, suzerainguildid, gmlogin));
    }

    public RequestResult RemoveGuildSuzerain(long guildid, string gmlogin)
    {
      _log.DebugFormat("AccountManagement request RemoveGuildSuzerain()");
      return PerformAndHandle(() => client.RemoveGuildSuzerain(guildid, gmlogin));
    }

    public DynamicQuestByIdResponse GetDynamicQuestById(int id)
    {
      _log.DebugFormat("AccountManagement request GetDynamicQuestById({0})", id);
      return PerformAndHandle(() => client.GetDynamicQuestById(id));
    }

    public AuidsListResponse GetAuidsLists()
    {
      _log.DebugFormat("AccountManagement request GetAuidsLists()");
      return PerformAndHandle(() => client.GetAuidsLists());
    }

    public AuidsListByIdResponse GetAuidsListById(int index)
    {
      _log.DebugFormat("AccountManagement request GetAuidsListById({0})", index);
      return PerformAndHandle(() => client.GetAuidsListById(index));
    }

    public RequestResult AddAuidsList(AuidsList auidsList, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request AddAuidsList({0})", auidsList);
      return PerformAndHandle(() => client.AddAuidsList(auidsList, gmLogin));
    }

    public RequestResult EditAuidsList(AuidsList auidsList, string gmLogin)
    {
      _log.DebugFormat("AccountManagement request EditAuidsList({0})", auidsList);
      return PerformAndHandle(() => client.EditAuidsList(auidsList, gmLogin));
    }

    public RequestResult RemoveAuidsList(int index)
    {
      _log.DebugFormat("AccountManagement request RemoveAuidsList({0})", index);
      return PerformAndHandle(() => client.RemoveAuidsList(index));
    }

    public FriendInfoResponse GetAccountFriends(long auid)
    {
      _log.DebugFormat( "AccountManagement request GetAccountFriends({0})", auid );
      return PerformAndHandle( () => client.GetAccountFriends( auid ) );
    }

    public RequestResult RemoveFriend( long auid, long friendAuid )
    {
      _log.DebugFormat( "AccountManagement request RemoveFriend(auid={0}, friendAuid]{1})", auid, friendAuid );
      return PerformAndHandle( () => client.RemoveFriend( auid, friendAuid ) );
    }

    public RequestResult AddMassOperation( MassOperationInfo massOperation, string gmLogin )
    {
      _log.DebugFormat( "AccountManagement request AddMassOperation(massOperation={0}, gmLogin]{1})", massOperation, gmLogin );
      return PerformAndHandle( () => client.AddMassOperation( massOperation, gmLogin ) );
    }

    public RequestResult DeleteMassOperationInfo( int operationId )
    {
      _log.DebugFormat( "AccountManagement request DeleteMassOperationInfo(operationId={0}", operationId );
      return PerformAndHandle( () => client.DeleteMassOperationInfo( operationId ) );
    }
    public MassOperationsResultResponse GetMassOperationsInfo()
    {
      _log.DebugFormat( "AccountManagement request GetMassOperationsInfo()" );
      return PerformAndHandle( () => client.GetMassOperationsInfo() );
    }

    public StringDataResponse GetFullGuildDump( long guildid, bool zip )
    {
      _log.DebugFormat( "AccountManagement request GetFullGuildDump(guildid={0},zip={1})", guildid, zip );
      return PerformAndHandle( () => client.GetFullGuildDump( guildid, zip ) ) ?? new StringDataResponse { Result = RequestResult.TransportException };
    }

    public NickSnidResponse FindPlayerByNickname(string nickname)
    {
      //FOR TESTS
      //return new NickSnidResponse
      //{
      //  Result = RequestResult.Success,
      //  FoundAccount = new AccountShortInfo
      //  {
      //    Email = "testEmail",
      //    Login = "testLogin",
      //    Nickname = "testNickname",
      //    Snid = "12312312321",
      //    Snuid = "123123112312132"
      //  }
      //};
      _log.DebugFormat("AccountManagement request FindPlayerByNickname(nickname={0})", nickname);
      return PerformAndHandle(() => client.FindPlayerByNickname(nickname)) ?? new NickSnidResponse { Result = RequestResult.TransportException };
    }

    public NickSnidResponse FindPlayerByEmail(string email)
    {
      //FOR TESTS
      //return new NickSnidResponse
      //{
      //  Result = RequestResult.Success,
      //  FoundAccount = new AccountShortInfo
      //  {
      //    Email = "testEmail",
      //    Login = "testLogin",
      //    Nickname = "testNickname",
      //    Snid = "12312312321",
      //    Snuid = "123123112312132"
      //  }
      //};
      _log.DebugFormat("AccountManagement request FindPlayerByEmail(email={0})", email);
      return PerformAndHandle(() => client.FindPlayerByEmail(email)) ?? new NickSnidResponse { Result = RequestResult.TransportException }; 
    }

    public NickSnidResponse PlayerChangeEmail(string email, string newEmail, string newPass)
    {
      //FOR TESTS
      //return new NickSnidResponse
      //{
      //  Result = RequestResult.Success,
      //  FoundAccount = new AccountShortInfo
      //  {
      //    Email = "testEmail",
      //    Login = "testLogin",
      //    Nickname = "testNickname",
      //    Snid = "12312312321",
      //    Snuid = "123123112312132"
      //  }
      //};
      _log.DebugFormat("AccountManagement request PlayerChangeEmail(email={0},newEmail={1},newPass={2})", email, newEmail, newPass);
      return PerformAndHandle(() => client.PlayerChangeEmail(email, newEmail, newPass)) ?? new NickSnidResponse { Result = RequestResult.TransportException }; 
    }

    //wipe
    public NickSnidResponse PlayerRemoveNickname(string email, string nickname)
    {
      //FOR TESTS
      //return new NickSnidResponse 
      //{
      //  Result = RequestResult.Success,
      //  FoundAccount = new AccountShortInfo
      //  {
      //    Email = "testEmail",
      //    Login = "testLogin",
      //    Nickname = "testNickname",
      //    Snid = "12312312321",
      //    Snuid = "123123112312132"
      //  }
      //};
      _log.DebugFormat("AccountManagement request PlayerRemoveNickname(email={0}, nickname={1})", email);
      return PerformAndHandle(() => client.PlayerRemoveNickname(email, nickname)) ?? new NickSnidResponse { Result = RequestResult.TransportException }; 
    }

    private void Test()
    {
      var list = new List<int> { 1, 2, 3, 4 };
      ListToString(list);
    }

    /// <summary>
    /// Небольшой хелпер для распечатывания массивов
    /// </summary>
    private string ListToString(IEnumerable list)
    {
      if (list == null)
        return String.Empty;
      string res = "";
      foreach (var obj in list)
        res += obj + ",";
      return res.TrimEnd(',');
    }
  }
}