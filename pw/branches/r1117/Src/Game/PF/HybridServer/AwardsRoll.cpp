#include "stdafx.h"
#include "AwardsRoll.h"
#include "Db/DBServer.auto.h"


namespace Peered
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AwardsRequester::RollClientCb : public roll::IClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RollClientCb, roll::IClient, BaseObjectMT );

  RollClientCb( AwardsRequester * _owner ) : owner( _owner ) {}

  virtual void RollResults( const TUserAwards & _award )
  {
    if ( StrongMT<AwardsRequester> locked = owner.Lock() )
      locked->OnRollResults( _award );
  }

  virtual void ForgeRollAck() {}

  virtual void RollFailed()
  {
    if ( StrongMT<AwardsRequester> locked = owner.Lock() )
      locked->OnRollFailed();
  }

  WeakMT<AwardsRequester> owner;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AwardsRequester::AwardsRequester(
  rpc::IfaceRequester<roll::RIBalancer> * _rollBalancer,
  NLogg::CChannelLogger * _logStream,
  TSessionId _serverId,
  int _retryTimer)
  : logStream(_logStream)
  , serverId(_serverId)
  , isInterfaceRequested(false)
  , isAwardsReceived(false)
  , retryTimer(_retryTimer)
  , currentTimer(0)
{
  if (_rollBalancer)
    rollBalancer = _rollBalancer;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::FillPreGameData(const nstl::vector<ClientInfo> & _clientsInfo, const SAuxData & _auxData)
{
  preGameData.socialLobbyGameId = _auxData.socialLobbyGameId;
  preGameData.mapDesc = _auxData.mapDesc;
  preGameData.mmBasket = _auxData.mmBasket;
  preGameData.guildData = _auxData.guildData;
  preGameData.sessionType = _auxData.sessiontype;

  if ( _auxData.lobbyGameType == lobby::EGameType::Custom )
  {
    preGameData.mode = roll::EMode::Train;
  }
  else if ( _auxData.lobbyGameType == lobby::EGameType::SocialMMaking )
  {
    switch ( _auxData.mapType )
    {
      case NDb::MAPTYPE_PVP:
      case NDb::MAPTYPE_CTE:
        if ( _auxData.customGame )
          preGameData.mode = roll::EMode::CustomGame;
        else if ( _auxData.hadPreGameLobby )
          preGameData.mode = roll::EMode::LobbyPvp;
        else
          preGameData.mode = roll::EMode::PvP;
        break;

      case NDb::MAPTYPE_TRAINING:
        preGameData.mode = roll::EMode::Train;
        break;

      case NDb::MAPTYPE_TUTORIAL:
        preGameData.mode = roll::EMode::Tutorial;
        break;

      case NDb::MAPTYPE_SERIES:
        preGameData.mode = roll::EMode::Singleplayer;
        break;

      case NDb::MAPTYPE_COOPERATIVE:
        preGameData.mode = roll::EMode::Coop;
        break;

      default:
        break;
    }
  }

  preGameData.users.reserve( _auxData.users.size() );

  for ( int i = 0; i < _auxData.users.size(); ++i )
  {
    const SAuxUserData & userSrc = _auxData.users[i];

    preGameData.users.push_back( roll::SPreGamePerUserData() );
    roll::SPreGamePerUserData & userDst = preGameData.users.back();

    userDst.clientId = userSrc.clientId;
    userDst.faction = userSrc.faction;

    bool found = false;
    for (int j = 0; j < _clientsInfo.size(); ++j)
    {
      const ClientInfo * clientInfo = &_clientsInfo[j];
      if (clientInfo->clientId == userDst.clientId)
      {
        found = true;
        userDst.playerInfo = clientInfo->info;
        break;
      }
    }

    if (!found)
    {
      localLog(logStream, NLogg::LEVEL_ERROR).Trace(
        "GameServer: FillPreGameData: Client info not found (sid=%016x cid=%d)", serverId, userSrc.clientId);
    }
  }
}



void AwardsRequester::FillExtraData(StatisticService::SessionPlayerExtra& extra, const vector<roll::SPreGamePerUserData>& _preData, roll::UserId _clientId )
{ 

  struct Party
  {
    lobby::ETeam::Enum team;
    vector< NCore::TAuid> users;
  };

  typedef nstl::map<uint, Party> PartyData;
  typedef nstl::map<lobby::ETeam::Enum, PartyData > TeamData;

  PartyData parties;
  TeamData teams;
  vector<roll::SPreGamePerUserData>::const_iterator uit = _preData.begin();
  

  uint partyId = 0;
  lobby::ETeam::Enum team = lobby::ETeam::None;
  for (;uit != _preData.end(); ++uit)
  {
    if (_clientId == uit->clientId)
    {
      partyId = uit->playerInfo.partyId;
      team = uit->faction;
      extra.isGuildFight = uit->playerInfo.guildData.guidWarEventPass;
    }
    PartyData::const_iterator it=teams[uit->faction].find(uit->playerInfo.partyId);
    if (it == teams[uit->faction].end())
      teams[uit->faction][uit->playerInfo.partyId] = Party();

    teams[uit->faction][uit->playerInfo.partyId].team =  uit->faction;
    teams[uit->faction][uit->playerInfo.partyId].users.push_back(uit->playerInfo.auid);
    //localLog(logStream, NLogg::LEVEL_DEBUG).Trace("FillExtraData: clientID %d, partyId %d, team %s, users_size %d ",_clientId, uit->playerInfo.partyId, lobby::ETeam::ToString(uit->faction),
    //  teams[uit->faction][uit->playerInfo.partyId].users.size());

  }


  lobby::ETeam::Enum enemyTeam  = lobby::ETeam::Invert(team);
  int enemyPartySize = 1;
  PartyData::const_iterator it = teams[enemyTeam].begin();
  for (;it != teams[enemyTeam].end(); ++it)
  {
    int sz = it->second.users.size();
    if ( (it->first != 0) && (enemyPartySize < sz) )
      enemyPartySize = sz;

  }
  if (partyId == 0)
    extra.partySize = 1;
  else
    extra.partySize = teams[team][partyId].users.size();

  extra.enemyPartySize = enemyPartySize;
  //localLog(logStream, NLogg::LEVEL_DEBUG).Trace("FillExtraData: partySize %d, enemyPartySize %d",extra.partySize, extra.enemyPartySize );
  return;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::FillPostGameData(lobby::EGameResult::Enum _gameResult, const StatisticService::RPC::SessionClientResults & _gameFinishInfo, const nstl::vector<SClientStatistics> & _clientsStatistics, uint _totalSeconds)
{
  postGameData.gameResult = _gameResult;
  postGameData.victoriousFaction = (lobby::ETeam::Enum)_gameFinishInfo.sideWon;
  postGameData.totalSeconds = _totalSeconds;
  postGameData.users.resize( preGameData.users.size() );

  for ( int i = 0; i < preGameData.users.size(); ++i )
  {
    const roll::SPreGamePerUserData & userSrc = preGameData.users[i];

    roll::SPostGamePerUserData & userDest = postGameData.users[i];

    userDest.clientId = userSrc.clientId;

    bool found = false;
    for ( int j = 0; j < _clientsStatistics.size(); ++j )
    {
      if ( _clientsStatistics[j].clientId == userSrc.clientId )
      {
        found = true;
        userDest.statistics = _clientsStatistics[j];
        break;
      }
    }

    if (!found)
    {
      localLog(logStream, NLogg::LEVEL_ERROR).Trace(
        "GameServer: FillPostGameData: Client statistics not found (sid=%016x cid=%d)", serverId, userSrc.clientId);
    }


    found = false;
    for ( int j = 0; j < _gameFinishInfo.players.size(); ++j )
    {
      if ( _gameFinishInfo.players[j].userid == userSrc.clientId )
      {
        found = true;
        userDest.scoring = _gameFinishInfo.players[j].scoring;
        userDest.extra = _gameFinishInfo.players[j].extra;

        FillExtraData(userDest.extra,preGameData.users,userSrc.clientId);
        //userDest.extra.isGuildFight = preGameData.sessionType == lobby::ETypeOfSession::SESSIONTYPE_GUILDBATTLE;
        
        break;
      }
    }

    if (!found)
    {
      localLog(logStream, NLogg::LEVEL_ERROR).Trace(
        "GameServer: FillPostGameData: Client statistics data not found (sid=%016x cid=%d)", serverId, userSrc.clientId);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::Step()
{
  threading::MutexLock lock(awardsLock);

  if (!isInterfaceRequested)
  {
    StrongMT<rpc::IfaceRequester<roll::RIBalancer> > locked = rollBalancer.Lock();

    if (locked && locked->isopen())
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Requesting roll interface (sid=%016x)", serverId);

      locked->iface()->AllocateInstance( this, &AwardsRequester::OnInstanceAllocation );
      isInterfaceRequested = true;
      currentTimer = retryTimer;
    }
  }
  else if (currentTimer > 0)
  {
    --currentTimer;
    if (!currentTimer)
    {
      localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
        "GameServer: Retry roll due to time out (sid=%016x retryTimer=%d)", serverId, retryTimer);
      isInterfaceRequested = false;
      clientCb = 0;
      rollInstance = 0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::OnRollResults( const TUserAwards & _awards )
{
  threading::MutexLock lock(awardsLock);

  localLog(logStream, NLogg::LEVEL_DEBUG).Trace(
    "GameServer: Awards roll received for %d users (sid=%016x)", _awards.size(), serverId);

  awards = _awards;
  isAwardsReceived = true;
  clientCb = 0;
  rollInstance = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::OnRollFailed()
{
  threading::MutexLock lock(awardsLock);

  localLog(logStream, NLogg::LEVEL_WARNING).Trace("GameServer: Awards roll failed (sid=%016x)", serverId);

  isInterfaceRequested = false;
  clientCb = 0;
  rollInstance = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AwardsRequester::OnInstanceAllocation( roll::RIInstance * inst )
{
  threading::MutexLock lock(awardsLock);

  if (inst)
  {
    localLog(logStream, NLogg::LEVEL_DEBUG).Trace("GameServer: Requesting awards roll (sid=%016x)", serverId);

    rollInstance = inst;

    clientCb = new RollClientCb( this );
    rollInstance->Roll( clientCb, preGameData, postGameData );
  }
  else
  {
    localLog(logStream, NLogg::LEVEL_WARNING).Trace("GameServer: Null roll interface received (sid=%016x)", serverId);
    isInterfaceRequested = false;
  }
}

} // namespace Peered
