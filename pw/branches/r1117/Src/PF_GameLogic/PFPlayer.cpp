#include "stdafx.h"

#include "PFBaseUnit.h"
#include "PFHero.h"
#include "HeroActions.h"
#include "PFPlayer.h"
#include "PFAbilityData.h"
#include "PFAIWorld.h"
#include "PFBaseUnitStates.h"

#include "IAdventureScreen.h"

#include "PlayerBehaviourTracker.h"

namespace NWorld
{

NAMEMAP_BEGIN( PFPlayer )
  NAMEMAP_FUNC_RO ( playerName, &PFPlayer::GetPlayerName )
  NAMEMAP_CUSTOM_SUBMAP( hero, pHero, IsValid(pHero) )
NAMEMAP_END

PFPlayer::PFPlayer( PFWorld * _world,
                    int _playerID,
                    NCore::ETeam::Enum _teamID,
                    NCore::ETeam::Enum _originalTeamID,
                    int _userID,
                    NCore::ESex::Enum _zzimaSex,
                    bool _aiForLeaversEnabled,
                    int _aiForLeaversThreshold,
                    const bool chatMuted,
                    const bool enableBehaviourTracking)
: PFWorldObjectBase( _world, 1 )
, playerID( _playerID )
, teamID( _teamID )
, originalTeamID( _originalTeamID )
, userID( _userID )
, zzimaSex( _zzimaSex )
, isLocal( false )
, isPlaying( true )
, isActive( true )
, aiForLeaversEnabled( _aiForLeaversEnabled )
, aiForLeaversThreshold( _aiForLeaversThreshold )
, aiStartTimer( 0 )
, disconnected(false)
, leaver(false)
, timeWhenDisconnected(0)
, behaviourTracker()
, chatMuted(chatMuted)
{
  behaviourTracker = new PlayerBehaviourTracker(_world, this, enableBehaviourTracking);
}

PFPlayer::PFPlayer()
: chatMuted(false)
{

}

void PFPlayer::AttachHero(PFBaseHero* pNewHero)
{
  if( IsValid(pHero) )
    pHero->DetachFromPlayer();

  pHero = pNewHero;
}

void PFPlayer::DetachHero()
{
  pHero = NULL;
}

void PFPlayer::SetIsPlaying(bool _isPlaying)
{
  if (isPlaying != _isPlaying)
  {
    isPlaying = _isPlaying;
    if (aiForLeaversEnabled)
    {
      if (isPlaying)
      {
        if (aiStartTimer > 0)
          aiStartTimer = 0;
        else
          GetWorld()->RemoveAI( GetHero() );
      }
      else
      {
        if (aiForLeaversThreshold > 0)
          aiStartTimer = aiForLeaversThreshold;
        else
          GetWorld()->AddAI( GetHero(), GetPlayerID() % 3 );
      }
    }
  }
}

bool PFPlayer::Step(float dtInSeconds)
{
  if (aiStartTimer > 0)
  {
    --aiStartTimer;
    if (aiStartTimer == 0)
    {
      GetWorld()->AddAI( GetHero(), GetPlayerID() % 3 );
    }
  }

  if (!IsPlaying() && (!aiForLeaversEnabled || aiStartTimer > 0) && IsValid(pHero) && pHero->CanMove())
  {
    const CVec2 & spawnPos = pHero->GetSpawnPosition().AsVec2D();
    if (!pHero->IsPositionInRange(spawnPos, 1.0f))
      pHero->Move(spawnPos);
  }

  // NOTE: NUM_TASK
  // в рамках NUM_TASK было внесено исправление в PlayerBehaviourTracker. с тех пор он не является "настоящим" WorldObject'ом, соответственно,
  // его Step() не вызывается автоматически
  if (IsValid(behaviourTracker))
    behaviourTracker->Step(dtInSeconds);

  return PFWorldObjectBase::Step(dtInSeconds);
}

void PFPlayer::OnDestroyContents()
{
  if (IsValid(pHero))
    pHero->DetachFromPlayer();

  // call parent
  PF_Core::WorldObjectBase::OnDestroyContents();
}

const wstring& PFPlayer::GetPlayerName() const
{
  return GetWorld()->GetIAdventureScreen()->GetPlayerName( playerID );
}

NDb::EFaction TeamIdToFaction( NCore::ETeam::Enum teamId )
{
  switch(teamId)
  {
    case NCore::ETeam::Team1:
      return NDb::FACTION_FREEZE;
    case NCore::ETeam::Team2:
      return NDb::FACTION_BURN;
    default:
      return NDb::FACTION_NEUTRAL;
  }
}


NDb::EFaction GetFaction(NWorld::PFPlayer const* pPlayer)
{
  if ( pPlayer ) 
    return TeamIdToFaction( pPlayer->GetTeamID() );

  return NDb::FACTION_NEUTRAL;
}


NDb::EFaction GetOriginalFaction(NWorld::PFPlayer const* pPlayer)
{
  if ( pPlayer ) 
    return TeamIdToFaction( pPlayer->GetOriginalTeamID() );

  return NDb::FACTION_NEUTRAL;
}

void PFPlayer::SetDisconnected(const bool _disconnected, const bool _leaver)
{
  if (disconnected != _disconnected)
  {
    disconnected = _disconnected;

    if (disconnected)
      timeWhenDisconnected = timer::Now();
  }

  // NOTE: игрок не может перестать быть ливером
  if (_leaver)
    leaver = true;
}

timer::Time const PFPlayer::GetTimeElapsedSinceDisconnection() const
{
  if (disconnected)
  {
    const timer::Time time = timer::Now();

    if (time > timeWhenDisconnected)
      return (time - timeWhenDisconnected);
  }

  return timer::Time(0);
}


} // namespace NWorld


REGISTER_WORLD_OBJECT_NM(PFPlayer, NWorld);
