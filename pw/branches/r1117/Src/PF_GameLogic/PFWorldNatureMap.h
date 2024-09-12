#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "../PF_Core/WorldObject.h"
#include "../System/2Darray.h"
#include "PFWorldObjectBase.h"
#include "PFWorld.h"
#include "PFAIWorld.h"
#include "../System/ScopedArray.h"
#include "../Terrain/TerrainLayerManager.h"

namespace NGameX { class PFClientNatureMap; }
namespace Terrain { class NatureMap; }

namespace NWorld
{

class PFWorldNatureMap : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x165C9B80, PFWorldNatureMap, NGameX::PFClientNatureMap)
public:
  PFWorldNatureMap() : pMap(0) {}
  explicit PFWorldNatureMap(PFWorld *pWorld);
  
  void OnLoaded(const NDb::Ptr<NDb::Terrain>& pDBTerrain);
  void OnStep(float dt);
  
  int  LocateElement(float x, float y) const;
  int  GetNatureInPoint(float x, float y) const;
  int  GetNatureInPoint(int) const;

  bool IsAtBase(float x, float y) const;

  void SetDesiredPosition(NDb::EFaction faction, NDb::ENatureRoad road, int segment);
  void Expand(NDb::EFaction faction, NDb::ENatureRoad roadIndex, int numSegments);
  void Override(NDb::EFaction faction, const CCircle & circle, float lifeTime, unsigned ownerData);

  void DebugOverride(NDb::EFaction faction, CVec2 const &center, float radius, float lifeTime);

  // game play service function
  float GetNaturePercent(NDb::EFaction faction) const;
  float GetNaturePercent(NDb::EFaction faction, NDb::ENatureRoad roadIndex) const;
  int GetNumSegments() const;
  void GetNatureBorders(NDb::EFaction faction, CVec2 roadPoints[]) const;
  vector<CVec2> const& GetAttackSpaceRoad(NDb::ENatureRoad roadIndex) const { return pDBTerrain->natureMap.attackSpaceRoads[roadIndex].nodes; }
  vector<CVec2> const& GetLogicRoad(NDb::ENatureRoad roadIndex) const { return pDBTerrain->natureMap.logicRoads[roadIndex].nodes; }
  bool GetUseRoadInPathFinding() const { return pDBTerrain->natureMap.useRoadsInPathFinding; }

  void GetNatureSegment(CVec2 const &pos, NDb::ENatureRoad &road, int &segment) const;

  void SetCustomNaturePercents( float freeze, float burn );
  void ChangeNature( CVec2 const &pos, float radius, NDb::ENatureType from, NDb::ENatureType to );
  void ChangeNature( const vector<CVec2>& polygon, NDb::ENatureType from, NDb::ENatureType to );

  bool IsOverrideActive(unsigned int ownerData) const;

	void Reset();
private:
  NDb::Ptr<NDb::Terrain> pDBTerrain;
  //Ќет ZDATA, т.к. используетс€ пр€ма€ сериализаци€ pMap
  Terrain::NatureMap *pMap;
  CVec2 customNaturePercents; //m[0] for Freeze, m[1] for Burn
public:
  int operator&( IBinSaver &f );

#ifndef _SHIPPING
  NDb::EFaction overrideFaction;
  CVec2 overridePoint;
  float overrideRadius;
  float overrideTime;
#endif
};

} // namespace NWorld

