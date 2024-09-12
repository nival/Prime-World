#include "stdafx.h"
#include "EaselPriestess.h"

#include "DBEasel.h"

#include "Easel.h"
#include "EaselWorld.h"
#include "EaselCommands.h"

#include "MinigameSessionInterface.h"

#include "LuxDef.h"

#include "EaselConstants.h"

#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/PFStatistics.h"

#include "../PF_GameLogic/SessionEventType.h"

namespace PF_Minigames
{


EaselPriestess::EaselPriestess() :
IPriestessProxy(),
easelLevel( EaselConst::Get_EASEL_LEVEL_MIN() ),
delayedGold(0.0f)
{
}



EaselPriestess::~EaselPriestess()
{
  delayedGold = 0.0f; 
}



int EaselPriestess::GetGold() const
{
  if( IsValid( easel ) )
  {
    NI_VERIFY( IsValid( easel->GetWorldSessionInterface() ), "", return 0 );
    return easel->GetWorldSessionInterface()->GetGold();
  }

  return 0;
}



void EaselPriestess::AddGoldDelayed( int _gold )
{
  delayedGold += _gold;
}



void EaselPriestess::ApplyDelayedGold()
{
  AddGold( delayedGold );
  delayedGold = 0.0f;
}



bool EaselPriestess::CanBuyZZBoost() const
{
  if(IsValid(easel))
  {
    NI_VERIFY( IsValid( easel->GetWorldSessionInterface() ), "", return false; );
    return easel->GetWorldSessionInterface()->CanBuyZZBoost();
  }

  return false;
}




void EaselPriestess::SetRewardItemId( int id )
{
  if ( !IsValid( easel ) )
    return;

  NI_ASSERT( !rewardItem, "" );

  const NDb::DBEaselArtifacts & arts = easel->GetData()->artifacts;
  NI_VERIFY( ( id >= 0 ) && ( id < arts.artifact.size() ), "", return );

  rewardItem = arts.artifact[id];
}



int EaselPriestess::GetLevel()
{
  if(IsValid(easel))
  {
    NI_VERIFY( IsValid( easel->GetWorldSessionInterface() ), "", return -1 );
    return easel->GetWorldSessionInterface()->GetPriestessLevel();
  }

  return -1;
}



int EaselPriestess::GetMinigameLevel() const
{
  return easelLevel;
}



int EaselPriestess::SetMinigameLevel(int _level)
{
  if(_level >= EaselConst::Get_EASEL_LEVEL_MIN() && _level <= EaselConst::Get_EASEL_LEVEL_MAX())
  {
    easelLevel = _level;
    return easelLevel;
  }
  
  return easelLevel;
}















EaselPriestessLocal::EaselPriestessLocal( PF_Core::IWorld* _pWorld ) :
PF_Core::WorldObjectBase( _pWorld, false ),
allowFeatBoost( true ),
localGoldDebt( 0 )
{
}



int EaselPriestessLocal::GetGold() const
{
  int sessionGoldValue = EaselPriestess::GetGold();
  return sessionGoldValue + localGoldDebt;
}



void EaselPriestessLocal::AddGold( int value )
{
  localGoldDebt += value;

  DebugTrace( "Easel local debt add: %d (+%d)", localGoldDebt, value );
}



void EaselPriestessLocal::TakeGold( int value )
{
  localGoldDebt -= value;

  DebugTrace( "Easel local debt sub: %d (-%d)", localGoldDebt, value );
}



void EaselPriestessLocal::BalanceLocalGold( int delta )
{
  localGoldDebt += delta;

  DebugTrace( "Easel local debt balance: %d (%d)", localGoldDebt, delta );
}











EaselPriestessRemote::EaselPriestessRemote(  PF_Core::IWorld* _pWorld, IRemoteToLocalLink * _localLink ) :
PF_Core::WorldObjectBase( _pWorld, false ),
localLink( _localLink )
{
}



void EaselPriestessRemote::AddGold( int value )
{
  if( IsValid( easel ) )
  {
    NI_VERIFY( IsValid( easel->GetWorldSessionInterface() ), "", return );

    if ( IsValid( localLink ) )
      localLink->BalanceLocalGold( -value );

    IWorldSessionInterface * pReceiver = easel->GetWorldSessionInterface();

    if (pReceiver)
    {
      pReceiver->AddGold( value );
      pReceiver->LogMinigameEvent(SessionEventType::NaftaIncomeFromMinigame, value, 0);
    }
  }
}



void EaselPriestessRemote::TakeGold( int value )
{
  if( IsValid( easel ) )
  {
    NI_VERIFY( IsValid( easel->GetWorldSessionInterface() ), "", return );

    if ( IsValid( localLink ) )
      localLink->BalanceLocalGold( value );

    easel->GetWorldSessionInterface()->TakeGold( value );
  }
}



void EaselPriestessRemote::BuyZZBoost()
{
  if ( IsValid( easel ) )
    if ( IsValid( easel->GetWorldSessionInterface() ) )
    {
      easel->GetWorldSessionInterface()->BuyZZBoost();
    }
}



void EaselPriestessRemote::MinigameComplete()
{
  if ( IsValid( easel ) )
    if ( IsValid( easel->GetWorldSessionInterface() ) )
    {
      NDb::DBID gameId = easel->GetData()->GetDBID();
      int id = easel->GetWorldSessionInterface()->GetPriestessID();

      NWorld::PFStatistics * stat = easel->GetWorldSessionInterface()->GetSessionWorld()->GetStatistics();
      stat->MinigameComplete( gameId, id );
    }
}



void EaselPriestessRemote::MinigameLevelEnd( int levelIndex, EMinigameLevelStatus::Enum status )
{
  if ( IsValid( easel ) && IsValid( easel->GetWorldSessionInterface() ) )
  {
    NDb::DBID gameId = easel->GetData()->GetDBID();
    int playerId = easel->GetWorldSessionInterface()->GetPriestessID();
    int levelsCount = easel->GetData()->game->levels.size();

    NWorld::PFStatistics * stat = easel->GetWorldSessionInterface()->GetSessionWorld()->GetStatistics();
    stat->MinigameLevelEnded( gameId, playerId, levelIndex, status, (levelIndex == levelsCount - 1) );
  }
}

} //namespace PF_Minigames


BASIC_REGISTER_CLASS( PF_Minigames::IPriestessProxy)
BASIC_REGISTER_CLASS( PF_Minigames::EaselPriestess )
REGISTER_SAVELOAD_CLASS_NM( EaselPriestessLocal, PF_Minigames )
REGISTER_SAVELOAD_CLASS_NM( EaselPriestessRemote, PF_Minigames )
