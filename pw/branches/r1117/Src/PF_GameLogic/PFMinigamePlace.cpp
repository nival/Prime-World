#include "stdafx.h"

#ifndef VISUAL_CUTTED

#include "PFMinigamePlace.h"
#include "PFClientMinigamePlace.h"
#include "PFEaselPlayer.h"

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////
PFMinigamePlace::PFMinigamePlace(PFWorld* pWorld, NDb::AdvMapObject const& dbObject) : 
  PFBuilding(pWorld, dbObject),
  radiusPow2(1.f),
  scale(1.f),
  visualState(NDb::MINIGAMEVISUALSTATE_NONE),
  placementApplyType(NDb::CHANGESAPPLYTYPE_DONOTAPPLY)
{
  minigamePlaceDB = dynamic_cast<NDb::MinigamePlace const*>(dbObjectCopy.gameObject.GetPtr());
  NI_VERIFY( IsValid(minigamePlaceDB), "PFMinigamePlace: Invalid game object for the Minigame Place", return; );

  minigameId = minigamePlaceDB->minigameId;
  
  basePlacement = dbObject.offset.GetPlace();
  NScene::PlaceOnTerrain( pWorld->GetScene()->GetHeightsController(), basePlacement.pos );
  animatedPlacement.SetPlacement(basePlacement);

	NGameX::PFClientLogicObject::CreatePars cp( pWorld->GetScene(), BADNODENAME, dbObject );
	CreateClientObject<NGameX::PFClientMinigamePlace>( cp, pWorld->GetScene(), minigamePlaceDB.GetPtr() ); //HAS
	Init(dbObject, minigamePlaceDB, NDb::UNITTYPE_MINIGAMEPLACE);

  CALL_CLIENT_1ARGS( SetIdleEffect, minigamePlaceDB->onIdleEffect );
  CALL_CLIENT( OnUnlocked );

  if ( IsValid( dbObject.gameObject ) )
  {
    radiusPow2 = fabs2( dbObject.gameObject->collision.x2, dbObject.gameObject->collision.x2 );
    scale = fabs( dbObject.gameObject->collision.x2 );
  }

  SetVulnerable( false );

  visualState = NDb::MINIGAMEVISUALSTATE_SESSION;
}

CObj<PFAbilityInstance> PFMinigamePlace::Use( PFBaseUnit* pUser )
{
  PFEaselPlayer * easelPlayer = dynamic_cast<PFEaselPlayer *>( pUser );
  NI_ASSERT( easelPlayer, "" );

  easelPlayer->StartMinigame( this );
  return 0;
}

// Can building be used by a unit at the moment
bool PFMinigamePlace::CanBeUsedBy( PFBaseHero const* pHero ) const
{
  return !pHero->IsMounted() && CheckFlagType( NDb::UNITFLAGTYPE_FORBIDINTERACT ) == false;
}

void PFMinigamePlace::Reset()
{
  // [AZ] no need to recreate client for minigame

  // [IM] для того чтобы отвалившийся юзер после реконнекта видел удаленную миниигру в функционирующем состоянии, она должна переинитится
  PFEaselPlayer* pPlayer = CurrentEaselPlayer();
  SetEaselPlayer(0);
  if (pPlayer)
    Use( pPlayer );
}

void PFMinigamePlace::OnPlayerEnter()
{
  CALL_CLIENT( OnLocked );
}

void PFMinigamePlace::OnPlayerLeave()
{
  CALL_CLIENT( OnUnlocked );
}

//////////////////////////////////////////////////////////////////////////
PFMinigamePlace::~PFMinigamePlace()
{
  CALL_CLIENT( OnLocked );
}

//////////////////////////////////////////////////////////////////////////
const Placement& PFMinigamePlace::GetMinigamePlacement() const
{
  return animatedPlacement.GetPlacement();
}

//////////////////////////////////////////////////////////////////////////
bool PFMinigamePlace::Step( float dtInSeconds )
{
  NI_PROFILE_FUNCTION
  
  // пересчитываем анимированую позицию объекта
  animatedPlacement.Step(dtInSeconds);
  

  if( IsValid(ClientObject()) && placementApplyType !=  NDb::CHANGESAPPLYTYPE_DONOTAPPLY && placementApplyType != NDb::CHANGESAPPLYTYPE_APPLYDEFAULT)
  {
    const Placement& oldPlacement = ClientObject()->GetPosition();
    const Placement& newPlacement = animatedPlacement.GetPlacement();

    if( memcmp(&newPlacement, &oldPlacement, sizeof(Placement)) != 0)
    {
      CALL_CLIENT_1ARGS(ForcePlacement, newPlacement);
    }
  }

  return PFBuilding::Step( dtInSeconds );
}

//////////////////////////////////////////////////////////////////////////
bool PFMinigamePlace::IsAvailable()
{
  return CurrentEaselPlayer() ? false : true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::MinigameVisualStateChange> PFMinigamePlace::ChangeVisualState(NDb::MinigameVisualState _state, NDb::MinigameClientType _clientType)
{
  NDb::Ptr<NDb::MinigameVisualStateChange> stateChange = GetVisualStateChangeParams(visualState, _state, _clientType);
  if(IsValid(stateChange))
  {
    ChangePositionForVisualState(*stateChange);
  }

  visualState = _state;

  return stateChange;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::Ptr<NDb::MinigameVisualStateChange> PFMinigamePlace::GetVisualStateChangeParams(NDb::MinigameVisualState fromState
                                                                                     , NDb::MinigameVisualState toState, NDb::MinigameClientType _clientType)
{
  NI_VERIFY(IsValid(minigamePlaceDB), "PFMinigamePlace: minigame place db is invalid", return NDb::Ptr<NDb::MinigameVisualStateChange>());

  if(!IsValid(minigamePlaceDB->placeParams))
  {
    return NDb::Ptr<NDb::MinigameVisualStateChange>();
  }

  const vector<NDb::Ptr<NDb::MinigameVisualStateChange>>& stateChanges = minigamePlaceDB->placeParams->stateChanges;

  int size = stateChanges.size();
  for(int i = 0; i < size; ++i)
  {
    const NDb::Ptr<NDb::MinigameVisualStateChange>& currentStateChange = stateChanges[i];
    if(!IsValid(currentStateChange))
    {
      continue;
    }

    if(currentStateChange->clientType != NDb::MINIGAMECLIENTTYPE_ANY && currentStateChange->clientType != _clientType)
    {
      continue;
    }

    if(currentStateChange->fromState == fromState && currentStateChange->toState == toState)
    {
      return currentStateChange;
    }
  }

  return NDb::Ptr<NDb::MinigameVisualStateChange>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFMinigamePlace::ChangePositionForVisualState(const NDb::MinigameVisualStateChange& _stateChangeParams)
{

  placementApplyType = _stateChangeParams.changePlacement;

  switch(_stateChangeParams.changePlacement)
  {
  case NDb::CHANGESAPPLYTYPE_DONOTAPPLY:
    break;

  case NDb::CHANGESAPPLYTYPE_APPLYDEFAULT:
    animatedPlacement.SetBase(NULLPLACEMENT.pos, NULLPLACEMENT.rot, NULLPLACEMENT.scale);
    animatedPlacement.SetPlacement( basePlacement );
    break;

  case NDb::CHANGESAPPLYTYPE_APPLYABSOLUTEROTATION:
    animatedPlacement.SetBase(basePlacement.pos, CQuat(0, 0, 0), basePlacement.scale);
    animatedPlacement.Init(_stateChangeParams.newPlacement, 0.0f);
    break;

  case NDb::CHANGESAPPLYTYPE_APPLYABSOLUTEALL:
    animatedPlacement.SetBase(NULLPLACEMENT.pos, NULLPLACEMENT.rot, NULLPLACEMENT.scale);
    animatedPlacement.Init(_stateChangeParams.newPlacement, 0.0f);
    break;


  case NDb::CHANGESAPPLYTYPE_APPLYRELATIONAL:
    animatedPlacement.SetBase(basePlacement.pos, basePlacement.rot, basePlacement.scale);
    animatedPlacement.Init(_stateChangeParams.newPlacement, 0.0f);
    break;

  default:
    NI_ALWAYS_ASSERT("PFClientMinigamePlace: unknown placement apply type");
  }

  if(ClientObject())
  {
    CALL_CLIENT_1ARGS(ForcePlacement, animatedPlacement.GetPlacement());
  }
}

} // namespace NWorld

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFMinigamePlace, NWorld)

#endif
