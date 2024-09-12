#include "stdafx.h"

#include "PFFlagpole.h"
#include "PFWorldNatureMap.h"
#include "../Terrain/Terrain.h"
#include "../System/InlineProfiler.h"

#ifndef VISUAL_CUTTED
#include "PFClientNatureMap.h"
#include "AdventureScreen.h"
#include "../Terrain/NatureMap.h"
#else
#include "../Game/pf/Audit/ClientStubs.h"
#endif

namespace NWorld
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFWorldNatureMap::PFWorldNatureMap(PFWorld *pWorld)
: PFWorldObjectBase( pWorld, 1 )
, pMap(0)
, customNaturePercents(VNULL2)
#ifndef _SHIPPING
, overrideFaction( NDb::FACTION_NEUTRAL )
, overridePoint( VNULL2 )
, overrideRadius( 0.0f )
, overrideTime( -1.0f )
#endif
{
  CreateClientObject<NGameX::PFClientNatureMap>();
}

void PFWorldNatureMap::Reset()
{
	PFWorldObjectBase::Reset();
	CreateClientObject<NGameX::PFClientNatureMap>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFWorldNatureMap::OnLoaded(const NDb::Ptr<NDb::Terrain>& pDBTerrain_)
{
  NI_PROFILE_FUNCTION

  pDBTerrain = pDBTerrain_;
  NI_VERIFY( pDBTerrain && pDBTerrain->natureMap.attackSpaceRoads.size(), "DBNatureMap not defined properly!", return; );
  NI_VERIFY( pDBTerrain && pDBTerrain->natureMap.logicRoads.size(), "DBNatureMap not defined properly!", return; );

  if (PFWorld * pWorld = GetWorld())
    if (NScene::IScene* pScene = pWorld->GetScene())
      if (Terrain::Terrain* pTerrain = pScene->GetTerrain())
        pMap = &pTerrain->GetNatureMap();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PFWorldNatureMap::LocateElement(float x, float y) const
{
  return pMap ? pMap->LocateElement(x, y) : Terrain::NATUREMAPELEMENTID_BAD;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PFWorldNatureMap::GetNatureInPoint(float x, float y) const
{
  return pMap ? pMap->GetNature(x, y) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int PFWorldNatureMap::GetNatureInPoint(int id) const
{
  return pMap ? pMap->GetNature(id) : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PFWorldNatureMap::IsAtBase(float x, float y) const
{
  return pMap ? pMap->IsAtBase(x, y) : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float PFWorldNatureMap::GetNaturePercent(NDb::EFaction faction) const
{
  NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
  if ( pDBTerrain && pDBTerrain->natureMap.editableNatureMap )
  {
    return faction == NDb::FACTION_FREEZE ? customNaturePercents.m[0] : 
      ( faction == NDb::FACTION_BURN ? customNaturePercents.m[1] : 1.f - customNaturePercents.m[0] - customNaturePercents.m[1]  );
  }

  return pMap ? pMap->GetNaturePercent((NDb::ENatureType)faction) : 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float PFWorldNatureMap::GetNaturePercent(NDb::EFaction faction, NDb::ENatureRoad roadIndex) const
{
  NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
  NI_STATIC_ASSERT(NDb::KnownEnum<NDb::ENatureRoad>::sizeOf == 3, THERE_MUST_BE_THREE_ROADS);
  return pMap ? pMap->GetNaturePercent((NDb::ENatureType)faction, roadIndex) : 0.0f;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::SetCustomNaturePercents( float freeze, float burn )
{
  NI_VERIFY( pDBTerrain->natureMap.editableNatureMap, "Custom nature percent can be used on map with editable terrain", return );
  NI_VERIFY( freeze + burn <= 1.f, "Invalid custom nature percent: should be <1 total", freeze /= freeze + burn; burn /= freeze + burn );
  customNaturePercents.m[0] = freeze;
  customNaturePercents.m[1] = burn;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFWorldNatureMap::GetNumSegments() const
{
  return pMap ? pMap->GetNumSegments() : 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFWorldNatureMap::GetNatureBorders(NDb::EFaction faction, CVec2 roadPoints[]) const
{
  if (pMap)
  {
    NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
    NI_STATIC_ASSERT(NDb::KnownEnum<NDb::ENatureRoad>::sizeOf == 3, THERE_MUST_BE_THREE_ROADS);
    roadPoints[0] = pMap->GetNatureBound((NDb::ENatureType)faction, NDb::NATUREROAD_TOP);
    roadPoints[1] = pMap->GetNatureBound((NDb::ENatureType)faction, NDb::NATUREROAD_CENTER);
    roadPoints[2] = pMap->GetNatureBound((NDb::ENatureType)faction, NDb::NATUREROAD_BOTTOM);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::GetNatureSegment(CVec2 const &pos, NDb::ENatureRoad &road, int &segment) const
{
  if (pMap)
    pMap->GetNatureSegment(pos, road, segment);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::SetDesiredPosition(NDb::EFaction faction, NDb::ENatureRoad road, int segment)
{
  NI_VERIFY(faction == 1 || faction == 2, "Invalid faction index", return;); 
  NI_VERIFY(road >= 0 && road <= 2, "Invalid road", return;);  
  NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
  
  if (pMap)
    pMap->SetDesiredPosition((NDb::ENatureType)faction, road, segment);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFWorldNatureMap::Expand(NDb::EFaction faction, NDb::ENatureRoad roadIndex, int numSegments)
{
  NI_ALWAYS_ASSERT("Obsolete method PFWorldNatureMap::Expand is called. The caller must be refactored according to new design.");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PFWorldNatureMap::Override(NDb::EFaction faction, const CCircle & circle, float lifeTime, unsigned ownerData)
{
  NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
  if (pMap)
    pMap->Override((NDb::ENatureType)faction, circle, lifeTime, ownerData);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::DebugOverride(NDb::EFaction faction, CVec2 const &center, float radius, float lifeTime)
{
#ifndef _SHIPPING
  overrideFaction = faction;
  overridePoint = center;
  overrideRadius = radius;
  overrideTime = lifeTime;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
  struct NatureChnager : public NonCopyable
  {
  public :
    NatureChnager(Terrain::NatureMap& nmap, NDb::ENatureType from, NDb::ENatureType to )
      : nmap(nmap), from(from), to(to) {}
    void operator()(const CVec2& elemPos, Terrain::NatureMapElementId id, Terrain::NatureMapElementInfo const& info)
    {  
      if ( (int)from >= 0 && info.natureBase != (uint)from )
        return;

      nmap.EditNature( id, to );
    }

    Terrain::NatureMap& nmap;
    NDb::ENatureType from;
    NDb::ENatureType to;
  }; 

}
void PFWorldNatureMap::ChangeNature( CVec2 const &pos, float radius, NDb::ENatureType from, NDb::ENatureType to )
{
  if (!pMap)
    return;

  if ( radius <= 0 )
    return;

  NatureChnager func( *pMap, from, to );
  pMap->ForAllElementsInCircle( func, pos, radius );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::ChangeNature( const vector<CVec2>& polygon, NDb::ENatureType from, NDb::ENatureType to )
{
  if (!pMap)
    return;
  if( polygon.empty() )
    return;

  NatureChnager func( *pMap, from, to );
  pMap->ForAllElementsInPolygon( func, polygon );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFWorldNatureMap::IsOverrideActive(unsigned int ownerData) const
{
  return pMap ? pMap->IsOverrideActive(ownerData) : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWorldNatureMap::OnStep(float dt)
{
  NI_PROFILE_FUNCTION

  if (pMap)                                                                                                                                        
  {
#ifndef _SHIPPING
    // execute postponed debug command
    if (overrideTime > 0.0f)
    {
      static unsigned int overrideId = 0x000FFFFF; // Just a big number so we won't get ids collision
      NI_STATIC_ASSERT(NDb::KnownEnum<NDb::EFaction>::sizeOf == NDb::KnownEnum<NDb::ENatureType>::sizeOf, ASSUME_FACTIONS_EQ_NATURES);
      pMap->Override((NDb::ENatureType)overrideFaction, CCircle(overridePoint, overrideRadius), overrideTime, overrideId);
      ++overrideId;
      overrideTime = -1.0f;
    }
#endif

    bool changed = pMap->OnStep(dt);
    if (changed)
    {
      struct 
      {
        void operator()(PFLogicObject& o) { o.UpdateNatureType(); }
      } updateNatureType;

      if (PFWorld * pWorld = GetWorld())
      {
        pWorld->GetAIWorld()->ForAllObjects(updateNatureType);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int PFWorldNatureMap::operator&( IBinSaver &f )
{
  f.Add(1,(PFWorldObjectBase*)this); 
  f.Add(2,pMap);  
  f.Add(3, &customNaturePercents);
  return 0;
}


} // namespace

REGISTER_WORLD_OBJECT_WITH_CLIENT_NM(PFWorldNatureMap, NWorld)


