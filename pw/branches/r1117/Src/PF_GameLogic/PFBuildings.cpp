#include "stdafx.h"
#include "PFAdvMapObject.h"
#include "PFBuildings.h"
#include "DBStats.h"
#include "TileMap.h"
#include "PFStatistics.h"

#include "PFHero.h"
#include "PFAbilityData.h"
#include "PFBaseAttackData.h"
#include "PFAIWorld.h"
#include "SessionEventType.h"

#include "DBGameLogic.h"
#include "PFClientObjectHelpers.h"

#ifndef VISUAL_CUTTED
#include "PFClientBuilding.h"
#else
#include "../game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBuilding::PFBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBaseUnit( pWorld, dbObject.offset.GetPlace().pos, static_cast<NDb::Building const*>(dbObject.gameObject.GetPtr()) )
  , dbObjectCopy(dbObject)
  , isDenying(false)
  , isDecoration(static_cast<NDb::Building const*>(dbObject.gameObject.GetPtr())->isDecoration)
  ,levelUpInterval(0.f)
  ,levelUpTimer(0.f)
{
  MarkObject(pWorld->GetTileMap(), dbObject, occupiedTiles);
  pWorld->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBuilding::Init(NDb::AdvMapObject const& dbObject, NDb::Building const* pDesc, NDb::EUnitType type)
{
  PFBaseUnit::InitData data;
  data.faction      = pDesc->faction;
  data.type         = type;
  data.playerId     = -1; // buildings are not bound to players
  data.pObjectDesc  = pDesc;
  Initialize(data);
  InitBaseAttack();

  // @BVS@TODO Move this code into some common class
  CQuat res = dbObject.offset.GetPlace().rot;
  CALL_CLIENT_1ARGS(SetRotation, res);

  routeID = pDesc->routeID;
  routeLevel = pDesc->routeLevel;
  PFAIWorld *pAIWorld = GetWorld()->GetAIWorld();
  pAIWorld->OnBuildingCreate( pDesc->faction, pDesc->routeID, pDesc->routeLevel, this );
  
  levelUpInterval = pDesc->levelUpInterval;
  if ( levelUpInterval > 0.f )
    levelUpTimer = pAIWorld->GetBattleStartDelay();
  // Upgrade building's abilities
  UpgradeAbilities();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBuilding::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  PFQuarters* quarter = dynamic_cast<PFQuarters*>(this);

  CPtr<PFBaseUnit> pActualKiller = pKiller;
  GetWorld()->GetAIWorld()->GetKiller( this, pActualKiller );

  if(IsValid(quarter))
    GetWorld()->GetIAdventureScreen()->NotifyPushedLine( quarter, pActualKiller);

  GetWorld()->GetAIWorld()->OnBuildingDestroy( GetFaction(), routeID, routeLevel, GetObjectId(), quarter!=0 );  

  //const NWorld::PFBuilding * quarter, const NWorld::PFBaseUnit * killer

  //log session event
  StatisticService::RPC::SessionEventInfo eventParams;
  eventParams.intParam1  = DbUnitDesc()->GetDBID().GetHashKey();
  
  if( IsValid(pActualKiller) )
  {
    if ( pActualKiller->IsHero() )
    {
      PFBaseHero * heroKiller = static_cast<PFBaseHero *> (pActualKiller.GetPtr());
      eventParams.intParam2 = heroKiller->GetStatisticsUid();  
    }
    else
    {
      eventParams.intParam3 = pActualKiller->DbUnitDesc()->GetDBID().GetHashKey();
    }
  }
  
  //eventParams.intParam4  = isQuarter;
  GetWorld()->GetIAdventureScreen()->LogWorldSessionEvent(SessionEventType::BuildingDestroyed, eventParams);

  // unlock place on TileMap
  //!! NOTE: should use the same MAP_MODE_... as when marking tree on TileMap
  //   from function PFWorld::AddMapObject()
  GetWorld()->GetTileMap()->MarkObject(occupiedTiles, false, MAP_MODE_BUILDING);

  PFBaseUnit::OnUnitDie(pKiller, flags, pDamageDesc);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBuilding::Step(float dtInSeconds)
{
  if ( levelUpInterval > 0.f )
  {
    levelUpTimer -= dtInSeconds;
    if (  levelUpTimer <= 0.f )
    {
      DoLevelups( 1 );
      levelUpTimer = levelUpInterval;
    }
  }

  return PFBaseUnit::Step( dtInSeconds );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFBuilding::CanDenyBuilding( CPtr<PFBaseHero>const& pDennier ) const
{
  if (isDenying)
    return false; // deny dot already activated!
  
  if ( !IsUnitValid(pDennier) || !IsVulnerable() || IsDead() )
    return false; // invalid hero, or can not apply damage to building

  // Check faction
  if ( pDennier->GetFaction() != GetFaction() )
    return false; // wrong faction (building to deny must be same faction as hero is

  // getting deny ability from AILogic.AILP
  const NDb::AILogicParameters& aiParams = GetWorld()->GetAIWorld()->GetAIParameters();

  // Check tower health
  if ( GetHealthPercent() > aiParams.buildingsDenyMinHealth )
    return false; // wrong tower health

  NI_VERIFY( aiParams.buildingsDenyAbility, "Invalid AI parameter buildingsDenyAbility in GameLogic/AILogic.AILP!", return false; );

	// Hacky calculation of use range
	float useRange = aiParams.buildingsDenyAbility->useRange(this, this, pAttackAbility, 0.0f);

  // Check range
  if ( fabs2( pDennier->GetPosition() - GetPosition() ) > fabs2( useRange ) )
    return false; // too far away from building to deny

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBuilding::DenyBuilding( CPtr<PFBaseHero>const& pDennier )
{
  NI_ASSERT( CanDenyBuilding(pDennier), "Need to check if building can be denied first!" );
  pDennier->UseExternalAbility( GetWorld()->GetAIWorld()->GetAIParameters().buildingsDenyAbility, Target(CPtr<PFBaseUnit>(this)) );
}

//////////////////////////////////////////////////////////////////////////
bool PFBuilding::IsInRange( const CVec2& aimerPos, float range ) const
{
  const int rangeInTiles = GetWorld()->GetTileMap()->GetLenghtInTiles( range );
  const SVector aimerTile = GetWorld()->GetTileMap()->GetTile( aimerPos );

  for ( int i = 0; i < occupiedTiles.size(); i++ )
  {
    if ( fabs2( aimerTile - occupiedTiles[i] ) <= fabs2( rangeInTiles ) ) 
    {
      return true;
    }
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////
void PFBuilding::Reset()
{
  PFBaseUnit::Reset();
}

void PFBuilding::OnAfterReset()
{
  PFBaseUnit::OnAfterReset();

  if ( !stateName.empty() )
  {
    CALL_CLIENT_2ARGS( SetAnimState, stateName, true );
  }

  if ( CheckFlag( NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE ) )
  {
    CALL_CLIENT_1ARGS( Hide, true );
  }
  else if ( IsDead() )
  {
    CALL_CLIENT( MakeRuined );
  }
  else 
  {
    CALL_CLIENT( ApplyHealthEffects );
    CALL_CLIENT( ShowFragEffect );
  }
}

void PFBuilding::Hide(bool hide)
{
 // PFBaseUnit::Hide(hide);

  if ( hide )
  {
    AddFlag(NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE);
    GetWorld()->GetTileMap()->MarkObject(occupiedTiles, false, MAP_MODE_BUILDING);
    if (!IsDead())
    {
      if ( ringField.isLinked() )
        GetWorld()->GetAIWorld()->UnregisterObjectOrUnit( this );
      CloseWarFog(true);
    }
 //   WorldObjectBase::Reset();
  }
  else
  {
    RemoveFlag(NDb::UNITFLAG_ISOLATED | NDb::UNITFLAG_INVISIBLE);
    if (!IsDead())
    {
      GetWorld()->GetTileMap()->MarkObject(occupiedTiles, true, MAP_MODE_BUILDING);
      GetWorld()->GetAIWorld()->RegisterUnit(this);
      OpenWarFog();
    }
//    Reset();
 //   OnAfterReset();
  }

  CALL_CLIENT_1ARGS(OnHide, hide);
  UpdateHiddenState( !hide );
  CALL_CLIENT_1ARGS(Hide, hide);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFBuilding::OnHeal( CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods /*= false */ )
{
  float healed = PFBaseUnit::OnHeal( pSender, amount, ignoreHealingMods );
  CALL_CLIENT_2ARGS( OnHeal, GetHealth(), healed );
  return healed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBuilding::MakeLevelupsForTimeDelta( float dtInSeconds )
{
  if ( levelUpInterval > 0.f )
  {
    float timeAfterStep = dtInSeconds + levelUpInterval - levelUpTimer;
    int fullIntervals = (int)floor( timeAfterStep / levelUpInterval );
    float toNextLevelup = timeAfterStep - fullIntervals * levelUpInterval;
    levelUpTimer = levelUpInterval - toNextLevelup;
    DoLevelups( fullIntervals );
  }
}

void PFBuilding::SetState( const string& newStateName )
{
  if ( newStateName.empty() || stateName == newStateName )
    return;

  stateName = newStateName;

  CALL_CLIENT_2ARGS( SetAnimState, stateName, false );
}

//////////////////////////////////////////////////////////////////////////
PFQuarters::PFQuarters(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBuilding(pWorld, dbObject)
{
	const NDb::Quarter* pDesc = dynamic_cast<NDb::Quarter const*>(dbObject.gameObject.GetPtr());
	NI_VERIFY( pDesc, "Invalid game object for the building", return; );

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFBuilding>( cp, pWorld->GetScene(), pDesc );
  Init(dbObject, pDesc, NDb::UNITTYPE_BUILDING);
}

void PFQuarters::Reset()
{
	PFBuilding::Reset();
	NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
	CreateClientObject<NGameX::PFBuilding>( cp, GetWorld()->GetScene(), dbObjectCopy.gameObject.GetPtr() ); //HAS
}

void PFQuarters::OnUnitDie( CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc /*= 0*/ )
{
  GetWorld()->GetStatistics()->AddQuartersDestroy(this, pKiller);
  PFBuilding::OnUnitDie( pKiller, flags, pDamageDesc );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFShop::PFShop(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBuilding(pWorld, dbObject)
  , pDesc( dynamic_cast<NDb::Shop const*>(dbObject.gameObject.GetPtr()) )
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObject.gameObject.GetPtr());
	NI_VERIFY( pDesc, "Invalid game object for the building", return; );

	for ( vector<NDb::Ptr<NDb::Consumable>>::const_iterator iConsumable = pDesc->shop->items.begin(), iEnd = pDesc->shop->items.end(); iConsumable != iEnd; ++iConsumable )
	{
		pWorld->GetIAdventureScreen()->PreloadEffectsInResourceTree( (*iConsumable).GetPtr(), BADNODENAME );
	}

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFBuilding>( cp, pWorld->GetScene(), pDesc ); //HAS
  Init(dbObject, pDesc, NDb::UNITTYPE_SHOP);

  AddFlag( NDb::UNITFLAG_FORBIDTAKEDAMAGE );
}

void PFShop::Reset()
{
	PFBuilding::Reset();
	NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
	CreateClientObject<NGameX::PFBuilding>( cp, GetWorld()->GetScene(), dbObjectCopy.gameObject.GetPtr() ); //HAS
}

float PFShop::GetInteractionRadius() const
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
	return NULL != pDesc ? pDesc->shop->interactionRadius : 0.0f;
}

NDb::ConsumablesShop const* PFShop::GetConsumablesShop() const
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
	return pDesc ? pDesc->shop : NULL;
}
int PFShop::GetNumConsumables() const 
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
	return pDesc && pDesc->shop ? pDesc->shop->items.size() : 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Consumable const* PFShop::GetConsumableDesc(int item) const 
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
	NI_VERIFY( pDesc && pDesc->shop && item >= 0 && item < pDesc->shop->items.size(), "No shop or wrong item index!", return NULL; );
	return pDesc->shop->items[item];
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFShop::IsHeroNear(PFBaseHero const *pHero) const
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
  NI_VERIFY( IsValid(pHero), "Hero must be valid!", return false; );

  if ( !pHero->IsDead() )
    return fabs2(pHero->GetPosition() - GetPosition()) <= (pDesc->shop->interactionRadius * pDesc->shop->interactionRadius);
  else
    return GetFaction() == pHero->GetFaction();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFShop::CanBuyConsumable(PFBaseHero const *pHero, int itemId) const
{
	const NDb::Shop* pDesc = dynamic_cast<NDb::Shop const*>(dbObjectCopy.gameObject.GetPtr());
  NI_VERIFY(pDesc && pDesc->shop && 0 <= itemId && itemId < pDesc->shop->items.size(), "No shop or wrong item index!", return false; );

  // check cost of consumable
  if ( IsHeroNear(pHero) )
  {
    NDb::Ptr<NDb::Consumable> pConsumable = GetConsumableDesc(itemId);
    NI_VERIFY(IsValid(pConsumable), "Consumable we're buying should be present in shop", return false);
    float cost = pHero->GetConsumableCost(pConsumable);
    if ( cost <= pHero->GetGold() )
      return true;
  }

  return false;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class PFSimpleBuilding
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFSimpleBuilding::PFSimpleBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
  : PFBuilding(pWorld, dbObject)
{
	const NDb::Building* pDesc = dynamic_cast<NDb::Building const*>(dbObject.gameObject.GetPtr());
	NI_VERIFY( pDesc, "Invalid game object for the building", return; );

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFBuilding>( cp, pWorld->GetScene(), pDesc ); //HAS
  Init(dbObject, pDesc, NDb::UNITTYPE_BUILDING);
}

void PFSimpleBuilding::Reset()
{
	PFBuilding::Reset();
	NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
	CreateClientObject<NGameX::PFBuilding>( cp, GetWorld()->GetScene(), dbObjectCopy.gameObject.GetPtr() ); //HAS
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFUsableBuilding::PFUsableBuilding(PFWorld* pWorld, NDb::AdvMapObject const& dbObject)
: PFBuilding(pWorld, dbObject)
{
  NDb::UsableBuilding const* pDesc = dynamic_cast<NDb::UsableBuilding const*>(dbObject.gameObject.GetPtr());
  NI_VERIFY( pDesc, "Invalid game object for the building", return; );

  NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
  CreateClientObject<NGameX::PFBuilding>( cp, pWorld->GetScene(), pDesc );
  Init(dbObject, pDesc, NDb::UNITTYPE_SHOP); // UNITTYPE_SHOP best fits for usable building
}

void PFUsableBuilding::Reset()
{
  PFBuilding::Reset();
  NGameX::PFClientLogicObject::CreatePars cp( GetWorld()->GetScene(), BADNODENAME, dbObjectCopy );
  CreateClientObject<NGameX::PFBuilding>( cp, GetWorld()->GetScene(), dbObjectCopy.gameObject.GetPtr() );
}

}

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFBuilding,      NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFQuarters,      NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFShop,          NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFSimpleBuilding,NWorld);
REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFUsableBuilding,NWorld);
