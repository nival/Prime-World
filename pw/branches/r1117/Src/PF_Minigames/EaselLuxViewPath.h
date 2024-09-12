#pragma once

#include "RollCoordsConverter.h"
#include "ViewBallCoordsConverter.h"

namespace PF_Core
{
  class BasicEffectStandalone;
}

namespace PF_Minigames
{

class MinigameClientObject;
class LuxPath;
class Easel;
class PathConverter;
class LuxGameLogic;

//////////////////////////////////////////////////////////////////////////
//
// wrapper class on View Path object
// creates leafs path, startpoint path, end point path (well)
// creates path Converter object
//
//////////////////////////////////////////////////////////////////////////
class EaselLuxViewPath : public CObjectBase
{
  OBJECT_BASIC_METHODS( EaselLuxViewPath )

public:
  EaselLuxViewPath( const CPtr<Easel>& _easel, LuxPath* _path );
  ~EaselLuxViewPath();

  // getters
  SplineBallCoordsConverter* GetCoordsConverter() { return coordsConverter; };


  void Uninit();

  void Step( float deltaTime, LuxGameLogic* _gameLogic );

private:
  EaselLuxViewPath() {}

  bool InitStartPos( const CPtr<Easel>& _easel, LuxPath* _path );
  bool InitEndPos( const CPtr<Easel>& _easel, LuxPath* _path );

  void CleanUp();
  void CleanUpPath();

  void CreateNewPathHeadEffect( LuxGameLogic* _gameLogic );
  void ReleasePathHeadEffect();

  void CreateNewPathTailEffect( LuxGameLogic* _gameLogic, bool visible );

  void PlaceEffectOnPath( PF_Core::BasicEffectStandalone* _effect, int64 _pathPos );

  CPtr<Easel> easel;

  CObj<PathConverter> pathConverter;
  CObj<BambooRollInConverter> rollInConverter;
  CObj<WellRollOutConverter> rollOutConverter;

  CObj<SplineBallCoordsConverter> coordsConverter;

  CPtr<LuxPath> path;
  
  typedef nstl::vector<CPtr<MinigameClientObject>> PathObjects;
  typedef nstl::list<CObj<PF_Core::BasicEffectStandalone>> PathTailObjects;

  PathObjects pathObjects;

  bool firstRun;
  int64 coveredPath;

  CObj<PF_Core::BasicEffectStandalone> pathHeadEffect;
  PathTailObjects pathTail;
};

}