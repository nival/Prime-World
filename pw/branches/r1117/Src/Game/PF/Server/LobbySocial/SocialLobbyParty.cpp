#include "stdafx.h"
#include "SocialLobbyParty.h"
#include "SocialLobbyUserContext.h"
#include "SocialLobbyCtrl.h"
#include "SocialLobbyRemoteMm.h"
#include "SocialLobbyConfig.h"
#include "SocialLobbyLog.h"
#include "SocialLobbyMaps.h"
#include "Db/DBServer.auto.h"
#include "Server/LiveMMaking/ILiveMMaking.h"
#include "System/InlineProfiler.h"


NI_DEFINE_REFCOUNT( socialLobby::Party );

namespace socialLobby
{

Party::Party( Config * _cfg, timer::Time _now, UserContext * _firstMember, IControl * _control ) :
config( _cfg ),
id( _firstMember->Data().partyId ),
creationTime( _now ),
mapId( _firstMember->Data().map ),
commonData( _firstMember->Data().faction, _firstMember->Data().clientRevision ),
lineup( _firstMember->Data().partyLineup ),
enemyLineup( _firstMember->Data().enemyPartyLineup ),
state( EPartyState::WaitingMembers ),
control( _control ),
mmReqId( 0 )
{
  NI_ASSERT( !mapId.empty(), "" );

  int sz = _firstMember->Data().partyLineup.size();
  members.reserve( Max( 1, sz ) );

  members.push_back( _firstMember );

  SOCLOBBY_LOG_MSG( "Party created. pty_id=%d, uid=%s", id, _firstMember->FmtId() );
}


template<class T>
inline bool VectorsEquals( const vector<T> & _a, const vector<T> & _b )
{
  if ( _a.size() != _b.size() )
    return false;

  for ( int i = 0; i < _a.size(); ++i )
  {
    bool found = false;
    for ( int j = 0; !found && j < _b.size(); ++j )
      if ( _a[i] == _b[j] )
        found = true;
    if ( !found )
      return false;
  }

  return true;
}



int Party::PlayersNumber() const
{
  if ( !id || lineup.empty() )
    return 1;
  return lineup.size() + enemyLineup.size();
}



bool Party::HasMember( UserContext * _ctx ) const
{
  for ( int i = 0; i < members.size(); ++i )
    if ( members[i] == _ctx )
      return true;
  return false;
}



inline bool BoolEq( bool a, bool b ) { return ( a && b ) || ( !a && !b ); }

bool Party::Add( UserContext * _ctx )
{
  NI_PROFILE_FUNCTION;

  if ( state != EPartyState::WaitingMembers ) {
    SOCLOBBY_LOG_ERR( "Cant add member to party in wrong state. pty_id=%d, uid=%s, state=%d", id, _ctx->FmtId(), (int)state );
    return false;
  }

  //Let's check party consistency...
  const char * ctxid = _ctx->FmtId();

  const SMatchmakingRequest & data = _ctx->Data();

  if ( data.partyId != id ) {
    SOCLOBBY_LOG_ERR( "Inconsistent party id. pty_id=%d, pty_id=%d, uid=%s", data.partyId, id, ctxid );
    return false;
  }

  if ( data.map != mapId ) {
    SOCLOBBY_LOG_ERR( "Inconsistent party map. pty_id=%d, map=%s, map=%s, uid=%s", id, data.map, mapId, ctxid );
    return false;
  }

  if ( data.clientRevision && commonData.clientRevision && ( data.clientRevision != commonData.clientRevision ) ) {
    SOCLOBBY_LOG_ERR( "Inconsistent party client revision. pty_id=%d, revision=%d, revision=%d, uid=%s", id, data.clientRevision, commonData.clientRevision, ctxid );
    return false;
  }
  /*
  if ( !BoolEq( data.readyToManoeuvre, commonData.readyToManoeuvre ) ) {
    SOCLOBBY_LOG_ERR( "Inconsistent party manoeuvres flag. pty_id=%d, uid=%s", id, ctxid );
    return false;
  }*/

  if ( !VectorsEquals( data.partyLineup, lineup ) || !VectorsEquals( data.enemyPartyLineup, enemyLineup ) )
  {
    SOCLOBBY_LOG_ERR( "Inconsistent party line-up. pty_id=%d, uid=%s", id, ctxid );
    return false;
  }

  if ( !commonData.clientRevision && data.clientRevision )
    commonData.clientRevision = data.clientRevision;

  if ( !UpdateLineup( _ctx ) )
    return false;

  members.push_back( _ctx );

  SOCLOBBY_LOG_MSG( "Member added to party. pty_id=%d, uid=%s", id, ctxid );
  return true;
}



bool Party::UpdateLineup( UserContext * _ctx )
{
  if ( !id || lineup.empty() )
    return true;

  //TEMP: look for party-members by pvxUserId and NOT by uid
  bool found[2] = {
    nstl::find( lineup.begin(), lineup.end(), (TUId)_ctx->Data().userIdPvx ) != lineup.end(),
    nstl::find( enemyLineup.begin(), enemyLineup.end(), (TUId)_ctx->Data().userIdPvx ) != enemyLineup.end()
  };

  if ( !found[0] && !found[1] )
  {
    SOCLOBBY_LOG_ERR( "User is NOT in his party line-up. pty_id=%d, uid=%s", id, _ctx->FmtId() );
    return false;
  }

  return true;
}



bool Party::Completed() const
{
  NI_VERIFY( state == EPartyState::WaitingMembers, "", return false );

  int livecount = 0;
  for ( int i = 0; i < members.size(); ++i )
    if ( members[i] )
      ++livecount;

  int count = PlayersNumber();
  NI_ASSERT( livecount <= count, "" );

  return livecount >= count;
}



inline mmaking::SRequestMember SocialMember2Mm( const SMatchmakingRequest & data )
{
  int loseStreak = UserContext::CountLoseStreak( data.winLoseHistory );

  return mmaking::SRequestMember(
      data.userIdPvx,
      data.heroId.c_str(),
      data.zzimaSex,
      data.basket,
      data.guardRating,
      data.playerRating,
      data.heroRating,
      data.force,
      data.geoInfo,
      loseStreak,
      data.totalWins,
      data.fameLevel,
      data.original_faction,
      data.totalLeaves
      );
}



bool Party::PutRequestInLine( mmaking::TRequestUId _mmReqId, timer::Time _addWaitTime, bool _canBeEmpty )
{
  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return false );

  Strong<RemoteMmLogic> logicStrong = lockedControl->GetMmLogic( mapId );
  if ( !logicStrong ) {
    SOCLOBBY_LOG_ERR( "MM logic not found! pty_id=%d, map=%s, reqId=%d", id, mapId, _mmReqId );
    return false;
  }

  NI_PROFILE_HEAVY_FUNCTION;

  if ( ( state != EPartyState::WaitingMembers ) && ( state != EPartyState::InOperation ) ) {
    SOCLOBBY_LOG_ERR( "Wrong party state. pty_id=%d, reqId=%d, state=%d", id, _mmReqId, (int)state );
    return false;
  }

  vector<mmaking::SRequestMember> mmMembers;
  mmMembers.reserve( lineup.size() );
  for ( int i = 0; i < members.size(); ++i )
  {
    UserContext * partyMemb = members[i];
    if ( !partyMemb )
      continue;

    mmMembers.push_back( SocialMember2Mm( partyMemb->Data() ) );
  }

  if ( mmMembers.size() < PlayersNumber() )
  {
    if ( !_canBeEmpty )
      SOCLOBBY_LOG_ERR( "Broken party line-up, pty_id=%d", id );
    return false;
  }

  if ( _mmReqId )
  {
    if ( mmReqId )
      SOCLOBBY_LOG_ERR( "Inconsistent mm request id. pty_id=%d", id );
    mmReqId = _mmReqId;
  }
  else
    if ( !mmReqId )
      SOCLOBBY_LOG_ERR( "Inconsistent mm request id. pty_id=%d", id );
  
  logicStrong->Interface()->AddMmRequest( mmReqId, commonData, mmMembers, _addWaitTime );

  logic = logicStrong;

  state = EPartyState::InLine;

  for ( int i = 0; i < members.size(); ++i )
    if ( UserContext * memb = members[i] )
      memb->ChangeStatus( ERequestStatus::InLine );
  return true;
}



void Party::RemoveRequestFromLine()
{
  NI_VERIFY( state == EPartyState::InLine, "", return );
  NI_ASSERT( mmReqId, "" );

  Strong<RemoteMmLogic> logicStrong = logic;
  
  if ( logicStrong )
    logicStrong->Interface()->RemoveMmRequest( mmReqId );
  else
    SOCLOBBY_LOG_ERR( "Remove request: MM logic is not valid! map=%s, reqId=%d, pty_id=%d", mapId, mmReqId, id );

  state = EPartyState::InOperation;
}



void Party::ResetRequestInLine()
{
  NI_VERIFY( state == EPartyState::InLine, "", return );
  state = EPartyState::InOperation;
}



void Party::ChangeAllMembersStatus( ERequestStatus::Enum _newStatus )
{
  for ( int i = 0; i < members.size(); ++i )
  {
    UserContext * ctx = members[i];
    if ( !ctx )
      continue;
    ctx->ChangeStatus( _newStatus );
  }
}



void Party::RemoveAllRequests( bool _logStatistics, UserContext * _exceptThis )
{
  StrongMT<IControl> lockedControl = control.Lock();
  NI_VERIFY( lockedControl, "", return );

  for ( int mi = 0; mi < members.size(); ++mi )
  {
    Strong<UserContext> memb = members[mi];
    if ( !memb || ( memb == _exceptThis ) )
      continue;
    lockedControl->RemoveUserContext( memb, _logStatistics );
  }
}



bool Party::SetupCustomGame( mmaking::SGame & _mmData, const NDb::AdvMapDescription * _map )
{
  if ( ( lineup.size() > _map->teamSize ) || ( enemyLineup.size() > _map->teamSize ) )
  {
    SOCLOBBY_LOG_MSG( "Wrong custom game party size. pty_id=%d, team_size=%d, pty_size=%d, pty_size=%d", id, _map->teamSize, lineup.size(), enemyLineup.size() );
    return false;
  }

  const string clientCompatibleMapId = _map->GetDBID().GetFormatted();

  _mmData.mapType = _map->mapType;
  _mmData.mapId = clientCompatibleMapId;
  _mmData.manoeuvresFaction = lobby::ETeam::None; //To be filled later
  _mmData.basket = mmaking::EBasket::Normal;
  _mmData.debugGameType = mmaking::EDebugGameType::FullParty;
  _mmData.humans.resize( 2 );

  for ( int i = 0; i < 2; ++i ) {
    _mmData.humans[i].common = commonData;
    _mmData.humans[i].common.team = lobby::ETeam::None;
  }

  const vector<TUId> *lineups[2] = { &lineup, &enemyLineup };

  for ( int i = 0; i < members.size(); ++i )
  {
    UserContext * memb = members[i];
    NI_VERIFY( memb, "", return false );

    lobby::ETeam::Enum fact = memb->Data().faction;

    for ( int t = 0; t < 2; ++t )
      if ( nstl::find( lineups[t]->begin(), lineups[t]->end(), (TUId)memb->Data().userIdPvx ) != lineups[t]->end() )
      {
        mmaking::SGameParty & partyData = _mmData.humans[t];

        if ( partyData.common.team == lobby::ETeam::None )
          partyData.common.team = fact;
        else if ( partyData.common.team != fact )
        {
          SOCLOBBY_LOG_ERR( "Wrong user party lineup and faction. pty_id=%d, uid=%s", id, memb->FmtId() );
          return false;
        }

        partyData.members.push_back( SocialMember2Mm( memb->Data() ) );
        break;
      }
  }

  if ( ( _mmData.humans[0].common.team == lobby::ETeam::None ) || ( _mmData.humans[1].common.team == lobby::ETeam::None ) )
  {
    SOCLOBBY_LOG_ERR( "Wrong party factions. pty_id=%d", id );
    return false;
  }

  if ( _mmData.humans[0].common.team == _mmData.humans[1].common.team )
  {
    SOCLOBBY_LOG_MSG( "Custom maneuvers detected. pty_id=%d", id );
    _mmData.manoeuvresFaction = _mmData.humans[0].common.team;
    _mmData.humans[1].common.team = lobby::ETeam::Invert( _mmData.humans[1].common.team );
  }

  state = EPartyState::InOperation;

  return true;
}



bool Party::Poll( timer::Time _now )
{
  if ( state == EPartyState::WaitingMembers )
  {
    if ( _now > creationTime + config->partyMembersTimeout )
    {
      state = EPartyState::Incomplete;
      ChangeAllMembersStatus( ERequestStatus::IncompleteParty );
      return false;
    }
  }

  return true;
}

} //namespace socialLobby
