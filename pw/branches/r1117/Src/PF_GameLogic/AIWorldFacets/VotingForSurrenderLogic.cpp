#include "stdafx.h"
#include "VotingForSurrenderLogic.h"
#include "./../PFHero.h"
#include "Core/WorldCommand.h"
#include "../PFAIContainer.h"
#include "../PFWorld.h"
#include "../PFAIWorld.h"
#include "../PFMainBuilding.h"
#include "../WarFog.h"
#include "../TileMap.h"
#include "../PFClientVotingForSurrender.h"
#include "../Scripts/FuncCallMacroses.h"

namespace NWorld
{
namespace AIWorldFacets
{

inline bool CheckPlayer( const NWorld::PFPlayer* pPlayer, int userId )
{
  if ( pPlayer )
    if ( pPlayer->GetUserID() == userId )
      return true;

  NI_ALWAYS_ASSERT(NStr::StrFmt("Wrong player received in command (uid=%d)", userId));
  return false;
}

DEFINE_1_PARAM_CMD_CHECK ( 0x67885400,  CmdVotingForSurrenderStart,  CPtr<PFPlayer>, pPlayer );
DEFINE_2_PARAM_CMD_CHECK ( 0x67885401,  CmdVotingForSurrenderMakeDecision,  CPtr<PFPlayer>, pPlayer, bool, vote );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CmdVotingForSurrenderStart::CanExecute() const
{
  return CheckPlayer( pPlayer, GetId() );
}

void CmdVotingForSurrenderStart::Execute( NCore::IWorldBase* pWorld )
{
  PFWorld * const pPFWorld = dynamic_cast<PFWorld*>( pWorld );
  
  if( pPFWorld )
    pPFWorld->GetAIWorld()->VotingForSurrenderStart(pPlayer);
}

bool CmdVotingForSurrenderMakeDecision::CanExecute() const
{
  return CheckPlayer( pPlayer, GetId() );
}

void CmdVotingForSurrenderMakeDecision::Execute( NCore::IWorldBase* pWorld )
{
  PFWorld * const pPFWorld = dynamic_cast<PFWorld*>( pWorld );
  
  if( pPFWorld )
    pPFWorld->GetAIWorld()->VotingForSurrenderMakeDecision(pPlayer, vote); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NAMEMAP_BEGIN(VotingForSurrenderNameMap)
  NAMEMAP_INCLUDE( pThis )
  NAMEMAP_CUSTOM_SUBMAP( player, pPlayer, IsValid(pPlayer) )
  NAMEMAP_VAR_ALIAS_RO( votesForSurrender, stat.votesForSurrender )
  NAMEMAP_VAR_ALIAS_RO( votesForFight, stat.votesForFight )
NAMEMAP_END
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NAMEMAP_BEGIN(SimpleTimerWitnNameMap)
  NAMEMAP_FUNC_RO(timeToAlarm, &SimpleTimer::GetTimeToAlarm)  
  NAMEMAP_FUNC_RO(timeToAlarmMinutesFloor, &SimpleTimerWitnNameMap::GetTimeToAlarmMinutesFloor )
  NAMEMAP_FUNC_RO(timeToAlarmMinutesCeil, &SimpleTimerWitnNameMap::GetTimeToAlarmMinutesCeil )
  NAMEMAP_FUNC_RO(timeToAlarmSecOnlyFloor, &SimpleTimerWitnNameMap::GetTimeToAlarmSecOnlyFloor )
NAMEMAP_END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NAMEMAP_BEGIN(VotingForSurrenderLogic)
  NAMEMAP_CUSTOM_SUBMAP( cooldown, &votingCooldown, true )
  NAMEMAP_FUNC_RO(teamName, &VotingForSurrenderLogic::GetTeamName)  
NAMEMAP_END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class VotingForSurender
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VotingForSurrenderLogic::VotingForSurrenderLogic()
{
  Init( NCore::ETeam::None, new NDb::VotingForSurrender(), new NDb::VotingForSurrenderPerMission() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
VotingForSurrenderLogic::VotingForSurrenderLogic( 
    PFWorld* pWorld, NCore::ETeam::Enum team, 
    NDb::Ptr<NDb::VotingForSurrender> pDb
):  PFWorldObjectBase(pWorld, 1)
{
  Init( team, pDb, 0 );
  CreateClientObject<NGameX::ClientVotingForSurrender>(pDb);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
void VotingForSurrenderLogic::InitPerMissionData( NDb::Ptr<NDb::VotingForSurrenderPerMission> pDbMission )
{
  Init( team, pDb, pDbMission );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
void VotingForSurrenderLogic::Init( NCore::ETeam::Enum team_, NDb::Ptr<NDb::VotingForSurrender> pDb_, NDb::Ptr<NDb::VotingForSurrenderPerMission> pDbMission_ )
{
  surrenderVotes = 0;
  
  pDb = pDb_;
  NI_ASSERT( IsValid(pDb), "NDb::VotingForSurrender is empty" );
  
  pDbMission = IsValid(pDbMission_) ? pDbMission_ : pDb->defaultMissionSettings;
  NI_ASSERT( IsValid(pDbMission), "NDb::VotingForSurrenderPerMission is empty" );
  
  team = team_;
  state.Clear();  
  beforeSurrender.Reset();
  votingDuration.Reset();
  votingCooldown.Start( pDbMission->cooldownAfterStart );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
STARFORCE_FORCE_INLINE void VotingForSurrenderLogic::StopVoting()
{
  Statistics stat;
  CalcStatistics( state, stat );
  ResetVoting();
  
  DebugTrace( "Command decline surrender" );
  SendUserMsg( NDb::VFSUSERMESSAGES_COMMANDDECLINESURRENDER, NameMap(this, stat) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        
void VotingForSurrenderLogic::Start( CPtr<PFPlayer> pPlayer )
{
  if( !IsValid(pPlayer) )
    return;

  //√олосование может быть только одно
  if( state.IsVotingInProgress() )
  {
    DebugTrace( "Can't initiate voting because another one in progress" );
    SendUserMsg( NDb::VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS, NameMap(this, pPlayer) ); 
    return;
  }
   
  //Ћюбой игрок может инициировать голосование о сдаче в сессии только 
  //начина€ с N-й минуты игры
  //” голосовани€ есть  ƒ (N секунд) - нельз€ голосовать сразу же повторно 
  //после отказа в первом голосовании.
  if( votingCooldown.IsInProgress() )
  {
    DebugTrace( "Can't initiate voting before N minutes of game or less than N seconds after prevision one" );
    SendUserMsg( NDb::VFSUSERMESSAGES_CANTSTARTCOOLDOWN, NameMap(this, pPlayer) );
    return;
  }
  
  DebugTrace( "Player [Name] has started voting" );
  SendUserMsg( NDb::VFSUSERMESSAGES_PLAYERSTARTVOTING, NameMap(this, pPlayer) );
   
  votingDuration.Start( pDb->votingDuration );
  
  NI_ASSERT( state.result.find(pPlayer->GetPlayerID()) == state.result.end(), "Player has already voted" );
  state.result[pPlayer->GetPlayerID()] = VotedForSurrender; 
  
  CheckForVotingComplete(); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::MakeDecision( CPtr<PFPlayer> pPlayer, VoteResult result )
{
  if( !IsValid(pPlayer) )
    return;
    
  //√олосование должно идти
  if( !state.IsVotingInProgress() )
  {
    DebugTrace( "Can't make decision because voting is not in progress" );
    SendUserMsg( NDb::VFSUSERMESSAGES_CANTMAKEDECISIONISNTINPROGRESS, NameMap(this, pPlayer) );
    return;
  }
  
  const PlayersVoteResult::iterator it = state.result.find( pPlayer->GetPlayerID() );
  
  if( it != state.result.end() )
  {
    DebugTrace( "Player has already voted" );
    SendUserMsg( NDb::VFSUSERMESSAGES_CANTMAKEDECISIONALREADYVOTED, NameMap(this, pPlayer) );
    return;
  }
  
  state.result.insert( PlayersVoteResult::value_type(pPlayer->GetPlayerID(), result) );
  
  CheckForVotingComplete();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VotingForSurrenderLogic::Step( float dtInSeconds )
{
  votingCooldown.Tick( dtInSeconds );
  
  if( state.IsVotingInProgress() )
  {
    //»гроки могут вывалитс€ в любой момент, поэтому провер€ем регул€рно
    if ( UpdateLeavers() )
      CheckForVotingComplete(); 
      
    if ( beforeSurrender.Tick(dtInSeconds) )
      StartSurrender();
    
    if ( !beforeSurrender.IsInProgress() && votingDuration.Tick(dtInSeconds) )
      StopVoting();  
  }
  
  return PFWorldObjectBase::Step(dtInSeconds);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool VotingForSurrenderLogic::UpdateLeavers()
{
  bool hasChanges = false;

  for( int i = 0; i < GetWorld()->GetPlayersCount(); ++i )
  {
    const PFPlayer * const player = GetWorld()->GetPlayer(i);

    NI_ASSERT(!!player, "Invalid player");

    if (player->GetTeamID() != team)
      continue;

    if (player->IsBot() && TryVoteForBotPlayer(player))
      hasChanges = true;
    if (player->IsDisconnected() && TryVoteForDisconnectedPlayer(player))
      hasChanges = true;
  }

  return hasChanges;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::Abort()
{
  Init( team, pDb, pDbMission );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::ResetVoting()
{
  NI_ASSERT( state.IsVotingInProgress(), "" ); 
  NI_ASSERT( !beforeSurrender.IsInProgress(), "" );
  state.Clear();
  votingDuration.Reset();
  votingCooldown.Start( pDbMission->cooldownAfterPrevisionVoting );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::StartSurrender()
{
  Statistics stat;
  CalcStatistics( state, stat );

  surrenderVotes = stat.votesForSurrender;

  ResetVoting();
        
  //Ќачинаем процесс капитул€ции
  DebugTrace( "Command accept surrender" );
  SendUserMsg( NDb::VFSUSERMESSAGES_COMMANDACCEPTSURRENDER, NameMap(this, stat) );  
    
  //Ќаходим главное здание
  typedef vector<PFMainBuilding*> BldCnt;
  BldCnt cnt;
  
  FindMainBuildings( GetWorld(), TeamIdToFaction(team), cnt );
    
  //дл€ команды противника там открываетс€ варфог
  for( int i = 0; i < NDb::KnownEnum<NDb::EFaction>::sizeOf; ++i )
    if( i != TeamIdToFaction(team) )
        for( BldCnt::iterator it = cnt.begin(); it != cnt.end(); ++it )
        {
          const SVector position = GetWorld()->GetTileMap()->GetTile((*it)->GetPosition().AsVec2D());  
          GetWorld()->GetFogOfWar()->AddObject( position, i, pDb->warforOpenedRadius );  
        }

  // —начала вызываем скриптовую функцию OnSurrender (если она есть)
  PFScript* pLuaScript = GetWorld()->GetAIContainer()->GetLuaScript();
  CALL_LUA_FUNCTION_ARG1( pLuaScript, "OnPlayersSurrender", false, (int)TeamIdToFaction(team) );

  if ( !cnt.empty() )
  {
    //уничтожаетс€ √лавное «дание, со всеми взрывами и эффектами, как при обычном поражении.
    //камера переезжает к главному зданию сдавшейс€ команды
    for( BldCnt::iterator it = cnt.begin(); it != cnt.end(); ++it )
      (*it)->KillUnit(); 
  }
  else 
  {
    // ј если главного здани€ нет - просто проигрываем
    GetWorld()->OnGameFinished( TeamIdToFaction(team) );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const wstring &VotingForSurrenderLogic::GetTeamName() const
{
  return GetWorld()->GetAIWorld()->GetFactionName( TeamIdToFaction(team) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::SendUserMsg( NDb::VFSUserMessages msg, const NameMap &map ) const
{
  CALL_CLIENT_2ARGS( SendUserMsg, msg, map );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VotingForSurrenderLogic::Reset()
{
  PFWorldObjectBase::Reset();
  CreateClientObject<NGameX::ClientVotingForSurrender>(pDb);
}

bool VotingForSurrenderLogic::TryVoteForBotPlayer(const NWorld::PFPlayer* const player)
{
  NI_VERIFY(!!player, "Invalid player!", return false);

  const int playerId = player->GetPlayerID();
  const bool alreadyVoted = state.result.find(playerId) != state.result.end();

  if (alreadyVoted)
    return false;

  VoteResult& vote = state.result[playerId];

  vote = VotedForSurrender;

  return true;
}

bool VotingForSurrenderLogic::TryVoteForDisconnectedPlayer(const NWorld::PFPlayer* const player)
{
  NI_VERIFY(!!player, "Invalid player!", return false);

  const int playerId = player->GetPlayerID();
  const bool alreadyVoted = state.result.find(playerId) != state.result.end();

  float voteForFightThreshold = 0.f;

  if (IsValid(pDbMission))
    voteForFightThreshold = pDbMission->timeDisconnectedPlayersVoteForFight;
  if (!(voteForFightThreshold > 0.f))
    voteForFightThreshold = (3.f * 60.f);

  const bool surrender =
    (player->IsLeaver()) ||
    (player->GetTimeElapsedSinceDisconnection() > voteForFightThreshold);

  VoteResult& vote = state.result[playerId];

  if (alreadyVoted)
  {
    // нельз€ мен€ть, если уже голосовал за сдачу
    if (vote == VotedForSurrender)
      return false;

    if (surrender)
      vote = VotedForSurrender;
    else
      return false;
  }
  else
  {
    if (surrender)
      vote = VotedForSurrender;
    else
      vote = VotedForFight;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NCore::WorldCommand* VotingForSurrenderStartCommandCreate( CPtr<PFPlayer> pPlayer )
{
  return new CmdVotingForSurrenderStart( pPlayer );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NCore::WorldCommand* VotingForSurrenderMakeDecisionCommandCreate( CPtr<PFPlayer> pPlayer, bool vote )
{
  return new CmdVotingForSurrenderMakeDecision( pPlayer, vote );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma code_seg(push, "~")

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrenderLogic::CalcStatistics( const State &state, Statistics &stat ) const
{
  STARFORCE_STOPWATCH();

  //¬ычисл€ем общее количество игроков
  stat.playersCount = 0;

  for( int i = 0; i < GetWorld()->GetPlayersCount(); ++i )
  {
    const PFPlayer * const pPlayer = GetWorld()->GetPlayer(i);

    if( pPlayer->GetTeamID() == team ) 
      ++stat.playersCount;
  } 

  //¬ычисл€ем количество игроков проголосовавших за капитул€цию и против
  stat.votesForSurrender = 0;
  stat.votesForFight = 0;
  PlayersVoteResult::const_iterator it;

  for( it = state.result.begin(); it != state.result.end(); ++it )
    if( it->second == VotedForSurrender )
      ++stat.votesForSurrender;
    else if( it->second == VotedForFight )
      ++stat.votesForFight;

  NI_ASSERT( stat.votesForSurrender + stat.votesForFight <= stat.playersCount, "" ); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrenderLogic::CheckForVotingComplete()
{
  STARFORCE_STOPWATCH();

  struct Proxy
  {
    VotingForSurrenderLogic *pThis;

    static void Call( const void *pProxyRaw )
    {
      const Proxy * const pProxy = static_cast<const Proxy *>(pProxyRaw);     
      pProxy->pThis->CheckForVotingCompleteImpl(); 
    } 
  };

  Proxy proxy; 
  proxy.pThis = this;

  Protection::CallFunctionInProtectedSpace( &Proxy::Call, &proxy );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrenderLogic::CheckForVotingCompleteImpl()
{
  STARFORCE_STOPWATCH();

  NI_ASSERT( state.IsVotingInProgress(), "" );

  Statistics stat; 
  CalcStatistics( state, stat );

  //ћинимальное количество пользователей, которые могут проголосовать против при общем 
  //положительном итоге 
  const int maxUsersForFightIgnored = pDbMission->maxUsersForFightIgnored;

  //≈сли слишком много пользователей против, то голосование провалено
  if( stat.votesForFight > maxUsersForFightIgnored )
    StopVoting();
  //√олосование считаетс€ состо€вшимс€, если проголосовало "против" не более N игроков
  else if( stat.votesForSurrender + maxUsersForFightIgnored >= stat.playersCount )
  {
    //≈сли голосование состо€лось, то ставитс€ задержка в N секунд  - задержка нужна, 
    //чтобы успел "доголосовать" п€тый игрок, если его голос ничего не решает
    beforeSurrender.Start( pDb->delayBeforeVotingComplete );  
  }
}

#pragma code_seg(pop)

}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM( VotingForSurrenderLogic, NWorld::AIWorldFacets )
REGISTER_SAVELOAD_CLASS_NM( CmdVotingForSurrenderStart, NWorld::AIWorldFacets )
REGISTER_SAVELOAD_CLASS_NM( CmdVotingForSurrenderMakeDecision, NWorld::AIWorldFacets )