#include "stdafx.h"

#include "PFAbilityData.h"
#include "PFAdvMapObject.h"
#include "PFClientFlagpole.h"
#include "PFFlagpole.h"
#include "PFTargetSelector.h"
#include "PFWorldNatureMap.h"
#include "TileMap.h"
#include "SessionEventType.h"
#include "PFStatistics.h"
#include "PFMaleHero.h"
#include "PFClientHero.h"


namespace NWorld
{

PFFlagpole::PFFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject)
: PFBaseUnit( pWorld, _dbObject.offset.GetPlace().pos, static_cast<NDb::Flagpole const*>( _dbObject.gameObject.GetPtr() ) )
, isRising( false )
, dbObject( _dbObject )
{
  const NDb::Flagpole* db = dynamic_cast<const NDb::Flagpole*>(dbObject.gameObject.GetPtr());
  NI_VERIFY( db, "Need gameObject to create Flagpole!", return; );

  CreateClientObject<NGameX::PFClientFlagpole>(dbObject, pWorld->GetScene());

  PFBaseUnit::InitData data;
  data.faction      = NDb::FACTION_NEUTRAL;
  data.type         = NDb::UNITTYPE_FLAGPOLE;
  data.playerId     = -1; 
  data.pObjectDesc  = db;
  Initialize(data);
  InitBaseAttack();

  MarkObject(pWorld->GetTileMap(), dbObject, occupiedTiles);
  pWorld->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);

  health = GetMaxHealth();
  AddFlag( NDb::UNITFLAG_FORBIDAUTOTARGETME );
  AddFlag( NDb::UNITFLAG_FORBIDATTACK );
  AddFlag( NDb::UNITFLAG_FORBIDSELECTTARGET );
  lastSetVulnerable = true;
  UpdateVulnerable();

  // Upgrade building's abilities
  UpgradeAbilities();
}

void PFFlagpole::Reset()
{
	PFBaseUnit::Reset();
	CreateClientObject<NGameX::PFClientFlagpole>(dbObject, GetWorld()->GetScene());
}

void PFFlagpole::OnStartRaise( int teamId, const float raiseTime )
{
  isRising = true;
  CALL_CLIENT( OnStartRaiseFlag );
}

void PFFlagpole::OnCancelRaise()
{
  if ( isRising )
    CALL_CLIENT( OnDropFlag );

  isRising = false;
}

void PFFlagpole::OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised )
{
  NI_ASSERT( !IsVulnerable(), "Flagpole should be invulnerable before raise" );
  if (unitWhoRaised)
  {
    if (NWorld::PFWorld * pWorld = GetWorld())
      if (NWorld::PFStatistics * pStatistics = pWorld->GetStatistics())
        pStatistics->AddFlagRaised(unitWhoRaised);

    LogFlagEvent(_faction, unitWhoRaised, true);
  }

  ChangeFaction( _faction );
  health = GetMaxHealth();
  RemoveFlag( NDb::UNITFLAG_FORBIDAUTOTARGETME );

  UpdateVulnerable();

  if ( PFFlagpole* prev = GetPrevFlagpole( faction ) )
  {
    prev->UpdateVulnerable();
  }

  isRising = false;
  
  CALL_CLIENT_1ARGS( OnRaiseFlag, GetTeamId(faction) );

  const NWorld::PFBaseMaleHero* pHero = dynamic_cast<const NWorld::PFBaseMaleHero*>( unitWhoRaised );

  if( pHero )
    pHero->PlayAskSound( NDb::ASKSOUNDS_RAISEFLAG );
}


void PFFlagpole::OnDropFlag(PFBaseUnit * unitWhoDropped)
{
  if (unitWhoDropped)
  {
    if (NWorld::PFWorld * pWorld = GetWorld())
      if (NWorld::PFStatistics * pStatistics = pWorld->GetStatistics())
        pStatistics->AddFlagDestroyed(unitWhoDropped);

    LogFlagEvent(unitWhoDropped->GetFaction(), unitWhoDropped, false);
  }

  NDb::EFaction oldFaction = faction;

  ChangeFaction( NDb::FACTION_NEUTRAL );
  health = GetMaxHealth();
  AddFlag( NDb::UNITFLAG_FORBIDAUTOTARGETME );
  UpdateVulnerable();

  if ( PFFlagpole* prev = GetPrevFlagpole( oldFaction ) )
  {
    prev->UpdateVulnerable();
  }

  CALL_CLIENT( OnDropFlag );
}

void PFFlagpole::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags /*= UNITDIEFLAGS_NONE*/, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  OnDropFlag( 0 );
  PFBaseUnit::OnUnitDie( pKiller, flags, pDamageDesc );
}

NDb::ETeamID PFFlagpole::GetTeamId( NDb::EFaction faction )
{
  return faction == NDb::FACTION_FREEZE ? NDb::TEAMID_A : NDb::TEAMID_B;
}

const NDb::Texture* PFFlagpole::GetUiAvatarImage() const
{
  if ( !IsNeutral() )
  {
    const NDb::Flagpole* db = static_cast<const NDb::Flagpole*>( DbUnitDesc() );
    const NDb::ETeamID teamId = GetTeamId(faction);
    return db->factionImages[teamId];
  }
  else
  {
    return PFBaseUnit::GetUiAvatarImage();
  }
}

const wstring& PFFlagpole::GetDescription() const
{
  if ( !IsNeutral() )
  {
    const NDb::Flagpole* db = static_cast<const NDb::Flagpole*>( DbUnitDesc() );
    const NDb::ETeamID teamId = GetTeamId(faction);
    return db->factionDescriptions[teamId].GetText();
  }
  else
  {
    return PFBaseUnit::GetDescription();
  }
}

float PFFlagpole::OnDamage(const DamageDesc &desc)
{
  if (desc.amount < EPS_VALUE)
    return 0.0f;

  health -= 1.0f;

  if ( IsDead() )
  {
    OnDropFlag(desc.pSender);
  }
  else
  {
    PFBaseUnitDamageEvent evt(desc, desc.amount);
    EventHappened(evt);
  }

  return 1.0f;
}

void PFFlagpole::UpdateVulnerable()
{
  const bool vulnerable = ( !IsNeutral() && !IsProtected() );

  if ( lastSetVulnerable == vulnerable )
  {
    return;
  }
  SetVulnerable( vulnerable );
  lastSetVulnerable = vulnerable;
}


const PFFlagpole* PFFlagpole::GetPrevFlagpole( NDb::EFaction _faction ) const
{
  return (const_cast<PFFlagpole*>(this))->GetPrevFlagpole(_faction);
}

const PFFlagpole* PFFlagpole::GetNextFlagpole( NDb::EFaction _faction ) const
{
  return (const_cast<PFFlagpole*>(this))->GetNextFlagpole(_faction);
}


void PFFlagpole::OnAfterReset()
{
  PFBaseUnit::OnAfterReset();
  CALL_CLIENT_2ARGS( OnAfterReset, !IsNeutral(), GetTeamId(faction) );
}

void PFFlagpole::Hide(bool hide)
{
  if ( hide )
  {
    AddFlag(NDb::UNITFLAG_ISOLATED);
    GetWorld()->GetTileMap()->MarkObject(occupiedTiles, false, MAP_MODE_BUILDING);
    if ( ringField.isLinked() )
      GetWorld()->GetAIWorld()->UnregisterObjectOrUnit( this );
    WorldObjectBase::Reset();
  }
  else
  {
    RemoveFlag(NDb::UNITFLAG_ISOLATED);
    GetWorld()->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);
    GetWorld()->GetAIWorld()->RegisterUnit(this);
    Reset();
    OnAfterReset();
  }
}


} // end of namespace NWorld

WORLD_OBJECT_FUNCTIONS_NM(PFFlagpole, NWorld);
