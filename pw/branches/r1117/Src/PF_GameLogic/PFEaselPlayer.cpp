#include "stdafx.h"
#include "PFEaselPlayer.h"

#include "PFAbilityData.h"

#include "PFMinigamePlace.h"
#include "PFChest.h"
#include "PFStatistics.h"
#include "PFImpulsiveBuffs.h"
#include "PFPredefinedUnitVariables.h"

#ifndef VISUAL_CUTTED
#include "PFClientMinigamePlace.h"
#include "AdventureScreen.h"
#else //VISUAL_CUTTED
#include "../Game/PF/Audit/ClientStubs.h"
#endif //VISUAL_CUTTED

#include "SessionEventType.h"

#include "PlayerBehaviourTracking.h"

namespace 
{
  void HideUnit(NWorld::PFBaseUnit * unit, bool hide)
  {
    if (!IsValid(unit))
      return;

    unit->Hide( hide );
    unit->StopAttackingMe();

    if( hide )
      unit->EventHappened(NWorld::PFBaseUnitEvent(NDb::BASEUNITEVENT_ISOLATE));

  }
}

namespace NWorld
{


PFEaselPlayer::PFEaselPlayer(PFWorld* pWorld, const SpawnInfo &info, NDb::EUnitType unitType, NDb::EFaction faction, NDb::EFaction _originalFaction)
  : PFBaseHero(pWorld, info, unitType , faction, _originalFaction)
  , bidon(NDb::BIDONTYPE_NONE)
{  
  if( info.playerId >= 0 && IsValid(GetWorld()->GetMinigamesMain()))
  {
    bool allowLocalMinigame;
    if ( NGameX::AdventureScreen::Instance()->IsSpectator() )
    {
      allowLocalMinigame = false;
    }
    else
    {
      bool isReplay = NGameX::AdventureScreen::Instance()->IsInReplayMode();
      allowLocalMinigame = !isReplay && pWorld->GetPlayer(info.playerId)->IsLocal();
    }

    minigames = GetWorld()->GetMinigamesMain()->ProduceMinigamesObject( pWorld, this, allowLocalMinigame );
  }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::OnDestroyContents()
{
  minigames = 0;
 
  PFBaseHero::OnDestroyContents();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::ForceLeaveMinigame()
{
  if( IsValid( minigames ) )
    minigames->ForceLeaveMinigame();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFEaselPlayer::Step(float dtInSeconds)
{
  if ( IsValid( GetPlayer() ) )
  {
    if ( !GetPlayer()->IsPlaying() && IsIsolated() )
      OnLeaveMinigameCmd();
  }

  if( IsValid( minigames ) )
    minigames->OnStep( dtInSeconds );

  return PFBaseHero::Step(dtInSeconds);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::OnGameFinished( const NDb::EFaction failedFaction )
{
  PFBaseHero::OnGameFinished( failedFaction );

  if ( minigames )
    if ( IsValid( minigames->GetCurrentMinigame() ) )
      minigames->GetCurrentMinigame()->SessionFinished( failedFaction != GetFaction() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::OnBeforeClose()
{
  // If we've got here (exit via menu, Alt+F4, etc.) and still have minigame - log exit
  if ( minigames )
    if ( IsValid( minigames->GetCurrentMinigame() ) )
    {
      LogMinigameEvent(SessionEventType::MG2Exit, 0, 0);
      MinigameEvent(NDb::BASEUNITEVENT_MINIGAMEEXIT);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::DropCooldowns( DropCooldownParams const& dropCooldownParams )
{
  PFBaseHero::DropCooldowns( dropCooldownParams );

  if ( minigames )
    if ( IsValid( minigames->GetCurrentMinigame() ) )
      minigames->GetCurrentMinigame()->CheatDropCooldowns();
}



//////////////////////////////////////////////////////////////////////////
void PFEaselPlayer::Isolate( bool isolate )
{
  if( isolated == isolate )
    return;

  isolated = isolate;

  HideUnit(this, isolate);

  struct Func : public ISummonAction, public NonCopyable
  {
    bool hide;
    Func(bool _hide): hide(_hide) {}
    virtual void operator()(PFBaseUnit * pUnit)
    {
      HideUnit(pUnit, hide);
    }
  } hider(isolate);

  ForAllSummons(hider, NDb::SUMMONTYPE_PRIMARY);
  ForAllSummons(hider, NDb::SUMMONTYPE_PET);
}


//////////////////////////////////////////////////////////////////////////
bool PFEaselPlayer::StartMinigame( PFMinigamePlace * pPlace )
{
  if ( !pPlace->CanBeUsedBy( this ) )
    return false;

  if( pPlace->GetFaction() != GetFaction() )
    return false;

  if( pPlace->CurrentEaselPlayer() )
    return false;

  bool isMount = IsMount();
  if ( isMount )
  {
    if ( PFBaseHero* hero = dynamic_cast<PFBaseHero*>(GetAttachUnit().GetPtr()) )
    {
      hero->EventHappened(NWorld::PFBaseUnitMinigameEvent(NDb::BASEUNITEVENT_MINIGAMESTARTED, this));
    }
  }

  NI_ASSERT( pPlace, "Null minigame place. NUM_TASK?" );
  minigamePlace = pPlace;
  minigamePlace->SetEaselPlayer( this );

  Isolate( true );

  // Избавляемся от стейтов в очереди. 
  FlushStateQueue();

  if (!CheckFlag(NDb::UNITFLAG_INMINIGAME))
    AddFlag(NDb::UNITFLAG_INMINIGAME);

#ifndef VISUAL_CUTTED
  NGameX::AdventureScreen::Instance()->OnEnterLeaveMinigame( this, true );
#endif //VISUAL_CUTTED

  Placement placement = minigamePlace->GetMinigamePlacement();
  minigames->SetPlacement( placement);

  minigames->StartMinigame( pPlace );

  pPlace->OnPlayerEnter();

  //just log mg2 started without params
  LogMinigameEvent(SessionEventType::MG2Started, 0, 0);
  MinigameEvent(NDb::BASEUNITEVENT_MINIGAMESTARTED);

  GetWorld()->SetIgnoreSlowdownHint( true );

  return true;
}


//////////////////////////////////////////////////////////////////////////
bool PFEaselPlayer::OnLeaveMinigameCmd()
{
  DebugTrace( "OnLeaveMinigameCmd..." ); //NUM_TASK debugging

  SetNaftaInfoProvider(0);

  if (CheckFlag(NDb::UNITFLAG_INMINIGAME))
    RemoveFlag(NDb::UNITFLAG_INMINIGAME);

  Isolate( false );

#ifndef VISUAL_CUTTED
  NGameX::AdventureScreen::Instance()->OnEnterLeaveMinigame( this, false );
#endif //VISUAL_CUTTED

  if ( minigames )
    minigames->LeaveMinigame();

  GetWorld()->SetIgnoreSlowdownHint( false );

  NI_VERIFY( IsValid( minigamePlace ), "minigame place somehow is not valid. may be NUM_TASK?",  minigamePlace = 0; return true; );
  minigamePlace->OnPlayerLeave();
  minigamePlace->SetEaselPlayer( 0 );
  minigamePlace = 0;

  LogMinigameEvent(SessionEventType::MG2Exit, 0, 0);
  MinigameEvent(NDb::BASEUNITEVENT_MINIGAMEEXIT);

  return true;
}



void PFEaselPlayer::GetItemTransferTargets( vector<CPtr<PFBaseHero>> & targets )
{
  targets.clear();

  NDb::EFaction we = GetFaction();

  const PFWorld * world = GetWorld();
  for ( int i = 0; i < world->GetPlayersCount(); ++i )
  {
    PFPlayer * player = world->GetPlayer( i );
    PFBaseHero * hero = player->GetHero();
    if ( !hero )
      continue;

    hero->IsLocal();

    if ( hero->GetFaction() != we )
      continue;

    targets.push_back( hero );
  }
}

bool PFEaselPlayer::CanGetScrollDuplicate( PFBaseHero * target )
{
  if ( this == target )
    return false;

  const float probability = GetVariableValue( UnitVariables::szScrollDuplicationProc );

  return GetWorld()->GetRndGen()->Roll( probability );
}

bool PFEaselPlayer::AddItemToHero( PFBaseHero * target, const NDb::Consumable * pDBDesc, int quantity )
{
  if ( target )
  {
    const EPlayerBehaviourEvent::Enum behaviourEvent = (this == target)
      ? EPlayerBehaviourEvent::TookScroll
      : EPlayerBehaviourEvent::GaveScroll;

    PlayerBehaviourTracking::DispatchEvent(this, behaviourEvent);

    // Gain the same scroll if possible
    if ( CanGetScrollDuplicate( target ) )
    {
      if ( this->TakeConsumable( pDBDesc, quantity, NDb::CONSUMABLEORIGIN_MINIGAME ) )
      {
        GetWorld()->GetStatistics()->NotifyItemTransfer( this, this, pDBDesc );
      }
    }

    if ( target->TakeConsumable( pDBDesc, quantity, NDb::CONSUMABLEORIGIN_MINIGAME ) )
    {
      GetWorld()->GetStatistics()->NotifyItemTransfer( this, target, pDBDesc );
      // Play FX on a local hero who gained scroll
      if ( this != target && target->IsLocal() )
      {
        target->OnScrollReceived();
      }
      return true;
    }
  }
  return false;
}



void PFEaselPlayer::SetCurrentBidon( NDb::EBidonType _bidon ) 
{ 
  //TODO refactor this

  if ( NDb::BIDONTYPE_NONE <= _bidon && _bidon <= NDb::BIDONTYPE_PALETTE )
  {
    bidon = _bidon; 

    if ( !IsValid( minigames ) )
      return;

    const NDb::Bidon& bidonDesc = minigames->GetMain()->GetCommonDBData()->sessionBidonAbilities[bidon];

    if ( !bidonDesc.ability )
      return;

    //CALL_CLIENT_1ARGS(OnChangeBidon, bidonDesc );

    PFAbilityData *pA = new PFAbilityData(this, bidonDesc.ability, NDb::ABILITYTYPEID_ABILITY2 );
    SetAbility(NDb::ABILITY_ID_2, pA);
  }
}

void PFEaselPlayer::SetNaftaInfoProvider( NGameX::INaftaInfoProvider * naftaInfoProvider )
{
  NGameX::IAdventureScreen * advScreen = GetWorld()->GetIAdventureScreen();
   if (IsValid(advScreen))
     advScreen->SetNaftaInfoProvider(naftaInfoProvider);

}

bool PFEaselPlayer::CanBuyZZBoost()
{
  NGameX::IAdventureScreen * advScreen = GetWorld()->GetIAdventureScreen();
  NI_VERIFY(IsValid(advScreen), "", return false;)
  ImpulsiveBuffsManager * buffsManager = advScreen->GetImpulseBuffsManager();
  NI_VERIFY(IsValid(buffsManager), "impulse buff manager is not setted", return false;)

  return buffsManager->CanBuyService(NDb::GENERALSERVICES_ZZBOOST);
}

void PFEaselPlayer::BuyZZBoost()
{
  if (!IsLocal())
    return;
  NGameX::IAdventureScreen * advScreen = GetWorld()->GetIAdventureScreen();
  NI_VERIFY(IsValid(advScreen), "", return ;);
  ImpulsiveBuffsManager * buffsManager = advScreen->GetImpulseBuffsManager();
  NI_VERIFY(IsValid(buffsManager), "impulse buff manager is not setted", return;);
  buffsManager->BuyService(NDb::GENERALSERVICES_ZZBOOST);
}

void PFEaselPlayer::LogMinigameEvent( SessionEventType::EventType eventType, int param1, int param2 )
{
  StatisticService::RPC::SessionEventInfo params;
  params.intParam1 = param1;
  params.intParam2 = param2;
  LogSessionEvent(eventType,params);
}

void PFEaselPlayer::OnMapLoaded()
{
  if( IsValid( minigames ) )
    minigames->OnMapLoaded();
}

void PFEaselPlayer::MinigameEvent( NDb::EBaseUnitEvent eventType)
{
  PFBaseUnitMinigameEvent evt(eventType, this);
  EventHappened(evt);
}

void PFEaselPlayer::OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/)
{
  if (CheckFlagType(NDb::UNITFLAGTYPE_INMINIGAME))
  {
    minigames->GetCurrentMinigame()->Eject();
  }

  PFBaseHero::OnUnitDie(pKiller, flags, pDamageDesc);
}

} //namespace NWorld

REGISTER_WORLD_OBJECT_NM( PFEaselPlayer, NWorld )
BASIC_REGISTER_CLASS( PF_Minigames::IMinigames );
