#include "stdafx.h"
#include "PFLogicObject.h"
#include "TileMap.h"
#include "../Terrain/Terrain.h"
#include "PFWorldNatureMap.h"

#ifndef VISUAL_CUTTED
#include "PFClientLogicObject.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFLogicObject::PFLogicObject(PFWorld* _pWorld, const CVec3 &pos, const NDb::GameObject* objectDesc)
  : PFWorldObjectBase( _pWorld, 1 )
  , health(0.0f)
  , type(NDb::UNITTYPE_CREEP)
  , faction(NDb::FACTION_NEUTRAL)
  , playerId(0)
  , natureType(0)
  , position(pos)
  , objectSize(0.0f)
  , objectTileSize(0)
  , objectDynTileSize(0)
  , isRounded(false)
  , hiddenCounter(0)
{
  isRounded      = objectDesc ? objectDesc->rounded : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::RegisterInAIWorld()
{
  NI_ASSERT(GetWorld()->GetAIWorld(), "No AI World!");
  GetWorld()->GetAIWorld()->RegisterObject(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::Initialize(InitData const& data)
{
  type              = data.type;
  faction           = data.faction;
  playerId          = data.playerId;

  RegisterInAIWorld();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::EFaction PFLogicObject::GetOppositeFaction() const
{
  switch (faction)
  {
  case NDb::FACTION_FREEZE:
    return NDb::FACTION_BURN;
  case NDb::FACTION_BURN:
    return NDb::FACTION_FREEZE;
  default:
    return NDb::FACTION_NEUTRAL; // just to return something
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::OnDie()
{
  if (ringField.isLinked())
	  GetWorld()->GetAIWorld()->UnregisterObjectOrUnit(this);
  
  PFWorldObjectBase::OnDie();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::OnDestroyContents()
{
  NI_VERIFY(!ringField.isLinked(), "Object should not be linked!", GetWorld()->GetAIWorld()->UnregisterObjectOrUnit(this););
  
  PFWorldObjectBase::OnDestroyContents();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::UpdateNatureType()
{
  natureType = GetWorld()->GetNatureMap()->GetNatureInPoint( position.X(), position.Y() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::UpdateDayNightState(const bool night)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFLogicObject::GetOppositeFactionFlags() const
{
  switch (faction)
  {
  case NDb::FACTION_NEUTRAL:
    return (1L << NDb::FACTION_BURN)|(1L << NDb::FACTION_FREEZE);
  case NDb::FACTION_FREEZE:
    return (1L << NDb::FACTION_BURN)|(1L << NDb::FACTION_NEUTRAL);
  case NDb::FACTION_BURN:
    return (1L << NDb::FACTION_FREEZE)|(1L << NDb::FACTION_NEUTRAL);
  default:
    NI_ALWAYS_ASSERT("Invalid faction in PFBaseUnit");
  }
  return ((1L << NDb::FACTION_BURN)|(1L << NDb::FACTION_FREEZE)|(1L << NDb::FACTION_NEUTRAL));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFLogicObject::GetFactionMask( int flags ) const
{
  int factionFlags = 0;
  if( flags & NDb::FACTIONFLAGS_FACTIONFREEZE )
    factionFlags |= (1 << NDb::FACTION_FREEZE);
  if( flags & NDb::FACTIONFLAGS_FACTIONBURN )
    factionFlags |= (1 << NDb::FACTION_BURN);
  if( flags & NDb::FACTIONFLAGS_NEUTRAL )
    factionFlags |= (1 << NDb::FACTION_NEUTRAL);
  if( flags & NDb::FACTIONFLAGS_SELF )
    factionFlags |= (1 << GetFaction() );
  if( flags & NDb::FACTIONFLAGS_OPPOSITE )
    factionFlags |= ( GetOppositeFactionFlags() & ~(1 << NDb::FACTION_NEUTRAL) ) ;

  return factionFlags;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFLogicObject::GetOnBase() const
{
  NDb::ENatureRoad road = NDb::NATUREROAD_CENTER;
  int segment = -1;
  GetWorld()->GetNatureMap()->GetNatureSegment( position.AsVec2D(), road, segment );
  return segment == 0 || segment == GetWorld()->GetNatureMap()->GetNumSegments();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFLogicObject::UnitCheck(UnitCheckID id) const 
{ 
	switch (id)
	{
	case UNITCHECKID_ISHERO: return type == NDb::UNITTYPE_HEROMALE || type == NDb::UNITTYPE_HEROFEMALE;
	case UNITCHECKID_ISBUILDING: return type == NDb::UNITTYPE_BUILDING || type == NDb::UNITTYPE_MAINBUILDING || type == NDb::UNITTYPE_TOWER;
	default: NI_ALWAYS_ASSERT("Unknown check id"); return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFLogicObject::GetTeamId()const
{
  return (faction == NDb::FACTION_FREEZE) ? NCore::ETeam::Team1 : (faction == NDb::FACTION_BURN) ? NCore::ETeam::Team2 : NCore::ETeam::None;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::ChangeFaction( NDb::EFaction newFaction )
{
	faction = newFaction;
}

void PFLogicObject::UpdateHiddenState( bool bVisiblility  )
{
  if (bVisiblility)
  {
    NI_ASSERT(hiddenCounter > 0, "PFClientLogicObject::hiddenCounter counter logic failure");
    if (--hiddenCounter == 0)
      CALL_CLIENT( RevalidateVisibility ); // update visibility
  }
  else
  {
    if (++hiddenCounter == 1)
      CALL_CLIENT( RevalidateVisibility ); // update visibility
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 PFLogicObject::GetVisualPosition3D() const
{
	const NScene::IScene *pScene = GetWorld()->GetScene();
  
  if (!pScene)
    return VNULL3;

	const NScene::IHeightsController& heights = pScene->GetHeightsController();

	CVec3 result = GetPosition();
	heights.GetHeight(result.x, result.y, 1, &result.z, NULL);
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFLogicObject::SetObjectSizes(float size, int tileSize, int dynamicTileSize)
{ 
  SetObjectSize(size); 
  SetObjectTileSize(tileSize); 
  SetObjectDynamicTileSize(dynamicTileSize); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVec3 PFLogicObject::GetClientPosition() const
{
  NGameX::PFClientLogicObject const* pClient = ClientObject();
  if (pClient)
    return pClient->GetPosition().pos;
  else
    return GetVisualPosition3D();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFLogicObject::IsInRange( const CVec2& aimerPos, float range ) const
{
  // ( aimerPos <--> this->edge )
  const float halfObjectSize = GetObjectSize() * 0.5f;
  const float distance2 = fabs2( GetPosition().AsVec2D() - aimerPos );

  return ( distance2 <= fabs2( range + halfObjectSize ) );
}

bool PFLogicObject::IsObjectInRange( const PFLogicObject* pTargetObject, float range ) const
{
  // ( this->center <--> pTarget->edge )
  return pTargetObject->IsInRange( GetPosition().AsVec2D(), range );
}

bool PFLogicObject::IsPositionInRange( const CVec2& targetPos, float range ) const
{
  // ( this->center <--> targetPos )
  return ( fabs2( GetPosition().AsVec2D() - targetPos ) <= fabs2( range ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} //namespace NWorld

BASIC_REGISTER_CLASS(NWorld::PFLogicObject)
WORLD_OBJECT_FUNCTIONS_NM(PFLogicObject, NWorld)

