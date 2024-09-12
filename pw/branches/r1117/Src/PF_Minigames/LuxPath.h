#pragma once

#include "../Scene/DBScene.h"
#include "../PF_Core/WorldObject.h"

namespace NDb
{
  struct DBEaselPath;
  struct DBTunnel;
  struct DBEaselChains;
}

namespace PF_Minigames
{

class PolylineTrajectory;
class LuxGameLogic;

class LuxPath : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D8AF4C0, LuxPath )
  
public:
  LuxPath( PF_Core::IWorld* _pWorld, int _pathID, int _level, const NDb::DBEaselPath * _path );
  ~LuxPath();

  int GetID() const { return pathID; };

  PolylineTrajectory*              GetTrajectory() const;
  const nstl::vector<NDb::DBTunnel>& GetTunnels() const;
  const NDb::DBEaselChains*        GetChainsData() const;
  const NDb::AnimatedPlacement&    GetStartOffset() const;
  const NDb::AnimatedPlacement&    GetEndOffset() const;

  bool IsPointInsideTunnel( int64 _point, LuxGameLogic* _gameLogic ) const;

private:
  LuxPath() {}

  void CreateTrajectory();

  ZDATA_(PF_Core::WorldObjectBase)

  int pathID;
  int level;

  CObj<PolylineTrajectory> trajectory;
  NDb::Ptr<NDb::DBEaselPath> dbPath;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&pathID); f.Add(3,&level); f.Add(4,&trajectory); f.Add(5,&dbPath); return 0; }
};

}
